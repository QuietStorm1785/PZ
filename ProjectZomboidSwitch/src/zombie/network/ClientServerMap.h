
#pragma once
#include <vector>
#include <cstdint>

// Forward declarations for types used in method signatures
namespace zombie { namespace core { class Texture; } }
namespace zombie { namespace core { class UdpConnection; } }
namespace zombie { namespace core { class ByteBuffer; } }

namespace zombie {
namespace network {

class ClientServerMap {
public:
    static constexpr int ChunksPerServerCell = 5;
    static constexpr int SquaresPerServerCell = 50;

    int playerIndex = 0;
    int centerX = 0;
    int centerY = 0;
    int chunkGridWidth = 0;
    int width = 0;
    std::vector<bool> loaded;

    // Constructors
    ClientServerMap(int playerIndex, int centerX, int centerY, int chunkGridWidth);
    ~ClientServerMap();

    // Methods
    int getMinX() const;
    int getMinY() const;
    int getMaxX() const;
    int getMaxY() const;
    bool isValidCell(int x, int y) const;
    bool setLoaded();

    // Ported from Java (see .cpp for logic)
    bool setPlayerPosition(int x, int y);
    static bool isChunkLoaded(int x, int y);
    static void characterIn(core::UdpConnection* conn, int idx);
    void sendPacket(core::UdpConnection* conn);
    static void receivePacket(core::ByteBuffer* buffer);
    static void render(int idx);
    static void Reset();

private:
    static std::vector<bool> isLoaded;
    static core::Texture* trafficCone;
};

} // namespace network
} // namespace zombie
