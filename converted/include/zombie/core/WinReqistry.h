#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WinReqistry {
public:
 static std::string getSteamDirectory() {
 return readRegistry();
 }

 static std::string readRegistry(const std::string& string1, const std::string& string0) {
 try {
 Process process = Runtime.getRuntime().exec("reg query \"" + string1 + "\" /v " + string0);
 WinReqistry.StreamReader streamReader = new WinReqistry.StreamReader(process.getInputStream());
 streamReader.start();
 process.waitFor();
 streamReader.join();
 std::string string2 = streamReader.getResult();
 if (string2 != nullptr && !string2 == "")) {
 string2 = string2.substring(string2.indexOf("REG_SZ") + 7).trim();
 String[] strings = string2.split("\t");
 return strings[strings.length - 1];
 } else {
 return nullptr;
 }
 } catch (Exception exception) {
 return nullptr;
 }
 }

 static class StreamReader extends Thread {
 InputStream is;
 StringWriter sw = new StringWriter();

 public StreamReader(InputStream inputStream) {
 this->is = inputStream;
 }

 void run() {
 int int0;
 try {
 while ((int0 = this->is.read()) != -1) {
 this->sw.write(int0);
 }
 } catch (IOException iOException) {
 }
 }

 std::string getResult() {
 return this->sw.toString();
 }
 }
}
} // namespace core
} // namespace zombie
