// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.sandbox;

import zombie.scripting.ScriptParser;

public final class CustomStringSandboxOption extends CustomSandboxOption {
    public final String defaultValue;

    CustomStringSandboxOption(String string0, String string1) {
        super(string0);
        this.defaultValue = string1;
    }

    static CustomStringSandboxOption parse(ScriptParser.Block block) {
        ScriptParser.Value value = block.getValue("default");
        if (value == null) {
            return null;
        } else {
            CustomStringSandboxOption customStringSandboxOption = new CustomStringSandboxOption(block.id, value.getValue().trim());
            return !customStringSandboxOption.parseCommon(block) ? null : customStringSandboxOption;
        }
    }
}
