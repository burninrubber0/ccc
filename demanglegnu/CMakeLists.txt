add_library(demanglegnu STATIC
	alloca.c
	cp-demangle.c
	cplus-dem.c
	d-demangle.c
	dyn-string.c
	getopt1.c
	getopt.c
	rust-demangle.c
	safe-ctype.c
	xexit.c
	xmalloc.c
	xmemdup.c
	xstrdup.c
)
include_directories(.)
target_compile_definitions(demanglegnu PRIVATE -DHAVE_STRING_H=1)
if(APPLE)
	target_compile_options(demanglegnu PRIVATE -Wno-implicit-function-declaration)
endif()
