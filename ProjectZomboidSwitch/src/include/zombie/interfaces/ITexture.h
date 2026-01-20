#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Mask.h"
#include "zombie/core/utils/WrappedBuffer.h"
#include <filesystem>

namespace zombie {
namespace interfaces {


class ITexture {
public:
    virtual ~ITexture() = default;
    void bind();

    void bind(int var1);

    WrappedBuffer getData();

    int getHeight();

    int getHeightHW();

    int getID();

    int getWidth();

    int getWidthHW();

    float getXEnd();

    float getXStart();

    float getYEnd();

    float getYStart();

    bool isSolid();

    void makeTransp(int var1, int var2, int var3);

    void setAlphaForeach(int var1, int var2, int var3, int var4);

    void setData(ByteBuffer var1);

    void setMask(Mask var1);

    void setRegion(int var1, int var2, int var3, int var4);
}
} // namespace interfaces
} // namespace zombie
