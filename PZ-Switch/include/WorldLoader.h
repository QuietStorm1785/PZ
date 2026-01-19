#pragma once
#include <string>
#include <string_view>

class IsoCell;

// Loads simple .lot-style files and places IsoObjects into the world grid
class WorldLoader {
public:
 // Format per line: TYPE x y [z] [solid]
 // Example: tree 10 12 0 0
 // Lines starting with # are ignored.
 static bool loadLotFile(std::string_view path, IsoCell* cell, int defaultZ = 0);
};
