#include <boost/test/unit_test.hpp>
#include "tools.h"

BOOST_AUTO_TEST_SUITE(test_filters)

    BOOST_AUTO_TEST_CASE(test_ip_sorting) {
        auto comp = [](const std::vector<std::string> & a, const std::vector<std::string> & b)
        {
            bool isGreater = false;

            for (size_t idx = 0; idx < std::min(a.size(), b.size()); ++idx)
            {
                int valA = std::stoi(a[idx]);
                int valB = std::stoi(b[idx]);

                if (valA == valB)
                    continue;
                else if (valA > valB)
                {
                    isGreater = true;
                    break;
                }
                else
                    break;
            }

            return isGreater;
        };

        std::vector<std::vector<std::string>> ips = {
                {"192","168","1","10"},
                {"192","168","0","1"},
                {"10","0","0","1"},
                {"192","168","0","100"},
                {"10","0","0","2"}
        };

        std::sort(ips.begin(), ips.end(), comp);

        std::vector<std::vector<std::string>> expected = {
                {"192","168","1","10"},
                {"192","168","0","100"},
                {"192","168","0","1"},
                {"10","0","0","2"},
                {"10","0","0","1"}
        };

        for (size_t i = 0; i < ips.size(); ++i) {
            BOOST_CHECK_EQUAL_COLLECTIONS(
                    ips[i].begin(), ips[i].end(),
                    expected[i].begin(), expected[i].end()
            );
        }

        std::vector<std::vector<std::string>> wronglySorted = {
                {"192","168","0","100"},
                {"192","168","1","10"},
                {"192","168","0","1"},
                {"10","0","0","1"},
                {"10","0","0","2"},
        };

    }

    BOOST_AUTO_TEST_CASE(test_ip_filtering) {

        std::vector<std::vector<std::string>> ips = {
                {"192","168","1","10"},
                {"192","168","0","1"},
                {"10","0","0","1"},
                {"192","168","0","100"},
                {"10","0","0","2"}
        };

        auto filtered = filterIpPoolByAny(ips, 777);

        BOOST_CHECK(filtered.empty());

        filtered = filterIpPoolByAny(ips, 192);

        BOOST_CHECK_EQUAL(filtered.size(), 3);

        filtered = filterIpPoolByValues(ips, 0, 1);

        BOOST_CHECK(filtered.empty());

        filtered = filterIpPoolByValues(ips, 10, 0);

        BOOST_CHECK_EQUAL(filtered.size(), 2);

        filtered = filterIpPoolByValues(ips, 192, 168);

        BOOST_CHECK_EQUAL(filtered.size(), 3);

        filtered = filterIpPoolByValues(ips, 10, 168);

        BOOST_CHECK_EQUAL(filtered.size(), 0);

        filtered = filterIpPool(ips);

        BOOST_CHECK_EQUAL(filtered.size(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()