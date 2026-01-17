// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package astar.datastructures;

import astar.ISearchNode;

public interface IClosedSet {
    boolean contains(ISearchNode var1);

    void add(ISearchNode var1);

    ISearchNode min();

    void clear();
}
