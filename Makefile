clang_flag+=-std=c17
clang_flag+=-Wall
clang_flag+=-I./library/ArgParseX/include/
clang_flag+=-O3

lib_src+=./library/ArgParseX/argpx.c

src+=./main.c

ALL: monkey-string

monkey-string: Makefile ${lib_src} ${src}
	clang ${lib_src} ${src} \
		--output monkey-string \
		${clang_flag}
