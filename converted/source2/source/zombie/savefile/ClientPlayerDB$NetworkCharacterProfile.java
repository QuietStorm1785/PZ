package zombie.savefile;

final class ClientPlayerDB$NetworkCharacterProfile {
   boolean isLoaded;
   final byte[][] character;
   String username;
   String server;
   int playerCount;
   final int[] worldVersion;
   final float[] x;
   final float[] y;
   final float[] z;
   final boolean[] isDead;

   public ClientPlayerDB$NetworkCharacterProfile(ClientPlayerDB var1) {
      this.this$0 = var1;
      this.isLoaded = false;
      this.playerCount = 0;
      this.character = new byte[4][];
      this.worldVersion = new int[4];
      this.x = new float[4];
      this.y = new float[4];
      this.z = new float[4];
      this.isDead = new boolean[4];
   }
}
