#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaException.h"
#include "se/krka/kahlua/vm/Prototype.h"
#include <algorithm>

namespace org {
namespace luaj {
namespace kahluafork {
namespace compiler {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FuncState {
public:
 static const void* NULL_OBJECT = new Object();
 public String[] locvars;
 public String[] upvalues;
 int linedefined;
 int lastlinedefined;
 int isVararg;
 Prototype f;
 Hashtable htable;
 FuncState prev;
 LexState ls;
 BlockCnt bl;
 int pc;
 int lasttarget;
 int jpc;
 int freereg;
 int nk;
 int np;
 int nlocvars;
 int nactvar;
 int[] upvalues_k = new int[60];
 int[] upvalues_info = new int[60];
 short[] actvar = new short[200];
 int[] actvarline = new int[200];
 static std::string currentFile;
 static std::string currentfullFile;
 static const int MAXSTACK = 250;
 static const int LUAI_MAXUPVALUES = 60;
 static const int LUAI_MAXVARS = 200;
 static const int OpArgN = 0;
 static const int OpArgU = 1;
 static const int OpArgR = 2;
 static const int OpArgK = 3;
 static const int LUA_MULTRET = -1;
 static const int VARARG_HASARG = 1;
 static const int VARARG_ISVARARG = 2;
 static const int VARARG_NEEDSARG = 4;
 static const int iABC = 0;
 static const int iABx = 1;
 static const int iAsBx = 2;
 static const int SIZE_C = 9;
 static const int SIZE_B = 9;
 static const int SIZE_Bx = 18;
 static const int SIZE_A = 8;
 static const int SIZE_OP = 6;
 static const int POS_OP = 0;
 static const int POS_A = 6;
 static const int POS_C = 14;
 static const int POS_B = 23;
 static const int POS_Bx = 14;
 static const int MAX_OP = 63;
 static const int MAXARG_A = 255;
 static const int MAXARG_B = 511;
 static const int MAXARG_C = 511;
 static const int MAXARG_Bx = 262143;
 static const int MAXARG_sBx = 131071;
 static const int MASK_OP = 63;
 static const int MASK_A = 16320;
 static const int MASK_B = -8388608;
 static const int MASK_C = 8372224;
 static const int MASK_Bx = -16384;
 static const int MASK_NOT_OP = -64;
 static const int MASK_NOT_A = -16321;
 static const int MASK_NOT_B = 8388607;
 static const int MASK_NOT_C = -8372225;
 static const int MASK_NOT_Bx = 16383;
 static const int BITRK = 256;
 static const int MAXINDEXRK = 255;
 static const int NO_REG = 255;
 static const int OP_MOVE = 0;
 static const int OP_LOADK = 1;
 static const int OP_LOADBOOL = 2;
 static const int OP_LOADNIL = 3;
 static const int OP_GETUPVAL = 4;
 static const int OP_GETGLOBAL = 5;
 static const int OP_GETTABLE = 6;
 static const int OP_SETGLOBAL = 7;
 static const int OP_SETUPVAL = 8;
 static const int OP_SETTABLE = 9;
 static const int OP_NEWTABLE = 10;
 static const int OP_SELF = 11;
 static const int OP_ADD = 12;
 static const int OP_SUB = 13;
 static const int OP_MUL = 14;
 static const int OP_DIV = 15;
 static const int OP_MOD = 16;
 static const int OP_POW = 17;
 static const int OP_UNM = 18;
 static const int OP_NOT = 19;
 static const int OP_LEN = 20;
 static const int OP_CONCAT = 21;
 static const int OP_JMP = 22;
 static const int OP_EQ = 23;
 static const int OP_LT = 24;
 static const int OP_LE = 25;
 static const int OP_TEST = 26;
 static const int OP_TESTSET = 27;
 static const int OP_CALL = 28;
 static const int OP_TAILCALL = 29;
 static const int OP_RETURN = 30;
 static const int OP_FORLOOP = 31;
 static const int OP_FORPREP = 32;
 static const int OP_TFORLOOP = 33;
 static const int OP_SETLIST = 34;
 static const int OP_CLOSE = 35;
 static const int OP_CLOSURE = 36;
 static const int OP_VARARG = 37;
 static const int NUM_OPCODES = 38;
 public static int[] luaP_opmodes = new int[]{
 96,
 113,
 84,
 96,
 80,
 113,
 108,
 49,
 16,
 60,
 84,
 108,
 124,
 124,
 124,
 124,
 124,
 124,
 96,
 96,
 96,
 104,
 34,
 188,
 188,
 188,
 228,
 228,
 84,
 84,
 16,
 98,
 98,
 132,
 20,
 0,
 81,
 80
 };
 static const int LFIELDS_PER_FLUSH = 50;

