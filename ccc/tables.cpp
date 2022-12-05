#include "tables.h"

namespace ccc::mips {

const InsnInfo* INSN_TABLES[MAX_INSN_CLASS] = {
	MIPS_OPCODE_TABLE,
	MIPS_SPECIAL_TABLE,
	MIPS_REGIMM_TABLE,
	MMI_TABLE,
	MMI0_TABLE,
	MMI1_TABLE,
	MMI2_TABLE,
	MMI3_TABLE,
	COP0_TABLE,
	COP0_BC0_TABLE,
	COP0_C0_TABLE,
	COP1_TABLE,
	COP1_BC1_TABLE,
	COP1_S_TABLE,
	COP1_W_TABLE
};

using IT = InsnType;
using FD = FlowDirection;
using FT = FlowType;
using IF = InsnField;
using RC = RegisterClass;

extern const InsnInfo MIPS_OPCODE_TABLE[MAX_OPCODE] = {
	{"special" , IT::INVALD},
	{"regimm"  , IT::INVALD},
	{"j"       , IT::BRANCH, {{FD::OUT  , SpecialGPR::PC} , {FD::IN, FT::IMMED, IF::TARGET}}},
	{"jal"     , IT::CALL  , {{FD::OUT  , SpecialGPR::PC} , {FD::OUT, GPR::RA}         , {FD::IN, FT::IMMED, IF::TARGET}}},
	{"beq"     , IT::BRANCH, {{FD::OUT  , SpecialGPR::PC} , {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"bne"     , IT::BRANCH, {{FD::OUT  , SpecialGPR::PC} , {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"blez"    , IT::BRANCH, {{FD::OUT  , SpecialGPR::PC} , {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"bgtz"    , IT::BRANCH, {{FD::OUT  , SpecialGPR::PC} , {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"addi"    , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"addiu"   , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"slti"    , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"sltiu"   , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"andi"    , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"ori"     , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"xori"    , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"lui"     , IT::LOADFM, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"cop0"    , IT::INVALD},
	{"cop1"    , IT::INVALD},
	{"cop2"    , IT::INVALD},
	{"resvd_19", IT::INVALD},
	{"beql"    , IT::BRANCH, {{FD::OUT  , SpecialGPR::PC} , {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"bnel"    , IT::BRANCH, {{FD::OUT  , SpecialGPR::PC} , {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"blezl"   , IT::BRANCH, {{FD::OUT  , SpecialGPR::PC} , {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"bgtzl"   , IT::BRANCH, {{FD::OUT  , SpecialGPR::PC} , {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"daddi"   , IT::INVALD, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"daddiu"  , IT::INVALD, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, FT::IMMED, IF::IMMED}}},
	{"ldl"     , IT::LOADFM, {{FD::INOUT, RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"ldr"     , IT::LOADFM, {{FD::INOUT, RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"mmi"     , IT::INVALD},
	{"resvd_29", IT::INVALD},
	{"lq"      , IT::LOADFM, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"sq"      , IT::STOREM, {{FD::IN   , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"lb"      , IT::LOADFM, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"lh"      , IT::LOADFM, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"lwl"     , IT::LOADFM, {{FD::INOUT, RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"lw"      , IT::LOADFM, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"lbu"     , IT::LOADFM, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"lhu"     , IT::LOADFM, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"lwr"     , IT::LOADFM, {{FD::INOUT, RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"lwu"     , IT::LOADFM, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"sb"      , IT::STOREM, {{FD::IN   , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"sh"      , IT::STOREM, {{FD::IN   , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"swl"     , IT::STOREM, {{FD::IN   , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"sw"      , IT::STOREM, {{FD::IN   , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"sdl"     , IT::STOREM, {{FD::IN   , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"sdr"     , IT::STOREM, {{FD::IN   , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"swr"     , IT::STOREM, {{FD::IN   , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"cache"   , IT::SYSTEM},
	{"unsup_48", IT::INVALD},
	{"lwc1"    , IT::LOADFM, {{FD::OUT  , RC::FPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"unsup_50", IT::INVALD},
	{"pref"    , IT::SYSTEM},
	{"unsup_52", IT::INVALD},
	{"unsup_53", IT::INVALD},
	{"lqc2"    , IT::LOADFM, {{FD::OUT  , RC::VU0, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"ld"      , IT::LOADFM, {{FD::OUT  , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"unsup_56", IT::INVALD},
	{"swc1"    , IT::LOADFM, {{FD::IN   , RC::FPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"unsup_58", IT::INVALD},
	{"resvd_59", IT::INVALD},
	{"unsup_60", IT::INVALD},
	{"unsup_61", IT::INVALD},
	{"sqc2"    , IT::LOADFM, {{FD::IN   , RC::VU0, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}},
	{"sd"      , IT::STOREM, {{FD::IN   , RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::IMMED}, {FD::IN, RC::GPR, IF::RS}}}
};

extern const InsnInfo MIPS_SPECIAL_TABLE[MAX_SPECIAL] = {
	{"sll"     , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RD}, {FD::IN, RC::GPR  , IF::RT}   , {FD::IN, FT::IMMED, IF::SA}}},
	{"resvd_1" , IT::INVALD},
	{"srl"     , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RD}, {FD::IN, RC::GPR  , IF::RT}   , {FD::IN, FT::IMMED, IF::SA}}},
	{"sra"     , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RD}, {FD::IN, RC::GPR  , IF::RT}   , {FD::IN, FT::IMMED, IF::SA}}},
	{"sllv"    , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RD}, {FD::IN, RC::GPR  , IF::RT}   , {FD::IN, RC::GPR  , IF::RS}}},
	{"resvd_5" , IT::INVALD},
	{"srlv"    , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RD}, {FD::IN, RC::GPR  , IF::RT}   , {FD::IN, RC::GPR  , IF::RS}}},
	{"srav"    , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RD}, {FD::IN, RC::GPR  , IF::RT}   , {FD::IN, RC::GPR  , IF::RS}}},
	{"jr"      , IT::BRANCH, {{FD::OUT  , SpecialGPR::PC} , {FD::IN, RC::GPR  , IF::RS}}},
	{"jalr"    , IT::CALL  , {{FD::OUT  , SpecialGPR::PC} , {FD::OUT, RC::GPR , IF::RD}   , {FD::IN, RC::GPR  , IF::RS}}},
	{"movz"    , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RD}     , {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, RC::GPR  , IF::RS}}},
	{"movn"    , IT::ARTMTC, {{FD::OUT  , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RD}     , {FD::IN, RC::GPR  , IF::RS}   , {FD::IN, RC::GPR  , IF::RT}}},
	{"syscall" , IT::SYSTEM},
	{"break"   , IT::SYSTEM},
	{"resvd_14", IT::INVALD},
	{"sync"    , IT::SYSTEM},
	{"mfhi"    , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN , SpecialGPR::HI}}},
	{"mthi"    , IT::ARTMTC, {{FD::OUT , SpecialGPR::HI} , {FD::OUT, RC::GPR, IF::RS}}},
	{"mflo"    , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN , SpecialGPR::LO}}},
	{"mtlo"    , IT::ARTMTC, {{FD::OUT , SpecialGPR::LO} , {FD::OUT, RC::GPR, IF::RS}}},
	{"dsllv"   , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, RC::GPR, IF::RS}}},
	{"resvd_21", IT::INVALD},
	{"dsrlv"   , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, RC::GPR, IF::RS}}},
	{"dsrav"   , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, RC::GPR, IF::RS}}},
	{"mult"    , IT::ARTMTC, {{FD::OUT , SpecialGPR::LO} , {FD::OUT, SpecialGPR::HI}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"multu"   , IT::ARTMTC, {{FD::OUT , SpecialGPR::LO} , {FD::OUT, SpecialGPR::HI}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"div"     , IT::ARTMTC, {{FD::OUT , SpecialGPR::LO} , {FD::OUT, SpecialGPR::HI}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"divu"    , IT::ARTMTC, {{FD::OUT , SpecialGPR::LO} , {FD::OUT, SpecialGPR::HI}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"unsup_28", IT::INVALD},
	{"unsup_29", IT::INVALD},
	{"unsup_30", IT::INVALD},
	{"unsup_31", IT::INVALD},
	{"add"     , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"addu"    , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"sub"     , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"subu"    , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"and"     , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"or"      , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"xor"     , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"nor"     , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"mfsa"    , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, SpecialGPR::SA}}},
	{"mtsa"    , IT::ARTMTC, {{FD::OUT , SpecialGPR::SA} , {FD::IN, RC::GPR, IF::RS}}},
	{"slt"     , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"sltu"    , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"dadd"    , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"daddu"   , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"dsub"    , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"dsubu"   , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"tge"     , IT::SYSTEM},
	{"tgeu"    , IT::SYSTEM},
	{"tlt"     , IT::SYSTEM},
	{"tltu"    , IT::SYSTEM},
	{"teq"     , IT::SYSTEM},
	{"resvd_53", IT::INVALD},
	{"tne"     , IT::SYSTEM},
	{"resvd_55", IT::INVALD},
	{"dsll"    , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::RT}}},
	{"resvd_57"},
	{"dsrl"    , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::RT}}},
	{"dsra"    , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::RT}}},
	{"dsll32"  , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::RT}}},
	{"resvd_61"},
	{"dsrl32"  , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::RT}}},
	{"dsra32"  , IT::ARTMTC, {{FD::OUT , RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, FT::IMMED, IF::RT}}}
};

extern const InsnInfo MIPS_REGIMM_TABLE[MAX_REGIMM] = {
	{"bltz"    , IT::BRANCH, {{FD::OUT, SpecialGPR::PC}, {FD::IN, SpecialGPR::PC}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"bgez"    , IT::BRANCH, {{FD::OUT, SpecialGPR::PC}, {FD::IN, SpecialGPR::PC}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"bltzl"   , IT::BRANCH, {{FD::OUT, SpecialGPR::PC}, {FD::IN, SpecialGPR::PC}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"bgezl"   , IT::BRANCH, {{FD::OUT, SpecialGPR::PC}, {FD::IN, SpecialGPR::PC}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"resvd_4" , IT::INVALD},
	{"resvd_5" , IT::INVALD},
	{"resvd_6" , IT::INVALD},
	{"resvd_7" , IT::INVALD},
	{"tgei"    , IT::SYSTEM},
	{"tgeiu"   , IT::SYSTEM},
	{"tlti"    , IT::SYSTEM},
	{"tltiu"   , IT::SYSTEM},
	{"teqi"    , IT::SYSTEM},
	{"resvd_13", IT::INVALD},
	{"tnei"    , IT::SYSTEM},
	{"resvd_15", IT::INVALD},
	{"bltzal"  , IT::CALL  , {{FD::OUT, SpecialGPR::PC}, {FD::IN, SpecialGPR::PC}, {FD::OUT, GPR::RA}, {FD::IN, RC::GPR, IF::RS}}},
	{"bgezal"  , IT::CALL  , {{FD::OUT, SpecialGPR::PC}, {FD::IN, SpecialGPR::PC}, {FD::OUT, GPR::RA}, {FD::IN, RC::GPR, IF::RS}}},
	{"bltzall" , IT::CALL  , {{FD::OUT, SpecialGPR::PC}, {FD::IN, SpecialGPR::PC}, {FD::OUT, GPR::RA}, {FD::IN, GPR::RA}, {FD::IN, RC::GPR, IF::RS}}},
	{"bgezall" , IT::CALL  , {{FD::OUT, SpecialGPR::PC}, {FD::IN, SpecialGPR::PC}, {FD::OUT, GPR::RA}, {FD::IN, GPR::RA}, {FD::IN, RC::GPR, IF::RS}}},
	{"resvd_20", IT::INVALD},
	{"resvd_21", IT::INVALD},
	{"resvd_22", IT::INVALD},
	{"resvd_23", IT::INVALD},
	{"mtsab"   , IT::ARTMTC, {{FD::OUT, SpecialGPR::SA}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"mtsah"   , IT::ARTMTC, {{FD::OUT, SpecialGPR::SA}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"resvd_26", IT::INVALD},
	{"resvd_27", IT::INVALD},
	{"resvd_28", IT::INVALD},
	{"resvd_29", IT::INVALD},
	{"resvd_30", IT::INVALD},
	{"resvd_31", IT::INVALD}
};

extern const InsnInfo MMI_TABLE[MAX_MMI] = {
	{"madd"    , IT::ARTMTC, {{FD::OUT, SpecialGPR::LO}, {FD::OUT, SpecialGPR::HI}, {FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"maddu"   , IT::ARTMTC, {{FD::OUT, SpecialGPR::LO}, {FD::OUT, SpecialGPR::HI}, {FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_2" , IT::INVALD},
	{"resvd_3" , IT::INVALD},
	{"plzcw"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}}},
	{"resvd_5" , IT::INVALD},
	{"resvd_6" , IT::INVALD},
	{"resvd_7" , IT::INVALD},
	{"mmi0"},
	{"mmi2"},
	{"resvd_10", IT::INVALD},
	{"resvd_11", IT::INVALD},
	{"resvd_12", IT::INVALD},
	{"resvd_13", IT::INVALD},
	{"resvd_14", IT::INVALD},
	{"resvd_15", IT::INVALD},
	{"mfhi1"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, SpecialGPR::HI1}}},
	{"mthi1"   , IT::ARTMTC, {{FD::OUT, SpecialGPR::HI1}, {FD::OUT, RC::GPR, IF::RS}}},
	{"mflo1"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, SpecialGPR::LO1}}},
	{"mtlo1"   , IT::ARTMTC, {{FD::OUT, SpecialGPR::LO1}, {FD::OUT, RC::GPR, IF::RS}}},
	{"resvd_20", IT::INVALD},
	{"resvd_21", IT::INVALD},
	{"resvd_22", IT::INVALD},
	{"resvd_23", IT::INVALD},
	{"mult1"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::OUT, SpecialGPR::LO1}, {FD::OUT, SpecialGPR::HI1}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"multu1"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::OUT, SpecialGPR::LO1}, {FD::OUT, SpecialGPR::HI1}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"div1"    , IT::ARTMTC, {{FD::OUT, SpecialGPR::LO1}, {FD::OUT, SpecialGPR::HI1}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"divu1"   , IT::ARTMTC, {{FD::OUT, SpecialGPR::LO1}, {FD::OUT, SpecialGPR::HI1}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_28", IT::INVALD},
	{"resvd_29", IT::INVALD},
	{"resvd_30", IT::INVALD},
	{"resvd_31", IT::INVALD},
	{"madd1"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::OUT, SpecialGPR::HI1}, {FD::OUT, SpecialGPR::LO1}, {FD::IN, SpecialGPR::HI1}, {FD::IN, SpecialGPR::LO1}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"maddu1"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::OUT, SpecialGPR::HI1}, {FD::OUT, SpecialGPR::LO1}, {FD::IN, SpecialGPR::HI1}, {FD::IN, SpecialGPR::LO1}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_34", IT::INVALD},
	{"resvd_35", IT::INVALD},
	{"resvd_36", IT::INVALD},
	{"resvd_37", IT::INVALD},
	{"resvd_38", IT::INVALD},
	{"resvd_39", IT::INVALD},
	{"mmi1"    , IT::INVALD},
	{"mmi3"    , IT::INVALD},
	{"resvd_42", IT::INVALD},
	{"resvd_43", IT::INVALD},
	{"resvd_44", IT::INVALD},
	{"resvd_45", IT::INVALD},
	{"resvd_46", IT::INVALD},
	{"resvd_47", IT::INVALD},
	{"pmfhl"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, SpecialGPR::LO}, {FD::IN, SpecialGPR::HI}}},
	{"pmthl"   , IT::ARTMTC, {{FD::INOUT, SpecialGPR::LO}, {FD::INOUT, SpecialGPR::HI}, {FD::IN, RC::GPR, IF::RS}}},
	{"resvd_50", IT::INVALD},
	{"resvd_51", IT::INVALD},
	{"psllh"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, SpecialGPR::SA}}},
	{"resvd_53", IT::INVALD},
	{"psrlh"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, SpecialGPR::SA}}},
	{"psrah"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, SpecialGPR::SA}}},
	{"resvd_56", IT::INVALD},
	{"resvd_57", IT::INVALD},
	{"resvd_58", IT::INVALD},
	{"resvd_59", IT::INVALD},
	{"psllw"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, SpecialGPR::SA}}},
	{"resvd_61", IT::INVALD},
	{"psrlw"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, SpecialGPR::SA}}},
	{"psraw"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, SpecialGPR::SA}}}
};

extern const InsnInfo MMI0_TABLE[MAX_MMI0] = {
	{"paddw"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"psubw"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pcgtw"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pmaxw"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"paddh"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"psubh"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pcgth"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pmaxh"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"paddb"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"psubb"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pcgtb"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_11", IT::INVALD},
	{"resvd_12", IT::INVALD},
	{"resvd_13", IT::INVALD},
	{"resvd_14", IT::INVALD},
	{"resvd_15", IT::INVALD},
	{"paddsw"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"psubsw"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pextlw"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"ppacw"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"paddsh"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"psubsh"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pextlh"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"ppach"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"paddsb"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"psubsb"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pextlb"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"ppacb"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_28", IT::INVALD},
	{"resvd_29", IT::INVALD},
	{"pext5"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}}},
	{"ppac5"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}}}
};

extern const InsnInfo MMI1_TABLE[MAX_MMI1] = {
	{"resvd_0" , IT::INVALD},
	{"pabsw"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}}},
	{"pceqw"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pminw"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"padsbh"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pabsh"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}}},
	{"pceqh"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pminh"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_8" , IT::INVALD},
	{"resvd_9" , IT::INVALD},
	{"pceqb"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_11", IT::INVALD},
	{"resvd_12", IT::INVALD},
	{"resvd_13", IT::INVALD},
	{"resvd_14", IT::INVALD},
	{"resvd_15", IT::INVALD},
	{"padduw"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"psubuw"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pextuw"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_19", IT::INVALD},
	{"padduh"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"psubuh"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pextuh"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_23", IT::INVALD},
	{"paddub"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"psubub"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pextub"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"qfsrv"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_28", IT::INVALD},
	{"resvd_29", IT::INVALD},
	{"resvd_30", IT::INVALD},
	{"resvd_31", IT::INVALD}
};

