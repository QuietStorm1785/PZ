package zombie.core.Collections;

import java.util.Map.Entry;

abstract class AbstractEntry<TypeK, TypeV> implements Entry<TypeK, TypeV> {
   protected final TypeK _key;
   protected TypeV _val;

   public AbstractEntry(TypeK var1, TypeV var2) {
      this._key = (TypeK)var1;
      this._val = (TypeV)var2;
   }

   public AbstractEntry(Entry<TypeK, TypeV> var1) {
      this._key = (TypeK)var1.getKey();
      this._val = (TypeV)var1.getValue();
   }

   @Override
   public String toString() {
      return this._key + "=" + this._val;
   }

   @Override
   public TypeK getKey() {
      return this._key;
   }

   @Override
   public TypeV getValue() {
      return this._val;
   }

   @Override
   public boolean equals(Object var1) {
      return !(var1 instanceof Entry var2) ? false : eq(this._key, var2.getKey()) && eq(this._val, var2.getValue());
   }

   @Override
   public int hashCode() {
      return (this._key == null ? 0 : this._key.hashCode()) ^ (this._val == null ? 0 : this._val.hashCode());
   }

   private static boolean eq(Object var0, Object var1) {
      return var0 == null ? var1 == null : var0.equals(var1);
   }
}
