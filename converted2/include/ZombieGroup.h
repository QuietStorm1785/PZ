#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ZombieGroup.java
namespace zombie {
namespace characters {
// Referenced classes of package zombie.characters:
//            IsoZombie
class ZombieGroup {
public:
{
    public ZombieGroup()
    {
        zombies = new IsoZombie[MaxSize];
        Leader = nullptr;
    }
    void update()
    {
        IsoZombie oldLeader = Leader;
        if(Leader == nullptr || Leader.isDead())
        {
            IsoZombie z = nullptr;
            int n = 0;
            do
            {
                z = zombies[n];
                if(z != nullptr && z.isDead())
                {
                    zombies[n] = nullptr;
                    z = nullptr;
                }
            } while(++n < MaxSize && (z == nullptr || z.isDead()));
            if(n < MaxSize)
            {
                Leader = z;
                if(oldLeader == nullptr);
            }
        }
    }
    public static int MaxSize = 200;
    public IsoZombie zombies[];
    public IsoZombie Leader;
}
} // namespace
