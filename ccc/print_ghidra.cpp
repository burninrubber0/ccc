#include "print_ghidra.h"

namespace ccc {

struct TypeLookup {
	const std::vector<std::unique_ptr<ast::Node>>& ast_nodes;
	const std::map<std::string, s32>& type_name_to_index;
};

// print_ghidra_prologue
// print_ghidra_types
// print_ghidra_epilogue
static bool create_type(FILE* dest, const ast::Node& node, const std::string& variable_name, const TypeLookup& lookup, s32 depth);
static void create_non_builtin_typedefs(FILE* dest, const TypeLookup& lookup);
static void fill_in_type(FILE* dest, ast::Node& node, const std::string& variable_name, const TypeLookup& lookup, s32 depth);
static void register_types(FILE* dest, const std::vector<std::unique_ptr<ast::Node>>& ast_nodes);
static const char* ast_node_to_java_type(ast::Node& node);
static void indent(FILE* dest, s32 level);

void print_ghidra_prologue(FILE* dest, const fs::path& input_file) {
	fprintf(dest, "// Generated by stdump from %s\n", input_file.filename().string().c_str());
	fprintf(dest, "//@author stdump\n");
	fprintf(dest, "//@category stdump\n");
	fprintf(dest, "\n");
	fprintf(dest, "import ghidra.app.script.GhidraScript;\n");
	fprintf(dest, "import ghidra.app.services.DataTypeManagerService;\n");
	fprintf(dest, "import ghidra.framework.plugintool.PluginTool;\n");
	fprintf(dest, "import ghidra.program.model.mem.*;\n");
	fprintf(dest, "import ghidra.program.model.lang.*;\n");
	fprintf(dest, "import ghidra.program.model.pcode.*;\n");
	fprintf(dest, "import ghidra.program.model.util.*;\n");
	fprintf(dest, "import ghidra.program.model.reloc.*;\n");
	fprintf(dest, "import ghidra.program.model.data.*;\n");
	fprintf(dest, "import ghidra.program.model.block.*;\n");
	fprintf(dest, "import ghidra.program.model.symbol.*;\n");
	fprintf(dest, "import ghidra.program.model.scalar.*;\n");
	fprintf(dest, "import ghidra.program.model.listing.*;\n");
	fprintf(dest, "import ghidra.program.model.address.*;\n");
	fprintf(dest, "\n");
	fprintf(dest, "public class GeneratedSymbolImporter extends GhidraScript {\n");
	fprintf(dest, "\tpublic void run() throws Exception {\n");
	fprintf(dest, "\t\tDataTypeManager program_type_manager = currentProgram.getDataTypeManager();\n");
	fprintf(dest, "\t\tint transaction_id = program_type_manager.startTransaction(\"stdump import script\");\n");
	fprintf(dest, "\t\tPluginTool tool = state.getTool();\n");
	fprintf(dest, "\t\tDataTypeManagerService data_type_manager_service = tool.getService(DataTypeManagerService.class);\n");
	fprintf(dest, "\t\tDataTypeManager builtin_type_manager = data_type_manager_service.getBuiltInDataTypesManager();\n");
	fprintf(dest, "\t\tDataType builtin_void = builtin_type_manager.getDataType(\"void\");\n");
	fprintf(dest, "\t\tDataType builtin_bool = builtin_type_manager.getDataType(\"bool\");\n");
	fprintf(dest, "\t\tDataType builtin_float = builtin_type_manager.getDataType(\"float\");\n");
	fprintf(dest, "\t\tDataType builtin_double = builtin_type_manager.getDataType(\"double\");\n");
	fprintf(dest, "\t\tDataType builtin_char = builtin_type_manager.getDataType(\"char\");\n");
	fprintf(dest, "\t\tDataType builtin_short = builtin_type_manager.getDataType(\"short\");\n");
	fprintf(dest, "\t\tDataType builtin_int = builtin_type_manager.getDataType(\"int\");\n");
	fprintf(dest, "\t\tDataType builtin_longlong = builtin_type_manager.getDataType(\"longlong\");\n");
	fprintf(dest, "\t\tDataType builtin_longlonglong = new ArrayDataType(builtin_char, 16, 1);\n");
	fprintf(dest, "\t\tDataType builtin_uchar = builtin_type_manager.getDataType(\"uchar\");\n");
	fprintf(dest, "\t\tDataType builtin_ushort = builtin_type_manager.getDataType(\"ushort\");\n");
	fprintf(dest, "\t\tDataType builtin_uint = builtin_type_manager.getDataType(\"uint\");\n");
	fprintf(dest, "\t\tDataType builtin_ulonglong = builtin_type_manager.getDataType(\"ulonglong\");\n");
	fprintf(dest, "\t\tDataType builtin_ulonglonglong = new ArrayDataType(builtin_uchar, 16, 1);\n");
}

void print_ghidra_types(FILE* dest, const std::vector<std::unique_ptr<ast::Node>>& ast_nodes, const std::map<std::string, s32>& type_lookup) {
	TypeLookup lookup{ast_nodes, type_lookup};
	
	fprintf(dest, "\t\tprint(\"Creating top level types...\\n\");\n");
	for(s32 i = 0; i < (s32) ast_nodes.size(); i++) {
		std::string variable_name = stringf("type_%d", i);
		create_type(dest, *ast_nodes[i].get(), variable_name, lookup, 0);
	}
	fprintf(dest, "\t\tprint(\"Creating typedefs...\\n\");\n");
	create_non_builtin_typedefs(dest, lookup);
	fprintf(dest, "\t\tprint(\"Filling in types...\\n\");\n");
	for(s32 i = 0; i < (s32) ast_nodes.size(); i++) {
		std::string variable_name = stringf("type_%d", i);
		fill_in_type(dest, *ast_nodes[i].get(), variable_name, lookup, 0);
	}
	fprintf(dest, "\t\tprint(\"Registering types...\\n\");\n");
	register_types(dest, ast_nodes);
}

void print_ghidra_functions(FILE* dest) {
	//fprintf(dest, "\t\tprintf(\"Creating functions...\\n\");\n");
}

void print_ghidra_epilogue(FILE* dest) {
	fprintf(dest, "\t\tprogram_type_manager.endTransaction(transaction_id, true);\n");
	fprintf(dest, "\t}\n");
	fprintf(dest, "}\n");
}

static bool create_type(FILE* dest, const ast::Node& node, const std::string& variable_name, const TypeLookup& lookup, s32 depth) {
	switch(node.descriptor) {
		case ast::ARRAY: {
			if(depth > 0) {
				//const auto& array = node.as<ast::Array>();
				//indent(dest, depth);
				//fprintf(dest, "ArrayDataType %s = new ArrayDataType(%s, );\n", variable_name.c_str());
			}
			break;
		}
		case ast::BITFIELD: {
			break;
		}
		case ast::BUILTIN: {
			const auto& builtin = node.as<ast::BuiltIn>();
			const char* type = "";
			switch(builtin.bclass) {
				case BuiltInClass::VOID: type = "builtin_void"; break;
				case BuiltInClass::UNSIGNED_8: type = "builtin_uchar"; break;
				case BuiltInClass::SIGNED_8: type = "builtin_char"; break;
				case BuiltInClass::UNQUALIFIED_8: type = "builtin_char"; break;
				case BuiltInClass::UNSIGNED_16: type = "builtin_ushort"; break;
				case BuiltInClass::BOOL_8: type = "builtin_bool";
				case BuiltInClass::SIGNED_16: type = "builtin_short"; break;
				case BuiltInClass::UNSIGNED_32: type = "builtin_uint"; break;
				case BuiltInClass::SIGNED_32: type = "builtin_int"; break;
				case BuiltInClass::FLOAT_32: type = "builtin_float"; break;
				case BuiltInClass::UNSIGNED_64: type = "builtin_ulonglong"; break;
				case BuiltInClass::SIGNED_64: type = "builtin_longlong"; break;
				case BuiltInClass::FLOAT_64: type = "builtin_double"; break;
				case BuiltInClass::UNSIGNED_128: type = "builtin_ulonglonglong"; break;
				case BuiltInClass::SIGNED_128: type = "builtin_longlonglong"; break;
				case BuiltInClass::UNQUALIFIED_128: type = "builtin_longlonglong"; break;
				case BuiltInClass::FLOAT_128: type = "builtin_longlonglong"; break;
				case BuiltInClass::UNKNOWN_PROBABLY_ARRAY: type = "CCC_BADBUILTIN"; break;
			}
			indent(dest, depth);
			fprintf(dest, "DataType %s = %s;\n", variable_name.c_str(), type);
			return true;
		}
		case ast::FUNCTION: {
			break;
		}
		case ast::INLINE_ENUM: {
			const auto& inline_enum = node.as<ast::InlineEnum>();
			indent(dest, depth);
			fprintf(dest, "EnumDataType %s = new EnumDataType(null, \"%s\", 4);\n",
					variable_name.c_str(), inline_enum.name.c_str());
			return true;
		}
		case ast::INLINE_STRUCT_OR_UNION: {
			const auto& struct_or_union = node.as<ast::InlineStructOrUnion>();
			indent(dest, depth);
			if(struct_or_union.is_struct) {
				fprintf(dest, "StructureDataType %s = new StructureDataType(null, \"%s\", 0x%x);\n",
					variable_name.c_str(), struct_or_union.name.c_str(), struct_or_union.size_bits / 8);
			} else {
				fprintf(dest, "UnionDataType %s = new UnionDataType(null, \"%s\");\n",
					variable_name.c_str(), struct_or_union.name.c_str());
			}
			return true;
		}
		case ast::POINTER: {
			indent(dest, depth);
			fprintf(dest, "Pointer32DataType %s = new Pointer32DataType();\n", variable_name.c_str());
			return true;
		}
		case ast::REFERENCE: {
			indent(dest, depth);
			fprintf(dest, "Pointer32DataType %s = new Pointer32DataType();\n", variable_name.c_str());
			return true;
		}
		case ast::TYPE_NAME: {
			if(depth > 0) {
				auto type_index = lookup.type_name_to_index.find(node.as<ast::TypeName>().type_name);
				indent(dest, depth);
				if(type_index != lookup.type_name_to_index.end()) {
					fprintf(dest, "DataType %s = type_%d;\n", variable_name.c_str(), type_index->second);
				} else {
					fprintf(dest, "/* ERROR TYPE LOOKUP FAILED*/\n");
				}
				return true;
			}
			break;
		}
	}
	
	if(depth == 0) {
		indent(dest, depth);
		fprintf(dest, "/* %s %s */\n", variable_name.c_str(), ast::NODE_DESCRIPTOR_STRINGS[node.descriptor]);
	}
	
	return false;
}

static void create_non_builtin_typedefs(FILE* dest, const TypeLookup& lookup) {
	for(s32 i = 0; i < (s32) lookup.ast_nodes.size(); i++) {
		ast::Node& node = *lookup.ast_nodes[i];
		switch(node.descriptor) {
			case ast::ARRAY:
			case ast::BITFIELD:
			case ast::BUILTIN:
			case ast::FUNCTION:
			case ast::INLINE_ENUM:
			case ast::INLINE_STRUCT_OR_UNION:
			case ast::POINTER:
			case ast::REFERENCE: {
				break;
			}
			case ast::TYPE_NAME: {
				const ast::TypeName& type_name = node.as<ast::TypeName>();
				if(type_name.storage_class == ast::StorageClass::TYPEDEF) {
					auto type_index = lookup.type_name_to_index.find(type_name.type_name);
					if(type_index != lookup.type_name_to_index.end()) {
						fprintf(dest, "\t\tTypedefDataType type_%d = new TypedefDataType(\"%s\", type_%d);\n",
							i, type_name.name.c_str(), type_index->second);
					}
				}
				break;
			}
		}
	}
}

static void fill_in_type(FILE* dest, ast::Node& node, const std::string& variable_name, const TypeLookup& lookup, s32 depth) {
	indent(dest, depth);
	fprintf(dest, "{%s%s\n", node.name.empty() ? "" : " // ", node.name.c_str());
	switch(node.descriptor) {
		case ast::ARRAY:
		case ast::BITFIELD:
		case ast::BUILTIN:
		case ast::FUNCTION: {
			break;
		}
		case ast::INLINE_ENUM: {
			const auto& inline_enum = node.as<ast::InlineEnum>();
			for(const auto& [value, name] : inline_enum.constants) {
				indent(dest, depth);
				fprintf(dest, "%s.add(\"%s\", %d);\n", variable_name.c_str(), name.c_str(), value);
			}
			break;
		}
		case ast::INLINE_STRUCT_OR_UNION: {
			const ast::InlineStructOrUnion& struct_or_union = node.as<ast::InlineStructOrUnion>();
			for(s32 i = 0; i < (s32) struct_or_union.fields.size(); i++) {
				ast::Node& field = *struct_or_union.fields[i].get();
				std::string field_variable_name = stringf("%s_%d", variable_name.c_str(), i);
				if(create_type(dest, field, field_variable_name, lookup, depth + 1)) {
					fill_in_type(dest, field, field_variable_name, lookup, depth + 1);
					indent(dest, depth + 1);
					if(struct_or_union.is_struct) {
						fprintf(dest, "%s.insertAtOffset(0x%x, %s, 0x%x);\n",
							variable_name.c_str(), field.relative_offset_bytes, field_variable_name.c_str(), field.size_bits / 8);
					} else {
						fprintf(dest, "%s.insert(0, %s, 0x%x, \"\", \"\");\n",
							variable_name.c_str(), field_variable_name.c_str(), field.size_bits / 8);
					}
				}
			}
			break;
		}
		case ast::POINTER:
		case ast::REFERENCE: {
			break;
		}
		case ast::TYPE_NAME: {
			break;
		}
	}
	indent(dest, depth);
	fprintf(dest, "}\n");
}

static void register_types(FILE* dest, const std::vector<std::unique_ptr<ast::Node>>& ast_nodes) {
	for(s32 i = 0; i < (s32) ast_nodes.size(); i++) {
		ast::Node& node = *ast_nodes[i];
		switch(node.descriptor) {
			case ast::ARRAY:
			case ast::BITFIELD:
			case ast::BUILTIN:
			case ast::FUNCTION: {
				break;
			}
			case ast::INLINE_ENUM:
			case ast::INLINE_STRUCT_OR_UNION: {
				indent(dest, 0);
				fprintf(dest, "program_type_manager.addDataType(type_%d, null);\n", i);
				break;
			}
			case ast::POINTER:
			case ast::REFERENCE:
			case ast::TYPE_NAME: {
				indent(dest, 0);
				fprintf(dest, "program_type_manager.addDataType(type_%d, null);\n", i);
				break;
			}
		}
	}
}

static const char* ast_node_to_java_type(ast::Node& node) {
	switch(node.descriptor) {
		case ast::ARRAY: return "ArrayDataType";
		case ast::BITFIELD: return "BitFieldDataType";
		case ast::BUILTIN: return "BuiltInDataType";
		case ast::FUNCTION: return "PointerDataType";
		case ast::INLINE_ENUM: return "EnumDataType";
		case ast::INLINE_STRUCT_OR_UNION: {
			if(node.as<ast::InlineStructOrUnion>().is_struct) {
				return "StructureDataType";
			} else {
				return "UnionDataType";
			}
		}
		case ast::POINTER: return "PointerDataType";
		case ast::REFERENCE: return "PointerDataType";
		case ast::TYPE_NAME: return "TypedefDataType";
	}
	return "CCC_BADASTNODE";
}

static void indent(FILE* dest, s32 depth) {
	for(s32 i = 0; i < depth + 2; i++) {
		fputc('\t', dest);
	}
}

}
