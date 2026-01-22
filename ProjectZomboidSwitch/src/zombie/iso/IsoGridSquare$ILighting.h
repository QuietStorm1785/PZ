#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoGridSquare/ResultLight.h"

namespace zombie {
namespace iso {


class IsoGridSquare {
public:
    virtual ~IsoGridSquare() = default;
    int lightverts(int var1);

    float lampostTotalR();

    float lampostTotalG();

    float lampostTotalB();

    bool bSeen();

    bool bCanSee();

    bool bCouldSee();

    float darkMulti();

    float targetDarkMulti();

    ColorInfo lightInfo();

    void lightverts(int var1, int var2);

    void lampostTotalR(float var1);

    void lampostTotalG(float var1);

    void lampostTotalB(float var1);

    void bSeen(bool var1);

    void bCanSee(bool var1);

    void bCouldSee(bool var1);

    void darkMulti(float var1);

    void targetDarkMulti(float var1);

    int resultLightCount();

    ResultLight getResultLight(int var1);

    void reset();
}
} // namespace iso
} // namespace zombie
