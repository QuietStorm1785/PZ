#include <stack>
#include <string>
#include <vector>
#include "zombie/iso/IsoCell.h"
#include "zombie/core/Rect.h"

namespace zombie {
namespace iso {


int IsoCell::getMaxHeight() {
    // Returns the maximum height of the cell (static field)
    return MaxHeight;
}


LotHeader IsoCell::getCurrentLotHeader() {
    // Returns the current lot header for the cell
    IsoChunk* chunk = getChunkForGridSquare((int)IsoCamera::CamCharacter.x, (int)IsoCamera::CamCharacter.y, (int)IsoCamera::CamCharacter.z);
    if (chunk) {
        return chunk->lotheader;
    }
    return nullptr;
}


IsoChunkMap* IsoCell::getChunkMap(int var1) {
    // Returns the chunk map for the given player index
    if (var1 >= 0 && var1 < 4) {
        return ChunkMap[var1].get();
    }
    return nullptr;
}


IsoGridSquare* IsoCell::getFreeTile(RoomDef var1) {
    // Returns a free tile in the given room
    stchoices.clear();
    for (size_t i = 0; i < var1.rects.size(); ++i) {
        RoomRect* rect = var1.rects[i];
        for (int x = rect->x; x < rect->x + rect->w; ++x) {
            for (int y = rect->y; y < rect->y + rect->h; ++y) {
                IsoGridSquare* sq = getGridSquare(x, y, var1.level);
                if (sq) stchoices.push_back(sq);
            }
        }
    }
    if (stchoices.empty()) return nullptr;
    IsoGridSquare* result = stchoices[Rand::Next(stchoices.size())];
    stchoices.clear();
    return result;
}


void IsoCell::setBuildings(std::stack<BuildingScore> var0) {
    // Sets the static buildingscores stack
    buildingscores = var0;
}


IsoZombie* IsoCell::getNearestVisibleZombie(int var1) {
    // Returns the nearest visible zombie for the given index
    if (var1 >= 0 && var1 < 4) {
        return nearestVisibleZombie[var1];
    }
    return nullptr;
}


IsoChunk* IsoCell::getChunkForGridSquare(int var1, int var2, int var3) {
    // Returns the chunk for the given grid square coordinates
    for (int i = 0; i < IsoPlayer::numPlayers; ++i) {
        if (!ChunkMap[i]->ignore) {
            int localX = var1 - ChunkMap[i]->getWorldXMinTiles();
            int localY = var2 - ChunkMap[i]->getWorldYMinTiles();
            if (localX >= 0 && localY >= 0) {
                IsoChunkMap* map = ChunkMap[i].get();
                localX /= 10;
                localY /= 10;
                IsoChunk* chunk = map->getChunk(localX, localY);
                if (chunk) return chunk;
            }
        }
    }
    return nullptr;
}


IsoChunk* IsoCell::getChunk(int var1, int var2) {
    // Returns the chunk for the given world coordinates
    for (int i = 0; i < IsoPlayer::numPlayers; ++i) {
        IsoChunkMap* map = ChunkMap[i].get();
        if (!map->ignore) {
            IsoChunk* chunk = map->getChunk(var1 - map->getWorldXMin(), var2 - map->getWorldYMin());
            if (chunk) return chunk;
        }
    }
    return nullptr;
}


IsoCell::IsoCell(int var1, int var2) {
    // Constructor for IsoCell
    IsoWorld::instance->CurrentCell = this;
    instance = this;
    width = var1;
    height = var2;
    for (int i = 0; i < 4; ++i) {
        ChunkMap[i] = std::make_shared<IsoChunkMap>(this);
        ChunkMap[i]->PlayerID = i;
        ChunkMap[i]->ignore = i > 0;
        playerOccluderBuildings.push_back(std::make_shared<std::vector<IsoBuilding*>>(5));
        zombieOccluderBuildings.push_back(std::make_shared<std::vector<IsoBuilding*>>(5));
        otherOccluderBuildings.push_back(std::make_shared<std::vector<IsoBuilding*>>(5));
    }
    WorldReuserThread::instance->run();
}


short IsoCell::getStencilValue(int var1, int var2, int var3) {
    // Returns the stencil value for the given coordinates
    auto& var4 = perPlayerRender[IsoCamera::frameState.playerIndex]->StencilValues;
    int var5 = 0, var6 = 0;
    for (size_t i = 0; i < sizeof(StencilXY)/sizeof(StencilXY[0]); i += 2) {
        int var8 = -var3 * 3;
        int var9 = var1 + var8 + StencilXY[i];
        int var10 = var2 + var8 + StencilXY[i + 1];
        if (var9 >= minX && var9 < maxX && var10 >= minY && var10 < maxY) {
            auto& var11 = var4[var9 - minX][var10 - minY];
            if (var11[0] != 0) {
                var5++;
                var6 += var11[0];
            }
        }
    }
    if (var5 == 0) return 1;
    return var5 > 10 ? (short)(var5 - 10) : (short)(var6 + 1);
}


void IsoCell::setStencilValue(int var1, int var2, int var3, int var4) {
    // Sets the stencil value for the given coordinates
    auto& var5 = perPlayerRender[IsoCamera::frameState.playerIndex]->StencilValues;
    for (size_t i = 0; i < sizeof(StencilXY)/sizeof(StencilXY[0]); i += 2) {
        int var7 = -var3 * 3;
        int var8 = var1 + var7 + StencilXY[i];
        int var9 = var2 + var7 + StencilXY[i + 1];
        if (var8 >= minX && var8 < maxX && var9 >= minY && var9 < maxY) {
            auto& var10 = var5[var8 - minX][var9 - minY];
            if (var10[0] == 0) {
                var10[0] = var4;
            } else {
                var10[0] = std::max(var10[0], (short)var4);
            }
        }
    }
}


short IsoCell::getStencilValue2z(int var1, int var2, int var3) {
    // Returns the stencil value for the given coordinates (2z variant)
    auto& var4 = perPlayerRender[IsoCamera::frameState.playerIndex]->StencilValues;
    int var5 = 0, var6 = 0, var7 = -var3 * 3;
    for (size_t i = 0; i < sizeof(StencilXY2z)/sizeof(StencilXY2z[0]); i += 2) {
        int var9 = var1 + var7 + StencilXY2z[i];
        int var10 = var2 + var7 + StencilXY2z[i + 1];
        if (var9 >= minX && var9 < maxX && var10 >= minY && var10 < maxY) {
            auto& var11 = var4[var9 - minX][var10 - minY];
            if (var11[0] != 0) {
                var5++;
                var6 += var11[0];
            }
        }
    }
    if (var5 == 0) return 1;
    return var5 > 10 ? (short)(var5 - 10) : (short)(var6 + 1);
}


void IsoCell::setStencilValue2z(int var1, int var2, int var3, int var4) {
    // Sets the stencil value for the given coordinates (2z variant)
    auto& var5 = perPlayerRender[IsoCamera::frameState.playerIndex]->StencilValues;
    int var6 = -var3 * 3;
    for (size_t i = 0; i < sizeof(StencilXY2z)/sizeof(StencilXY2z[0]); i += 2) {
        int var8 = var1 + var6 + StencilXY2z[i];
        int var9 = var2 + var6 + StencilXY2z[i + 1];
        if (var8 >= minX && var8 < maxX && var9 >= minY && var9 < maxY) {
            auto& var10 = var5[var8 - minX][var9 - minY];
            if (var10[0] == 0) {
                var10[0] = var4;
            } else {
                var10[0] = std::max(var10[0], (short)var4);
            }
        }
    }
}


void IsoCell::CalculateVertColoursForTile(IsoGridSquare var1, int var2, int var3, int var4, int var5) {
    // Compute neighbor squares for each corner based on vision matrix and nav array
    IsoGridSquare* var6 = !IsoGridSquare::getMatrixBit(var1.visionMatrix, 0, 0, 1) ? var1.nav[static_cast<int>(IsoDirections::NW)] : nullptr;
    IsoGridSquare* var7 = !IsoGridSquare::getMatrixBit(var1.visionMatrix, 1, 0, 1) ? var1.nav[static_cast<int>(IsoDirections::N)] : nullptr;
    IsoGridSquare* var8 = !IsoGridSquare::getMatrixBit(var1.visionMatrix, 2, 0, 1) ? var1.nav[static_cast<int>(IsoDirections::NE)] : nullptr;
    IsoGridSquare* var9 = !IsoGridSquare::getMatrixBit(var1.visionMatrix, 2, 1, 1) ? var1.nav[static_cast<int>(IsoDirections::E)] : nullptr;
    IsoGridSquare* var10 = !IsoGridSquare::getMatrixBit(var1.visionMatrix, 2, 2, 1) ? var1.nav[static_cast<int>(IsoDirections::SE)] : nullptr;
    IsoGridSquare* var11 = !IsoGridSquare::getMatrixBit(var1.visionMatrix, 1, 2, 1) ? var1.nav[static_cast<int>(IsoDirections::S)] : nullptr;
    IsoGridSquare* var12 = !IsoGridSquare::getMatrixBit(var1.visionMatrix, 0, 2, 1) ? var1.nav[static_cast<int>(IsoDirections::SW)] : nullptr;
    IsoGridSquare* var13 = !IsoGridSquare::getMatrixBit(var1.visionMatrix, 0, 1, 1) ? var1.nav[static_cast<int>(IsoDirections::W)] : nullptr;

    // Call CalculateColor for each corner
    this->CalculateColor(var6, var7, var13, &var1, 0, var5);
    this->CalculateColor(var7, var8, var9, &var1, 1, var5);
    this->CalculateColor(var10, var11, var9, &var1, 2, var5);
    this->CalculateColor(var12, var11, var13, &var1, 3, var5);
}


Texture* IsoCell::getStencilTexture() {
    // Returns the stencil texture, loading if necessary
    if (!m_stencilTexture) {
        m_stencilTexture = Texture::getSharedTexture("media/mask_circledithernew.png");
    }
    return m_stencilTexture;
}


void IsoCell::DrawStencilMask() {
    Texture* tex = getStencilTexture();
    if (tex) {
        IndieGL::glStencilMask(255);
        IndieGL::glClear(1280);
        int px = IsoCamera::getOffscreenWidth(IsoPlayer::getPlayerIndex()) / 2;
        int py = IsoCamera::getOffscreenHeight(IsoPlayer::getPlayerIndex()) / 2;
        px -= tex->getWidth() / (2 / Core::TileScale);
        py -= tex->getHeight() / (2 / Core::TileScale);
        IndieGL::enableStencilTest();
        IndieGL::enableAlphaTest();
        IndieGL::glAlphaFunc(516, 0.1f);
        IndieGL::glStencilFunc(519, 128, 255);
        IndieGL::glStencilOp(7680, 7680, 7681);
        IndieGL::glColorMask(false, false, false, false);
        tex->renderstrip(
            px - static_cast<int>(IsoCamera::getRightClickOffX()),
            py - static_cast<int>(IsoCamera::getRightClickOffY()),
            tex->getWidth() * Core::TileScale,
            tex->getHeight() * Core::TileScale,
            1.0f, 1.0f, 1.0f, 1.0f, nullptr
        );
        IndieGL::glColorMask(true, true, true, true);
        IndieGL::glStencilFunc(519, 0, 255);
        IndieGL::glStencilOp(7680, 7680, 7680);
        IndieGL::glStencilMask(127);
        IndieGL::glAlphaFunc(519, 0.0f);
        StencilX1 = px - static_cast<int>(IsoCamera::getRightClickOffX());
        StencilY1 = py - static_cast<int>(IsoCamera::getRightClickOffY());
        StencilX2 = StencilX1 + tex->getWidth() * Core::TileScale;
        StencilY2 = StencilY1 + tex->getHeight() * Core::TileScale;
    }
}


void IsoCell::RenderTiles(int var1) {
    // Calls the performance-measured renderTilesInternal
    s_performance.isoCellRenderTiles.invokeAndMeasure(this, var1, &IsoCell::renderTilesInternal);
}


void IsoCell::renderTilesInternal(int var1) {
    // Main tile rendering logic (adapted from legacy sources)
    if (DebugOptions::instance.Terrain.RenderTiles.Enable.getValue()) {
        if (!m_floorRenderShader) {
            RenderThread::invokeOnRenderContext([this]() { this->initTileShaders(); });
        }

        int playerIdx = IsoCamera::frameState.playerIndex;
        IsoPlayer* player = IsoPlayer::players[playerIdx];
        player->dirtyRecalcGridStackTime -= GameTime::getInstance()->getMultiplier() / 4.0f;
        PerPlayerRender* ppr = this->getPerPlayerRenderAt(playerIdx);
        ppr->setSize(this->maxX - this->minX + 1, this->maxY - this->minY + 1);
        long now = /* System.currentTimeMillis() or similar */ 0;
        if (this->minX != ppr->minX || this->minY != ppr->minY || this->maxX != ppr->maxX || this->maxY != ppr->maxY) {
            ppr->minX = this->minX;
            ppr->minY = this->minY;
            ppr->maxX = this->maxX;
            ppr->maxY = this->maxY;
            player->dirtyRecalcGridStack = true;
            // WeatherFxMask::forceMaskUpdate(playerIdx); // If available
#ifdef HAS_WEATHERFXMASK
            WeatherFxMask::forceMaskUpdate(playerIdx);
#endif
        }

        // renderTiles.recalculateAnyGridStacks.start();
        bool wasDirty = player->dirtyRecalcGridStack;
        this->recalculateAnyGridStacks(*ppr, var1, playerIdx, now);
        // renderTiles.recalculateAnyGridStacks.end();
        this->DeferredCharacterTick++;
        // renderTiles.flattenAnyFoliage.start();
        this->flattenAnyFoliage(*ppr, playerIdx);
        // renderTiles.flattenAnyFoliage.end();
        if (this->SetCutawayRoomsForPlayer() || wasDirty) {
            auto& gridStacks = ppr->GridStacks;
            int playerIdx = IsoCamera::frameState.playerIndex;
            for (size_t i = 0; i < gridStacks->Squares.size() && i < static_cast<size_t>(var1 + 1); ++i) {
                auto& gridStack = gridStacks->Squares[i];
                for (auto& sq : gridStack) {
                    if (sq) {
                        sq->setPlayerCutawayFlag(playerIdx, this->IsCutawaySquare(sq, now), now);
                    }
                }
            }
        }
        }

        // renderTiles.performRenderTiles.start();
        this->performRenderTiles(*ppr, var1, playerIdx, now);
        // renderTiles.performRenderTiles.end();
        this->playerCutawaysDirty[playerIdx] = false;
        ShadowSquares.clear();
        MinusFloorCharacters.clear();
        ShadedFloor.clear();
        SolidFloor.clear();
        VegetationCorpses.clear();
        // renderTiles.renderDebugPhysics.start();
        this->renderDebugPhysics(playerIdx);
        // renderTiles.renderDebugPhysics.end();
        // renderTiles.renderDebugLighting.start();
        this->renderDebugLighting(*ppr, var1);
        // renderTiles.renderDebugLighting.end();
    }
}


void IsoCell::initTileShaders() {
    // Initialize tile shaders for floor and wall rendering
    // (matches legacy logic from DoNotUse/include/zombie/iso/IsoCell.cpp)
    m_floorRenderShader = Shader("floorTile");
    m_wallRenderShader = Shader("wallTile");
}


PerPlayerRender* IsoCell::getPerPlayerRenderAt(int var1) {
    // Returns the PerPlayerRender for the given player index, creating if necessary
    if (!perPlayerRender[var1]) {
        perPlayerRender[var1] = std::make_unique<PerPlayerRender>();
    }
    return perPlayerRender[var1].get();
}

void IsoCell::recalculateAnyGridStacks(PerPlayerRender var1, int var2, int var3, long var4) {
    // Ported from legacy Java/C++ sources, adapted for C++ idioms and merged PerPlayerRender/IsoGridStack
    // Only recalculate if the player has dirtyRecalcGridStack set
    IsoPlayer* player = IsoPlayer::players[var3];
    if (!player || !player->dirtyRecalcGridStack) return;
    player->dirtyRecalcGridStack = false;

    // Unpack PerPlayerRender and IsoGridStack
    auto& gridStacksPtr = var1.GridStacks;
    if (!gridStacksPtr) return;
    auto& gridStacks = gridStacksPtr->Squares;
    auto& visiOccluded = var1.VisiOccludedFlags;
    auto& visiCulled = var1.VisiCulledFlags;

    int chunkX = -1, chunkY = -1, maxLevel = -1;
    // WeatherFxMask::setDiamondIterDone(var3); // If available
#ifdef HAS_WEATHERFXMASK
    WeatherFxMask::setDiamondIterDone(var3);
#endif

    // For each Z level (floor), from top to bottom
    for (int z = var2; z >= 0; --z) {
        if (z >= static_cast<int>(gridStacks.size())) continue;
        auto& gridStack = gridStacks[z];
        gridStack.clear();
        if (z < this->maxZ) {
            // Use diamond matrix iterator if enabled, else fallback to classic
            if (DebugOptions::instance.Terrain.RenderTiles.NewRender.getValue()) {
                // Diamond matrix iterator logic (ported from legacy Java/C++)
                // Assume diamondMatrixIterator and diamondMatrixPos are available as members
                auto& diamondMatrixIterator = this->diamondMatrixIterator;
                auto& diamondMatrixPos = this->diamondMatrixPos;
                diamondMatrixIterator.reset(this->maxX - this->minX);
                while (diamondMatrixIterator.next(diamondMatrixPos)) {
                    if (diamondMatrixPos.y < this->maxY - this->minY + 1) {
                        IsoGridSquare* sq = this->ChunkMap[var3]->getGridSquare(diamondMatrixPos.x + this->minX, diamondMatrixPos.y + this->minY, z);
                        if (z == 0) {
                            int xx = diamondMatrixPos.x, yy = diamondMatrixPos.y;
                            if (xx >= 0 && yy >= 0 && xx < static_cast<int>(visiOccluded.size()) && yy < static_cast<int>(visiOccluded[xx].size())) {
                                visiOccluded[xx][yy][0] = false;
                                visiOccluded[xx][yy][1] = false;
                                visiCulled[xx][yy] = false;
                            }
                        }
                        if (!sq) {
#ifdef HAS_WEATHERFXMASK
                            WeatherFxMask::addMaskLocation(nullptr, diamondMatrixPos.x + this->minX, diamondMatrixPos.y + this->minY, z);
#endif
                            continue;
                        }
                        IsoChunk* chunk = sq->getChunk();
                        if (chunk && sq->IsOnScreen(true)) {
#ifdef HAS_WEATHERFXMASK
                            WeatherFxMask::addMaskLocation(sq, diamondMatrixPos.x + this->minX, diamondMatrixPos.y + this->minY, z);
#endif
                            bool dissolved = this->IsDissolvedSquare(sq, var3);
                            sq->setIsDissolved(var3, dissolved, var4);
                            if (!sq->getIsDissolved(var3, var4)) {
                                sq->cacheLightInfo();
                                gridStack.push_back(sq);
                            }
                        }
                    }
                }
            } else {
                // Classic iteration: scan all X/Y in visible bounds
                for (int y = this->minY; y < this->maxY; ++y) {
                    for (int x = this->minX; x < this->maxX; ++x) {
                        // Reset occlusion/culling flags for ground floor
                        if (z == 0) {
                            int xx = x - this->minX, yy = y - this->minY;
                            if (xx >= 0 && yy >= 0 && xx < static_cast<int>(visiOccluded.size()) && yy < static_cast<int>(visiOccluded[xx].size())) {
                                visiOccluded[xx][yy][0] = false;
                                visiOccluded[xx][yy][1] = false;
                                visiCulled[xx][yy] = false;
                            }
                        }
                        // Get the grid square for this position and level
                        IsoGridSquare* sq = this->getGridSquare(x, y, z);
                        if (!sq) continue;
                        // Only add squares that are on screen and not dissolved
                        if (sq->IsOnScreen(true)) {
                            bool dissolved = this->IsDissolvedSquare(sq, var3);
                            sq->setIsDissolved(var3, dissolved, var4);
                            if (!sq->getIsDissolved(var3, var4)) {
                                sq->cacheLightInfo();
                                gridStack.push_back(sq);
                            }
                        }
                    }
                }
            }
        }
    }
    // Cull fully occluded squares after grid stack build
    this->CullFullyOccludedSquares(*gridStacksPtr, visiOccluded, visiCulled);
}

void IsoCell::flattenAnyFoliage(PerPlayerRender var1, int var2) {
    // Ported from legacy Java/C++ sources
    // Reset stencil and flatten arrays
    auto& stencil = var1.StencilValues;
    auto& flatten = var1.FlattenGrassEtc;
    int w = static_cast<int>(stencil.size());
    int h = w > 0 ? static_cast<int>(stencil[0].size()) : 0;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            stencil[x][y][0] = 0;
            stencil[x][y][1] = 0;
            flatten[x][y] = false;
        }
    }

    // Mark areas under vehicles as flattened
    for (auto& vehicle : this->vehicles) {
        if (!vehicle) continue;
        if (vehicle->getAlpha(var2) <= 0.0f) continue;
        int vx = static_cast<int>(vehicle->x);
        int vy = static_cast<int>(vehicle->y);
        for (int dy = -2; dy < 5; ++dy) {
            for (int dx = -2; dx < 5; ++dx) {
                int px = vx + dx - this->minX;
                int py = vy + dy - this->minY;
                if (px >= 0 && px < w && py >= 0 && py < h) {
                    flatten[px][py] = true;
                }
            }
        }
    }
}

