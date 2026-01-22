#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/Schema.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/TopLevelElement.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


class XmlSchemaGenerator {
public:
    const bool nillable;
   private const NonElement<T, C> type;

   public XmlSchemaGenerator$Namespace$ElementWithType(boolean this$1, NonElement<T, C> nillable, NonElement type) {
      super(this$1);
      this.this$1 = this$1;
      this.type = type;
      this.nillable = nillable;
   }

    void writeTo(const std::string& localName, Schema schema) {
    TopLevelElement e = schema.element().name(localName);
      if (this.nillable) {
         e.nillable(true);
      }

      if (this.type != nullptr) {
         Namespace.access$2100(this.this$1, e, this.type, "type");
      } else {
         e.complexType();
      }

      e.commit();
   }

    bool equals(void* o) {
      // $VF: Couldn't be decompiled
      // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
      // java.lang.NullPointerException: Cannot invoke "org.jetbrains.java.decompiler.struct.StructClass.getSignature()" because "cls" is nullptr
      //   at org.jetbrains.java.decompiler.struct.gen.generics.GenericType.mapGenVarsTo(GenericType.java:645)
      //   at org.jetbrains.java.decompiler.modules.decompiler.exps.FieldExprent.getInferredExprType(FieldExprent.java:93)
      //   at org.jetbrains.java.decompiler.modules.decompiler.ExprProcessor.getCastedExprent(ExprProcessor.java:962)
      //   at org.jetbrains.java.decompiler.modules.decompiler.exps.InvocationExprent.appendParamList(InvocationExprent.java:1153)
      //   at org.jetbrains.java.decompiler.modules.decompiler.exps.InvocationExprent.toJava(InvocationExprent.java:904)
      //   at org.jetbrains.java.decompiler.modules.decompiler.ExprProcessor.getCastedExprent(ExprProcessor.java:1014)
      //   at org.jetbrains.java.decompiler.modules.decompiler.exps.ExitExprent.toJava(ExitExprent.java:86)
      //   at org.jetbrains.java.decompiler.modules.decompiler.ExprProcessor.listToJava(ExprProcessor.java:891)
      //   at org.jetbrains.java.decompiler.modules.decompiler.stats.BasicBlockStatement.toJava(BasicBlockStatement.java:91)
      //   at org.jetbrains.java.decompiler.modules.decompiler.ExprProcessor.jmpWrapper(ExprProcessor.java:829)
      //   at org.jetbrains.java.decompiler.modules.decompiler.stats.IfStatement.toJava(IfStatement.java:238)
      //   at org.jetbrains.java.decompiler.modules.decompiler.ExprProcessor.jmpWrapper(ExprProcessor.java:829)
      //   at org.jetbrains.java.decompiler.modules.decompiler.stats.IfStatement.toJava(IfStatement.java:251)
      //   at org.jetbrains.java.decompiler.modules.decompiler.stats.RootStatement.toJava(RootStatement.java:36)
      //   at org.jetbrains.java.decompiler.main.ClassWriter.writeMethod(ClassWriter.java:1326)
      //
      // Bytecode:
      // 00: aload 0
      // 01: aload 1
      // 02: if_acmpne 07
      // 05: bipush 1
      // 06: ireturn
      // 07: aload 1
      // 08: ifnull 16
      // 0b: aload 0
      // 0c: invokevirtual java/lang/Object.getClass ()Ljava/lang/Class;
      // 0f: aload 1
      // 10: invokevirtual java/lang/Object.getClass ()Ljava/lang/Class;
      // 13: if_acmpeq 18
      // 16: bipush 0
      // 17: ireturn
      // 18: aload 1
      // 19: checkcast com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator$Namespace$ElementWithType
      // 1c: astore 2
      // 1d: aload 0
      // 1e: getfield com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator$Namespace$ElementWithType.type Lcom/sun/xml/bind/v2/model/core/NonElement;
      // 21: aload 2
      // 22: getfield com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator$Namespace$ElementWithType.type Lcom/sun/xml/bind/v2/model/core/NonElement;
      // 25: invokevirtual java/lang/Object.equals (Ljava/lang/Object;)Z
      // 28: ireturn
   }

    int hashCode() {
      return this.type.hashCode();
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
