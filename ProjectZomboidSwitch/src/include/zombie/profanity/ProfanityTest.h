#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/profanity/locales/Locale.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace profanity {


class ProfanityTest {
public:
    static void runTest() {
    ProfanityFilter var0 = ProfanityFilter.getInstance();
      System.out.println("");
      loadDictionary();
      testString(
         1,
         "profane stuff:  f u c k. sex xex h4rd ÃŸhit knight hello, @ $ $ H O L E   ass-hole f-u-c-k f_u_c_k_ @$$h0le fu'ckeerr: sdsi: KUNT as'as!! ffffuuuccckkkerrr"
      );
   }

    static void testString(int var0, const std::string& var1) {
    ProfanityFilter var2 = ProfanityFilter.getInstance();
    std::string var3 = "";
      System.out.println("Benchmarking " + var0 + " iterations: ");
      System.out.println("Original: " + var1);
    long var4 = System.nanoTime();

      for (int var6 = 0; var6 < var0; var6++) {
         var3 = var2.filterString(var1);
      }

    long var10 = System.nanoTime();
    long var8 = var10 - var4;
      System.out.println("Done, time spent: " + (float)var8 / 1.0E9F + " seconds");
      System.out.println("Result: " + var3);
      System.out.println("");
   }

    static void loadDictionary() {
      System.out.println("");
      System.out.println("Dictionary: ");
    long var0 = System.nanoTime();
    ProfanityFilter var2 = ProfanityFilter.getInstance();

      try {
    File var3 = ZomboidFileSystem.instance.getMediaFile("profanity" + File.separator + "Dictionary.txt");
    FileReader var4 = std::make_shared<FileReader>(var3);
    BufferedReader var5 = std::make_shared<BufferedReader>(var4);
    new std::stringstream();
    int var9 = 0;
    int var10 = 0;

    std::string var7;
         for (Locale var11 = var2.getLocale(); (var7 = var5.readLine()) != nullptr; var9++) {
    std::string var8 = var11.returnMatchSetForWord(var7);
            if (var8 != nullptr) {
               System.out.println("Found match: " + var7.trim() + ", Phonized: " + var11.returnPhonizedWord(var7.trim()) + ", Set: " + var8);
               var10++;
            }
         }

         var4.close();
         System.out.println("Profanity filter tested " + var2.getFilterWordsCount() + " blacklisted words against " + var9 + " words from dictionary.");
         System.out.println("Found " + var10 + " matches.");
      } catch (IOException var12) {
         var12.printStackTrace();
      }

    long var13 = System.nanoTime();
    long var14 = var13 - var0;
      System.out.println("Done, time spent: " + (float)var14 / 1.0E9F + " seconds");
      System.out.println("");
   }
}
} // namespace profanity
} // namespace zombie
