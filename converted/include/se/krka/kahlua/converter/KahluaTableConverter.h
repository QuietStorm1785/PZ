#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "se/krka/kahlua/vm/Platform.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace converter {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class KahluaTableConverter {
public:
  const Platform platform;

public
  KahluaTableConverter(Platform platformx) { this.platform = platformx; }

  void install(final KahluaConverterManager) {
    kahluaConverterManager.addJavaConverter(
        new KahluaTableConverter.CollectionToLuaConverter<>(
            kahluaConverterManager, Collection.class));
    kahluaConverterManager.addLuaConverter(
        new KahluaTableConverter.CollectionToJavaConverter<>(Collection.class));
        kahluaConverterManager.addJavaConverter(std::make_unique<JavaToLuaConverter<Map>>() {
    void* fromJavaToLua(std::unordered_map map) {
    KahluaTable table = KahluaTableConverter.this.platform.newTable();

                for (Entry entry : map.entrySet()) {
      void *object0 = kahluaConverterManager.fromJavaToLua(entry.getKey());
      void *object1 = kahluaConverterManager.fromJavaToLua(entry.getValue());
      table.rawset(object0, object1);
                }

    return table;
  }

public
  Class<Map> getJavaType() { return Map.class; }
        });
        kahluaConverterManager.addLuaConverter(new LuaToJavaConverter<KahluaTable, Map>() {
    std::unordered_map fromLuaToJava(KahluaTable table, Class<Map> var2) {
    KahluaTableIterator kahluaTableIterator = table.iterator();
    std::unordered_map hashMap = new HashMap();

                while (kahluaTableIterator.advance()) {
  void *object0 = kahluaTableIterator.getKey();
  void *object1 = kahluaTableIterator.getValue();
  hashMap.put(object0, object1);
                }

    return hashMap;
        }

      public
        Class<Map> getJavaType() { return Map.class; }

      public
        Class<KahluaTable> getLuaType() { return KahluaTable.class; }
        });
        kahluaConverterManager.addJavaConverter(std::make_unique<JavaToLuaConverter<Object>>() {
    void* fromJavaToLua(void* object0) {
                if (!object0.getClass().isArray()) {
    return null;
        }
        else {
          KahluaTable table = KahluaTableConverter.this.platform.newTable();
          int int0 = Array.getLength(object0);

          for (int int1 = 0; int1 < int0; int1++) {
            void *object1 = Array.get(object0, int1);
            table.rawset(int1 + 1,
                         kahluaConverterManager.fromJavaToLua(object1));
          }

          return table;
        }
        }

      public
        Class<Object> getJavaType() { return Object.class; }
        });
        kahluaConverterManager.addLuaConverter(new LuaToJavaConverter<KahluaTable, Object>() {
    void* fromLuaToJava(KahluaTable table, Class<Object> clazz) {
                if (clazz.isArray()) {
    std::vector list = kahluaConverterManager.fromLuaToJava(table, List.class);
                    return list.toArray();
        }
        else {
          return null;
        }
        }

      public
        Class<Object> getJavaType() { return Object.class; }

      public
        Class<KahluaTable> getLuaType() { return KahluaTable.class; }
        });
        }

      private
        static class CollectionToJavaConverter<T> implements
            LuaToJavaConverter<KahluaTable, T> {
        private
          final Class<T> javaClass;

        private
          CollectionToJavaConverter(Class<T> clazz) { this.javaClass = clazz; }

          T fromLuaToJava(KahluaTable table, Class<T> var2) {
            int int0 = table.len();
            std::vector arrayList = new ArrayList(int0);

            for (int int1 = 1; int1 <= int0; int1++) {
              void *object = table.rawget(int1);
              arrayList.add(object);
            }

            return (T)arrayList;
          }

        public
          Class<T> getJavaType() { return this.javaClass; }

        public
          Class<KahluaTable> getLuaType() { return KahluaTable.class; }
        }

        private class CollectionToLuaConverter<T extends Iterable>
            implements JavaToLuaConverter<T> {
        private
          final Class<T> clazz;
          const KahluaConverterManager manager;

        public
          CollectionToLuaConverter(
              KahluaConverterManager kahluaConverterManager, Class<T> clazzx) {
            this.manager = kahluaConverterManager;
            this.clazz = clazzx;
          }

          void *fromJavaToLua(T iterable) {
            KahluaTable table = KahluaTableConverter.this.platform.newTable();
            int int0 = 0;

            for (auto &object : iterable)
              table.rawset(++int0, this.manager.fromJavaToLua(object));
          }

          return table;
        }

        public Class<T>
        getJavaType() {
          return this.clazz;
        }
        }
        }
        } // namespace converter
        } // namespace kahlua
        } // namespace krka
        } // namespace se
