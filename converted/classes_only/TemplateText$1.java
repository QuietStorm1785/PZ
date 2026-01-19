package zombie.text.templating;

import zombie.characters.SurvivorFactory;

class TemplateText$1 implements IReplace {
   public String getString() {
      return SurvivorFactory.getRandomSurname();
   }
}
