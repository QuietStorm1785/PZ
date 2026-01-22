#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/http/read.hpp>
#include <nlohmann/json.hpp>
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "org/json/JSONArray.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {


class ImplDiscordAPI {
public:
   ImplDiscordAPI$3(ImplDiscordAPI& parent, const std::string& id) : parent_(parent), id_(id) {}

   User call() {
      // Debug log: "Trying request/find user with id who isn't cached"
      boost::asio::io_context ioc;
      boost::asio::ip::tcp::resolver resolver(ioc);
      boost::beast::tcp_stream stream(ioc);
      auto const host = "discordapp.com";
      auto const port = "443";
      auto const target = "/api/v6/users/" + id_;

      // Resolve and connect
      auto const results = resolver.resolve(host, port);
      stream.connect(results);

      // Prepare request
      boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, target, 11};
      req.set(boost::beast::http::field::host, host);
      req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
      req.set("authorization", parent_.getToken()); // You must implement getToken()
      req.prepare_payload();

      // Send request
      boost::beast::http::write(stream, req);

      // Receive response
      boost::beast::flat_buffer buffer;
      boost::beast::http::response<boost::beast::http::string_body> res;
      boost::beast::http::read(stream, buffer, res);

      // Parse response (assume JSON)
      nlohmann::json response_json = nlohmann::json::parse(res.body());
      // TODO: Parse user from response_json and add to server
      User user;
      // ...existing code...
      return user;
   }
private:
   ImplDiscordAPI& parent_;
   std::string id_;
}
} // namespace javacord
} // namespace btobastian
} // namespace de
