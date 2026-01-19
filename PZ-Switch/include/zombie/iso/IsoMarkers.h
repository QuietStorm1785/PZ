#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/Type.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoMarkers {
public:
 static const IsoMarkers instance = new IsoMarkers();
 static int NextIsoMarkerID = 0;
private
 List<IsoMarkers.IsoMarker> markers = std::make_unique<ArrayList<>>();
private
 List<IsoMarkers.CircleIsoMarker> circlemarkers =
 std::make_unique<ArrayList<>>();
 static int NextCircleIsoMarkerID = 0;

private
 IsoMarkers() {}

 void init() {}

 void reset() {
 this->markers.clear();
 this->circlemarkers.clear();
 }

 void update() {
 if (!GameServer.bServer) {
 this->updateIsoMarkers();
 this->updateCircleIsoMarkers();
 }
 }

 void updateIsoMarkers() {
 if (IsoCamera.frameState.playerIndex == 0) {
 if (this->markers.size() != 0) {
 for (int int0 = this->markers.size() - 1; int0 >= 0; int0--) {
 if (this->markers.get(int0).isRemoved()) {
 if (this->markers.get(int0).hasTempSquareObject()) {
 this->markers.get(int0).removeTempSquareObjects();
 }

 this->markers.remove(int0);
 }
 }

 for (int int1 = 0; int1 < this->markers.size(); int1++) {
 IsoMarkers.IsoMarker marker = this->markers.get(int1);
 if (marker.alphaInc) {
 marker.alpha =
 marker.alpha +
 GameTime.getInstance().getMultiplier() * marker.fadeSpeed;
 if (marker.alpha > marker.alphaMax) {
 marker.alphaInc = false;
 marker.alpha = marker.alphaMax;
 }
 } else {
 marker.alpha =
 marker.alpha -
 GameTime.getInstance().getMultiplier() * marker.fadeSpeed;
 if (marker.alpha < marker.alphaMin) {
 marker.alphaInc = true;
 marker.alpha = 0.3F;
 }
 }
 }
 }
 }
 }

 bool removeIsoMarker(IsoMarkers.IsoMarker marker) {
 return this->removeIsoMarker(marker.getID());
 }

 bool removeIsoMarker(int id) {
 for (int int0 = this->markers.size() - 1; int0 >= 0; int0--) {
 if (this->markers.get(int0).getID() == id) {
 this->markers.get(int0).remove();
 this->markers.remove(int0);
 return true;
 }
 }

 return false;
 }

public
 IsoMarkers.IsoMarker getIsoMarker(int id) {
 for (int int0 = 0; int0 < this->markers.size(); int0++) {
 if (this->markers.get(int0).getID() == id) {
 return this->markers.get(int0);
 }
 }

 return nullptr;
 }

public
 IsoMarkers.IsoMarker addIsoMarker(String spriteName, IsoGridSquare gs,
 float r, float g, float b, boolean doAlpha,
 boolean doIsoObject) {
 if (GameServer.bServer) {
 return nullptr;
 } else {
 IsoMarkers.IsoMarker marker = new IsoMarkers.IsoMarker();
 marker.setSquare(gs);
 marker.init(spriteName, gs.x, gs.y, gs.z, gs, doIsoObject);
 marker.setR(r);
 marker.setG(g);
 marker.setB(b);
 marker.setA(1.0F);
 marker.setDoAlpha(doAlpha);
 marker.setFadeSpeed(0.006F);
 marker.setAlpha(1.0F);
 marker.setAlphaMin(0.3F);
 marker.setAlphaMax(1.0F);
 this->markers.add(marker);
 return marker;
 }
 }

public
 IsoMarkers.IsoMarker addIsoMarker(KahluaTable textureTable,
 KahluaTable textureOverlayTable,
 IsoGridSquare gs, float r, float g, float b,
 boolean doAlpha, boolean doIsoObject) {
 return this->addIsoMarker(textureTable, textureOverlayTable, gs, r, g, b,
 doAlpha, doIsoObject, 0.006F, 0.3F, 1.0F);
 }

