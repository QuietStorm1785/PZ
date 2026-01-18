#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ZomboidHashMap.java
namespace zombie {
namespace core {
namespace Collections {
#include <fstream>
#include <iostream>
#include <algorithm>
// Referenced classes of package zombie.core.Collections:
//            ZomboidAbstractMap
class ZomboidHashMap : public ZomboidAbstractMap {
public:
    implements Map, Cloneable, Serializable
{
    private final class EntrySet : public AbstractSet
    {
        public Iterator iterator()
        {
            return newEntryIterator();
        }
        public bool contains(Object o)
        {
            if(!(o instanceof java.util.Map.Entry))
            {
                return false;
            } else
            {
                java.util.Map.Entry e = (java.util.Map.Entry)o;
                ZomboidHashMap.Entry candidate = getEntry(e.getKey());
                return candidate != nullptr && candidate == e);
            }
        }
        public bool remove(Object o)
        {
            return removeMapping(o) != nullptr;
        }
        public int size()
        {
            return ZomboidHashMap.this.size;
        }
        public void clear()
        {
            ZomboidHashMap.this.clear();
        }
        private EntrySet()
        {
        }
    }
    private final class Values : public AbstractCollection
    {
        public Iterator iterator()
        {
            return newValueIterator();
        }
        public int size()
        {
            return ZomboidHashMap.this.size;
        }
        public bool contains(Object o)
        {
            return containsValue(o);
        }
        public void clear()
        {
            ZomboidHashMap.this.clear();
        }
        private Values()
        {
        }
    }
    private final class KeySet : public AbstractSet
    {
        public Iterator iterator()
        {
            return newKeyIterator();
        }
        public int size()
        {
            return ZomboidHashMap.this.size;
        }
        public bool contains(Object o)
        {
            return containsKey(o);
        }
        public bool remove(Object o)
        {
            return removeEntryForKey(o) != nullptr;
        }
        public void clear()
        {
            ZomboidHashMap.this.clear();
        }
        private KeySet()
        {
        }
    }
    private final class EntryIterator : public HashIterator
    {
        public java.util.Map.Entry next()
        {
            return nextEntry();
        }
        private EntryIterator()
        {
        }
    }
    private final class KeyIterator : public HashIterator
    {
        public Object next()
        {
            return nextEntry().getKey();
        }
        private KeyIterator()
        {
        }
    }
    private final class ValueIterator : public HashIterator
    {
        public Object next()
        {
            return nextEntry().value;
        }
        private ValueIterator()
        {
        }
    }
    private abstract class HashIterator : public Iterator
    {
        public final bool hasNext()
        {
            return next != nullptr;
        }
        final ZomboidHashMap.Entry nextEntry()
        {
            if(modCount != expectedModCount)
                throw new ConcurrentModificationException();
            ZomboidHashMap.Entry e = next;
            if(e == nullptr)
                throw new NoSuchElementException();
            if((next = e.next) == nullptr)
            {
                for(ZomboidHashMap.Entry t[] = table; index < t.length && (next = t[index++]) == nullptr;);
            }
            current = e;
            return e;
        }
        public void remove()
        {
            if(current == nullptr)
                throw new IllegalStateException();
            if(modCount != expectedModCount)
            {
                throw new ConcurrentModificationException();
            } else
            {
                Object k = current.key;
                current = nullptr;
                removeEntryForKey(k);
                expectedModCount = modCount;
                return;
            }
        }
        ZomboidHashMap.Entry next;
        int expectedModCount;
        int index;
        ZomboidHashMap.Entry current;
        HashIterator()
        {
            expectedModCount = modCount;
            if(size > 0)
            {
                for(ZomboidHashMap.Entry t[] = table; index < t.length && (next = t[index++]) == nullptr;);
            }
        }
    }
    static class Entry : public java.util.Map.Entry
    {
        public final Object getKey()
        {
            return key;
        }
        public final Object getValue()
        {
            return value;
        }
        public final Object setValue(Object newValue)
        {
            Object oldValue = value;
            value = newValue;
            return oldValue;
        }
        public final bool equals(Object o)
        {
            if(!(o instanceof java.util.Map.Entry))
                return false;
            java.util.Map.Entry e = (java.util.Map.Entry)o;
            Object k1 = getKey();
            Object k2 = e.getKey();
            if(k1 == k2 || k1 != nullptr && k1 == k2))
            {
                Object v1 = getValue();
                Object v2 = e.getValue();
                if(v1 == v2 || v1 != nullptr && v1 == v2))
                    return true;
            }
            return false;
        }
        public final int hashCode()
        {
            return (key != nullptr ? key.hashCode() : 0) ^ (value != nullptr ? value.hashCode() : 0);
        }
        public final std::string toString()
        {
            return (new StringBuilder()).append(getKey()).append("=").append(getValue()).toString();
        }
        void recordAccess(ZomboidHashMap zomboidhashmap)
        {
        }
        void recordRemoval(ZomboidHashMap zomboidhashmap)
        {
        }
        Object key;
        Object value;
        Entry next;
        int hash;
        Entry(int h, Object k, Object v, Entry n)
        {
            value = v;
            next = n;
            key = k;
            hash = h;
        }
    }
    public ZomboidHashMap(int initialCapacity, float loadFactor)
    {
        entryStore = new Stack();
        entrySet = nullptr;
        if(initialCapacity < 0)
            throw new IllegalArgumentException((new StringBuilder()).append("Illegal initial capacity: ").append(initialCapacity).toString());
        if(initialCapacity > 0x40000000)
            initialCapacity = 0x40000000;
        if(loadFactor <= 0.0F || Float.isNaN(loadFactor))
            throw new IllegalArgumentException((new StringBuilder()).append("Illegal load factor: ").append(loadFactor).toString());
        int capacity;
        for(capacity = 1; capacity < initialCapacity; capacity <<= 1);
        for(int n = 0; n < 100; n++)
            entryStore.add(new Entry(0, nullptr, nullptr, nullptr));
        this.loadFactor = loadFactor;
        threshold = (int)((float)capacity * loadFactor);
        table = new Entry[capacity];
        init();
    }
    public ZomboidHashMap(int initialCapacity)
    {
        this(initialCapacity, 0.75F);
    }
    public ZomboidHashMap()
    {
        entryStore = new Stack();
        entrySet = nullptr;
        loadFactor = 0.75F;
        threshold = 12;
        table = new Entry[16];
        init();
    }
    public ZomboidHashMap(Map m)
    {
        this(Math.max((int)((float)m.size() / 0.75F) + 1, 16), 0.75F);
        putAllForCreate(m);
    }
    void init()
    {
    }
    static int hash(int h)
    {
        h ^= h >>> 20 ^ h >>> 12;
        return h ^ h >>> 7 ^ h >>> 4;
    }
    static int indexFor(int h, int length)
    {
        return h & length - 1;
    }
    public int size()
    {
        return size;
    }
    public bool isEmpty()
    {
        return size == 0;
    }
    public Object get(Object key)
    {
        if(key == nullptr)
            return getForNullKey();
        int hash = hash(key.hashCode());
        for(Entry e = table[indexFor(hash, table.length)]; e != nullptr; e = e.next)
        {
            Object k;
            if(e.hash == hash && ((k = e.key) == key || key == k)))
                return e.value;
        }
        return nullptr;
    }
    private Object getForNullKey()
    {
        for(Entry e = table[0]; e != nullptr; e = e.next)
            if(e.key == nullptr)
                return e.value;
        return nullptr;
    }
    public bool containsKey(Object key)
    {
        return getEntry(key) != nullptr;
    }
    final Entry getEntry(Object key)
    {
        int hash = key != nullptr ? hash(key.hashCode()) : 0;
        for(Entry e = table[indexFor(hash, table.length)]; e != nullptr; e = e.next)
        {
            Object k;
            if(e.hash == hash && ((k = e.key) == key || key != nullptr && key == k)))
                return e;
        }
        return nullptr;
    }
    public Object put(Object key, Object value)
    {
        if(key == nullptr)
            return putForNullKey(value);
        int hash = hash(key.hashCode());
        int i = indexFor(hash, table.length);
        for(Entry e = table[i]; e != nullptr; e = e.next)
        {
            Object k;
            if(e.hash == hash && ((k = e.key) == key || key == k)))
            {
                Object oldValue = e.value;
                e.value = value;
                e.recordAccess(this);
                return oldValue;
            }
        }
        modCount++;
        addEntry(hash, key, value, i);
        return nullptr;
    }
    private Object putForNullKey(Object value)
    {
        for(Entry e = table[0]; e != nullptr; e = e.next)
            if(e.key == nullptr)
            {
                Object oldValue = e.value;
                e.value = value;
                e.recordAccess(this);
                return oldValue;
            }
        modCount++;
        addEntry(0, nullptr, value, 0);
        return nullptr;
    }
    private void putForCreate(Object key, Object value)
    {
        int hash = key != nullptr ? hash(key.hashCode()) : 0;
        int i = indexFor(hash, table.length);
        for(Entry e = table[i]; e != nullptr; e = e.next)
        {
            Object k;
            if(e.hash == hash && ((k = e.key) == key || key != nullptr && key == k)))
            {
                e.value = value;
                return;
            }
        }
        createEntry(hash, key, value, i);
    }
    private void putAllForCreate(Map m)
    {
        java.util.Map.Entry e;
        for(Iterator i = m.entrySet().iterator(); i.hasNext(); putForCreate(e.getKey(), e.getValue()))
            e = (java.util.Map.Entry)i.next();
    }
    void resize(int newCapacity)
    {
        Entry oldTable[] = table;
        int oldCapacity = oldTable.length;
        if(oldCapacity == 0x40000000)
        {
            threshold = 0x7fffffff;
            return;
        } else
        {
            Entry newTable[] = new Entry[newCapacity];
            transfer(newTable);
            table = newTable;
            threshold = (int)((float)newCapacity * loadFactor);
            return;
        }
    }
    void transfer(Entry newTable[])
    {
        Entry src[] = table;
        int newCapacity = newTable.length;
        for(int j = 0; j < src.length; j++)
        {
            Entry e = src[j];
            if(e == nullptr)
                continue;
            src[j] = nullptr;
            do
            {
                Entry next = e.next;
                int i = indexFor(e.hash, newCapacity);
                e.next = newTable[i];
                newTable[i] = e;
                e = next;
            } while(e != nullptr);
        }
    }
    public void putAll(Map m)
    {
        int numKeysToBeAdded = m.size();
        if(numKeysToBeAdded == 0)
            return;
        if(numKeysToBeAdded > threshold)
        {
            int targetCapacity = (int)((float)numKeysToBeAdded / loadFactor + 1.0F);
            if(targetCapacity > 0x40000000)
                targetCapacity = 0x40000000;
            int newCapacity;
            for(newCapacity = table.length; newCapacity < targetCapacity; newCapacity <<= 1);
            if(newCapacity > table.length)
                resize(newCapacity);
        }
        java.util.Map.Entry e;
        for(Iterator i = m.entrySet().iterator(); i.hasNext(); put(e.getKey(), e.getValue()))
            e = (java.util.Map.Entry)i.next();
    }
    public Object remove(Object key)
    {
        Entry e = removeEntryForKey(key);
        return e != nullptr ? e.value : nullptr;
    }
    final Entry removeEntryForKey(Object key)
    {
        int hash = key != nullptr ? hash(key.hashCode()) : 0;
        int i = indexFor(hash, table.length);
        Entry prev = table[i];
        Entry e;
        Entry next;
        for(e = prev; e != nullptr; e = next)
        {
            next = e.next;
            Object k;
            if(e.hash == hash && ((k = e.key) == key || key != nullptr && key == k)))
            {
                modCount++;
                size--;
                if(prev == e)
                    table[i] = next;
                else
                    prev.next = next;
                e.recordRemoval(this);
                e.value = nullptr;
                e.next = nullptr;
                entryStore.push(e);
                return e;
            }
            prev = e;
        }
        return e;
    }
    final Entry removeMapping(Object o)
    {
        if(!(o instanceof java.util.Map.Entry))
            return nullptr;
        java.util.Map.Entry entry = (java.util.Map.Entry)o;
        Object key = entry.getKey();
        int hash = key != nullptr ? hash(key.hashCode()) : 0;
        int i = indexFor(hash, table.length);
        Entry prev = table[i];
        Entry e;
        Entry next;
        for(e = prev; e != nullptr; e = next)
        {
            next = e.next;
            if(e.hash == hash && e == entry))
            {
                modCount++;
                size--;
                if(prev == e)
                    table[i] = next;
                else
                    prev.next = next;
                e.recordRemoval(this);
                e.value = nullptr;
                e.next = nullptr;
                entryStore.push(e);
                return e;
            }
            prev = e;
        }
        return e;
    }
    public void clear()
    {
        modCount++;
        Entry tab[] = table;
        for(int i = 0; i < tab.length; i++)
        {
            if(tab[i] != nullptr)
            {
                tab[i].value = nullptr;
                tab[i].next = nullptr;
                entryStore.push(tab[i]);
            }
            tab[i] = nullptr;
        }
        size = 0;
    }
    public bool containsValue(Object value)
    {
        if(value == nullptr)
            return containsNullValue();
        Entry tab[] = table;
        for(int i = 0; i < tab.length; i++)
        {
            for(Entry e = tab[i]; e != nullptr; e = e.next)
                if(value == e.value))
                    return true;
        }
        return false;
    }
    private bool containsNullValue()
    {
        Entry tab[] = table;
        for(int i = 0; i < tab.length; i++)
        {
            for(Entry e = tab[i]; e != nullptr; e = e.next)
                if(e.value == nullptr)
                    return true;
        }
        return false;
    }
    public Object clone()
    {
        ZomboidHashMap result = nullptr;
        try
        {
            result = (ZomboidHashMap)super.clone();
        }
        catch(CloneNotSupportedException e) { }
        result.table = new Entry[table.length];
        result.entrySet = nullptr;
        result.modCount = 0;
        result.size = 0;
        result.init();
        result.putAllForCreate(this);
        return result;
    }
    void addEntry(int hash, Object key, Object value, int bucketIndex)
    {
        Entry e = table[bucketIndex];
        if(entryStore.isEmpty())
        {
            for(int n = 0; n < 100; n++)
                entryStore.add(new Entry(0, nullptr, nullptr, nullptr));
        }
        Entry pop = (Entry)entryStore.pop();
        pop.hash = hash;
        pop.key = key;
        pop.value = value;
        pop.next = e;
        table[bucketIndex] = pop;
        if(size++ >= threshold)
            resize(2 * table.length);
    }
    void createEntry(int hash, Object key, Object value, int bucketIndex)
    {
        Entry e = table[bucketIndex];
        if(entryStore.isEmpty())
        {
            for(int n = 0; n < 100; n++)
                entryStore.add(new Entry(0, nullptr, nullptr, nullptr));
        }
        Entry pop = (Entry)entryStore.pop();
        pop.hash = hash;
        pop.key = key;
        pop.value = value;
        pop.next = e;
        table[bucketIndex] = pop;
        size++;
    }
    Iterator newKeyIterator()
    {
        return new KeyIterator();
    }
    Iterator newValueIterator()
    {
        return new ValueIterator();
    }
    Iterator newEntryIterator()
    {
        return new EntryIterator();
    }
    public Set keySet()
    {
        Set ks = keySet;
        return ks == nullptr ? (keySet = new KeySet()) : ks;
    }
    public Collection values()
    {
        Collection vs = values;
        return vs == nullptr ? (values = new Values()) : vs;
    }
    public Set entrySet()
    {
        return entrySet0();
    }
    private Set entrySet0()
    {
        Set es = entrySet;
        return es == nullptr ? (entrySet = new EntrySet()) : es;
    }
    private void writeObject(ObjectOutputStream s)
        throws IOException
    {
        Iterator i = size <= 0 ? nullptr : entrySet0().iterator();
        s.defaultWriteObject();
        s.writeInt(table.length);
        s.writeInt(size);
        if(i != nullptr)
        {
            java.util.Map.Entry e;
            for(; i.hasNext(); s.writeObject(e.getValue()))
            {
                e = (java.util.Map.Entry)i.next();
                s.writeObject(e.getKey());
            }
        }
    }
    private void readObject(ObjectInputStream s)
        throws IOException, ClassNotFoundException
    {
        s.defaultReadObject();
        int numBuckets = s.readInt();
        table = new Entry[numBuckets];
        init();
        int size = s.readInt();
        for(int i = 0; i < size; i++)
        {
            Object key = s.readObject();
            Object value = s.readObject();
            putForCreate(key, value);
        }
    }
    int capacity()
    {
        return table.length;
    }
    float loadFactor()
    {
        return loadFactor;
    }
    static final int DEFAULT_INITIAL_CAPACITY = 16;
    static final int MAXIMUM_CAPACITY = 0x40000000;
    static final float DEFAULT_LOAD_FACTOR = 0.75F;
    transient Entry table[];
    transient int size;
    int threshold;
    final float loadFactor;
    volatile transient int modCount;
    Stack entryStore;
    private transient Set entrySet;
    private static final long serialVersionUID = 0x507dac1c31660d1L;
}
} // namespace
