package zombie.util.list;

import java.util.AbstractList;
import java.util.Comparator;
import java.util.List;
import java.util.Objects;
import java.util.RandomAccess;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.UnaryOperator;

public final class PZConvertList<S, T> extends AbstractList<T> implements RandomAccess {
   private final List<S> m_list;
   private final Function<S, T> m_converterST;
   private final Function<T, S> m_converterTS;

   public PZConvertList(List<S> var1, Function<S, T> var2) {
      this(var1, var2, null);
   }

   public PZConvertList(List<S> var1, Function<S, T> var2, Function<T, S> var3) {
      this.m_list = Objects.requireNonNull(var1);
      this.m_converterST = var2;
      this.m_converterTS = var3;
   }

   public boolean isReadonly() {
      return this.m_converterTS == null;
   }

   @Override
   public int size() {
      return this.m_list.size();
   }

   @Override
   public Object[] toArray() {
      return this.m_list.toArray();
   }

   @Override
   public <R> R[] toArray(R[] var1) {
      int var2 = this.size();

      for (int var3 = 0; var3 < var2 && var3 < var1.length; var3++) {
         Object var4 = this.get(var3);
         var1[var3] = var4;
      }

      if (var1.length > var2) {
         var1[var2] = null;
      }

      return (R[])var1;
   }

   @Override
   public T get(int var1) {
      return this.convertST(this.m_list.get(var1));
   }

   @Override
   public T set(int var1, T var2) {
      Object var3 = this.get(var1);
      this.setS(var1, this.convertTS((T)var2));
      return (T)var3;
   }

   public S setS(int var1, S var2) {
      Object var3 = this.m_list.get(var1);
      this.m_list.set(var1, (S)var2);
      return (S)var3;
   }

   @Override
   public int indexOf(Object var1) {
      int var2 = -1;
      int var3 = 0;

      for (int var4 = this.size(); var3 < var4; var3++) {
         if (objectsEqual(var1, this.get(var3))) {
            var2 = var3;
            break;
         }
      }

      return var2;
   }

   private static boolean objectsEqual(Object var0, Object var1) {
      return var0 == var1 || var0 != null && var0.equals(var1);
   }

   @Override
   public boolean contains(Object var1) {
      return this.indexOf(var1) != -1;
   }

   @Override
   public void forEach(Consumer<? super T> var1) {
      int var2 = 0;

      for (int var3 = this.size(); var2 < var3; var2++) {
         var1.accept(this.get(var2));
      }
   }

   @Override
   public void replaceAll(UnaryOperator<T> var1) {
      int var2 = 0;

      for (int var3 = this.size(); var2 < var3; var2++) {
         Object var4 = this.get(var2);
         Object var5 = var1.apply(var4);
         this.set(var2, (T)var5);
      }
   }

   @Override
   public void sort(Comparator<? super T> var1) {
      this.m_list.sort((var2, var3) -> var1.compare(this.convertST((S)var2), this.convertST((S)var3)));
   }

   private T convertST(S var1) {
      return this.m_converterST.apply((S)var1);
   }

   private S convertTS(T var1) {
      return this.m_converterTS.apply((T)var1);
   }
}