public
 IsoMarkers.IsoMarker addIsoMarker(KahluaTable textureTable,
 KahluaTable textureOverlayTable,
 IsoGridSquare gs, float r, float g, float b,
 boolean doAlpha, boolean doIsoObject,
 float fadeSpeed, float fadeMin,
 float fadeMax) {
 if (GameServer.bServer) {
 return nullptr;
 } else {
 IsoMarkers.IsoMarker marker = new IsoMarkers.IsoMarker();
 marker.init(textureTable, textureOverlayTable, gs.x, gs.y, gs.z, gs,
 doIsoObject);
 marker.setSquare(gs);
 marker.setR(r);
 marker.setG(g);
 marker.setB(b);
 marker.setA(1.0F);
 marker.setDoAlpha(doAlpha);
 marker.setFadeSpeed(fadeSpeed);
 marker.setAlpha(0.0F);
 marker.setAlphaMin(fadeMin);
 marker.setAlphaMax(fadeMax);
 this->markers.add(marker);
 return marker;
 }
 }

 void renderIsoMarkers(IsoCell.PerPlayerRender perPlayerRender, int zLayer,
 int playerIndex) {
 if (!GameServer.bServer && this->markers.size() != 0) {
 IsoPlayer player = IsoPlayer.players[playerIndex];
 if (player != nullptr) {
 for (int int0 = 0; int0 < this->markers.size(); int0++) {
 IsoMarkers.IsoMarker marker = this->markers.get(int0);
 if (marker.z == zLayer && marker.z == player.getZ() &&
 marker.active) {
 for (int int1 = 0; int1 < marker.textures.size(); int1++) {
 Texture texture = marker.textures.get(int1);
 float float0 =
 IsoUtils.XToScreen(marker.x, marker.y, marker.z, 0) -
 IsoCamera.cameras[playerIndex].getOffX() -
 texture.getWidth() / 2.0F;
 float float1 =
 IsoUtils.YToScreen(marker.x, marker.y, marker.z, 0) -
 IsoCamera.cameras[playerIndex].getOffY() -
 texture.getHeight();
 SpriteRenderer.instance.render(
 texture, float0, float1, texture.getWidth(),
 texture.getHeight(), marker.r, marker.g, marker.b,
 marker.alpha, nullptr);
 }
 }
 }
 }
 }
 }

 void renderIsoMarkersDeferred(IsoCell.PerPlayerRender perPlayerRender,
 int zLayer, int playerIndex) {
 if (!GameServer.bServer && this->markers.size() != 0) {
 IsoPlayer player = IsoPlayer.players[playerIndex];
 if (player != nullptr) {
 for (int int0 = 0; int0 < this->markers.size(); int0++) {
 IsoMarkers.IsoMarker marker = this->markers.get(int0);
 if (marker.z == zLayer && marker.z == player.getZ() &&
 marker.active) {
 for (int int1 = 0; int1 < marker.overlayTextures.size(); int1++) {
 Texture texture = marker.overlayTextures.get(int1);
 float float0 =
 IsoUtils.XToScreen(marker.x, marker.y, marker.z, 0) -
 IsoCamera.cameras[playerIndex].getOffX() -
 texture.getWidth() / 2.0F;
 float float1 =
 IsoUtils.YToScreen(marker.x, marker.y, marker.z, 0) -
 IsoCamera.cameras[playerIndex].getOffY() -
 texture.getHeight();
 SpriteRenderer.instance.render(
 texture, float0, float1, texture.getWidth(),
 texture.getHeight(), marker.r, marker.g, marker.b,
 marker.alpha, nullptr);
 }
 }
 }
 }
 }
 }

 void renderIsoMarkersOnSquare(IsoCell.PerPlayerRender perPlayerRender,
 int zLayer, int playerIndex) {
 if (!GameServer.bServer && this->markers.size() != 0) {
 IsoPlayer player = IsoPlayer.players[playerIndex];
 if (player != nullptr) {
 for (int int0 = 0; int0 < this->markers.size(); int0++) {
 IsoMarkers.IsoMarker marker = this->markers.get(int0);
 if (marker.z == zLayer && marker.z == player.getZ() &&
 marker.active) {
 for (int int1 = 0; int1 < marker.overlayTextures.size(); int1++) {
 Texture texture = marker.overlayTextures.get(int1);
 float float0 =
 IsoUtils.XToScreen(marker.x, marker.y, marker.z, 0) -
 IsoCamera.cameras[playerIndex].getOffX() -
 texture.getWidth() / 2.0F;
 float float1 =
 IsoUtils.YToScreen(marker.x, marker.y, marker.z, 0) -
 IsoCamera.cameras[playerIndex].getOffY() -
 texture.getHeight();
 SpriteRenderer.instance.render(
 texture, float0, float1, texture.getWidth(),
 texture.getHeight(), marker.r, marker.g, marker.b,
 marker.alpha, nullptr);
 }
 }
 }
 }
 }
 }

 void updateCircleIsoMarkers() {
 if (IsoCamera.frameState.playerIndex == 0) {
 if (this->circlemarkers.size() != 0) {
 for (int int0 = this->circlemarkers.size() - 1; int0 >= 0; int0--) {
 if (this->circlemarkers.get(int0).isRemoved()) {
 this->circlemarkers.remove(int0);
 }
 }

 for (int int1 = 0; int1 < this->circlemarkers.size(); int1++) {
 IsoMarkers.CircleIsoMarker circleIsoMarker =
 this->circlemarkers.get(int1);
 if (circleIsoMarker.alphaInc) {
 circleIsoMarker.alpha =
 circleIsoMarker.alpha + GameTime.getInstance().getMultiplier() *
 circleIsoMarker.fadeSpeed;
 if (circleIsoMarker.alpha > circleIsoMarker.alphaMax) {
 circleIsoMarker.alphaInc = false;
 circleIsoMarker.alpha = circleIsoMarker.alphaMax;
 }
 } else {
 circleIsoMarker.alpha =
 circleIsoMarker.alpha - GameTime.getInstance().getMultiplier() *
 circleIsoMarker.fadeSpeed;
 if (circleIsoMarker.alpha < circleIsoMarker.alphaMin) {
 circleIsoMarker.alphaInc = true;
 circleIsoMarker.alpha = 0.3F;
 }
 }
 }
 }
 }
 }

 bool removeCircleIsoMarker(IsoMarkers.CircleIsoMarker marker) {
 return this->removeCircleIsoMarker(marker.getID());
 }

 bool removeCircleIsoMarker(int id) {
 for (int int0 = this->circlemarkers.size() - 1; int0 >= 0; int0--) {
 if (this->circlemarkers.get(int0).getID() == id) {
 this->circlemarkers.get(int0).remove();
 this->circlemarkers.remove(int0);
 return true;
 }
 }

 return false;
 }

