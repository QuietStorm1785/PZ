#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TByteByteMapDecorator.h"
#include "gnu/trove/decorator/TByteCharMapDecorator.h"
#include "gnu/trove/decorator/TByteDoubleMapDecorator.h"
#include "gnu/trove/decorator/TByteFloatMapDecorator.h"
#include "gnu/trove/decorator/TByteIntMapDecorator.h"
#include "gnu/trove/decorator/TByteListDecorator.h"
#include "gnu/trove/decorator/TByteLongMapDecorator.h"
#include "gnu/trove/decorator/TByteObjectMapDecorator.h"
#include "gnu/trove/decorator/TByteSetDecorator.h"
#include "gnu/trove/decorator/TByteShortMapDecorator.h"
#include "gnu/trove/decorator/TCharByteMapDecorator.h"
#include "gnu/trove/decorator/TCharCharMapDecorator.h"
#include "gnu/trove/decorator/TCharDoubleMapDecorator.h"
#include "gnu/trove/decorator/TCharFloatMapDecorator.h"
#include "gnu/trove/decorator/TCharIntMapDecorator.h"
#include "gnu/trove/decorator/TCharListDecorator.h"
#include "gnu/trove/decorator/TCharLongMapDecorator.h"
#include "gnu/trove/decorator/TCharObjectMapDecorator.h"
#include "gnu/trove/decorator/TCharSetDecorator.h"
#include "gnu/trove/decorator/TCharShortMapDecorator.h"
#include "gnu/trove/decorator/TDoubleByteMapDecorator.h"
#include "gnu/trove/decorator/TDoubleCharMapDecorator.h"
#include "gnu/trove/decorator/TDoubleDoubleMapDecorator.h"
#include "gnu/trove/decorator/TDoubleFloatMapDecorator.h"
#include "gnu/trove/decorator/TDoubleIntMapDecorator.h"
#include "gnu/trove/decorator/TDoubleListDecorator.h"
#include "gnu/trove/decorator/TDoubleLongMapDecorator.h"
#include "gnu/trove/decorator/TDoubleObjectMapDecorator.h"
#include "gnu/trove/decorator/TDoubleSetDecorator.h"
#include "gnu/trove/decorator/TDoubleShortMapDecorator.h"
#include "gnu/trove/decorator/TFloatByteMapDecorator.h"
#include "gnu/trove/decorator/TFloatCharMapDecorator.h"
#include "gnu/trove/decorator/TFloatDoubleMapDecorator.h"
#include "gnu/trove/decorator/TFloatFloatMapDecorator.h"
#include "gnu/trove/decorator/TFloatIntMapDecorator.h"
#include "gnu/trove/decorator/TFloatListDecorator.h"
#include "gnu/trove/decorator/TFloatLongMapDecorator.h"
#include "gnu/trove/decorator/TFloatObjectMapDecorator.h"
#include "gnu/trove/decorator/TFloatSetDecorator.h"
#include "gnu/trove/decorator/TFloatShortMapDecorator.h"
#include "gnu/trove/decorator/TIntByteMapDecorator.h"
#include "gnu/trove/decorator/TIntCharMapDecorator.h"
#include "gnu/trove/decorator/TIntDoubleMapDecorator.h"
#include "gnu/trove/decorator/TIntFloatMapDecorator.h"
#include "gnu/trove/decorator/TIntIntMapDecorator.h"
#include "gnu/trove/decorator/TIntListDecorator.h"
#include "gnu/trove/decorator/TIntLongMapDecorator.h"
#include "gnu/trove/decorator/TIntObjectMapDecorator.h"
#include "gnu/trove/decorator/TIntSetDecorator.h"
#include "gnu/trove/decorator/TIntShortMapDecorator.h"
#include "gnu/trove/decorator/TLongByteMapDecorator.h"
#include "gnu/trove/decorator/TLongCharMapDecorator.h"
#include "gnu/trove/decorator/TLongDoubleMapDecorator.h"
#include "gnu/trove/decorator/TLongFloatMapDecorator.h"
#include "gnu/trove/decorator/TLongIntMapDecorator.h"
#include "gnu/trove/decorator/TLongListDecorator.h"
#include "gnu/trove/decorator/TLongLongMapDecorator.h"
#include "gnu/trove/decorator/TLongObjectMapDecorator.h"
#include "gnu/trove/decorator/TLongSetDecorator.h"
#include "gnu/trove/decorator/TLongShortMapDecorator.h"
#include "gnu/trove/decorator/TObjectByteMapDecorator.h"
#include "gnu/trove/decorator/TObjectCharMapDecorator.h"
#include "gnu/trove/decorator/TObjectDoubleMapDecorator.h"
#include "gnu/trove/decorator/TObjectFloatMapDecorator.h"
#include "gnu/trove/decorator/TObjectIntMapDecorator.h"
#include "gnu/trove/decorator/TObjectLongMapDecorator.h"
#include "gnu/trove/decorator/TObjectShortMapDecorator.h"
#include "gnu/trove/decorator/TShortByteMapDecorator.h"
#include "gnu/trove/decorator/TShortCharMapDecorator.h"
#include "gnu/trove/decorator/TShortDoubleMapDecorator.h"
#include "gnu/trove/decorator/TShortFloatMapDecorator.h"
#include "gnu/trove/decorator/TShortIntMapDecorator.h"
#include "gnu/trove/decorator/TShortListDecorator.h"
#include "gnu/trove/decorator/TShortLongMapDecorator.h"
#include "gnu/trove/decorator/TShortObjectMapDecorator.h"
#include "gnu/trove/decorator/TShortSetDecorator.h"
#include "gnu/trove/decorator/TShortShortMapDecorator.h"
#include "gnu/trove/list/TByteList.h"
#include "gnu/trove/list/TCharList.h"
#include "gnu/trove/list/TDoubleList.h"
#include "gnu/trove/list/TFloatList.h"
#include "gnu/trove/list/TIntList.h"
#include "gnu/trove/list/TLongList.h"
#include "gnu/trove/list/TShortList.h"
#include "gnu/trove/map/TByteByteMap.h"
#include "gnu/trove/map/TByteCharMap.h"
#include "gnu/trove/map/TByteDoubleMap.h"
#include "gnu/trove/map/TByteFloatMap.h"
#include "gnu/trove/map/TByteIntMap.h"
#include "gnu/trove/map/TByteLongMap.h"
#include "gnu/trove/map/TByteObjectMap.h"
#include "gnu/trove/map/TByteShortMap.h"
#include "gnu/trove/map/TCharByteMap.h"
#include "gnu/trove/map/TCharCharMap.h"
#include "gnu/trove/map/TCharDoubleMap.h"
#include "gnu/trove/map/TCharFloatMap.h"
#include "gnu/trove/map/TCharIntMap.h"
#include "gnu/trove/map/TCharLongMap.h"
#include "gnu/trove/map/TCharObjectMap.h"
#include "gnu/trove/map/TCharShortMap.h"
#include "gnu/trove/map/TDoubleByteMap.h"
#include "gnu/trove/map/TDoubleCharMap.h"
#include "gnu/trove/map/TDoubleDoubleMap.h"
#include "gnu/trove/map/TDoubleFloatMap.h"
#include "gnu/trove/map/TDoubleIntMap.h"
#include "gnu/trove/map/TDoubleLongMap.h"
#include "gnu/trove/map/TDoubleObjectMap.h"
#include "gnu/trove/map/TDoubleShortMap.h"
#include "gnu/trove/map/TFloatByteMap.h"
#include "gnu/trove/map/TFloatCharMap.h"
#include "gnu/trove/map/TFloatDoubleMap.h"
#include "gnu/trove/map/TFloatFloatMap.h"
#include "gnu/trove/map/TFloatIntMap.h"
#include "gnu/trove/map/TFloatLongMap.h"
#include "gnu/trove/map/TFloatObjectMap.h"
#include "gnu/trove/map/TFloatShortMap.h"
#include "gnu/trove/map/TIntByteMap.h"
#include "gnu/trove/map/TIntCharMap.h"
#include "gnu/trove/map/TIntDoubleMap.h"
#include "gnu/trove/map/TIntFloatMap.h"
#include "gnu/trove/map/TIntIntMap.h"
#include "gnu/trove/map/TIntLongMap.h"
#include "gnu/trove/map/TIntObjectMap.h"
#include "gnu/trove/map/TIntShortMap.h"
#include "gnu/trove/map/TLongByteMap.h"
#include "gnu/trove/map/TLongCharMap.h"
#include "gnu/trove/map/TLongDoubleMap.h"
#include "gnu/trove/map/TLongFloatMap.h"
#include "gnu/trove/map/TLongIntMap.h"
#include "gnu/trove/map/TLongLongMap.h"
#include "gnu/trove/map/TLongObjectMap.h"
#include "gnu/trove/map/TLongShortMap.h"
#include "gnu/trove/map/TObjectByteMap.h"
#include "gnu/trove/map/TObjectCharMap.h"
#include "gnu/trove/map/TObjectDoubleMap.h"
#include "gnu/trove/map/TObjectFloatMap.h"
#include "gnu/trove/map/TObjectIntMap.h"
#include "gnu/trove/map/TObjectLongMap.h"
#include "gnu/trove/map/TObjectShortMap.h"
#include "gnu/trove/map/TShortByteMap.h"
#include "gnu/trove/map/TShortCharMap.h"
#include "gnu/trove/map/TShortDoubleMap.h"
#include "gnu/trove/map/TShortFloatMap.h"
#include "gnu/trove/map/TShortIntMap.h"
#include "gnu/trove/map/TShortLongMap.h"
#include "gnu/trove/map/TShortObjectMap.h"
#include "gnu/trove/map/TShortShortMap.h"
#include "gnu/trove/set/TByteSet.h"
#include "gnu/trove/set/TCharSet.h"
#include "gnu/trove/set/TDoubleSet.h"
#include "gnu/trove/set/TFloatSet.h"
#include "gnu/trove/set/TIntSet.h"
#include "gnu/trove/set/TLongSet.h"
#include "gnu/trove/set/TShortSet.h"

