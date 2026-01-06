#include "../include/files_collector.h"

/*
 * @brief Scan directories and files, filters them according to command line arguments
 */
void CFilesCollector::CollectFiles(const std::vector<std::string>& dirs, const std::vector<std::string>& excludes,
                                   int level, unsigned long minFileSize, const std::vector<std::string>& masks)
{
    std::set<std::string> excludedSet(excludes.begin(), excludes.end());
    std::vector<std::string> lowerMasks;

    for (const auto& m : masks)
    {
        std::string lm = m;
        ba::to_lower(lm);
        lowerMasks.push_back(lm);
    }

    for (const auto& d : dirs)
    {
        fs::path dir(d);

        if (level > 0)
        {
            fs::recursive_directory_iterator it(dir), end;
            for (; it != end; ++it)
            {
                fs::path p = it->path();

                if (fs::is_directory(p))
                {
                    std::string absPath = p.string();

                    if (excludedSet.count(absPath))
                    {
                        it.disable_recursion_pending();
                        continue;
                    }
                }
                else if (!fs::is_regular_file(p))
                    continue;  // Skip non-regular files
                else
                {
                    uintmax_t file_size = fs::file_size(p);

                    if (file_size < static_cast<uintmax_t>(minFileSize))
                        continue;

                    bool match = lowerMasks.empty();

                    if (!match)
                    {
                        std::string fileName = p.filename().string();
                        ba::to_lower(fileName);

                        match = doesMatchesAnyMask(fileName, lowerMasks);
                    }

                    if (match)
                        m_FilteredFiles.push_back(p);
                }
            }
        }
        else
        {
            // Non-recursive: directory_iterator
            fs::directory_iterator it(dir), end;
            for (; it != end; ++it) {
                fs::path p = it->path();

                if (fs::is_directory(p))
                {
                    std::string absPath = p.string();
                    ba::to_lower(absPath);

                    if (excludedSet.count(absPath))
                        continue;  // Skip excluded dirs in non-recursive mode
                }
                else if (!fs::is_regular_file(p))
                    continue;  // Skip non-regular files
                else
                {
                    // Check file size filter
                    uintmax_t file_size = fs::file_size(p);

                    if (file_size < static_cast<uintmax_t>(minFileSize))
                        continue;

                    bool match = lowerMasks.empty();

                    if (!match)
                    {
                        std::string fileName = p.filename().string();
                        ba::to_lower(fileName);

                        match = doesMatchesAnyMask(fileName, lowerMasks);
                    }

                    if (match)
                        m_FilteredFiles.push_back(p);
                }
            }
        }
    }
}

/*
 * @brief Prints filtered files paths
 */
void CFilesCollector::PrintFilteredFiles()
{
    for (size_t i = 0; i < m_FilteredFiles.size(); ++i)
    {
        std::cout << std::setw(3) << i + 1 << ": " << m_FilteredFiles[i].string() << std::endl;
    }
}

/*
 * @brief Prints duplicated files paths
 */
void CFilesCollector::PrintDuplicates()
{
    auto currIt = m_Duplicates.begin();

    for (auto it = m_Duplicates.begin(); it != m_Duplicates.end(); ++it)
    {
        if (currIt->first != it->first)
        {
            std::cout << "\n";
            currIt = it;
        }

        std::cout << it->second << "\n";
    }

    std::cout << "\n";
}

/*
 * @brief Check if duplicate file is already added to list
 */
bool CFilesCollector::isDuplicateFileAlreadyAdded(const std::pair<std::vector<uint32_t>, const fs::path>& pair)
{
    std::pair<DuplicateFileConstIt,DuplicateFileConstIt> range = m_Duplicates.equal_range(pair.first);

    for (auto it = range.first; it != range.second; ++it)
        if (it->second == pair.second)
            return true;

    return false;
}

/*
 * @brief Iterate through filtered files and compare them between each other
 */
