package zombie.characters.action.conditions;

import org.w3c.dom.Element;
import zombie.characters.action.IActionCondition;
import zombie.characters.action.IActionCondition.IFactory;

public class CharacterVariableCondition$Factory implements IFactory {
   public IActionCondition create(Element var1) {
      CharacterVariableCondition var2 = new CharacterVariableCondition();
      return var2.load(var1) ? var2 : null;
   }
}
