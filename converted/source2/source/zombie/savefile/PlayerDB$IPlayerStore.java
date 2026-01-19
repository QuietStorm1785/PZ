package zombie.savefile;

import gnu.trove.set.hash.TIntHashSet;
import zombie.savefile.PlayerDB.PlayerData;

interface PlayerDB$IPlayerStore {
   void init(TIntHashSet var1) throws Exception;

   void Reset() throws Exception;

   void save(PlayerData var1) throws Exception;

   boolean load(PlayerData var1) throws Exception;

   boolean loadEverythingExceptBytes(PlayerData var1) throws Exception;
}