extern const InsnInfo MMI2_TABLE[MAX_MMI2] = {
	{"pmaddw"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::OUT, SpecialGPR::HI}, {FD::OUT, SpecialGPR::LO}, {FD::IN, SpecialGPR::HI}, {FD::IN, SpecialGPR::LO}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_1" , IT::INVALD},
	{"psllvw"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, RC::GPR, IF::RS}}},
	{"psrlvw"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, RC::GPR, IF::RS}}},
	{"pmsubw"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_5" , IT::INVALD},
	{"resvd_6" , IT::INVALD},
	{"resvd_7" , IT::INVALD},
	{"pmfhi"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, SpecialGPR::HI}}},
	{"pmflo"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, SpecialGPR::LO}}},
	{"pinth"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_11", IT::INVALD},
	{"pmultw"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::OUT, SpecialGPR::LO}, {FD::OUT, SpecialGPR::HI}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pdivw"   , IT::ARTMTC, {{FD::OUT, SpecialGPR::LO}, {FD::OUT, SpecialGPR::HI}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pcpyld"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_15", IT::INVALD},
	{"pmaddh"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::INOUT, SpecialGPR::HI}, {FD::INOUT, SpecialGPR::LO}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"phmadh"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::INOUT, SpecialGPR::HI}, {FD::INOUT, SpecialGPR::LO}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pand"    , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pxor"    , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pmsubh"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::INOUT, SpecialGPR::HI}, {FD::INOUT, SpecialGPR::LO}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"phmsbh"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::INOUT, SpecialGPR::HI}, {FD::INOUT, SpecialGPR::LO}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_22", IT::INVALD},
	{"resvd_23", IT::INVALD},
	{"resvd_24", IT::INVALD},
	{"resvd_25", IT::INVALD},
	{"pexeh"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}}},
	{"prevh"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}}},
	{"pmulth"  , IT::ARTMTC, {{FD::OUT, SpecialGPR::LO}, {FD::OUT, SpecialGPR::HI}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pdivbw"  , IT::ARTMTC, {{FD::OUT, SpecialGPR::LO}, {FD::OUT, SpecialGPR::HI}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pexew"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}}},
	{"prot3w"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}}},
};

