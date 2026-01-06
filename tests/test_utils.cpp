#define BOOST_TEST_MODULE test_utils

#include <boost/test/included/unit_test.hpp>
#include "../include/utils.h"

BOOST_AUTO_TEST_SUITE(test_utils)

    BOOST_AUTO_TEST_CASE(testTransformMaskToRegex) {
        BOOST_CHECK_EQUAL(transformMaskToRegex("*.txt"), "^.*\\.txt$");
        BOOST_CHECK_EQUAL(transformMaskToRegex("test?.log"), "^test.\\.log$");

        std::cout << "transformMaskToRegex(\"test?.log\"): " << transformMaskToRegex("test?.log") << "\n";

        BOOST_CHECK_EQUAL(transformMaskToRegex("file.txt"), "^file\\.txt$");
        BOOST_CHECK_EQUAL(transformMaskToRegex("^special$"), "^\\^special\\$$");
        BOOST_CHECK_EQUAL(transformMaskToRegex("group(name)"), "^group\\(name\\)$");
        BOOST_CHECK_EQUAL(transformMaskToRegex("path\\file"), "^path\\\\file$");

        BOOST_CHECK_EQUAL(transformMaskToRegex(""), "^$");
        BOOST_CHECK_EQUAL(transformMaskToRegex("abc"), "^abc$");
        BOOST_CHECK_EQUAL(transformMaskToRegex("a*b?c"), "^a.*b.c$");
    }

    BOOST_AUTO_TEST_CASE(testDoesMatchesAnyMask) {
        std::vector<std::string> masks{ "file.txt", "*.txt", "test?.log", "example.log", "", "abc"};

        BOOST_CHECK(doesMatchesAnyMask("file.txt", masks));
        BOOST_CHECK(doesMatchesAnyMask("test1.log", masks));

        BOOST_CHECK(!doesMatchesAnyMask("test12.log", masks));
        BOOST_CHECK(!doesMatchesAnyMask("file1txt", masks));

        BOOST_CHECK(doesMatchesAnyMask("", masks));
        BOOST_CHECK(doesMatchesAnyMask("abc", masks));
    }

BOOST_AUTO_TEST_SUITE_END()