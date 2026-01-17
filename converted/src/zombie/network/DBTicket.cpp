#include "zombie/network/DBTicket.h"

namespace zombie {
namespace network {

public
DBTicket::DBTicket(const std::string &_author, const std::string &_message,
                   int _ticketID) {
  // TODO: Implement DBTicket
  return nullptr;
}

std::string DBTicket::getAuthor() {
  // TODO: Implement getAuthor
  return "";
}

void DBTicket::setAuthor(const std::string &_author) {
  // TODO: Implement setAuthor
}

std::string DBTicket::getMessage() {
  // TODO: Implement getMessage
  return "";
}

void DBTicket::setMessage(const std::string &_message) {
  // TODO: Implement setMessage
}

int DBTicket::getTicketID() {
  // TODO: Implement getTicketID
  return 0;
}

void DBTicket::setTicketID(int _ticketID) {
  // TODO: Implement setTicketID
}

bool DBTicket::isViewed() {
  // TODO: Implement isViewed
  return false;
}

void DBTicket::setViewed(bool _viewed) {
  // TODO: Implement setViewed
}

DBTicket DBTicket::getAnswer() {
  // TODO: Implement getAnswer
  return nullptr;
}

void DBTicket::setAnswer(DBTicket _answer) {
  // TODO: Implement setAnswer
}

bool DBTicket::isAnswer() {
  // TODO: Implement isAnswer
  return false;
}

void DBTicket::setIsAnswer(bool _isAnswer) {
  // TODO: Implement setIsAnswer
}

} // namespace network
} // namespace zombie
