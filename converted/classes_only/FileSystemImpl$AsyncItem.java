package zombie.fileSystem;

import java.util.concurrent.FutureTask;

final class FileSystemImpl$AsyncItem {
   int m_id;
   FileTask m_task;
   FutureTask<Object> m_future;

   private FileSystemImpl$AsyncItem() {
   }
}
