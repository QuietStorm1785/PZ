#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class Colors {
public:
private
 static ArrayList<Color> colors = std::make_unique<ArrayList<>>();
private
 static HashMap<String, Color> colorMap = std::make_unique<HashMap<>>();
private
 static ArrayList<String> colorNames = std::make_unique<ArrayList<>>();
private
 static HashSet<String> colorSet = std::make_unique<HashSet<>>();
 static const Color IndianRed =
 addColor("IndianRed", new Color(0.804F, 0.361F, 0.361F);
 static const Color LightCoral =
 addColor("LightCoral", new Color(0.941F, 0.502F, 0.502F);
 static const Color Salmon =
 addColor("Salmon", new Color(0.98F, 0.502F, 0.447F);
 static const Color DarkSalmon =
 addColor("DarkSalmon", new Color(0.914F, 0.588F, 0.478F);
 static const Color LightSalmon =
 addColor("LightSalmon", new Color(1.0F, 0.627F, 0.478F);
 static const Color Crimson =
 addColor("Crimson", new Color(0.863F, 0.078F, 0.235F);
 static const Color Red = addColor("Red", new Color(1.0F, 0.0F, 0.0F);
 static const Color FireBrick =
 addColor("FireBrick", new Color(0.698F, 0.133F, 0.133F);
 static const Color DarkRed =
 addColor("DarkRed", new Color(0.545F, 0.0F, 0.0F);
 static const Color Pink = addColor("Pink", new Color(1.0F, 0.753F, 0.796F);
 static const Color LightPink =
 addColor("LightPink", new Color(1.0F, 0.714F, 0.757F);
 static const Color HotPink =
 addColor("HotPink", new Color(1.0F, 0.412F, 0.706F);
 static const Color DeepPink =
 addColor("DeepPink", new Color(1.0F, 0.078F, 0.576F);
 static const Color MediumVioletRed =
 addColor("MediumVioletRed", new Color(0.78F, 0.082F, 0.522F);
 static const Color PaleVioletRed =
 addColor("PaleVioletRed", new Color(0.859F, 0.439F, 0.576F);
 static const Color Coral = addColor("Coral", new Color(1.0F, 0.498F, 0.314F);
 static const Color Tomato =
 addColor("Tomato", new Color(1.0F, 0.388F, 0.278F);
 static const Color OrangeRed =
 addColor("OrangeRed", new Color(1.0F, 0.271F, 0.0F);
 static const Color DarkOrange =
 addColor("DarkOrange", new Color(1.0F, 0.549F, 0.0F);
 static const Color Orange = addColor("Orange", new Color(1.0F, 0.647F, 0.0F);
 static const Color Gold = addColor("Gold", new Color(1.0F, 0.843F, 0.0F);
 static const Color Yellow = addColor("Yellow", new Color(1.0F, 1.0F, 0.0F);
 static const Color LightYellow =
 addColor("LightYellow", new Color(1.0F, 1.0F, 0.878F);
 static const Color LemonChiffon =
 addColor("LemonChiffon", new Color(1.0F, 0.98F, 0.804F);
 static const Color LightGoldenrodYellow =
 addColor("LightGoldenrodYellow", new Color(0.98F, 0.98F, 0.824F);
 static const Color PapayaWhip =
 addColor("PapayaWhip", new Color(1.0F, 0.937F, 0.835F);
 static const Color Moccasin =
 addColor("Moccasin", new Color(1.0F, 0.894F, 0.71F);
 static const Color PeachPu =
 addColor("PeachPu", new Color(1.0F, 0.855F, 0.725F);
 static const Color PaleGoldenrod =
 addColor("PaleGoldenrod", new Color(0.933F, 0.91F, 0.667F);
 static const Color Khaki =
 addColor("Khaki", new Color(0.941F, 0.902F, 0.549F);
 static const Color DarkKhaki =
 addColor("DarkKhaki", new Color(0.741F, 0.718F, 0.42F);
 static const Color Lavender =
 addColor("Lavender", new Color(0.902F, 0.902F, 0.98F);
 static const Color Thistle =
 addColor("Thistle", new Color(0.847F, 0.749F, 0.847F);
 static const Color Plum = addColor("Plum", new Color(0.867F, 0.627F, 0.867F);
 static const Color Violet =
 addColor("Violet", new Color(0.933F, 0.51F, 0.933F);
 static const Color Orchid =
 addColor("Orchid", new Color(0.855F, 0.439F, 0.839F);
 static const Color Fuchsia = addColor("Fuchsia", new Color(1.0F, 0.0F, 1.0F);
 static const Color Magenta = addColor("Magenta", new Color(1.0F, 0.0F, 1.0F);
 static const Color MediumOrchid =
 addColor("MediumOrchid", new Color(0.729F, 0.333F, 0.827F);
 static const Color MediumPurple =
 addColor("MediumPurple", new Color(0.576F, 0.439F, 0.859F);
 static const Color BlueViolet =
 addColor("BlueViolet", new Color(0.541F, 0.169F, 0.886F);
 static const Color DarkViolet =
 addColor("DarkViolet", new Color(0.58F, 0.0F, 0.827F);
 static const Color DarkOrchid =
 addColor("DarkOrchid", new Color(0.6F, 0.196F, 0.8F);
 static const Color DarkMagenta =
 addColor("DarkMagenta", new Color(0.545F, 0.0F, 0.545F);
 static const Color Purple =
 addColor("Purple", new Color(0.502F, 0.0F, 0.502F);
 static const Color Indigo =
 addColor("Indigo", new Color(0.294F, 0.0F, 0.51F);
 static const Color SlateBlue =
 addColor("SlateBlue", new Color(0.416F, 0.353F, 0.804F);
 static const Color DarkSlateBlue =
 addColor("DarkSlateBlue", new Color(0.282F, 0.239F, 0.545F);
 static const Color GreenYellow =
 addColor("GreenYellow", new Color(0.678F, 1.0F, 0.184F);
 static const Color Chartreuse =
 addColor("Chartreuse", new Color(0.498F, 1.0F, 0.0F);
 static const Color LawnGreen =
 addColor("LawnGreen", new Color(0.486F, 0.988F, 0.0F);
 static const Color Lime = addColor("Lime", new Color(0.0F, 1.0F, 0.0F);
 static const Color LimeGreen =
 addColor("LimeGreen", new Color(0.196F, 0.804F, 0.196F);
 static const Color PaleGreen =
 addColor("PaleGreen", new Color(0.596F, 0.984F, 0.596F);
 static const Color LightGreen =
 addColor("LightGreen", new Color(0.565F, 0.933F, 0.565F);
 static const Color MediumSpringGreen =
 addColor("MediumSpringGreen", new Color(0.0F, 0.98F, 0.604F);
 static const Color SpringGreen =
 addColor("SpringGreen", new Color(0.0F, 1.0F, 0.498F);
 static const Color MediumSeaGreen =
 addColor("MediumSeaGreen", new Color(0.235F, 0.702F, 0.443F);
 static const Color SeaGreen =
 addColor("SeaGreen", new Color(0.18F, 0.545F, 0.341F);
 static const Color ForestGreen =
 addColor("ForestGreen", new Color(0.133F, 0.545F, 0.133F);
 static const Color Green = addColor("Green", new Color(0.0F, 0.502F, 0.0F);
 static const Color DarkGreen =
 addColor("DarkGreen", new Color(0.0F, 0.392F, 0.0F);
 static const Color YellowGreen =
 addColor("YellowGreen", new Color(0.604F, 0.804F, 0.196F);
 static const Color OliveDrab =
 addColor("OliveDrab", new Color(0.42F, 0.557F, 0.137F);
 static const Color Olive = addColor("Olive", new Color(0.502F, 0.502F, 0.0F);
 static const Color DarkOliveGreen =
 addColor("DarkOliveGreen", new Color(0.333F, 0.42F, 0.184F);
 static const Color MediumAquamarine =
 addColor("MediumAquamarine", new Color(0.4F, 0.804F, 0.667F);
 static const Color DarkSeaGreen =
 addColor("DarkSeaGreen", new Color(0.561F, 0.737F, 0.561F);
 static const Color LightSeaGreen =
 addColor("LightSeaGreen", new Color(0.125F, 0.698F, 0.667F);
 static const Color DarkCyan =
 addColor("DarkCyan", new Color(0.0F, 0.545F, 0.545F);
 static const Color Teal = addColor("Teal", new Color(0.0F, 0.502F, 0.502F);
 static const Color Aqua = addColor("Aqua", new Color(0.0F, 1.0F, 1.0F);
 static const Color Cyan = addColor("Cyan", new Color(0.0F, 1.0F, 1.0F);
 static const Color LightCyan =
 addColor("LightCyan", new Color(0.878F, 1.0F, 1.0F);
 static const Color PaleTurquoise =
 addColor("PaleTurquoise", new Color(0.686F, 0.933F, 0.933F);
 static const Color Aquamarine =
 addColor("Aquamarine", new Color(0.498F, 1.0F, 0.831F);
 static const Color Turquoise =
 addColor("Turquoise", new Color(0.251F, 0.878F, 0.816F);
 static const Color MediumTurquoise =
 addColor("MediumTurquoise", new Color(0.282F, 0.82F, 0.8F);
 static const Color DarkTurquoise =
 addColor("DarkTurquoise", new Color(0.0F, 0.808F, 0.82F);
 static const Color CadetBlue =
 addColor("CadetBlue", new Color(0.373F, 0.62F, 0.627F);
 static const Color SteelBlue =
 addColor("SteelBlue", new Color(0.275F, 0.51F, 0.706F);
 static const Color LightSteelBlue =
 addColor("LightSteelBlue", new Color(0.69F, 0.769F, 0.871F);
 static const Color PowderBlue =
 addColor("PowderBlue", new Color(0.69F, 0.878F, 0.902F);
 static const Color LightBlue =
 addColor("LightBlue", new Color(0.678F, 0.847F, 0.902F);
 static const Color SkyBlue =
 addColor("SkyBlue", new Color(0.529F, 0.808F, 0.922F);
 static const Color LightSkyBlue =
 addColor("LightSkyBlue", new Color(0.529F, 0.808F, 0.98F);
 static const Color DeepSkyBlue =
 addColor("DeepSkyBlue", new Color(0.0F, 0.749F, 1.0F);
 static const Color DodgerBlue =
 addColor("DodgerBlue", new Color(0.118F, 0.565F, 1.0F);
 static const Color CornFlowerBlue =
 addColor("CornFlowerBlue", new Color(0.392F, 0.584F, 0.929F);
 static const Color MediumSlateBlue =
 addColor("MediumSlateBlue", new Color(0.482F, 0.408F, 0.933F);
 static const Color RoyalBlue =
 addColor("RoyalBlue", new Color(0.255F, 0.412F, 0.882F);
 static const Color Blue = addColor("Blue", new Color(0.0F, 0.0F, 1.0F);
 static const Color MediumBlue =
 addColor("MediumBlue", new Color(0.0F, 0.0F, 0.804F);
 static const Color DarkBlue =
 addColor("DarkBlue", new Color(0.0F, 0.0F, 0.545F);
 static const Color Navy = addColor("Navy", new Color(0.0F, 0.0F, 0.502F);
 static const Color MidnightBlue =
 addColor("MidnightBlue", new Color(0.098F, 0.098F, 0.439F);
 static const Color CornSilk =
 addColor("CornSilk", new Color(1.0F, 0.973F, 0.863F);
 static const Color BlanchedAlmond =
 addColor("BlanchedAlmond", new Color(1.0F, 0.922F, 0.804F);
 static const Color Bisque =
 addColor("Bisque", new Color(1.0F, 0.894F, 0.769F);
 static const Color NavajoWhite =
 addColor("NavajoWhite", new Color(1.0F, 0.871F, 0.678F);
 static const Color Wheat =
 addColor("Wheat", new Color(0.961F, 0.871F, 0.702F);
 static const Color BurlyWood =
 addColor("BurlyWood", new Color(0.871F, 0.722F, 0.529F);
 static const Color Tan = addColor("Tan", new Color(0.824F, 0.706F, 0.549F);
 static const Color RosyBrown =
 addColor("RosyBrown", new Color(0.737F, 0.561F, 0.561F);
 static const Color SandyBrown =
 addColor("SandyBrown", new Color(0.957F, 0.643F, 0.376F);
 static const Color Goldenrod =
 addColor("Goldenrod", new Color(0.855F, 0.647F, 0.125F);
 static const Color DarkGoldenrod =
 addColor("DarkGoldenrod", new Color(0.722F, 0.525F, 0.043F);
 static const Color Peru = addColor("Peru", new Color(0.804F, 0.522F, 0.247F);
 static const Color Chocolate =
 addColor("Chocolate", new Color(0.824F, 0.412F, 0.118F);
 static const Color SaddleBrown =
 addColor("SaddleBrown", new Color(0.545F, 0.271F, 0.075F);
 static const Color Sienna =
 addColor("Sienna", new Color(0.627F, 0.322F, 0.176F);
 static const Color Brown =
 addColor("Brown", new Color(0.647F, 0.165F, 0.165F);
 static const Color Maroon = addColor("Maroon", new Color(0.502F, 0.0F, 0.0F);

 static Color addColor(const std::string &string, Color color) {
 colors.add(color);
 colorMap.put(string.toLowerCase(), color);
 colorNames.add(string);
 colorSet.add(string.toLowerCase());
 return color;
 }

 static Color GetRandomColor() {
 return colors.get(Rand.Next(0, colors.size() - 1);
 }

 static Color GetColorFromIndex(int index) { return colors.get(index); }

 static int GetColorsCount() { return colors.size(); }

 static Color GetColorByName(const std::string &name) {
 return colorMap.get(name.toLowerCase());
 }

public
 static ArrayList<String> GetColorNames() { return colorNames; }

 static bool ColorExists(const std::string &name) {
 return colorSet.contains(name.toLowerCase());
 }
}
} // namespace core
} // namespace zombie
