package zombie.text.templating;

import zombie.characters.SurvivorFactory;

class TemplateText$4 implements IReplace {
   public String getString() {
      return SurvivorFactory.getRandomForename(true);
   }
}
