#pragma once
#include "astar/ISearchNode.h"
#include "absl/container/flat_hash_map.h"
// TObjectProcedure replaced by C++ functor/lambda pattern
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace astar {
namespace datastructures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ClosedSetHash {

public:
	using ComparatorType = std::function<int(const ISearchNode&, const ISearchNode&)>;
	explicit ClosedSetHash(ComparatorType comparator) : comp(comparator) {}

	bool contains(const ISearchNode& iSearchNode) const {
		return hashMap.find(iSearchNode.keyCode()) != hashMap.end();
	}

	void add(const ISearchNode& iSearchNode) {
		hashMap[iSearchNode.keyCode()] = iSearchNode;
	}

	ISearchNode min() const {
		MinNodeProc minNodeProc{comp};
		for (const auto& kv : hashMap) {
			minNodeProc.execute(kv.second);
		}
		return minNodeProc.candidate;
	}

	void clear() { hashMap.clear(); }

private:
	absl::flat_hash_map<int, ISearchNode> hashMap;
	ComparatorType comp;

	struct MinNodeProc {
		ComparatorType comp;
		ISearchNode candidate;
		bool has_candidate = false;
		bool execute(const ISearchNode& iSearchNode) {
			if (!has_candidate) {
				candidate = iSearchNode;
				has_candidate = true;
				return true;
			} else {
				if (comp(iSearchNode, candidate) < 0) {
					candidate = iSearchNode;
				}
				return true;
			}
		}
	};


 bool contains(const ISearchNode& iSearchNode) const {
	 return hashMap.find(iSearchNode.keyCode()) != hashMap.end();
 }


 void add(const ISearchNode& iSearchNode) {
	 hashMap[iSearchNode.keyCode()] = iSearchNode;
 }



 ISearchNode min() const {
	 minNodeProc.comp = this->comp;
	 minNodeProc.candidate = ISearchNode();
	 for (const auto& kv : hashMap) {
		 minNodeProc.execute(kv.second);
	 }
	 return minNodeProc.candidate;
 }


 void clear() { hashMap.clear(); }

private:
 struct MinNodeProc {
	 Comparator<ISearchNode> comp;
	 ISearchNode candidate;
	 bool execute(const ISearchNode& iSearchNode) {
		 if (!candidate || candidate.empty()) {
			 candidate = iSearchNode;
			 return true;
		 } else {
			 if (comp.compare(iSearchNode, candidate) < 0) {
				 candidate = iSearchNode;
			 }
			 return true;
		 }
	 }
 };
}
} // namespace datastructures
} // namespace astar
