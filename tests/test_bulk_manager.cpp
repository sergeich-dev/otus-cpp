#define BOOST_TEST_MODULE test_bulk_manager

#include <boost/test/included/unit_test.hpp>
#include "../src/bulk/bulk_manager.cpp"

BOOST_AUTO_TEST_SUITE(test_bulk_manager)

    BOOST_AUTO_TEST_CASE(testAddCommand) {

        CBulkManager manager;

        auto cmd1 = std::make_shared<CBaseCommand>("cmd1");
        auto cmd2 = std::make_shared<CBaseCommand>("cmd2");
        auto cmd3 = std::make_shared<CBaseCommand>("cmd3");

        BOOST_CHECK(manager.GetCommands().empty());

        manager.AddCommand(cmd1);
        manager.AddCommand(cmd2);
        manager.AddCommand(cmd3);

        BOOST_CHECK(manager.GetCommands().size() == 3);
    }

    BOOST_AUTO_TEST_CASE(testExecuteBulk) {

        CBulkManager manager;
        manager.SetBulkProcessingSize(3);

        BOOST_CHECK(manager.IsTimeToExecuteBulk() == false);

        auto cmd1 = std::make_shared<CBaseCommand>("cmd1");
        auto cmd2 = std::make_shared<CBaseCommand>("cmd2");
        auto cmd3 = std::make_shared<CBaseCommand>("cmd3");

        manager.AddCommand(cmd1);
        manager.AddCommand(cmd2);
        manager.AddCommand(cmd3);

        BOOST_CHECK(manager.IsTimeToExecuteBulk() == true);

        manager.ExecuteBulk();

        BOOST_CHECK(manager.GetCommands().empty());
    }

BOOST_AUTO_TEST_SUITE_END()