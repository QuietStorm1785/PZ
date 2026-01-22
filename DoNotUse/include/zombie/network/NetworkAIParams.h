#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class NetworkAIParams {
public:
    static const int ZOMBIE_UPDATE_INFO_BUNCH_RATE_MS = 200;
    static const int CHARACTER_UPDATE_RATE_MS = 200;
    static const int CHARACTER_EXTRAPOLATION_UPDATE_INTERVAL_MS = 500;
    static const float ZOMBIE_ANTICIPATORY_UPDATE_MULTIPLIER = 0.6F;
    static const int ZOMBIE_OWNERSHIP_INTERVAL = 2000;
    static const int ZOMBIE_REMOVE_INTERVAL_MS = 4000;
    static const int ZOMBIE_MAX_UPDATE_INTERVAL_MS = 3800;
    static const int ZOMBIE_MIN_UPDATE_INTERVAL_MS = 200;
    static const int CHARACTER_PREDICTION_INTERVAL_MS = 2000;
    static const int ZOMBIE_TELEPORT_PLAYER = 2;
    static const int ZOMBIE_TELEPORT_DISTANCE_SQ = 9;
    static const int VEHICLE_SPEED_CAP = 10;
    static const int VEHICLE_MOVING_MP_PHYSIC_UPDATE_RATE = 150;
    static const int VEHICLE_MP_PHYSIC_UPDATE_RATE = 300;
    static const int VEHICLE_BUFFER_DELAY_MS = 500;
    static const int VEHICLE_BUFFER_HISTORY_MS = 800;
    static const long TIME_VALIDATION_DELAY = 1000L;
    static const long TIME_VALIDATION_INTERVAL = 4000L;
    static const long TIME_VALIDATION_TIMEOUT = 10000L;
    static const float MAX_TOWING_TRAILER_DISTANCE_SQ = 1.0F;
    static const float MAX_TOWING_CAR_DISTANCE_SQ = 4.0F;
    static const float MAX_RECONNECT_DISTANCE_SQ = 10.0F;
    static const float TOWING_DISTANCE = 1.5F;
    static bool showConnectionInfo = false;
    static bool showServerInfo = false;
    static bool showPingInfo = false;

    static bool isShowConnectionInfo() {
    return showConnectionInfo;
   }

    static void setShowConnectionInfo(bool var0) {
      showConnectionInfo = var0;
   }

    static bool isShowServerInfo() {
    return showServerInfo;
   }

    static void setShowServerInfo(bool var0) {
      showServerInfo = var0;
   }

    static bool isShowPingInfo() {
    return showPingInfo;
   }

    static void setShowPingInfo(bool var0) {
      showPingInfo = var0;
   }

    static void Init() {
      if (GameClient.bClient) {
         showConnectionInfo = false;
         showServerInfo = true;
         showPingInfo = true;
      }

      MPStatistics.Init();
   }
}
} // namespace network
} // namespace zombie
