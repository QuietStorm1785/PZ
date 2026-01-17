#include "zombie/iso/IsoCell.h"

namespace zombie {
namespace iso {

int IsoCell::getMaxHeight() {
  // TODO: Implement getMaxHeight
  return 0;
}

LotHeader IsoCell::getCurrentLotHeader() {
  // TODO: Implement getCurrentLotHeader
  return nullptr;
}

IsoChunkMap IsoCell::getChunkMap(int pl) {
  // TODO: Implement getChunkMap
  return nullptr;
}

IsoGridSquare IsoCell::getFreeTile(RoomDef def) {
  // TODO: Implement getFreeTile
  return nullptr;
}

void IsoCell::setBuildings(Stack<BuildingScore> scores) {
  // TODO: Implement setBuildings
}

IsoZombie IsoCell::getNearestVisibleZombie(int playerIndex) {
  // TODO: Implement getNearestVisibleZombie
  return nullptr;
}

IsoChunk IsoCell::getChunkForGridSquare(int x, int y, int z) {
  // TODO: Implement getChunkForGridSquare
  return nullptr;
}

IsoChunk IsoCell::getChunk(int _wx, int _wy) {
  // TODO: Implement getChunk
  return nullptr;
}

public
IsoCell::IsoCell(int _width, int _height) {
  // TODO: Implement IsoCell
  return nullptr;
}

short IsoCell::getStencilValue(int x, int y, int z) {
  // TODO: Implement getStencilValue
  return 0;
}

void IsoCell::setStencilValue(int x, int y, int z, int stencil) {
  // TODO: Implement setStencilValue
}

short IsoCell::getStencilValue2z(int x, int y, int z) {
  // TODO: Implement getStencilValue2z
  return 0;
}

void IsoCell::setStencilValue2z(int x, int y, int z, int stencil) {
  // TODO: Implement setStencilValue2z
}

void IsoCell::CalculateVertColoursForTile(IsoGridSquare sqThis, int x, int y,
                                          int zz, int playerIndex) {
  // TODO: Implement CalculateVertColoursForTile
}

Texture IsoCell::getStencilTexture() {
  // TODO: Implement getStencilTexture
  return nullptr;
}

void IsoCell::DrawStencilMask() {
  // TODO: Implement DrawStencilMask
}

void IsoCell::RenderTiles(int _MaxHeight) {
  // TODO: Implement RenderTiles
}

void IsoCell::renderTilesInternal(int int1) {
  // TODO: Implement renderTilesInternal
}

void IsoCell::initTileShaders() {
  // TODO: Implement initTileShaders
}

void IsoCell::recalculateAnyGridStacks(IsoCell.PerPlayerRender perPlayerRenderx,
                                       int int5, int int0, long long0) {
  // TODO: Implement recalculateAnyGridStacks
}

void IsoCell::flattenAnyFoliage(IsoCell.PerPlayerRender perPlayerRenderx,
                                int int3) {
  // TODO: Implement flattenAnyFoliage
}

void IsoCell::performRenderTiles(IsoCell.PerPlayerRender perPlayerRenderx,
                                 int int1, int int3, long long0) {
  // TODO: Implement performRenderTiles
}

void IsoCell::renderShadows() {
  // TODO: Implement renderShadows
}

void IsoCell::renderDebugPhysics(int int0) {
  // TODO: Implement renderDebugPhysics
}

void IsoCell::renderDebugLighting(IsoCell.PerPlayerRender perPlayerRenderx,
                                  int int1) {
  // TODO: Implement renderDebugLighting
}

void IsoCell::CullFullyOccludedSquares(IsoGridStack gridStack,
                                       boolean[][][] booleans1,
                                       boolean[][] booleans0) {
  // TODO: Implement CullFullyOccludedSquares
}

void IsoCell::RenderFloorShading(int zza) {
  // TODO: Implement RenderFloorShading
}

bool IsoCell::IsPlayerWindowPeeking(int playerIndex) {
  // TODO: Implement IsPlayerWindowPeeking
  return false;
}

bool IsoCell::CanBuildingSquareOccludePlayer(IsoGridSquare square,
                                             int playerIndex) {
  // TODO: Implement CanBuildingSquareOccludePlayer
  return false;
}

int IsoCell::GetEffectivePlayerRoomId() {
  // TODO: Implement GetEffectivePlayerRoomId
  return 0;
}

bool IsoCell::SetCutawayRoomsForPlayer() {
  // TODO: Implement SetCutawayRoomsForPlayer
  return false;
}

bool IsoCell::IsCutawaySquare(IsoGridSquare square0, long long0) {
  // TODO: Implement IsCutawaySquare
  return false;
}

bool IsoCell::DoesSquareHaveValidCutaways(IsoGridSquare square6,
                                          IsoGridSquare square1, int int1,
                                          long long0) {
  // TODO: Implement DoesSquareHaveValidCutaways
  return false;
}

bool IsoCell::IsCollapsibleBuildingSquare(IsoGridSquare square) {
  // TODO: Implement IsCollapsibleBuildingSquare
  return false;
}

bool IsoCell::collapsibleBuildingSquareAlgorithm(BuildingDef buildingDef,
                                                 IsoGridSquare square2,
                                                 IsoGridSquare square0) {
  // TODO: Implement collapsibleBuildingSquareAlgorithm
  return false;
}

bool IsoCell::IsDissolvedSquare(IsoGridSquare square1, int int0) {
  // TODO: Implement IsDissolvedSquare
  return false;
}

int IsoCell::GetBuildingHeightAt(IsoBuilding building, int int2, int int3,
                                 int int1) {
  // TODO: Implement GetBuildingHeightAt
  return 0;
}

void IsoCell::updateSnow(int int0) {
  // TODO: Implement updateSnow
}

void IsoCell::setSnowTarget(int target) {
  // TODO: Implement setSnowTarget
}

bool IsoCell::gridSquareIsSnow(int x, int y, int z) {
  // TODO: Implement gridSquareIsSnow
  return false;
}

void IsoCell::RenderSnow(int int6) {
  // TODO: Implement RenderSnow
}

void IsoCell::renderSnowTileBase(Texture texture, int int1, int int0,
                                 float float0, bool boolean0) {
  // TODO: Implement renderSnowTileBase
}

int IsoCell::getShoreInt(IsoGridSquare square) {
  // TODO: Implement getShoreInt
  return 0;
}

bool IsoCell::isSnowShore(IsoGridSquare square1, int int1, int int0) {
  // TODO: Implement isSnowShore
  return false;
}

IsoBuilding IsoCell::getClosestBuildingExcept(IsoGameCharacter chr,
                                              IsoRoom except) {
  // TODO: Implement getClosestBuildingExcept
  return nullptr;
}

int IsoCell::getDangerScore(int x, int y) {
  // TODO: Implement getDangerScore
  return 0;
}

void IsoCell::ObjectDeletionAddition() {
  // TODO: Implement ObjectDeletionAddition
}

void IsoCell::ProcessItems(Iterator<InventoryItem> var1) {
  // TODO: Implement ProcessItems
}

void IsoCell::ProcessIsoObject() {
  // TODO: Implement ProcessIsoObject
}

void IsoCell::ProcessObjects(Iterator<IsoMovingObject> var1) {
  // TODO: Implement ProcessObjects
}

void IsoCell::ProcessRemoveItems(Iterator<InventoryItem> var1) {
  // TODO: Implement ProcessRemoveItems
}

void IsoCell::ProcessStaticUpdaters() {
  // TODO: Implement ProcessStaticUpdaters
}

void IsoCell::addToProcessIsoObject(IsoObject object) {
  // TODO: Implement addToProcessIsoObject
}

void IsoCell::addToProcessIsoObjectRemove(IsoObject object) {
  // TODO: Implement addToProcessIsoObjectRemove
}

void IsoCell::addToStaticUpdaterObjectList(IsoObject object) {
  // TODO: Implement addToStaticUpdaterObjectList
}

void IsoCell::addToProcessItems(InventoryItem item) {
  // TODO: Implement addToProcessItems
}

void IsoCell::addToProcessItems(ArrayList<InventoryItem> items) {
  // TODO: Implement addToProcessItems
}

void IsoCell::addToProcessItemsRemove(InventoryItem item) {
  // TODO: Implement addToProcessItemsRemove
}

void IsoCell::addToProcessItemsRemove(ArrayList<InventoryItem> items) {
  // TODO: Implement addToProcessItemsRemove
}

void IsoCell::addToProcessWorldItems(IsoWorldInventoryObject worldItem) {
  // TODO: Implement addToProcessWorldItems
}

void IsoCell::addToProcessWorldItemsRemove(IsoWorldInventoryObject worldItem) {
  // TODO: Implement addToProcessWorldItemsRemove
}

IsoSurvivor IsoCell::getNetworkPlayer(int RemoteID) {
  // TODO: Implement getNetworkPlayer
  return nullptr;
}

IsoGridSquare IsoCell::ConnectNewSquare(IsoGridSquare square, bool var2,
                                        bool var3) {
  // TODO: Implement ConnectNewSquare
  return nullptr;
}

void IsoCell::DoGridNav(IsoGridSquare newSquare,
                        IsoGridSquare.GetSquare getter) {
  // TODO: Implement DoGridNav
}

IsoGridSquare IsoCell::ConnectNewSquare(IsoGridSquare newSquare,
                                        bool bDoSurrounds) {
  // TODO: Implement ConnectNewSquare
  return nullptr;
}

void IsoCell::PlaceLot(const std::string &filename, int sx, int sy, int sz,
                       bool bClearExisting) {
  // TODO: Implement PlaceLot
}

void IsoCell::PlaceLot(IsoLot lot, int sx, int sy, int sz,
                       bool bClearExisting) {
  // TODO: Implement PlaceLot
}

void IsoCell::PlaceLot(IsoLot lot, int sx, int sy, int sz, IsoChunk ch, int WX,
                       int WY) {
  // TODO: Implement PlaceLot
}

void IsoCell::setDrag(KahluaTable item, int player) {
  // TODO: Implement setDrag
}

KahluaTable IsoCell::getDrag(int player) {
  // TODO: Implement getDrag
  return nullptr;
}

bool IsoCell::DoBuilding(int player, bool bRender) {
  // TODO: Implement DoBuilding
  return false;
}

bool IsoCell::doBuildingInternal(int int0, bool boolean0) {
  // TODO: Implement doBuildingInternal
  return false;
}

float IsoCell::DistanceFromSupport(int x, int y, int z) {
  // TODO: Implement DistanceFromSupport
  return 0;
}

void IsoCell::addToWindowList(IsoWindow window) {
  // TODO: Implement addToWindowList
}

void IsoCell::removeFromWindowList(IsoWindow window) {
  // TODO: Implement removeFromWindowList
}

IsoRoom IsoCell::getRoom(int ID) {
  // TODO: Implement getRoom
  return nullptr;
}

void IsoCell::addMovingObject(IsoMovingObject o) {
  // TODO: Implement addMovingObject
}

int IsoCell::getHeight() {
  // TODO: Implement getHeight
  return 0;
}

void IsoCell::setHeight(int _height) {
  // TODO: Implement setHeight
}

int IsoCell::getWidth() {
  // TODO: Implement getWidth
  return 0;
}

void IsoCell::setWidth(int _width) {
  // TODO: Implement setWidth
}

int IsoCell::getWorldX() {
  // TODO: Implement getWorldX
  return 0;
}

void IsoCell::setWorldX(int _worldX) {
  // TODO: Implement setWorldX
}

int IsoCell::getWorldY() {
  // TODO: Implement getWorldY
  return 0;
}

void IsoCell::setWorldY(int _worldY) {
  // TODO: Implement setWorldY
}

bool IsoCell::isSafeToAdd() {
  // TODO: Implement isSafeToAdd
  return false;
}

void IsoCell::setSafeToAdd(bool _safeToAdd) {
  // TODO: Implement setSafeToAdd
}

IsoLightSource IsoCell::getLightSourceAt(int x, int y, int z) {
  // TODO: Implement getLightSourceAt
  return nullptr;
}

void IsoCell::addLamppost(IsoLightSource light) {
  // TODO: Implement addLamppost
}

IsoLightSource IsoCell::addLamppost(int x, int y, int z, float r, float g,
                                    float b, int rad) {
  // TODO: Implement addLamppost
  return nullptr;
}

void IsoCell::removeLamppost(int x, int y, int z) {
  // TODO: Implement removeLamppost
}

void IsoCell::removeLamppost(IsoLightSource light) {
  // TODO: Implement removeLamppost
}

int IsoCell::getCurrentLightX() {
  // TODO: Implement getCurrentLightX
  return 0;
}

void IsoCell::setCurrentLightX(int _currentLX) {
  // TODO: Implement setCurrentLightX
}

int IsoCell::getCurrentLightY() {
  // TODO: Implement getCurrentLightY
  return 0;
}

void IsoCell::setCurrentLightY(int _currentLY) {
  // TODO: Implement setCurrentLightY
}

int IsoCell::getCurrentLightZ() {
  // TODO: Implement getCurrentLightZ
  return 0;
}

void IsoCell::setCurrentLightZ(int _currentLZ) {
  // TODO: Implement setCurrentLightZ
}

int IsoCell::getMinX() {
  // TODO: Implement getMinX
  return 0;
}

void IsoCell::setMinX(int _minX) {
  // TODO: Implement setMinX
}

int IsoCell::getMaxX() {
  // TODO: Implement getMaxX
  return 0;
}

void IsoCell::setMaxX(int _maxX) {
  // TODO: Implement setMaxX
}

int IsoCell::getMinY() {
  // TODO: Implement getMinY
  return 0;
}

void IsoCell::setMinY(int _minY) {
  // TODO: Implement setMinY
}

int IsoCell::getMaxY() {
  // TODO: Implement getMaxY
  return 0;
}

void IsoCell::setMaxY(int _maxY) {
  // TODO: Implement setMaxY
}

int IsoCell::getMinZ() {
  // TODO: Implement getMinZ
  return 0;
}

void IsoCell::setMinZ(int _minZ) {
  // TODO: Implement setMinZ
}

int IsoCell::getMaxZ() {
  // TODO: Implement getMaxZ
  return 0;
}

void IsoCell::setMaxZ(int _maxZ) {
  // TODO: Implement setMaxZ
}

OnceEvery IsoCell::getDangerUpdate() {
  // TODO: Implement getDangerUpdate
  return nullptr;
}

void IsoCell::setDangerUpdate(OnceEvery _dangerUpdate) {
  // TODO: Implement setDangerUpdate
}

Thread IsoCell::getLightInfoUpdate() {
  // TODO: Implement getLightInfoUpdate
  return nullptr;
}

void IsoCell::setLightInfoUpdate(Thread _LightInfoUpdate) {
  // TODO: Implement setLightInfoUpdate
}

int IsoCell::getRComponent(int col) {
  // TODO: Implement getRComponent
  return 0;
}

int IsoCell::getGComponent(int col) {
  // TODO: Implement getGComponent
  return 0;
}

int IsoCell::getBComponent(int col) {
  // TODO: Implement getBComponent
  return 0;
}

int IsoCell::toIntColor(float r, float g, float b, float a) {
  // TODO: Implement toIntColor
  return 0;
}

IsoGridSquare IsoCell::getRandomOutdoorTile() {
  // TODO: Implement getRandomOutdoorTile
  return nullptr;
}

void IsoCell::InsertAt(int int1, BuildingScore buildingScore,
                       BuildingScore[] buildingScores) {
  // TODO: Implement InsertAt
}

void IsoCell::Place(BuildingScore buildingScore, BuildingScore[] buildingScores,
                    IsoCell.BuildingSearchCriteria buildingSearchCriteria) {
  // TODO: Implement Place
}

bool IsoCell::blocked(Mover mover, int x, int y, int z, int lx, int ly,
                      int lz) {
  // TODO: Implement blocked
  return false;
}

void IsoCell::Dispose() {
  // TODO: Implement Dispose
}

IsoGridSquare IsoCell::getGridSquare(double x, double y, double z) {
  // TODO: Implement getGridSquare
  return nullptr;
}

IsoGridSquare IsoCell::getOrCreateGridSquare(double x, double y, double z) {
  // TODO: Implement getOrCreateGridSquare
  return nullptr;
}

void IsoCell::setCacheGridSquare(int x, int y, int z, IsoGridSquare square) {
  // TODO: Implement setCacheGridSquare
}

void IsoCell::setCacheChunk(IsoChunk chunk) {
  // TODO: Implement setCacheChunk
}

void IsoCell::setCacheChunk(IsoChunk chunk, int playerIndex) {
  // TODO: Implement setCacheChunk
}

void IsoCell::clearCacheGridSquare(int playerIndex) {
  // TODO: Implement clearCacheGridSquare
}

void IsoCell::setCacheGridSquareLocal(int x, int y, int z, IsoGridSquare square,
                                      int playerIndex) {
  // TODO: Implement setCacheGridSquareLocal
}

IsoGridSquare IsoCell::getGridSquare(double x, double y, double z) {
  // TODO: Implement getGridSquare
  return nullptr;
}

IsoGridSquare IsoCell::getGridSquare(int x, int y, int z) {
  // TODO: Implement getGridSquare
  return nullptr;
}

void IsoCell::EnsureSurroundNotNull(int xx, int yy, int zz) {
  // TODO: Implement EnsureSurroundNotNull
}

void IsoCell::DeleteAllMovingObjects() {
  // TODO: Implement DeleteAllMovingObjects
}

int IsoCell::getMaxFloors() {
  // TODO: Implement getMaxFloors
  return 0;
}

KahluaTable IsoCell::getLuaObjectList() {
  // TODO: Implement getLuaObjectList
  return nullptr;
}

int IsoCell::getHeightInTiles() {
  // TODO: Implement getHeightInTiles
  return 0;
}

int IsoCell::getWidthInTiles() {
  // TODO: Implement getWidthInTiles
  return 0;
}

bool IsoCell::isNull(int x, int y, int z) {
  // TODO: Implement isNull
  return false;
}

void IsoCell::Remove(IsoMovingObject obj) {
  // TODO: Implement Remove
}

bool IsoCell::isBlocked(IsoGridSquare square1, IsoGridSquare square0) {
  // TODO: Implement isBlocked
  return false;
}

int IsoCell::CalculateColor(IsoGridSquare square1, IsoGridSquare square2,
                            IsoGridSquare square3, IsoGridSquare square0,
                            int int1, int int0) {
  // TODO: Implement CalculateColor
  return 0;
}

IsoCell IsoCell::getInstance() {
  // TODO: Implement getInstance
  return nullptr;
}

void IsoCell::render() {
  // TODO: Implement render
}

void IsoCell::renderInternal() {
  // TODO: Implement renderInternal
}

void IsoCell::invalidatePeekedRoom(int playerIndex) {
  // TODO: Implement invalidatePeekedRoom
}

bool IsoCell::initWeatherFx() {
  // TODO: Implement initWeatherFx
  return false;
}

void IsoCell::updateWeatherFx() {
  // TODO: Implement updateWeatherFx
}

void IsoCell::renderWeatherFx() {
  // TODO: Implement renderWeatherFx
}

IsoWeatherFX IsoCell::getWeatherFX() {
  // TODO: Implement getWeatherFX
  return nullptr;
}

void IsoCell::renderRain() {
  // TODO: Implement renderRain
}

void IsoCell::setRainAlpha(int alpha) {
  // TODO: Implement setRainAlpha
}

void IsoCell::setRainIntensity(int intensity) {
  // TODO: Implement setRainIntensity
}

void IsoCell::setRainSpeed(int speed) {
  // TODO: Implement setRainSpeed
}

void IsoCell::reloadRainTextures() {
  // TODO: Implement reloadRainTextures
}

void IsoCell::GetBuildingsInFrontOfCharacter(ArrayList<IsoBuilding> arrayList,
                                             IsoGridSquare square,
                                             bool boolean0) {
  // TODO: Implement GetBuildingsInFrontOfCharacter
}

void IsoCell::GetBuildingsInFrontOfCharacterSquare(
    int int0, int int1, int int2, bool boolean0,
    ArrayList<IsoBuilding> arrayList0) {
  // TODO: Implement GetBuildingsInFrontOfCharacterSquare
}

IsoBuilding IsoCell::GetPeekedInBuilding(IsoGridSquare square0,
                                         IsoDirections directions) {
  // TODO: Implement GetPeekedInBuilding
  return nullptr;
}

void IsoCell::GetSquaresAroundPlayerSquare(
    IsoPlayer player, IsoGridSquare square0,
    ArrayList<IsoGridSquare> arrayList0, ArrayList<IsoGridSquare> arrayList1) {
  // TODO: Implement GetSquaresAroundPlayerSquare
}

bool IsoCell::IsBehindStuff(IsoGridSquare square0) {
  // TODO: Implement IsBehindStuff
  return false;
}

IsoDirections IsoCell::FromMouseTile() {
  // TODO: Implement FromMouseTile
  return nullptr;
}

void IsoCell::update() {
  // TODO: Implement update
}

void IsoCell::updateInternal() {
  // TODO: Implement updateInternal
}

IsoGridSquare IsoCell::getRandomFreeTile() {
  // TODO: Implement getRandomFreeTile
  return nullptr;
}

IsoGridSquare IsoCell::getRandomOutdoorFreeTile() {
  // TODO: Implement getRandomOutdoorFreeTile
  return nullptr;
}

IsoGridSquare IsoCell::getRandomFreeTileInRoom() {
  // TODO: Implement getRandomFreeTileInRoom
  return nullptr;
}

void IsoCell::roomSpotted(IsoRoom room) {
  // TODO: Implement roomSpotted
}

void IsoCell::ProcessSpottedRooms() {
  // TODO: Implement ProcessSpottedRooms
}

void IsoCell::savePlayer() {
  // TODO: Implement savePlayer
}

void IsoCell::save(DataOutputStream output, bool bDoChars) {
  // TODO: Implement save
}

bool IsoCell::LoadPlayer(int WorldVersion) {
  // TODO: Implement LoadPlayer
  return false;
}

IsoGridSquare IsoCell::getRelativeGridSquare(int x, int y, int z) {
  // TODO: Implement getRelativeGridSquare
  return nullptr;
}

IsoGridSquare IsoCell::createNewGridSquare(int x, int y, int z,
                                           bool recalcAll) {
  // TODO: Implement createNewGridSquare
  return nullptr;
}

IsoGridSquare IsoCell::getGridSquareDirect(int x, int y, int z,
                                           int playerIndex) {
  // TODO: Implement getGridSquareDirect
  return nullptr;
}

bool IsoCell::isInChunkMap(int x, int y) {
  // TODO: Implement isInChunkMap
  return false;
}

void IsoCell::checkHaveRoof(int x, int y) {
  // TODO: Implement checkHaveRoof
}

IsoZombie IsoCell::getFakeZombieForHit() {
  // TODO: Implement getFakeZombieForHit
  return nullptr;
}

void IsoCell::addHeatSource(IsoHeatSource heatSource) {
  // TODO: Implement addHeatSource
}

void IsoCell::removeHeatSource(IsoHeatSource heatSource) {
  // TODO: Implement removeHeatSource
}

void IsoCell::updateHeatSources() {
  // TODO: Implement updateHeatSources
}

int IsoCell::getHeatSourceTemperature(int x, int y, int z) {
  // TODO: Implement getHeatSourceTemperature
  return 0;
}

float IsoCell::getHeatSourceHighestTemperature(float surroundingAirTemperature,
                                               int x, int y, int z) {
  // TODO: Implement getHeatSourceHighestTemperature
  return 0;
}

void IsoCell::putInVehicle(IsoGameCharacter chr) {
  // TODO: Implement putInVehicle
}

void IsoCell::resumeVehicleSounds(IsoGameCharacter chr) {
  // TODO: Implement resumeVehicleSounds
}

void IsoCell::AddUniqueToBuildingList(ArrayList<IsoBuilding> arrayList,
                                      IsoBuilding building) {
  // TODO: Implement AddUniqueToBuildingList
}

IsoSpriteManager IsoCell::getSpriteManager() {
  // TODO: Implement getSpriteManager
  return nullptr;
}

void IsoCell::setSize(int w, int h) {
  // TODO: Implement setSize
}

public
IsoCell::SnowGrid(int arg1) {
  // TODO: Implement SnowGrid
  return nullptr;
}

bool IsoCell::check(int arg0, int arg1) {
  // TODO: Implement check
  return false;
}

bool IsoCell::checkAny(int arg0, int arg1) {
  // TODO: Implement checkAny
  return false;
}

void IsoCell::set(int arg0, int arg1, int arg2, IsoCell.SnowGridTiles arg3) {
  // TODO: Implement set
}

void IsoCell::subtract(IsoCell.SnowGrid arg0) {
  // TODO: Implement subtract
}

public
IsoCell::SnowGridTiles(uint8_t arg1) {
  // TODO: Implement SnowGridTiles
  return nullptr;
}

void IsoCell::add(Texture texture) {
  // TODO: Implement add
}

Texture IsoCell::getNext() {
  // TODO: Implement getNext
  return nullptr;
}

Texture IsoCell::get(int int0) {
  // TODO: Implement get
  return nullptr;
}

int IsoCell::size() {
  // TODO: Implement size
  return 0;
}

Texture IsoCell::getRand() {
  // TODO: Implement getRand
  return nullptr;
}

bool IsoCell::contains(Texture texture) {
  // TODO: Implement contains
  return false;
}

void IsoCell::resetCounter() {
  // TODO: Implement resetCounter
}

} // namespace iso
} // namespace zombie
