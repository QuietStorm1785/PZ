#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by kroto on 7/12/2017.
 */
enum class TransmissionNumber {
 R(-1), N(0), Speed1(1), Speed2(2), Speed3(3), Speed4(4), Speed5(5), Speed6(6),
 Speed7(7), Speed8(8);

 const int index;

 private TransmissionNumber(int int1){this->index = int1;}

int getIndex() { return this->index; }

static TransmissionNumber fromIndex(int _index) {
 switch (_index) {
 case -1:
 return R;
 case 0:
 return N;
 case 1:
 return Speed1;
 case 2:
 return Speed2;
 case 3:
 return Speed3;
 case 4:
 return Speed4;
 case 5:
 return Speed5;
 case 6:
 return Speed6;
 case 7:
 return Speed7;
 case 8:
 return Speed8;
 default:
 return N;
 }
}

TransmissionNumber getNext(int gearRatioCount) {
 return this->index != -1 && this->index != gearRatioCount
 ? fromIndex(this->index + 1)
 : this;
}

TransmissionNumber getPrev(int gearRatioCount) {
 return this->index != -1 && this->index != gearRatioCount
 ? fromIndex(this->index - 1)
 : this;
}

std::string getString() {
 switch (this->index) {
 case -1:
 return "R";
 case 0:
 return "N";
 case 1:
 return "1";
 case 2:
 return "2";
 case 3:
 return "3";
 case 4:
 return "4";
 case 5:
 return "5";
 case 6:
 return "6";
 case 7:
 return "7";
 case 8:
 return "8";
 default:
 return "";
 }
}
} // namespace vehicles
} // namespace zombie
} // namespace zombie
