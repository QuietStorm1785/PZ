package zombie.fileSystem;

final class FileSystemImpl$OpenTask extends FileTask {
   IFile m_file;
   String m_path;
   int m_mode;
   IFileTask2Callback m_cb;

   FileSystemImpl$OpenTask(FileSystem var1) {
      super(var1);
   }

   public Object call() throws Exception {
      return this.m_file.open(this.m_path, this.m_mode);
   }

   public void handleResult(Object var1) {
      if (this.m_cb != null) {
         this.m_cb.onFileTaskFinished(this.m_file, var1);
      }
   }

   public void done() {
      if ((this.m_mode & 5) == 5) {
         this.m_file_system.closeAsync(this.m_file, null);
      }

      this.m_file = null;
      this.m_path = null;
      this.m_cb = null;
   }
}
