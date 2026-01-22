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
#include <algorithm>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/http/read.hpp>

namespace de {
namespace btobastian {
namespace javacord {


class ImplDiscordAPI {
public:
   ImplDiscordAPI$8(ImplDiscordAPI& parent, const std::string& inviteCode)
      : parent_(parent), inviteCode_(inviteCode) {}

   void call() {
      // Prepare HTTP DELETE using Boost.Beast
      boost::asio::io_context ioc;
      boost::asio::ip::tcp::resolver resolver(ioc);
      boost::beast::tcp_stream stream(ioc);
      auto const host = "discordapp.com";
      auto const port = "443";
      auto const target = "/api/v6/invite/" + inviteCode_;

      // Resolve and connect
      auto const results = resolver.resolve(host, port);
      stream.connect(results);

      // Prepare request
      boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::delete_, target, 11};
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

      // TODO: Check response and handle deletion
   }
private:
   ImplDiscordAPI& parent_;
   std::string inviteCode_;
}
} // namespace javacord
} // namespace btobastian
} // namespace de
