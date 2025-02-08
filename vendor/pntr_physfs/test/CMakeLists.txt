
# Add the cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/.cmake)

find_package(pntr)
find_package(PhysFS)

# Resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/)

# pntr_physfs_test
add_executable(pntr_physfs_test pntr_physfs_test.c)
target_link_libraries(pntr_physfs_test PUBLIC
    pntr
    pntr_physfs
    physfs-static
)

# C99
set_property(TARGET pntr_physfs_test PROPERTY C_STANDARD 99)

# Warnings as errors
if(MSVC)
    target_compile_options(pntr_physfs_test PRIVATE /W4 /WX)
else()
    target_compile_options(pntr_physfs_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# Set up the test
add_test(NAME pntr_physfs_test COMMAND pntr_physfs_test)
