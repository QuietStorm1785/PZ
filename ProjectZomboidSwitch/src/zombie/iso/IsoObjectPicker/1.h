#pragma once

namespace zombie {
namespace iso {

// Placeholder for Java's anonymous comparator class for ClickObject
class ClickObjectComparator {
public:
    bool operator()(const ClickObject& a, const ClickObject& b) const {
        // TODO: Implement actual comparison logic based on score or other fields
        return a.score < b.score;
    }
};

} // namespace iso
} // namespace zombie
