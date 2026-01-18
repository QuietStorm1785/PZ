// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.text.templating;

/**
 * TurboTuTone.  Interface that can provide IReplace for ITemplateBuilder.  Any keys present in a IReplaceProvider take priority when replacing keys in a template.   NOTE: When checking the key String, this should be equaling a lowercase version or equalsIgnoreCase
 */
public interface IReplaceProvider {
    boolean hasReplacer(String key);

    IReplace getReplacer(String key);
}
