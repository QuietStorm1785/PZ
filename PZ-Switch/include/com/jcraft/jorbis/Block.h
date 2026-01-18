#pragma once
#include "com/jcraft/jogg/Buffer.h"
#include "com/jcraft/jogg/Packet.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace jcraft {
namespace jorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Block {
public:
 int eofflag;
 int floor_bits;
 int glue_bits;
 long granulepos;
 int lW;
 int mode;
 int nW;
 Buffer opb = std::make_unique<Buffer>();
 float[][] pcm = new float[0][];
 int pcmend;
 int res_bits;
 long sequence;
 int time_bits;
 DspState vd;
 int W;

 static std::string asdsadsa(const std::string &string, byte[] bytes,
 int int0) {
 return string +
 Integer.toString((bytes[int0] & 255) + 256, 16).substring(1);
 }

public
 Block(DspState dspState) {
 this->vd = dspState;
 if (dspState.analysisp != 0) {
 this->opb.writeinit();
 }
 }

 int clear() {
 if (this->vd != nullptr && this->vd.analysisp != 0) {
 this->opb.writeclear();
 }

 return 0;
 }

 void init(DspState dspState) { this->vd = dspState; }

 int synthesis(Packet packet) {
 Info info = this->vd.vi;
 this->opb.readinit(packet.packet_base, packet.packet, packet.bytes);
 if (this->opb.read(1) != 0) {
 return -1;
 } else {
 int int0 = this->opb.read(this->vd.modebits);
 if (int0 == -1) {
 return -1;
 } else {
 this->mode = int0;
 this->W = info.mode_param[this->mode].blockflag;
 if (this->W != 0) {
 this->lW = this->opb.read(1);
 this->nW = this->opb.read(1);
 if (this->nW == -1) {
 return -1;
 }
 } else {
 this->lW = 0;
 this->nW = 0;
 }

 this->granulepos = packet.granulepos;
 this->sequence = packet.packetno - 3L;
 this->eofflag = packet.e_o_s;
 this->pcmend = info.blocksizes[this->W];
 if (this->pcm.length < info.channels) {
 this->pcm = new float[info.channels][];
 }

 for (int int1 = 0; int1 < info.channels; int1++) {
 if (this->pcm[int1] != nullptr &&
 this->pcm[int1].length >= this->pcmend) {
 for (int int2 = 0; int2 < this->pcmend; int2++) {
 this->pcm[int1][int2] = 0.0F;
 }
 } else {
 this->pcm[int1] = new float[this->pcmend];
 }
 }

 int int3 = info.map_type[info.mode_param[this->mode].mapping];
 return FuncMapping.mapping_P[int3].inverse(this,
 this->vd.mode[this->mode]);
 }
 }
 }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
