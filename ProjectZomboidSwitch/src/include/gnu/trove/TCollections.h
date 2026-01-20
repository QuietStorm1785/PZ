#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/sync/TSynchronizedByteByteMap.h"
#include "gnu/trove/impl/sync/TSynchronizedByteCharMap.h"
#include "gnu/trove/impl/sync/TSynchronizedByteCollection.h"
#include "gnu/trove/impl/sync/TSynchronizedByteDoubleMap.h"
#include "gnu/trove/impl/sync/TSynchronizedByteFloatMap.h"
#include "gnu/trove/impl/sync/TSynchronizedByteIntMap.h"
#include "gnu/trove/impl/sync/TSynchronizedByteList.h"
#include "gnu/trove/impl/sync/TSynchronizedByteLongMap.h"
#include "gnu/trove/impl/sync/TSynchronizedByteObjectMap.h"
#include "gnu/trove/impl/sync/TSynchronizedByteSet.h"
#include "gnu/trove/impl/sync/TSynchronizedByteShortMap.h"
#include "gnu/trove/impl/sync/TSynchronizedCharByteMap.h"
#include "gnu/trove/impl/sync/TSynchronizedCharCharMap.h"
#include "gnu/trove/impl/sync/TSynchronizedCharCollection.h"
#include "gnu/trove/impl/sync/TSynchronizedCharDoubleMap.h"
#include "gnu/trove/impl/sync/TSynchronizedCharFloatMap.h"
#include "gnu/trove/impl/sync/TSynchronizedCharIntMap.h"
#include "gnu/trove/impl/sync/TSynchronizedCharList.h"
#include "gnu/trove/impl/sync/TSynchronizedCharLongMap.h"
#include "gnu/trove/impl/sync/TSynchronizedCharObjectMap.h"
#include "gnu/trove/impl/sync/TSynchronizedCharSet.h"
#include "gnu/trove/impl/sync/TSynchronizedCharShortMap.h"
#include "gnu/trove/impl/sync/TSynchronizedDoubleByteMap.h"
#include "gnu/trove/impl/sync/TSynchronizedDoubleCharMap.h"
#include "gnu/trove/impl/sync/TSynchronizedDoubleCollection.h"
#include "gnu/trove/impl/sync/TSynchronizedDoubleDoubleMap.h"
#include "gnu/trove/impl/sync/TSynchronizedDoubleFloatMap.h"
#include "gnu/trove/impl/sync/TSynchronizedDoubleIntMap.h"
#include "gnu/trove/impl/sync/TSynchronizedDoubleList.h"
#include "gnu/trove/impl/sync/TSynchronizedDoubleLongMap.h"
#include "gnu/trove/impl/sync/TSynchronizedDoubleObjectMap.h"
#include "gnu/trove/impl/sync/TSynchronizedDoubleSet.h"
#include "gnu/trove/impl/sync/TSynchronizedDoubleShortMap.h"
#include "gnu/trove/impl/sync/TSynchronizedFloatByteMap.h"
#include "gnu/trove/impl/sync/TSynchronizedFloatCharMap.h"
#include "gnu/trove/impl/sync/TSynchronizedFloatCollection.h"
#include "gnu/trove/impl/sync/TSynchronizedFloatDoubleMap.h"
#include "gnu/trove/impl/sync/TSynchronizedFloatFloatMap.h"
#include "gnu/trove/impl/sync/TSynchronizedFloatIntMap.h"
#include "gnu/trove/impl/sync/TSynchronizedFloatList.h"
#include "gnu/trove/impl/sync/TSynchronizedFloatLongMap.h"
#include "gnu/trove/impl/sync/TSynchronizedFloatObjectMap.h"
#include "gnu/trove/impl/sync/TSynchronizedFloatSet.h"
#include "gnu/trove/impl/sync/TSynchronizedFloatShortMap.h"
#include "gnu/trove/impl/sync/TSynchronizedIntByteMap.h"
#include "gnu/trove/impl/sync/TSynchronizedIntCharMap.h"
#include "gnu/trove/impl/sync/TSynchronizedIntCollection.h"
#include "gnu/trove/impl/sync/TSynchronizedIntDoubleMap.h"
#include "gnu/trove/impl/sync/TSynchronizedIntFloatMap.h"
#include "gnu/trove/impl/sync/TSynchronizedIntIntMap.h"
#include "gnu/trove/impl/sync/TSynchronizedIntList.h"
#include "gnu/trove/impl/sync/TSynchronizedIntLongMap.h"
#include "gnu/trove/impl/sync/TSynchronizedIntObjectMap.h"
#include "gnu/trove/impl/sync/TSynchronizedIntSet.h"
#include "gnu/trove/impl/sync/TSynchronizedIntShortMap.h"
#include "gnu/trove/impl/sync/TSynchronizedLongByteMap.h"
#include "gnu/trove/impl/sync/TSynchronizedLongCharMap.h"
#include "gnu/trove/impl/sync/TSynchronizedLongCollection.h"
#include "gnu/trove/impl/sync/TSynchronizedLongDoubleMap.h"
#include "gnu/trove/impl/sync/TSynchronizedLongFloatMap.h"
#include "gnu/trove/impl/sync/TSynchronizedLongIntMap.h"
#include "gnu/trove/impl/sync/TSynchronizedLongList.h"
#include "gnu/trove/impl/sync/TSynchronizedLongLongMap.h"
#include "gnu/trove/impl/sync/TSynchronizedLongObjectMap.h"
#include "gnu/trove/impl/sync/TSynchronizedLongSet.h"
#include "gnu/trove/impl/sync/TSynchronizedLongShortMap.h"
#include "gnu/trove/impl/sync/TSynchronizedObjectByteMap.h"
#include "gnu/trove/impl/sync/TSynchronizedObjectCharMap.h"
#include "gnu/trove/impl/sync/TSynchronizedObjectDoubleMap.h"
#include "gnu/trove/impl/sync/TSynchronizedObjectFloatMap.h"
#include "gnu/trove/impl/sync/TSynchronizedObjectIntMap.h"
#include "gnu/trove/impl/sync/TSynchronizedObjectLongMap.h"
#include "gnu/trove/impl/sync/TSynchronizedObjectShortMap.h"
#include "gnu/trove/impl/sync/TSynchronizedRandomAccessByteList.h"
#include "gnu/trove/impl/sync/TSynchronizedRandomAccessCharList.h"
#include "gnu/trove/impl/sync/TSynchronizedRandomAccessDoubleList.h"
#include "gnu/trove/impl/sync/TSynchronizedRandomAccessFloatList.h"
#include "gnu/trove/impl/sync/TSynchronizedRandomAccessIntList.h"
#include "gnu/trove/impl/sync/TSynchronizedRandomAccessLongList.h"
#include "gnu/trove/impl/sync/TSynchronizedRandomAccessShortList.h"
#include "gnu/trove/impl/sync/TSynchronizedShortByteMap.h"
#include "gnu/trove/impl/sync/TSynchronizedShortCharMap.h"
#include "gnu/trove/impl/sync/TSynchronizedShortCollection.h"
#include "gnu/trove/impl/sync/TSynchronizedShortDoubleMap.h"
#include "gnu/trove/impl/sync/TSynchronizedShortFloatMap.h"
#include "gnu/trove/impl/sync/TSynchronizedShortIntMap.h"
#include "gnu/trove/impl/sync/TSynchronizedShortList.h"
#include "gnu/trove/impl/sync/TSynchronizedShortLongMap.h"
#include "gnu/trove/impl/sync/TSynchronizedShortObjectMap.h"
#include "gnu/trove/impl/sync/TSynchronizedShortSet.h"
#include "gnu/trove/impl/sync/TSynchronizedShortShortMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteByteMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteCharMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteDoubleMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteFloatMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteIntMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteLongMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteObjectMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteSet.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteShortMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharByteMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharCharMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharDoubleMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharFloatMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharIntMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharLongMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharObjectMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharSet.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharShortMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleByteMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleCharMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleDoubleMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleFloatMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleIntMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleLongMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleObjectMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleSet.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleShortMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatByteMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatCharMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatDoubleMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatFloatMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatIntMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatLongMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatObjectMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatSet.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatShortMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntByteMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntCharMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntDoubleMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntFloatMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntIntMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntLongMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntObjectMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntSet.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntShortMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongByteMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongCharMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongDoubleMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongFloatMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongIntMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongLongMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongObjectMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongSet.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongShortMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableObjectByteMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableObjectCharMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableObjectDoubleMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableObjectFloatMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableObjectIntMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableObjectLongMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableObjectShortMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableRandomAccessByteList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableRandomAccessCharList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableRandomAccessDoubleList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableRandomAccessFloatList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableRandomAccessIntList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableRandomAccessLongList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableRandomAccessShortList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortByteMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortCharMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortCollection.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortDoubleMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortFloatMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortIntMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortList.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortLongMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortObjectMap.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortSet.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortShortMap.h"
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
#include <algorithm>

