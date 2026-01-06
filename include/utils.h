#ifndef _UTILS_H_
#define _UTILS_H_

#include <boost/regex.hpp>
#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <vector>

inline std::string transformMaskToRegex(const std::string& mask)
{
    std::string regex = "^";

    for (char c : mask) {
        switch (c) {
            case '*': regex += ".*"; break;
            case '?': regex += "."; break;
            case '.': case '^': case '$': case '+': case '(': case ')':
            case '[': case '{': case '\\': case '|': regex += '\\';
                [[fallthrough]];
            default: regex += c; break;
        }
    }

    regex += "$";

    return regex;
}

inline bool doesMatchesAnyMask(const std::string& filename, const std::vector<std::string>& masks)
{
    for (const auto& mask : masks)
    {
        std::string regex_str = transformMaskToRegex(mask);

        boost::regex re(regex_str, boost::regex_constants::icase);

        if (boost::regex_match(filename, re))
            return true;
    }
    return false;
}

inline uint32_t crc32(const char* data, std::streamsize size)
{
    boost::crc_32_type crc;
    crc.process_bytes(data, size);
    return crc.checksum();
}

inline uint32_t computeHash(const char* data, std::streamsize size, const std::string& algorythm) {
    if (algorythm == "crc32")
    {
        boost::crc_32_type crc;
        crc.process_bytes(data, size);
        return crc.checksum();
    }
    else if (algorythm == "md5")
    {
        boost::uuids::detail::md5 hash;
        boost::uuids::detail::md5::digest_type digest;

        hash.process_bytes(data, size);
        hash.get_digest(digest);

        uint32_t result = 0;
        std::memcpy(&result, &digest[0], sizeof(uint32_t));
        return result;
    }

    return 0;
}

inline void printHashes(const std::vector<uint32_t> & data)
{
    std::cout << "Hashes: ";
    for (uint32_t n : data) {
        std::cout << std::hex;
        std::cout << std::setw(8);
        std::cout << "[" << n << "]";
    }

    std::cout << std::dec << std::endl;
}

#endif //_UTILS_H_
