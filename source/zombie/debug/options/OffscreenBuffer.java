// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.debug.options;

import zombie.debug.BooleanDebugOption;

public final class OffscreenBuffer extends OptionGroup {
    public final BooleanDebugOption Render = newDebugOnlyOption(this.Group, "Render", true);

    public OffscreenBuffer() {
        super("OffscreenBuffer");
    }
}
