#include <string>
#include "zombie/iso/IsoLot.h"

namespace zombie {
namespace iso {

void IsoLot::Dispose() {
    std::lock_guard<std::mutex> lock(lot_mutex);
    for (auto& kv : InfoHeaders) {
        if (kv.second) kv.second->Dispose();
    }
    InfoHeaders.clear();
    InfoHeaderNames.clear();
    InfoFileNames.clear();
    pool.forEach([](IsoLot* lot) {
        if (lot->m_in) {
            lot->m_in->close();
            lot->m_in = nullptr;
        }
    });
}

std::string IsoLot::readString(BufferedRandomAccessFile& var0) {
    return var0.getNextLine();
}

int IsoLot::readInt(BufferedRandomAccessFile& var0) {
    int b1 = var0.read();
    int b2 = var0.read();
    int b3 = var0.read();
    int b4 = var0.read();
    if ((b1 | b2 | b3 | b4) < 0) throw std::runtime_error("EOF");
    return (b1 << 0) + (b2 << 8) + (b3 << 16) + (b4 << 24);
}

int IsoLot::readShort(BufferedRandomAccessFile& var0) {
    int b1 = var0.read();
    int b2 = var0.read();
    if ((b1 | b2) < 0) throw std::runtime_error("EOF");
    return (b1 << 0) + (b2 << 8);
}

void IsoLot::load(int cellX, int cellY, int wx_, int wy_, std::shared_ptr<IsoChunk> chunk) {
    std::lock_guard<std::mutex> lock(lot_mutex);
    std::string headerKey = ChunkMapFilenames::instance.getHeader(cellX, cellY);
    info = InfoHeaders.count(headerKey) ? InfoHeaders[headerKey] : nullptr;
    wx = wx_;
    wy = wy_;
    if (chunk) chunk->lotheader = info;

    try {
        std::string lotFile = "world_" + std::to_string(cellX) + "_" + std::to_string(cellY) + ".lotpack";
        std::string lotPath = InfoFileNames.count(lotFile) ? InfoFileNames[lotFile] : lotFile;
        if (!m_in || m_lastUsedPath != lotPath) {
            if (m_in) m_in->close();
            m_in = std::make_shared<BufferedRandomAccessFile>(lotPath, "r", 4096);
            m_lastUsedPath = lotPath;
        }
        int var8 = 0;
        int var9 = wx - cellX * 30;
        int var10 = wy - cellY * 30;
        int var11 = var9 * 30 + var10;
        m_in->seek(4 + var11 * 8);
        int var12 = readInt(*m_in);
        m_in->seek(var12);
        m_data.clear();
        int maxLevels = info ? std::min(info->levels, 8) : 8;
        for (int l = 0; l < maxLevels; ++l) {
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    int idx = i + j * 10 + l * 100;
                    m_offsetInData[idx] = -1;
                    if (var8 > 0) {
                        var8--;
                    } else {
                        int var18 = readInt(*m_in);
                        if (var18 == -1) {
                            var8 = readInt(*m_in);
                            if (var8 > 0) {
                                var8--;
                                continue;
                            }
                        }
                        if (var18 > 1) {
                            m_offsetInData[idx] = (int)m_data.size();
                            m_data.push_back(var18 - 1);
                            int var19 = readInt(*m_in);
                            for (int k = 1; k < var18; ++k) {
                                int var21 = readInt(*m_in);
                                m_data.push_back(var21);
                            }
                        }
                    }
                }
            }
        }
    } catch (const std::exception& ex) {
        std::fill(m_offsetInData.begin(), m_offsetInData.end(), -1);
        m_data.clear();
        ExceptionLogger::logException(ex);
    }
}

} // namespace iso
} // namespace zombie