void CFilesCollector::PrepareDuplicates()
{
    for (size_t i = 0; i < m_FilteredFiles.size(); ++i)
    {
        for (size_t j = i; j < m_FilteredFiles.size(); ++j)
        {
            if (i == j)
                continue;

            std::uintmax_t sizeLeft = fs::file_size(m_FilteredFiles[i]);
            std::uintmax_t sizeRight = fs::file_size(m_FilteredFiles[j]);

            if (sizeLeft == sizeRight && areFilesEqual(m_FilteredFiles[i], m_FilteredFiles[j]))
            {
                auto hash = filesHashes[m_FilteredFiles[i]];

                if (!isDuplicateFileAlreadyAdded(std::make_pair(hash, m_FilteredFiles[i])))
                    m_Duplicates.insert({hash, m_FilteredFiles[i]});

                if (!isDuplicateFileAlreadyAdded(std::make_pair(hash, m_FilteredFiles[j])))
                    m_Duplicates.insert({hash, m_FilteredFiles[j]});
            }
        }
    }
}

/*
 * @brief Read two files from disk block by block, calculate its hashes and compares them
 */
bool CFilesCollector::areFilesEqual(const fs::path& left, const fs::path& right)
{
    bool areFilesEqual = false;

    std::vector<uint32_t> leftHashes;
    std::vector<uint32_t> rightHashes;

    auto itLeft  = filesHashes.find(left);
    auto itRight = filesHashes.find(right);

    // check if file was previously read and get its calculated hash list
    // (in order to prevent redundant reading from disk)
    if (itLeft != filesHashes.end())
        leftHashes = itLeft->second;

    if (itRight != filesHashes.end())
        rightHashes = itRight->second;

    auto blockSize = m_ReadFileBlockSize;

    std::vector<char> buf1(blockSize, 0),
                      buf2(blockSize, 0);
    
    std::ifstream fileLeft(left, std::ios::binary);
    std::ifstream fileRight(right, std::ios::binary);

    auto leftOffset  = blockSize * leftHashes.size();
    auto rightOffset = blockSize * rightHashes.size();

    // start reading file from point where we stopped last time, not from begin
    fileLeft.seekg(leftOffset);
    fileRight.seekg(rightOffset);

    int compareOffset = 0;

    while (true) {
        auto leftSize = leftHashes.size();
        auto rightSize= rightHashes.size();

        auto leftReadBytes  = 0;
        auto rightReadBytes = 0;

        if (leftSize <= rightSize)
        {
            leftReadBytes = fileLeft.read(buf1.data(), blockSize).gcount();

            uint32_t leftBlockHash  = 0;
            if (leftReadBytes) {
                leftBlockHash = computeHash(buf1.data(), leftReadBytes, m_HashAlgorythm);
                leftHashes.push_back(leftBlockHash);

                leftOffset += leftReadBytes;
                fileLeft.seekg(leftOffset);

                buf1.clear();
            }
        }

        if (rightSize <= leftSize)
        {
            rightReadBytes = fileRight.read(buf2.data(), blockSize).gcount();

            uint32_t rightBlockHash  = 0;
            if (rightReadBytes) {
                rightBlockHash = computeHash(buf2.data(), rightReadBytes, m_HashAlgorythm);
                rightHashes.push_back(rightBlockHash);

                rightOffset += rightReadBytes;
                fileRight.seekg(rightOffset);

                buf2.clear();
            }
        }

        if (leftHashes.size() != rightHashes.size())
            continue;

        areFilesEqual = std::equal(leftHashes.begin() + compareOffset, leftHashes.end(), rightHashes.begin() + compareOffset, rightHashes.end());

        compareOffset = compareOffset == 0 ? leftHashes.size() : compareOffset + 1;

        if (!areFilesEqual)
            break;

        if (leftReadBytes == 0 && rightReadBytes == 0)
            break;
    }

    filesHashes[left]  = leftHashes;
    filesHashes[right] = rightHashes;

    return areFilesEqual;
}


