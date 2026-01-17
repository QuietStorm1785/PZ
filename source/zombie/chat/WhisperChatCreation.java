// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.chat;

import java.util.ArrayList;
import zombie.chat.defaultChats.WhisperChat;

public final class WhisperChatCreation {
    String destPlayerName = null;
    WhisperChat.ChatStatus status = WhisperChat.ChatStatus.None;
    long createTime = 0L;
    final ArrayList<String> messages = new ArrayList<>();
}
