package zombie.characters;

import zombie.characters.NetworkCharacter.Operation;
import zombie.iso.Vector2;

public class NetworkCharacter$Transform {
   public Vector2 position = new Vector2();
   public Vector2 rotation = new Vector2();
   public Operation operation = Operation.NONE;
   public boolean moving = false;
   public int time = 0;
}
