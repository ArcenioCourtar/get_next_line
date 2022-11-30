
clean:
	rm -f test

test: clean
	cc -Wall -Wextra -Werror test.c get_next_line.c get_next_line_utils.c -o test && ./test | cat -e

testm: clean
	cc -Wall -Wextra -Werror test.c get_next_line.c get_next_line_utils.c -o test -fsanitize=address \
	&& ./test | cat -e

.PHONY:
	test