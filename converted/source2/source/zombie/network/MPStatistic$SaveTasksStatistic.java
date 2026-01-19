package zombie.network;

import zombie.network.MPStatistic.TasksStatistic;

public class MPStatistic$SaveTasksStatistic extends TasksStatistic {
   private int SaveUnloadedTasksAdded = 0;
   private int SaveLoadedTasksAdded = 0;
   private int SaveGameTimeTasksAdded = 0;
   private int QuitThreadTasksAdded = 0;

   public void Clear() {
      super.Clear();
      this.SaveUnloadedTasksAdded = 0;
      this.SaveLoadedTasksAdded = 0;
      this.SaveGameTimeTasksAdded = 0;
      this.QuitThreadTasksAdded = 0;
   }

   public String PrintTitle(String var1) {
      return var1 + "SaveUnloadedAdded; " + var1 + "SaveLoadedAdded; " + var1 + "SaveGameTimeAdded; " + var1 + "QuitThreadAdded; " + var1 + "Processed; ";
   }

   public String Print() {
      return this.SaveUnloadedTasksAdded
         + "; "
         + this.SaveLoadedTasksAdded
         + "; "
         + this.SaveGameTimeTasksAdded
         + "; "
         + this.QuitThreadTasksAdded
         + "; "
         + this.processed
         + "; ";
   }

   public void SaveUnloadedTasksAdded() {
      this.SaveUnloadedTasksAdded++;
   }

   public void SaveLoadedTasksAdded() {
      this.SaveLoadedTasksAdded++;
   }

   public void SaveGameTimeTasksAdded() {
      this.SaveGameTimeTasksAdded++;
   }

   public void QuitThreadTasksAdded() {
      this.QuitThreadTasksAdded++;
   }
}
