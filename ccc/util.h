#ifndef _CCC_UTIL_H
#define _CCC_UTIL_H

#include <map>
#include <set>
#include <span>
#include <vector>
#include <cstdio>
#include <memory>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <variant>
#include <assert.h>
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include <optional>
#include <algorithm>
#include <filesystem>
#include <inttypes.h>

namespace ccc {

namespace fs = std::filesystem;

using u8 = unsigned char;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using s8 = signed char;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

#define ANSI_COLOUR_OFF "\033[0m"
#define ANSI_COLOUR_RED "\033[31m"
#define ANSI_COLOUR_MAGENTA "\033[35m"
#define ANSI_COLOUR_GRAY "\033[90m"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
template <typename... Args>
void verify_impl(const char* file, int line, bool condition, const char* format, Args... args) {
	if(!condition) {
		fprintf(stderr, "[%s:%d] " ANSI_COLOUR_RED "error:" ANSI_COLOUR_OFF " ", file, line);
		fprintf(stderr, format, args...);
		fprintf(stderr, "\n");
		exit(1);
	}
}
#define verify(condition, ...) \
	ccc::verify_impl(__FILE__, __LINE__, condition, __VA_ARGS__)
template <typename... Args>
[[noreturn]] void verify_not_reached_impl(const char* file, int line, const char* format, Args... args) {
	fprintf(stderr, "[%s:%d] " ANSI_COLOUR_RED "error:" ANSI_COLOUR_OFF " ", file, line);
	fprintf(stderr, format, args...);
	fprintf(stderr, "\n");
	exit(1);
}
#define verify_not_reached(...) \
	ccc::verify_not_reached_impl(__FILE__, __LINE__, __VA_ARGS__)
template <typename... Args>
void warn_impl(const char* file, int line, const char* format, Args... args) {
	fprintf(stderr, "[%s:%d] " ANSI_COLOUR_MAGENTA "warning:" ANSI_COLOUR_OFF " ", file, line);
	fprintf(stderr, format, args...);
	fprintf(stderr, "\n");
}
#define warn(...) \
	ccc::warn_impl(__FILE__, __LINE__, __VA_ARGS__)
#pragma GCC diagnostic pop

#ifdef _MSC_VER
	#define packed_struct(name, ...) \
		__pragma(pack(push, 1)) struct name { __VA_ARGS__ } __pragma(pack(pop));
#else
	#define packed_struct(name, ...) \
		struct __attribute__((__packed__)) name { __VA_ARGS__ };
#endif

template <typename T>
const T& get_packed(const std::vector<u8>& bytes, u64 offset, const char* subject) {
	verify(bytes.size() >= offset + sizeof(T), "Failed to read %s.", subject);
	return *(const T*) &bytes[offset];
}

std::vector<u8> read_binary_file(const fs::path& path);
std::optional<std::string> read_text_file(const fs::path& path);
s64 file_size(FILE* file);
std::string get_string(const std::vector<u8>& bytes, u64 offset);
const char* get_c_string(const std::vector<u8>& bytes, u64 offset);

struct Range {
	s32 low;
	s32 high;
};

#define BEGIN_END(x) (x).begin(), (x).end()
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

std::string string_format(const char* format, va_list args);
std::string stringf(const char* format, ...);

// These functions are to be used only for source file paths present in the
// symbol table, since we want them to be handled consistently across different
// platforms, which with std::filesystem::path doesn't seem to be possible.
std::string merge_paths(const std::string& base, const std::string& path);
std::string normalise_path(const char* input, bool use_backslashes_as_path_separators);
bool guess_is_windows_path(const char* path);
std::string extract_file_name(const std::string& path);

// On Windows long is only 4 bytes, so the regular libc standard IO functions
// are crippled, hence we need to use these special versions instead.
#ifdef _MSC_VER
	#define open_file_rb(filename) _wfopen(filename, L"rb")
	#define open_file_w(filename) _wfopen(filename, L"w")
	#define fseek _fseeki64
	#define ftell _ftelli64
#else
	#define open_file_rb(filename) fopen(filename, "rb")
	#define open_file_w(filename) fopen(filename, "w")
#endif

}

#endif
