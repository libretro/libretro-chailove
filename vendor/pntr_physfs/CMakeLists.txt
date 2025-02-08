cmake_minimum_required(VERSION 3.11)
project(pntr_physfs
    DESCRIPTION "pntr_physfs: PhysicsFS support for pntr"
    HOMEPAGE_URL "https://github.com/robloach/pntr_physfs"
    VERSION 0.1.0
    LANGUAGES C
)

# pntr_physfs
add_library(pntr_physfs INTERFACE)
target_include_directories(pntr_physfs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Options
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(PNTR_PHYSFS_IS_MAIN TRUE)
else()
    set(PNTR_PHYSFS_IS_MAIN FALSE)
endif()
option(PNTR_PHYSFS_BUILD_TESTS "Examples" ${PNTR_PHYSFS_IS_MAIN})

# Testing
if (PNTR_PHYSFS_BUILD_TESTS)
    include(CTest)
    enable_testing()
    if (BUILD_TESTING)
        set(CTEST_CUSTOM_TESTS_IGNORE
            pkg-config--static
        )
        # Always print verbose output when tests fail if run using `make test`.
        list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
        add_subdirectory(test)
    endif()
endif()
