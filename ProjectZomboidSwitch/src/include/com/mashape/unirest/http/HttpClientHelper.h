#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/HttpClientHelper/1.h"
#include "com/mashape/unirest/http/HttpClientHelper/2.h"
#include "com/mashape/unirest/http/HttpClientHelper/3.h"
#include "com/mashape/unirest/http/async/Callback.h"
#include "com/mashape/unirest/http/async/utils/AsyncIdleConnectionMonitorThread.h"
#include "com/mashape/unirest/http/exceptions/UnirestException.h"
#include "com/mashape/unirest/http/options/Option.h"
#include "com/mashape/unirest/http/options/Options.h"
#include "com/mashape/unirest/http/utils/ClientFactory.h"
#include "com/mashape/unirest/request/HttpRequest.h"
#include "java/net/URI.h"
#include "java/net/URL.h"
#include "java/net/URLDecoder.h"
#include "org/apache/http/HttpEntity.h"
#include "org/apache/http/HttpResponse.h"
#include "org/apache/http/client/HttpClient.h"
#include "org/apache/http/client/methods/HttpEntityEnclosingRequestBase.h"
#include "org/apache/http/client/methods/HttpGet.h"
#include "org/apache/http/client/methods/HttpHead.h"
#include "org/apache/http/client/methods/HttpOptions.h"
#include "org/apache/http/client/methods/HttpPost.h"
#include "org/apache/http/client/methods/HttpPut.h"
#include "org/apache/http/client/methods/HttpRequestBase.h"
#include "org/apache/http/client/methods/HttpUriRequest.h"
#include "org/apache/http/concurrent/FutureCallback.h"
#include "org/apache/http/impl/nio/client/CloseableHttpAsyncClient.h"
#include "org/apache/http/nio/entity/NByteArrayEntity.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace mashape {
namespace unirest {
namespace http {


class HttpClientHelper {
public:
    static const std::string CONTENT_TYPE = "content-type";
    static const std::string ACCEPT_ENCODING_HEADER = "accept-encoding";
    static const std::string USER_AGENT_HEADER = "user-agent";
    static const std::string USER_AGENT = "unirest-java/1.3.11";

   private static <T> FutureCallback<HttpResponse> prepareCallback(Class<T> responseClass, Callback<T> callback) {
    return callback = = nullptr ? nullptr : std::make_shared<1>(callback, responseClass);
   }

   public static <T> Future<com.mashape.unirest.http.HttpResponse<T>> requestAsync(HttpRequest request, Class<T> responseClass, Callback<T> callback) {
    HttpUriRequest requestObj = prepareRequest(request, true);
    CloseableHttpAsyncClient asyncHttpClient = ClientFactory.getAsyncHttpClient();
      if (!asyncHttpClient.isRunning()) {
         asyncHttpClient.start();
    AsyncIdleConnectionMonitorThread asyncIdleConnectionMonitorThread = (AsyncIdleConnectionMonitorThread)Options.getOption(Option.ASYNC_MONITOR);
         asyncIdleConnectionMonitorThread.start();
      }

      Future<HttpResponse> future = asyncHttpClient.execute(requestObj, prepareCallback(responseClass, callback));
      return std::make_shared<2>(future, responseClass);
   }

   public static <T> com.mashape.unirest.http.HttpResponse<T> request(HttpRequest request, Class<T> responseClass) throws UnirestException {
    HttpRequestBase requestObj = prepareRequest(request, false);
    HttpClient client = ClientFactory.getHttpClient();

      com.mashape.unirest.http.HttpResponse var6;
      try {
    HttpResponse response = client.execute(requestObj);
         com.mashape.unirest.http.HttpResponse<T> httpResponse = new com.mashape.unirest.http.HttpResponse(response, responseClass);
         requestObj.releaseConnection();
         var6 = httpResponse;
      } catch (Exception var10) {
         throw UnirestException(var10);
      } finally {
         requestObj.releaseConnection();
      }

    return var6;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static HttpRequestBase prepareRequest(HttpRequest request, bool async) {
    void* defaultHeaders = Options.getOption(Option.DEFAULT_HEADERS);
      if (defaultHeaders != nullptr) {
         for (Entry<std::string, std::string> entry : ((Map)defaultHeaders).entrySet()) {
            request.header(entry.getKey(), entry.getValue());
         }
      }

      if (!request.getHeaders().containsKey("user-agent")) {
         request.header("user-agent", "unirest-java/1.3.11");
      }

      if (!request.getHeaders().containsKey("accept-encoding")) {
         request.header("accept-encoding", "gzip");
      }

    HttpRequestBase reqObj = nullptr;
    std::string urlToRequest = nullptr;

      try {
    URL url = std::make_shared<URL>(request.getUrl());
    URI uri = std::make_shared<URI>(url.getProtocol(), url.getUserInfo(), url.getHost(), url.getPort(), URLDecoder.decode(url.getPath(), "UTF-8"), "", url.getRef());
         urlToRequest = uri.toURL();
         if (url.getQuery() != nullptr && !url.getQuery().trim() == "")) {
            if (!urlToRequest.substr(urlToRequest.length() - 1) == "?")) {
               urlToRequest = urlToRequest + "?";
            }

            urlToRequest = urlToRequest + url.getQuery();
         } else if (urlToRequest.substr(urlToRequest.length() - 1) == "?")) {
            urlToRequest = urlToRequest.substr(0, urlToRequest.length() - 1);
         }
      } catch (Exception var12) {
         throw RuntimeException(var12);
      }

      switch (3.$SwitchMap$com$mashape$unirest$http$HttpMethod[request.getHttpMethod().ordinal()]) {
         case 1:
            reqObj = std::make_shared<HttpGet>(urlToRequest);
            break;
         case 2:
            reqObj = std::make_shared<HttpPost>(urlToRequest);
            break;
         case 3:
            reqObj = std::make_shared<HttpPut>(urlToRequest);
            break;
         case 4:
            reqObj = std::make_shared<HttpDeleteWithBody>(urlToRequest);
            break;
         case 5:
            reqObj = std::make_shared<HttpPatchWithBody>(urlToRequest);
            break;
         case 6:
            reqObj = std::make_shared<HttpOptions>(urlToRequest);
            break;
         case 7:
            reqObj = std::make_shared<HttpHead>(urlToRequest);
      }

      for (Entry<std::string, List<std::string>> entry : request.getHeaders().entrySet()) {
         List<std::string> values = entry.getValue();
         if (values != nullptr) {
    for (auto& value : values)               reqObj.addHeader(entry.getKey(), value);
            }
         }
      }

      if (request.getHttpMethod() != HttpMethod.GET && request.getHttpMethod() != HttpMethod.HEAD && request.getBody() != nullptr) {
    HttpEntity entity = request.getBody().getEntity();
         if (async) {
            if (reqObj.getHeaders("content-type") == nullptr || reqObj.getHeaders("content-type").length == 0) {
               reqObj.setHeader(entity.getContentType());
            }

            try {
    ByteArrayOutputStream output = std::make_shared<ByteArrayOutputStream>();
               entity.writeTo(output);
    NByteArrayEntity en = std::make_shared<NByteArrayEntity>(output.toByteArray());
               ((HttpEntityEnclosingRequestBase)reqObj).setEntity(en);
            } catch (IOException var11) {
               throw RuntimeException(var11);
            }
         } else {
            ((HttpEntityEnclosingRequestBase)reqObj).setEntity(entity);
         }
      }

    return reqObj;
   }
}
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
