#pragma once
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace de {
namespace jarnbjo {
namespace util {
namespace io {

class HuffmanNode; // forward

class ByteArrayBitInputStream {
public:
	explicit ByteArrayBitInputStream(const std::vector<uint8_t>& src, int endian = 0)
		: source_(src), currentByte_(0), endian_(endian), byteIndex_(0), bitIndex_(endian == 0 ? 0 : 7) {
		if (source_.empty()) throw std::invalid_argument("source cannot be empty");
		currentByte_ = source_[0];
	}

	bool getBit() {
		if (endian_ == 0) {
			if (bitIndex_ > 7) {
				bitIndex_ = 0;
				++byteIndex_;
				currentByte_ = source_.at(byteIndex_);
			}
			return (currentByte_ & (1u << bitIndex_++)) != 0;
		} else {
			if (bitIndex_ < 0) {
				bitIndex_ = 7;
				++byteIndex_;
				currentByte_ = source_.at(byteIndex_);
			}
			return (currentByte_ & (1u << bitIndex_--)) != 0;
		}
	}

	uint32_t getInt(int bits) {
		if (bits > 32) throw std::invalid_argument("bits must be <= 32");
		uint32_t value = 0;
		if (endian_ == 0) {
			for (int i = 0; i < bits; ++i) if (getBit()) value |= (1u << i);
		} else {
			if (bitIndex_ < 0) { bitIndex_ = 7; currentByte_ = source_.at(++byteIndex_); }
			if (bits <= bitIndex_ + 1) {
				uint32_t b = static_cast<uint32_t>(currentByte_) & 0xFFu;
				int shift = 1 + bitIndex_ - bits;
				uint32_t mask = ((1u << bits) - 1u) << shift;
				value = (b & mask) >> shift;
				bitIndex_ -= bits;
			} else {
				value = ((static_cast<uint32_t>(currentByte_) & 0xFFu) & ((1u << (bitIndex_ + 1)) - 1u)) << (bits - bitIndex_ - 1);
				bits -= (bitIndex_ + 1);
				currentByte_ = source_.at(++byteIndex_);
				while (bits >= 8) {
					bits -= 8;
					value |= (static_cast<uint32_t>(source_.at(byteIndex_)) & 0xFFu) << bits;
					currentByte_ = source_.at(++byteIndex_);
				}
				if (bits > 0) {
					uint32_t b = static_cast<uint32_t>(source_.at(byteIndex_)) & 0xFFu;
					value |= (b >> (8 - bits)) & ((1u << bits) - 1u);
					bitIndex_ = 7 - bits;
				} else {
					currentByte_ = source_.at(--byteIndex_);
					bitIndex_ = -1;
				}
			}
		}
		return value;
	}

	int32_t getSignedInt(int bits) {
		uint32_t v = getInt(bits);
		if (v >= (1u << (bits - 1))) v -= (1u << bits);
		return static_cast<int32_t>(v);
	}

	int32_t getInt(const HuffmanNode& node);

	uint64_t getLong(int bits) {
		if (bits > 64) throw std::invalid_argument("bits must be <= 64");
		uint64_t value = 0;
		if (endian_ == 0) {
			for (int i = 0; i < bits; ++i) if (getBit()) value |= (1ull << i);
		} else {
			for (int i = bits - 1; i >= 0; --i) if (getBit()) value |= (1ull << i);
		}
		return value;
	}

	int32_t readSignedRice(int k) {
		if (endian_ == 0) throw std::logic_error("readSignedRice supported only in big endian mode");
		int m = -1, bits = 0, val = 0;
		uint8_t b = source_.at(byteIndex_);
		do {
			++m;
			if (bitIndex_ < 0) { bitIndex_ = 7; ++byteIndex_; b = source_.at(byteIndex_); }
		} while ((b & (1u << bitIndex_--)) == 0);
		if (bitIndex_ < 0) { bitIndex_ = 7; ++byteIndex_; }
		if (k <= bitIndex_ + 1) {
			uint32_t cur = static_cast<uint32_t>(source_.at(byteIndex_)) & 0xFFu;
			int sh = 1 + bitIndex_ - k;
			uint32_t mask = ((1u << k) - 1u) << sh;
			bits = (cur & mask) >> sh;
			bitIndex_ -= k;
		} else {
			bits = (static_cast<uint32_t>(source_.at(byteIndex_)) & 0xFFu & ((1u << (bitIndex_ + 1)) - 1u)) << (k - bitIndex_ - 1);
			int rem = k - (bitIndex_ + 1);
			++byteIndex_;
			while (rem >= 8) { rem -= 8; bits |= (static_cast<uint32_t>(source_.at(byteIndex_)) & 0xFFu) << rem; ++byteIndex_; }
			if (rem > 0) {
				uint32_t cur = static_cast<uint32_t>(source_.at(byteIndex_)) & 0xFFu;
				bits |= (cur >> (8 - rem)) & ((1u << rem) - 1u);
				bitIndex_ = 7 - rem;
			} else {
				--byteIndex_;
				bitIndex_ = -1;
			}
		}
		val = (m << k) | bits;
		return (val & 1) ? -(val >> 1) - 1 : (val >> 1);
	}

	void readSignedRice(int k, std::vector<int>& out, int off, int len) {
		if (endian_ == 0) throw std::logic_error("readSignedRice supported only in big endian mode");
		for (int i = off; i < off + len; ++i) out[i] = readSignedRice(k);
	}

	void align() {
		if (endian_ == 1 && bitIndex_ >= 0) { bitIndex_ = 7; ++byteIndex_; }
		else if (endian_ == 0 && bitIndex_ <= 7) { bitIndex_ = 0; ++byteIndex_; }
	}

	void setEndian(int e) {
		if (endian_ == 1 && e == 0) { bitIndex_ = 0; ++byteIndex_; }
		else if (endian_ == 0 && e == 1) { bitIndex_ = 7; ++byteIndex_; }
		endian_ = e;
	}

	const std::vector<uint8_t>& getSource() const { return source_; }

private:
	std::vector<uint8_t> source_;
	uint8_t currentByte_;
	int endian_;
	size_t byteIndex_;
	int bitIndex_;
};

} // namespace io
} // namespace util
} // namespace jarnbjo
} // namespace de

