// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.text.templating;

import se.krka.kahlua.j2se.KahluaTableImpl;

/**
 * TurboTuTone.
 */
public interface ITemplateBuilder {
    String Build(String input);

    String Build(String input, IReplaceProvider replaceProvider);

    String Build(String input, KahluaTableImpl table);

    void RegisterKey(String key, KahluaTableImpl table);

    void RegisterKey(String key, IReplace replace);

    void Reset();
}
