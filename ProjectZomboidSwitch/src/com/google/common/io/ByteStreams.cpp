#include <memory>
#include "com\google\common\io/ByteStreams.h"

namespace com {
namespace google {
namespace common {
namespace io {

private ByteStreams::ByteStreams() {
    // TODO: Implement ByteStreams
    return nullptr;
}

long ByteStreams::copy(InputStream from, OutputStream to) {
    // TODO: Implement copy
    return 0;
}

long ByteStreams::copy(ReadableByteChannel from, WritableByteChannel to) {
    // TODO: Implement copy
    return 0;
}

long ByteStreams::exhaust(InputStream in) {
    // TODO: Implement exhaust
    return 0;
}

ByteArrayDataInput ByteStreams::newDataInput(byte[] bytes) {
    // TODO: Implement newDataInput
    return nullptr;
}

return ByteStreams::newDataInput(std::make_shared<ByteArrayInputStream>(bytes) {
    // TODO: Implement newDataInput
    return nullptr;
}

ByteArrayDataInput ByteStreams::newDataInput(byte[] bytes, int start) {
    // TODO: Implement newDataInput
    return nullptr;
}

return ByteStreams::newDataInput(std::make_shared<ByteArrayInputStream>(bytes, bytes.length -) {
    // TODO: Implement newDataInput
    return nullptr;
}

ByteArrayDataInput ByteStreams::newDataInput(ByteArrayInputStream byteArrayInputStream) {
    // TODO: Implement newDataInput
    return nullptr;
}

ByteArrayDataOutput ByteStreams::newDataOutput() {
    // TODO: Implement newDataOutput
    return nullptr;
}

return ByteStreams::newDataOutput(std::make_shared<ByteArrayOutputStream>() {
    // TODO: Implement newDataOutput
    return nullptr;
}

ByteArrayDataOutput ByteStreams::newDataOutput(int size) {
    // TODO: Implement newDataOutput
    return nullptr;
}

return ByteStreams::newDataOutput(std::make_shared<ByteArrayOutputStream>(size) {
    // TODO: Implement newDataOutput
    return nullptr;
}

ByteArrayDataOutput ByteStreams::newDataOutput(ByteArrayOutputStream byteArrayOutputSteam) {
    // TODO: Implement newDataOutput
    return nullptr;
}

OutputStream ByteStreams::nullOutputStream() {
    // TODO: Implement nullOutputStream
    return nullptr;
}

InputStream ByteStreams::limit(InputStream in, long limit) {
    // TODO: Implement limit
    return nullptr;
}

void ByteStreams::readFully(InputStream in, byte[] b) {
    // TODO: Implement readFully
}

void ByteStreams::readFully(InputStream in, byte[] b, int off, int len) {
    // TODO: Implement readFully
}

void ByteStreams::skipFully(InputStream in, long n) {
    // TODO: Implement skipFully
}

long ByteStreams::skipUpTo(InputStream in, long n) {
    // TODO: Implement skipUpTo
    return 0;
}

long ByteStreams::skipSafely(InputStream in, long n) {
    // TODO: Implement skipSafely
    return 0;
}

int ByteStreams::read(InputStream in, byte[] b, int off, int len) {
    // TODO: Implement read
    return 0;
}

} // namespace io
} // namespace common
} // namespace google
} // namespace com