namespace gnu {
namespace trove {


class TDecorators {
public:
    private TDecorators() {
   }

   public static Map<double, double> wrap(TDoubleDoubleMap map) {
      return std::make_shared<TDoubleDoubleMapDecorator>(map);
   }

   public static Map<double, float> wrap(TDoubleFloatMap map) {
      return std::make_shared<TDoubleFloatMapDecorator>(map);
   }

   public static Map<double, int> wrap(TDoubleIntMap map) {
      return std::make_shared<TDoubleIntMapDecorator>(map);
   }

   public static Map<double, int64_t> wrap(TDoubleLongMap map) {
      return std::make_shared<TDoubleLongMapDecorator>(map);
   }

   public static Map<double, uint8_t> wrap(TDoubleByteMap map) {
      return std::make_shared<TDoubleByteMapDecorator>(map);
   }

   public static Map<double, int16_t> wrap(TDoubleShortMap map) {
      return std::make_shared<TDoubleShortMapDecorator>(map);
   }

   public static Map<double, char> wrap(TDoubleCharMap map) {
      return std::make_shared<TDoubleCharMapDecorator>(map);
   }

   public static Map<float, double> wrap(TFloatDoubleMap map) {
      return std::make_shared<TFloatDoubleMapDecorator>(map);
   }

