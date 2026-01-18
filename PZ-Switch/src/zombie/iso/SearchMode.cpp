#include "zombie/iso/SearchMode.h"

namespace zombie {
namespace iso {

SearchMode SearchMode::getInstance() {
 // TODO: Implement getInstance
 return nullptr;
}

private
SearchMode::SearchMode() {
 // TODO: Implement SearchMode
 return nullptr;
}

float SearchMode::getFadeTime() {
 // TODO: Implement getFadeTime
 return 0;
}

void SearchMode::setFadeTime(float _fadeTime) {
 // TODO: Implement setFadeTime
}

bool SearchMode::isOverride(int plrIdx) {
 // TODO: Implement isOverride
 return false;
}

void SearchMode::setOverride(int plrIdx, bool enabled) {
 // TODO: Implement setOverride
}

bool SearchMode::isEnabled(int plrIdx) {
 // TODO: Implement isEnabled
 return false;
}

void SearchMode::setEnabled(int plrIdx, bool b) {
 // TODO: Implement setEnabled
}

void SearchMode::FadeIn(int int0) {
 // TODO: Implement FadeIn
}

void SearchMode::FadeOut(int int0) {
 // TODO: Implement FadeOut
}

void SearchMode::update() {
 // TODO: Implement update
}

void SearchMode::reset() {
 // TODO: Implement reset
}

public
SearchMode::PlayerSearchMode(int index, SearchMode sm) {
 // TODO: Implement PlayerSearchMode
 return nullptr;
}

bool SearchMode::isShaderEnabled() {
 // TODO: Implement isShaderEnabled
 return false;
}

bool SearchMode::isPlayerExterior() {
 // TODO: Implement isPlayerExterior
 return false;
}

float SearchMode::getShaderBlur() {
 // TODO: Implement getShaderBlur
 return 0;
}

float SearchMode::getShaderDesat() {
 // TODO: Implement getShaderDesat
 return 0;
}

float SearchMode::getShaderRadius() {
 // TODO: Implement getShaderRadius
 return 0;
}

float SearchMode::getShaderGradientWidth() {
 // TODO: Implement getShaderGradientWidth
 return 0;
}

float SearchMode::getShaderDarkness() {
 // TODO: Implement getShaderDarkness
 return 0;
}

void SearchMode::update() {
 // TODO: Implement update
}

private
SearchMode::SearchModeFloat(float float0, float float1, float float2) {
 // TODO: Implement SearchModeFloat
 return nullptr;
}

void SearchMode::set(float _exterior, float _targetExterior, float _interior,
 float _targetInterior) {
 // TODO: Implement set
}

void SearchMode::setTargets(float _targetExterior, float _targetInterior) {
 // TODO: Implement setTargets
}

float SearchMode::getExterior() {
 // TODO: Implement getExterior
 return 0;
}

void SearchMode::setExterior(float _exterior) {
 // TODO: Implement setExterior
}

float SearchMode::getTargetExterior() {
 // TODO: Implement getTargetExterior
 return 0;
}

void SearchMode::setTargetExterior(float _targetExterior) {
 // TODO: Implement setTargetExterior
}

float SearchMode::getInterior() {
 // TODO: Implement getInterior
 return 0;
}

void SearchMode::setInterior(float _interior) {
 // TODO: Implement setInterior
}

float SearchMode::getTargetInterior() {
 // TODO: Implement getTargetInterior
 return 0;
}

void SearchMode::setTargetInterior(float _targetInterior) {
 // TODO: Implement setTargetInterior
}

void SearchMode::update(float delta) {
 // TODO: Implement update
}

void SearchMode::equalise() {
 // TODO: Implement equalise
}

void SearchMode::reset() {
 // TODO: Implement reset
}

float SearchMode::getMin() {
 // TODO: Implement getMin
 return 0;
}

float SearchMode::getMax() {
 // TODO: Implement getMax
 return 0;
}

float SearchMode::getStepsize() {
 // TODO: Implement getStepsize
 return 0;
}

} // namespace iso
} // namespace zombie
