#pragma once
#include "org/junit/Assert.h"
#include "org/junit/Before.h"
#include "org/junit/BeforeClass.h"
#include "org/junit/Test.h"
#include "zombie/core/Rand.h"
#include "zombie/core/raknet/UdpConnection.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class MPStatisticsTest {
public:
  UdpConnection connection;
  const long limit = 200L;

  static void init() {
    Rand.init();
    ServerOptions.instance.init();
  }

  void reset() {
    ServerOptions.instance.PingLimit.setValue(200);
    this.connection = new UdpConnection(nullptr, 0L, 0);
    MPStatistics.pingIntervalCount = 10L;
    MPStatistics.pingLimitCount = 0L;
    MPStatistics.maxPingToSum = 400L;
  }

  void TestAveragePingIsGreaterThanLimit() {
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(201L, long0);
    Assert.assertTrue(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestAveragePingIsLessThanLimit() {
    this.connection.pingHistory.addFirst(199L);
    this.connection.pingHistory.addFirst(199L);
    this.connection.pingHistory.addFirst(199L);
    this.connection.pingHistory.addFirst(199L);
    this.connection.pingHistory.addFirst(199L);
    this.connection.pingHistory.addFirst(199L);
    this.connection.pingHistory.addFirst(199L);
    this.connection.pingHistory.addFirst(199L);
    this.connection.pingHistory.addFirst(199L);
    this.connection.pingHistory.addFirst(199L);
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(199L, long0);
    Assert.assertFalse(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestAveragePingIsEqualToLimit() {
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(200L, long0);
    Assert.assertFalse(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestAveragePingIsSlightlyGreaterThanLimit() {
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(201L);
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(201L, long0);
    Assert.assertTrue(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestAveragePingIsSlightlyLessThanLimit() {
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(199L);
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(200L, long0);
    Assert.assertFalse(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestNotEnoughPingIntervals() {
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    MPStatistics.pingIntervalCount = 5L;
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(0L, long0);
    Assert.assertFalse(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestEnoughPingIntervals() {
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    MPStatistics.pingIntervalCount = 5L;
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(201L, long0);
    Assert.assertTrue(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestNotEnoughPingSpikes() {
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    MPStatistics.pingLimitCount = 3L;
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(0L, long0);
    Assert.assertFalse(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestEnoughPingSpikes() {
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    this.connection.pingHistory.addFirst(201L);
    MPStatistics.pingLimitCount = 3L;
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(201L, long0);
    Assert.assertTrue(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestSeveralHugeSpikesDoesNotExceedTheLimit() {
    this.connection.pingHistory.addFirst(10000000L);
    this.connection.pingHistory.addFirst(10000000L);
    this.connection.pingHistory.addFirst(99L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(200L, long0);
    Assert.assertFalse(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestSeveralHugeSpikesEqualToLimit() {
    this.connection.pingHistory.addFirst(10000000L);
    this.connection.pingHistory.addFirst(10000000L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(200L, long0);
    Assert.assertFalse(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestSeveralHugeSpikesExceedTheLimit() {
    this.connection.pingHistory.addFirst(10000000L);
    this.connection.pingHistory.addFirst(10000000L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(200L);
    this.connection.pingHistory.addFirst(201L);
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(201L, long0);
    Assert.assertTrue(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestTheLatestDataIsUsedForCounting() {
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(100L);
    this.connection.pingHistory.addFirst(301L);
    this.connection.pingHistory.removeLast();
    MPStatistics.pingIntervalCount = 2L;
    MPStatistics.pingLimitCount = 1L;
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(201L, MPStatistics.checkLatest(this.connection, 200L));
    Assert.assertTrue(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestKickWhileLoadingWhenKickIsDisabledViaMinValue() {
    this.connection.pingHistory.addFirst(201L);
    MPStatistics.pingIntervalCount = 1L;
    MPStatistics.pingLimitCount = 0L;
    ServerOptions.instance.PingLimit.setValue(
        (int)ServerOptions.instance.PingLimit.getMin());
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(201L, MPStatistics.checkLatest(this.connection, 200L));
    Assert.assertFalse(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestKickWhileLoadingWhenConnectionIsPreferredInQueue() {
    this.connection.pingHistory.addFirst(201L);
    MPStatistics.pingIntervalCount = 1L;
    MPStatistics.pingLimitCount = 0L;
    this.connection.preferredInQueue = true;
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(201L, MPStatistics.checkLatest(this.connection, 200L));
    Assert.assertFalse(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestKickWhileLoadingWhenConnectionIsAdmin() {
    this.connection.pingHistory.addFirst(201L);
    MPStatistics.pingIntervalCount = 1L;
    MPStatistics.pingLimitCount = 0L;
    this.connection.accessLevel = 32;
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(201L, MPStatistics.checkLatest(this.connection, 200L));
    Assert.assertFalse(MPStatistics.doKickWhileLoading(this.connection, long0));
  }

  void TestKick() {
    this.connection.setFullyConnected();
    this.connection.connectionTimestamp -= 120000L;
    this.connection.pingHistory.addFirst(201L);
    MPStatistics.pingIntervalCount = 1L;
    MPStatistics.pingLimitCount = 0L;
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(201L, MPStatistics.checkLatest(this.connection, 200L));
    Assert.assertTrue(MPStatistics.doKick(this.connection, long0));
  }

  void TestKickGraceInterval() {
    this.connection.setFullyConnected();
    this.connection.pingHistory.addFirst(201L);
    MPStatistics.pingIntervalCount = 1L;
    MPStatistics.pingLimitCount = 0L;
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(201L, MPStatistics.checkLatest(this.connection, 200L));
    Assert.assertFalse(MPStatistics.doKick(this.connection, long0));
  }

  void TestKickIsNotFullyConnected() {
    this.connection.connectionTimestamp -= 120000L;
    this.connection.pingHistory.addFirst(201L);
    MPStatistics.pingIntervalCount = 1L;
    MPStatistics.pingLimitCount = 0L;
    long long0 = MPStatistics.checkLatest(this.connection, 200L);
    Assert.assertEquals(201L, MPStatistics.checkLatest(this.connection, 200L));
    Assert.assertFalse(MPStatistics.doKick(this.connection, long0));
  }
}
} // namespace network
} // namespace zombie
