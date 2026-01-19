package zombie.characters.BodyDamage;

class BodyPartContacts$ContactNode {
   BodyPartType bodyPart;
   int depth = -1;
   BodyPartContacts$ContactNode parent;
   BodyPartContacts$ContactNode[] children;
   BodyPartContacts$ContactNode[] allContacts;
   BodyPartType bodyPartParent;
   BodyPartType[] bodyPartChildren;
   BodyPartType[] bodyPartAllContacts;
   boolean initialised = false;

   public BodyPartContacts$ContactNode(BodyPartType var1) {
      this.bodyPart = var1;
   }
}
