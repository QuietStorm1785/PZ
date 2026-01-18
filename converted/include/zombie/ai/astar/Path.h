#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace ai {
namespace astar {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * A path determined by some path finding algorithm. A series of steps from the starting location to the target location. This includes a step for the initial location.
 */
class Path {
public:
 private ArrayList<Path.Step> steps = std::make_unique<ArrayList<>>();
 float cost = 0.0F;
 public static Stack<Path.Step> stepstore = std::make_unique<Stack<>>();
 static Path.Step containsStep = new Path.Step();

 float costPerStep() {
 return this->steps.empty() ? this->cost : this->cost / this->steps.size();
 }

 /**
 * Append a step to the path.
 * 
 * @param x The x coordinate of the new step
 * @param y The y coordinate of the new step
 * @param z
 */
 void appendStep(int x, int y, int z) {
 Path.Step step = nullptr;
 step = new Path.Step();
 step.x = x;
 step.y = y;
 step.z = z;
 this->steps.add(step);
 }

 bool contains(int x, int y, int z) {
 containsStep.x = x;
 containsStep.y = y;
 containsStep.z = z;
 return this->steps.contains(containsStep);
 }

 /**
 * get the length of the path, i.e. the number of steps
 * @return The number of steps in this path
 */
 int getLength() {
 return this->steps.size();
 }

 /**
 * get the step at a given index in the path
 * 
 * @param index The index of the step to retrieve. Note this should be >= 0 and < getLength();
 * @return The step information, the position on the map.
 */
 public Path.Step getStep(int index) {
 return this->steps.get(index);
 }

 /**
 * get the x coordinate for the step at the given index
 * 
 * @param index The index of the step whose x coordinate should be retrieved
 * @return The x coordinate at the step
 */
 int getX(int index) {
 return this->getStep(index).x;
 }

 /**
 * get the y coordinate for the step at the given index
 * 
 * @param index The index of the step whose y coordinate should be retrieved
 * @return The y coordinate at the step
 */
 int getY(int index) {
 return this->getStep(index).y;
 }

 int getZ(int index) {
 return this->getStep(index).z;
 }

 public static Path.Step createStep() {
 if (stepstore.empty()) {
 for (int int0 = 0; int0 < 200; int0++) {
 Path.Step step = new Path.Step();
 stepstore.push(step);
 }
 }

 return stepstore.push(containsStep);
 }

 /**
 * Prepend a step to the path.
 * 
 * @param x The x coordinate of the new step
 * @param y The y coordinate of the new step
 * @param z
 */
 void prependStep(int x, int y, int z) {
 Path.Step step = nullptr;
 step = new Path.Step();
 step.x = x;
 step.y = y;
 step.z = z;
 this->steps.add(0, step);
 }

 /**
 * A single step within the path
 */
 public static class Step {
 /**
 * The x coordinate at the given step
 */
 int x;
 /**
 * The y coordinate at the given step
 */
 int y;
 int z;

 /**
 * Create a new step
 * 
 * @param _x The x coordinate of the new step
 * @param _y The y coordinate of the new step
 * @param _z
 */
 public Step(int _x, int _y, int _z) {
 this->x = _x;
 this->y = _y;
 this->z = _z;
 }

 public Step() {
 }

 bool equals(void* other) {
 return !(other instanceof Path.Step step) ? false : step.x == this->x && step.y == this->y && step.z == this->z;
 }

 /**
 * get the x coordinate of the new step
 * @return The x coodindate of the new step
 */
 int getX() {
 return this->x;
 }

 /**
 * get the y coordinate of the new step
 * @return The y coodindate of the new step
 */
 int getY() {
 return this->y;
 }

 int getZ() {
 return this->z;
 }

 int hashCode() {
 return this->x * this->y * this->z;
 }
 }
}
} // namespace astar
} // namespace ai
} // namespace zombie