namespace gnu {
namespace trove {


class TCollections {
public:
    private TCollections() {
   }

    static TDoubleCollection unmodifiableCollection(TDoubleCollection c) {
      return std::make_shared<TUnmodifiableDoubleCollection>(c);
   }

    static TFloatCollection unmodifiableCollection(TFloatCollection c) {
      return std::make_shared<TUnmodifiableFloatCollection>(c);
   }

    static TIntCollection unmodifiableCollection(TIntCollection c) {
      return std::make_shared<TUnmodifiableIntCollection>(c);
   }

    static TLongCollection unmodifiableCollection(TLongCollection c) {
      return std::make_shared<TUnmodifiableLongCollection>(c);
   }

    static TByteCollection unmodifiableCollection(TByteCollection c) {
      return std::make_shared<TUnmodifiableByteCollection>(c);
   }

    static TShortCollection unmodifiableCollection(TShortCollection c) {
      return std::make_shared<TUnmodifiableShortCollection>(c);
   }

    static TCharCollection unmodifiableCollection(TCharCollection c) {
      return std::make_shared<TUnmodifiableCharCollection>(c);
   }

    static TDoubleSet unmodifiableSet(TDoubleSet s) {
      return std::make_shared<TUnmodifiableDoubleSet>(s);
   }

