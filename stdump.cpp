#include "ccc/ccc.h"

void print_address(const char* name, u64 address) {
	fprintf(stderr, "%32s @ 0x%08lx\n", name, address);
}

enum OutputMode : u32 {
	OUTPUT_HELP = 0,
	OUTPUT_SYMBOLS = 1,
	OUTPUT_TYPES = 2
};

struct Options {
	OutputMode mode = OUTPUT_HELP;
	fs::path input_file;
	bool verbose = false;
};

Options parse_args(int argc, char** argv);
void print_symbols(Program& program, SymbolTable& symbol_table);
void print_types(Program& program, SymbolTable& symbol_table);
void print_help();

int main(int argc, char** argv) {
	Options options = parse_args(argc, argv);
	if(options.mode == OUTPUT_HELP) {
		print_help();
		exit(1);
	}
	
	Program program;
	program.images.emplace_back(read_program_image(options.input_file));
	parse_elf_file(program, 0);
	
	SymbolTable symbol_table;
	bool has_symbol_table = false;
	for(ProgramSection& section : program.sections) {
		if(section.type == ProgramSectionType::MIPS_DEBUG) {
			if(options.verbose) {
				print_address("mdebug section", section.file_offset);
			}
			symbol_table = parse_symbol_table(program.images[0], section);
			has_symbol_table = true;
		}
	}
	verify(has_symbol_table, "No symbol table.\n");
	if(options.verbose) {
		print_address("procedure descriptor table", symbol_table.procedure_descriptor_table_offset);
		print_address("local symbol table", symbol_table.local_symbol_table_offset);
		print_address("file descriptor table", symbol_table.file_descriptor_table_offset);
	}
	
	if(options.mode & OUTPUT_SYMBOLS) {
		print_symbols(program, symbol_table);
	}
	if(options.mode & OUTPUT_TYPES) {
		print_types(program, symbol_table);
	}
}

Options parse_args(int argc, char** argv) {
	Options options;
	for(int i = 1; i < argc; i++) {
		std::string arg = argv[i];
		if(arg == "--symbols" || arg == "-s") {
			(u32&) options.mode |= OUTPUT_SYMBOLS;
		}
		if(arg == "--types" || arg == "-t") {
			(u32&) options.mode |= OUTPUT_TYPES;
		}
		if(arg == "--verbose" || arg == "-v") {
			options.verbose = true;
		}
	}
	for(int i = 1; i < argc; i++) {
		std::string arg = argv[i];
		if(arg == "--symbols" || arg == "-s") {
			continue;
		}
		if(arg == "--types" || arg == "-t") {
			continue;
		}
		if(arg == "--verbose" || arg == "-v") {
			continue;
		}
		verify(options.input_file.empty(), "error: Multiple input files specified.\n");
		options.input_file = arg;
	}
	return options;
}

void print_symbols(Program& program, SymbolTable& symbol_table) {
	for(SymFileDescriptor& fd : symbol_table.files) {
		printf("FILE %s:\n", fd.name.c_str());
		for(Symbol& sym : fd.symbols) {
			const char* symbol_type_str = symbol_type(sym.type);
			if(symbol_type_str) {
				printf("\t%s %s\n", symbol_type_str, sym.string.c_str());
			} else {
				printf("\tUNK(%d) %s\n", (u32) sym.type, sym.string.c_str());
			}
		}
	}
}

void print_types(Program& program, SymbolTable& symbol_table) {
	
}

void print_help() {
	puts("stdump: MIPS/GCC symbol table parser.");
	puts("");
	puts("OPTIONS:");
	puts(" --symbols, -s      Print a list of all the local symbols, grouped");
	puts("                    by file descriptor.");
	puts("");
	puts(" --types, -t        TODO");
	puts("");
	puts(" --verbose, -v      Print out addition information e.g. the offsets of");
	puts("                    various data structures in the input file.");
}
