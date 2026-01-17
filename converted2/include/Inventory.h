#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Inventory.java
namespace zombie {
namespace scripting {
namespace objects {
#include "NulledArrayList.h"
// Referenced classes of package zombie.scripting.objects:
//            BaseScriptObject
class Inventory : public BaseScriptObject {
public:
{
    class Source
    {
        public std::string type;
        public int count;
        public Source()
        {
            count = 1;
        }
    }
    public Inventory()
    {
        Items = new NulledArrayList();
    }
    public void Load(std::string name, std::string strArray[])
    {
        for(int n = 0; n < strArray.length; n++)
            if(strArray[n] != nullptr)
                DoSource(strArray[n].trim());
    }
    private void DoSource(std::string type)
    {
        Source source = new Source();
        if(type.contains("="))
        {
            source.count = Integer.parseInt(type.split("=")[1].trim());
            type = type.split("=")[0].trim();
        }
        if(type == "nullptr"))
            source.type = nullptr;
        else
            source.type = type;
        Items.add(source);
    }
    public NulledArrayList Items;
}
} // namespace