void IsoCell::performRenderTiles(PerPlayerRender var1, int var2, int var3, long var4) {
    // Ported from legacy Java/C++ sources, adapted for C++ idioms and merged PerPlayerRender/IsoGridStack
    // var1: PerPlayerRender for the player
    // var2: Z level (floor)
    // var3: player index
    // var4: current time (ms)

    if (!var1.GridStacks) return;
    auto& gridStacks = var1.GridStacks->Squares;
    if (var2 < 0 || var2 >= static_cast<int>(gridStacks.size())) return;
    auto& gridStack = gridStacks[var2];

    // Iterate over all IsoGridSquares in the grid stack for this Z level
    for (auto* sq : gridStack) {
        if (!sq) continue;
        // Only render squares that are on screen and not dissolved
        if (!sq->IsOnScreen(true)) continue;
        if (this->IsDissolvedSquare(sq, var3)) continue;

        // Handle cutaway/cutaway flag logic if needed
        // (If SetCutawayRoomsForPlayer or playerCutawaysDirty is true, update cutaway flags)
        // This is handled in renderTilesInternal before this call, so we just render here

        // Render the grid square (main tile rendering logic)
        sq->render(var3, var2, var4);
    }
    // Additional per-tile or per-stack logic can be added here if needed
}

void IsoCell::renderShadows() {
    // Ported from legacy Java/C++ sources, adapted for C++ idioms and merged PerPlayerRender/IsoGridStack
    // Iterate over all players' PerPlayerRender grid stacks and render shadows for each square
    for (int playerIdx = 0; playerIdx < IsoPlayer::numPlayers; ++playerIdx) {
        PerPlayerRender* ppr = this->getPerPlayerRenderAt(playerIdx);
        if (!ppr || !ppr->GridStacks) continue;
        auto& gridStacks = ppr->GridStacks->Squares;
        for (size_t z = 0; z < gridStacks.size(); ++z) {
            auto& gridStack = gridStacks[z];
            for (auto* sq : gridStack) {
                if (!sq) continue;
                if (!sq->IsOnScreen(true)) continue;
                if (this->IsDissolvedSquare(sq, playerIdx)) continue;
                // Render shadow for this grid square
                sq->renderShadow(playerIdx, static_cast<int>(z));
            }
        }
    }
}

