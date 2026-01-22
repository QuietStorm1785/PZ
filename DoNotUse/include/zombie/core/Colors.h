#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {


class Colors {
public:
   private static const std::vector<Color> colors = std::make_unique<std::vector<>>();
   private static const std::unordered_map<std::string, Color> colorMap = std::make_unique<std::unordered_map<>>();
   private static const std::vector<std::string> colorNames = std::make_unique<std::vector<>>();
   private static const std::unordered_set<std::string> colorSet = std::make_unique<std::unordered_set<>>();
    static const Color IndianRed = addColor("IndianRed", std::make_shared<Color>(0.804F, 0.361F, 0.361F));
    static const Color LightCoral = addColor("LightCoral", std::make_shared<Color>(0.941F, 0.502F, 0.502F));
    static const Color Salmon = addColor("Salmon", std::make_shared<Color>(0.98F, 0.502F, 0.447F));
    static const Color DarkSalmon = addColor("DarkSalmon", std::make_shared<Color>(0.914F, 0.588F, 0.478F));
    static const Color LightSalmon = addColor("LightSalmon", std::make_shared<Color>(1.0F, 0.627F, 0.478F));
    static const Color Crimson = addColor("Crimson", std::make_shared<Color>(0.863F, 0.078F, 0.235F));
    static const Color Red = addColor("Red", std::make_shared<Color>(1.0F, 0.0F, 0.0F));
    static const Color FireBrick = addColor("FireBrick", std::make_shared<Color>(0.698F, 0.133F, 0.133F));
    static const Color DarkRed = addColor("DarkRed", std::make_shared<Color>(0.545F, 0.0F, 0.0F));
    static const Color Pink = addColor("Pink", std::make_shared<Color>(1.0F, 0.753F, 0.796F));
    static const Color LightPink = addColor("LightPink", std::make_shared<Color>(1.0F, 0.714F, 0.757F));
    static const Color HotPink = addColor("HotPink", std::make_shared<Color>(1.0F, 0.412F, 0.706F));
    static const Color DeepPink = addColor("DeepPink", std::make_shared<Color>(1.0F, 0.078F, 0.576F));
    static const Color MediumVioletRed = addColor("MediumVioletRed", std::make_shared<Color>(0.78F, 0.082F, 0.522F));
    static const Color PaleVioletRed = addColor("PaleVioletRed", std::make_shared<Color>(0.859F, 0.439F, 0.576F));
    static const Color Coral = addColor("Coral", std::make_shared<Color>(1.0F, 0.498F, 0.314F));
    static const Color Tomato = addColor("Tomato", std::make_shared<Color>(1.0F, 0.388F, 0.278F));
    static const Color OrangeRed = addColor("OrangeRed", std::make_shared<Color>(1.0F, 0.271F, 0.0F));
    static const Color DarkOrange = addColor("DarkOrange", std::make_shared<Color>(1.0F, 0.549F, 0.0F));
    static const Color Orange = addColor("Orange", std::make_shared<Color>(1.0F, 0.647F, 0.0F));
    static const Color Gold = addColor("Gold", std::make_shared<Color>(1.0F, 0.843F, 0.0F));
    static const Color Yellow = addColor("Yellow", std::make_shared<Color>(1.0F, 1.0F, 0.0F));
    static const Color LightYellow = addColor("LightYellow", std::make_shared<Color>(1.0F, 1.0F, 0.878F));
    static const Color LemonChiffon = addColor("LemonChiffon", std::make_shared<Color>(1.0F, 0.98F, 0.804F));
    static const Color LightGoldenrodYellow = addColor("LightGoldenrodYellow", std::make_shared<Color>(0.98F, 0.98F, 0.824F));
    static const Color PapayaWhip = addColor("PapayaWhip", std::make_shared<Color>(1.0F, 0.937F, 0.835F));
    static const Color Moccasin = addColor("Moccasin", std::make_shared<Color>(1.0F, 0.894F, 0.71F));
    static const Color PeachPu = addColor("PeachPu", std::make_shared<Color>(1.0F, 0.855F, 0.725F));
    static const Color PaleGoldenrod = addColor("PaleGoldenrod", std::make_shared<Color>(0.933F, 0.91F, 0.667F));
    static const Color Khaki = addColor("Khaki", std::make_shared<Color>(0.941F, 0.902F, 0.549F));
    static const Color DarkKhaki = addColor("DarkKhaki", std::make_shared<Color>(0.741F, 0.718F, 0.42F));
    static const Color Lavender = addColor("Lavender", std::make_shared<Color>(0.902F, 0.902F, 0.98F));
    static const Color Thistle = addColor("Thistle", std::make_shared<Color>(0.847F, 0.749F, 0.847F));
    static const Color Plum = addColor("Plum", std::make_shared<Color>(0.867F, 0.627F, 0.867F));
    static const Color Violet = addColor("Violet", std::make_shared<Color>(0.933F, 0.51F, 0.933F));
    static const Color Orchid = addColor("Orchid", std::make_shared<Color>(0.855F, 0.439F, 0.839F));
    static const Color Fuchsia = addColor("Fuchsia", std::make_shared<Color>(1.0F, 0.0F, 1.0F));
    static const Color Magenta = addColor("Magenta", std::make_shared<Color>(1.0F, 0.0F, 1.0F));
    static const Color MediumOrchid = addColor("MediumOrchid", std::make_shared<Color>(0.729F, 0.333F, 0.827F));
    static const Color MediumPurple = addColor("MediumPurple", std::make_shared<Color>(0.576F, 0.439F, 0.859F));
    static const Color BlueViolet = addColor("BlueViolet", std::make_shared<Color>(0.541F, 0.169F, 0.886F));
    static const Color DarkViolet = addColor("DarkViolet", std::make_shared<Color>(0.58F, 0.0F, 0.827F));
    static const Color DarkOrchid = addColor("DarkOrchid", std::make_shared<Color>(0.6F, 0.196F, 0.8F));
    static const Color DarkMagenta = addColor("DarkMagenta", std::make_shared<Color>(0.545F, 0.0F, 0.545F));
    static const Color Purple = addColor("Purple", std::make_shared<Color>(0.502F, 0.0F, 0.502F));
    static const Color Indigo = addColor("Indigo", std::make_shared<Color>(0.294F, 0.0F, 0.51F));
    static const Color SlateBlue = addColor("SlateBlue", std::make_shared<Color>(0.416F, 0.353F, 0.804F));
    static const Color DarkSlateBlue = addColor("DarkSlateBlue", std::make_shared<Color>(0.282F, 0.239F, 0.545F));
    static const Color GreenYellow = addColor("GreenYellow", std::make_shared<Color>(0.678F, 1.0F, 0.184F));
    static const Color Chartreuse = addColor("Chartreuse", std::make_shared<Color>(0.498F, 1.0F, 0.0F));
    static const Color LawnGreen = addColor("LawnGreen", std::make_shared<Color>(0.486F, 0.988F, 0.0F));
    static const Color Lime = addColor("Lime", std::make_shared<Color>(0.0F, 1.0F, 0.0F));
    static const Color LimeGreen = addColor("LimeGreen", std::make_shared<Color>(0.196F, 0.804F, 0.196F));
    static const Color PaleGreen = addColor("PaleGreen", std::make_shared<Color>(0.596F, 0.984F, 0.596F));
    static const Color LightGreen = addColor("LightGreen", std::make_shared<Color>(0.565F, 0.933F, 0.565F));
    static const Color MediumSpringGreen = addColor("MediumSpringGreen", std::make_shared<Color>(0.0F, 0.98F, 0.604F));
    static const Color SpringGreen = addColor("SpringGreen", std::make_shared<Color>(0.0F, 1.0F, 0.498F));
    static const Color MediumSeaGreen = addColor("MediumSeaGreen", std::make_shared<Color>(0.235F, 0.702F, 0.443F));
    static const Color SeaGreen = addColor("SeaGreen", std::make_shared<Color>(0.18F, 0.545F, 0.341F));
    static const Color ForestGreen = addColor("ForestGreen", std::make_shared<Color>(0.133F, 0.545F, 0.133F));
    static const Color Green = addColor("Green", std::make_shared<Color>(0.0F, 0.502F, 0.0F));
    static const Color DarkGreen = addColor("DarkGreen", std::make_shared<Color>(0.0F, 0.392F, 0.0F));
    static const Color YellowGreen = addColor("YellowGreen", std::make_shared<Color>(0.604F, 0.804F, 0.196F));
    static const Color OliveDrab = addColor("OliveDrab", std::make_shared<Color>(0.42F, 0.557F, 0.137F));
    static const Color Olive = addColor("Olive", std::make_shared<Color>(0.502F, 0.502F, 0.0F));
    static const Color DarkOliveGreen = addColor("DarkOliveGreen", std::make_shared<Color>(0.333F, 0.42F, 0.184F));
    static const Color MediumAquamarine = addColor("MediumAquamarine", std::make_shared<Color>(0.4F, 0.804F, 0.667F));
    static const Color DarkSeaGreen = addColor("DarkSeaGreen", std::make_shared<Color>(0.561F, 0.737F, 0.561F));
    static const Color LightSeaGreen = addColor("LightSeaGreen", std::make_shared<Color>(0.125F, 0.698F, 0.667F));
    static const Color DarkCyan = addColor("DarkCyan", std::make_shared<Color>(0.0F, 0.545F, 0.545F));
    static const Color Teal = addColor("Teal", std::make_shared<Color>(0.0F, 0.502F, 0.502F));
    static const Color Aqua = addColor("Aqua", std::make_shared<Color>(0.0F, 1.0F, 1.0F));
    static const Color Cyan = addColor("Cyan", std::make_shared<Color>(0.0F, 1.0F, 1.0F));
    static const Color LightCyan = addColor("LightCyan", std::make_shared<Color>(0.878F, 1.0F, 1.0F));
    static const Color PaleTurquoise = addColor("PaleTurquoise", std::make_shared<Color>(0.686F, 0.933F, 0.933F));
    static const Color Aquamarine = addColor("Aquamarine", std::make_shared<Color>(0.498F, 1.0F, 0.831F));
    static const Color Turquoise = addColor("Turquoise", std::make_shared<Color>(0.251F, 0.878F, 0.816F));
    static const Color MediumTurquoise = addColor("MediumTurquoise", std::make_shared<Color>(0.282F, 0.82F, 0.8F));
    static const Color DarkTurquoise = addColor("DarkTurquoise", std::make_shared<Color>(0.0F, 0.808F, 0.82F));
    static const Color CadetBlue = addColor("CadetBlue", std::make_shared<Color>(0.373F, 0.62F, 0.627F));
    static const Color SteelBlue = addColor("SteelBlue", std::make_shared<Color>(0.275F, 0.51F, 0.706F));
    static const Color LightSteelBlue = addColor("LightSteelBlue", std::make_shared<Color>(0.69F, 0.769F, 0.871F));
    static const Color PowderBlue = addColor("PowderBlue", std::make_shared<Color>(0.69F, 0.878F, 0.902F));
    static const Color LightBlue = addColor("LightBlue", std::make_shared<Color>(0.678F, 0.847F, 0.902F));
    static const Color SkyBlue = addColor("SkyBlue", std::make_shared<Color>(0.529F, 0.808F, 0.922F));
    static const Color LightSkyBlue = addColor("LightSkyBlue", std::make_shared<Color>(0.529F, 0.808F, 0.98F));
    static const Color DeepSkyBlue = addColor("DeepSkyBlue", std::make_shared<Color>(0.0F, 0.749F, 1.0F));
    static const Color DodgerBlue = addColor("DodgerBlue", std::make_shared<Color>(0.118F, 0.565F, 1.0F));
    static const Color CornFlowerBlue = addColor("CornFlowerBlue", std::make_shared<Color>(0.392F, 0.584F, 0.929F));
    static const Color MediumSlateBlue = addColor("MediumSlateBlue", std::make_shared<Color>(0.482F, 0.408F, 0.933F));
    static const Color RoyalBlue = addColor("RoyalBlue", std::make_shared<Color>(0.255F, 0.412F, 0.882F));
    static const Color Blue = addColor("Blue", std::make_shared<Color>(0.0F, 0.0F, 1.0F));
    static const Color MediumBlue = addColor("MediumBlue", std::make_shared<Color>(0.0F, 0.0F, 0.804F));
    static const Color DarkBlue = addColor("DarkBlue", std::make_shared<Color>(0.0F, 0.0F, 0.545F));
    static const Color Navy = addColor("Navy", std::make_shared<Color>(0.0F, 0.0F, 0.502F));
    static const Color MidnightBlue = addColor("MidnightBlue", std::make_shared<Color>(0.098F, 0.098F, 0.439F));
    static const Color CornSilk = addColor("CornSilk", std::make_shared<Color>(1.0F, 0.973F, 0.863F));
    static const Color BlanchedAlmond = addColor("BlanchedAlmond", std::make_shared<Color>(1.0F, 0.922F, 0.804F));
    static const Color Bisque = addColor("Bisque", std::make_shared<Color>(1.0F, 0.894F, 0.769F));
    static const Color NavajoWhite = addColor("NavajoWhite", std::make_shared<Color>(1.0F, 0.871F, 0.678F));
    static const Color Wheat = addColor("Wheat", std::make_shared<Color>(0.961F, 0.871F, 0.702F));
    static const Color BurlyWood = addColor("BurlyWood", std::make_shared<Color>(0.871F, 0.722F, 0.529F));
    static const Color Tan = addColor("Tan", std::make_shared<Color>(0.824F, 0.706F, 0.549F));
    static const Color RosyBrown = addColor("RosyBrown", std::make_shared<Color>(0.737F, 0.561F, 0.561F));
    static const Color SandyBrown = addColor("SandyBrown", std::make_shared<Color>(0.957F, 0.643F, 0.376F));
    static const Color Goldenrod = addColor("Goldenrod", std::make_shared<Color>(0.855F, 0.647F, 0.125F));
    static const Color DarkGoldenrod = addColor("DarkGoldenrod", std::make_shared<Color>(0.722F, 0.525F, 0.043F));
    static const Color Peru = addColor("Peru", std::make_shared<Color>(0.804F, 0.522F, 0.247F));
    static const Color Chocolate = addColor("Chocolate", std::make_shared<Color>(0.824F, 0.412F, 0.118F));
    static const Color SaddleBrown = addColor("SaddleBrown", std::make_shared<Color>(0.545F, 0.271F, 0.075F));
    static const Color Sienna = addColor("Sienna", std::make_shared<Color>(0.627F, 0.322F, 0.176F));
    static const Color Brown = addColor("Brown", std::make_shared<Color>(0.647F, 0.165F, 0.165F));
    static const Color Maroon = addColor("Maroon", std::make_shared<Color>(0.502F, 0.0F, 0.0F));

    static Color addColor(const std::string& var0, Color var1) {
      colors.push_back(var1);
      colorMap.put(var0.toLowerCase(), var1);
      colorNames.push_back(var0);
      colorSet.push_back(var0.toLowerCase());
    return var1;
   }

    static Color GetRandomColor() {
      return colors.get(Rand.Next(0, colors.size() - 1));
   }

    static Color GetColorFromIndex(int var0) {
      return colors.get(var0);
   }

    static int GetColorsCount() {
      return colors.size();
   }

    static Color GetColorByName(const std::string& var0) {
      return colorMap.get(var0.toLowerCase());
   }

   public static std::vector<std::string> GetColorNames() {
    return colorNames;
   }

    static bool ColorExists(const std::string& var0) {
      return colorSet.contains(var0.toLowerCase());
   }
}
} // namespace core
} // namespace zombie
