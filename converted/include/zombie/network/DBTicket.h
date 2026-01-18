#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class DBTicket {
public:
 std::string author = nullptr;
 std::string message = "";
 int ticketID = 0;
 bool viewed = false;
 DBTicket answer = nullptr;
 bool isAnswer = false;

 public DBTicket(const std::string& _author, const std::string& _message, int _ticketID) {
 this->author = _author;
 this->message = _message;
 this->ticketID = _ticketID;
 this->viewed = this->viewed;
 }

 std::string getAuthor() {
 return this->author;
 }

 void setAuthor(const std::string& _author) {
 this->author = _author;
 }

 std::string getMessage() {
 return this->message;
 }

 void setMessage(const std::string& _message) {
 this->message = _message;
 }

 int getTicketID() {
 return this->ticketID;
 }

 void setTicketID(int _ticketID) {
 this->ticketID = _ticketID;
 }

 bool isViewed() {
 return this->viewed;
 }

 void setViewed(bool _viewed) {
 this->viewed = _viewed;
 }

 DBTicket getAnswer() {
 return this->answer;
 }

 void setAnswer(DBTicket _answer) {
 this->answer = _answer;
 }

 bool isAnswer() {
 return this->isAnswer;
 }

 void setIsAnswer(bool _isAnswer) {
 this->isAnswer = _isAnswer;
 }
}
} // namespace network
} // namespace zombie
