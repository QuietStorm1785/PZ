#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   LanguageDefinition.java
namespace zombie {
namespace scripting {
namespace objects {
#include "NulledArrayList.h"
// Referenced classes of package zombie.scripting.objects:
//            BaseScriptObject
class LanguageDefinition : public BaseScriptObject {
public:
{
    public LanguageDefinition()
    {
        Items = new NulledArrayList();
    }
    public std::string get(int index)
    {
        return (std::string)Items.get(index);
    }
    public void Load(std::string name, std::string strArray[])
    {
        for(int n = 0; n < strArray.length; n++)
            if(strArray[n] != nullptr)
                DoSource(strArray[n].trim());
    }
    private void DoSource(std::string type)
    {
        std::string source = "";
        source = type;
        Items.add(source);
    }
    public NulledArrayList Items;
}
} // namespace
