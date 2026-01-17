// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.characters;

public interface Talker {
    boolean IsSpeaking();

    void Say(String line);

    String getSayLine();

    String getTalkerType();
}
