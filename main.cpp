#include <iostream>
#include <chrono>

#include "lib/include/string_parser/string_parser.h"
#include "async.h"

using namespace std::literals::chrono_literals;

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Invalid arguments count! Stop working.\n";
            return -1;
        }

        auto nBulkSize = std::stoi(argv[1]);

        std::cout << "Start processing commands\n\n";

        {
            auto ctx  = connect(nBulkSize);
            auto ctx2 = connect(nBulkSize);

            std::string testCmd1  = "testCmd1";
            std::string testCmd2  = "testCmd2";
            std::string testCmd3  = "testCmd3";
            std::string testCmd4  = "testCmd4";
            std::string testCmd5  = "testCmd5";
            std::string testCmd6  = "testCmd6";
            std::string testCmd7  = "testCmd7";
            std::string testCmd8  = "testCmd8";
            std::string testCmd9  = "testCmd9";
            std::string testCmd10 = "testCmd10";

            receive(testCmd1.c_str(), testCmd1.size(), ctx);
            receive(testCmd2.c_str(), testCmd2.size(), ctx);
            receive(testCmd3.c_str(), testCmd3.size(), ctx);
            receive(testCmd4.c_str(), testCmd4.size(), ctx);
            receive(testCmd5.c_str(), testCmd5.size(), ctx);

            receive(testCmd6.c_str(), testCmd6.size(), ctx2);
            receive(testCmd7.c_str(), testCmd7.size(), ctx2);
            receive(testCmd8.c_str(), testCmd8.size(), ctx);

            receive(testCmd9.c_str(),  testCmd9.size(),  ctx);
            receive(testCmd10.c_str(), testCmd10.size(), ctx2);

            disconnect(ctx);
            disconnect(ctx2);

            if (!ctx)
                std::cout << "ctx is not valid anymore \n";

            if (!ctx2)
                std::cout << "ctx2 is not valid anymore \n";
        }

        std::cout << "\n";

        // --------------------- Different threads test --------------------------- //

        {
            auto ctx3  = connect(nBulkSize);
            auto ctx4  = connect(nBulkSize);

            std::string testCmd11  = "testCmd11";
            std::string testCmd12  = "testCmd12";
            std::string testCmd13  = "testCmd13";
            std::string testCmd14  = "testCmd14";
            std::string testCmd15  = "testCmd15";
            std::string testCmd16  = "testCmd16";
            std::string testCmd17  = "testCmd17";
            std::string testCmd18  = "testCmd18";
            std::string testCmd19  = "testCmd19";
            std::string testCmd20  = "testCmd20";

            std::thread thread1([&](){

                receive(testCmd11.c_str(), testCmd11.size(), ctx3);
                receive(testCmd12.c_str(), testCmd12.size(), ctx3);
                receive(testCmd13.c_str(), testCmd13.size(), ctx3);
                receive(testCmd14.c_str(), testCmd14.size(), ctx3);
                receive(testCmd15.c_str(), testCmd15.size(), ctx3);

                receive(testCmd18.c_str(), testCmd18.size(), ctx3);

                receive(testCmd19.c_str(), testCmd19.size(),  ctx3);

                disconnect(ctx3);
            });

            std::thread thread2([&](){

                receive(testCmd16.c_str(),  testCmd16.size(), ctx4);
                receive(testCmd17.c_str(),  testCmd17.size(), ctx4);
                receive(testCmd20.c_str(), testCmd20.size(), ctx4);

                disconnect(ctx4);
            });

            thread1.join();
            thread2.join();

            if (!ctx4)
                std::cout << "ctx3 is not valid anymore \n";

            if (!ctx4)
                std::cout << "ctx4 is not valid anymore \n";
        }

        std::cout << "\nComplete\n";
    }
    catch (const std::invalid_argument & e)
    {
        std::cerr << "invalid_argument exception" << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