extern const InsnInfo MMI3_TABLE[MAX_MMI3] = {
	{"pmadduw" , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::INOUT, SpecialGPR::HI}, {FD::INOUT, SpecialGPR::LO}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_1" , IT::INVALD},
	{"resvd_2" , IT::INVALD},
	{"psravw"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}, {FD::IN, RC::GPR, IF::RS}}},
	{"resvd_4" , IT::INVALD},
	{"resvd_5" , IT::INVALD},
	{"resvd_6" , IT::INVALD},
	{"resvd_7" , IT::INVALD},
	{"pmthi"   , IT::ARTMTC, {{FD::OUT, SpecialGPR::HI}, {FD::IN, RC::GPR, IF::RS}}},
	{"pmtlo"   , IT::ARTMTC, {{FD::OUT, SpecialGPR::LO}, {FD::IN, RC::GPR, IF::RS}}},
	{"pinteh"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_11", IT::INVALD},
	{"pmultuw" , IT::ARTMTC, {{FD::OUT, SpecialGPR::LO}, {FD::OUT, SpecialGPR::HI}, {FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pdivuw"  , IT::ARTMTC, {{FD::OUT, SpecialGPR::LO}, {FD::OUT, SpecialGPR::HI}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pcpyud"  , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_15", IT::INVALD},
	{"resvd_16", IT::INVALD},
	{"resvd_17", IT::INVALD},
	{"por"     , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"pnor"    , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RS}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_20", IT::INVALD},
	{"resvd_21", IT::INVALD},
	{"resvd_22", IT::INVALD},
	{"resvd_23", IT::INVALD},
	{"resvd_24", IT::INVALD},
	{"resvd_25", IT::INVALD},
	{"pexch"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}}},
	{"pcpyh"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_28", IT::INVALD},
	{"resvd_29", IT::INVALD},
	{"pexcw"   , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RD}, {FD::IN, RC::GPR, IF::RT}}},
	{"resvd_31", IT::INVALD}
};

