ALL: monkey-string

monkey-string: main.c Makefile
	gcc main.c \
		--output monkey-string \
		-O3
