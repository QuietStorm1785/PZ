#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace vm {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Prototype {
public:
public
 int[] code;
public
 Object[] constants;
public
 Prototype[] prototypes;
 int numParams;
 bool isVararg;
 std::string name;
public
 int[] lines;
 int numUpvalues;
 int maxStacksize;
 std::string file;
 std::string filename;
public
 String[] locvars;
public
 int[] locvarlines;

public
 Prototype() {}

public
 Prototype(DataInputStream arg0, bool arg1, const std::string &arg2,
 int arg3) {
 this->name = readLuaString(arg0, arg3, arg1);
 if (this->name.empty()) {
 this->name = arg2;
 }

 arg0.readInt();
 arg0.readInt();
 this->numUpvalues = arg0.read();
 this->numParams = arg0.read();
 int int0 = arg0.read();
 this->isVararg = (int0 & 2) != 0;
 this->maxStacksize = arg0.read();
 int int1 = toInt(arg0.readInt(), arg1);
 this->code = new int[int1];

 for (int int2 = 0; int2 < int1; int2++) {
 int int3 = toInt(arg0.readInt(), arg1);
 this->code[int2] = int3;
 }

 int int4 = toInt(arg0.readInt(), arg1);
 this->constants = new Object[int4];

 for (int int5 = 0; int5 < int4; int5++) {
 void *object = nullptr;
 int int6 = arg0.read();

 this->constants[int5] = switch (int6) {
 case 0->{} case 1->{
 int int7 = arg0.read(); yield int7 = = 0 ? Boolean.FALSE:
 Boolean.TRUE;
 }
 default->throw IOException("unknown constant type: " + int6);
 case 3 -> {
 long long0 = arg0.readLong();
 if (arg1) {
 long0 = rev(long0);
 }

 yield KahluaUtil.toDouble(Double.longBitsToDouble(long0);
 }
 case 4 -> readLuaString(arg0, arg3, arg1);
 };
 }

 int int8 = toInt(arg0.readInt(), arg1);
 this->prototypes = new Prototype[int8];

 for (int int9 = 0; int9 < int8; int9++) {
 this->prototypes[int9] = new Prototype(arg0, arg1, this->name, arg3);
 }

 int int10 = toInt(arg0.readInt(), arg1);
 this->lines = new int[int10];

 for (int int11 = 0; int11 < int10; int11++) {
 int int12 = toInt(arg0.readInt(), arg1);
 this->lines[int11] = int12;
 }

 int10 = toInt(arg0.readInt(), arg1);

 for (int int13 = 0; int13 < int10; int13++) {
 readLuaString(arg0, arg3, arg1);
 arg0.readInt();
 arg0.readInt();
 }

 int10 = toInt(arg0.readInt(), arg1);

 for (int int14 = 0; int14 < int10; int14++) {
 readLuaString(arg0, arg3, arg1);
 }
 }

 std::string toString() {
 return this->name;
 }

 static std::string readLuaString(DataInputStream dataInputStream0, int int0, bool boolean0) {
 long long0 = 0L;
 if (int0 == 4) {
 int int1 = dataInputStream0.readInt();
 long0 = toInt(int1, boolean0);
 } else if (int0 == 8) {
 long0 = toLong(dataInputStream0.readLong(), boolean0);
 } else {
 loadAssert(false, "Bad string size");
 }

 if (long0 == 0L) {
 return nullptr;
 } else {
 long0--;
 loadAssert(long0 < 65536L, "Too long string:" + long0);
 int int2 = (int)long0;
 byte[] bytes = new byte[3 + int2];
 bytes[0] = (byte)(int2 >> 8 & 0xFF);
 bytes[1] = (byte)(int2 & 0xFF);
 dataInputStream0.readFully(bytes, 2, int2 + 1);
 loadAssert(bytes[2 + int2] == 0, "String loading");
 DataInputStream dataInputStream1 = new DataInputStream(new ByteArrayInputStream(bytes);
 std::string string = dataInputStream1.readUTF();
 dataInputStream1.close();
 return string;
 }
 }

 static int rev(int arg0) {
 int int0 = arg0 >>> 24 & 0xFF;
 int int1 = arg0 >>> 16 & 0xFF;
 int int2 = arg0 >>> 8 & 0xFF;
 int int3 = arg0 & 0xFF;
 return int3 << 24 | int2 << 16 | int1 << 8 | int0;
 }

 static long rev(long arg0) {
 long long0 = arg0 >>> 56 & 255L;
 long long1 = arg0 >>> 48 & 255L;
 long long2 = arg0 >>> 40 & 255L;
 long long3 = arg0 >>> 32 & 255L;
 long long4 = arg0 >>> 24 & 255L;
 long long5 = arg0 >>> 16 & 255L;
 long long6 = arg0 >>> 8 & 255L;
 long long7 = arg0 & 255L;
 return long7 << 56 | long6 << 48 | long5 << 40 | long4 << 32 | long3 << 24 | long2 << 16 | long1 << 8 | long0;
 }

 static int toInt(int arg0, bool arg1) {
 return arg1 ? rev(arg0) :
 arg0;
 }

 static long toLong(long arg0, bool arg1) {
 return arg1 ? rev(arg0) : arg0;
 }

 static LuaClosure loadByteCode(DataInputStream arg0,
 KahluaTable arg1) {
 int int0 = arg0.read();
 loadAssert(int0 == 27, "Signature 1");
 int0 = arg0.read();
 loadAssert(int0 == 76, "Signature 2");
 int0 = arg0.read();
 loadAssert(int0 == 117, "Signature 3");
 int0 = arg0.read();
 loadAssert(int0 == 97, "Signature 4");
 int0 = arg0.read();
 loadAssert(int0 == 81, "Version");
 int0 = arg0.read();
 loadAssert(int0 == 0, "Format");
 bool boolean0 = arg0.read() == 1;
 int0 = arg0.read();
 loadAssert(int0 == 4, "Size int");
 int int1 = arg0.read();
 loadAssert(int1 == 4 || int1 == 8, "Size t");
 int0 = arg0.read();
 loadAssert(int0 == 4, "Size instr");
 int0 = arg0.read();
 loadAssert(int0 == 8, "Size number");
 int0 = arg0.read();
 loadAssert(int0 == 0, "Integral");
 Prototype prototype =
 new Prototype(arg0, boolean0, nullptr, int1);
 return new LuaClosure(prototype, arg1);
 }

 static void loadAssert(bool boolean0,
 const std::string &string) {
 if (!boolean0) {
 throw IOException("Could not load bytecode:" + string);
 }
 }

 static LuaClosure loadByteCode(InputStream arg0,
 KahluaTable arg1) {
 if (!(dynamic_cast<DataInputStream*>(arg0) != nullptr) {
 arg0 = new DataInputStream((InputStream)arg0);
 }

 return loadByteCode();
 }

 void dump(OutputStream arg0) {
 if (!(dynamic_cast<DataOutputStrea*>(arg0) != nullptrm dataOutputStream) {
 dataOutputStream = new DataOutputStream(arg0);
 }

 dataOutputStream.write(27);
 dataOutputStream.write(76);
 dataOutputStream.write(117);
 dataOutputStream.write(97);
 dataOutputStream.write(81);
 dataOutputStream.write(0);
 dataOutputStream.write(0);
 dataOutputStream.write(4);
 dataOutputStream.write(4);
 dataOutputStream.write(4);
 dataOutputStream.write(8);
 dataOutputStream.write(0);
 this->dumpPrototype(dataOutputStream);
 }

 void dumpPrototype(DataOutputStream dataOutputStream) {
 dumpString(this->name, dataOutputStream);
 dataOutputStream.writeInt(0);
 dataOutputStream.writeInt(0);
 dataOutputStream.write(this->numUpvalues);
 dataOutputStream.write(this->numParams);
 dataOutputStream.write(this->isVararg ? 2 : 0);
 dataOutputStream.write(this->maxStacksize);
 int int0 = this->code.length;
 dataOutputStream.writeInt(int0);

 for (int int1 = 0; int1 < int0; int1++) {
 dataOutputStream.writeInt(this->code[int1]);
 }

 int int2 = this->constants.length;
 dataOutputStream.writeInt(int2);

 for (int int3 = 0; int3 < int2; int3++) {
 void *object = this->constants[int3];
 if (object.empty()) {
 dataOutputStream.write(0);
 } else if (dynamic_cast<Boolean*>(object) != nullptr) {
 dataOutputStream.write(1);
 dataOutputStream.write((Boolean)object ? 1 : 0);
 } else if (dynamic_cast<Double*>(object) != nullptr) {
 dataOutputStream.write(3);
 double double0 = (Double)object;
 dataOutputStream.writeLong(
 Double.doubleToLongBits(double0);
 } else {
 if (!(dynamic_cast<String*>(object) != nullptr) {
 throw RuntimeException("Bad type in constant pool");
 }

 dataOutputStream.write(4);
 dumpString((String)object, dataOutputStream);
 }
 }

 int int4 = this->prototypes.length;
 dataOutputStream.writeInt(int4);

 for (int int5 = 0; int5 < int4; int5++) {
 this->prototypes[int5].dumpPrototype(dataOutputStream);
 }

 int int6 = this->lines.length;
 dataOutputStream.writeInt(int6);

 for (int int7 = 0; int7 < int6; int7++) {
 dataOutputStream.writeInt(this->lines[int7]);
 }

 dataOutputStream.writeInt(0);
 dataOutputStream.writeInt(0);
 }

 static void dumpString(const std::string &string,
 DataOutputStream dataOutputStream) {
 if (string.empty()) {
 dataOutputStream.writeShort(0);
 } else {
 ByteArrayOutputStream byteArrayOutputStream =
 new ByteArrayOutputStream();
 new DataOutputStream();
 byte[] bytes = byteArrayOutputStream.toByteArray();
 int int0 = bytes.length - 2;
 dataOutputStream.writeInt(int0 + 1);
 dataOutputStream.write(bytes, 2, int0);
 dataOutputStream.write(0);
 }
 }
 }
} // namespace vm
} // namespace vm
} // namespace kahlua
} // namespace krka
