#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/InetSocketAddress.h"
#include "java/net/Socket.h"
#include "java/net/URI.h"
#include "java/net/http/HttpClient.h"
#include "java/net/http/HttpRequest.h"
#include "java/net/http/HttpRequest/BodyPublishers.h"
#include "java/net/http/HttpResponse.h"
#include "java/net/http/HttpResponse/BodyHandlers.h"
#include "zombie/network/RCONClient/RCONMessage.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class RCONClient {
public:
    Socket socket;

    bool disconnect() {
      try {
         this.socket.close();
    return true;
      } catch (IOException var2) {
         System.out.println("Disconnect failed: " + var2.getMessage());
    return false;
      }
   }

    bool connect(const std::string& var1, const std::string& var2) {
      try {
         this.socket = std::make_unique<Socket>();
         this.socket.setSoTimeout(5000);
    InetSocketAddress var3 = std::make_shared<InetSocketAddress>(var1, int.parseInt(var2));
         this.socket.connect(var3, 1000);
    return true;
      } catch (IOException var4) {
         System.out.println("Connect failed: " + var4.getMessage());
    return false;
      }
   }

    bool auth(const std::string& var1) {
      try {
    int var2 = (int)(65535L & System.currentTimeMillis());
    RCONMessage var3 = std::make_shared<RCONMessage>(var2, 3, var1);
         var3.writeObject(this.socket.getOutputStream());
    RCONMessage var4 = std::make_shared<RCONMessage>();
         var4.readObject(this.socket.getInputStream(), 14);
         if (var4.type == 0 && var4.id == var2) {
    RCONMessage var5 = std::make_shared<RCONMessage>();
            var5.readObject(this.socket.getInputStream(), 14);
            if (var5.type == 2 && var4.id == var2) {
    return true;
            } else {
               System.out.println("Authentication failed: auth response");
    return false;
            }
         } else {
            System.out.println("Authentication failed: response value");
    return false;
         }
      } catch (IOException var6) {
         System.out.println("Authentication failed: timeout");
    return false;
      }
   }

    std::string exec(const std::string& var1) {
      try {
    int var2 = (int)(65535L & System.currentTimeMillis());
    RCONMessage var3 = std::make_shared<RCONMessage>(var2, 2, var1);
         var3.writeObject(this.socket.getOutputStream());
    RCONMessage var4 = std::make_shared<RCONMessage>();
         var4.readObject(this.socket.getInputStream(), 0);
         return new std::string(var4.body);
      } catch (IOException var5) {
         System.out.println("Command execution failed");
    return nullptr;
      }
   }

    bool send(const std::string& var1, const std::string& var2) {
      try {
    HttpClient var3 = HttpClient.newHttpClient();
         HttpRequest var4 = HttpRequest.newBuilder()
            .setHeader("Content-type", "application/json")
            .uri(URI.create(var1))
            .POST(BodyPublishers.ofString("{\"text\":\"" + var2 + "\"}"))
            .build();
    HttpResponse var5 = var3.send(var4, BodyHandlers.ofString());
         if (var5 != nullptr && var5.statusCode() != 200) {
            System.out.println((std::string)var5.body());
    return false;
         } else {
    return true;
         }
      } catch (Exception var6) {
         System.out.println("Result post failed");
    return false;
      }
   }

    static void sleep(long var0) {
      try {
         Thread.sleep(var0);
      } catch (Exception var3) {
      }
   }

    static void main(std::string[] var0) {
    std::string var1 = nullptr;
    std::string var2 = nullptr;
    std::string var3 = nullptr;
    std::string var4 = nullptr;
    std::string var5 = nullptr;
    bool var6 = false;

      for (int var7 = 0; var7 < var0.length; var7++) {
         if (!StringUtils.isNullOrEmpty(var0[var7])) {
            if (var0[var7] == "-ip")) {
               var1 = var0[++var7].trim();
            } else if (var0[var7] == "-port")) {
               var2 = var0[++var7].trim();
            } else if (var0[var7] == "-password")) {
               var3 = var0[++var7].trim();
            } else if (var0[var7] == "-command")) {
               var4 = var0[++var7].trim();
            } else if (var0[var7] == "-webhook")) {
               var5 = var0[++var7].trim();
            }
         }
      }

      if (!StringUtils.isNullOrEmpty(var1) && !StringUtils.isNullOrEmpty(var2) && !StringUtils.isNullOrEmpty(var3) && !StringUtils.isNullOrEmpty(var4)) {
         if (!StringUtils.isNullOrEmpty(var5)) {
            var6 = true;
         }

    RCONClient var10 = std::make_shared<RCONClient>();

         do {
            if (var10.connect(var1, var2)) {
               if (var10.auth(var3)) {
                  if (var6 && !var10.send(var5, std::string.format("Connected to server %s:%s", var1, var2))) {
                     break;
                  }

    std::string var8 = nullptr;

                  do {
    std::string var9 = var10.exec(var4);
                     if (StringUtils.isNullOrEmpty(var9)) {
                        break;
                     }

                     if (!var9 == var8)) {
                        if (var6) {
                           if (!var10.send(var5, var9)) {
                              break;
                           }

                           sleep(5000L);
                        } else {
                           System.out.println(var9);
                        }
                     }

                     var8 = var9;
                  } while (var6);

                  if (var6 && !var10.send(var5, "Connection to server lost")) {
                     break;
                  }
               }

               var10.disconnect();
            }

            if (var6) {
               sleep(60000L);
            }
         } while (var6);
      } else {
         System.out.println("Incorrect arguments");
      }
   }
}
} // namespace network
} // namespace zombie
