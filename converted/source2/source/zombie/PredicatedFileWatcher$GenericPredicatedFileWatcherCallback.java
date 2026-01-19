package zombie;

import zombie.PredicatedFileWatcher.IPredicatedDataPacketFileWatcherCallback;
import zombie.PredicatedFileWatcher.IPredicatedFileWatcherCallback;
import zombie.debug.DebugLog;
import zombie.util.PZXmlParserException;
import zombie.util.PZXmlUtil;

public class PredicatedFileWatcher$GenericPredicatedFileWatcherCallback<T> implements IPredicatedFileWatcherCallback {
   private final Class<T> m_class;
   private final IPredicatedDataPacketFileWatcherCallback<T> m_callback;

   public PredicatedFileWatcher$GenericPredicatedFileWatcherCallback(Class<T> var1, IPredicatedDataPacketFileWatcherCallback<T> var2) {
      this.m_class = var1;
      this.m_callback = var2;
   }

   public void call(String var1) {
      Object var2;
      try {
         var2 = PZXmlUtil.parse(this.m_class, var1);
      } catch (PZXmlParserException var4) {
         DebugLog.General.error("Exception thrown. " + var4);
         return;
      }

      this.m_callback.call(var2);
   }
}
