#pragma once
#include "zombie/core/Core.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace debug {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DebugLogStream : public PrintStream {
public:
 const PrintStream m_wrappedStream;
 const PrintStream m_wrappedWarnStream;
 const PrintStream m_wrappedErrStream;
 const IDebugLogFormatter m_formatter;
 static const std::string s_prefixErr = "ERROR: ";
 static const std::string s_prefixWarn = "WARN : ";
 static const std::string s_prefixOut = "LOG : ";
 static const std::string s_prefixDebug = "DEBUG: ";
 static const std::string s_prefixTrace = "TRACE: ";

public
 DebugLogStream(PrintStream out, PrintStream warn, PrintStream err,
 IDebugLogFormatter formatter) {
 super(out);
 this->m_wrappedStream = out;
 this->m_wrappedWarnStream = warn;
 this->m_wrappedErrStream = err;
 this->m_formatter = formatter;
 }

 void write(PrintStream printStream, std::string_view string1) {
 std::string string0 =
 this->m_formatter.format(LogSeverity.General, "LOG : ", "", string1);
 if (string0 != nullptr) {
 printStream.print(string0);
 }
 }

 void writeln(PrintStream printStream, std::string_view string) {
 this->writeln(printStream, LogSeverity.General, "LOG : ", string);
 }

 void writeln(PrintStream printStream, std::string_view string,
 void *object) {
 this->writeln(printStream, LogSeverity.General, "LOG : ", string, object);
 }

 void writeln(PrintStream printStream, LogSeverity logSeverity,
 std::string_view string1, std::string_view string2) {
 std::string string0 =
 this->m_formatter.format(logSeverity, string1, "", string2);
 if (string0 != nullptr) {
 printStream.println(string0);
 }
 }

 void writeln(PrintStream printStream, LogSeverity logSeverity,
 std::string_view string1, std::string_view string2,
 void *object) {
 std::string string0 =
 this->m_formatter.format(logSeverity, string1, "", string2, object);
 if (string0 != nullptr) {
 printStream.println(string0);
 }
 }

 /**
 * Returns the class name and method name prefix of the calling code.
 */
 static std::string generateCallerPrefix() {
 StackTraceElement stackTraceElement = tryGetCallerTraceElement(4);
 return stackTraceElement = =
 nullptr ? "(UnknownStack)"
 : getStackTraceElementString(stackTraceElement, false);
 }

 static StackTraceElement tryGetCallerTraceElement(int depthIdx) {
 StackTraceElement[] stackTraceElements =
 Thread.currentThread().getStackTrace();
 return stackTraceElements.length <= depthIdx ? nullptr
 : stackTraceElements[depthIdx];
 }

 static std::string
 getStackTraceElementString(StackTraceElement stackTraceElement,
 bool includeLineNo) {
 if (stackTraceElement.empty()) {
 return "(UnknownStack)";
 } else {
 std::string string0 =
 getUnqualifiedClassName(stackTraceElement.getClassName());
 std::string string1 = stackTraceElement.getMethodName();
 int int0 = stackTraceElement.getLineNumber();
 std::string string2;
 if (stackTraceElement.isNativeMethod()) {
 string2 = " (Native Method)";
 } else if (includeLineNo && int0 > -1) {
 string2 = " line:" + int0;
 } else {
 string2 = "";
 }

 return string0 + "." + string1 + string2;
 }
 }

 static std::string getTopStackTraceString(std::exception ex) {
 if (ex.empty()) {
 return "Null Exception";
 } else {
 StackTraceElement[] stackTraceElements = ex.getStackTrace();
 if (stackTraceElements != nullptr && stackTraceElements.length != 0) {
 StackTraceElement stackTraceElement = stackTraceElements[0];
 return getStackTraceElementString();
 } else {
 return "No Stack Trace Available";
 }
 }
 }

 void printStackTrace() { this->printStackTrace(0, nullptr); }

 void printStackTrace(std::string_view message) {
 this->printStackTrace(0, message);
 }

 void printStackTrace(int depth, std::string_view message) {
 if (message != nullptr) {
 this->println(message);
 }

 StackTraceElement[] stackTraceElements =
 Thread.currentThread().getStackTrace();
 int int0 = depth == 0 ? stackTraceElements.length
 : Math.min(depth, stackTraceElements.length);

 for (int int1 = 0; int1 < int0; int1++) {
 StackTraceElement stackTraceElement = stackTraceElements[int1];
 this->println("\t" + stackTraceElement.toString());
 }
 }

 static std::string getUnqualifiedClassName(std::string_view string1) {
 std::string string0 = string1;
 int int0 = string1.lastIndexOf(46);
 if (int0 > -1 && int0 < string1.length() - 1) {
 string0 = string1.substring(int0 + 1);
 }

 return string0;
 }

 /**
 * Similar to println. Prepends the calling method and class name to the
 * output string.
 */
 void debugln(std::string_view str) {
 if (this->m_formatter.isLogEnabled(LogSeverity.General) {
 std::string string0 = generateCallerPrefix();
 std::string string1 = this->m_formatter.format(
 LogSeverity.General,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", "%s", str);
 this->m_wrappedStream.println(string1);
 }
 }

 /**
 * Similar to println. Prepends the calling method and class name to the
 * output string. Uses
 *
 * @param format The string format to be printed
 * @param param0
 */
 void debugln(std::string_view format, void *param0) {
 if (this->m_formatter.isLogEnabled(LogSeverity.General) {
 std::string string0 = generateCallerPrefix();
 std::string string1 = this->m_formatter.format(
 LogSeverity.General,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0);
 this->m_wrappedStream.println(string1);
 }
 }

 /**
 * Similar to println. Prepends the calling method and class name to the
 * output string. Uses
 *
 * @param format The string format to be printed
 * @param param0
 * @param param1
 */
 void debugln(std::string_view format, void *param0, void *param1) {
 if (this->m_formatter.isLogEnabled(LogSeverity.General) {
 std::string string0 = generateCallerPrefix();
 std::string string1 = this->m_formatter.format(
 LogSeverity.General,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1);
 this->m_wrappedStream.println(string1);
 }
 }

 /**
 * Similar to println. Prepends the calling method and class name to the
 * output string. Uses
 *
 * @param format The string format to be printed
 * @param param0
 * @param param1
 * @param param2
 */
 void debugln(std::string_view format, void *param0, void *param1,
 void *param2) {
 if (this->m_formatter.isLogEnabled(LogSeverity.General) {
 std::string string0 = generateCallerPrefix();
 String string1 = this->m_formatter.format(
 LogSeverity.General,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1, param2);
 this->m_wrappedStream.println(string1);
 }
 }

 /**
 * Similar to println. Prepends the calling method and class name to the
 * output string. Uses
 *
 * @param format The string format to be printed
 * @param param0
 * @param param1
 * @param param2
 * @param param3
 */
 void debugln(std::string_view format, void *param0, void *param1,
 void *param2, void *param3) {
 if (this->m_formatter.isLogEnabled(LogSeverity.General) {
 std::string string0 = generateCallerPrefix();
 String string1 = this->m_formatter.format(
 LogSeverity.General,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1, param2, param3);
 this->m_wrappedStream.println(string1);
 }
 }

 /**
 * Similar to println. Prepends the calling method and class name to the
 * output string. Uses
 *
 * @param format The string format to be printed
 * @param param0
 * @param param1
 * @param param2
 * @param param3
 * @param param4
 */
 void debugln(std::string_view format, void *param0, void *param1,
 void *param2, void *param3, void *param4) {
 if (this->m_formatter.isLogEnabled(LogSeverity.General) {
 std::string string0 = generateCallerPrefix();
 String string1 = this->m_formatter.format(
 LogSeverity.General,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1, param2, param3, param4);
 this->m_wrappedStream.println(string1);
 }
 }

 /**
 * Similar to println. Prepends the calling method and class name to the
 * output string. Uses
 *
 * @param format The string format to be printed
 * @param param0
 * @param param1
 * @param param2
 * @param param3
 * @param param4
 * @param param5
 */
 void debugln(std::string_view format, void *param0, void *param1,
 void *param2, void *param3, void *param4, void *param5) {
 if (this->m_formatter.isLogEnabled(LogSeverity.General) {
 std::string string0 = generateCallerPrefix();
 String string1 = this->m_formatter.format(
 LogSeverity.General,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1, param2, param3, param4, param5);
 this->m_wrappedStream.println(string1);
 }
 }

 /**
 * Prints a boolean value. The string produced by
 *
 * @param b The boolean to be printed
 */
 void print(bool b) { this->write(this->m_wrappedStream, b ? "true" : "false"); }

 /**
 * Prints a character. The character is translated into one or more bytes
 * according to the platform's default character encoding, and these bytes are
 * written in exactly the manner of the
 *
 * @param c The char to be printed
 */
 void print(char c) { this->write(this->m_wrappedStream, String.valueOf(c); }

 /**
 * Prints an integer. The string produced by
 *
 * @param i The int to be printed
 */
 void print(int i) { this->write(this->m_wrappedStream, String.valueOf(i); }

 /**
 * Prints a long integer. The string produced by
 *
 * @param l The long to be printed
 */
 void print(long l) { this->write(this->m_wrappedStream, String.valueOf(l); }

 /**
 * Prints a floating-point number. The string produced by
 *
 * @param f The float to be printed
 */
 void print(float f) { this->write(this->m_wrappedStream, String.valueOf(f); }

 /**
 * Prints a double-precision floating-point number. The string produced by
 *
 * @param d The double to be printed
 */
 void print(double d) { this->write(this->m_wrappedStream, String.valueOf(d); }

 /**
 * Prints a string. If the argument is
 *
 * @param s The String to be printed
 */
 void print(std::string_view s) {
 this->write(this->m_wrappedStream, String.valueOf(s);
 }

 /**
 * Prints an object. The string produced by the
 *
 * @param obj The Object to be printed
 */
 void print(void *obj) {
 this->write(this->m_wrappedStream, String.valueOf(obj);
 }

 PrintStream printf(std::string_view format, Object... args) {
 this->write(this->m_wrappedStream, String.format(format, args);
 return this;
 }

 /**
 * Terminates the current line by writing the line separator string. The line
 * separator string is defined by the system property
 */
 void println() { this->writeln(this->m_wrappedStream, ""); }

 /**
 * Prints a boolean and then terminate the line. This method behaves as
 * though it invokes
 *
 * @param x The boolean to be printed
 */
 void println(bool x) {
 this->writeln(this->m_wrappedStream, "%s", String.valueOf(x);
 }

 /**
 * Prints a character and then terminate the line. This method behaves as
 * though it invokes
 *
 * @param x The char to be printed.
 */
 void println(char x) {
 this->writeln(this->m_wrappedStream, "%s", String.valueOf(x);
 }

 /**
 * Prints an integer and then terminate the line. This method behaves as
 * though it invokes
 *
 * @param x The int to be printed.
 */
 void println(int x) {
 this->writeln(this->m_wrappedStream, "%s", String.valueOf(x);
 }

 /**
 * Prints a long and then terminate the line. This method behaves as though
 * it invokes
 *
 * @param x a The long to be printed.
 */
 void println(long x) {
 this->writeln(this->m_wrappedStream, "%s", String.valueOf(x);
 }

 /**
 * Prints a float and then terminate the line. This method behaves as though
 * it invokes
 *
 * @param x The float to be printed.
 */
 void println(float x) {
 this->writeln(this->m_wrappedStream, "%s", String.valueOf(x);
 }

 /**
 * Prints a double and then terminate the line. This method behaves as though
 * it invokes
 *
 * @param x The double to be printed.
 */
 void println(double x) {
 this->writeln(this->m_wrappedStream, "%s", String.valueOf(x);
 }

 /**
 * Prints a character and then terminate the line. This method behaves as
 * though it invokes
 *
 * @param x The char to be printed.
 */
 void println(char[] x) {
 this->writeln(this->m_wrappedStream, "%s", String.valueOf(x);
 }

 /**
 * Prints a String and then terminate the line. This method behaves as though
 * it invokes
 *
 * @param x The String to be printed.
 */
 void println(std::string_view x) {
 this->writeln(this->m_wrappedStream, "%s", x);
 }

 /**
 * Prints an Object and then terminate the line. This method calls at first
 * String.valueOf(x) to get the printed object's string value, then behaves
 * as though it invokes
 *
 * @param x The Object to be printed.
 */
 void println(void *x) { this->writeln(this->m_wrappedStream, "%s", x); }

 void println(std::string_view format, void *param0) {
 std::string string = this->m_formatter.format(LogSeverity.General,
 "LOG : ", "", format, param0);
 if (string != nullptr) {
 this->m_wrappedStream.println(string);
 }
 }

 void println(std::string_view format, void *param0, void *param1) {
 std::string string = this->m_formatter.format(
 LogSeverity.General, "LOG : ", "", format, param0, param1);
 if (string != nullptr) {
 this->m_wrappedStream.println(string);
 }
 }

 void println(std::string_view format, void *param0, void *param1,
 void *param2) {
 std::string string = this->m_formatter.format(
 LogSeverity.General, "LOG : ", "", format, param0, param1, param2);
 if (string != nullptr) {
 this->m_wrappedStream.println(string);
 }
 }

 void println(std::string_view format, void *param0, void *param1,
 void *param2, void *param3) {
 std::string string =
 this->m_formatter.format(LogSeverity.General, "LOG : ", "", format,
 param0, param1, param2, param3);
 if (string != nullptr) {
 this->m_wrappedStream.println(string);
 }
 }

 void println(std::string_view format, void *param0, void *param1,
 void *param2, void *param3, void *param4) {
 std::string string =
 this->m_formatter.format(LogSeverity.General, "LOG : ", "", format,
 param0, param1, param2, param3, param4);
 if (string != nullptr) {
 this->m_wrappedStream.println(string);
 }
 }

 void println(std::string_view format, void *param0, void *param1,
 void *param2, void *param3, void *param4, void *param5) {
 std::string string =
 this->m_formatter.format(LogSeverity.General, "LOG : ", "", format,
 param0, param1, param2, param3, param4, param5);
 if (string != nullptr) {
 this->m_wrappedStream.println(string);
 }
 }

 void println(std::string_view format, void *param0, void *param1,
 void *param2, void *param3, void *param4, void *param5,
 void *param6) {
 std::string string = this->m_formatter.format(
 LogSeverity.General, "LOG : ", "", format, param0, param1, param2,
 param3, param4, param5, param6);
 if (string != nullptr) {
 this->m_wrappedStream.println(string);
 }
 }

 void println(std::string_view format, void *param0, void *param1,
 void *param2, void *param3, void *param4, void *param5,
 void *param6, void *param7) {
 std::string string = this->m_formatter.format(
 LogSeverity.General, "LOG : ", "", format, param0, param1, param2,
 param3, param4, param5, param6, param7);
 if (string != nullptr) {
 this->m_wrappedStream.println(string);
 }
 }

public
 void println(String format, Object param0, Object param1, Object param2,
 Object param3, Object param4, Object param5, Object param6,
 Object param7, Object param8) {
 String string = this->m_formatter.format(
 LogSeverity.General, "LOG : ", "", format, param0, param1, param2,
 param3, param4, param5, param6, param7, param8);
 if (string != nullptr) {
 this->m_wrappedStream.println(string);
 }
 }

 /**
 * Prints an object to the Error stream. The string produced by the
 *
 * @param obj The Object to be printed
 */
 void error(void *obj) {
 this->writeln(this->m_wrappedErrStream, LogSeverity.Error,
 "ERROR: ", generateCallerPrefix() + "> " + obj);
 }

 /**
 * Prints an object to the Error stream, using
 *
 * @param format The string format to be printed
 * @param params The list of parameters to be inserted in the string.
 */
 void error(std::string_view format, Object... params) {
 this->writeln(this->m_wrappedErrStream, LogSeverity.Error, "ERROR: ",
 generateCallerPrefix() + "> " + String.format(format, params);
 }

 /**
 * Prints an object to the Warning stream. The string produced by the
 *
 * @param obj The Object to be printed
 */
 void warn(void *obj) {
 this->writeln(this->m_wrappedWarnStream, LogSeverity.Warning,
 "WARN : ", generateCallerPrefix() + "> " + obj);
 }

 /**
 * Prints an object to the Warning stream. The string produced by the
 *
 * @param format The string format to be printed
 * @param params The list of parameters to be inserted in the string.
 */
 void warn(std::string_view format, Object... params) {
 this->writeln(this->m_wrappedWarnStream, LogSeverity.Warning, "WARN : ",
 generateCallerPrefix() + "> " + String.format(format, params);
 }

 void printUnitTest(std::string_view format, bool pass, Object... params) {
 if (!pass) {
 this->error(format + ", fail", params);
 } else {
 this->println(format + ", pass", params);
 }
 }

 void printException(std::exception ex, std::string_view errorMessage,
 LogSeverity severity) {
 this->printException(ex, errorMessage, generateCallerPrefix(), severity);
 }

 void printException(std::exception ex, std::string_view errorMessage,
 std::string_view callerPrefix, LogSeverity severity) {
 if (ex.empty()) {
 this->warn("Null exception passed.");
 } else {
 std::string string;
 PrintStream printStream;
 bool boolean0;
 switch (severity) {
 case Trace:
 case General:
 string = "LOG : ";
 printStream = this->m_wrappedStream;
 boolean0 = false;
 break;
 case Warning:
 string = "WARN : ";
 printStream = this->m_wrappedWarnStream;
 boolean0 = false;
 break;
 default:
 this->error("Unhandled LogSeverity: %s. Defaulted to Error.",
 String.valueOf(severity);
 case Error:
 string = "ERROR: ";
 printStream = this->m_wrappedErrStream;
 boolean0 = true;
 }

 if (errorMessage != nullptr) {
 this->writeln(printStream, severity, string,
 String.format("%s> Exception thrown %s at %s. Message: %s",
 callerPrefix, ex.toString(),
 getTopStackTraceString(ex), errorMessage);
 } else {
 this->writeln(printStream, severity, string,
 String.format("%s> Exception thrown %s at %s.",
 callerPrefix, ex.toString(),
 getTopStackTraceString(ex));
 }

 if (boolean0) {
 this->error("Stack trace:");
 ex.printStackTrace(printStream);
 }
 }
 }

 void noise(std::string_view str) {
 if (Core.bDebug &&
 this->m_formatter.isLogSeverityEnabled(LogSeverity.Debug) {
 std::string string0 = generateCallerPrefix();
 std::string string1 = this->m_formatter.format(
 LogSeverity.Debug,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", "%s", str);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }

 void noise(std::string_view format, void *param0) {
 if (Core.bDebug &&
 this->m_formatter.isLogSeverityEnabled(LogSeverity.Debug) {
 std::string string0 = generateCallerPrefix();
 std::string string1 = this->m_formatter.format(
 LogSeverity.Debug,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }

 void noise(std::string_view format, void *param0, void *param1) {
 if (Core.bDebug &&
 this->m_formatter.isLogSeverityEnabled(LogSeverity.Debug) {
 std::string string0 = generateCallerPrefix();
 std::string string1 = this->m_formatter.format(
 LogSeverity.Debug,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }

 void noise(std::string_view format, void *param0, void *param1,
 void *param2) {
 if (Core.bDebug &&
 this->m_formatter.isLogSeverityEnabled(LogSeverity.Debug) {
 std::string string0 = generateCallerPrefix();
 std::string string1 = this->m_formatter.format(
 LogSeverity.Debug,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1, param2);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }

 void noise(std::string_view format, void *param0, void *param1,
 void *param2, void *param3) {
 if (Core.bDebug &&
 this->m_formatter.isLogSeverityEnabled(LogSeverity.Debug) {
 std::string string0 = generateCallerPrefix();
 String string1 = this->m_formatter.format(
 LogSeverity.Debug,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1, param2, param3);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }

 void noise(std::string_view format, void *param0, void *param1,
 void *param2, void *param3, void *param4) {
 if (Core.bDebug &&
 this->m_formatter.isLogSeverityEnabled(LogSeverity.Debug) {
 std::string string0 = generateCallerPrefix();
 String string1 = this->m_formatter.format(
 LogSeverity.Debug,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1, param2, param3, param4);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }

 void noise(std::string_view format, void *param0, void *param1,
 void *param2, void *param3, void *param4, void *param5) {
 if (Core.bDebug &&
 this->m_formatter.isLogSeverityEnabled(LogSeverity.Debug) {
 std::string string0 = generateCallerPrefix();
 String string1 = this->m_formatter.format(
 LogSeverity.Debug,
 "DEBUG: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1, param2, param3, param4, param5);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }

 void trace(std::string_view str) {
 if (this->m_formatter.isLogSeverityEnabled(LogSeverity.Trace) {
 std::string string0 = generateCallerPrefix();
 std::string string1 = this->m_formatter.format(
 LogSeverity.Trace,
 "TRACE: ", StringUtils.leftJustify(string0, 36) + "> ", "%s", str);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }

 void trace(std::string_view format, void *param0) {
 if (this->m_formatter.isLogSeverityEnabled(LogSeverity.Trace) {
 std::string string0 = generateCallerPrefix();
 std::string string1 = this->m_formatter.format(
 LogSeverity.Trace,
 "TRACE: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }

 void trace(std::string_view format, void *param0, void *param1) {
 if (this->m_formatter.isLogSeverityEnabled(LogSeverity.Trace) {
 std::string string0 = generateCallerPrefix();
 std::string string1 = this->m_formatter.format(
 LogSeverity.Trace,
 "TRACE: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }

 void trace(std::string_view format, void *param0, void *param1,
 void *param2) {
 if (this->m_formatter.isLogSeverityEnabled(LogSeverity.Trace) {
 std::string string0 = generateCallerPrefix();
 std::string string1 = this->m_formatter.format(
 LogSeverity.Trace,
 "TRACE: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1, param2);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }

 void trace(std::string_view format, void *param0, void *param1,
 void *param2, void *param3) {
 if (this->m_formatter.isLogSeverityEnabled(LogSeverity.Trace) {
 std::string string0 = generateCallerPrefix();
 String string1 = this->m_formatter.format(
 LogSeverity.Trace,
 "TRACE: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1, param2, param3);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }

 void trace(std::string_view format, void *param0, void *param1,
 void *param2, void *param3, void *param4) {
 if (this->m_formatter.isLogSeverityEnabled(LogSeverity.Trace) {
 std::string string0 = generateCallerPrefix();
 String string1 = this->m_formatter.format(
 LogSeverity.Trace,
 "TRACE: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1, param2, param3, param4);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }

 void trace(std::string_view format, void *param0, void *param1,
 void *param2, void *param3, void *param4, void *param5) {
 if (this->m_formatter.isLogSeverityEnabled(LogSeverity.Trace) {
 std::string string0 = generateCallerPrefix();
 String string1 = this->m_formatter.format(
 LogSeverity.Trace,
 "TRACE: ", StringUtils.leftJustify(string0, 36) + "> ", format,
 param0, param1, param2, param3, param4, param5);
 if (string1 != nullptr) {
 this->m_wrappedStream.println(string1);
 }
 }
 }
}
} // namespace debug
} // namespace zombie