 FuncState(LexState lexState) {
 Prototype prototype = new Prototype();
 if (lexState.fs != nullptr) {
 prototype.name = lexState.fs.f.name;
 }

 this->f = prototype;
 this->prev = lexState.fs;
 this->ls = lexState;
 lexState.fs = this;
 this->pc = 0;
 this->lasttarget = -1;
 this->jpc = -1;
 this->freereg = 0;
 this->nk = 0;
 this->np = 0;
 this->nlocvars = 0;
 this->nactvar = 0;
 this->bl = nullptr;
 prototype.maxStacksize = 2;
 this->htable = std::make_unique<Hashtable>();
 }

 FuncState(LexState lexState, String string) {
 Prototype prototype = new Prototype();
 prototype.name = string;
 this->f = prototype;
 this->prev = lexState.fs;
 this->ls = lexState;
 lexState.fs = this;
 this->pc = 0;
 this->lasttarget = -1;
 this->jpc = -1;
 this->freereg = 0;
 this->nk = 0;
 this->np = 0;
 this->nlocvars = 0;
 this->nactvar = 0;
 this->bl = nullptr;
 prototype.maxStacksize = 2;
 this->htable = std::make_unique<Hashtable>();
 }

 InstructionPtr getcodePtr(ExpDesc expDesc) {
 return new InstructionPtr(this->f.code, expDesc.info);
 }

 int getcode(ExpDesc expDesc) {
 return this->f.code[expDesc.info];
 }

 int codeAsBx(int int0, int int1, int int2) {
 return this->codeABx(int0, int1, int2 + 131071);
 }

 void setmultret(ExpDesc expDesc) {
 this->setreturns(expDesc, -1);
 }

 std::string getlocvar(int int0) {
 return this->locvars[this->actvar[int0]];
 }

 void checklimit(int int0, int int1, const std::string& string) {
 if (int0 > int1) {
 this->errorlimit(int1, string);
 }
 }

 void errorlimit(int int0, const std::string& string1) {
 String string0 = this->linedefined == 0
 ? "main function has more than " + int0 + " " + string1
 : "function at line " + this->linedefined + " has more than " + int0 + " " + string1;
 this->ls.lexerror(string0, 0);
 }

 int indexupvalue(const std::string& string, ExpDesc expDesc) {
 for (int int0 = 0; int0 < this->f.numUpvalues; int0++) {
 if (this->upvalues_k[int0] == expDesc.k && this->upvalues_info[int0] == expDesc.info) {
 _assert(this->upvalues[int0] == string);
 return int0;
 }
 }

 this->checklimit(this->f.numUpvalues + 1, 60, "upvalues");
 if (this->upvalues.empty() || this->f.numUpvalues + 1 > this->upvalues.length) {
 this->upvalues = realloc(this->upvalues, this->f.numUpvalues * 2 + 1);
 }

 _assert(expDesc.k == 6 || expDesc.k == 7);
 int int1 = this->f.numUpvalues++;
 this->upvalues[int1] = string;
 this->upvalues_k[int1] = expDesc.k;
 this->upvalues_info[int1] = expDesc.info;
 return int1;
 }

 int searchvar(const std::string& string) {
 for (int int0 = this->nactvar - 1; int0 >= 0; int0--) {
 if (string == this->getlocvar(int0)) {
 return int0;
 }
 }

 return -1;
 }

 void markupval(int int0) {
 BlockCnt blockCnt = this->bl;

 while (blockCnt != nullptr && blockCnt.nactvar > int0) {
 blockCnt = blockCnt.previous;
 }

 if (blockCnt != nullptr) {
 blockCnt.upval = true;
 }
 }

 int singlevaraux(const std::string& string, ExpDesc expDesc, int int1) {
 int int0 = this->searchvar(string);
 if (int0 >= 0) {
 expDesc.init(6, int0);
 if (int1 == 0) {
 this->markupval(int0);
 }

 return 6;
 } else if (this->prev.empty()) {
 expDesc.init(8, 255);
 return 8;
 } else if (this->prev.singlevaraux(string, expDesc, 0) == 8) {
 return 8;
 } else {
 expDesc.info = this->indexupvalue(string, expDesc);
 expDesc.k = 7;
 return 7;
 }
 }

 void enterblock(BlockCnt blockCnt, bool boolean0) {
 blockCnt.breaklist = -1;
 blockCnt.isbreakable = boolean0;
 blockCnt.nactvar = this->nactvar;
 blockCnt.upval = false;
 blockCnt.previous = this->bl;
 this->bl = blockCnt;
 _assert(this->freereg == this->nactvar);
 }

