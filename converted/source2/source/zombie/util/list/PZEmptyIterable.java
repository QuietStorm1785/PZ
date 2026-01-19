package zombie.util.list;

import java.util.Iterator;
import zombie.util.list.PZEmptyIterable.1;

public final class PZEmptyIterable<T> implements Iterable<T> {
   private static final PZEmptyIterable<Object> instance = new PZEmptyIterable<>();
   private final Iterator<T> s_it = new 1(this);

   private PZEmptyIterable() {
   }

   public static <E> PZEmptyIterable<E> getInstance() {
      return (PZEmptyIterable<E>)instance;
   }

   @Override
   public Iterator<T> iterator() {
      return this.s_it;
   }
}
