#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   EndMeetingOrder.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include <algorithm>
#include "characters.h"
#include "NulledArrayList.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            OrderSequence, GuardOrder
class EndMeetingOrder : public OrderSequence {
public:
{
    public EndMeetingOrder(IsoGameCharacter chr)
    {
        super(chr);
        this.chr = chr;
    }
    public bool complete()
    {
        return true;
    }
    public void initOrder()
    {
        for(int n = 0; n < chr.getDescriptor().getGroup().Members.size(); n++)
        {
            SurvivorDesc desc = (SurvivorDesc)chr.getDescriptor().getGroup().Members.get(n);
            if(desc != chr.getDescriptor() && desc.getInstance().InRoomWith(chr) && (desc.getInstance().getOrder() instanceof GuardOrder))
                desc.getInstance().getOrders().pop();
        }
    }
    IsoGameCharacter chr;
}
} // namespace