public
 IsoMarkers.CircleIsoMarker getCircleIsoMarker(int id) {
 for (int int0 = 0; int0 < this->circlemarkers.size(); int0++) {
 if (this->circlemarkers.get(int0).getID() == id) {
 return this->circlemarkers.get(int0);
 }
 }

 return nullptr;
 }

public
 IsoMarkers.CircleIsoMarker addCircleIsoMarker(IsoGridSquare gs, float r,
 float g, float b, float a) {
 if (GameServer.bServer) {
 return nullptr;
 } else {
 IsoMarkers.CircleIsoMarker circleIsoMarker =
 new IsoMarkers.CircleIsoMarker();
 circleIsoMarker.init(gs.x, gs.y, gs.z, gs);
 circleIsoMarker.setSquare(gs);
 circleIsoMarker.setR(r);
 circleIsoMarker.setG(g);
 circleIsoMarker.setB(b);
 circleIsoMarker.setA(a);
 circleIsoMarker.setDoAlpha(false);
 circleIsoMarker.setFadeSpeed(0.006F);
 circleIsoMarker.setAlpha(1.0F);
 circleIsoMarker.setAlphaMin(1.0F);
 circleIsoMarker.setAlphaMax(1.0F);
 this->circlemarkers.add(circleIsoMarker);
 return circleIsoMarker;
 }
 }

 void renderCircleIsoMarkers(IsoCell.PerPlayerRender perPlayerRender,
 int zLayer, int playerIndex) {
 if (!GameServer.bServer && this->circlemarkers.size() != 0) {
 IsoPlayer player = IsoPlayer.players[playerIndex];
 if (player != nullptr) {
 for (int int0 = 0; int0 < this->circlemarkers.size(); int0++) {
 IsoMarkers.CircleIsoMarker circleIsoMarker =
 this->circlemarkers.get(int0);
 if (circleIsoMarker.z == zLayer &&
 circleIsoMarker.z == player.getZ() && circleIsoMarker.active) {
 LineDrawer.DrawIsoCircle(circleIsoMarker.x, circleIsoMarker.y,
 circleIsoMarker.z, circleIsoMarker.size,
 32, circleIsoMarker.r, circleIsoMarker.g,
 circleIsoMarker.b, circleIsoMarker.a);
 }
 }
 }
 }
 }

 void render() { this->update(); }