void IsoCell::renderDebugPhysics(int var1) {
    // Ported from legacy Java/C++ sources, adapted for C++ idioms and merged PerPlayerRender/IsoGridStack
    // var1: player index
    PerPlayerRender* ppr = this->getPerPlayerRenderAt(var1);
    if (!ppr || !ppr->GridStacks) return;
    auto& gridStacks = ppr->GridStacks->Squares;
    for (size_t z = 0; z < gridStacks.size(); ++z) {
        auto& gridStack = gridStacks[z];
        for (auto* sq : gridStack) {
            if (!sq) continue;
            if (!sq->IsOnScreen(true)) continue;
            if (this->IsDissolvedSquare(sq, var1)) continue;
            // Render debug physics overlay for this grid square
            sq->renderDebugPhysics(var1, static_cast<int>(z));
        }
    }
}

void IsoCell::renderDebugLighting(PerPlayerRender var1, int var2) {
    // Ported from legacy Java/C++ sources
    // var1: PerPlayerRender for the player
    // var2: Z level (floor)
    if (!var1.GridStacks) return;
    auto& gridStacks = var1.GridStacks->Squares;
    if (var2 < 0 || var2 >= static_cast<int>(gridStacks.size())) return;
    auto& gridStack = gridStacks[var2];
    for (auto* sq : gridStack) {
        if (!sq) continue;
        if (!sq->IsOnScreen(true)) continue;
        if (this->IsDissolvedSquare(sq, IsoCamera::frameState.playerIndex)) continue;
        sq->renderDebugLighting(IsoCamera::frameState.playerIndex, var2);
    }
}

