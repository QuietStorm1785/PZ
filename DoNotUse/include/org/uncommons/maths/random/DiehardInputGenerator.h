#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace org {
namespace uncommons {
namespace maths {
namespace random {


class DiehardInputGenerator {
public:
    static const int INT_COUNT = 3000000;

    private DiehardInputGenerator() {
   }

    static void main(std::string[] args) {
      if (args.length != 2) {
         System.out.println("Expected arguments:");
         System.out.println("\t<Fully-qualified RNG class name> <Output file>");
         System.exit(1);
      }

      Class<? : public Random> rngClass = (Class<? : public Random>)Class.forName(args[0]);
    File outputFile = std::make_shared<File>(args[1]);
      generateOutputFile(rngClass.newInstance(), outputFile);
   }

    static void generateOutputFile(Random rng, File outputFile) {
    DataOutputStream dataOutput = nullptr;

      try {
         dataOutput = std::make_shared<DataOutputStream>(std::make_shared<BufferedOutputStream>(std::make_shared<FileOutputStream>(outputFile)));

         for (int i = 0; i < 3000000; i++) {
            dataOutput.writeInt(rng.nextInt());
         }

         dataOutput.flush();
      } finally {
         if (dataOutput != nullptr) {
            dataOutput.close();
         }
      }
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
