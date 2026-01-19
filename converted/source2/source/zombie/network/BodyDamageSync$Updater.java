package zombie.network;

import java.nio.ByteBuffer;
import zombie.GameWindow;
import zombie.characters.IsoPlayer;
import zombie.characters.BodyDamage.BodyDamage;
import zombie.characters.BodyDamage.BodyPart;
import zombie.characters.Moodles.MoodleType;
import zombie.core.network.ByteBufferWriter;
import zombie.network.PacketTypes.PacketType;

public final class BodyDamageSync$Updater {
   static ByteBuffer bb = ByteBuffer.allocate(1024);
   short localIndex;
   short remoteID;
   BodyDamage bdLocal;
   BodyDamage bdSent;
   boolean partStarted;
   byte partIndex;
   long sendTime;

   void update() {
      long var1 = System.currentTimeMillis();
      if (var1 - this.sendTime >= 500L) {
         this.sendTime = var1;
         bb.clear();
         int var3 = this.bdLocal.getParentChar().getMoodles().getMoodleLevel(MoodleType.Pain);
         if (this.compareFloats(this.bdLocal.getOverallBodyHealth(), (int)this.bdSent.getOverallBodyHealth())
            || var3 != this.bdSent.getRemotePainLevel()
            || this.bdLocal.IsFakeInfected != this.bdSent.IsFakeInfected
            || this.compareFloats(this.bdLocal.InfectionLevel, this.bdSent.InfectionLevel)) {
            bb.put((byte)50);
            bb.putFloat(this.bdLocal.getOverallBodyHealth());
            bb.put((byte)var3);
            bb.put((byte)(this.bdLocal.IsFakeInfected ? 1 : 0));
            bb.putFloat(this.bdLocal.InfectionLevel);
            this.bdSent.setOverallBodyHealth(this.bdLocal.getOverallBodyHealth());
            this.bdSent.setRemotePainLevel(var3);
            this.bdSent.IsFakeInfected = this.bdLocal.IsFakeInfected;
            this.bdSent.InfectionLevel = this.bdLocal.InfectionLevel;
         }

         for (int var4 = 0; var4 < this.bdLocal.BodyParts.size(); var4++) {
            this.updatePart(var4);
         }

         if (bb.position() > 0) {
            bb.put((byte)65);
            ByteBufferWriter var5 = GameClient.connection.startPacket();
            PacketType.BodyDamageUpdate.doPacket(var5);
            var5.putByte((byte)3);
            var5.putShort(IsoPlayer.players[this.localIndex].getOnlineID());
            var5.putShort(this.remoteID);
            var5.bb.put(bb.array(), 0, bb.position());
            PacketType.BodyDamageUpdate.send(GameClient.connection);
         }
      }
   }

   void updatePart(int var1) {
      BodyPart var2 = (BodyPart)this.bdLocal.BodyParts.get(var1);
      BodyPart var3 = (BodyPart)this.bdSent.BodyParts.get(var1);
      this.partStarted = false;
      this.partIndex = (byte)var1;
      var2.sync(var3, this);
      if (this.partStarted) {
         bb.put((byte)65);
      }
   }

   public void updateField(byte var1, boolean var2) {
      if (!this.partStarted) {
         bb.put((byte)64);
         bb.put(this.partIndex);
         this.partStarted = true;
      }

      bb.put(var1);
      bb.put((byte)(var2 ? 1 : 0));
   }

   private boolean compareFloats(float var1, float var2) {
      return Float.compare(var1, 0.0F) != Float.compare(var2, 0.0F) ? true : (int)var1 != (int)var2;
   }

   public boolean updateField(byte var1, float var2, float var3) {
      if (!this.compareFloats(var2, var3)) {
         return false;
      } else {
         if (!this.partStarted) {
            bb.put((byte)64);
            bb.put(this.partIndex);
            this.partStarted = true;
         }

         bb.put(var1);
         bb.putFloat(var2);
         return true;
      }
   }

   public void updateField(byte var1, String var2) {
      if (!this.partStarted) {
         bb.put((byte)64);
         bb.put(this.partIndex);
         this.partStarted = true;
      }

      bb.put(var1);
      GameWindow.WriteStringUTF(bb, var2);
   }
}
