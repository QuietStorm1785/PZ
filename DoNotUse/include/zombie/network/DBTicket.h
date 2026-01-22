#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class DBTicket {
public:
    std::string author = nullptr;
    std::string message = "";
    int ticketID = 0;
    bool viewed = false;
    DBTicket answer = nullptr;
    bool isAnswer = false;

    public DBTicket(const std::string& var1, const std::string& var2, int var3) {
      this.author = var1;
      this.message = var2;
      this.ticketID = var3;
      this.viewed = this.viewed;
   }

    std::string getAuthor() {
      return this.author;
   }

    void setAuthor(const std::string& var1) {
      this.author = var1;
   }

    std::string getMessage() {
      return this.message;
   }

    void setMessage(const std::string& var1) {
      this.message = var1;
   }

    int getTicketID() {
      return this.ticketID;
   }

    void setTicketID(int var1) {
      this.ticketID = var1;
   }

    bool isViewed() {
      return this.viewed;
   }

    void setViewed(bool var1) {
      this.viewed = var1;
   }

    DBTicket getAnswer() {
      return this.answer;
   }

    void setAnswer(DBTicket var1) {
      this.answer = var1;
   }

    bool isAnswer() {
      return this.isAnswer;
   }

    void setIsAnswer(bool var1) {
      this.isAnswer = var1;
   }
}
} // namespace network
} // namespace zombie
