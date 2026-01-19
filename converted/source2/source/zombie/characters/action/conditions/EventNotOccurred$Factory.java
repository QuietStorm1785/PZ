package zombie.characters.action.conditions;

import org.w3c.dom.Element;
import zombie.characters.action.IActionCondition;
import zombie.characters.action.IActionCondition.IFactory;

public class EventNotOccurred$Factory implements IFactory {
   public IActionCondition create(Element var1) {
      EventNotOccurred var2 = new EventNotOccurred();
      return var2.load(var1) ? var2 : null;
   }
}
