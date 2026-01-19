package zombie.network;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.concurrent.ConcurrentLinkedQueue;
import zombie.debug.DebugLog;
import zombie.network.RCONServer.ExecCommand;

class RCONServer$ClientThread extends Thread {
   public Socket socket;
   public boolean bAuth;
   public boolean bQuit;
   private String password;
   private InputStream in;
   private OutputStream out;
   private ConcurrentLinkedQueue<ExecCommand> toThread = new ConcurrentLinkedQueue<>();
   private int pendingCommands;

   public RCONServer$ClientThread(Socket var1, String var2) {
      this.socket = var1;
      this.password = var2;

      try {
         this.in = var1.getInputStream();
         this.out = var1.getOutputStream();
      } catch (IOException var4) {
         var4.printStackTrace();
      }

      this.setName("RCONClient" + var1.getLocalPort());
   }

   @Override
   public void run() {
      if (this.in != null) {
         if (this.out != null) {
            while (!this.bQuit) {
               try {
                  this.runInner();
               } catch (SocketException var3) {
                  this.bQuit = true;
               } catch (Exception var4) {
                  var4.printStackTrace();
               }
            }

            try {
               this.socket.close();
            } catch (IOException var2) {
               var2.printStackTrace();
            }

            DebugLog.log("RCON: connection closed " + this.socket.toString());
         }
      }
   }

   private void runInner() throws IOException {
      byte[] var1 = new byte[4];
      int var2 = this.in.read(var1, 0, 4);
      if (var2 < 0) {
         this.bQuit = true;
      } else {
         ByteBuffer var3 = ByteBuffer.wrap(var1);
         var3.order(ByteOrder.LITTLE_ENDIAN);
         int var4 = var3.getInt();
         int var5 = var4;
         byte[] var6 = new byte[var4];

         do {
            var2 = this.in.read(var6, var4 - var5, var5);
            if (var2 < 0) {
               this.bQuit = true;
               return;
            }

            var5 -= var2;
         } while (var5 > 0);

         var3 = ByteBuffer.wrap(var6);
         var3.order(ByteOrder.LITTLE_ENDIAN);
         int var7 = var3.getInt();
         int var8 = var3.getInt();
         String var9 = new String(var3.array(), var3.position(), var3.limit() - var3.position() - 2);
         this.handlePacket(var7, var8, var9);
      }
   }

   private void handlePacket(int var1, int var2, String var3) throws IOException {
      if (!"players".equals(var3)) {
         DebugLog.log("RCON: ID=" + var1 + " Type=" + var2 + " Body='" + var3 + "' " + this.socket.toString());
      }

      switch (var2) {
         case 0:
            if (this.checkAuth()) {
               ByteBuffer var8 = ByteBuffer.allocate(14);
               var8.order(ByteOrder.LITTLE_ENDIAN);
               var8.putInt(var8.capacity() - 4);
               var8.putInt(var1);
               var8.putInt(0);
               var8.putShort((short)0);
               this.out.write(var8.array());
               this.out.write(var8.array());
            }
            break;
         case 1:
         default:
            DebugLog.log("RCON: unknown packet Type=" + var2);
            break;
         case 2:
            if (!this.checkAuth()) {
               break;
            }

            ExecCommand var5 = new ExecCommand(var1, var3, this);
            this.pendingCommands++;
            RCONServer.instance.toMain.add(var5);

            while (this.pendingCommands > 0) {
               var5 = this.toThread.poll();
               if (var5 != null) {
                  this.pendingCommands--;
                  this.handleResponse(var5);
               } else {
                  try {
                     Thread.sleep(50L);
                  } catch (InterruptedException var7) {
                     if (this.bQuit) {
                        return;
                     }
                  }
               }
            }
            break;
         case 3:
            this.bAuth = var3.equals(this.password);
            if (!this.bAuth) {
               DebugLog.log("RCON: password doesn't match");
               this.bQuit = true;
            }

            ByteBuffer var4 = ByteBuffer.allocate(14);
            var4.order(ByteOrder.LITTLE_ENDIAN);
            var4.putInt(var4.capacity() - 4);
            var4.putInt(var1);
            var4.putInt(0);
            var4.putShort((short)0);
            this.out.write(var4.array());
            var4.clear();
            var4.putInt(var4.capacity() - 4);
            var4.putInt(this.bAuth ? var1 : -1);
            var4.putInt(2);
            var4.putShort((short)0);
            this.out.write(var4.array());
      }
   }

   public void handleResponse(ExecCommand var1) {
      String var2 = var1.response;
      if (var2 == null) {
         var2 = "";
      }

      ByteBuffer var3 = ByteBuffer.allocate(12 + var2.length() + 2);
      var3.order(ByteOrder.LITTLE_ENDIAN);
      var3.putInt(var3.capacity() - 4);
      var3.putInt(var1.ID);
      var3.putInt(0);
      var3.put(var2.getBytes());
      var3.putShort((short)0);

      try {
         this.out.write(var3.array());
      } catch (IOException var5) {
         var5.printStackTrace();
      }
   }

   private boolean checkAuth() throws IOException {
      if (this.bAuth) {
         return true;
      } else {
         this.bQuit = true;
         ByteBuffer var1 = ByteBuffer.allocate(14);
         var1.order(ByteOrder.LITTLE_ENDIAN);
         var1.putInt(var1.capacity() - 4);
         var1.putInt(-1);
         var1.putInt(2);
         var1.putShort((short)0);
         this.out.write(var1.array());
         return false;
      }
   }

   public void quit() {
      if (this.socket != null) {
         try {
            this.socket.close();
         } catch (IOException var3) {
         }
      }

      this.bQuit = true;
      this.interrupt();

      while (this.isAlive()) {
         try {
            Thread.sleep(50L);
         } catch (InterruptedException var2) {
            var2.printStackTrace();
         }
      }
   }
}
