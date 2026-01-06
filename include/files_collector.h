#ifndef _FILES_COLLECTOR_H_
#define _FILES_COLLECTOR_H_

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <set>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include "utils.h"

namespace fs = boost::filesystem;
namespace ba = boost::algorithm;

class CFilesCollector
{
public:
    using DuplicateFileConstIt = std::multimap<std::vector<uint32_t>, fs::path>::const_iterator;

        void CollectFiles                   (const std::vector<std::string> & dirs,
                                             const std::vector<std::string> & excludes,
                                             int                              level,
                                             unsigned long                    minFileSize,
                                             const std::vector<std::string> & masks);

        void PrintFilteredFiles             ();

        void PrepareDuplicates              ();

        void PrintDuplicates                ();

        void SetReadingBlockSize            (int blockSize);

        void SetHashAlgorythm               (const std::string & algorythm);

private:
        bool areFilesEqual                  (const fs::path                 & left,
                                             const fs::path                 & right);

        bool isDuplicateFileAlreadyAdded    (const std::pair<std::vector<uint32_t>, const fs::path>& pair);

private:
    int                                             m_ReadFileBlockSize;//!< Size of block for one reading from disk
    std::string                                     m_HashAlgorythm;    //!< Hash algorythm

    std::vector<fs::path>                           m_FilteredFiles;    //!< File paths list for read and compare
    std::multimap<std::vector<uint32_t>, fs::path>  m_Duplicates;       //!< Duplicates list
    std::map<fs::path, std::vector<uint32_t>>       filesHashes;        //!< Calculated hashes for each file
};

inline void CFilesCollector::SetReadingBlockSize(int blockSize)
{
    m_ReadFileBlockSize = blockSize;
}

inline void CFilesCollector::SetHashAlgorythm(const std::string & algorythm)
{
    if (algorythm != "crc32" && algorythm != "md5")
        throw std::runtime_error("Unsupported hash algorythm");

    m_HashAlgorythm = algorythm;
}

#endif //_FILES_COLLECTOR_H_
