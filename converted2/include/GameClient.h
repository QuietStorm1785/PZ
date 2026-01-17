#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   GameClient.java
namespace zombie {
namespace network {
#include "IsoPlayer.h"
#include "IsoDirections.h"
#include "IsoAnim.h"
#include "IsoSprite.h"
// Referenced classes of package zombie.network:
//            ClientPlayerUpdateData
class GameClient {
public:
{
    public GameClient()
    {
        readyForGameData = false;
        readyForUpdateData = false;
        updatedelay = 5;
        pingUpdate = 60;
    }
    public bool Connect(std::string ip)
    {
        return ip == nullptr ? true : true;
    }
    public void update()
    {
        updatedelay--;
        ClientPlayerUpdateData da = new ClientPlayerUpdateData();
        da.x = IsoPlayer.getInstance().getX();
        da.y = IsoPlayer.getInstance().getY();
        da.z = IsoPlayer.getInstance().getZ();
        da.animID = IsoPlayer.getInstance().sprite.CurrentAnim.ID;
        da.dir = IsoPlayer.getInstance().dir.index();
    }
    public void SendPlayer(IsoPlayer isoplayer)
    {
    }
    public void SendToServerTCP(Object obj)
    {
    }
    public int getPing()
    {
        return 0;
    }
    public static GameClient instance = new GameClient();
    public bool readyForGameData;
    public bool readyForUpdateData;
    public int updatedelay;
    public int pingUpdate;
}
} // namespace
