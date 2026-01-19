package zombie.chat;

import java.util.ArrayList;
import zombie.chat.defaultChats.WhisperChat.ChatStatus;

public final class WhisperChatCreation {
   String destPlayerName = null;
   ChatStatus status = ChatStatus.None;
   long createTime = 0L;
   final ArrayList<String> messages = new ArrayList<>();
}
