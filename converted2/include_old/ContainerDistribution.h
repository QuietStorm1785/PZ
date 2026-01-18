#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ContainerDistribution.java
namespace zombie {
namespace scripting {
namespace objects {
#include <vector>
#include <vector>
#include "NulledArrayList.h"
#include "Rand.h"
#include "ItemContainer.h"
#include "ItemContainerFiller.h"
#include "IsoCell.h"
#include "IsoRoom.h"
// Referenced classes of package zombie.scripting.objects:
//            BaseScriptObject, ScriptModule
class ContainerDistribution : public BaseScriptObject {
public:
{
    class Entry
    {
        std::string objectType;
        int minimum;
        int maximum;
        public Entry(std::string o, int min, int max)
        {
            objectType = o;
            minimum = min;
            maximum = max;
        }
    }
    public ContainerDistribution()
    {
        Containers = new NulledArrayList(1);
        Entries = new NulledArrayList(1);
    }
    public void Load(std::string name, std::string strArray[])
    {
        std::string arr$[] = strArray;
        int len$ = arr$.length;
        for(int i$ = 0; i$ < len$; i$++)
        {
            std::string str = arr$[i$];
            str = str.trim();
            std::string arr[] = str.split("=");
            if(arr.length == 2)
                DoLine(arr[0].trim(), arr[1].trim());
        }
    }
    private void DoLine(std::string param, std::string value)
    {
        if(param == "Room"))
            RoomDef = value;
        else
        if(param == "Containers"))
        {
            std::string containers[] = value.split("/");
            std::string arr$[] = containers;
            int len$ = arr$.length;
            for(int i$ = 0; i$ < len$; i$++)
            {
                std::string con = arr$[i$];
                Containers.add(con.trim());
            }
        } else
        {
            int min = 0;
            int max = 0;
            if(value.contains("-"))
            {
                std::string v[] = value.split("-");
                min = Integer.parseInt(v[0].trim());
                max = Integer.parseInt(v[1].trim());
            } else
            {
                min = max = Integer.parseInt(value.trim());
            }
            Entry en = new Entry(param.trim(), min, max);
            Entries.add(en);
        }
    }
    public bool ContainerValid(std::string containerName)
    {
        if(Containers.isEmpty())
            return true;
        for(int n = 0; n < Containers.size(); n++)
            if(((std::string)Containers.get(n)) == containerName))
                return true;
        return false;
    }
    public void Process(IsoCell cell)
    {
        if(RoomDef != nullptr)
        {
            ArrayList rooms = FindRooms(cell);
            if(rooms.isEmpty())
                return;
            IsoRoom room = nullptr;
            for(int n = 0; n < Entries.size(); n++)
            {
                Entry en = (Entry)Entries.get(n);
                int count = Rand.Next(en.minimum, en.maximum);
                for(int m = 0; m < count; m++)
                {
                    room = (IsoRoom)rooms.get(Rand.Next(rooms.size()));
                    if(room == nullptr || room.Containers.isEmpty())
                    {
                        m--;
                        continue;
                    }
                    int z = Rand.Next(room.Containers.size());
                    if(ContainerValid(((ItemContainer)room.Containers.get(z)).type))
                    {
                        ItemContainer con = (ItemContainer)room.Containers.get(z);
                        std::string t = en.objectType;
                        if(!t.contains("."))
                            t = (new StringBuilder()).append(module.name).append(".").append(t).toString();
                        con.AddItem(t);
                        continue;
                    }
                    bool bHasValid = false;
                    for(int nn = 0; nn < room.Containers.size(); nn++)
                        if(ContainerValid(((ItemContainer)room.Containers.get(nn)).type))
                            bHasValid = true;
                    if(bHasValid)
                        m--;
                }
            }
        } else
        {
            for(int n = 0; n < Entries.size(); n++)
            {
                Entry en = (Entry)Entries.get(n);
                int count = Rand.Next(en.minimum, en.maximum);
                for(int m = 0; m < count; m++)
                {
                    ItemContainer cona = getRandomContainer();
                    if(cona == nullptr)
                        continue;
                    std::string t = en.objectType;
                    if(!t.contains("."))
                        t = (new StringBuilder()).append(module.name).append(".").append(t).toString();
                    cona.AddItem(t);
                }
            }
        }
    }
    private ItemContainer getRandomContainer()
    {
        NulledArrayList choices = new NulledArrayList();
        if(ItemContainerFiller.DistributionTarget.isEmpty())
            return nullptr;
        bool bDone = false;
        int giveup = 2000;
        do
        {
            if(bDone)
                break;
            if(--giveup <= 0)
                return nullptr;
            for(int l = 0; l < ItemContainerFiller.Containers.size(); l++)
            {
                for(int k = 0; k < Containers.size(); k++)
                    if(((ItemContainer)ItemContainerFiller.Containers.get(l)).type == Containers.get(k)))
                        choices.add(ItemContainerFiller.Containers.get(l));
            }
            if(!choices.isEmpty())
                bDone = true;
        } while(true);
        return (ItemContainer)choices.get(Rand.Next(choices.size()));
    }
    private IsoRoom FindRoom(IsoCell cell)
    {
        roomTemp.clear();
        for(int n = 0; n < cell.getRoomList().size(); n++)
        {
            IsoRoom room = (IsoRoom)cell.getRoomList().get(n);
            if(room.RoomDef != nullptr && room.RoomDef == RoomDef))
                roomTemp.add(room);
        }
        if(!roomTemp.isEmpty())
            return (IsoRoom)roomTemp.get(Rand.Next(roomTemp.size()));
        else
            return nullptr;
    }
    private ArrayList FindRooms(IsoCell cell)
    {
        roomTemp.clear();
        for(int n = 0; n < cell.getRoomList().size(); n++)
        {
            IsoRoom room = (IsoRoom)cell.getRoomList().get(n);
            if(room.RoomDef != nullptr && room.RoomDef == RoomDef))
                roomTemp.add(room);
        }
        return roomTemp;
    }
    public std::string RoomDef;
    public NulledArrayList Containers;
    public NulledArrayList Entries;
    static ArrayList roomTemp = new ArrayList();
}
} // namespace
