package zombie.characters.action.conditions;

import org.w3c.dom.Element;
import zombie.characters.action.IActionCondition;
import zombie.characters.action.IActionCondition.IFactory;

public class LuaCall$Factory implements IFactory {
   public IActionCondition create(Element var1) {
      return new LuaCall();
   }
}