extern const InsnInfo COP0_TABLE[MAX_COP0] = {
	{"mf0"},
	{"resvd_1" , IT::INVALD},
	{"resvd_2" , IT::INVALD},
	{"resvd_3" , IT::INVALD},
	{"mt0"},
	{"resvd_5" , IT::INVALD},
	{"resvd_6" , IT::INVALD},
	{"resvd_7" , IT::INVALD},
	{"bc0"},
	{"resvd_9" , IT::INVALD},
	{"resvd_10", IT::INVALD},
	{"resvd_11", IT::INVALD},
	{"resvd_12", IT::INVALD},
	{"resvd_13", IT::INVALD},
	{"resvd_14", IT::INVALD},
	{"resvd_15", IT::INVALD},
	{"c0"},
	{"resvd_17", IT::INVALD},
	{"resvd_18", IT::INVALD},
	{"resvd_19", IT::INVALD},
	{"resvd_20", IT::INVALD},
	{"resvd_21", IT::INVALD},
	{"resvd_22", IT::INVALD},
	{"resvd_23", IT::INVALD},
	{"resvd_24", IT::INVALD},
	{"resvd_25", IT::INVALD},
	{"resvd_26", IT::INVALD},
	{"resvd_27", IT::INVALD},
	{"resvd_28", IT::INVALD},
	{"resvd_29", IT::INVALD},
	{"resvd_30", IT::INVALD},
	{"resvd_31", IT::INVALD}
};