void IsoCell::CullFullyOccludedSquares(IsoGridStack var1, boolean[][][] var2, boolean[][] var3) {
    // Ported from legacy Java/C++ sources
    // var1: IsoGridStack (grid stack for player)
    // var2: VisiOccludedFlags
    // var3: VisiCulledFlags
    // This method culls fully occluded squares from the grid stack
    // For each Z level, remove squares that are fully occluded
    for (size_t z = 0; z < var1.Squares.size(); ++z) {
        auto& gridStack = var1.Squares[z];
        gridStack.erase(
            std::remove_if(gridStack.begin(), gridStack.end(), [&](IsoGridSquare* sq) {
                if (!sq) return true;
                int x = sq->getX();
                int y = sq->getY();
                if (z < var2.size() && x < var2[z].size() && y < var2[z][x].size()) {
                    return var2[z][x][y];
                }
                return false;
            }),
            gridStack.end()
        );
    }
}

void IsoCell::RenderFloorShading(int var1) {
    // Ported from legacy Java/C++ sources
    // var1: player index
    PerPlayerRender* ppr = this->getPerPlayerRenderAt(var1);
    if (!ppr || !ppr->GridStacks) return;
    auto& gridStacks = ppr->GridStacks->Squares;
    for (size_t z = 0; z < gridStacks.size(); ++z) {
        auto& gridStack = gridStacks[z];
        for (auto* sq : gridStack) {
            if (!sq) continue;
            if (!sq->IsOnScreen(true)) continue;
            if (this->IsDissolvedSquare(sq, var1)) continue;
            sq->renderFloorShading(var1, static_cast<int>(z));
        }
    }
}

bool IsoCell::IsPlayerWindowPeeking(int var1) {
    // Ported from legacy Java/C++ sources
    // var1: player index
    // This is a stub; actual logic may depend on player state
    return false;
}

bool IsoCell::CanBuildingSquareOccludePlayer(IsoGridSquare var1, int var2) {
    // Ported from legacy Java/C++ sources
    // var1: IsoGridSquare
    // var2: player index
    // This is a stub; actual logic may depend on building/occlusion state
    return false;
}

int IsoCell::GetEffectivePlayerRoomId() {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on player/room state
    return 0;
}

bool IsoCell::SetCutawayRoomsForPlayer() {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on cutaway room state
    return false;
}

bool IsoCell::IsCutawaySquare(IsoGridSquare var1, long var2) {
    // Ported from legacy Java/C++ sources
    // var1: IsoGridSquare
    // var2: flags
    // This is a stub; actual logic may depend on cutaway flags
    return false;
}

bool IsoCell::DoesSquareHaveValidCutaways(IsoGridSquare var1, IsoGridSquare var2, int var3, long var4) {
    // Ported from legacy Java/C++ sources
    // var1: IsoGridSquare
    // var2: neighbor IsoGridSquare
    // var3: player index
    // var4: flags
    // This is a stub; actual logic may depend on cutaway validation
    return false;
}

bool IsoCell::IsCollapsibleBuildingSquare(IsoGridSquare var1) {
    // Ported from legacy Java/C++ sources
    // var1: IsoGridSquare
    // This is a stub; actual logic may depend on building collapse state
    return false;
}

bool IsoCell::collapsibleBuildingSquareAlgorithm(BuildingDef var1, IsoGridSquare var2, IsoGridSquare var3) {
    // Ported from legacy Java/C++ sources
    // var1: BuildingDef
    // var2: IsoGridSquare
    // var3: neighbor IsoGridSquare
    // This is a stub; actual logic may depend on building collapse algorithm
    return false;
}

bool IsoCell::IsDissolvedSquare(IsoGridSquare var1, int var2) {
    // Ported from legacy Java/C++ sources
    // var1: IsoGridSquare
    // var2: player index
    // This is a stub; actual logic may depend on dissolve state
    return false;
}

int IsoCell::GetBuildingHeightAt(IsoBuilding var1, int var2, int var3, int var4) {
    // Ported from legacy Java/C++ sources
    // var1: IsoBuilding
    // var2, var3, var4: coordinates
    // This is a stub; actual logic may depend on building height
    return 0;
}

void IsoCell::updateSnow(int var1) {
    // Ported from legacy Java/C++ sources
    // var1: player index
    // This is a stub; actual logic may depend on snow system
    // (Update snow grid, snow melt, etc.)
}

void IsoCell::setSnowTarget(int var1) {
    // Ported from legacy Java/C++ sources
    // var1: player index
    // This is a stub; actual logic may depend on snow system
}

bool IsoCell::gridSquareIsSnow(int var1, int var2, int var3) {
    // Ported from legacy Java/C++ sources
    // var1, var2, var3: coordinates
    // This is a stub; actual logic may depend on snow grid
    return false;
}

void IsoCell::RenderSnow(int var1) {
    // Ported from legacy Java/C++ sources
    // var1: player index
    // This is a stub; actual logic may depend on snow rendering system
}

void IsoCell::renderSnowTileGeneral(SnowGrid var1, float var2, IsoGridSquare var3, int var4, int var5, int var6, int var7, int var8, int var9) {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on snow rendering system
}

void IsoCell::renderSnowTileBase(Texture var1, int var2, int var3, float var4, bool var5) {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on snow rendering system
}

void IsoCell::renderSnowTile(SnowGrid var1, int var2, int var3, int var4, IsoGridSquare var5, int var6, Texture var7, int var8, int var9, float var10) {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on snow rendering system
}

int IsoCell::getShoreInt(IsoGridSquare var0) {
    // Ported from legacy Java/C++ sources
    // var0: IsoGridSquare
    // This is a stub; actual logic may depend on shore detection
    return 0;
}

bool IsoCell::isSnowShore(IsoGridSquare var0, int var1, int var2) {
    // Ported from legacy Java/C++ sources
    // var0: IsoGridSquare
    // var1, var2: coordinates
    // This is a stub; actual logic may depend on snow/shore detection
    return false;
}

IsoBuilding IsoCell::getClosestBuildingExcept(IsoGameCharacter var1, IsoRoom var2) {
    // Ported from legacy Java/C++ sources
    // var1: IsoGameCharacter
    // var2: IsoRoom
    // This is a stub; actual logic may depend on building proximity
    return nullptr;
}

int IsoCell::getDangerScore(int var1, int var2) {
    // Ported from legacy Java/C++ sources
    // var1, var2: coordinates
    // This is a stub; actual logic may depend on danger scoring system
    return 0;
}


void IsoCell::ObjectDeletionAddition() {
    // Ported from legacy C++/Java sources
    // Remove objects in removeList
    for (auto* obj : removeList) {
        // Remove from ObjectList
        auto it = std::find(ObjectList.begin(), ObjectList.end(), obj);
        if (it != ObjectList.end()) ObjectList.erase(it);
        // Remove from current and last square
        if (obj && obj->getCurrentSquare()) {
            auto& mos = obj->getCurrentSquare()->getMovingObjects();
            mos.erase(std::remove(mos.begin(), mos.end(), obj), mos.end());
        }
        if (obj && obj->getLastSquare()) {
            auto& mos = obj->getLastSquare()->getMovingObjects();
            mos.erase(std::remove(mos.begin(), mos.end(), obj), mos.end());
        }
        // Remove from VirtualZombieManager if zombie
        if (auto* zombie = dynamic_cast<IsoZombie*>(obj)) {
            VirtualZombieManager::getInstance().RemoveZombie(zombie);
        }
        // Remove from MovingObjectUpdateScheduler
        zombie::MovingObjectUpdateScheduler::removeObject(obj);
    }
    removeList.clear();
    // Add objects in addList
    for (auto* obj : addList) {
        if (std::find(ObjectList.begin(), ObjectList.end(), obj) == ObjectList.end()) {
            ObjectList.push_back(obj);
        }
    }
    addList.clear();
    // Add vehicles in addVehicles
    for (auto* v : addVehicles) {
        if (std::find(ObjectList.begin(), ObjectList.end(), v) == ObjectList.end()) {
            ObjectList.push_back(v);
        }
        if (std::find(vehicles.begin(), vehicles.end(), v) == vehicles.end()) {
            vehicles.push_back(v);
        }
    }
    addVehicles.clear();
}


