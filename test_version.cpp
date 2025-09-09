#define BOOST_TEST_MODULE test_version

#include "lib.h"

#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version) {
	BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_CASE(test_string_equality) {
        std::string s1 = "hello";
        std::string s2 = "hello";
        std::string s3 = "world";

        BOOST_TEST(s1 == s2);
        BOOST_TEST(s1 != s3);
}

BOOST_AUTO_TEST_SUITE_END()
