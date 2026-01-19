package zombie.fileSystem;

final class FileSystemImpl$CloseTask extends FileTask {
   IFile m_file;
   IFileTask2Callback m_cb;

   FileSystemImpl$CloseTask(FileSystem var1) {
      super(var1);
   }

   public Object call() throws Exception {
      this.m_file.close();
      this.m_file.release();
      return null;
   }

   public void handleResult(Object var1) {
      if (this.m_cb != null) {
         this.m_cb.onFileTaskFinished(this.m_file, var1);
      }
   }

   public void done() {
      this.m_file = null;
      this.m_cb = null;
   }
}
