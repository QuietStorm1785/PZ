#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace common {
namespace net {


class HttpHeaders {
public:
    static const std::string CACHE_CONTROL = "Cache-Control";
    static const std::string CONTENT_LENGTH = "Content-Length";
    static const std::string CONTENT_TYPE = "Content-Type";
    static const std::string DATE = "Date";
    static const std::string PRAGMA = "Pragma";
    static const std::string VIA = "Via";
    static const std::string WARNING = "Warning";
    static const std::string ACCEPT = "Accept";
    static const std::string ACCEPT_CHARSET = "Accept-Charset";
    static const std::string ACCEPT_ENCODING = "Accept-Encoding";
    static const std::string ACCEPT_LANGUAGE = "Accept-Language";
    static const std::string ACCESS_CONTROL_REQUEST_HEADERS = "Access-Control-Request-Headers";
    static const std::string ACCESS_CONTROL_REQUEST_METHOD = "Access-Control-Request-Method";
    static const std::string AUTHORIZATION = "Authorization";
    static const std::string CONNECTION = "Connection";
    static const std::string COOKIE = "Cookie";
    static const std::string EXPECT = "Expect";
    static const std::string FROM = "From";
    static const std::string FORWARDED = "Forwarded";
    static const std::string FOLLOW_ONLY_WHEN_PRERENDER_SHOWN = "Follow-Only-When-Prerender-Shown";
    static const std::string HOST = "Host";
    static const std::string IF_MATCH = "If-Match";
    static const std::string IF_MODIFIED_SINCE = "If-Modified-Since";
    static const std::string IF_NONE_MATCH = "If-None-Match";
    static const std::string IF_RANGE = "If-Range";
    static const std::string IF_UNMODIFIED_SINCE = "If-Unmodified-Since";
    static const std::string LAST_EVENT_ID = "Last-Event-ID";
    static const std::string MAX_FORWARDS = "Max-Forwards";
    static const std::string ORIGIN = "Origin";
    static const std::string PROXY_AUTHORIZATION = "Proxy-Authorization";
    static const std::string RANGE = "Range";
    static const std::string REFERER = "Referer";
    static const std::string SERVICE_WORKER = "Service-Worker";
    static const std::string TE = "TE";
    static const std::string UPGRADE = "Upgrade";
    static const std::string USER_AGENT = "User-Agent";
    static const std::string ACCEPT_RANGES = "Accept-Ranges";
    static const std::string ACCESS_CONTROL_ALLOW_HEADERS = "Access-Control-Allow-Headers";
    static const std::string ACCESS_CONTROL_ALLOW_METHODS = "Access-Control-Allow-Methods";
    static const std::string ACCESS_CONTROL_ALLOW_ORIGIN = "Access-Control-Allow-Origin";
    static const std::string ACCESS_CONTROL_ALLOW_CREDENTIALS = "Access-Control-Allow-Credentials";
    static const std::string ACCESS_CONTROL_EXPOSE_HEADERS = "Access-Control-Expose-Headers";
    static const std::string ACCESS_CONTROL_MAX_AGE = "Access-Control-Max-Age";
    static const std::string AGE = "Age";
    static const std::string ALLOW = "Allow";
    static const std::string CONTENT_DISPOSITION = "Content-Disposition";
    static const std::string CONTENT_ENCODING = "Content-Encoding";
    static const std::string CONTENT_LANGUAGE = "Content-Language";
    static const std::string CONTENT_LOCATION = "Content-Location";
    static const std::string CONTENT_MD5 = "Content-MD5";
    static const std::string CONTENT_RANGE = "Content-Range";
    static const std::string CONTENT_SECURITY_POLICY = "Content-Security-Policy";
    static const std::string CONTENT_SECURITY_POLICY_REPORT_ONLY = "Content-Security-Policy-Report-Only";
    static const std::string X_CONTENT_SECURITY_POLICY = "X-Content-Security-Policy";
    static const std::string X_CONTENT_SECURITY_POLICY_REPORT_ONLY = "X-Content-Security-Policy-Report-Only";
    static const std::string X_WEBKIT_CSP = "X-WebKit-CSP";
    static const std::string X_WEBKIT_CSP_REPORT_ONLY = "X-WebKit-CSP-Report-Only";
    static const std::string ETAG = "ETag";
    static const std::string EXPIRES = "Expires";
    static const std::string LAST_MODIFIED = "Last-Modified";
    static const std::string LINK = "Link";
    static const std::string LOCATION = "Location";
    static const std::string P3P = "P3P";
    static const std::string PROXY_AUTHENTICATE = "Proxy-Authenticate";
    static const std::string REFRESH = "Refresh";
    static const std::string RETRY_AFTER = "Retry-After";
    static const std::string SERVER = "Server";
    static const std::string SERVICE_WORKER_ALLOWED = "Service-Worker-Allowed";
    static const std::string SET_COOKIE = "Set-Cookie";
    static const std::string SET_COOKIE2 = "Set-Cookie2";
    static const std::string STRICT_TRANSPORT_SECURITY = "Strict-Transport-Security";
    static const std::string TIMING_ALLOW_ORIGIN = "Timing-Allow-Origin";
    static const std::string TRAILER = "Trailer";
    static const std::string TRANSFER_ENCODING = "Transfer-Encoding";
    static const std::string VARY = "Vary";
    static const std::string WWW_AUTHENTICATE = "WWW-Authenticate";
    static const std::string DNT = "DNT";
    static const std::string X_CONTENT_TYPE_OPTIONS = "X-Content-Type-Options";
    static const std::string X_DO_NOT_TRACK = "X-Do-Not-Track";
    static const std::string X_FORWARDED_FOR = "X-Forwarded-For";
    static const std::string X_FORWARDED_PROTO = "X-Forwarded-Proto";
    static const std::string X_FORWARDED_HOST = "X-Forwarded-Host";
    static const std::string X_FORWARDED_PORT = "X-Forwarded-Port";
    static const std::string X_FRAME_OPTIONS = "X-Frame-Options";
    static const std::string X_POWERED_BY = "X-Powered-By";
    static const std::string PUBLIC_KEY_PINS = "Public-Key-Pins";
    static const std::string PUBLIC_KEY_PINS_REPORT_ONLY = "Public-Key-Pins-Report-Only";
    static const std::string X_REQUESTED_WITH = "X-Requested-With";
    static const std::string X_USER_IP = "X-User-IP";
    static const std::string X_XSS_PROTECTION = "X-XSS-Protection";
    static const std::string PING_FROM = "Ping-From";
    static const std::string PING_TO = "Ping-To";

    private HttpHeaders() {
   }
}
} // namespace net
} // namespace common
} // namespace google
} // namespace com
