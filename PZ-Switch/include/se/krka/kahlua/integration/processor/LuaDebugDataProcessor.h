#pragma once
#include "javax/annotation/processing/Completion.h"
#include "javax/annotation/processing/Filer.h"
#include "javax/annotation/processing/ProcessingEnvironment.h"
#include "javax/annotation/processing/Processor.h"
#include "javax/annotation/processing/RoundEnvironment.h"
#include "javax/lang/model/SourceVersion.h"
#include "javax/lang/model/element/AnnotationMirror.h"
#include "javax/lang/model/element/Element.h"
#include "javax/lang/model/element/ElementKind.h"
#include "javax/lang/model/element/ElementVisitor.h"
#include "javax/lang/model/element/ExecutableElement.h"
#include "javax/lang/model/element/PackageElement.h"
#include "javax/lang/model/element/TypeElement.h"
#include "javax/lang/model/element/TypeParameterElement.h"
#include "javax/lang/model/element/VariableElement.h"
#include "javax/tools/FileObject.h"
#include "javax/tools/StandardLocation.h"
#include "se/krka/kahlua/integration/annotations/LuaConstructor.h"
#include "se/krka/kahlua/integration/annotations/LuaMethod.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace processor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LuaDebugDataProcessor {
public:
private
 HashMap<String, ClassParameterInformation> classes;
 Filer filer;

public
 Iterable < ? extends Completion >
 getCompletions(Element var1, AnnotationMirror var2,
 ExecutableElement var3, String var4) {
 return std::make_unique<HashSet<>>();
 }

public
 Set<String> getSupportedAnnotationTypes() {
 std::unordered_set hashSet = new HashSet();
 hashSet.add(LuaMethod.class.getName());
 hashSet.add(LuaConstructor.class.getName());
 return hashSet;
 }

public
 Set<String> getSupportedOptions() { return std::make_unique<HashSet<>>(); }

 SourceVersion getSupportedSourceVersion() { return SourceVersion.latest(); }

 void init(ProcessingEnvironment processingEnvironment) {
 this->filer = processingEnvironment.getFiler();
 this->classes = std::make_unique<HashMap<>>();
 }

 bool process(Set<? extends, RoundEnvironment roundEnvironment) {
 for (auto &typeElement : set)
 for (Element element :
 roundEnvironment.getElementsAnnotatedWith(typeElement) {
 element.accept(this, nullptr);
 }
 }

 if (roundEnvironment.processingOver()) {
 try {
 this->store();
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 return true;
}

 Void visit(Element var1) {
 return nullptr;
}

Void visit(Element var1, Void var2) { return nullptr; }

Void visitExecutable(ExecutableElement executableElement, Void var2) {
 std::string string0 = this->findClass(executableElement);
 std::string string1 = this->findPackage(executableElement);
 ClassParameterInformation classParameterInformation =
 this->getOrCreate(this->classes, string0, string1,
 this->findSimpleClassName(executableElement);
 std::string string2 = executableElement.getSimpleName().toString();
 std::string string3 =
 DescriptorUtil.getDescriptor(string2, executableElement.getParameters());
 std::vector arrayList = new ArrayList();

 for (VariableElement variableElement : executableElement.getParameters()) {
 arrayList.add(variableElement.getSimpleName().toString());
 }

 MethodParameterInformation methodParameterInformation =
 new MethodParameterInformation(arrayList);
 classParameterInformation.methods.put(string3, methodParameterInformation);
 return nullptr;
}

ClassParameterInformation getOrCreate(ClassParameterInformation > hashMap,
 std::string_view string0,
 std::string_view string1,
 std::string_view string2) {
 ClassParameterInformation classParameterInformation =
 (ClassParameterInformation)hashMap.get(string0);
 if (classParameterInformation.empty()) {
 classParameterInformation = new ClassParameterInformation(string1, string2);
 hashMap.put(string0, classParameterInformation);
 }

 return classParameterInformation;
}

std::string findClass(Element element) {
 return element.getKind() == ElementKind.CLASS
 ? element.toString()
 : this->findClass(element.getEnclosingElement());
}

std::string findSimpleClassName(Element element) {
 if (element.getKind() == ElementKind.CLASS) {
 std::string string = element.getSimpleName().toString();
 return element.getEnclosingElement().getKind() == ElementKind.CLASS
 ? this->findSimpleClassName(element.getEnclosingElement()) + "_" +
 string
 : string;
 } else {
 return this->findSimpleClassName(element.getEnclosingElement());
 }
}

std::string findPackage(Element element) {
 return element.getKind() == ElementKind.PACKAGE
 ? element.toString()
 : this->findPackage(element.getEnclosingElement());
}

Void visitPackage(PackageElement var1, Void var2) { return nullptr; }

Void visitType(TypeElement var1, Void var2) { return nullptr; }

Void visitVariable(VariableElement var1, Void var2) { return nullptr; }

Void visitTypeParameter(TypeParameterElement var1, Void var2) { return nullptr; }

Void visitUnknown(Element var1, Void var2) { return nullptr; }

void store() {
 for (Entry entry : this->classes.entrySet()) {
 ClassParameterInformation classParameterInformation =
 (ClassParameterInformation)entry.getValue();
 void *object = nullptr;
 FileObject fileObject = this->filer.createResource(
 StandardLocation.CLASS_OUTPUT,
 classParameterInformation.getPackageName(),
 classParameterInformation.getSimpleClassName() + ".luadebugdata",
 (Element[])object);
 OutputStream outputStream = fileObject.openOutputStream();
 classParameterInformation.saveToStream(outputStream);
 outputStream.close();
 }
}
}
} // namespace processor
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
