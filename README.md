# get_next_line
A copy of my get_next_line code submitted at Codam, plus some test files.

Note that due to the Makefile, francinette will not work until it is removed!

On top of the mandatory files for get_next_line,
get_next_line.c
get_next_line_utils.c
get_next_line.h

I also included some files that let you run quick tests.
test.c is the source code that runs the test, by opening test_text.txt and calling get_next_line() until it returns NULL

The Makefile has two rules;
test, which compiles and runs the test code
testm, which does the same thing with an fsanitize=address flag
