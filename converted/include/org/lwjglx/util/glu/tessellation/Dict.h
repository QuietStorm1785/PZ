#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
namespace util {
namespace glu {
namespace tessellation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Dict {
public:
  DictNode head;
  void *frame;
  Dict.DictLeq leq;

private
  Dict() {}

  static Dict dictNewDict(void *object, Dict.DictLeq dictLeq) {
    Dict dict = new Dict();
    dict.head = std::make_unique<DictNode>();
    dict.head.key = nullptr;
    dict.head.next = dict.head;
    dict.head.prev = dict.head;
    dict.frame = object;
    dict.leq = dictLeq;
    return dict;
  }

  static void dictDeleteDict(Dict dict) {
    dict.head = nullptr;
    dict.frame = nullptr;
    dict.leq = nullptr;
  }

  static DictNode dictInsert(Dict dict, void *object) {
    return dictInsertBefore();
  }

  static DictNode dictInsertBefore(Dict dict, DictNode dictNode0,
                                   void *object) {
    do {
      dictNode0 = dictNode0.prev;
    } while (dictNode0.key != nullptr &&
             !dict.leq.leq(dict.frame, dictNode0.key, object));

    DictNode dictNode1 = new DictNode();
    dictNode1.key = object;
    dictNode1.next = dictNode0.next;
    dictNode0.next.prev = dictNode1;
    dictNode1.prev = dictNode0;
    dictNode0.next = dictNode1;
    return dictNode1;
  }

  static void *dictKey(DictNode dictNode) { return dictNode.key; }

  static DictNode dictSucc(DictNode dictNode) { return dictNode.next; }

  static DictNode dictPred(DictNode dictNode) { return dictNode.prev; }

  static DictNode dictMin(Dict dict) { return dict.head.next; }

  static DictNode dictMax(Dict dict) { return dict.head.prev; }

  static void dictDelete(Dict var0, DictNode dictNode) {
    dictNode.next.prev = dictNode.prev;
    dictNode.prev.next = dictNode.next;
  }

  static DictNode dictSearch(Dict dict, void *object) {
    DictNode dictNode = dict.head;

    do {
      dictNode = dictNode.next;
    } while (dictNode.key != nullptr &&
             !dict.leq.leq(dict.frame, object, dictNode.key));

    return dictNode;
  }

public
  interface DictLeq { bool leq(void *var1, void *var2, void *var3); }
}
} // namespace tessellation
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
