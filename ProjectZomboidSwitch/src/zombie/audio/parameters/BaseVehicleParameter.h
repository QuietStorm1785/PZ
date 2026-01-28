#pragma once
#include <string>
#include <memory>

namespace zombie {
namespace audio {

class BaseVehicleParameter {
public:
    BaseVehicleParameter(const std::string& name) : name_(name) {}
    virtual ~BaseVehicleParameter() = default;
    virtual float calculateCurrentValue() const { return 0.0f; }
    virtual void setCurrentValue(float value) {}
    const std::string& getName() const { return name_; }
private:
    std::string name_;
};

} // namespace audio
} // namespace zombie
