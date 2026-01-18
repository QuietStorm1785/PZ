#include "org/luaj/kahluafork/compiler/LexState.h"

namespace org {
namespace luaj {
namespace kahluafork {
namespace compiler {

std::string LexState::LUA_QS(const std::string &string) {
 // TODO: Implement LUA_QS
 return "";
}

std::string LexState::LUA_QL(void *object) {
 // TODO: Implement LUA_QL
 return "";
}

return LexState::LUA_QS() {
 // TODO: Implement LUA_QS
 return nullptr;
}

bool LexState::isReservedKeyword(const std::string &string) {
 // TODO: Implement isReservedKeyword
 return false;
}

bool LexState::isalnum(int int0) {
 // TODO: Implement isalnum
 return false;
}

bool LexState::isalpha(int int0) {
 // TODO: Implement isalpha
 return false;
}

bool LexState::isdigit(int int0) {
 // TODO: Implement isdigit
 return false;
}

bool LexState::isspace(int int0) {
 // TODO: Implement isspace
 return false;
}

Prototype LexState::compile(int int0, Reader reader, const std::string &string0,
 const std::string &string1) {
 // TODO: Implement compile
 return nullptr;
}

public
LexState::LexState(Reader reader, int int0, const std::string &string) {
 // TODO: Implement LexState
 return nullptr;
}

void LexState::nextChar() {
 // TODO: Implement nextChar
}

bool LexState::currIsNewline() {
 // TODO: Implement currIsNewline
 return false;
}

void LexState::save_and_next() {
 // TODO: Implement save_and_next
}

void LexState::save(int int0) {
 // TODO: Implement save
}

std::string LexState::token2str(int int0) {
 // TODO: Implement token2str
 return "";
}

return LexState::iscntrl() {
 // TODO: Implement iscntrl
 return nullptr;
}

bool LexState::iscntrl(int int0) {
 // TODO: Implement iscntrl
 return false;
}

std::string LexState::txtToken(int int0) {
 // TODO: Implement txtToken
 return "";
}

void LexState::lexerror(const std::string &string2, int int0) {
 // TODO: Implement lexerror
}

std::string LexState::trim(const std::string &string, int int0) {
 // TODO: Implement trim
 return "";
}

void LexState::syntaxerror(const std::string &string) {
 // TODO: Implement syntaxerror
}

std::string LexState::newstring(byte[] bytes, int int0, int int1) {
 // TODO: Implement newstring
 return "";
}

void LexState::inclinenumber() {
 // TODO: Implement inclinenumber
}

void LexState::skipShebang() {
 // TODO: Implement skipShebang
}

bool LexState::check_next(const std::string &string) {
 // TODO: Implement check_next
 return false;
}

void LexState::str2d(const std::string &string, Token token) {
 // TODO: Implement str2d
}

void LexState::read_numeral(Token token) {
 // TODO: Implement read_numeral
}

int LexState::skip_sep() {
 // TODO: Implement skip_sep
 return 0;
}

void LexState::read_long_string(Token token, int int1) {
 // TODO: Implement read_long_string
}

void LexState::read_string(int int1, Token token) {
 // TODO: Implement read_string
}

int LexState::llex(Token token) {
 // TODO: Implement llex
 return 0;
}

void LexState::next() {
 // TODO: Implement next
}

void LexState::lookahead() {
 // TODO: Implement lookahead
}

bool LexState::hasmultret(int int0) {
 // TODO: Implement hasmultret
 return false;
}

void LexState::error_expected(int int0) {
 // TODO: Implement error_expected
}

bool LexState::testnext(int int0) {
 // TODO: Implement testnext
 return false;
}

void LexState::check(int int0) {
 // TODO: Implement check
}

void LexState::checknext(int int0) {
 // TODO: Implement checknext
}

void LexState::check_condition(bool boolean0, const std::string &string) {
 // TODO: Implement check_condition
}

void LexState::check_match(int int0, int int2, int int1) {
 // TODO: Implement check_match
}

std::string LexState::str_checkname() {
 // TODO: Implement str_checkname
 return "";
}

void LexState::codestring(ExpDesc expDesc, const std::string &string) {
 // TODO: Implement codestring
}

void LexState::checkname(ExpDesc expDesc) {
 // TODO: Implement checkname
}

int LexState::registerlocalvar(const std::string &string) {
 // TODO: Implement registerlocalvar
 return 0;
}

void LexState::new_localvarliteral(const std::string &string, int int0) {
 // TODO: Implement new_localvarliteral
}

void LexState::new_localvar(const std::string &string, int int0, int var3) {
 // TODO: Implement new_localvar
}

void LexState::new_localvar(const std::string &string, int int0) {
 // TODO: Implement new_localvar
}

void LexState::adjustlocalvars(int int0) {
 // TODO: Implement adjustlocalvars
}

void LexState::removevars(int int0) {
 // TODO: Implement removevars
}

void LexState::singlevar(ExpDesc expDesc) {
 // TODO: Implement singlevar
}

void LexState::adjust_assign(int int1, int int2, ExpDesc expDesc) {
 // TODO: Implement adjust_assign
}

void LexState::enterlevel() {
 // TODO: Implement enterlevel
}

void LexState::leavelevel() {
 // TODO: Implement leavelevel
}

void LexState::pushclosure(FuncState funcState1, ExpDesc expDesc) {
 // TODO: Implement pushclosure
}

void LexState::close_func() {
 // TODO: Implement close_func
}

void LexState::field(ExpDesc expDesc1) {
 // TODO: Implement field
}

void LexState::yindex(ExpDesc expDesc) {
 // TODO: Implement yindex
}

void LexState::recfield(ConsControl consControl) {
 // TODO: Implement recfield
}

void LexState::listfield(ConsControl consControl) {
 // TODO: Implement listfield
}

void LexState::constructor(ExpDesc expDesc) {
 // TODO: Implement constructor
}

int LexState::luaO_int2fb(int int1) {
 // TODO: Implement luaO_int2fb
 return 0;
}

void LexState::parlist() {
 // TODO: Implement parlist
}

void LexState::body(ExpDesc expDesc, bool boolean0, int int0) {
 // TODO: Implement body
}

int LexState::explist1(ExpDesc expDesc) {
 // TODO: Implement explist1
 return 0;
}

void LexState::funcargs(ExpDesc expDesc1) {
 // TODO: Implement funcargs
}

void LexState::prefixexp(ExpDesc expDesc) {
 // TODO: Implement prefixexp
}

void LexState::primaryexp(ExpDesc expDesc0) {
 // TODO: Implement primaryexp
}

void LexState::simpleexp(ExpDesc expDesc) {
 // TODO: Implement simpleexp
}

int LexState::getunopr(int int0) {
 // TODO: Implement getunopr
 return 0;
}

int LexState::getbinopr(int int0) {
 // TODO: Implement getbinopr
 return 0;
}

int LexState::subexpr(ExpDesc expDesc0, int int2) {
 // TODO: Implement subexpr
 return 0;
}

void LexState::expr(ExpDesc expDesc) {
 // TODO: Implement expr
}

bool LexState::block_follow(int int0) {
 // TODO: Implement block_follow
 return false;
}

void LexState::block() {
 // TODO: Implement block
}

void LexState::check_conflict(LHS_assign lHS_assign, ExpDesc expDesc) {
 // TODO: Implement check_conflict
}

void LexState::assignment(LHS_assign lHS_assign0, int int0) {
 // TODO: Implement assignment
}

int LexState::cond() {
 // TODO: Implement cond
 return 0;
}

void LexState::breakstat() {
 // TODO: Implement breakstat
}

void LexState::whilestat(int int2) {
 // TODO: Implement whilestat
}

void LexState::repeatstat(int int1) {
 // TODO: Implement repeatstat
}

int LexState::exp1() {
 // TODO: Implement exp1
 return 0;
}

void LexState::forbody(int int1, int int4, int int2, bool boolean0) {
 // TODO: Implement forbody
}

void LexState::fornum(const std::string &string, int int1) {
 // TODO: Implement fornum
}

void LexState::forlist(const std::string &string) {
 // TODO: Implement forlist
}

void LexState::forstat(int int0) {
 // TODO: Implement forstat
}

int LexState::test_then_block() {
 // TODO: Implement test_then_block
 return 0;
}

void LexState::ifstat(int int2) {
 // TODO: Implement ifstat
}

void LexState::localfunc() {
 // TODO: Implement localfunc
}

void LexState::localstat(int int1) {
 // TODO: Implement localstat
}

bool LexState::funcname(ExpDesc expDesc) {
 // TODO: Implement funcname
 return false;
}

void LexState::funcstat(int int0) {
 // TODO: Implement funcstat
}

void LexState::exprstat() {
 // TODO: Implement exprstat
}

void LexState::retstat() {
 // TODO: Implement retstat
}

bool LexState::statement() {
 // TODO: Implement statement
 return false;
}

void LexState::chunk() {
 // TODO: Implement chunk
}

} // namespace compiler
} // namespace kahluafork
} // namespace luaj
} // namespace org
