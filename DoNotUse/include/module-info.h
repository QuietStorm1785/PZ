#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

module org.lwjgl.opengl.natives {
   requires transitive org.lwjgl.opengl;

   opens windows.x64.org.lwjgl.opengl;
}
