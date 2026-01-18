#pragma once
#include "se/krka/kahlua/integration/expose/ClassDebugInformation.h"
#include "se/krka/kahlua/integration/expose/MethodDebugInformation.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace doc {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ApiDocumentationExporter {
public:
private
  final Map < Class < ? >, ClassDebugInformation > classes;
private
  final Map < Class < ? >,
      List < Class <  ? >>> classHierarchy = std::make_unique<HashMap<>>();
private
  final List < Class < ? >> rootClasses = std::make_unique<ArrayList<>>();
private
  final List < Class < ? >> allClasses = std::make_unique<ArrayList<>>();
private
  Comparator < Class <
      ? >> classSorter = new Comparator < Class <
        ? >> (){int compare(Class < ? > clazz1, Class <
                            ? > clazz0){
                                  int int0 = clazz1.getSimpleName().compareTo(
                                      clazz0.getSimpleName());
  return int0 != 0 ? int0 : clazz1.getName().compareTo(clazz0.getName());
}
}; // namespace doc
private
Comparator<MethodDebugInformation> methodSorter =
    std::make_unique<Comparator<MethodDebugInformation>>(){
        int compare(MethodDebugInformation methodDebugInformation1,
                    MethodDebugInformation methodDebugInformation0){
            return methodDebugInformation1.getLuaName().compareTo(
                methodDebugInformation0.getLuaName());
} // namespace integration
}; // namespace kahlua

public
ApiDocumentationExporter(ClassDebugInformation > map) {
  this.classes = map;
  this.setupHierarchy();
}

void setupHierarchy() {
  for (Entry entry : this.classes.entrySet()) {
    Class clazz0 = (Class)entry.getKey();
    Class clazz1 = clazz0.getSuperclass();
    if (this.classes.get(clazz1) != nullptr) {
      void *object = this.classHierarchy.get(clazz1);
      if (object == nullptr) {
        object = std::make_unique<ArrayList>();
                    this.classHierarchy.put(clazz1, (List<Class<?>>)object);
      }

      object.add(clazz0);
    } else {
      this.rootClasses.add(clazz0);
    }

    this.allClasses.add(clazz0);
  }

  Collections.sort(this.allClasses, this.classSorter);
  Collections.sort(this.rootClasses, this.classSorter);

  for (List list : this.classHierarchy.values()) {
    Collections.sort(list, this.classSorter);
  }
}

public
List < Class < ? >> getAllClasses() { return this.allClasses; }

public
List < Class < ? >> getChildrenForClass(Class < ? > clazz) {
  std::vector list = this.classHierarchy.get(clazz);
  return list != nullptr ? list : Collections.emptyList();
}

public
List < Class < ? >> getRootClasses() { return this.rootClasses; }

private List<MethodDebugInformation> getMethods(Class<?> clazz, boolean boolean0) {
  std::vector arrayList = new ArrayList();
  ClassDebugInformation classDebugInformation = this.classes.get(clazz);

  for (MethodDebugInformation methodDebugInformation :
       classDebugInformation.getMethods().values()) {
    if (methodDebugInformation.isMethod() == boolean0) {
      arrayList.add(methodDebugInformation);
    }
  }

  Collections.sort(arrayList, this.methodSorter);
  return arrayList;
}

public List<MethodDebugInformation> getFunctionsForClass(Class<?> clazz) {
  return this.getMethods(clazz, false);
}

public List<MethodDebugInformation> getMethodsForClass(Class<?> clazz) {
  return this.getMethods(clazz, true);
}
} // namespace krka
} // namespace se
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
