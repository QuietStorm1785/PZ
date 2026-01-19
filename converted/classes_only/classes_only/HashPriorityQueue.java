package astar.datastructures;

import java.util.Comparator;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.Map.Entry;

public class HashPriorityQueue<K, V> {
   HashMap<K, V> hashMap = new HashMap<>();
   TreeMap<V, K> treeMap;

   public HashPriorityQueue(Comparator<V> var1) {
      this.treeMap = new TreeMap<>(var1);
   }

   public int size() {
      return this.treeMap.size();
   }

   public boolean isEmpty() {
      return this.treeMap.isEmpty();
   }

   public boolean contains(K var1) {
      return this.hashMap.containsKey(var1);
   }

   public V get(K var1) {
      return this.hashMap.get(var1);
   }

   public boolean add(K var1, V var2) {
      this.hashMap.put((K)var1, (V)var2);
      this.treeMap.put((V)var2, (K)var1);
      return true;
   }

   public boolean remove(K var1, V var2) {
      if (var2 == null) {
         var2 = this.hashMap.get(var1);
      }

      this.hashMap.remove(var1);
      this.treeMap.remove(var2);
      return true;
   }

   public V poll() {
      Entry var1 = this.treeMap.pollFirstEntry();
      return (V)var1.getKey();
   }

   public void clear() {
      this.hashMap.clear();
      this.treeMap.clear();
   }

   public HashMap<K, V> getHashMap() {
      return this.hashMap;
   }

   public TreeMap<V, K> getTreeMap() {
      return this.treeMap;
   }
}
