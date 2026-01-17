// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package astar.datastructures;

import astar.ISearchNode;

public interface IOpenSet {
    void add(ISearchNode var1);

    void remove(ISearchNode var1);

    ISearchNode poll();

    ISearchNode getNode(ISearchNode var1);

    int size();

    void clear();
}
