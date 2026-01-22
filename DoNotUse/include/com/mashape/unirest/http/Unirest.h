#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/async/utils/AsyncIdleConnectionMonitorThread.h"
#include "com/mashape/unirest/http/options/Option.h"
#include "com/mashape/unirest/http/options/Options.h"
#include "com/mashape/unirest/http/utils/SyncIdleConnectionMonitorThread.h"
#include "com/mashape/unirest/request/GetRequest.h"
#include "com/mashape/unirest/request/HttpRequestWithBody.h"
#include "org/apache/http/HttpHost.h"
#include "org/apache/http/client/HttpClient.h"
#include "org/apache/http/impl/client/CloseableHttpClient.h"
#include "org/apache/http/impl/nio/client/CloseableHttpAsyncClient.h"
#include <fstream>
#include <iostream>

namespace com {
namespace mashape {
namespace unirest {
namespace http {


class Unirest {
public:
    static void setHttpClient(HttpClient httpClient) {
      Options.setOption(Option.HTTPCLIENT, httpClient);
      Options.customClientSet();
   }

    static void setAsyncHttpClient(CloseableHttpAsyncClient asyncHttpClient) {
      Options.setOption(Option.ASYNCHTTPCLIENT, asyncHttpClient);
      Options.customClientSet();
   }

    static void setProxy(HttpHost proxy) {
      Options.setOption(Option.PROXY, proxy);
      Options.refresh();
   }

    static void setObjectMapper(ObjectMapper objectMapper) {
      Options.setOption(Option.OBJECT_MAPPER, objectMapper);
      Options.refresh();
   }

    static void setTimeouts(long connectionTimeout, long socketTimeout) {
      Options.setOption(Option.CONNECTION_TIMEOUT, connectionTimeout);
      Options.setOption(Option.SOCKET_TIMEOUT, socketTimeout);
      Options.refresh();
   }

    static void setConcurrency(int maxTotal, int maxPerRoute) {
      Options.setOption(Option.MAX_TOTAL, maxTotal);
      Options.setOption(Option.MAX_PER_ROUTE, maxPerRoute);
      Options.refresh();
   }

    static void clearDefaultHeaders() {
      Options.setOption(Option.DEFAULT_HEADERS, nullptr);
   }

    static void setDefaultHeader(const std::string& name, const std::string& value) {
    void* headers = Options.getOption(Option.DEFAULT_HEADERS);
      if (headers == nullptr) {
         headers = std::make_unique<std::unordered_map>();
      }

      ((Map)headers).put(name, value);
      Options.setOption(Option.DEFAULT_HEADERS, headers);
   }

    static void shutdown() {
    CloseableHttpClient syncClient = (CloseableHttpClient)Options.getOption(Option.HTTPCLIENT);
      if (syncClient != nullptr) {
         syncClient.close();
      }

    SyncIdleConnectionMonitorThread syncIdleConnectionMonitorThread = (SyncIdleConnectionMonitorThread)Options.getOption(Option.SYNC_MONITOR);
      if (syncIdleConnectionMonitorThread != nullptr) {
         syncIdleConnectionMonitorThread.interrupt();
      }

    CloseableHttpAsyncClient asyncClient = (CloseableHttpAsyncClient)Options.getOption(Option.ASYNCHTTPCLIENT);
      if (asyncClient != nullptr && asyncClient.isRunning()) {
         asyncClient.close();
      }

    AsyncIdleConnectionMonitorThread asyncMonitorThread = (AsyncIdleConnectionMonitorThread)Options.getOption(Option.ASYNC_MONITOR);
      if (asyncMonitorThread != nullptr) {
         asyncMonitorThread.interrupt();
      }
   }

    static GetRequest get(const std::string& url) {
      return std::make_shared<GetRequest>(HttpMethod.GET, url);
   }

    static GetRequest head(const std::string& url) {
      return std::make_shared<GetRequest>(HttpMethod.HEAD, url);
   }

    static HttpRequestWithBody options(const std::string& url) {
      return std::make_shared<HttpRequestWithBody>(HttpMethod.OPTIONS, url);
   }

    static HttpRequestWithBody post(const std::string& url) {
      return std::make_shared<HttpRequestWithBody>(HttpMethod.POST, url);
   }

    static HttpRequestWithBody delete(const std::string& url) {
      return std::make_shared<HttpRequestWithBody>(HttpMethod.DELETE, url);
   }

    static HttpRequestWithBody patch(const std::string& url) {
      return std::make_shared<HttpRequestWithBody>(HttpMethod.PATCH, url);
   }

    static HttpRequestWithBody put(const std::string& url) {
      return std::make_shared<HttpRequestWithBody>(HttpMethod.PUT, url);
   }
}
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
