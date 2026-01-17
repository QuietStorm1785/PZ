#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   GotoNextTo.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include <algorithm>
#include "Behavior.h"
#include "FaceOrder.h"
#include "IsoGameCharacter.h"
#include "Rand.h"
#include "iso.h"
#include "TextManager.h"
#include "UIFont.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            Order, OrderSequence, GotoOrder
class GotoNextTo : public Order {
public:
{
    public GotoNextTo(IsoGameCharacter chr, int x, int y, int z)
    {
        super(chr);
        order = nullptr;
        order = new OrderSequence(chr);
        Stack choices = new Stack();
        IsoGridSquare osq = IsoWorld.instance.CurrentCell.getGridSquare(x, y, z);
        for(int ax = -1; ax <= 1; ax++)
        {
            for(int ay = -1; ay <= 1; ay++)
            {
                if(ax != 0 && ay != 0 || ax == 0 && ay == 0)
                    continue;
                IsoGridSquare sq = IsoWorld.instance.CurrentCell.getGridSquare(x + ax, y + ay, z);
                if(sq != nullptr && sq.isFree(false) && (osq == nullptr || sq.getRoom() == osq.getRoom()))
                    choices.add(sq);
            }
        }
        if(choices.isEmpty())
        {
            return;
        } else
        {
            IsoGridSquare choice = (IsoGridSquare)choices.get(Rand.Next(choices.size()));
            order.Orders.add(new GotoOrder(chr, choice.getX(), choice.getY(), choice.getZ()));
            Vector2 dirVec = new Vector2(0.0F, 0.0F);
            dirVec.x = x - choice.getX();
            dirVec.y = y - choice.getY();
            order.Orders.add(new FaceOrder(chr, IsoDirections.fromAngle(dirVec)));
            return;
        }
    }
    public int getAttackIfEnemiesAroundBias()
    {
        return character.getCurrentSquare().getRoom() == nullptr ? 0 : -1000;
    }
    public void update()
    {
        if(order != nullptr)
            order.update();
    }
    public bool complete()
    {
        if(order == nullptr)
            return true;
        else
            return order.complete();
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        if(order == nullptr)
            return zombie.behaviors.Behavior.BehaviorResult.Failed;
        else
            return order.process();
    }
    public int renderDebug(int y)
    {
        int x = 50;
        TextManager.instance.DrawString(UIFont.Small, x, y, "GotoNextTo", 1.0F, 1.0F, 1.0F, 1.0F);
        y += 30;
        if(order != nullptr)
            order.renderDebug(y);
        return y;
    }
    public void initOrder()
    {
        if(order != nullptr)
            order.initOrder();
    }
    public float getPriority(IsoGameCharacter character)
    {
        if(order == nullptr)
            return -100000F;
        else
            return order.getPriority(character);
    }
    OrderSequence order;
}
} // namespace
