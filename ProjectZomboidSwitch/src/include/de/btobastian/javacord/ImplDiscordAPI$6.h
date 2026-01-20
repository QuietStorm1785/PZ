#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/HttpResponse.h"
#include "com/mashape/unirest/http/JsonNode.h"
#include "com/mashape/unirest/http/Unirest.h"
#include "de/btobastian/javacord/ImplDiscordAPI/6/1.h"
#include "de/btobastian/javacord/entities/impl/ImplUser.h"
#include "java/awt/image/BufferedImage.h"
#include "org/json/JSONObject.h"
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/http/read.hpp>
#include <sstream>
#include <iomanip>

namespace de {
namespace btobastian {
namespace javacord {


class ImplDiscordAPI {
public:
   ImplDiscordAPI$6(ImplDiscordAPI& parent, const nlohmann::json& params, const std::string& newUsername, const std::string& newPassword, const std::string& newAvatarPath)
      : parent_(parent), params_(params), newUsername_(newUsername), newPassword_(newPassword), newAvatarPath_(newAvatarPath) {}

   void call() {
      nlohmann::json payload = params_;
      payload["username"] = newUsername_;
      payload["password"] = newPassword_;
      // Handle avatar image (OpenCV + base64)
      if (!newAvatarPath_.empty()) {
         cv::Mat avatar = cv::imread(newAvatarPath_, cv::IMREAD_COLOR);
         if (avatar.empty() || avatar.rows != 128 || avatar.cols != 128) {
            throw std::invalid_argument("Avatar must be 128x128px and valid!");
         }
         std::vector<uchar> buf;
         cv::imencode(".jpg", avatar, buf);
         std::string encoded;
         static const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
         auto base64_encode = [](const std::vector<uchar>& bytes) -> std::string {
            std::string ret;
            int i = 0;
            unsigned char char_array_3[3];
            unsigned char char_array_4[4];
            int len = bytes.size();
            int pos = 0;
            while (len--) {
               char_array_3[i++] = bytes[pos++];
               if (i == 3) {
                  char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                  char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                  char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                  char_array_4[3] = char_array_3[2] & 0x3f;
                  for (i = 0; i < 4; i++)
                     ret += base64_chars[char_array_4[i]];
                  i = 0;
               }
            }
            if (i) {
               for (int j = i; j < 3; j++)
                  char_array_3[j] = '\0';
               char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
               char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
               char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
               char_array_4[3] = char_array_3[2] & 0x3f;
               for (int j = 0; j < i + 1; j++)
                  ret += base64_chars[char_array_4[j]];
               while (i++ < 3)
                  ret += '=';
            }
            return ret;
         };
         encoded = base64_encode(buf);
         payload["avatar"] = "data:image/jpg;base64," + encoded;
      }

      // Prepare HTTP PATCH using Boost.Beast
      boost::asio::io_context ioc;
      boost::asio::ip::tcp::resolver resolver(ioc);
      boost::beast::tcp_stream stream(ioc);
      auto const host = "discordapp.com";
      auto const port = "443";
      auto const target = "/api/v6/users/@me";

      // Resolve and connect
      auto const results = resolver.resolve(host, port);
      stream.connect(results);

      // Prepare request
      boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::patch, target, 11};
      req.set(boost::beast::http::field::host, host);
      req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
      req.set(boost::beast::http::field::content_type, "application/json");
      req.set("authorization", parent_.getToken()); // You must implement getToken()
      req.body() = payload.dump();
      req.prepare_payload();

      // Send request
      boost::beast::http::write(stream, req);

      // Receive response
      boost::beast::flat_buffer buffer;
      boost::beast::http::response<boost::beast::http::string_body> res;
      boost::beast::http::read(stream, buffer, res);

      // Parse response (assume JSON)
      nlohmann::json response_json = nlohmann::json::parse(res.body());
      // TODO: Update ImplUser and parent_ with response_json
   }
private:
   ImplDiscordAPI& parent_;
   nlohmann::json params_;
   std::string newUsername_;
   std::string newPassword_;
   std::string newAvatarPath_;
}
} // namespace javacord
} // namespace btobastian
} // namespace de
