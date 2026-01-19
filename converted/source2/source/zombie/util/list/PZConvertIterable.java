package zombie.util.list;

import java.util.Iterator;
import java.util.function.Function;
import zombie.util.list.PZConvertIterable.1;

public final class PZConvertIterable<T, S> implements Iterable<T> {
   private final Iterable<S> m_srcIterable;
   private final Function<S, T> m_converter;

   public PZConvertIterable(Iterable<S> var1, Function<S, T> var2) {
      this.m_srcIterable = var1;
      this.m_converter = var2;
   }

   @Override
   public Iterator<T> iterator() {
      return new 1(this);
   }
}
