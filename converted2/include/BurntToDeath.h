#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:46
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   BurntToDeath.java
namespace zombie {
namespace ai {
namespace states {
#include "SoundManager.h"
#include "State.h"
#include "StateMachine.h"
#include "IsoGameCharacter.h"
#include "IsoZombie.h"
#include "NulledArrayList.h"
#include "IsoDirections.h"
#include "IsoWorld.h"
#include "IsoDeadBody.h"
#include "IsoFireManager.h"
#include "sprite.h"
#include "TutorialManager.h"
class BurntToDeath : public State {
public:
{
    public BurntToDeath()
    {
    }
    public static BurntToDeath instance()
    {
        return _instance;
    }
    public void enter(IsoGameCharacter owner)
    {
        if(!(owner instanceof IsoZombie))
            owner.PlayAnim("Die");
        else
            owner.PlayAnim("ZombieDeath");
        owner.getStateMachine().Lock = true;
        SoundManager.instance.PlayWorldSound("splat", owner.getCurrentSquare(), 0.4F, 10F, 0.6F, 2, false);
    }
    public void execute(IsoGameCharacter owner)
    {
        if(owner.def.Frame == (float)(owner.sprite.CurrentAnim.Frames.size() - 1))
        {
            if(owner == TutorialManager.instance.wife)
                owner.dir = IsoDirections.S;
            owner.RemoveAttachedAnims();
            IsoFireManager.StartFire(owner.getCell(), owner.getCurrentSquare(), true, 60);
            if(owner instanceof IsoZombie)
                IsoWorld.instance.MetaCellGrid[IsoWorld.instance.x][IsoWorld.instance.y].zombieCount--;
            IsoDeadBody body = new IsoDeadBody(owner);
        }
    }
    public void exit(IsoGameCharacter owner)
    {
        owner.setIgnoreMovementForDirection(false);
    }
    static BurntToDeath _instance = new BurntToDeath();
}} // namespace
