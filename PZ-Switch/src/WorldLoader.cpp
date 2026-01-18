#include "WorldLoader.h"
#include "IsoCell.h"
#include "IsoGridSquare.h"
#include "WorldContent.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool WorldLoader::loadLotFile(const std::string& path, IsoCell* cell, int defaultZ) {
 if (!cell) {
 std::cerr << "WorldLoader: cell is null, cannot load lot file." << std::endl;
 return false;
 }

 std::ifstream file(path);
 if (!file.is_open()) {
 std::cerr << "WorldLoader: failed to open lot file: " << path << std::endl;
 return false;
 }

 int lineNo = 0;
 int placed = 0;
 std::string line;
 while (std::getline(file, line)) {
 lineNo++;
 // Skip comments and empty lines
 std::string trimmed = line;
 trimmed.erase(0, trimmed.find_first_not_of(" \t"));
 if (trimmed.empty() || trimmed[0] == '#') continue;

 std::stringstream ss(trimmed);
 std::string type;
 int x = 0, y = 0, z = defaultZ;
 int solidFlag = 0;

 if (!(ss >> type >> x >> y)) {
 std::cerr << "WorldLoader: parse error at line " << lineNo << " in " << path << std::endl;
 continue;
 }

 // Optional z and solid flag
 if (!(ss >> z)) {
 z = defaultZ;
 ss.clear();
 }
 if (!(ss >> solidFlag)) {
 solidFlag = 0;
 ss.clear();
 }

 IsoObject* obj = IsoWorldObjectFactory::create(type, solidFlag != 0);
 if (!obj) {
 std::cerr << "WorldLoader: unknown object type '" << type << "' at line " << lineNo << std::endl;
 continue;
 }

 obj->setX(static_cast<float>(x));
 obj->setY(static_cast<float>(y));
 obj->setZ(static_cast<float>(z));

 IsoGridSquare* sq = cell->getGridSquare(x, y, z);
 if (!sq) {
 std::cerr << "WorldLoader: missing square for coords (" << x << ", " << y << ", " << z << ")" << std::endl;
 delete obj;
 continue;
 }

 sq->addObject(obj);
 placed++;
 }

 std::cout << "WorldLoader: placed " << placed << " objects from " << path << std::endl;
 return placed > 0;
}