extern const InsnInfo COP0_BC0_TABLE[MAX_BC0] = {
	{"bc0f"},
	{"bc0t"},
	{"bc0fl"},
	{"bc0tl"},
	{"resvd_4" , IT::INVALD},
	{"resvd_5" , IT::INVALD},
	{"resvd_6" , IT::INVALD},
	{"resvd_7" , IT::INVALD},
	{"resvd_8" , IT::INVALD},
	{"resvd_9" , IT::INVALD},
	{"resvd_10", IT::INVALD},
	{"resvd_11", IT::INVALD},
	{"resvd_12", IT::INVALD},
	{"resvd_13", IT::INVALD},
	{"resvd_14", IT::INVALD},
	{"resvd_15", IT::INVALD},
	{"resvd_16", IT::INVALD},
	{"resvd_17", IT::INVALD},
	{"resvd_18", IT::INVALD},
	{"resvd_19", IT::INVALD},
	{"resvd_20", IT::INVALD},
	{"resvd_21", IT::INVALD},
	{"resvd_22", IT::INVALD},
	{"resvd_23", IT::INVALD},
	{"resvd_24", IT::INVALD},
	{"resvd_25", IT::INVALD},
	{"resvd_26", IT::INVALD},
	{"resvd_27", IT::INVALD},
	{"resvd_28", IT::INVALD},
	{"resvd_29", IT::INVALD},
	{"resvd_30", IT::INVALD},
	{"resvd_31", IT::INVALD}
};

