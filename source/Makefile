clang_flag+=-std=c17
clang_flag+=-Wall
clang_flag+=-I../library/ArgParseX/include/

ifeq (${type}, release)
	clang_flag+=-O3
	clang_flag+=-DVERSION="\"2.0\""
else
	clang_flag+=-O0
	clang_flag+=-g
endif

lib_src+=../library/ArgParseX/argpx.c

src+=./main.c

default: monkey-string

monkey-string: Makefile ${lib_src} ${src}
	clang ${lib_src} ${src} \
		--output monkey-string \
		${clang_flag}
