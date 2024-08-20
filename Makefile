ALL: monkey-string

monkey-string: main.c Makefile
	clang main.c \
		--output monkey-string \
		-O3
