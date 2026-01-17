#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ShelfDistribution.java
namespace zombie {
namespace scripting {
namespace objects {
#include <algorithm>
#include "NulledArrayList.h"
#include "Rand.h"
#include "PropertyContainer.h"
#include "ItemContainerFiller.h"
#include "IsoCell.h"
#include "IsoGridSquare.h"
#include "IsoFlagType.h"
#include "ScriptManager.h"
// Referenced classes of package zombie.scripting.objects:
//            BaseScriptObject, Zone, ScriptModule
class ShelfDistribution : public BaseScriptObject {
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
    public ShelfDistribution()
    {
        LootedValue = 0;
        Entries = new NulledArrayList(1);
        ItemDepth = 0.5F;
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
            {
                DoLine(arr[0].trim(), arr[1].trim());
                continue;
            }
            if(arr[0].trim().length() > 0)
                Entries.add(new Entry(arr[0].trim(), 1, 1));
        }
    }
    private void DoLine(std::string param, std::string value)
    {
        if(param == "Zone"))
            Zone = value;
        if(param == "LootedValue"))
            LootedValue = Integer.parseInt(value);
        if(param == "ItemDepth"))
            ItemDepth = Float.parseFloat(value);
    }
    public void Process(IsoCell cell)
    {
        Stack zones = ScriptManager.instance.getZones(Zone);
        for(int n = 0; n < zones.size(); n++)
        {
            Zone z = (Zone)zones.get(n);
            for(int x = z.x; x < z.x2; x++)
            {
                for(int y = z.y; y < z.y2; y++)
                {
                    IsoGridSquare sq = cell.getGridSquare(x, y, z.z);
                    if(sq == nullptr)
                        continue;
                    float height;
                    std::string s;
                    if(sq.getProperties().Is(IsoFlagType.floorS) || sq.getProperties().Is(IsoFlagType.floorE))
                    {
                        height = 0.1F;
                        s = ((Entry)Entries.get(Rand.Next(Entries.size()))).objectType;
                        if(!s.contains("."))
                            s = (new StringBuilder()).append(module.name).append(".").append(s).toString();
                        ItemContainerFiller.FillTable(LootedValue, sq, nullptr, s, height, ItemDepth);
                    }
                    if(sq.getProperties().Is(IsoFlagType.tableS) || sq.getProperties().Is(IsoFlagType.tableE))
                    {
                        height = 0.4F;
                        s = ((Entry)Entries.get(Rand.Next(Entries.size()))).objectType;
                        if(!s.contains("."))
                            s = (new StringBuilder()).append(module.name).append(".").append(s).toString();
                        ItemContainerFiller.FillTable(LootedValue, sq, nullptr, s, height);
                    }
                    if(!sq.getProperties().Is(IsoFlagType.shelfE) && !sq.getProperties().Is(IsoFlagType.shelfS))
                        continue;
                    height = 0.65F;
                    s = ((Entry)Entries.get(Rand.Next(Entries.size()))).objectType;
                    if(!s.contains("."))
                        s = (new StringBuilder()).append(module.name).append(".").append(s).toString();
                    ItemContainerFiller.FillTable(LootedValue, sq, nullptr, s, height, ItemDepth);
                }
            }
        }
    }
    public std::string Zone;
    public int LootedValue;
    public NulledArrayList Entries;
    private float ItemDepth;
}
} // namespace
