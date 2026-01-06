cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(bayan VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

find_package(Boost COMPONENTS program_options
                              filesystem REQUIRED)

add_executable(bayan src/main.cpp
                     src/args_parser.cpp
                     src/files_collector.cpp
)

target_link_libraries(bayan Boost::program_options Boost::filesystem)

add_library(bayan_lib STATIC src/main.cpp
)
target_include_directories(bayan_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(bayan PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(proj_tests tests/test_utils.cpp)

    target_link_libraries(proj_tests
            PRIVATE bayan_lib
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
    target_compile_options(bayan PRIVATE
        /W4
    )

    if(WITH_BOOST_TEST)
        target_compile_options(proj_tests PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(bayan PRIVATE
        -Wall -Wextra -pedantic ##-Werror
    )
    if(WITH_BOOST_TEST)
        target_compile_options(proj_tests PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS bayan RUNTIME DESTINATION bin)

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