    static TFloatSet unmodifiableSet(TFloatSet s) {
      return std::make_shared<TUnmodifiableFloatSet>(s);
   }

    static TIntSet unmodifiableSet(TIntSet s) {
      return std::make_shared<TUnmodifiableIntSet>(s);
   }

    static TLongSet unmodifiableSet(TLongSet s) {
      return std::make_shared<TUnmodifiableLongSet>(s);
   }

    static TByteSet unmodifiableSet(TByteSet s) {
      return std::make_shared<TUnmodifiableByteSet>(s);
   }

    static TShortSet unmodifiableSet(TShortSet s) {
      return std::make_shared<TUnmodifiableShortSet>(s);
   }

    static TCharSet unmodifiableSet(TCharSet s) {
      return std::make_shared<TUnmodifiableCharSet>(s);
   }

    static TDoubleList unmodifiableList(TDoubleList list) {
      return (TDoubleList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessDoubleList>(list) : std::make_shared<TUnmodifiableDoubleList>(list));
   }

    static TFloatList unmodifiableList(TFloatList list) {
      return (TFloatList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessFloatList>(list) : std::make_shared<TUnmodifiableFloatList>(list));
   }

    static TIntList unmodifiableList(TIntList list) {
      return (TIntList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessIntList>(list) : std::make_shared<TUnmodifiableIntList>(list));
   }

    static TLongList unmodifiableList(TLongList list) {
      return (TLongList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessLongList>(list) : std::make_shared<TUnmodifiableLongList>(list));
   }

    static TByteList unmodifiableList(TByteList list) {
      return (TByteList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessByteList>(list) : std::make_shared<TUnmodifiableByteList>(list));
   }

    static TShortList unmodifiableList(TShortList list) {
      return (TShortList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessShortList>(list) : std::make_shared<TUnmodifiableShortList>(list));
   }

    static TCharList unmodifiableList(TCharList list) {
      return (TCharList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TUnmodifiableRandomAccessCharList>(list) : std::make_shared<TUnmodifiableCharList>(list));
   }

    static TDoubleDoubleMap unmodifiableMap(TDoubleDoubleMap m) {
      return std::make_shared<TUnmodifiableDoubleDoubleMap>(m);
   }

    static TDoubleFloatMap unmodifiableMap(TDoubleFloatMap m) {
      return std::make_shared<TUnmodifiableDoubleFloatMap>(m);
   }

    static TDoubleIntMap unmodifiableMap(TDoubleIntMap m) {
      return std::make_shared<TUnmodifiableDoubleIntMap>(m);
   }

    static TDoubleLongMap unmodifiableMap(TDoubleLongMap m) {
      return std::make_shared<TUnmodifiableDoubleLongMap>(m);
   }

    static TDoubleByteMap unmodifiableMap(TDoubleByteMap m) {
      return std::make_shared<TUnmodifiableDoubleByteMap>(m);
   }

    static TDoubleShortMap unmodifiableMap(TDoubleShortMap m) {
      return std::make_shared<TUnmodifiableDoubleShortMap>(m);
   }

    static TDoubleCharMap unmodifiableMap(TDoubleCharMap m) {
      return std::make_shared<TUnmodifiableDoubleCharMap>(m);
   }

    static TFloatDoubleMap unmodifiableMap(TFloatDoubleMap m) {
      return std::make_shared<TUnmodifiableFloatDoubleMap>(m);
   }

    static TFloatFloatMap unmodifiableMap(TFloatFloatMap m) {
      return std::make_shared<TUnmodifiableFloatFloatMap>(m);
   }

    static TFloatIntMap unmodifiableMap(TFloatIntMap m) {
      return std::make_shared<TUnmodifiableFloatIntMap>(m);
   }

    static TFloatLongMap unmodifiableMap(TFloatLongMap m) {
      return std::make_shared<TUnmodifiableFloatLongMap>(m);
   }

    static TFloatByteMap unmodifiableMap(TFloatByteMap m) {
      return std::make_shared<TUnmodifiableFloatByteMap>(m);
   }

    static TFloatShortMap unmodifiableMap(TFloatShortMap m) {
      return std::make_shared<TUnmodifiableFloatShortMap>(m);
   }

    static TFloatCharMap unmodifiableMap(TFloatCharMap m) {
      return std::make_shared<TUnmodifiableFloatCharMap>(m);
   }