void IsoCell::ProcessItems() {
    // Ported from legacy C++/Java sources
    // Update all ProcessItems
    for (auto* item : ProcessItems) {
        if (item) {
            item->update();
            if (item->finishupdate()) {
                ProcessItemsRemove.push_back(item);
            }
        }
    }
    // Update all ProcessWorldItems
    for (auto* witem : ProcessWorldItems) {
        if (witem) {
            witem->update();
            if (witem->finishupdate()) {
                ProcessWorldItemsRemove.push_back(witem);
            }
        }
    }
}


void IsoCell::ProcessIsoObject() {
    // Ported from legacy C++/Java sources
    // Remove all objects marked for removal
    for (auto* obj : ProcessIsoObjectRemove) {
        auto it = std::find(ProcessIsoObject.begin(), ProcessIsoObject.end(), obj);
        if (it != ProcessIsoObject.end()) ProcessIsoObject.erase(it);
    }
    ProcessIsoObjectRemove.clear();
    // Update all ProcessIsoObject
    for (auto* obj : ProcessIsoObject) {
        if (obj) obj->update();
    }
}


void IsoCell::ProcessObjects() {
    // Ported from legacy C++/Java sources
    // Update all moving objects (MovingObjectUpdateScheduler)
    zombie::MovingObjectUpdateScheduler::update();

    // Update all zombies' vocal properties
    for (auto* zombie : ZombieList) {
        if (zombie) zombie->updateVocalProperties();
    }
}


void IsoCell::ProcessRemoveItems() {
    // Ported from legacy C++/Java sources
    // Remove items marked for removal
    for (auto* item : ProcessItemsRemove) {
        auto it = std::find(ProcessItems.begin(), ProcessItems.end(), item);
        if (it != ProcessItems.end()) ProcessItems.erase(it);
    }
    for (auto* witem : ProcessWorldItemsRemove) {
        auto it = std::find(ProcessWorldItems.begin(), ProcessWorldItems.end(), witem);
        if (it != ProcessWorldItems.end()) ProcessWorldItems.erase(it);
    }
    ProcessItemsRemove.clear();
    ProcessWorldItemsRemove.clear();
}


void IsoCell::ProcessStaticUpdaters() {
    // Ported from legacy C++/Java sources
    for (auto* obj : StaticUpdaterObjectList) {
        if (obj) obj->update();
    }
}


void IsoCell::addToProcessIsoObject(IsoObject* obj) {
    if (!obj) return;
    auto it = std::find(ProcessIsoObjectRemove.begin(), ProcessIsoObjectRemove.end(), obj);
    if (it != ProcessIsoObjectRemove.end()) ProcessIsoObjectRemove.erase(it);
    if (std::find(ProcessIsoObject.begin(), ProcessIsoObject.end(), obj) == ProcessIsoObject.end()) {
        ProcessIsoObject.push_back(obj);
    }
}


void IsoCell::addToProcessIsoObjectRemove(IsoObject* obj) {
    if (!obj) return;
    if (std::find(ProcessIsoObject.begin(), ProcessIsoObject.end(), obj) != ProcessIsoObject.end()) {
        if (std::find(ProcessIsoObjectRemove.begin(), ProcessIsoObjectRemove.end(), obj) == ProcessIsoObjectRemove.end()) {
            ProcessIsoObjectRemove.push_back(obj);
        }
    }
}


void IsoCell::addToStaticUpdaterObjectList(IsoObject* obj) {
    if (!obj) return;
    if (std::find(StaticUpdaterObjectList.begin(), StaticUpdaterObjectList.end(), obj) == StaticUpdaterObjectList.end()) {
        StaticUpdaterObjectList.push_back(obj);
    }
}


void IsoCell::addToProcessItems(InventoryItem* item) {
    if (!item) return;
    auto it = std::find(ProcessItemsRemove.begin(), ProcessItemsRemove.end(), item);
    if (it != ProcessItemsRemove.end()) ProcessItemsRemove.erase(it);
    if (std::find(ProcessItems.begin(), ProcessItems.end(), item) == ProcessItems.end()) {
        ProcessItems.push_back(item);
    }
}


void IsoCell::addToProcessItems(const std::vector<InventoryItem*>& items) {
    for (auto* item : items) {
        if (!item) continue;
        auto it = std::find(ProcessItemsRemove.begin(), ProcessItemsRemove.end(), item);
        if (it != ProcessItemsRemove.end()) ProcessItemsRemove.erase(it);
        if (std::find(ProcessItems.begin(), ProcessItems.end(), item) == ProcessItems.end()) {
            ProcessItems.push_back(item);
        }
    }
}


void IsoCell::addToProcessItemsRemove(InventoryItem* item) {
    if (!item) return;
    if (std::find(ProcessItemsRemove.begin(), ProcessItemsRemove.end(), item) == ProcessItemsRemove.end()) {
        ProcessItemsRemove.push_back(item);
    }
}


void IsoCell::addToProcessItemsRemove(const std::vector<InventoryItem*>& items) {
    for (auto* item : items) {
        if (!item) continue;
        if (std::find(ProcessItemsRemove.begin(), ProcessItemsRemove.end(), item) == ProcessItemsRemove.end()) {
            ProcessItemsRemove.push_back(item);
        }
    }
}


void IsoCell::addToProcessWorldItems(IsoWorldInventoryObject* obj) {
    if (!obj) return;
    auto it = std::find(ProcessWorldItemsRemove.begin(), ProcessWorldItemsRemove.end(), obj);
    if (it != ProcessWorldItemsRemove.end()) ProcessWorldItemsRemove.erase(it);
    if (std::find(ProcessWorldItems.begin(), ProcessWorldItems.end(), obj) == ProcessWorldItems.end()) {
        ProcessWorldItems.push_back(obj);
    }
}


void IsoCell::addToProcessWorldItemsRemove(IsoWorldInventoryObject* obj) {
    if (!obj) return;
    if (std::find(ProcessWorldItemsRemove.begin(), ProcessWorldItemsRemove.end(), obj) == ProcessWorldItemsRemove.end()) {
        ProcessWorldItemsRemove.push_back(obj);
    }
}

IsoSurvivor IsoCell::getNetworkPlayer(int var1) {
    // Placeholder: Return nullptr or lookup network player by index if available
    // (Legacy logic would search a player/network list)
    return nullptr;
}

IsoGridSquare IsoCell::ConnectNewSquare(IsoGridSquare var1, bool var2, bool var3) {
    // Placeholder: Connect a new grid square to the cell, with options for diagonal/adjacency
    // (Legacy logic would allocate and link a new IsoGridSquare)
    return nullptr;
}

void IsoCell::DoGridNav(IsoGridSquare var1, GetSquare var2) {
    // Placeholder: Implement grid navigation logic
    // (Legacy logic would perform a navigation or pathfinding step)
}

IsoGridSquare IsoCell::ConnectNewSquare(IsoGridSquare var1, bool var2) {
    // Placeholder: Connect a new grid square to the cell, with adjacency only
    // (Legacy logic would allocate and link a new IsoGridSquare)
    return nullptr;
}

void IsoCell::PlaceLot(const std::string& var1, int var2, int var3, int var4, bool var5) {
    // Placeholder: Place a lot by name at the given coordinates
    // (Legacy logic would load and instantiate a lot definition)
}

void IsoCell::PlaceLot(IsoLot var1, int var2, int var3, int var4, bool var5) {
    // Placeholder: Place a lot object at the given coordinates
    // (Legacy logic would instantiate the lot in the world)
}

void IsoCell::PlaceLot(IsoLot var1, int var2, int var3, int var4, IsoChunk var5, int var6, int var7) {
    // Placeholder: Place a lot object at the given coordinates in a specific chunk
    // (Legacy logic would instantiate the lot in the chunk)
}


// Use Lua 5.4.7: Store drag tables as Lua references in a per-player array
#include <lua.hpp>

// Assume: std::vector<int> dragRefs; // Lua registry references, one per player
//         lua_State* L; // The main Lua state for the cell

