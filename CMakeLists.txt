cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(editor VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

configure_file(version.h.in version.h)

add_executable(editor_cli main.cpp)
add_library(editor lib.cpp
            editor/controller/controller.h
            editor/document/document.h
            editor/primitive/primitive.h
            editor/renderer/renderer.h
)

set_target_properties(editor_cli editor PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(editor
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(editor_cli PRIVATE
    editor
)

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(tests test_version.cpp)

    set_target_properties(tests PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(tests PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(tests
        ${Boost_LIBRARIES}
        editor
    )
endif()

if (MSVC)
    target_compile_options(editor_cli PRIVATE
        /W4
    )
    target_compile_options(editor PRIVATE
        /W4
    )
    if(WITH_BOOST_TEST)
        target_compile_options(tests PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(editor_cli PRIVATE
        -Wall -Wextra -pedantic
    )
    target_compile_options(editor PRIVATE
        -Wall -Wextra -pedantic
    )
    if(WITH_BOOST_TEST)
        target_compile_options(tests PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS editor_cli RUNTIME DESTINATION bin)

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