    static TIntDoubleMap unmodifiableMap(TIntDoubleMap m) {
      return std::make_shared<TUnmodifiableIntDoubleMap>(m);
   }

    static TIntFloatMap unmodifiableMap(TIntFloatMap m) {
      return std::make_shared<TUnmodifiableIntFloatMap>(m);
   }

    static TIntIntMap unmodifiableMap(TIntIntMap m) {
      return std::make_shared<TUnmodifiableIntIntMap>(m);
   }

    static TIntLongMap unmodifiableMap(TIntLongMap m) {
      return std::make_shared<TUnmodifiableIntLongMap>(m);
   }

    static TIntByteMap unmodifiableMap(TIntByteMap m) {
      return std::make_shared<TUnmodifiableIntByteMap>(m);
   }

    static TIntShortMap unmodifiableMap(TIntShortMap m) {
      return std::make_shared<TUnmodifiableIntShortMap>(m);
   }

    static TIntCharMap unmodifiableMap(TIntCharMap m) {
      return std::make_shared<TUnmodifiableIntCharMap>(m);
   }

    static TLongDoubleMap unmodifiableMap(TLongDoubleMap m) {
      return std::make_shared<TUnmodifiableLongDoubleMap>(m);
   }

    static TLongFloatMap unmodifiableMap(TLongFloatMap m) {
      return std::make_shared<TUnmodifiableLongFloatMap>(m);
   }

    static TLongIntMap unmodifiableMap(TLongIntMap m) {
      return std::make_shared<TUnmodifiableLongIntMap>(m);
   }

    static TLongLongMap unmodifiableMap(TLongLongMap m) {
      return std::make_shared<TUnmodifiableLongLongMap>(m);
   }

    static TLongByteMap unmodifiableMap(TLongByteMap m) {
      return std::make_shared<TUnmodifiableLongByteMap>(m);
   }

    static TLongShortMap unmodifiableMap(TLongShortMap m) {
      return std::make_shared<TUnmodifiableLongShortMap>(m);
   }

    static TLongCharMap unmodifiableMap(TLongCharMap m) {
      return std::make_shared<TUnmodifiableLongCharMap>(m);
   }

    static TByteDoubleMap unmodifiableMap(TByteDoubleMap m) {
      return std::make_shared<TUnmodifiableByteDoubleMap>(m);
   }

    static TByteFloatMap unmodifiableMap(TByteFloatMap m) {
      return std::make_shared<TUnmodifiableByteFloatMap>(m);
   }

    static TByteIntMap unmodifiableMap(TByteIntMap m) {
      return std::make_shared<TUnmodifiableByteIntMap>(m);
   }

    static TByteLongMap unmodifiableMap(TByteLongMap m) {
      return std::make_shared<TUnmodifiableByteLongMap>(m);
   }

    static TByteByteMap unmodifiableMap(TByteByteMap m) {
      return std::make_shared<TUnmodifiableByteByteMap>(m);
   }

    static TByteShortMap unmodifiableMap(TByteShortMap m) {
      return std::make_shared<TUnmodifiableByteShortMap>(m);
   }

    static TByteCharMap unmodifiableMap(TByteCharMap m) {
      return std::make_shared<TUnmodifiableByteCharMap>(m);
   }

    static TShortDoubleMap unmodifiableMap(TShortDoubleMap m) {
      return std::make_shared<TUnmodifiableShortDoubleMap>(m);
   }

    static TShortFloatMap unmodifiableMap(TShortFloatMap m) {
      return std::make_shared<TUnmodifiableShortFloatMap>(m);
   }

    static TShortIntMap unmodifiableMap(TShortIntMap m) {
      return std::make_shared<TUnmodifiableShortIntMap>(m);
   }

    static TShortLongMap unmodifiableMap(TShortLongMap m) {
      return std::make_shared<TUnmodifiableShortLongMap>(m);
   }

    static TShortByteMap unmodifiableMap(TShortByteMap m) {
      return std::make_shared<TUnmodifiableShortByteMap>(m);
   }

    static TShortShortMap unmodifiableMap(TShortShortMap m) {
      return std::make_shared<TUnmodifiableShortShortMap>(m);
   }

    static TShortCharMap unmodifiableMap(TShortCharMap m) {
      return std::make_shared<TUnmodifiableShortCharMap>(m);
   }

    static TCharDoubleMap unmodifiableMap(TCharDoubleMap m) {
      return std::make_shared<TUnmodifiableCharDoubleMap>(m);
   }

    static TCharFloatMap unmodifiableMap(TCharFloatMap m) {
      return std::make_shared<TUnmodifiableCharFloatMap>(m);
   }

    static TCharIntMap unmodifiableMap(TCharIntMap m) {
      return std::make_shared<TUnmodifiableCharIntMap>(m);
   }

    static TCharLongMap unmodifiableMap(TCharLongMap m) {
      return std::make_shared<TUnmodifiableCharLongMap>(m);
   }

