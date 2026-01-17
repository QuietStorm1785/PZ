#include "zombie/ui/TextManager.h"

namespace zombie {
namespace ui {

void TextManager::DrawString(double x, double y, const std::string &str) {
  // TODO: Implement DrawString
}

void TextManager::DrawString(double x, double y, const std::string &str,
                             double r, double g, double b, double a) {
  // TODO: Implement DrawString
}

void TextManager::DrawString(UIFont _font, double x, double y, double zoom,
                             const std::string &str, double r, double g,
                             double b, double a) {
  // TODO: Implement DrawString
}

void TextManager::DrawString(UIFont _font, double x, double y,
                             const std::string &str, double r, double g,
                             double b, double a) {
  // TODO: Implement DrawString
}

void TextManager::DrawStringUntrimmed(UIFont _font, double x, double y,
                                      const std::string &str, double r,
                                      double g, double b, double a) {
  // TODO: Implement DrawStringUntrimmed
}

void TextManager::DrawStringCentre(double x, double y, const std::string &str,
                                   double r, double g, double b, double a) {
  // TODO: Implement DrawStringCentre
}

void TextManager::DrawStringCentre(UIFont _font, double x, double y,
                                   const std::string &str, double r, double g,
                                   double b, double a) {
  // TODO: Implement DrawStringCentre
}

void TextManager::DrawStringCentreDefered(UIFont _font, double x, double y,
                                          const std::string &str, double r,
                                          double g, double b, double a) {
  // TODO: Implement DrawStringCentreDefered
}

void TextManager::DrawTextFromGameWorld() {
  // TODO: Implement DrawTextFromGameWorld
}

void TextManager::DrawStringRight(double x, double y, const std::string &str,
                                  double r, double g, double b, double a) {
  // TODO: Implement DrawStringRight
}

TextDrawObject TextManager::GetDrawTextObject(const std::string &str,
                                              int maxLineWidth,
                                              bool restrictImages) {
  // TODO: Implement GetDrawTextObject
  return nullptr;
}

void TextManager::DrawTextObject(double x, double y, TextDrawObject td) {
  // TODO: Implement DrawTextObject
}

void TextManager::DrawStringBBcode(UIFont _font, double x, double y,
                                   const std::string &str, double r, double g,
                                   double b, double a) {
  // TODO: Implement DrawStringBBcode
}

AngelCodeFont TextManager::getNormalFromFontSize(int points) {
  // TODO: Implement getNormalFromFontSize
  return nullptr;
}

AngelCodeFont TextManager::getFontFromEnum(UIFont _font) {
  // TODO: Implement getFontFromEnum
  return nullptr;
}

int TextManager::getFontHeight(UIFont fontID) {
  // TODO: Implement getFontHeight
  return 0;
}

void TextManager::DrawStringRight(UIFont _font, double x, double y,
                                  const std::string &str, double r, double g,
                                  double b, double a) {
  // TODO: Implement DrawStringRight
}

std::string TextManager::getFontFilePath(const std::string &string3,
                                         const std::string &string0,
                                         const std::string &string2) {
  // TODO: Implement getFontFilePath
  return "";
}

void TextManager::Init() {
  // TODO: Implement Init
}

int TextManager::MeasureStringX(UIFont _font, const std::string &str) {
  // TODO: Implement MeasureStringX
  return 0;
}

int TextManager::MeasureStringY(UIFont _font, const std::string &str) {
  // TODO: Implement MeasureStringY
  return 0;
}

int TextManager::MeasureFont(UIFont _font) {
  // TODO: Implement MeasureFont
  return 0;
}

public
TextManager::DeferedTextDraw(UIFont uIFont, double double0, double double1,
                             const std::string &string, double double2,
                             double double3, double double4, double double5) {
  // TODO: Implement DeferedTextDraw
  return nullptr;
}

void TextManager::draw(UIFont var1, double var2, double var4,
                       const std::string &var6, double var7, double var9,
                       double var11, double var13) {
  // TODO: Implement draw
}

} // namespace ui
} // namespace zombie
