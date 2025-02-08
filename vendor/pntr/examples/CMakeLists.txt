# Resources
file(GLOB resources resources/*)
set(examples_resources)
list(APPEND examples_resources ${resources})
file(COPY ${examples_resources} DESTINATION "resources/")

# pntr_examples
add_executable(pntr_examples
    pntr_examples.c
)
target_link_libraries(pntr_examples PUBLIC
    pntr

    # Math: Define PNTR_ENABLE_MATH to use the math library
    #m
)

# pntr_examples_output
add_custom_target(pntr_examples_output
    COMMAND pntr_examples
)
