#ifndef ASTARCPP_HASHPRIORITYQUEUE_H
#define ASTARCPP_HASHPRIORITYQUEUE_H

#include <unordered_map>
#include <map>
#include <memory>
#include <queue>

// K: key type, V: value type (usually node pointer)
template<typename K, typename V, typename Compare>
class HashPriorityQueue {
public:
    HashPriorityQueue(Compare cmp) : cmp_(cmp) {}

    int size() const { return static_cast<int>(treeMap_.size()); }
    bool isEmpty() const { return treeMap_.empty(); }
    bool contains(const K& key) const { return hashMap_.count(key) > 0; }
    V get(const K& key) const {
        auto it = hashMap_.find(key);
        return it != hashMap_.end() ? it->second : V();
    }
    bool add(const K& key, const V& value) {
        hashMap_[key] = value;
        treeMap_[value] = key;
        return true;
    }
    bool remove(const K& key, const V& value = V()) {
        hashMap_.erase(key);
        treeMap_.erase(value ? value : get(key));
        return true;
    }
    V poll() {
        if (treeMap_.empty()) return V();
        auto it = treeMap_.begin();
        V value = it->first;
        K key = it->second;
        treeMap_.erase(it);
        hashMap_.erase(key);
        return value;
    }
private:
    std::unordered_map<K, V> hashMap_;
    std::map<V, K, Compare> treeMap_;
    Compare cmp_;
};

#endif // ASTARCPP_HASHPRIORITYQUEUE_H
