#pragma once
#include "gnu/trove/map/hash/THashMap.h"
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/objects/IsoStove.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/LocationRNG.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ContainerOverlays {
public:
  static const ContainerOverlays instance = new ContainerOverlays();
private
  static final ArrayList<ContainerOverlays.ContainerOverlayEntry> tempEntries =
      std::make_unique<ArrayList<>>();
private
  final THashMap<String, ContainerOverlays.ContainerOverlay> overlayMap =
      std::make_unique<THashMap<>>();

  void parseContainerOverlayMapV0(KahluaTableImpl kahluaTableImpl0) {
    for (Entry entry0 : kahluaTableImpl0.delegate.entrySet()) {
      std::string string0 = entry0.getKey().toString();
      ContainerOverlays.ContainerOverlay containerOverlay =
          new ContainerOverlays.ContainerOverlay();
      containerOverlay.name = string0;
      this.overlayMap.put(containerOverlay.name, containerOverlay);
      KahluaTableImpl kahluaTableImpl1 = (KahluaTableImpl)entry0.getValue();

      for (Entry entry1 : kahluaTableImpl1.delegate.entrySet()) {
        std::string string1 = entry1.getKey().toString();
        KahluaTableImpl kahluaTableImpl2 = (KahluaTableImpl)entry1.getValue();
        std::string string2 = null;
        if (kahluaTableImpl2.delegate.containsKey(1.0)) {
          string2 = kahluaTableImpl2.rawget(1.0).toString();
        }

        std::string string3 = null;
        if (kahluaTableImpl2.delegate.containsKey(2.0)) {
          string3 = kahluaTableImpl2.rawget(2.0).toString();
        }

        ContainerOverlays.ContainerOverlayEntry containerOverlayEntry =
            new ContainerOverlays.ContainerOverlayEntry();
        containerOverlayEntry.manyItems = string2;
        containerOverlayEntry.fewItems = string3;
        containerOverlayEntry.room = string1;
        containerOverlay.entries.add(containerOverlayEntry);
      }
    }
  }

  void parseContainerOverlayMapV1(KahluaTableImpl kahluaTableImpl0) {
    KahluaTableIterator kahluaTableIterator0 = kahluaTableImpl0.iterator();

    while (kahluaTableIterator0.advance()) {
      std::string string0 = kahluaTableIterator0.getKey().toString();
      if (!"VERSION".equalsIgnoreCase(string0)) {
        ContainerOverlays.ContainerOverlay containerOverlay =
            new ContainerOverlays.ContainerOverlay();
        containerOverlay.name = string0;
        KahluaTableImpl kahluaTableImpl1 =
            (KahluaTableImpl)kahluaTableIterator0.getValue();
        KahluaTableIterator kahluaTableIterator1 = kahluaTableImpl1.iterator();

        while (kahluaTableIterator1.advance()) {
          KahluaTableImpl kahluaTableImpl2 =
              (KahluaTableImpl)kahluaTableIterator1.getValue();
          std::string string1 = kahluaTableImpl2.rawgetStr("name");
          KahluaTableImpl kahluaTableImpl3 =
              (KahluaTableImpl)kahluaTableImpl2.rawget("tiles");
          ContainerOverlays.ContainerOverlayEntry containerOverlayEntry =
              new ContainerOverlays.ContainerOverlayEntry();
          containerOverlayEntry.manyItems = (String)kahluaTableImpl3.rawget(1);
          containerOverlayEntry.fewItems = (String)kahluaTableImpl3.rawget(2);
          if (StringUtils.isNullOrWhitespace(containerOverlayEntry.manyItems) ||
              "none".equalsIgnoreCase(containerOverlayEntry.manyItems)) {
            containerOverlayEntry.manyItems = nullptr;
          }

          if (StringUtils.isNullOrWhitespace(containerOverlayEntry.fewItems) ||
              "none".equalsIgnoreCase(containerOverlayEntry.fewItems)) {
            containerOverlayEntry.fewItems = nullptr;
          }

          containerOverlayEntry.room = string1;
          containerOverlay.entries.add(containerOverlayEntry);
        }

        this.overlayMap.put(containerOverlay.name, containerOverlay);
      }
    }
  }

  void addOverlays(KahluaTableImpl _overlayMap) {
    int int0 = _overlayMap.rawgetInt("VERSION");
    if (int0 == -1) {
      this.parseContainerOverlayMapV0(_overlayMap);
    } else {
      if (int0 != 1) {
        throw new RuntimeException("unknown overlayMap.VERSION " + int0);
      }

      this.parseContainerOverlayMapV1(_overlayMap);
    }
  }

  bool hasOverlays(IsoObject obj) {
    return obj != nullptr && obj.sprite != nullptr &&
           obj.sprite.name != nullptr &&
           this.overlayMap.containsKey(obj.sprite.name);
  }

  void updateContainerOverlaySprite(IsoObject obj) {
    if (obj != nullptr) {
      if (!(obj instanceof IsoStove)) {
        IsoGridSquare square = obj.getSquare();
        if (square != nullptr) {
          std::string string0 = null;
          ItemContainer container = obj.getContainer();
          if (obj.sprite != nullptr && obj.sprite.name != nullptr &&
              container != nullptr && container.getItems() != nullptr &&
              !container.isEmpty()) {
            ContainerOverlays.ContainerOverlay containerOverlay =
                this.overlayMap.get(obj.sprite.name);
            if (containerOverlay != nullptr) {
              std::string string1 = "other";
              if (square.getRoom() != nullptr) {
                string1 = square.getRoom().getName();
              }

              ContainerOverlays.ContainerOverlayEntry containerOverlayEntry =
                  containerOverlay.pickRandom(string1, square.x, square.y,
                                              square.z);
              if (containerOverlayEntry == nullptr) {
                containerOverlayEntry = containerOverlay.pickRandom(
                    "other", square.x, square.y, square.z);
              }

              if (containerOverlayEntry != nullptr) {
                string0 = containerOverlayEntry.manyItems;
                if (containerOverlayEntry.fewItems != nullptr &&
                    container.getItems().size() < 7) {
                  string0 = containerOverlayEntry.fewItems;
                }
              }
            }
          }

          if (!StringUtils.isNullOrWhitespace(string0) && !GameServer.bServer &&
              Texture.getSharedTexture(string0) == nullptr) {
            string0 = nullptr;
          }

          obj.setOverlaySprite(string0);
        }
      }
    }
  }

  void Reset() { this.overlayMap.clear(); }

private
  static final class ContainerOverlay {
    std::string name;
  public
    final ArrayList<ContainerOverlays.ContainerOverlayEntry> entries =
        std::make_unique<ArrayList<>>();

    void
    getEntries(const std::string &string,
               ArrayList<ContainerOverlays.ContainerOverlayEntry> arrayList) {
      arrayList.clear();

      for (int int0 = 0; int0 < this.entries.size(); int0++) {
        ContainerOverlays.ContainerOverlayEntry containerOverlayEntry =
            this.entries.get(int0);
        if (containerOverlayEntry.room.equalsIgnoreCase(string)) {
          arrayList.add(containerOverlayEntry);
        }
      }
    }

  public
    ContainerOverlays.ContainerOverlayEntry pickRandom(String string, int int1,
                                                       int int2, int int3) {
      this.getEntries(string, ContainerOverlays.tempEntries);
      if (ContainerOverlays.tempEntries.isEmpty()) {
        return null;
      } else {
        int int0 = LocationRNG.instance.nextInt(
            ContainerOverlays.tempEntries.size(), int1, int2, int3);
        return ContainerOverlays.tempEntries.get(int0);
      }
    }
  }

  private static final class ContainerOverlayEntry {
    std::string room;
    std::string manyItems;
    std::string fewItems;
  }
}
} // namespace iso
} // namespace zombie
