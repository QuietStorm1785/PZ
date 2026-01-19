package zombie.inventory;

import zombie.inventory.ItemContainer.ConditionComparator;
import zombie.inventory.ItemContainer.EvalArgComparator;
import zombie.inventory.ItemContainer.EvalComparator;
import zombie.popman.ObjectPool;

final class ItemContainer$Comparators {
   ObjectPool<ConditionComparator> condition = new ObjectPool(ConditionComparator::new);
   ObjectPool<EvalComparator> eval = new ObjectPool(EvalComparator::new);
   ObjectPool<EvalArgComparator> evalArg = new ObjectPool(EvalArgComparator::new);

   private ItemContainer$Comparators() {
   }
}