extern const InsnInfo COP0_C0_TABLE[MAX_C0] = {
	{"undef_0" , IT::INVALD},
	{"tlbr"},
	{"tlbwi"},
	{"undef_3" , IT::INVALD},
	{"undef_4" , IT::INVALD},
	{"undef_5" , IT::INVALD},
	{"tlbwr"},
	{"undef_7" , IT::INVALD},
	{"tlbp"},
	{"undef_9" , IT::INVALD},
	{"undef_10", IT::INVALD},
	{"undef_11", IT::INVALD},
	{"undef_12", IT::INVALD},
	{"undef_13", IT::INVALD},
	{"undef_14", IT::INVALD},
	{"undef_15", IT::INVALD},
	{"undef_16", IT::INVALD},
	{"undef_17", IT::INVALD},
	{"undef_18", IT::INVALD},
	{"undef_19", IT::INVALD},
	{"undef_20", IT::INVALD},
	{"undef_21", IT::INVALD},
	{"undef_22", IT::INVALD},
	{"undef_23", IT::INVALD},
	{"eret"},
	{"undef_25", IT::INVALD},
	{"undef_26", IT::INVALD},
	{"undef_27", IT::INVALD},
	{"undef_28", IT::INVALD},
	{"undef_29", IT::INVALD},
	{"undef_30", IT::INVALD},
	{"undef_31", IT::INVALD},
	{"undef_32", IT::INVALD},
	{"undef_33", IT::INVALD},
	{"undef_34", IT::INVALD},
	{"undef_35", IT::INVALD},
	{"undef_36", IT::INVALD},
	{"undef_37", IT::INVALD},
	{"undef_38", IT::INVALD},
	{"undef_39", IT::INVALD},
	{"undef_40", IT::INVALD},
	{"undef_41", IT::INVALD},
	{"undef_42", IT::INVALD},
	{"undef_43", IT::INVALD},
	{"undef_44", IT::INVALD},
	{"undef_45", IT::INVALD},
	{"undef_46", IT::INVALD},
	{"undef_47", IT::INVALD},
	{"undef_48", IT::INVALD},
	{"undef_49", IT::INVALD},
	{"undef_50", IT::INVALD},
	{"undef_51", IT::INVALD},
	{"undef_52", IT::INVALD},
	{"undef_53", IT::INVALD},
	{"undef_54", IT::INVALD},
	{"undef_55", IT::INVALD},
	{"ei"},
	{"di"},
	{"undef_58", IT::INVALD},
	{"undef_59", IT::INVALD},
	{"undef_60", IT::INVALD},
	{"undef_61", IT::INVALD},
	{"undef_62", IT::INVALD},
	{"undef_63", IT::INVALD}
};

