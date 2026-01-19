package zombie.network;

interface ServerChunkLoader$SaveTask {
   void save() throws Exception;

   void release();

   int wx();

   int wy();
}
