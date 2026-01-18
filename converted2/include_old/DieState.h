#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:46
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   DieState.java
namespace zombie {
namespace ai {
namespace states {
#include "State.h"
#include "StateMachine.h"
#include "BodyDamage.h"
#include "IsoGameCharacter.h"
#include "IsoSurvivor.h"
#include "NulledArrayList.h"
#include "IsoDirections.h"
#include "IsoDeadBody.h"
#include "sprite.h"
#include "TutorialManager.h"
// Referenced classes of package zombie.ai.states:
//            ReanimateState
class DieState : public State {
public:
{
    public DieState()
    {
    }
    public static DieState instance()
    {
        return _instance;
    }
    public void enter(IsoGameCharacter owner)
    {
        owner.PlayAnim("ZombieDeath");
        owner.def.Frame = 0.0F;
        owner.setDefaultState(this);
        owner.getStateMachine().Lock = true;
        if((owner instanceof IsoSurvivor) && owner.getTimeSinceZombieAttack() < 10)
            ((IsoSurvivor)owner).ChewedByZombies();
    }
    public void execute(IsoGameCharacter owner)
    {
        if((int)owner.def.Frame == owner.sprite.CurrentAnim.Frames.size() - 1)
        {
            if(owner instanceof IsoSurvivor)
                ((IsoSurvivor)owner).SetAllFrames((short)(int)owner.def.Frame);
            if(owner == TutorialManager.instance.wife)
                owner.dir = IsoDirections.S;
            IsoDeadBody body = new IsoDeadBody(owner);
            if(owner.getBodyDamage().getInfectionLevel() > 60F)
                owner.getStateMachine().changeState(ReanimateState.instance());
        }
    }
    static DieState _instance = new DieState();
}} // namespace