   public static Map<float, float> wrap(TFloatFloatMap map) {
      return std::make_shared<TFloatFloatMapDecorator>(map);
   }

   public static Map<float, int> wrap(TFloatIntMap map) {
      return std::make_shared<TFloatIntMapDecorator>(map);
   }

   public static Map<float, int64_t> wrap(TFloatLongMap map) {
      return std::make_shared<TFloatLongMapDecorator>(map);
   }

   public static Map<float, uint8_t> wrap(TFloatByteMap map) {
      return std::make_shared<TFloatByteMapDecorator>(map);
   }

   public static Map<float, int16_t> wrap(TFloatShortMap map) {
      return std::make_shared<TFloatShortMapDecorator>(map);
   }

   public static Map<float, char> wrap(TFloatCharMap map) {
      return std::make_shared<TFloatCharMapDecorator>(map);
   }

   public static Map<int, double> wrap(TIntDoubleMap map) {
      return std::make_shared<TIntDoubleMapDecorator>(map);
   }

   public static Map<int, float> wrap(TIntFloatMap map) {
      return std::make_shared<TIntFloatMapDecorator>(map);
   }

   public static Map<int, int> wrap(TIntIntMap map) {
      return std::make_shared<TIntIntMapDecorator>(map);
   }

   public static Map<int, int64_t> wrap(TIntLongMap map) {
      return std::make_shared<TIntLongMapDecorator>(map);
   }

