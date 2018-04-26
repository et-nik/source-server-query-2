all:
	[ ! -e ssq ] || rm ssq
	cc -Wall -Wextra -o ssq ssq.c
