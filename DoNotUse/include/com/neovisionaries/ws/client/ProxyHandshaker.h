#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/Socket.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class ProxyHandshaker {
public:
    static const std::string RN = "\r\n";
    const Socket mSocket;
    const std::string mHost;
    const int mPort;
    const ProxySettings mSettings;

    public ProxyHandshaker(Socket socket, const std::string& host, int port, ProxySettings settings) {
      this.mSocket = socket;
      this.mHost = host;
      this.mPort = port;
      this.mSettings = settings;
   }

    void perform() {
      this.sendRequest();
      this.receiveResponse();
   }

    void sendRequest() {
    std::string request = this.buildRequest();
      byte[] requestBytes = Misc.getBytesUTF8(request);
    OutputStream output = this.mSocket.getOutputStream();
      output.write(requestBytes);
      output.flush();
   }

    std::string buildRequest() {
    std::string host = std::string.format("%s:%d", this.mHost, this.mPort);
      std::stringstream builder = std::make_unique<std::stringstream>()
         .append("CONNECT ")
         .append(host)
         .append(" HTTP/1.1")
         .append("\r\n")
         .append("Host: ")
         .append(host)
         .append("\r\n");
      this.addHeaders(builder);
      this.addProxyAuthorization(builder);
      return builder.append("\r\n");
   }

    void addHeaders(std::stringstream builder) {
      for (Entry<std::string, List<std::string>> header : this.mSettings.getHeaders().entrySet()) {
    std::string name = header.getKey();

         for (std::string value : header.getValue()) {
            if (value == nullptr) {
               value = "";
            }

            builder.append(name).append(": ").append(value).append("\r\n");
         }
      }
   }

    void addProxyAuthorization(std::stringstream builder) {
    std::string id = this.mSettings.getId();
      if (id != nullptr && id.length() != 0) {
    std::string password = this.mSettings.getPassword();
         if (password == nullptr) {
            password = "";
         }

    std::string credentials = std::string.format("%s:%s", id, password);
         builder.append("Proxy-Authorization: Basic ").append(Base64.encode(credentials)).append("\r\n");
      }
   }

    void receiveResponse() {
    InputStream input = this.mSocket.getInputStream();
      this.readStatusLine(input);
      this.skipHeaders(input);
   }

    void readStatusLine(InputStream input) {
    std::string statusLine = Misc.readLine(input, "UTF-8");
      if (statusLine != nullptr && statusLine.length() != 0) {
         std::string[] elements = statusLine.split(" +", 3);
         if (elements.length < 2) {
            throw IOException("The status line in the response from the proxy server is badly formatted. The status line is: " + statusLine);
         } else if (!"200" == elements[1])) {
            throw IOException(
               "The status code in the response from the proxy server is not '200 Connection established'. The status line is: " + statusLine
            );
         }
      } else {
         throw IOException("The response from the proxy server does not contain a status line.");
      }
   }

    void skipHeaders(InputStream input) {
    int count = 0;

      while (true) {
    int ch = input.read();
         if (ch == -1) {
            throw EOFException("The end of the stream from the proxy server was reached unexpectedly.");
         }

         if (ch == 10) {
            if (count == 0) {
               return;
            }

            count = 0;
         } else if (ch != 13) {
            count++;
         } else {
            ch = input.read();
            if (ch == -1) {
               throw EOFException("The end of the stream from the proxy server was reached unexpectedly after a carriage return.");
            }

            if (ch != 10) {
               count += 2;
            } else {
               if (count == 0) {
                  return;
               }

               count = 0;
            }
         }
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
