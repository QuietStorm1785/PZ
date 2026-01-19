package zombie.characters;

import java.util.ArrayList;
import java.util.Stack;
import zombie.characters.IsoPlayer.VehicleContainer;

class IsoPlayer$VehicleContainerData {
   ArrayList<VehicleContainer> tempContainers = new ArrayList<>();
   ArrayList<VehicleContainer> containers = new ArrayList<>();
   Stack<VehicleContainer> freeContainers = new Stack<>();

   private IsoPlayer$VehicleContainerData() {
   }
}