void IsoCell::setDrag(lua_State* L, int playerIdx) {
    // Pops a table from the top of the stack and stores a reference in dragRefs[playerIdx]
    if ((int)dragRefs.size() <= playerIdx) dragRefs.resize(playerIdx + 1, LUA_NOREF);
    if (dragRefs[playerIdx] != LUA_NOREF) {
        luaL_unref(L, LUA_REGISTRYINDEX, dragRefs[playerIdx]);
    }
    dragRefs[playerIdx] = luaL_ref(L, LUA_REGISTRYINDEX);
}


// Returns the drag table for the given player index (pushes it onto the Lua stack)
// Returns true if found, false if not
bool IsoCell::getDrag(lua_State* L, int playerIdx) {
    if ((int)dragRefs.size() <= playerIdx || dragRefs[playerIdx] == LUA_NOREF) {
        lua_pushnil(L);
        return false;
    }
    lua_rawgeti(L, LUA_REGISTRYINDEX, dragRefs[playerIdx]);
    return true;
}

bool IsoCell::DoBuilding(int var1, bool var2) {
    // Placeholder: Implement building logic for player var1, flag var2
    // (Legacy logic would handle player building actions)
    return false;
}

bool IsoCell::doBuildingInternal(int var1, bool var2) {
    // Placeholder: Internal building logic for player var1, flag var2
    // (Legacy logic would handle internal building state)
    return false;
}

float IsoCell::DistanceFromSupport(int var1, int var2, int var3) {
    // Placeholder: Calculate distance from support at (var1, var2, var3)
    // (Legacy logic would compute structural support distance)
    return 0.0f;
}


void IsoCell::addToWindowList(IsoWindow* window) {
    if (!window) return;
    if (std::find(WindowList.begin(), WindowList.end(), window) == WindowList.end()) {
        WindowList.push_back(window);
    }
}


void IsoCell::removeFromWindowList(IsoWindow* window) {
    if (!window) return;
    auto it = std::find(WindowList.begin(), WindowList.end(), window);
    if (it != WindowList.end()) WindowList.erase(it);
}

IsoRoom IsoCell::getRoom(int var1) {
    // Placeholder: Return the room at index var1 if available
    // (Legacy logic would look up a room by index)
    return nullptr;
}

void IsoCell::addMovingObject(IsoMovingObject* obj) {
    if (!obj) return;
    if (std::find(ObjectList.begin(), ObjectList.end(), obj) == ObjectList.end()) {
        ObjectList.push_back(obj);
    }
}

int IsoCell::getHeight() {
    return height;
}

void IsoCell::setHeight(int h) {
    height = h;
}

int IsoCell::getWidth() {
    return width;
}

void IsoCell::setWidth(int w) {
    width = w;
}

int IsoCell::getWorldX() {
    return worldX;
}

void IsoCell::setWorldX(int x) {
    worldX = x;
}

int IsoCell::getWorldY() {
    return worldY;
}

void IsoCell::setWorldY(int y) {
    worldY = y;
}

bool IsoCell::isSafeToAdd() {
    return safeToAdd;
}

void IsoCell::setSafeToAdd(bool b) {
    safeToAdd = b;
}

int IsoCell::getMinX() {
    return minX;
}

void IsoCell::setMinX(int var1) {
    minX = var1;
}

int IsoCell::getMaxX() {
    return maxX;
}

void IsoCell::setMaxX(int var1) {
    maxX = var1;
}

int IsoCell::getMinY() {
    return minY;
}

void IsoCell::setMinY(int var1) {
    minY = var1;
}

int IsoCell::getMaxY() {
    return maxY;
}

void IsoCell::setMaxY(int var1) {
    maxY = var1;
}

int IsoCell::getMinZ() {
    return minZ;
}

void IsoCell::setMinZ(int var1) {
    minZ = var1;
}

int IsoCell::getMaxZ() {
    return maxZ;
}

void IsoCell::setMaxZ(int var1) {
    maxZ = var1;
}

OnceEvery IsoCell::getDangerUpdate() {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on danger update system
    return OnceEvery();
}

void IsoCell::setDangerUpdate(OnceEvery var1) {
    // Ported from legacy Java/C++ sources
    // Sets the dangerUpdate timer
    dangerUpdate = var1;
}

Thread IsoCell::getLightInfoUpdate() {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on light info update system
    return Thread();
}

void IsoCell::setLightInfoUpdate(Thread var1) {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on light info update system
}

int IsoCell::getRComponent(int var0) {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on color component
    return 0;
}

int IsoCell::getGComponent(int var0) {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on color component
    return 0;
}

int IsoCell::getBComponent(int var0) {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on color component
    return 0;
}

int IsoCell::toIntColor(float var0, float var1, float var2, float var3) {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on color conversion
    return 0;
}

IsoGridSquare IsoCell::getRandomOutdoorTile() {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on outdoor tile selection
    return nullptr;
}

void IsoCell::InsertAt(int var0, BuildingScore var1, BuildingScore[] var2) {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on insert at system
}

void IsoCell::Place(BuildingScore var0, BuildingScore[] var1, BuildingSearchCriteria var2) {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on place system
}

bool IsoCell::blocked(Mover var1, int var2, int var3, int var4, int var5, int var6, int var7) {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on blocked state
    return false;
}

void IsoCell::Dispose() {
    // Ported from legacy Java/C++ sources
    // This is a stub; actual logic may depend on dispose system
}


IsoGridSquare* IsoCell::getGridSquare(double var1, double var2, double var3) {
    // Placeholder: Implement grid square lookup by double coordinates
    return nullptr;
}


IsoGridSquare* IsoCell::getOrCreateGridSquare(double var1, double var2, double var3) {
    // Placeholder: Implement grid square creation by double coordinates
    return nullptr;
}


void IsoCell::setCacheGridSquare(int var1, int var2, int var3, IsoGridSquare* var4) {
    // Placeholder: Implement cache set for grid square
}


void IsoCell::setCacheChunk(IsoChunk* var1) {
    // Placeholder: Implement cache set for chunk
}


void IsoCell::setCacheChunk(IsoChunk* var1, int var2) {
    // Placeholder: Implement cache set for chunk with index
}


void IsoCell::clearCacheGridSquare(int var1) {
    // Placeholder: Implement cache clear for grid square
}


void IsoCell::setCacheGridSquareLocal(int var1, int var2, int var3, IsoGridSquare* var4, int var5) {
    // Placeholder: Implement local cache set for grid square
}

IsoGridSquare IsoCell::getGridSquare(double var1, double var2, double var3) {
    // TODO: Implement getGridSquare
    return nullptr;
}


// Returns the grid square at (x, y, z) if it exists, or nullptr if out of bounds
IsoGridSquare* IsoCell::getGridSquare(int x, int y, int z) {
    if (x < minX || x > maxX || y < minY || y > maxY || z < minZ || z > maxZ)
        return nullptr;
    // Assume gridSquares is a 3D vector or similar structure: gridSquares[z][x][y]
    // Adjust indices if minX/minY/minZ are not zero
    int localX = x - minX;
    int localY = y - minY;
    int localZ = z - minZ;
    if (localZ < 0 || localZ >= (int)gridSquares.size()) return nullptr;
    auto& plane = gridSquares[localZ];
    if (localX < 0 || localX >= (int)plane.size()) return nullptr;
    auto& row = plane[localX];
    if (localY < 0 || localY >= (int)row.size()) return nullptr;
    return row[localY];
}


void IsoCell::EnsureSurroundNotNull(int var1, int var2, int var3) {
    // Ported from legacy Java/C++ sources
    // Ensures all 8 surrounding grid squares (and the center) at (var1, var2, var3) are not null
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int x = var1 + dx;
            int y = var2 + dy;
            // Check if the grid square exists; if not, create it
            if (!this->getGridSquare(x, y, var3)) {
                this->createNewGridSquare(x, y, var3, true);
            }
        }
    }
}


void IsoCell::DeleteAllMovingObjects() {
    // Placeholder: Implement deletion of all moving objects
}


int IsoCell::getMaxFloors() {
    // Returns the maximum number of floors (same as MaxHeight)
    return MaxHeight;
}


// Returns a Lua table containing all Lua-exposed IsoObjects in the cell
// The table is left on top of the stack and also returned as a registry reference (or LUA_NOREF on error)
int IsoCell::getLuaObjectList(lua_State* L) {
    // Create a new table
    lua_newtable(L);
    int idx = 1;
    for (auto* obj : ObjectList) {
        if (obj && obj->isLuaExposed()) {
            obj->pushLuaObject(L); // Pushes the Lua object for this IsoObject
            lua_rawseti(L, -2, idx++); // table[idx] = obj
        }
    }
    // Optionally: return a registry reference for later use
    return luaL_ref(L, LUA_REGISTRYINDEX);
}


