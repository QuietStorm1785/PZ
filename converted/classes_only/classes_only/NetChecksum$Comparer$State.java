package zombie.network;

enum NetChecksum$Comparer$State {
   Init,
   SentTotalChecksum,
   SentGroupChecksum,
   SentFileChecksums,
   Success,
   Failed;
}
