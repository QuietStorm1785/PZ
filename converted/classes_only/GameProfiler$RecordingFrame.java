package zombie;

public class GameProfiler$RecordingFrame {
   private String m_frameInvokerKey = "";
   private int FrameNo = -1;
   private long m_startTime = 0L;
   private long m_endTime = 0L;
   private long m_totalTime = 0L;

   public void transferFrom(GameProfiler$RecordingFrame var1) {
      this.clear();
      this.FrameNo = var1.FrameNo;
      this.m_frameInvokerKey = var1.m_frameInvokerKey;
      this.m_startTime = var1.m_startTime;
      this.m_endTime = var1.m_endTime;
      this.m_totalTime = var1.m_totalTime;
      var1.clear();
   }

   public void clear() {
      this.FrameNo = -1;
      this.m_frameInvokerKey = "";
      this.m_startTime = 0L;
      this.m_endTime = 0L;
      this.m_totalTime = 0L;
   }
}