   public static Map<int, uint8_t> wrap(TIntByteMap map) {
      return std::make_shared<TIntByteMapDecorator>(map);
   }

   public static Map<int, int16_t> wrap(TIntShortMap map) {
      return std::make_shared<TIntShortMapDecorator>(map);
   }

   public static Map<int, char> wrap(TIntCharMap map) {
      return std::make_shared<TIntCharMapDecorator>(map);
   }

   public static Map<int64_t, double> wrap(TLongDoubleMap map) {
      return std::make_shared<TLongDoubleMapDecorator>(map);
   }

   public static Map<int64_t, float> wrap(TLongFloatMap map) {
      return std::make_shared<TLongFloatMapDecorator>(map);
   }

   public static Map<int64_t, int> wrap(TLongIntMap map) {
      return std::make_shared<TLongIntMapDecorator>(map);
   }

   public static Map<int64_t, int64_t> wrap(TLongLongMap map) {
      return std::make_shared<TLongLongMapDecorator>(map);
   }

   public static Map<int64_t, uint8_t> wrap(TLongByteMap map) {
      return std::make_shared<TLongByteMapDecorator>(map);
   }

   public static Map<int64_t, int16_t> wrap(TLongShortMap map) {
      return std::make_shared<TLongShortMapDecorator>(map);
   }

   public static Map<int64_t, char> wrap(TLongCharMap map) {
      return std::make_shared<TLongCharMapDecorator>(map);
   }

   public static Map<uint8_t, double> wrap(TByteDoubleMap map) {
      return std::make_shared<TByteDoubleMapDecorator>(map);
   }

   public static Map<uint8_t, float> wrap(TByteFloatMap map) {
      return std::make_shared<TByteFloatMapDecorator>(map);
   }

   public static Map<uint8_t, int> wrap(TByteIntMap map) {
      return std::make_shared<TByteIntMapDecorator>(map);
   }

   public static Map<uint8_t, int64_t> wrap(TByteLongMap map) {
      return std::make_shared<TByteLongMapDecorator>(map);
   }

   public static Map<uint8_t, uint8_t> wrap(TByteByteMap map) {
      return std::make_shared<TByteByteMapDecorator>(map);
   }

   public static Map<uint8_t, int16_t> wrap(TByteShortMap map) {
      return std::make_shared<TByteShortMapDecorator>(map);
   }

   public static Map<uint8_t, char> wrap(TByteCharMap map) {
      return std::make_shared<TByteCharMapDecorator>(map);
   }

   public static Map<int16_t, double> wrap(TShortDoubleMap map) {
      return std::make_shared<TShortDoubleMapDecorator>(map);
   }

   public static Map<int16_t, float> wrap(TShortFloatMap map) {
      return std::make_shared<TShortFloatMapDecorator>(map);
   }

   public static Map<int16_t, int> wrap(TShortIntMap map) {
      return std::make_shared<TShortIntMapDecorator>(map);
   }

   public static Map<int16_t, int64_t> wrap(TShortLongMap map) {
      return std::make_shared<TShortLongMapDecorator>(map);
   }

   public static Map<int16_t, uint8_t> wrap(TShortByteMap map) {
      return std::make_shared<TShortByteMapDecorator>(map);
   }

   public static Map<int16_t, int16_t> wrap(TShortShortMap map) {
      return std::make_shared<TShortShortMapDecorator>(map);
   }

   public static Map<int16_t, char> wrap(TShortCharMap map) {
      return std::make_shared<TShortCharMapDecorator>(map);
   }

   public static Map<char, double> wrap(TCharDoubleMap map) {
      return std::make_shared<TCharDoubleMapDecorator>(map);
   }

   public static Map<char, float> wrap(TCharFloatMap map) {
      return std::make_shared<TCharFloatMapDecorator>(map);
   }

   public static Map<char, int> wrap(TCharIntMap map) {
      return std::make_shared<TCharIntMapDecorator>(map);
   }

   public static Map<char, int64_t> wrap(TCharLongMap map) {
      return std::make_shared<TCharLongMapDecorator>(map);
   }

   public static Map<char, uint8_t> wrap(TCharByteMap map) {
      return std::make_shared<TCharByteMapDecorator>(map);
   }

