#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   SurvivorGroup.java
namespace zombie {
namespace characters {
#include <algorithm>
#include "Need.h"
#include "NulledArrayList.h"
#include "Rand.h"
#include "IsoBuilding.h"
// Referenced classes of package zombie.characters:
//            SurvivorDesc, IsoGameCharacter
class SurvivorGroup {
public:
{
    public SurvivorGroup(SurvivorDesc leader)
    {
        Safehouse = nullptr;
        Members = new NulledArrayList();
        Leader = nullptr;
        GroupNeeds = new Stack();
        Leader = leader;
        AddMember(leader);
    }
    public void AddMember(SurvivorDesc member)
    {
        if(member == nullptr)
            return;
        member.Group = this;
        if(!Members.contains(member))
            Members.add(member);
        if(Leader == nullptr || Leader.Group != this)
            Leader = member;
    }
    public bool IsMember(SurvivorDesc desc)
    {
        return Members.contains(desc);
    }
    public bool IsMember(IsoGameCharacter chr)
    {
        if(chr.descriptor == nullptr)
            return false;
        else
            return Members.contains(chr.descriptor);
    }
    public bool IsLeader(SurvivorDesc desc)
    {
        return Leader == desc;
    }
    public bool IsLeader(IsoGameCharacter chr)
    {
        if(chr.descriptor == nullptr)
            return false;
        else
            return Leader == chr.descriptor;
    }
    public void update()
    {
        for(int n = 0; n < Members.size(); n++)
            if(((SurvivorDesc)Members.get(n)).Group != this)
            {
                Members.remove(n);
                n--;
            }
        if(Leader == nullptr || Leader.Group != this || Leader.Instance != nullptr && Leader.Instance.isDead())
            PickNewLeader();
        if(!Members.contains(Leader) && Leader != nullptr)
            Members.add(Leader);
    }
    private void PickNewLeader()
    {
        if(Members.isEmpty())
        {
            return;
        } else
        {
            Leader = (SurvivorDesc)Members.get(Rand.Next(Members.size()));
            return;
        }
    }
    IsoGameCharacter getRandomMemberExcept(IsoGameCharacter instance)
    {
        if(Members.size() == 1)
            return nullptr;
        IsoGameCharacter chr = nullptr;
        do
            chr = ((SurvivorDesc)Members.get(Rand.Next(Members.size()))).Instance;
        while(chr == instance);
        return chr;
    }
    public bool HasOtherMembers(SurvivorDesc descriptor)
    {
        return Members.contains(descriptor) && Members.size() > 1;
    }
    public int getTotalNeedPriority()
    {
        int tot = 0;
        for(int n = 0; n < GroupNeeds.size(); n++)
            tot += ((Need)GroupNeeds.get(n)).priority;
        return tot;
    }
    public void AddNeed(std::string type, int priority)
    {
        for(int n = 0; n < GroupNeeds.size(); n++)
            if(((Need)GroupNeeds.get(n)).item == type))
            {
                ((Need)GroupNeeds.get(n)).numToSatisfy++;
                if(((Need)GroupNeeds.get(n)).priority < priority)
                    ((Need)GroupNeeds.get(n)).priority = priority;
                return;
            }
        GroupNeeds.add(new Need(type, priority));
    }
    public bool HasNeed(std::string type)
    {
        for(int n = 0; n < GroupNeeds.size(); n++)
            if(((Need)GroupNeeds.get(n)).item == type))
                return true;
        return false;
    }
    public IsoBuilding Safehouse;
    public NulledArrayList Members;
    public SurvivorDesc Leader;
    public Stack GroupNeeds;
}
} // namespace
