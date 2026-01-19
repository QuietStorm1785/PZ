package zombie.ai.states;

import zombie.iso.IsoGridSquare;
import zombie.iso.LosUtil.TestResults;

interface SwipeStatePlayer$LOSVisitor {
   boolean visit(IsoGridSquare var1, IsoGridSquare var2);

   TestResults getResult();
}
