# pntr_test
add_executable(pntr_test pntr_test.c)
target_compile_options(pntr_test PRIVATE -Wall -Wextra -Wconversion -Wsign-conversion)
target_link_libraries(pntr_test PUBLIC
    pntr
    #m
)

# C99 Standard
set_property(TARGET pntr_test PROPERTY C_STANDARD 99)
set_property(TARGET pntr_test PROPERTY C_STANDARD_REQUIRED TRUE)

# Strict Warnings and Errors
if(MSVC)
    target_compile_options(pntr_test PRIVATE /W4 /WX)
else()
    target_compile_options(pntr_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# Resources
file(GLOB resources resources/*)
set(examples_resources)
list(APPEND examples_resources ${resources})
file(COPY ${examples_resources} DESTINATION "resources/")

# Set up the test
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
add_test(NAME pntr_test COMMAND pntr_test)
