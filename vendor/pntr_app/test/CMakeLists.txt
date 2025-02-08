# CMAKE Modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

# Resources
file(GLOB resources resources/*)
set(examples_resources)
list(APPEND examples_resources ${resources})
file(COPY ${examples_resources} DESTINATION "resources/")

find_package(pntr)

add_executable(pntr_app_test
    pntr_app_test.c
)
target_compile_options(pntr_app_test PRIVATE -Wall -Wextra -Wconversion -Wsign-conversion)
target_link_libraries(pntr_app_test PUBLIC
    pntr
    pntr_app
)
target_compile_definitions(pntr_app_test PUBLIC PNTR_APP_CLI)

# C11 Standard
set_property(TARGET pntr_app_test PROPERTY C_STANDARD 11)
set_property(TARGET pntr_app_test PROPERTY C_STANDARD_REQUIRED TRUE)

# Strict Warnings and Errors
if(MSVC)
    target_compile_options(pntr_app_test PRIVATE /W4 /WX)
else()
    target_compile_options(pntr_app_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
add_test(NAME pntr_app_test COMMAND pntr_app_test)
