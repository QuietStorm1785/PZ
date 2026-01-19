package zombie.network;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.util.concurrent.ConcurrentLinkedQueue;
import zombie.debug.DebugLog;
import zombie.network.RCONServer.ExecCommand;
import zombie.network.RCONServer.ServerThread;

public class RCONServer {
   public static final int SERVERDATA_RESPONSE_VALUE = 0;
   public static final int SERVERDATA_AUTH_RESPONSE = 2;
   public static final int SERVERDATA_EXECCOMMAND = 2;
   public static final int SERVERDATA_AUTH = 3;
   private static RCONServer instance;
   private ServerSocket welcomeSocket;
   private ServerThread thread;
   private String password;
   private ConcurrentLinkedQueue<ExecCommand> toMain = new ConcurrentLinkedQueue<>();

   private RCONServer(int var1, String var2, boolean var3) {
      this.password = var2;

      try {
         this.welcomeSocket = new ServerSocket();
         if (var3) {
            this.welcomeSocket.bind(new InetSocketAddress("127.0.0.1", var1));
         } else if (GameServer.IPCommandline != null) {
            this.welcomeSocket.bind(new InetSocketAddress(GameServer.IPCommandline, var1));
         } else {
            this.welcomeSocket.bind(new InetSocketAddress(var1));
         }

         DebugLog.log("RCON: listening on port " + var1);
      } catch (IOException var7) {
         DebugLog.log("RCON: error creating socket on port " + var1);
         var7.printStackTrace();

         try {
            this.welcomeSocket.close();
            this.welcomeSocket = null;
         } catch (IOException var6) {
            var6.printStackTrace();
         }

         return;
      }

      this.thread = new ServerThread(this);
      this.thread.start();
   }

   private void updateMain() {
      for (ExecCommand var1 = this.toMain.poll(); var1 != null; var1 = this.toMain.poll()) {
         var1.update();
      }
   }

   public void quit() {
      if (this.welcomeSocket != null) {
         try {
            this.welcomeSocket.close();
         } catch (IOException var2) {
         }

         this.welcomeSocket = null;
         this.thread.quit();
         this.thread = null;
      }
   }

   public static void init(int var0, String var1, boolean var2) {
      instance = new RCONServer(var0, var1, var2);
   }

   public static void update() {
      if (instance != null) {
         instance.updateMain();
      }
   }

   public static void shutdown() {
      if (instance != null) {
         instance.quit();
      }
   }
}
