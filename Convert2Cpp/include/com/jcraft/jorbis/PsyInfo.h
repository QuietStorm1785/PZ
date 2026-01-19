#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace jcraft {
namespace jorbis {

class PsyInfo {
public:
    float ath_att;
    int athp;
    float attack_coeff;
    float decay_coeff;
    int decayp;
    float max_curve_dB;
   std::vector<float> noiseatt_1000Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> noiseatt_125Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> noiseatt_2000Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> noiseatt_250Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> noiseatt_4000Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> noiseatt_500Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> noiseatt_8000Hz = std::make_shared<std::array<float, 5>>();
    int noisefit_subblock;
    float noisefit_threshdB;
    int noisefitp;
    int noisemaskp;
   std::vector<float> peakatt_1000Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> peakatt_125Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> peakatt_2000Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> peakatt_250Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> peakatt_4000Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> peakatt_500Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> peakatt_8000Hz = std::make_shared<std::array<float, 5>>();
    int peakattp;
    int smoothp;
   std::vector<float> toneatt_1000Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> toneatt_125Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> toneatt_2000Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> toneatt_250Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> toneatt_4000Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> toneatt_500Hz = std::make_shared<std::array<float, 5>>();
   std::vector<float> toneatt_8000Hz = std::make_shared<std::array<float, 5>>();
    int tonemaskp;

    void free() {
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
