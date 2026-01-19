package zombie.text.templating;

import zombie.characters.SurvivorFactory;

class TemplateText$3 implements IReplace {
   public String getString() {
      return SurvivorFactory.getRandomForename(false);
   }
}
