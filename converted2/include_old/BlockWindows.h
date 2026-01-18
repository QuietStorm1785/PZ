#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   BlockWindows.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include <algorithm>
#include <vector>
#include "AquireSheetAndBlockWindow.h"
#include "characters.h"
#include "NulledArrayList.h"
#include "Rand.h"
#include "IsoGridSquare.h"
#include "IsoBuilding.h"
#include "IsoCurtain.h"
#include "IsoWindow.h"
#include "TextManager.h"
#include "UIFont.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            OrderSequence, Order, FollowOrder
class BlockWindows : public OrderSequence {
public:
{
    public BlockWindows(IsoGameCharacter chr, IsoBuilding building)
    {
        super(chr);
        windowsAll = new Stack();
        windowsFloorAB = new Stack();
        b = building;
    }
    public int renderDebug(int y)
    {
        int x = 50;
        TextManager.instance.DrawString(UIFont.Small, x, y, "BlockWindows", 1.0F, 1.0F, 1.0F, 1.0F);
        y += 30;
        if(ID < Orders.size())
            ((Order)Orders.get(ID)).renderDebug(y);
        return y;
    }
    public void initOrder()
    {
        if(((IsoSurvivor)character).getDescriptor().getGroup().Leader == character.getDescriptor())
        {
            for(int n = 0; n < character.getDescriptor().getGroup().Members.size(); n++)
            {
                SurvivorDesc desc = (SurvivorDesc)character.getDescriptor().getGroup().Members.get(n);
                if(desc.getInstance() != nullptr && (desc.getInstance().getOrder() == nullptr || (desc.getInstance().getOrder() instanceof FollowOrder)))
                    desc.getInstance().GiveOrder(new BlockWindows(desc.getInstance(), b), false);
            }
        }
        if(b.Windows.size() > 0)
        {
            IsoWindow r;
            for(; !b.Windows.isEmpty(); b.Windows.remove(r))
            {
                r = (IsoWindow)b.Windows.get(Rand.Next(b.Windows.size()));
                if(windowsAll.contains(r))
                    continue;
                IsoCurtain c = r.HasCurtains();
                windowsAll.add(r);
                if(r.square.getZ() < 2 && (c == nullptr || c.open))
                    windowsFloorAB.add(r);
            }
            b.Windows.addAll(windowsAll);
            for(int n = 0; n < windowsFloorAB.size(); n++)
            {
                IsoWindow w = (IsoWindow)windowsFloorAB.get(n);
                IsoCurtain c = w.HasCurtains();
                Orders.add(new AquireSheetAndBlockWindow(character, w, c));
            }
        }
    }
    Stack windowsAll;
    Stack windowsFloorAB;
    IsoBuilding b;
}
} // namespace
