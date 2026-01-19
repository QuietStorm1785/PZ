package com.jcraft.jorbis;

import com.jcraft.jorbis.Floor1.InfoFloor1;

class Floor1$LookFloor1 {
   static final int VIF_POSIT = 63;
   int[] forward_index;
   int frames;
   int[] hineighbor;
   int[] loneighbor;
   int n;
   int phrasebits;
   int postbits;
   int posts;
   int quant_q;
   int[] reverse_index;
   int[] sorted_index;
   InfoFloor1 vi;

   Floor1$LookFloor1(Floor1 var1) {
      this.this$0 = var1;
      this.forward_index = new int[65];
      this.hineighbor = new int[63];
      this.loneighbor = new int[63];
      this.reverse_index = new int[65];
      this.sorted_index = new int[65];
   }

   void free() {
      this.sorted_index = null;
      this.forward_index = null;
      this.reverse_index = null;
      this.hineighbor = null;
      this.loneighbor = null;
   }
}
