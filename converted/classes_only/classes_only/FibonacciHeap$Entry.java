package zombie.core.utils;

public final class FibonacciHeap$Entry<T> {
   private int mDegree = 0;
   private boolean mIsMarked = false;
   private FibonacciHeap$Entry<T> mNext;
   private FibonacciHeap$Entry<T> mPrev;
   private FibonacciHeap$Entry<T> mParent;
   private FibonacciHeap$Entry<T> mChild;
   private T mElem;
   private double mPriority;

   public T getValue() {
      return this.mElem;
   }

   public void setValue(T var1) {
      this.mElem = (T)var1;
   }

   public double getPriority() {
      return this.mPriority;
   }

   private FibonacciHeap$Entry(T var1, double var2) {
      this.mNext = this.mPrev = this;
      this.mElem = (T)var1;
      this.mPriority = var2;
   }
}
