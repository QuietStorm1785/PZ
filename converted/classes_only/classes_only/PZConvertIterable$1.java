package zombie.util.list;

import java.util.Iterator;

class PZConvertIterable$1 implements Iterator<T> {
   private Iterator<S> m_srcIterator;

   PZConvertIterable$1(PZConvertIterable var1) {
      this.this$0 = var1;
      this.m_srcIterator = this.this$0.m_srcIterable.iterator();
   }

   @Override
   public boolean hasNext() {
      return this.m_srcIterator.hasNext();
   }

   @Override
   public T next() {
      return (T)this.this$0.m_converter.apply(this.m_srcIterator.next());
   }
}