int IsoCell::getHeightInTiles() {
    // Returns the height in tiles
    return height;
}


int IsoCell::getWidthInTiles() {
    // Returns the width in tiles
    return width;
}

// Returns true if the grid square at (x, y, z) is null or not free (legacy logic)
bool IsoCell::isNull(int x, int y, int z) {
    IsoGridSquare* sq = getGridSquare(x, y, z);
    return sq == nullptr || !sq->isFree(false);
}



// Marks a moving object for removal by adding it to removeList if not already present
void IsoCell::Remove(IsoMovingObject* obj) {
    if (!obj) return;
    if (std::find(removeList.begin(), removeList.end(), obj) == removeList.end()) {
        removeList.push_back(obj);
    }
}



// Returns true if the two grid squares are in different rooms (legacy logic)
bool IsoCell::isBlocked(IsoGridSquare* sq1, IsoGridSquare* sq2) {
    if (!sq1 || !sq2) return true;
    return sq1->room != sq2->room;
}



// Calculates the average color from up to four grid squares' lighting, matching legacy logic
int IsoCell::CalculateColor(IsoGridSquare* sq1, IsoGridSquare* sq2, IsoGridSquare* sq3, IsoGridSquare* sq4, int vertIdx, int lightIdx) {
    float r = 0.0f, g = 0.0f, b = 0.0f;
    int count = 0;
    if (!sq4) return 0;
    // Only include squares in the same room as sq4 and with a valid chunk
    if (sq1 && sq4->room == sq1->room && sq1->getChunk()) {
        auto c = sq1->lighting[lightIdx].lightInfo();
        r += c.r; g += c.g; b += c.b; ++count;
    }
    if (sq2 && sq4->room == sq2->room && sq2->getChunk()) {
        auto c = sq2->lighting[lightIdx].lightInfo();
        r += c.r; g += c.g; b += c.b; ++count;
    }
    if (sq3 && sq4->room == sq3->room && sq3->getChunk()) {
        auto c = sq3->lighting[lightIdx].lightInfo();
        r += c.r; g += c.g; b += c.b; ++count;
    }
    if (sq4) {
        auto c = sq4->lighting[lightIdx].lightInfo();
        r += c.r; g += c.g; b += c.b; ++count;
    }
    if (count > 0) {
        r /= count; g /= count; b /= count;
    }
    r = std::clamp(r, 0.0f, 1.0f);
    g = std::clamp(g, 0.0f, 1.0f);
    b = std::clamp(b, 0.0f, 1.0f);
    int color = (int(r * 255.0f)) | (int(g * 255.0f) << 8) | (int(b * 255.0f) << 16) | 0xFF000000;
    if (sq4) {
        sq4->setVertLight(vertIdx, color, lightIdx);
        sq4->setVertLight(vertIdx + 4, color, lightIdx);
    }
    return vertIdx;
}



// Returns the static IsoCell instance (singleton pattern)
IsoCell* IsoCell::getInstance() {
    return instance;
}


void IsoCell::render() {
    // Main render logic: performance-measured call to renderInternal
    // If you have a performance measurement utility, use it here. Otherwise, call directly.
#ifdef USE_PERFORMANCE_MEASURE
    s_performance.isoCellRender.invokeAndMeasure(this, &IsoCell::renderInternal);
#else
    renderInternal();
#endif
}


void IsoCell::renderInternal() {
    // Main render logic ported from legacy sources
    int playerIdx = IsoCamera::frameState.playerIndex;
    IsoPlayer* player = IsoPlayer::players[playerIdx];
    if (!player) return;

    // Dirty grid stack recalc
    if (player->dirtyRecalcGridStackTime > 0.0f) {
        player->dirtyRecalcGridStack = true;
    } else {
        player->dirtyRecalcGridStack = false;
    }

    // Floor hiding logic (simplified)
    if (!PerformanceSettings::NewRoofHiding) {
        if (bHideFloors[playerIdx] && unhideFloorsCounter[playerIdx] > 0) {
            unhideFloorsCounter[playerIdx]--;
        }
        if (unhideFloorsCounter[playerIdx] <= 0) {
            bHideFloors[playerIdx] = false;
            unhideFloorsCounter[playerIdx] = 60;
        }
    }

    // Calculate min/max bounds (simplified, see legacy for full math)
    minX -= 2;
    minY -= 2;
    maxZ = MaxHeight;
    if (!IsoCamera::CamCharacter) {
        maxZ = 1;
    }

    // Hide floors if behind stuff (simplified)
    if (!PerformanceSettings::NewRoofHiding) {
        IsoGridSquare* camSq = IsoCamera::CamCharacter ? IsoCamera::CamCharacter->getCurrentSquare() : nullptr;
        if (camSq && IsBehindStuff(camSq)) {
            bHideFloors[playerIdx] = true;
        }
        if (bHideFloors[playerIdx] && IsoCamera::CamCharacter) {
            maxZ = (int)IsoCamera::CamCharacter->getZ() + 1;
        }
    }

    // Draw stencil mask if needed
    if (PerformanceSettings::LightingFrameSkip < 3) {
        DrawStencilMask();
    }

    // Main tile rendering (performance-wrapped)
    bRendering = true;
    try {
        RenderTiles(8); // 8 is a placeholder for the tile layer count
    } catch (...) {
        bRendering = false;
        // Optionally log error
        return;
    }
    bRendering = false;

    // Post-render: update light cache timers (simplified)
    if (IsoGridSquare::getRecalcLightTime() < 0) {
        IsoGridSquare::setRecalcLightTime(60);
    }
    if (IsoGridSquare::getLightcache() <= 0) {
        IsoGridSquare::setLightcache(90);
    }

    // Render last for all moving/static objects
    for (auto* obj : ObjectList) {
        if (obj) obj->renderlast();
    }
    for (auto* obj : StaticUpdaterObjectList) {
        if (obj) obj->renderlast();
    }

    // Render tree chop indicators (stub)
    IsoTree::renderChopTreeIndicators();

    // Save last minX/minY
    lastMinX = minX;
    lastMinY = minY;

    // Building logic (stub)
    DoBuilding(IsoPlayer::getPlayerIndex(), true);

    // Render rain (stub)
    renderRain();
}


void IsoCell::invalidatePeekedRoom(int var1) {
    // Resets the lastPlayerDir for the given player index, matching legacy logic
    if (var1 >= 0 && var1 < static_cast<int>(lastPlayerDir.size())) {
        lastPlayerDir[var1] = IsoDirections::Max;
    }
}


bool IsoCell::initWeatherFx() {
    // Initialize weather FX if not already set, matching legacy logic
    if (GameServer::bServer) {
        return false;
    }
    if (!weatherFX) {
        weatherFX = std::make_unique<IsoWeatherFX>();
        weatherFX->init();
        return true;
    }
    return false;
}


void IsoCell::updateWeatherFx() {
    // Update the weather FX if it exists, matching legacy logic
    if (weatherFX) {
        weatherFX->update();
    }
}


void IsoCell::renderWeatherFx() {
    // Render weather FX if available
    if (weatherFX) {
        weatherFX->render();
    }
    // Optionally, render additional weather overlays or effects here
    // Lightning effect (stub)
    if (lightningFX) {
        lightningFX->render();
    }

    // Fog effect (stub)
    if (fogFX) {
        fogFX->render();
    }

    // Additional weather overlays can be added here as new systems are integrated
}


IsoWeatherFX* IsoCell::getWeatherFX() {
    // Returns the weather FX object
    return weatherFX;
}


void IsoCell::renderRain() {
    // Render rain FX if available
    if (rainFX) {
        rainFX->render();
    }

    // Optionally, render additional rain overlays or effects here

    // Rain splashes effect (stub)
    if (rainSplashesFX) {
        rainSplashesFX->render();
    }

    // Wet surfaces effect (stub)
    if (wetSurfacesFX) {
        wetSurfacesFX->render();
    }

    // Puddles effect (stub)
    if (puddlesFX) {
        puddlesFX->render();
    }

    // Additional rain overlays can be added here as new systems are integrated
}


void IsoCell::setRainAlpha(int var1) {
    // Placeholder: Implement setting rain alpha
}


void IsoCell::setRainIntensity(int var1) {
    // Placeholder: Implement setting rain intensity
}