extern const InsnInfo COP1_TABLE[MAX_COP1] = {
	{"mfc1"    , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RT}, {FD::IN, RC::FPR, IF::RD}}},
	{"resvd_1" , IT::INVALD},
	{"cfc1"    , IT::ARTMTC, {{FD::OUT, RC::GPR, IF::RT}, {FD::IN, RC::SPECIAL_FPU, IF::RD}}},
	{"resvd_3" , IT::INVALD},
	{"mtc1"    , IT::ARTMTC, {{FD::IN, RC::GPR, IF::RD}, {FD::OUT, RC::FPR, IF::RT}}},
	{"resvd_5" , IT::INVALD},
	{"ctc1"    , IT::ARTMTC, {{FD::IN, RC::GPR, IF::RT}, {FD::OUT, RC::SPECIAL_FPU, IF::RD}}},
	{"resvd_7" , IT::INVALD},
	{"bc1"     , IT::BRANCH, {{FD::OUT, SpecialGPR::PC}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"resvd_9" , IT::INVALD},
	{"resvd_10", IT::INVALD},
	{"resvd_11", IT::INVALD},
	{"resvd_12", IT::INVALD},
	{"resvd_13", IT::INVALD},
	{"resvd_14", IT::INVALD},
	{"resvd_15", IT::INVALD},
	{"s"},
	{"resvd_17", IT::INVALD},
	{"resvd_18", IT::INVALD},
	{"resvd_19", IT::INVALD},
	{"w"},
	{"resvd_21", IT::INVALD},
	{"resvd_22", IT::INVALD},
	{"resvd_23", IT::INVALD},
	{"resvd_24", IT::INVALD},
	{"resvd_25", IT::INVALD},
	{"resvd_26", IT::INVALD},
	{"resvd_27", IT::INVALD},
	{"resvd_28", IT::INVALD},
	{"resvd_29", IT::INVALD},
	{"resvd_30", IT::INVALD},
	{"resvd_31", IT::INVALD}
};

extern const InsnInfo COP1_BC1_TABLE[MAX_BC1] = {
	{"bc1f"    , IT::BRANCH, {{FD::OUT, SpecialGPR::PC}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"bc1t"    , IT::BRANCH, {{FD::OUT, SpecialGPR::PC}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"bc1fl"   , IT::BRANCH, {{FD::OUT, SpecialGPR::PC}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"bc1tl"   , IT::BRANCH, {{FD::OUT, SpecialGPR::PC}, {FD::IN, FT::IMMED, IF::IMMED}}},
	{"resvd_4" , IT::INVALD},
	{"resvd_5" , IT::INVALD},
	{"resvd_6" , IT::INVALD},
	{"resvd_7" , IT::INVALD},
	{"resvd_8" , IT::INVALD},
	{"resvd_9" , IT::INVALD},
	{"resvd_10", IT::INVALD},
	{"resvd_11", IT::INVALD},
	{"resvd_12", IT::INVALD},
	{"resvd_13", IT::INVALD},
	{"resvd_14", IT::INVALD},
	{"resvd_15", IT::INVALD},
	{"resvd_16", IT::INVALD},
	{"resvd_17", IT::INVALD},
	{"resvd_18", IT::INVALD},
	{"resvd_19", IT::INVALD},
	{"resvd_20", IT::INVALD},
	{"resvd_21", IT::INVALD},
	{"resvd_22", IT::INVALD},
	{"resvd_23", IT::INVALD},
	{"resvd_24", IT::INVALD},
	{"resvd_25", IT::INVALD},
	{"resvd_26", IT::INVALD},
	{"resvd_27", IT::INVALD},
	{"resvd_28", IT::INVALD},
	{"resvd_29", IT::INVALD},
	{"resvd_30", IT::INVALD},
	{"resvd_31", IT::INVALD}
};

extern const InsnInfo COP1_S_TABLE[MAX_S] = {
	{"add.s"   , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"sub.s"   , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"mul.s"   , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"div.s"   , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"sqrt.s"  , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RT}}},
	{"abs.s"   , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}}},
	{"mov.s"   , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}}},
	{"neg.s"   , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}}},
	{"undef_8" , IT::INVALD},
	{"undef_9" , IT::INVALD},
	{"undef_10", IT::INVALD},
	{"undef_11", IT::INVALD},
	{"undef_12", IT::INVALD},
	{"undef_13", IT::INVALD},
	{"undef_14", IT::INVALD},
	{"undef_15", IT::INVALD},
	{"undef_16", IT::INVALD},
	{"undef_17", IT::INVALD},
	{"undef_18", IT::INVALD},
	{"undef_19", IT::INVALD},
	{"undef_20", IT::INVALD},
	{"undef_21", IT::INVALD},
	{"rsqrt.s" , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"undef_23", IT::INVALD},
	{"adda.s"  , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"suba.s"  , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"mula.s"  , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"undef_27", IT::INVALD},
	{"madd.s"  , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"msub.s"  , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"madda.s" , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"msuba.s" , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"undef_32", IT::INVALD},
	{"undef_33", IT::INVALD},
	{"undef_34", IT::INVALD},
	{"undef_35", IT::INVALD},
	{"cvtw.s"  , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}}},
	{"undef_37", IT::INVALD},
	{"undef_38", IT::INVALD},
	{"undef_39", IT::INVALD},
	{"max.s"   , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"min.s"   , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"undef_42", IT::INVALD},
	{"undef_43", IT::INVALD},
	{"undef_44", IT::INVALD},
	{"undef_45", IT::INVALD},
	{"undef_46", IT::INVALD},
	{"undef_47", IT::INVALD},
	{"c.f.s"   , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"undef_49", IT::INVALD},
	{"c.eq.s"  , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"undef_51", IT::INVALD},
	{"c.lt.s"  , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"undef_53", IT::INVALD},
	{"c.le.s"  , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::RD}, {FD::IN, RC::FPR, IF::RT}}},
	{"undef_55", IT::INVALD},
	{"undef_56", IT::INVALD},
	{"undef_57", IT::INVALD},
	{"undef_58", IT::INVALD},
	{"undef_59", IT::INVALD},
	{"undef_60", IT::INVALD},
	{"undef_61", IT::INVALD},
	{"undef_62", IT::INVALD},
	{"undef_63", IT::INVALD}
};

