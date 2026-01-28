// SDL2-based GameKeyboard for keyboard state and events
#pragma once
#include <SDL2/SDL.h>
#include <vector>

class GameKeyboard {
public:
  GameKeyboard();
  void update(); // Polls keyboard state
  bool isKeyDown(SDL_Scancode scancode) const;
  bool isKeyPressed(SDL_Scancode scancode) const;
  bool isKeyReleased(SDL_Scancode scancode) const;
  void handleEvent(const SDL_Event& event);

private:
  const Uint8* currentKeys_ = nullptr;
  std::vector<Uint8> lastKeys_;
  int numKeys_ = 0;
};
      s_keyboardStateCache.poll();
   }

    static bool isKeyPressed(int var0) {
    return isKeyDown();
   }

    static bool isKeyDown(int var0) {
      if (Core.CurrentTextEntryBox != nullptr && Core.CurrentTextEntryBox.DoingTextEntry) {
    return false;
      } else {
    return bDown = = nullptr ? false : bDown[var0];
      }
   }

    static bool wasKeyDown(int var0) {
      if (Core.CurrentTextEntryBox != nullptr && Core.CurrentTextEntryBox.DoingTextEntry) {
    return false;
      } else {
    return bLastDown = = nullptr ? false : bLastDown[var0];
      }
   }

    static void eatKeyPress(int var0) {
      if (var0 >= 0 && var0 < bEatKey.length) {
         bEatKey[var0] = true;
      }
   }

    static void setDoLuaKeyPressed(bool var0) {
      doLuaKeyPressed = var0;
   }

    static KeyEventQueue getEventQueue() {
      assert Thread.currentThread() == GameWindow.GameThread;

      return s_keyboardStateCache.getState().getEventQueue();
   }

    static KeyEventQueue getEventQueuePolling() {
      assert Thread.currentThread() == RenderThread.RenderThread;

      return s_keyboardStateCache.getStatePolling().getEventQueue();
   }
}
} // namespace input
} // namespace zombie
