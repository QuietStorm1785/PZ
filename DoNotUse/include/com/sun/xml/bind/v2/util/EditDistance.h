#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace util {


class EditDistance {
public:
   private static const WeakHashMap<SimpleEntry<std::string, std::string>, int> CACHE = std::make_unique<WeakHashMap<>>();
   private int[] cost;
   private int[] back;
    const std::string a;
    const std::string b;

    static int editDistance(const std::string& a, const std::string& b) {
      SimpleEntry<std::string, std::string> entry = new SimpleEntry<>(a, b);
    int result = nullptr;
      if (CACHE.containsKey(entry)) {
         result = CACHE.get(entry);
      }

      if (result == nullptr) {
         result = std::make_shared<EditDistance>(a, b).calc();
         CACHE.put(entry, result);
      }

    return result;
   }

    static std::string findNearest(const std::string& key, std::string[] group) {
    return findNearest();
   }

    static std::string findNearest(const std::string& key, Collection<std::string> group) {
    int c = int.MAX_VALUE;
    std::string r = nullptr;

    for (auto& s : group)    int ed = editDistance(key, s);
         if (c > ed) {
            c = ed;
            r = s;
         }
      }

    return r;
   }

    private EditDistance(const std::string& a, const std::string& b) {
      this.a = a;
      this.b = b;
      this.cost = new int[a.length() + 1];
      this.back = new int[a.length() + 1];
    int i = 0;

      while (i <= a.length()) {
         this.cost[i] = i++;
      }
   }

    void flip() {
      int[] t = this.cost;
      this.cost = this.back;
      this.back = t;
   }

    int min(int a, int b, int c) {
      return Math.min(a, Math.min(b, c));
   }

    int calc() {
      for (int j = 0; j < this.b.length(); j++) {
         this.flip();
         this.cost[0] = j + 1;

         for (int i = 0; i < this.a.length(); i++) {
    int match = this.a.charAt(i) == this.b.charAt(j) ? 0 : 1;
            this.cost[i + 1] = this.min(this.back[i] + match, this.cost[i] + 1, this.back[i + 1] + 1);
         }
      }

      return this.cost[this.a.length()];
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