   public static Map<char, int16_t> wrap(TCharShortMap map) {
      return std::make_shared<TCharShortMapDecorator>(map);
   }

   public static Map<char, char> wrap(TCharCharMap map) {
      return std::make_shared<TCharCharMapDecorator>(map);
   }

   public static <T> Map<T, double> wrap(TObjectDoubleMap<T> map) {
      return std::make_shared<TObjectDoubleMapDecorator>(map);
   }

   public static <T> Map<T, float> wrap(TObjectFloatMap<T> map) {
      return std::make_shared<TObjectFloatMapDecorator>(map);
   }

   public static <T> Map<T, int> wrap(TObjectIntMap<T> map) {
      return std::make_shared<TObjectIntMapDecorator>(map);
   }

   public static <T> Map<T, int64_t> wrap(TObjectLongMap<T> map) {
      return std::make_shared<TObjectLongMapDecorator>(map);
   }

   public static <T> Map<T, uint8_t> wrap(TObjectByteMap<T> map) {
      return std::make_shared<TObjectByteMapDecorator>(map);
   }

   public static <T> Map<T, int16_t> wrap(TObjectShortMap<T> map) {
      return std::make_shared<TObjectShortMapDecorator>(map);
   }

   public static <T> Map<T, char> wrap(TObjectCharMap<T> map) {
      return std::make_shared<TObjectCharMapDecorator>(map);
   }

   public static <T> Map<double, T> wrap(TDoubleObjectMap<T> map) {
      return std::make_shared<TDoubleObjectMapDecorator>(map);
   }

   public static <T> Map<float, T> wrap(TFloatObjectMap<T> map) {
      return std::make_shared<TFloatObjectMapDecorator>(map);
   }

   public static <T> Map<int, T> wrap(TIntObjectMap<T> map) {
      return std::make_shared<TIntObjectMapDecorator>(map);
   }

   public static <T> Map<int64_t, T> wrap(TLongObjectMap<T> map) {
      return std::make_shared<TLongObjectMapDecorator>(map);
   }

   public static <T> Map<uint8_t, T> wrap(TByteObjectMap<T> map) {
      return std::make_shared<TByteObjectMapDecorator>(map);
   }

   public static <T> Map<int16_t, T> wrap(TShortObjectMap<T> map) {
      return std::make_shared<TShortObjectMapDecorator>(map);
   }

   public static <T> Map<char, T> wrap(TCharObjectMap<T> map) {
      return std::make_shared<TCharObjectMapDecorator>(map);
   }

   public static Set<double> wrap(TDoubleSet set) {
      return std::make_shared<TDoubleSetDecorator>(set);
   }

   public static Set<float> wrap(TFloatSet set) {
      return std::make_shared<TFloatSetDecorator>(set);
   }

   public static Set<int> wrap(TIntSet set) {
      return std::make_shared<TIntSetDecorator>(set);
   }

   public static Set<int64_t> wrap(TLongSet set) {
      return std::make_shared<TLongSetDecorator>(set);
   }

   public static Set<uint8_t> wrap(TByteSet set) {
      return std::make_shared<TByteSetDecorator>(set);
   }

   public static Set<int16_t> wrap(TShortSet set) {
      return std::make_shared<TShortSetDecorator>(set);
   }

   public static Set<char> wrap(TCharSet set) {
      return std::make_shared<TCharSetDecorator>(set);
   }

   public static List<double> wrap(TDoubleList list) {
      return std::make_shared<TDoubleListDecorator>(list);
   }

   public static List<float> wrap(TFloatList list) {
      return std::make_shared<TFloatListDecorator>(list);
   }

   public static List<int> wrap(TIntList list) {
      return std::make_shared<TIntListDecorator>(list);
   }

   public static List<int64_t> wrap(TLongList list) {
      return std::make_shared<TLongListDecorator>(list);
   }

   public static List<uint8_t> wrap(TByteList list) {
      return std::make_shared<TByteListDecorator>(list);
   }

   public static List<int16_t> wrap(TShortList list) {
      return std::make_shared<TShortListDecorator>(list);
   }

   public static List<char> wrap(TCharList list) {
      return std::make_shared<TCharListDecorator>(list);
   }
}
} // namespace trove
} // namespace gnu
