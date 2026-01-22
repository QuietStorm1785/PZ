#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/async/utils/AsyncIdleConnectionMonitorThread.h"
#include "com/mashape/unirest/http/utils/SyncIdleConnectionMonitorThread.h"
#include "org/apache/http/HttpHost.h"
#include "org/apache/http/client/config/RequestConfig.h"
#include "org/apache/http/impl/client/HttpClientBuilder.h"
#include "org/apache/http/impl/conn/PoolingHttpClientConnectionManager.h"
#include "org/apache/http/impl/nio/client/CloseableHttpAsyncClient.h"
#include "org/apache/http/impl/nio/client/HttpAsyncClientBuilder.h"
#include "org/apache/http/impl/nio/conn/PoolingNHttpClientConnectionManager.h"
#include "org/apache/http/impl/nio/reactor/DefaultConnectingIOReactor.h"
#include "org/apache/http/nio/reactor/IOReactorException.h"

namespace com {
namespace mashape {
namespace unirest {
namespace http {
namespace options {


class Options {
public:
    static const long CONNECTION_TIMEOUT = 10000L;
    static const long SOCKET_TIMEOUT = 60000L;
    static const int MAX_TOTAL = 200;
    static const int MAX_PER_ROUTE = 20;
   private static Map<Option, Object> options = std::make_unique<std::unordered_map<>>();
    static bool customClientSet = false;

    static void customClientSet() {
      customClientSet = true;
   }

    static void setOption(Option option, void* value) {
      if ((option == Option.CONNECTION_TIMEOUT || option == Option.SOCKET_TIMEOUT) && customClientSet) {
         throw RuntimeException(
            "You can't set custom timeouts when providing custom client implementations. Set the timeouts directly in your custom client configuration instead."
         );
      } else {
         options.put(option, value);
      }
   }

    static void* getOption(Option option) {
      return options.get(option);
   }

    static void refresh() {
    void* connectionTimeout = getOption(Option.CONNECTION_TIMEOUT);
      if (connectionTimeout == nullptr) {
         connectionTimeout = 10000L;
      }

    void* socketTimeout = getOption(Option.SOCKET_TIMEOUT);
      if (socketTimeout == nullptr) {
         socketTimeout = 60000L;
      }

    void* maxTotal = getOption(Option.MAX_TOTAL);
      if (maxTotal == nullptr) {
         maxTotal = 200;
      }

    void* maxPerRoute = getOption(Option.MAX_PER_ROUTE);
      if (maxPerRoute == nullptr) {
         maxPerRoute = 20;
      }

    HttpHost proxy = (HttpHost)getOption(Option.PROXY);
      RequestConfig clientConfig = RequestConfig.custom()
         .setConnectTimeout(((int64_t)connectionTimeout).intValue())
         .setSocketTimeout(((int64_t)socketTimeout).intValue())
         .setConnectionRequestTimeout(((int64_t)socketTimeout).intValue())
         .setProxy(proxy)
         .build();
    PoolingHttpClientConnectionManager syncConnectionManager = std::make_shared<PoolingHttpClientConnectionManager>();
      syncConnectionManager.setMaxTotal((int)maxTotal);
      syncConnectionManager.setDefaultMaxPerRoute((int)maxPerRoute);
      setOption(Option.HTTPCLIENT, HttpClientBuilder.create().setDefaultRequestConfig(clientConfig).setConnectionManager(syncConnectionManager).build());
    SyncIdleConnectionMonitorThread syncIdleConnectionMonitorThread = std::make_shared<SyncIdleConnectionMonitorThread>(syncConnectionManager);
      setOption(Option.SYNC_MONITOR, syncIdleConnectionMonitorThread);
      syncIdleConnectionMonitorThread.start();

    PoolingNHttpClientConnectionManager asyncConnectionManager;
      try {
    DefaultConnectingIOReactor ioreactor = std::make_shared<DefaultConnectingIOReactor>();
         asyncConnectionManager = std::make_shared<PoolingNHttpClientConnectionManager>(ioreactor);
         asyncConnectionManager.setMaxTotal((int)maxTotal);
         asyncConnectionManager.setDefaultMaxPerRoute((int)maxPerRoute);
      } catch (IOReactorException var11) {
         throw RuntimeException(var11);
      }

      CloseableHttpAsyncClient asyncClient = HttpAsyncClientBuilder.create()
         .setDefaultRequestConfig(clientConfig)
         .setConnectionManager(asyncConnectionManager)
         .build();
      setOption(Option.ASYNCHTTPCLIENT, asyncClient);
      setOption(Option.ASYNC_MONITOR, std::make_shared<AsyncIdleConnectionMonitorThread>(asyncConnectionManager));
   }

   static {
      refresh();
   }
}
} // namespace options
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
