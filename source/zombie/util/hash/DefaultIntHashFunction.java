// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.util.hash;

import java.io.Serializable;

public class DefaultIntHashFunction implements IntHashFunction, Serializable {
    private static final long serialVersionUID = 1L;
    public static final IntHashFunction INSTANCE = new DefaultIntHashFunction();

    protected DefaultIntHashFunction() {
    }

    @Override
    public int hash(int int0) {
        return int0;
    }
}