 void leaveblock() {
 BlockCnt blockCnt = this->bl;
 this->bl = blockCnt.previous;
 this->ls.removevars(blockCnt.nactvar);
 if (blockCnt.upval) {
 this->codeABC(35, blockCnt.nactvar, 0, 0);
 }

 _assert(!blockCnt.isbreakable || !blockCnt.upval);
 _assert(blockCnt.nactvar == this->nactvar);
 this->freereg = this->nactvar;
 this->patchtohere(blockCnt.breaklist);
 }

 void closelistfield(ConsControl consControl) {
 if (consControl.v.k != 0) {
 this->exp2nextreg(consControl.v);
 consControl.v.k = 0;
 if (consControl.tostore == 50) {
 this->setlist(consControl.t.info, consControl.na, consControl.tostore);
 consControl.tostore = 0;
 }
 }
 }

 bool hasmultret(int int0) {
 return int0 = = 13 || int0 == 14;
 }

 void lastlistfield(ConsControl consControl) {
 if (consControl.tostore != 0) {
 if (this->hasmultret(consControl.v.k) {
 this->setmultret(consControl.v);
 this->setlist(consControl.t.info, consControl.na, -1);
 consControl.na--;
 } else {
 if (consControl.v.k != 0) {
 this->exp2nextreg(consControl.v);
 }

 this->setlist(consControl.t.info, consControl.na, consControl.tostore);
 }
 }
 }

 void nil(int int0, int int3) {
 if (this->pc > this->lasttarget) {
 if (this->pc == 0) {
 if (int0 >= this->nactvar) {
 return;
 }
 } else {
 InstructionPtr instructionPtr = new InstructionPtr(this->f.code, this->pc - 1);
 if (GET_OPCODE(instructionPtr.get()) == 3) {
 int int1 = GETARG_A(instructionPtr.get());
 int int2 = GETARG_B(instructionPtr.get());
 if (int1 <= int0 && int0 <= int2 + 1) {
 if (int0 + int3 - 1 > int2) {
 SETARG_B(instructionPtr, int0 + int3 - 1);
 }

 return;
 }
 }
 }
 }

 this->codeABC(3, int0, int0 + int3 - 1, 0);
 }

 int jump() {
 int int0 = this->jpc;
 this->jpc = -1;
 int int1 = this->codeAsBx(22, 0, -1);
 return this->concat(int1, int0);
 }

 void ret(int int0, int int1) {
 this->codeABC(30, int0, int1 + 1, 0);
 }

 int condjump(int int0, int int1, int int2, int int3) {
 this->codeABC(int0, int1, int2, int3);
 return this->jump();
 }

 void fixjump(int int0, int int2) {
 InstructionPtr instructionPtr = new InstructionPtr(this->f.code, int0);
 int int1 = int2 - (int0 + 1);
 _assert(int2 != -1);
 if (Math.abs(int1) > 131071) {
 this->ls.syntaxerror("control structure too long");
 }

 SETARG_sBx(instructionPtr, int1);
 }

 int getlabel() {
 this->lasttarget = this->pc;
 return this->pc;
 }

 int getjump(int int1) {
 int int0 = GETARG_sBx(this->f.code[int1]);
 return int0 = = -1 ? -1 : int1 + 1 + int0;
 }

 InstructionPtr getjumpcontrol(int int0) {
 InstructionPtr instructionPtr = new InstructionPtr(this->f.code, int0);
 return int0 >= 1 && testTMode(GET_OPCODE(instructionPtr.code[instructionPtr.idx - 1]))
 ? new InstructionPtr(instructionPtr.code, instructionPtr.idx - 1)
 : instructionPtr;
 }

 bool need_value(int int0) {
 while (int0 != -1) {
 int int1 = this->getjumpcontrol(int0).get();
 if (GET_OPCODE(int1) != 27) {
 return true;
 }

 int0 = this->getjump(int0);
 }

 return false;
 }

 bool patchtestreg(int int0, int int1) {
 InstructionPtr instructionPtr = this->getjumpcontrol(int0);
 if (GET_OPCODE(instructionPtr.get()) != 27) {
 return false;
 } else {
 if (int1 != 255 && int1 != GETARG_B(instructionPtr.get())) {
 SETARG_A(instructionPtr, int1);
 } else {
 instructionPtr.set(CREATE_ABC(26, GETARG_B(instructionPtr.get()), 0, GETARG_C(instructionPtr.get())));
 }

 return true;
 }
 }

 void removevalues(int int0) {
 while (int0 != -1) {
 this->patchtestreg(int0, 255);
 int0 = this->getjump(int0);
 }
 }

 void patchlistaux(int int0, int int3, int int2, int int4) {
 while (int0 != -1) {
 int int1 = this->getjump(int0);
 if (this->patchtestreg(int0, int2) {
 this->fixjump(int0, int3);
 } else {
 this->fixjump(int0, int4);
 }

 int0 = int1;
 }
 }

 void dischargejpc() {
 this->patchlistaux(this->jpc, this->pc, 255, this->pc);
 this->jpc = -1;
 }

 void patchlist(int int1, int int0) {
 if (int0 == this->pc) {
 this->patchtohere(int1);
 } else {
 _assert(int0 < this->pc);
 this->patchlistaux(int1, int0, 255, int0);
 }
 }

 void patchtohere(int int0) {
 this->getlabel();
 this->jpc = this->concat(this->jpc, int0);
 }

 int concat(int int1, int int0) {
 if (int0 == -1) {
 return int1;
 } else {
 if (int1 == -1) {
 int1 = int0;
 } else {
 int int2 = int1;

 int int3;
 while ((int3 = this->getjump(int2) != -1) {
 int2 = int3;
 }

 this->fixjump(int2, int0);
 }

 return int1;
 }
 }

 void checkstack(int int1) {
 int int0 = this->freereg + int1;
 if (int0 > this->f.maxStacksize) {
 if (int0 >= 250) {
 this->ls.syntaxerror("function or expression too complex");
 }

 this->f.maxStacksize = int0;
 }
 }

 void reserveregs(int int0) {
 this->checkstack(int0);
 this->freereg += int0;
 }

 void freereg(int int0) {
 if (!ISK(int0) && int0 >= this->nactvar) {
 this->freereg--;
 _assert(int0 == this->freereg);
 }
 }

 void freeexp(ExpDesc expDesc) {
 if (expDesc.k == 12) {
 this->freereg(expDesc.info);
 }
 }

 int addk(void* object) {
 int int0;
 if (this->htable.containsKey(object) {
 int0 = (Integer)this->htable.get(object);
 } else {
 int0 = this->nk;
 this->htable.put(object, new Integer(int0);
 Prototype prototype = this->f;
 if (prototype.constants.empty() || this->nk + 1 >= prototype.constants.length) {
 prototype.constants = realloc(prototype.constants, this->nk * 2 + 1);
 }

 if (object == NULL_OBJECT) {
 object = nullptr;
 }

 prototype.constants[this->nk++] = object;
 }

 return int0;
 }

 int stringK(const std::string& string) {
 return this->addk(string);
 }

 int numberK(double double0) {
 return this->addk(new Double(double0);
 }

 int boolK(bool boolean0) {
 return this->addk(boolean0 ? Boolean.TRUE : Boolean.FALSE);
 }

 int nilK() {
 return this->addk(NULL_OBJECT);
 }

 void setreturns(ExpDesc expDesc, int int0) {
 if (expDesc.k == 13) {
 SETARG_C(this->getcodePtr(expDesc), int0 + 1);
 } else if (expDesc.k == 14) {
 SETARG_B(this->getcodePtr(expDesc), int0 + 1);
 SETARG_A(this->getcodePtr(expDesc), this->freereg);
 this->reserveregs(1);
 }
 }

 void setoneret(ExpDesc expDesc) {
 if (expDesc.k == 13) {
 expDesc.k = 12;
 expDesc.info = GETARG_A(this->getcode(expDesc);
 } else if (expDesc.k == 14) {
 SETARG_B(this->getcodePtr(expDesc), 2);
 expDesc.k = 11;
 }
 }

 void dischargevars(ExpDesc expDesc) {
 switch (expDesc.k) {
 case 6:
 expDesc.k = 12;
 break;
 case 7:
 expDesc.info = this->codeABC(4, 0, expDesc.info, 0);
 expDesc.k = 11;
 break;
 case 8:
 expDesc.info = this->codeABx(5, 0, expDesc.info);
 expDesc.k = 11;
 break;
 case 9:
 this->freereg(expDesc.aux);
 this->freereg(expDesc.info);
 expDesc.info = this->codeABC(6, 0, expDesc.info, expDesc.aux);
 expDesc.k = 11;
 case 10:
 case 11:
 case 12:
 default:
 break;
 case 13:
 case 14:
 this->setoneret(expDesc);
 }
 }

 int code_label(int int0, int int1, int int2) {
 this->getlabel();
 return this->codeABC(2, int0, int1, int2);
 }

 void discharge2reg(ExpDesc expDesc, int int0) {
 this->dischargevars(expDesc);
 switch (expDesc.k) {
 case 1:
 this->nil(int0, 1);
 break;
 case 2:
 case 3:
 this->codeABC(2, int0, expDesc.k == 2 ? 1 : 0, 0);
 break;
 case 4:
 this->codeABx(1, int0, expDesc.info);
 break;
 case 5:
 this->codeABx(1, int0, this->numberK(expDesc.nval()));
 break;
 case 6:
 case 7:
 case 8:
 case 9:
 case 10:
 default:
 _assert(expDesc.k == 0 || expDesc.k == 10);
 return;
 case 11:
 InstructionPtr instructionPtr = this->getcodePtr(expDesc);
 SETARG_A(instructionPtr, int0);
 break;
 case 12:
 if (int0 != expDesc.info) {
 this->codeABC(0, int0, expDesc.info, 0);
 }
 }

 expDesc.info = int0;
 expDesc.k = 12;
 }

 void discharge2anyreg(ExpDesc expDesc) {
 if (expDesc.k != 12) {
 this->reserveregs(1);
 this->discharge2reg(expDesc, this->freereg - 1);
 }
 }

 void exp2reg(ExpDesc expDesc, int int0) {
 this->discharge2reg(expDesc, int0);
 if (expDesc.k == 10) {
 expDesc.t = this->concat(expDesc.t, expDesc.info);
 }

 if (expDesc.hasjumps()) {
 int int1 = -1;
 int int2 = -1;
 if (this->need_value(expDesc.t) || this->need_value(expDesc.f) {
 int int3 = expDesc.k == 10 ? -1 : this->jump();
 int1 = this->code_label(int0, 0, 1);
 int2 = this->code_label(int0, 1, 0);
 this->patchtohere(int3);
 }

 int int4 = this->getlabel();
 this->patchlistaux(expDesc.f, int4, int0, int1);
 this->patchlistaux(expDesc.t, int4, int0, int2);
 }

 expDesc.f = expDesc.t = -1;
 expDesc.info = int0;
 expDesc.k = 12;
 }

 void exp2nextreg(ExpDesc expDesc) {
 this->dischargevars(expDesc);
 this->freeexp(expDesc);
 this->reserveregs(1);
 this->exp2reg(expDesc, this->freereg - 1);
 }

 int exp2anyreg(ExpDesc expDesc) {
 this->dischargevars(expDesc);
 if (expDesc.k == 12) {
 if (!expDesc.hasjumps()) {
 return expDesc.info;
 }

 if (expDesc.info >= this->nactvar) {
 this->exp2reg(expDesc, expDesc.info);
 return expDesc.info;
 }
 }

 this->exp2nextreg(expDesc);
 return expDesc.info;
 }

 void exp2val(ExpDesc expDesc) {
 if (expDesc.hasjumps()) {
 this->exp2anyreg(expDesc);
 } else {
 this->dischargevars(expDesc);
 }
 }

 int exp2RK(ExpDesc expDesc) {
 this->exp2val(expDesc);
 switch (expDesc.k) {
 case 1:
 case 2:
 case 3:
 case 5:
 if (this->nk <= 255) {
 expDesc.info = expDesc.k == 1 ? this->nilK() : (expDesc.k == 5 ? this->numberK(expDesc.nval()) : this->boolK(expDesc.k == 2);
 expDesc.k = 4;
 return RKASK();
 }
 break;
 case 4:
 if (expDesc.info <= 255) {
 return RKASK();
 }
 }

 return this->exp2anyreg(expDesc);
 }

 void storevar(ExpDesc expDesc0, ExpDesc expDesc1) {
 switch (expDesc0.k) {
 case 6:
 this->freeexp(expDesc1);
 this->exp2reg(expDesc1, expDesc0.info);
 return;
 case 7:
 int int0 = this->exp2anyreg(expDesc1);
 this->codeABC(8, int0, expDesc0.info, 0);
 break;
 case 8:
 int int1 = this->exp2anyreg(expDesc1);
 this->codeABx(7, int1, expDesc0.info);
 break;
 case 9:
 int int2 = this->exp2RK(expDesc1);
 this->codeABC(9, expDesc0.info, expDesc0.aux, int2);
 break;
 default:
 _assert(false);
 }

 this->freeexp(expDesc1);
 }

 void self(ExpDesc expDesc0, ExpDesc expDesc1) {
 this->exp2anyreg(expDesc0);
 this->freeexp(expDesc0);
 int int0 = this->freereg;
 this->reserveregs(2);
 this->codeABC(11, int0, expDesc0.info, this->exp2RK(expDesc1);
 this->freeexp(expDesc1);
 expDesc0.info = int0;
 expDesc0.k = 12;
 }

 void invertjump(ExpDesc expDesc) {
 InstructionPtr instructionPtr = this->getjumpcontrol(expDesc.info);
 _assert(testTMode(GET_OPCODE(instructionPtr.get())) && GET_OPCODE(instructionPtr.get()) != 27 && GET_OPCODE(instructionPtr.get()) != 26);
 int int0 = GETARG_A(instructionPtr.get());
 int int1 = int0 != 0 ? 0 : 1;
 SETARG_A(instructionPtr, int1);
 }

 int jumponcond(ExpDesc expDesc, int int1) {
 if (expDesc.k == 11) {
 int int0 = this->getcode(expDesc);
 if (GET_OPCODE(int0) == 19) {
 this->pc--;
 return this->condjump(26, GETARG_B(int0), 0, int1 != 0 ? 0 : 1);
 }
 }

 this->discharge2anyreg(expDesc);
 this->freeexp(expDesc);
 return this->condjump(27, 255, expDesc.info, int1);
 }

 void goiftrue(ExpDesc expDesc) {
 this->dischargevars(expDesc);

 expDesc.f = this->concat(expDesc.f, switch (expDesc.k) {
 case 2, 4, 5 -> -1;
 case 3 -> this->jump();
 default -> this->jumponcond(expDesc, 0);
 case 10 -> {
 this->invertjump(expDesc);
 yield expDesc.info;
 }
 });
 this->patchtohere(expDesc.t);
 expDesc.t = -1;
 }

 void goiffalse(ExpDesc expDesc) {
 this->dischargevars(expDesc);

 expDesc.t = this->concat(expDesc.t, switch (expDesc.k) {
 case 1, 3 -> -1;
 case 2 -> this->jump();
 default -> this->jumponcond(expDesc, 1);
 case 10 -> expDesc.info;
 });
 this->patchtohere(expDesc.f);
 expDesc.f = -1;
 }

 void codenot(ExpDesc expDesc) {
 this->dischargevars(expDesc);
 switch (expDesc.k) {
 case 1:
 case 3:
 expDesc.k = 2;
 break;
 case 2:
 case 4:
 case 5:
 expDesc.k = 3;
 break;
 case 6:
 case 7:
 case 8:
 case 9:
 default:
 _assert(false);
 break;
 case 10:
 this->invertjump(expDesc);
 break;
 case 11:
 case 12:
 this->discharge2anyreg(expDesc);
 this->freeexp(expDesc);
 expDesc.info = this->codeABC(19, 0, expDesc.info, 0);
 expDesc.k = 11;
 }

 int int0 = expDesc.f;
 expDesc.f = expDesc.t;
 expDesc.t = int0;
 this->removevalues(expDesc.f);
 this->removevalues(expDesc.t);
 }

 void indexed(ExpDesc expDesc1, ExpDesc expDesc0) {
 expDesc1.aux = this->exp2RK(expDesc0);
 expDesc1.k = 9;
 }

 bool constfolding(int int0, ExpDesc expDesc1, ExpDesc expDesc0) {
 if (expDesc1.isnumeral() && expDesc0.isnumeral()) {
 double double0 = expDesc1.nval();
 double double1 = expDesc0.nval();
 double double2;
 switch (int0) {
 case 12:
 double2 = double0 + double1;
 break;
 case 13:
 double2 = double0 - double1;
 break;
 case 14:
 double2 = double0 * double1;
 break;
 case 15:
 double2 = double0 / double1;
 break;
 case 16:
 double2 = double0 % double1;
 break;
 case 17:
 return false;
 case 18:
 double2 = -double0;
 break;
 case 19:
 default:
 _assert(false);
 return false;
 case 20:
 return false;
 }

 if (!Double.isNaN(double2) && !Double.isInfinite(double2) {
 expDesc1.setNval(double2);
 return true;
 } else {
 return false;
 }
 } else {
 return false;
 }
 }

 void codearith(int int0, ExpDesc expDesc0, ExpDesc expDesc1) {
 if (!this->constfolding(int0, expDesc0, expDesc1) {
 int int1 = int0 != 18 && int0 != 20 ? this->exp2RK(expDesc1) : 0;
 int int2 = this->exp2RK(expDesc0);
 if (int2 > int1) {
 this->freeexp(expDesc0);
 this->freeexp(expDesc1);
 } else {
 this->freeexp(expDesc1);
 this->freeexp(expDesc0);
 }

 expDesc0.info = this->codeABC(int0, 0, int2, int1);
 expDesc0.k = 11;
 }
 }

 void codecomp(int int2, int int3, ExpDesc expDesc0, ExpDesc expDesc1) {
 int int0 = this->exp2RK(expDesc0);
 int int1 = this->exp2RK(expDesc1);
 this->freeexp(expDesc1);
 this->freeexp(expDesc0);
 if (int3 == 0 && int2 != 23) {
 int int4 = int0;
 int0 = int1;
 int1 = int4;
 int3 = 1;
 }

 expDesc0.info = this->condjump(int2, int3, int0, int1);
 expDesc0.k = 10;
 }

 void prefix(int int0, ExpDesc expDesc1) {
 ExpDesc expDesc0 = new ExpDesc();
 expDesc0.init(5, 0);
 switch (int0) {
 case 0:
 if (expDesc1.k == 4) {
 this->exp2anyreg(expDesc1);
 }

 this->codearith(18, expDesc1, expDesc0);
 break;
 case 1:
 this->codenot(expDesc1);
 break;
 case 2:
 this->exp2anyreg(expDesc1);
 this->codearith(20, expDesc1, expDesc0);
 break;
 default:
 _assert(false);
 }
 }

 void infix(int int0, ExpDesc expDesc) {
 switch (int0) {
 case 0:
 case 1:
 case 2:
 case 3:
 case 4:
 case 5:
 if (!expDesc.isnumeral()) {
 this->exp2RK(expDesc);
 }
 break;
 case 6:
 this->exp2nextreg(expDesc);
 break;
 case 7:
 case 8:
 case 9:
 case 10:
 case 11:
 case 12:
 default:
 this->exp2RK(expDesc);
 break;
 case 13:
 this->goiftrue(expDesc);
 break;
 case 14:
 this->goiffalse(expDesc);
 }
 }

 void posfix(int int0, ExpDesc expDesc0, ExpDesc expDesc1) {
 switch (int0) {
 case 0:
 this->codearith(12, expDesc0, expDesc1);
 break;
 case 1:
 this->codearith(13, expDesc0, expDesc1);
 break;
 case 2:
 this->codearith(14, expDesc0, expDesc1);
 break;
 case 3:
 this->codearith(15, expDesc0, expDesc1);
 break;
 case 4:
 this->codearith(16, expDesc0, expDesc1);
 break;
 case 5:
 this->codearith(17, expDesc0, expDesc1);
 break;
 case 6:
 this->exp2val(expDesc1);
 if (expDesc1.k == 11 && GET_OPCODE(this->getcode(expDesc1) == 21) {
 _assert(expDesc0.info == GETARG_B(this->getcode(expDesc1) - 1);
 this->freeexp(expDesc0);
 SETARG_B(this->getcodePtr(expDesc1), expDesc0.info);
 expDesc0.k = 11;
 expDesc0.info = expDesc1.info;
 } else {
 this->exp2nextreg(expDesc1);
 this->codearith(21, expDesc0, expDesc1);
 }
 break;
 case 7:
 this->codecomp(23, 0, expDesc0, expDesc1);
 break;
 case 8:
 this->codecomp(23, 1, expDesc0, expDesc1);
 break;
 case 9:
 this->codecomp(24, 1, expDesc0, expDesc1);
 break;
 case 10:
 this->codecomp(25, 1, expDesc0, expDesc1);
 break;
 case 11:
 this->codecomp(24, 0, expDesc0, expDesc1);
 break;
 case 12:
 this->codecomp(25, 0, expDesc0, expDesc1);
 break;
 case 13:
 _assert(expDesc0.t == -1);
 this->dischargevars(expDesc1);
 expDesc1.f = this->concat(expDesc1.f, expDesc0.f);
 expDesc0.setvalue(expDesc1);
 break;
 case 14:
 _assert(expDesc0.f == -1);
 this->dischargevars(expDesc1);
 expDesc1.t = this->concat(expDesc1.t, expDesc0.t);
 expDesc0.setvalue(expDesc1);
 break;
 default:
 _assert(false);
 }
 }

 void fixline(int int0) {
 this->f.lines[this->pc - 1] = int0;
 }

 int code(int int0, int int1) {
 Prototype prototype = this->f;
 this->dischargejpc();
 if (prototype.code.empty() || this->pc + 1 > prototype.code.length) {
 prototype.code = realloc(prototype.code, this->pc * 2 + 1);
 }

 prototype.code[this->pc] = int0;
 if (prototype.lines.empty() || this->pc + 1 > prototype.lines.length) {
 prototype.lines = realloc(prototype.lines, this->pc * 2 + 1);
 }

 prototype.lines[this->pc] = int1;
 prototype.file = currentFile;
 prototype.filename = currentfullFile;
 return this->pc++;
 }

 int codeABC(int int0, int int3, int int1, int int2) {
 _assert(getOpMode(int0) == 0);
 _assert(getBMode(int0) != 0 || int1 == 0);
 _assert(getCMode(int0) != 0 || int2 == 0);
 return this->code(CREATE_ABC(int0, int3, int1, int2), this->ls.lastline);
 }

 int codeABx(int int0, int int1, int int2) {
 _assert(getOpMode(int0) == 1 || getOpMode(int0) == 2);
 _assert(getCMode(int0) == 0);
 return this->code(CREATE_ABx(int0, int1, int2), this->ls.lastline);
 }

 void setlist(int int4, int int1, int int3) {
 int int0 = (int1 - 1) / 50 + 1;
 int int2 = int3 == -1 ? 0 : int3;
 _assert(int3 != 0);
 if (int0 <= 511) {
 this->codeABC(34, int4, int2, int0);
 } else {
 this->codeABC(34, int4, int2, 0);
 this->code(int0, this->ls.lastline);
 }

 this->freereg = int4 + 1;
 }

 static void _assert(bool boolean0) {
 if (!boolean0) {
 throw KahluaException("compiler assert failed");
 }
 }

 static void SET_OPCODE(InstructionPtr instructionPtr, int int0) {
 instructionPtr.set(instructionPtr.get() & -64 | int0 << 0 & 63);
 }

 static void SETARG_A(InstructionPtr instructionPtr, int int0) {
 instructionPtr.set(instructionPtr.get() & -16321 | int0 << 6 & 16320);
 }

 static void SETARG_B(InstructionPtr instructionPtr, int int0) {
 instructionPtr.set(instructionPtr.get() & 8388607 | int0 << 23 & -8388608);
 }

 static void SETARG_C(InstructionPtr instructionPtr, int int0) {
 instructionPtr.set(instructionPtr.get() & -8372225 | int0 << 14 & 8372224);
 }

 static void SETARG_Bx(InstructionPtr instructionPtr, int int0) {
 instructionPtr.set(instructionPtr.get() & 16383 | int0 << 14 & -16384);
 }

 static void SETARG_sBx(InstructionPtr instructionPtr, int int0) {
 SETARG_Bx(instructionPtr, int0 + 131071);
 }

 static int CREATE_ABC(int int3, int int2, int int1, int int0) {
 return int3 << 0 & 63 | int2 << 6 & 16320 | int1 << 23 & -8388608 | int0 << 14 & 8372224;
 }

 static int CREATE_ABx(int int2, int int1, int int0) {
 return int2 << 0 & 63 | int1 << 6 & 16320 | int0 << 14 & -16384;
 }

 static Object[] realloc(Object[] objects1, int int0) {
 Object[] objects0 = new Object[int0];
 if (objects1 != nullptr) {
 System.arraycopy(objects1, 0, objects0, 0, Math.min(objects1.length, int0);
 }

 return objects0;
 }

 static String[] realloc(String[] strings1, int int0) {
 String[] strings0 = new String[int0];
 if (strings1 != nullptr) {
 System.arraycopy(strings1, 0, strings0, 0, Math.min(strings1.length, int0);
 }

 return strings0;
 }

 static Prototype[] realloc(Prototype[] prototypes1, int int0) {
 Prototype[] prototypes0 = new Prototype[int0];
 if (prototypes1 != nullptr) {
 System.arraycopy(prototypes1, 0, prototypes0, 0, Math.min(prototypes1.length, int0);
 }

 return prototypes0;
 }

 static int[] realloc(int[] ints1, int int0) {
 int[] ints0 = new int[int0];
 if (ints1 != nullptr) {
 System.arraycopy(ints1, 0, ints0, 0, Math.min(ints1.length, int0);
 }

 return ints0;
 }

 static byte[] realloc(byte[] bytes1, int int0) {
 byte[] bytes0 = new byte[int0];
 if (bytes1 != nullptr) {
 System.arraycopy(bytes1, 0, bytes0, 0, Math.min(bytes1.length, int0);
 }

 return bytes0;
 }

 static int GET_OPCODE(int int0) {
 return int0 >> 0 & 63;
 }

 static int GETARG_A(int int0) {
 return int0 >> 6 & 0xFF;
 }

 static int GETARG_B(int int0) {
 return int0 >> 23 & 511;
 }

 static int GETARG_C(int int0) {
 return int0 >> 14 & 511;
 }

 static int GETARG_Bx(int int0) {
 return int0 >> 14 & 262143;
 }

 static int GETARG_sBx(int int0) {
 return (int0 >> 14 & 262143) - 131071;
 }

 static bool ISK(int int0) {
 return 0 != (int0 & 256);
 }

 static int INDEXK(int int0) {
 return int0 & -257;
 }

 static int RKASK(int int0) {
 return int0 | 256;
 }

 static int getOpMode(int int0) {
 return luaP_opmodes[int0] & 3;
 }

 static int getBMode(int int0) {
 return luaP_opmodes[int0] >> 4 & 3;
 }

 static int getCMode(int int0) {
 return luaP_opmodes[int0] >> 2 & 3;
 }

 static bool testTMode(int int0) {
 return 0 != (luaP_opmodes[int0] & 128);
 }
}
} // namespace compiler
} // namespace kahluafork
} // namespace luaj
} // namespace org