    static TCharByteMap unmodifiableMap(TCharByteMap m) {
      return std::make_shared<TUnmodifiableCharByteMap>(m);
   }

    static TCharShortMap unmodifiableMap(TCharShortMap m) {
      return std::make_shared<TUnmodifiableCharShortMap>(m);
   }

    static TCharCharMap unmodifiableMap(TCharCharMap m) {
      return std::make_shared<TUnmodifiableCharCharMap>(m);
   }

   public static <V> TDoubleObjectMap<V> unmodifiableMap(TDoubleObjectMap<V> m) {
      return std::make_shared<TUnmodifiableDoubleObjectMap>(m);
   }

   public static <V> TFloatObjectMap<V> unmodifiableMap(TFloatObjectMap<V> m) {
      return std::make_shared<TUnmodifiableFloatObjectMap>(m);
   }

   public static <V> TIntObjectMap<V> unmodifiableMap(TIntObjectMap<V> m) {
      return std::make_shared<TUnmodifiableIntObjectMap>(m);
   }

   public static <V> TLongObjectMap<V> unmodifiableMap(TLongObjectMap<V> m) {
      return std::make_shared<TUnmodifiableLongObjectMap>(m);
   }

   public static <V> TByteObjectMap<V> unmodifiableMap(TByteObjectMap<V> m) {
      return std::make_shared<TUnmodifiableByteObjectMap>(m);
   }

   public static <V> TShortObjectMap<V> unmodifiableMap(TShortObjectMap<V> m) {
      return std::make_shared<TUnmodifiableShortObjectMap>(m);
   }

   public static <V> TCharObjectMap<V> unmodifiableMap(TCharObjectMap<V> m) {
      return std::make_shared<TUnmodifiableCharObjectMap>(m);
   }

   public static <K> TObjectDoubleMap<K> unmodifiableMap(TObjectDoubleMap<K> m) {
      return std::make_shared<TUnmodifiableObjectDoubleMap>(m);
   }

   public static <K> TObjectFloatMap<K> unmodifiableMap(TObjectFloatMap<K> m) {
      return std::make_shared<TUnmodifiableObjectFloatMap>(m);
   }

   public static <K> TObjectIntMap<K> unmodifiableMap(TObjectIntMap<K> m) {
      return std::make_shared<TUnmodifiableObjectIntMap>(m);
   }

   public static <K> TObjectLongMap<K> unmodifiableMap(TObjectLongMap<K> m) {
      return std::make_shared<TUnmodifiableObjectLongMap>(m);
   }

   public static <K> TObjectByteMap<K> unmodifiableMap(TObjectByteMap<K> m) {
      return std::make_shared<TUnmodifiableObjectByteMap>(m);
   }

   public static <K> TObjectShortMap<K> unmodifiableMap(TObjectShortMap<K> m) {
      return std::make_shared<TUnmodifiableObjectShortMap>(m);
   }

   public static <K> TObjectCharMap<K> unmodifiableMap(TObjectCharMap<K> m) {
      return std::make_shared<TUnmodifiableObjectCharMap>(m);
   }

    static TDoubleCollection synchronizedCollection(TDoubleCollection c) {
      return std::make_shared<TSynchronizedDoubleCollection>(c);
   }

    static TDoubleCollection synchronizedCollection(TDoubleCollection c, void* mutex) {
      return std::make_shared<TSynchronizedDoubleCollection>(c, mutex);
   }

    static TFloatCollection synchronizedCollection(TFloatCollection c) {
      return std::make_shared<TSynchronizedFloatCollection>(c);
   }

    static TFloatCollection synchronizedCollection(TFloatCollection c, void* mutex) {
      return std::make_shared<TSynchronizedFloatCollection>(c, mutex);
   }

    static TIntCollection synchronizedCollection(TIntCollection c) {
      return std::make_shared<TSynchronizedIntCollection>(c);
   }

    static TIntCollection synchronizedCollection(TIntCollection c, void* mutex) {
      return std::make_shared<TSynchronizedIntCollection>(c, mutex);
   }

    static TLongCollection synchronizedCollection(TLongCollection c) {
      return std::make_shared<TSynchronizedLongCollection>(c);
   }

    static TLongCollection synchronizedCollection(TLongCollection c, void* mutex) {
      return std::make_shared<TSynchronizedLongCollection>(c, mutex);
   }

    static TByteCollection synchronizedCollection(TByteCollection c) {
      return std::make_shared<TSynchronizedByteCollection>(c);
   }

    static TByteCollection synchronizedCollection(TByteCollection c, void* mutex) {
      return std::make_shared<TSynchronizedByteCollection>(c, mutex);
   }

    static TShortCollection synchronizedCollection(TShortCollection c) {
      return std::make_shared<TSynchronizedShortCollection>(c);
   }

    static TShortCollection synchronizedCollection(TShortCollection c, void* mutex) {
      return std::make_shared<TSynchronizedShortCollection>(c, mutex);
   }

    static TCharCollection synchronizedCollection(TCharCollection c) {
      return std::make_shared<TSynchronizedCharCollection>(c);
   }

