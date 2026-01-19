package zombie.network;

enum FakeClientManager$Client$State {
   CONNECT,
   LOGIN,
   CHECKSUM,
   PLAYER_CONNECT,
   PLAYER_EXTRA_INFO,
   LOAD,
   RUN,
   WAIT,
   DISCONNECT,
   QUIT;
}
