package zombie.inventory;

import zombie.inventory.ItemContainer.CategoryPredicate;
import zombie.inventory.ItemContainer.EvalArgPredicate;
import zombie.inventory.ItemContainer.EvalPredicate;
import zombie.inventory.ItemContainer.TagEvalArgPredicate;
import zombie.inventory.ItemContainer.TagEvalPredicate;
import zombie.inventory.ItemContainer.TagPredicate;
import zombie.inventory.ItemContainer.TypeEvalArgPredicate;
import zombie.inventory.ItemContainer.TypeEvalPredicate;
import zombie.inventory.ItemContainer.TypePredicate;
import zombie.popman.ObjectPool;

final class ItemContainer$Predicates {
   final ObjectPool<CategoryPredicate> category = new ObjectPool(CategoryPredicate::new);
   final ObjectPool<EvalPredicate> eval = new ObjectPool(EvalPredicate::new);
   final ObjectPool<EvalArgPredicate> evalArg = new ObjectPool(EvalArgPredicate::new);
   final ObjectPool<TagPredicate> tag = new ObjectPool(TagPredicate::new);
   final ObjectPool<TagEvalPredicate> tagEval = new ObjectPool(TagEvalPredicate::new);
   final ObjectPool<TagEvalArgPredicate> tagEvalArg = new ObjectPool(TagEvalArgPredicate::new);
   final ObjectPool<TypePredicate> type = new ObjectPool(TypePredicate::new);
   final ObjectPool<TypeEvalPredicate> typeEval = new ObjectPool(TypeEvalPredicate::new);
   final ObjectPool<TypeEvalArgPredicate> typeEvalArg = new ObjectPool(TypeEvalArgPredicate::new);

   private ItemContainer$Predicates() {
   }
}
