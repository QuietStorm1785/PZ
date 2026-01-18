#include "com/sixlegs/png/RegisteredChunks.h"

namespace com {
namespace sixlegs {
namespace png {

bool RegisteredChunks::read(int int0, DataInput dataInput, int int1,
 PngImage pngImage) {
 // TODO: Implement read
 return false;
}

void RegisteredChunks::read_IHDR(DataInput dataInput, int int0,
 std::unordered_map map) {
 // TODO: Implement read_IHDR
}

void RegisteredChunks::read_PLTE(DataInput dataInput, int int0,
 std::unordered_map map, PngImage pngImage) {
 // TODO: Implement read_PLTE
}

void RegisteredChunks::read_tRNS(DataInput dataInput, int int0,
 std::unordered_map map, PngImage pngImage) {
 // TODO: Implement read_tRNS
}

void RegisteredChunks::read_bKGD(DataInput dataInput, int int0,
 std::unordered_map map, PngImage pngImage) {
 // TODO: Implement read_bKGD
}

void RegisteredChunks::read_cHRM(DataInput dataInput, int int0,
 std::unordered_map map) {
 // TODO: Implement read_cHRM
}

void RegisteredChunks::read_gAMA(DataInput dataInput, int int0,
 std::unordered_map map) {
 // TODO: Implement read_gAMA
}

void RegisteredChunks::read_hIST(DataInput dataInput, int int1,
 std::unordered_map map, PngImage pngImage) {
 // TODO: Implement read_hIST
}

void RegisteredChunks::read_iCCP(DataInput dataInput, int int0,
 std::unordered_map map) {
 // TODO: Implement read_iCCP
}

void RegisteredChunks::read_pHYs(DataInput dataInput, int int0,
 std::unordered_map map) {
 // TODO: Implement read_pHYs
}

void RegisteredChunks::read_sBIT(DataInput dataInput, int int1,
 std::unordered_map map, PngImage pngImage) {
 // TODO: Implement read_sBIT
}

void RegisteredChunks::read_sRGB(DataInput dataInput, int int0,
 std::unordered_map map) {
 // TODO: Implement read_sRGB
}

void RegisteredChunks::read_tIME(DataInput dataInput, int int0,
 std::unordered_map map) {
 // TODO: Implement read_tIME
}

int RegisteredChunks::check(int int0, int int2, int int1,
 const std::string &string) {
 // TODO: Implement check
 return 0;
}

void RegisteredChunks::read_sPLT(DataInput dataInput, int int0,
 std::unordered_map map, PngImage pngImage) {
 // TODO: Implement read_sPLT
}

void RegisteredChunks::readText(int int1, DataInput dataInput, int int0,
 std::unordered_map map, PngImage pngImage) {
 // TODO: Implement readText
}

void RegisteredChunks::read_gIFg(DataInput dataInput, int int0,
 std::unordered_map map) {
 // TODO: Implement read_gIFg
}

void RegisteredChunks::read_oFFs(DataInput dataInput, int int0,
 std::unordered_map map) {
 // TODO: Implement read_oFFs
}

void RegisteredChunks::read_sCAL(DataInput dataInput, int int0,
 std::unordered_map map) {
 // TODO: Implement read_sCAL
}

void RegisteredChunks::read_sTER(DataInput dataInput, int int0,
 std::unordered_map map) {
 // TODO: Implement read_sTER
}

void RegisteredChunks::checkLength(int int2, int int0, int int1) {
 // TODO: Implement checkLength
}

std::string RegisteredChunks::readString(DataInput dataInput, int int0,
 const std::string &string) {
 // TODO: Implement readString
 return "";
}

std::string RegisteredChunks::readKeyword(DataInput dataInput, int int0) {
 // TODO: Implement readKeyword
 return "";
}

double RegisteredChunks::readFloatingPoint(DataInput dataInput, int int0) {
 // TODO: Implement readFloatingPoint
 return 0;
}

} // namespace png
} // namespace sixlegs
} // namespace com
