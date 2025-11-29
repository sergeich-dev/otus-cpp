cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(matrix VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" OFF)

add_executable(matrix_cli src/main.cpp)

set_target_properties(matrix_cli PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(matrix_cli PRIVATE
        /W4
    )

    if(WITH_BOOST_TEST)
        target_compile_options(tests PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(matrix_cli PRIVATE
        -Wall -Wextra -pedantic
    )

    if(WITH_BOOST_TEST)
        target_compile_options(tests PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS matrix_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(tests tests)
endif()