    static TCharCollection synchronizedCollection(TCharCollection c, void* mutex) {
      return std::make_shared<TSynchronizedCharCollection>(c, mutex);
   }

    static TDoubleSet synchronizedSet(TDoubleSet s) {
      return std::make_shared<TSynchronizedDoubleSet>(s);
   }

    static TDoubleSet synchronizedSet(TDoubleSet s, void* mutex) {
      return std::make_shared<TSynchronizedDoubleSet>(s, mutex);
   }

    static TFloatSet synchronizedSet(TFloatSet s) {
      return std::make_shared<TSynchronizedFloatSet>(s);
   }

    static TFloatSet synchronizedSet(TFloatSet s, void* mutex) {
      return std::make_shared<TSynchronizedFloatSet>(s, mutex);
   }

    static TIntSet synchronizedSet(TIntSet s) {
      return std::make_shared<TSynchronizedIntSet>(s);
   }

    static TIntSet synchronizedSet(TIntSet s, void* mutex) {
      return std::make_shared<TSynchronizedIntSet>(s, mutex);
   }

    static TLongSet synchronizedSet(TLongSet s) {
      return std::make_shared<TSynchronizedLongSet>(s);
   }

    static TLongSet synchronizedSet(TLongSet s, void* mutex) {
      return std::make_shared<TSynchronizedLongSet>(s, mutex);
   }

    static TByteSet synchronizedSet(TByteSet s) {
      return std::make_shared<TSynchronizedByteSet>(s);
   }

    static TByteSet synchronizedSet(TByteSet s, void* mutex) {
      return std::make_shared<TSynchronizedByteSet>(s, mutex);
   }

    static TShortSet synchronizedSet(TShortSet s) {
      return std::make_shared<TSynchronizedShortSet>(s);
   }

    static TShortSet synchronizedSet(TShortSet s, void* mutex) {
      return std::make_shared<TSynchronizedShortSet>(s, mutex);
   }

    static TCharSet synchronizedSet(TCharSet s) {
      return std::make_shared<TSynchronizedCharSet>(s);
   }

    static TCharSet synchronizedSet(TCharSet s, void* mutex) {
      return std::make_shared<TSynchronizedCharSet>(s, mutex);
   }

    static TDoubleList synchronizedList(TDoubleList list) {
      return (TDoubleList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessDoubleList>(list) : std::make_shared<TSynchronizedDoubleList>(list));
   }

    static TDoubleList synchronizedList(TDoubleList list, void* mutex) {
      return (TDoubleList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessDoubleList>(list, mutex) : std::make_shared<TSynchronizedDoubleList>(list, mutex));
   }

    static TFloatList synchronizedList(TFloatList list) {
      return (TFloatList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessFloatList>(list) : std::make_shared<TSynchronizedFloatList>(list));
   }

    static TFloatList synchronizedList(TFloatList list, void* mutex) {
      return (TFloatList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessFloatList>(list, mutex) : std::make_shared<TSynchronizedFloatList>(list, mutex));
   }

    static TIntList synchronizedList(TIntList list) {
      return (TIntList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessIntList>(list) : std::make_shared<TSynchronizedIntList>(list));
   }

    static TIntList synchronizedList(TIntList list, void* mutex) {
      return (TIntList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessIntList>(list, mutex) : std::make_shared<TSynchronizedIntList>(list, mutex));
   }

    static TLongList synchronizedList(TLongList list) {
      return (TLongList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessLongList>(list) : std::make_shared<TSynchronizedLongList>(list));
   }

    static TLongList synchronizedList(TLongList list, void* mutex) {
      return (TLongList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessLongList>(list, mutex) : std::make_shared<TSynchronizedLongList>(list, mutex));
   }

    static TByteList synchronizedList(TByteList list) {
      return (TByteList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessByteList>(list) : std::make_shared<TSynchronizedByteList>(list));
   }

    static TByteList synchronizedList(TByteList list, void* mutex) {
      return (TByteList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessByteList>(list, mutex) : std::make_shared<TSynchronizedByteList>(list, mutex));
   }

    static TShortList synchronizedList(TShortList list) {
      return (TShortList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessShortList>(list) : std::make_shared<TSynchronizedShortList>(list));
   }

    static TShortList synchronizedList(TShortList list, void* mutex) {
      return (TShortList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessShortList>(list, mutex) : std::make_shared<TSynchronizedShortList>(list, mutex));
   }

    static TCharList synchronizedList(TCharList list) {
      return (TCharList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessCharList>(list) : std::make_shared<TSynchronizedCharList>(list));
   }

    static TCharList synchronizedList(TCharList list, void* mutex) {
      return (TCharList)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessCharList>(list, mutex) : std::make_shared<TSynchronizedCharList>(list, mutex));
   }

    static TDoubleDoubleMap synchronizedMap(TDoubleDoubleMap m) {
      return std::make_shared<TSynchronizedDoubleDoubleMap>(m);
   }

