#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class ClothingItemXML {
public:
    std::string m_GUID;
    std::string m_MaleModel;
    std::string m_FemaleModel;
    bool m_Static = false;
   public std::vector<std::string> m_BaseTextures = std::make_unique<std::vector<>>();
    std::string m_AttachBone;
   public std::vector<int> m_Masks = std::make_unique<std::vector<>>();
    std::string m_MasksFolder = "media/textures/Body/Masks";
    std::string m_UnderlayMasksFolder = "media/textures/Body/Masks";
   public std::vector<std::string> textureChoices = std::make_unique<std::vector<>>();
    bool m_AllowRandomHue = false;
    bool m_AllowRandomTint = false;
    std::string m_DecalGroup = nullptr;
    std::string m_Shader = nullptr;
    std::string m_HatCategory = nullptr;
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
