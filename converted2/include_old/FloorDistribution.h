#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   FloorDistribution.java
namespace zombie {
namespace scripting {
namespace objects {
#include <algorithm>
#include "NulledArrayList.h"
#include "Rand.h"
#include "IsoCell.h"
#include "IsoGridSquare.h"
#include "ScriptManager.h"
// Referenced classes of package zombie.scripting.objects:
//            BaseScriptObject, Zone, ScriptModule
class FloorDistribution : public BaseScriptObject {
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
    public FloorDistribution()
    {
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
        if(param == "Zone"))
        {
            Zone = value;
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
    public void Process(IsoCell cell)
    {
        Stack zones = ScriptManager.instance.getZones(Zone);
        if(zones.isEmpty())
            return;
        for(int m = 0; m < Entries.size(); m++)
        {
            int count = Rand.Next(((Entry)Entries.get(m)).minimum, ((Entry)Entries.get(m)).maximum);
            for(int n = 0; n < count; n++)
            {
                Zone choice = (Zone)zones.get(Rand.Next(zones.size()));
                IsoGridSquare sq = cell.getFreeTile(new zombie.iso.IsoCell.Zone(choice.name, choice.x, choice.y, choice.x2 - choice.x, choice.y2 - choice.y, choice.z));
                if(sq == nullptr)
                    continue;
                std::string na = ((Entry)Entries.get(m)).objectType;
                if(!na.contains("."))
                    na = (new StringBuilder()).append(module.name).append(".").append(na).toString();
                sq.AddWorldInventoryItem(na, (float)(100 + Rand.Next(400)) / 1000F, (float)(100 + Rand.Next(400)) / 1000F, 0.0F);
            }
        }
    }
    public std::string Zone;
    public NulledArrayList Entries;
}
} // namespace
