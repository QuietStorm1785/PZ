#pragma once
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

 name = "clothingItem"
)
class ClothingItemXML {
 public:
 std::string m_GUID;
 std::string m_MaleModel;
 std::string m_FemaleModel;
 bool m_Static = false;
 public
 ArrayList<String> m_BaseTextures = std::make_unique<ArrayList<>>();
 std::string m_AttachBone;
 public
 ArrayList<Integer> m_Masks = std::make_unique<ArrayList<>>();
 std::string m_MasksFolder = "media/textures/Body/Masks";
 std::string m_UnderlayMasksFolder = "media/textures/Body/Masks";
 public
 ArrayList<String> textureChoices = std::make_unique<ArrayList<>>();
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
