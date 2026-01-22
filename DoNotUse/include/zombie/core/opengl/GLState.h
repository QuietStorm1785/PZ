#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/opengl/GLState/CAlphaFunc.h"
#include "zombie/core/opengl/GLState/CAlphaTest.h"
#include "zombie/core/opengl/GLState/CBlendFunc.h"
#include "zombie/core/opengl/GLState/CBlendFuncSeparate.h"
#include "zombie/core/opengl/GLState/CColorMask.h"
#include "zombie/core/opengl/GLState/CStencilFunc.h"
#include "zombie/core/opengl/GLState/CStencilMask.h"
#include "zombie/core/opengl/GLState/CStencilOp.h"
#include "zombie/core/opengl/GLState/CStencilTest.h"

namespace zombie {
namespace core {
namespace opengl {


class GLState {
public:
    static const CAlphaFunc AlphaFunc = std::make_shared<CAlphaFunc>();
    static const CAlphaTest AlphaTest = std::make_shared<CAlphaTest>();
    static const CBlendFunc BlendFunc = std::make_shared<CBlendFunc>();
    static const CBlendFuncSeparate BlendFuncSeparate = std::make_shared<CBlendFuncSeparate>();
    static const CColorMask ColorMask = std::make_shared<CColorMask>();
    static const CStencilFunc StencilFunc = std::make_shared<CStencilFunc>();
    static const CStencilMask StencilMask = std::make_shared<CStencilMask>();
    static const CStencilOp StencilOp = std::make_shared<CStencilOp>();
    static const CStencilTest StencilTest = std::make_shared<CStencilTest>();

    static void startFrame() {
      AlphaFunc.setDirty();
      AlphaTest.setDirty();
      BlendFunc.setDirty();
      BlendFuncSeparate.setDirty();
      ColorMask.setDirty();
      StencilFunc.setDirty();
      StencilMask.setDirty();
      StencilOp.setDirty();
      StencilTest.setDirty();
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
