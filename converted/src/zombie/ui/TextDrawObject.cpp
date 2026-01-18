#include "zombie/ui/TextDrawObject.h"

namespace zombie {
namespace ui {

public TextDrawObject::TextDrawObject() {
 // TODO: Implement TextDrawObject
 return nullptr;
}

public TextDrawObject::TextDrawObject(int r, int g, int b, bool _allowBBcode) {
 // TODO: Implement TextDrawObject
 return nullptr;
}

void TextDrawObject::setEnabled(bool _enabled) {
 // TODO: Implement setEnabled
}

bool TextDrawObject::getEnabled() {
 // TODO: Implement getEnabled
 return false;
}

void TextDrawObject::setVisibleRadius(int radius) {
 // TODO: Implement setVisibleRadius
}

int TextDrawObject::getVisibleRadius() {
 // TODO: Implement getVisibleRadius
 return 0;
}

void TextDrawObject::setDrawBackground(bool draw) {
 // TODO: Implement setDrawBackground
}

void TextDrawObject::setAllowImages(bool _allowImages) {
 // TODO: Implement setAllowImages
}

void TextDrawObject::setAllowChatIcons(bool _allowChatIcons) {
 // TODO: Implement setAllowChatIcons
}

void TextDrawObject::setAllowColors(bool _allowColors) {
 // TODO: Implement setAllowColors
}

void TextDrawObject::setAllowFonts(bool _allowFonts) {
 // TODO: Implement setAllowFonts
}

void TextDrawObject::setAllowBBcode(bool _allowBBcode) {
 // TODO: Implement setAllowBBcode
}

void TextDrawObject::setAllowAnyImage(bool _allowAnyImage) {
 // TODO: Implement setAllowAnyImage
}

void TextDrawObject::setAllowLineBreaks(bool _allowLineBreaks) {
 // TODO: Implement setAllowLineBreaks
}

void TextDrawObject::setEqualizeLineHeights(bool _equalizeLineHeights) {
 // TODO: Implement setEqualizeLineHeights
}

void TextDrawObject::setCustomTag(const std::string& tag) {
 // TODO: Implement setCustomTag
}

std::string TextDrawObject::getCustomTag() {
 // TODO: Implement getCustomTag
 return "";
}

void TextDrawObject::setValidImages(String[] strings) {
 // TODO: Implement setValidImages
}

void TextDrawObject::setValidFonts(String[] strings) {
 // TODO: Implement setValidFonts
}

void TextDrawObject::setMaxCharsPerLine(int charsperline) {
 // TODO: Implement setMaxCharsPerLine
}

void TextDrawObject::setCustomImageMaxDimensions(int dim) {
 // TODO: Implement setCustomImageMaxDimensions
}

void TextDrawObject::setOutlineColors(int r, int g, int b) {
 // TODO: Implement setOutlineColors
}

void TextDrawObject::setOutlineColors(int r, int g, int b, int a) {
 // TODO: Implement setOutlineColors
}

void TextDrawObject::setOutlineColors(float r, float g, float b) {
 // TODO: Implement setOutlineColors
}

void TextDrawObject::setOutlineColors(float r, float g, float b, float a) {
 // TODO: Implement setOutlineColors
}

void TextDrawObject::setDefaultColors(int r, int g, int b) {
 // TODO: Implement setDefaultColors
}

void TextDrawObject::setDefaultColors(int r, int g, int b, int a) {
 // TODO: Implement setDefaultColors
}

void TextDrawObject::setDefaultColors(float r, float g, float b) {
 // TODO: Implement setDefaultColors
}

void TextDrawObject::setDefaultColors(float r, float g, float b, float a) {
 // TODO: Implement setDefaultColors
}

void TextDrawObject::setHorizontalAlign(const std::string& horz) {
 // TODO: Implement setHorizontalAlign
}

void TextDrawObject::setHorizontalAlign(TextDrawHorizontal horz) {
 // TODO: Implement setHorizontalAlign
}

TextDrawHorizontal TextDrawObject::getHorizontalAlign() {
 // TODO: Implement getHorizontalAlign
 return nullptr;
}

std::string TextDrawObject::getOriginal() {
 // TODO: Implement getOriginal
 return "";
}

std::string TextDrawObject::getUnformatted() {
 // TODO: Implement getUnformatted
 return "";
}

int TextDrawObject::getWidth() {
 // TODO: Implement getWidth
 return 0;
}

int TextDrawObject::getHeight() {
 // TODO: Implement getHeight
 return 0;
}

UIFont TextDrawObject::getDefaultFontEnum() {
 // TODO: Implement getDefaultFontEnum
 return nullptr;
}

bool TextDrawObject::isNullOrZeroLength() {
 // TODO: Implement isNullOrZeroLength
 return false;
}

float TextDrawObject::getInternalClock() {
 // TODO: Implement getInternalClock
 return 0;
}

void TextDrawObject::setInternalTickClock(float ticks) {
 // TODO: Implement setInternalTickClock
}

float TextDrawObject::updateInternalTickClock() {
 // TODO: Implement updateInternalTickClock
 return 0;
}

float TextDrawObject::updateInternalTickClock(float delta) {
 // TODO: Implement updateInternalTickClock
 return 0;
}

void TextDrawObject::setScrambleVal(float value) {
 // TODO: Implement setScrambleVal
}

float TextDrawObject::getScrambleVal() {
 // TODO: Implement getScrambleVal
 return 0;
}

void TextDrawObject::setHearRange(int range) {
 // TODO: Implement setHearRange
}

int TextDrawObject::getHearRange() {
 // TODO: Implement getHearRange
 return 0;
}

bool TextDrawObject::isValidFont(const std::string& string1) {
 // TODO: Implement isValidFont
 return false;
}

bool TextDrawObject::isValidImage(const std::string& string1) {
 // TODO: Implement isValidImage
 return false;
}

int TextDrawObject::tryColorInt(const std::string& string) {
 // TODO: Implement tryColorInt
 return 0;
}

std::string TextDrawObject::readTagValue(char[] chars, int int0) {
 // TODO: Implement readTagValue
 return "";
}

void TextDrawObject::Clear() {
 // TODO: Implement Clear
}

void TextDrawObject::reset() {
 // TODO: Implement reset
}

void TextDrawObject::addNewLine() {
 // TODO: Implement addNewLine
}

void TextDrawObject::addText(const std::string& string) {
 // TODO: Implement addText
}

void TextDrawObject::addWord(const std::string& string) {
 // TODO: Implement addWord
}

void TextDrawObject::addNewElement() {
 // TODO: Implement addNewElement
}

int TextDrawObject::readTag(char[] chars, int int0, const std::string& string0) {
 // TODO: Implement readTag
 return 0;
}

void TextDrawObject::setDefaultFont(UIFont f) {
 // TODO: Implement setDefaultFont
}

void TextDrawObject::setDefaultFontInternal(UIFont uIFont) {
 // TODO: Implement setDefaultFontInternal
}

void TextDrawObject::ReadString(const std::string& str) {
 // TODO: Implement ReadString
}

void TextDrawObject::ReadString(const std::string& str, int maxLineWidth) {
 // TODO: Implement ReadString
}

void TextDrawObject::ReadString(UIFont font, const std::string& str, int maxLineWidth) {
 // TODO: Implement ReadString
}

void TextDrawObject::calculateDimensions() {
 // TODO: Implement calculateDimensions
}

void TextDrawObject::Draw(double x, double y) {
 // TODO: Implement Draw
}

void TextDrawObject::Draw(double x, double y, bool drawOutlines) {
 // TODO: Implement Draw
}

void TextDrawObject::Draw(double x, double y, bool drawOutlines, float alpha) {
 // TODO: Implement Draw
}

void TextDrawObject::Draw(double x, double y, double r, double g, double b, double a, bool drawOutlines) {
 // TODO: Implement Draw
}

void TextDrawObject::Draw(TextDrawHorizontal horz, double x, double y, double r, double g, double b, double a, bool drawOutlines) {
 // TODO: Implement Draw
}

void TextDrawObject::AddBatchedDraw(double x, double y) {
 // TODO: Implement AddBatchedDraw
}

void TextDrawObject::AddBatchedDraw(double x, double y, bool drawOutlines) {
 // TODO: Implement AddBatchedDraw
}

void TextDrawObject::AddBatchedDraw(double x, double y, bool drawOutlines, float alpha) {
 // TODO: Implement AddBatchedDraw
}

void TextDrawObject::AddBatchedDraw(double x, double y, double r, double g, double b, double a, bool drawOutlines) {
 // TODO: Implement AddBatchedDraw
}

void TextDrawObject::AddBatchedDraw(TextDrawHorizontal horz, double x, double y, double r, double g, double b, double a, bool drawOutlines) {
 // TODO: Implement AddBatchedDraw
}

void TextDrawObject::RenderBatch(int playerNum) {
 // TODO: Implement RenderBatch
}

void TextDrawObject::NoRender(int playerNum) {
 // TODO: Implement NoRender
}

void TextDrawObject::DrawRaw(TextDrawHorizontal horz, double x, double y, float r, float g, float b, float a, bool drawOutlines) {
 // TODO: Implement DrawRaw
}

void TextDrawObject::reset() {
 // TODO: Implement reset
}

void TextDrawObject::addText(const std::string& string) {
 // TODO: Implement addText
}

void TextDrawObject::scrambleText(float float0) {
 // TODO: Implement scrambleText
}

void TextDrawObject::trim() {
 // TODO: Implement trim
}

void TextDrawObject::addElement(TextDrawObject.DrawElement drawElement) {
 // TODO: Implement addElement
}

} // namespace ui
} // namespace zombie