extern const InsnInfo COP1_W_TABLE[MAX_W] = {
	{"undef_0" , IT::INVALD},
	{"undef_1" , IT::INVALD},
	{"undef_2" , IT::INVALD},
	{"undef_3" , IT::INVALD},
	{"undef_4" , IT::INVALD},
	{"undef_5" , IT::INVALD},
	{"undef_6" , IT::INVALD},
	{"undef_7" , IT::INVALD},
	{"undef_8" , IT::INVALD},
	{"undef_9" , IT::INVALD},
	{"undef_10", IT::INVALD},
	{"undef_11", IT::INVALD},
	{"undef_12", IT::INVALD},
	{"undef_13", IT::INVALD},
	{"undef_14", IT::INVALD},
	{"undef_15", IT::INVALD},
	{"undef_16", IT::INVALD},
	{"undef_17", IT::INVALD},
	{"undef_18", IT::INVALD},
	{"undef_19", IT::INVALD},
	{"undef_20", IT::INVALD},
	{"undef_21", IT::INVALD},
	{"undef_22", IT::INVALD},
	{"undef_23", IT::INVALD},
	{"undef_24", IT::INVALD},
	{"undef_25", IT::INVALD},
	{"undef_26", IT::INVALD},
	{"undef_27", IT::INVALD},
	{"undef_28", IT::INVALD},
	{"undef_29", IT::INVALD},
	{"undef_30", IT::INVALD},
	{"undef_31", IT::INVALD},
	{"cvts"    , IT::ARTMTC, {{FD::OUT, RC::FPR, IF::SA}, {FD::IN, RC::FPR, IF::RD}}},
	{"undef_33", IT::INVALD},
	{"undef_34", IT::INVALD},
	{"undef_35", IT::INVALD},
	{"undef_36", IT::INVALD},
	{"undef_37", IT::INVALD},
	{"undef_38", IT::INVALD},
	{"undef_39", IT::INVALD},
	{"undef_40", IT::INVALD},
	{"undef_41", IT::INVALD},
	{"undef_42", IT::INVALD},
	{"undef_43", IT::INVALD},
	{"undef_44", IT::INVALD},
	{"undef_45", IT::INVALD},
	{"undef_46", IT::INVALD},
	{"undef_47", IT::INVALD},
	{"undef_48", IT::INVALD},
	{"undef_49", IT::INVALD},
	{"undef_50", IT::INVALD},
	{"undef_51", IT::INVALD},
	{"undef_52", IT::INVALD},
	{"undef_53", IT::INVALD},
	{"undef_54", IT::INVALD},
	{"undef_55", IT::INVALD},
	{"undef_56", IT::INVALD},
	{"undef_57", IT::INVALD},
	{"undef_58", IT::INVALD},
	{"undef_59", IT::INVALD},
	{"undef_60", IT::INVALD},
	{"undef_61", IT::INVALD},
	{"undef_62", IT::INVALD},
	{"undef_63", IT::INVALD}
};

}
