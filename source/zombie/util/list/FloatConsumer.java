// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.util.list;

import java.util.Objects;

public interface FloatConsumer {
    void accept(float var1);

    default FloatConsumer andThen(FloatConsumer floatConsumer0) {
        Objects.requireNonNull(floatConsumer0);
        return float0 -> {
            this.accept(float0);
            floatConsumer0.accept(float0);
        };
    }
}