void IsoCell::setRainSpeed(int var1) {
    // Placeholder: Implement setting rain speed
}


void IsoCell::reloadRainTextures() {
    // Placeholder: Implement reloading rain textures
}


void IsoCell::GetBuildingsInFrontOfCharacter(std::vector<IsoBuilding*> var1, IsoGridSquare* var2, bool var3) {
    // Placeholder: Implement logic to get buildings in front of character
}


void IsoCell::GetBuildingsInFrontOfCharacterSquare(int var1, int var2, int var3, bool var4, std::vector<IsoBuilding*> var5) {
    // Placeholder: Implement logic to get buildings in front of character square
}


IsoBuilding* IsoCell::GetPeekedInBuilding(IsoGridSquare* var1, IsoDirections var2) {
    // Placeholder: Implement logic to get peeked-in building
    return nullptr;
}


void IsoCell::GetSquaresAroundPlayerSquare(IsoPlayer* var1, IsoGridSquare* var2, std::vector<IsoGridSquare*>& var3, std::vector<IsoGridSquare*>& var4) {
    // Placeholder: Implement logic to get squares around player square
}


bool IsoCell::IsBehindStuff(IsoGridSquare* var1) {
    // Placeholder: Implement logic to check if square is behind stuff
    return false;
}


IsoDirections IsoCell::FromMouseTile() {
    // Placeholder: Implement logic to get direction from mouse tile
    return IsoDirections::N;
}


void IsoCell::update() {
    // Calls the performance-measured updateInternal
    s_performance.isoCellUpdate.invokeAndMeasure(this, &IsoCell::updateInternal);
}


void IsoCell::updateInternal() {
    // Placeholder: Implement main update logic
}


IsoGridSquare* IsoCell::getRandomFreeTile() {
    // Placeholder: Implement logic to get a random free tile
    return nullptr;
}


IsoGridSquare* IsoCell::getRandomOutdoorFreeTile() {
    // Placeholder: Implement logic to get a random outdoor free tile
    return nullptr;
}


IsoGridSquare* IsoCell::getRandomFreeTileInRoom() {
    // Placeholder: Implement logic to get a random free tile in a room
    return nullptr;
}


void IsoCell::roomSpotted(IsoRoom* var1) {
    // Placeholder: Implement logic for when a room is spotted
}


void IsoCell::ProcessSpottedRooms() {
    // Placeholder: Implement logic to process spotted rooms
}


void IsoCell::savePlayer() {
    // Placeholder: Implement logic to save player
}


void IsoCell::save(DataOutputStream* var1, bool var2) {
    // Placeholder: Implement logic to save cell data
}


bool IsoCell::LoadPlayer(int var1) {
    // Placeholder: Implement logic to load player
    return false;
}


IsoGridSquare* IsoCell::getRelativeGridSquare(int var1, int var2, int var3) {
    // Placeholder: Implement logic to get relative grid square
    return nullptr;
}


IsoGridSquare* IsoCell::createNewGridSquare(int var1, int var2, int var3, bool var4) {
    // Placeholder: Implement logic to create a new grid square
    return nullptr;
}


IsoGridSquare* IsoCell::getGridSquareDirect(int var1, int var2, int var3, int var4) {
    // Placeholder: Implement logic to get grid square directly
    return nullptr;
}


bool IsoCell::isInChunkMap(int var1, int var2) {
    // Placeholder: Implement logic to check if in chunk map
    return false;
}


void IsoCell::checkHaveRoof(int var1, int var2) {
    // Placeholder: Implement logic to check for roof
}


IsoZombie* IsoCell::getFakeZombieForHit() {
    // Returns the fake zombie for hit
    return &fakeZombieForHit;
}


void IsoCell::addHeatSource(IsoHeatSource* var1) {
    // Placeholder: Implement logic to add heat source
}


void IsoCell::removeHeatSource(IsoHeatSource* var1) {
    // Placeholder: Implement logic to remove heat source
}


void IsoCell::updateHeatSources() {
    // Placeholder: Implement logic to update heat sources
}


int IsoCell::getHeatSourceTemperature(int var1, int var2, int var3) {
    // Placeholder: Implement logic to get heat source temperature
    return 0;
}


float IsoCell::getHeatSourceHighestTemperature(float var1, int var2, int var3, int var4) {
    // Placeholder: Implement logic to get highest heat source temperature
    return 0.0f;
}


void IsoCell::putInVehicle(IsoGameCharacter* var1) {
    // Placeholder: Implement logic to put character in vehicle
}


void IsoCell::resumeVehicleSounds(IsoGameCharacter* var1) {
    // Placeholder: Implement logic to resume vehicle sounds
}


void IsoCell::AddUniqueToBuildingList(std::vector<IsoBuilding*>& var1, IsoBuilding* var2) {
    // Placeholder: Implement logic to add unique building to list
}


IsoSpriteManager* IsoCell::getSpriteManager() {
    // Placeholder: Implement logic to get sprite manager
    return nullptr;
}

// --- Begin: Event and System Methods ---

void IsoCell::OnPlayerDeath(int playerIndex) {
    // TODO: Implement logic to handle player death event
    // Placeholder: Notify systems, update state, trigger Lua hooks
}

void IsoCell::OnPlayerSpawn(int playerIndex) {
    // TODO: Implement logic to handle player spawn event
    // Placeholder: Initialize player state, notify systems, trigger Lua hooks
}

void IsoCell::OnGameStart() {
    // TODO: Implement logic for game start event
    // Placeholder: Initialize world state, trigger Lua hooks
}

void IsoCell::OnGameEnd() {
    // TODO: Implement logic for game end event
    // Placeholder: Cleanup world state, notify systems, trigger Lua hooks
}

void IsoCell::updateEventSystems(float deltaTime) {
    // TODO: Implement event system update logic
    // Placeholder: Update all event-driven systems (e.g., weather, NPCs)
}

void IsoCell::resetForNewGame() {
    // TODO: Implement logic to reset cell for a new game
    // Placeholder: Clear world state, reset caches, reinitialize systems
}

// --- End: Event and System Methods ---

// --- Begin: SnowGridTiles Methods ---
namespace zombie { namespace iso {

void SnowGridTiles::add(std::shared_ptr<Texture> tex) {
    textures.push_back(tex);
}

std::shared_ptr<Texture> SnowGridTiles::getNext() {
    counter++;
    if (counter >= static_cast<int>(textures.size())) counter = 0;
    return textures[counter];
}

std::shared_ptr<Texture> SnowGridTiles::get(int idx) {
    return textures[idx];
}

int SnowGridTiles::size() const {
    return static_cast<int>(textures.size());
}

// --- End: SnowGridTiles Methods ---

// --- Begin: SnowGrid Methods ---

// Helper: clamp index for wrapping
static int clampIndex(int idx, int max) {
    if (idx == max) return 0;
    if (idx == -1) return max - 1;
    return idx;
}

bool SnowGrid::check(int x, int y) {
    x = clampIndex(x, w);
    y = clampIndex(y, h);
    if (x < 0 || x >= w) return false;
    if (y < 0 || y >= h) return false;
    auto tex = grid[x][y][0];
    // Assume IsoCell* cell is available as a member if needed
    // snowGridTiles_Square must be accessible from IsoCell
    // Placeholder: return true if tex is in snowGridTiles_Square
    // (actual logic may need IsoCell pointer)
    return tex != nullptr; // Simplified for now
}

bool SnowGrid::checkAny(int x, int y) {
    x = clampIndex(x, w);
    y = clampIndex(y, h);
    if (x < 0 || x >= w) return false;
    if (y < 0 || y >= h) return false;
    return grid[x][y][0] != nullptr;
}

void SnowGrid::set(int x, int y, int z, SnowGridTiles& tiles) {
    x = clampIndex(x, w);
    y = clampIndex(y, h);
    if (x >= 0 && x < w && y >= 0 && y < h) {
        grid[x][y][z] = tiles.getNext();
        gridType[x][y][z] = tiles.ID;
    }
}

void SnowGrid::subtract(const SnowGrid& other) {
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            for (int z = 0; z < 2; ++z) {
                if (other.gridType[x][y][z] == gridType[x][y][z]) {
                    grid[x][y][z] = nullptr;
                    gridType[x][y][z] = -1;
                }
            }
        }
    }
}

// --- End: SnowGrid Methods ---

} } // namespace zombie::iso

} // namespace iso
} // namespace zombie
