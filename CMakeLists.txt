cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(bulk VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

add_executable(bulk src/main.cpp
                        src/string_parser/string_parser.cpp
                        src/command/command.cpp
                        src/bulk/bulk.cpp
                        src/bulk/bulk_manager.cpp
                        src/output/console_printer.cpp
                        src/output/file_saver.cpp
                        src/output/common.cpp
)

add_library(bulk_lib STATIC src/bulk/bulk.cpp
                            src/bulk/bulk_manager.cpp
                            src/command/command.cpp
)
target_include_directories(bulk_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(bulk PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(proj_tests tests/test_bulk_manager.cpp)

    target_link_libraries(proj_tests
            PRIVATE bulk_lib
    )

    set_target_properties(proj_tests PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(proj_tests PROPERTIES
            COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
            INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

endif()

if (MSVC)
    target_compile_options(bulk PRIVATE
        /W4
    )

    if(WITH_BOOST_TEST)
        target_compile_options(proj_tests PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(bulk PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_BOOST_TEST)
        target_compile_options(proj_tests PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(proj_tests proj_tests)
endif()