public
 static class CircleIsoMarker {
 int ID;
 IsoGridSquare square;
 float x;
 float y;
 float z;
 float r;
 float g;
 float b;
 float a;
 float size;
 bool doAlpha;
 float fadeSpeed = 0.006F;
 float alpha = 0.0F;
 float alphaMax = 1.0F;
 float alphaMin = 0.3F;
 bool alphaInc = true;
 bool active = true;
 bool isRemoved = false;

 public
 CircleIsoMarker() { this->ID = IsoMarkers.NextCircleIsoMarkerID++; }

 int getID() { return this->ID; }

 void remove() { this->isRemoved = true; }

 bool isRemoved() { return this->isRemoved; }

 void init(int _x, int _y, int _z, IsoGridSquare gs) { this->square = gs; }

 float getX() { return this->x; }

 float getY() { return this->y; }

 float getZ() { return this->z; }

 float getR() { return this->r; }

 float getG() { return this->g; }

 float getB() { return this->b; }

 float getA() { return this->a; }

 void setR(float _r) { this->r = _r; }

 void setG(float _g) { this->g = _g; }

 void setB(float _b) { this->b = _b; }

 void setA(float _a) { this->a = _a; }

 float getSize() noexcept{ return this->size; }

 void setSize(float _size) { this->size = _size; }

 float getAlpha() { return this->alpha; }

 void setAlpha(float _alpha) { this->alpha = _alpha; }

 float getAlphaMax() { return this->alphaMax; }

 void setAlphaMax(float _alphaMax) { this->alphaMax = _alphaMax; }

 float getAlphaMin() { return this->alphaMin; }

 void setAlphaMin(float _alphaMin) { this->alphaMin = _alphaMin; }

 bool isDoAlpha() { return this->doAlpha; }

 void setDoAlpha(bool _doAlpha) { this->doAlpha = _doAlpha; }

 float getFadeSpeed() { return this->fadeSpeed; }

 void setFadeSpeed(float _fadeSpeed) { this->fadeSpeed = _fadeSpeed; }

 IsoGridSquare getSquare() { return this->square; }

 void setSquare(IsoGridSquare _square) { this->square = _square; }

 void setPos(int _x, int _y, int _z) {
 this->x = _x;
 this->y = _y;
 this->z = _z;
 }

 bool isActive() { return this->active; }

 void setActive(bool _active) { this->active = _active; }
 }

 public static class IsoMarker {
 int ID;
 private
 ArrayList<Texture> textures = std::make_unique<ArrayList<>>();
 private
 ArrayList<Texture> overlayTextures = std::make_unique<ArrayList<>>();
 private
 ArrayList<IsoObject> tempObjects = std::make_unique<ArrayList<>>();
 IsoGridSquare square;
 float x;
 float y;
 float z;
 float r;
 float g;
 float b;
 float a;
 bool doAlpha;
 float fadeSpeed = 0.006F;
 float alpha = 0.0F;
 float alphaMax = 1.0F;
 float alphaMin = 0.3F;
 bool alphaInc = true;
 bool active = true;
 bool isRemoved = false;

 public
 IsoMarker() { this->ID = IsoMarkers.NextIsoMarkerID++; }

 int getID() { return this->ID; }

 void remove() { this->isRemoved = true; }

 bool isRemoved() { return this->isRemoved; }

 void init(KahluaTable textureTable, KahluaTable textureOverlayTable, int _x,
 int _y, int _z, IsoGridSquare gs) {
 this->square = gs;
 if (textureTable != nullptr) {
 int int0 = textureTable.len();

 for (int int1 = 1; int1 <= int0; int1++) {
 std::string string0 =
 Type.tryCastTo(textureTable.rawget(int1), String.class);
 Texture texture0 = Texture.trygetTexture(string0);
 if (texture0 != nullptr) {
 this->textures.add(texture0);
 this->setPos(_x, _y, _z);
 }
 }
 }

 if (textureOverlayTable != nullptr) {
 int int2 = textureOverlayTable.len();

 for (int int3 = 1; int3 <= int2; int3++) {
 std::string string1 =
 Type.tryCastTo(textureOverlayTable.rawget(int3), String.class);
 Texture texture1 = Texture.trygetTexture(string1);
 if (texture1 != nullptr) {
 this->overlayTextures.add(texture1);
 this->setPos(_x, _y, _z);
 }
 }
 }
 }

 void init(KahluaTable textureTable, KahluaTable textureOverlayTable, int _x,
 int _y, int _z, IsoGridSquare gs, bool doTempIsoObject) {
 this->square = gs;
 if (doTempIsoObject) {
 if (textureTable != nullptr) {
 int int0 = textureTable.len();

 for (int int1 = 1; int1 <= int0; int1++) {
 std::string string =
 Type.tryCastTo(textureTable.rawget(int1), String.class);
 Texture texture = Texture.trygetTexture(string);
 if (texture != nullptr) {
 IsoObject object =
 new IsoObject(gs.getCell(), gs, texture.getName());
 this->tempObjects.add(object);
 this->addTempSquareObject(object);
 this->setPos(_x, _y, _z);
 }
 }
 }
 } else {
 this->init(textureTable, textureOverlayTable, _x, _y, _z, gs);
 }
 }

 void init(std::string_view spriteName, int _x, int _y, int _z,
 IsoGridSquare gs, bool doTempIsoObject) {
 this->square = gs;
 if (doTempIsoObject && spriteName != nullptr) {
 IsoObject object = IsoObject.getNew(gs, spriteName, spriteName, false);
 this->tempObjects.add(object);
 this->addTempSquareObject(object);
 this->setPos(_x, _y, _z);
 }
 }

 bool hasTempSquareObject() { return this->tempObjects.size() > 0; }

 void addTempSquareObject(IsoObject tempObject) {
 this->square.localTemporaryObjects.add(tempObject);
 }

 void removeTempSquareObjects() {
 this->square.localTemporaryObjects.clear();
 }

 float getX() { return this->x; }

 float getY() { return this->y; }

 float getZ() { return this->z; }

 float getR() { return this->r; }

 float getG() { return this->g; }

 float getB() { return this->b; }

 float getA() { return this->a; }

 void setR(float _r) { this->r = _r; }

 void setG(float _g) { this->g = _g; }

 void setB(float _b) { this->b = _b; }

 void setA(float _a) { this->a = _a; }

 float getAlpha() { return this->alpha; }

 void setAlpha(float _alpha) { this->alpha = _alpha; }

 float getAlphaMax() { return this->alphaMax; }

 void setAlphaMax(float _alphaMax) { this->alphaMax = _alphaMax; }

 float getAlphaMin() { return this->alphaMin; }

 void setAlphaMin(float _alphaMin) { this->alphaMin = _alphaMin; }

 bool isDoAlpha() { return this->doAlpha; }

 void setDoAlpha(bool _doAlpha) { this->doAlpha = _doAlpha; }

 float getFadeSpeed() { return this->fadeSpeed; }

 void setFadeSpeed(float _fadeSpeed) { this->fadeSpeed = _fadeSpeed; }

 IsoGridSquare getSquare() { return this->square; }

 void setSquare(IsoGridSquare _square) { this->square = _square; }

 void setPos(int _x, int _y, int _z) {
 this->x = _x + 0.5F;
 this->y = _y + 0.5F;
 this->z = _z;
 }

 bool isActive() { return this->active; }

 void setActive(bool _active) { this->active = _active; }
 }
}
} // namespace iso
} // namespace zombie