    static TDoubleFloatMap synchronizedMap(TDoubleFloatMap m) {
      return std::make_shared<TSynchronizedDoubleFloatMap>(m);
   }

    static TDoubleIntMap synchronizedMap(TDoubleIntMap m) {
      return std::make_shared<TSynchronizedDoubleIntMap>(m);
   }

    static TDoubleLongMap synchronizedMap(TDoubleLongMap m) {
      return std::make_shared<TSynchronizedDoubleLongMap>(m);
   }

    static TDoubleByteMap synchronizedMap(TDoubleByteMap m) {
      return std::make_shared<TSynchronizedDoubleByteMap>(m);
   }

    static TDoubleShortMap synchronizedMap(TDoubleShortMap m) {
      return std::make_shared<TSynchronizedDoubleShortMap>(m);
   }

    static TDoubleCharMap synchronizedMap(TDoubleCharMap m) {
      return std::make_shared<TSynchronizedDoubleCharMap>(m);
   }

    static TFloatDoubleMap synchronizedMap(TFloatDoubleMap m) {
      return std::make_shared<TSynchronizedFloatDoubleMap>(m);
   }

    static TFloatFloatMap synchronizedMap(TFloatFloatMap m) {
      return std::make_shared<TSynchronizedFloatFloatMap>(m);
   }

    static TFloatIntMap synchronizedMap(TFloatIntMap m) {
      return std::make_shared<TSynchronizedFloatIntMap>(m);
   }

    static TFloatLongMap synchronizedMap(TFloatLongMap m) {
      return std::make_shared<TSynchronizedFloatLongMap>(m);
   }

    static TFloatByteMap synchronizedMap(TFloatByteMap m) {
      return std::make_shared<TSynchronizedFloatByteMap>(m);
   }

    static TFloatShortMap synchronizedMap(TFloatShortMap m) {
      return std::make_shared<TSynchronizedFloatShortMap>(m);
   }

    static TFloatCharMap synchronizedMap(TFloatCharMap m) {
      return std::make_shared<TSynchronizedFloatCharMap>(m);
   }

    static TIntDoubleMap synchronizedMap(TIntDoubleMap m) {
      return std::make_shared<TSynchronizedIntDoubleMap>(m);
   }

    static TIntFloatMap synchronizedMap(TIntFloatMap m) {
      return std::make_shared<TSynchronizedIntFloatMap>(m);
   }

    static TIntIntMap synchronizedMap(TIntIntMap m) {
      return std::make_shared<TSynchronizedIntIntMap>(m);
   }

    static TIntLongMap synchronizedMap(TIntLongMap m) {
      return std::make_shared<TSynchronizedIntLongMap>(m);
   }

    static TIntByteMap synchronizedMap(TIntByteMap m) {
      return std::make_shared<TSynchronizedIntByteMap>(m);
   }

    static TIntShortMap synchronizedMap(TIntShortMap m) {
      return std::make_shared<TSynchronizedIntShortMap>(m);
   }

    static TIntCharMap synchronizedMap(TIntCharMap m) {
      return std::make_shared<TSynchronizedIntCharMap>(m);
   }

    static TLongDoubleMap synchronizedMap(TLongDoubleMap m) {
      return std::make_shared<TSynchronizedLongDoubleMap>(m);
   }

    static TLongFloatMap synchronizedMap(TLongFloatMap m) {
      return std::make_shared<TSynchronizedLongFloatMap>(m);
   }

    static TLongIntMap synchronizedMap(TLongIntMap m) {
      return std::make_shared<TSynchronizedLongIntMap>(m);
   }

    static TLongLongMap synchronizedMap(TLongLongMap m) {
      return std::make_shared<TSynchronizedLongLongMap>(m);
   }

    static TLongByteMap synchronizedMap(TLongByteMap m) {
      return std::make_shared<TSynchronizedLongByteMap>(m);
   }

    static TLongShortMap synchronizedMap(TLongShortMap m) {
      return std::make_shared<TSynchronizedLongShortMap>(m);
   }

    static TLongCharMap synchronizedMap(TLongCharMap m) {
      return std::make_shared<TSynchronizedLongCharMap>(m);
   }

    static TByteDoubleMap synchronizedMap(TByteDoubleMap m) {
      return std::make_shared<TSynchronizedByteDoubleMap>(m);
   }

    static TByteFloatMap synchronizedMap(TByteFloatMap m) {
      return std::make_shared<TSynchronizedByteFloatMap>(m);
   }

    static TByteIntMap synchronizedMap(TByteIntMap m) {
      return std::make_shared<TSynchronizedByteIntMap>(m);
   }

    static TByteLongMap synchronizedMap(TByteLongMap m) {
      return std::make_shared<TSynchronizedByteLongMap>(m);
   }

    static TByteByteMap synchronizedMap(TByteByteMap m) {
      return std::make_shared<TSynchronizedByteByteMap>(m);
   }

