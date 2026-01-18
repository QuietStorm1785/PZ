// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.util.list;

import zombie.util.IntIterator;

public interface IntListIterator extends IntIterator {
    void add(int var1);

    boolean hasPrevious();

    int nextIndex();

    int previous();

    int previousIndex();

    void set(int var1);
}