    static TByteShortMap synchronizedMap(TByteShortMap m) {
      return std::make_shared<TSynchronizedByteShortMap>(m);
   }

    static TByteCharMap synchronizedMap(TByteCharMap m) {
      return std::make_shared<TSynchronizedByteCharMap>(m);
   }

    static TShortDoubleMap synchronizedMap(TShortDoubleMap m) {
      return std::make_shared<TSynchronizedShortDoubleMap>(m);
   }

    static TShortFloatMap synchronizedMap(TShortFloatMap m) {
      return std::make_shared<TSynchronizedShortFloatMap>(m);
   }

    static TShortIntMap synchronizedMap(TShortIntMap m) {
      return std::make_shared<TSynchronizedShortIntMap>(m);
   }

    static TShortLongMap synchronizedMap(TShortLongMap m) {
      return std::make_shared<TSynchronizedShortLongMap>(m);
   }

    static TShortByteMap synchronizedMap(TShortByteMap m) {
      return std::make_shared<TSynchronizedShortByteMap>(m);
   }

    static TShortShortMap synchronizedMap(TShortShortMap m) {
      return std::make_shared<TSynchronizedShortShortMap>(m);
   }

    static TShortCharMap synchronizedMap(TShortCharMap m) {
      return std::make_shared<TSynchronizedShortCharMap>(m);
   }

    static TCharDoubleMap synchronizedMap(TCharDoubleMap m) {
      return std::make_shared<TSynchronizedCharDoubleMap>(m);
   }

    static TCharFloatMap synchronizedMap(TCharFloatMap m) {
      return std::make_shared<TSynchronizedCharFloatMap>(m);
   }

    static TCharIntMap synchronizedMap(TCharIntMap m) {
      return std::make_shared<TSynchronizedCharIntMap>(m);
   }

    static TCharLongMap synchronizedMap(TCharLongMap m) {
      return std::make_shared<TSynchronizedCharLongMap>(m);
   }

    static TCharByteMap synchronizedMap(TCharByteMap m) {
      return std::make_shared<TSynchronizedCharByteMap>(m);
   }

    static TCharShortMap synchronizedMap(TCharShortMap m) {
      return std::make_shared<TSynchronizedCharShortMap>(m);
   }

    static TCharCharMap synchronizedMap(TCharCharMap m) {
      return std::make_shared<TSynchronizedCharCharMap>(m);
   }

   public static <V> TDoubleObjectMap<V> synchronizedMap(TDoubleObjectMap<V> m) {
      return std::make_shared<TSynchronizedDoubleObjectMap>(m);
   }

   public static <V> TFloatObjectMap<V> synchronizedMap(TFloatObjectMap<V> m) {
      return std::make_shared<TSynchronizedFloatObjectMap>(m);
   }

   public static <V> TIntObjectMap<V> synchronizedMap(TIntObjectMap<V> m) {
      return std::make_shared<TSynchronizedIntObjectMap>(m);
   }

   public static <V> TLongObjectMap<V> synchronizedMap(TLongObjectMap<V> m) {
      return std::make_shared<TSynchronizedLongObjectMap>(m);
   }

   public static <V> TByteObjectMap<V> synchronizedMap(TByteObjectMap<V> m) {
      return std::make_shared<TSynchronizedByteObjectMap>(m);
   }

   public static <V> TShortObjectMap<V> synchronizedMap(TShortObjectMap<V> m) {
      return std::make_shared<TSynchronizedShortObjectMap>(m);
   }

   public static <V> TCharObjectMap<V> synchronizedMap(TCharObjectMap<V> m) {
      return std::make_shared<TSynchronizedCharObjectMap>(m);
   }

   public static <K> TObjectDoubleMap<K> synchronizedMap(TObjectDoubleMap<K> m) {
      return std::make_shared<TSynchronizedObjectDoubleMap>(m);
   }

   public static <K> TObjectFloatMap<K> synchronizedMap(TObjectFloatMap<K> m) {
      return std::make_shared<TSynchronizedObjectFloatMap>(m);
   }

   public static <K> TObjectIntMap<K> synchronizedMap(TObjectIntMap<K> m) {
      return std::make_shared<TSynchronizedObjectIntMap>(m);
   }

   public static <K> TObjectLongMap<K> synchronizedMap(TObjectLongMap<K> m) {
      return std::make_shared<TSynchronizedObjectLongMap>(m);
   }

   public static <K> TObjectByteMap<K> synchronizedMap(TObjectByteMap<K> m) {
      return std::make_shared<TSynchronizedObjectByteMap>(m);
   }

   public static <K> TObjectShortMap<K> synchronizedMap(TObjectShortMap<K> m) {
      return std::make_shared<TSynchronizedObjectShortMap>(m);
   }

   public static <K> TObjectCharMap<K> synchronizedMap(TObjectCharMap<K> m) {
      return std::make_shared<TSynchronizedObjectCharMap>(m);
   }
}
} // namespace trove
} // namespace gnu
