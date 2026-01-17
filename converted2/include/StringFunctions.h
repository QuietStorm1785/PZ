#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   StringFunctions.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include <algorithm>
#include "IsoGameCharacter.h"
#include "SurvivorDesc.h"
class StringFunctions {
public:
{
    StringFunctions()
    {
    }
    static std::string EscapeChar(IsoGameCharacter chr, std::string str)
    {
        str = str.replace("$FIRSTNAME$", chr.getDescriptor().getForename());
        str = str.replace("$SURNAME$", chr.getDescriptor().getSurname());
        return str;
    }
    static std::string EscapeChar(IsoGameCharacter chr, Stack chrs, std::string str)
    {
        str = EscapeChar(chr, str);
        for(int n = 0; n < chrs.size(); n++)
        {
            str = str.replace((new StringBuilder()).append("$FIRSTNAME").append(n + 1).append("$").toString(), ((IsoGameCharacter)chrs.get(n)).getDescriptor().getForename());
            str = str.replace((new StringBuilder()).append("$SURNAME").append(n + 1).append("$").toString(), ((IsoGameCharacter)chrs.get(n)).getDescriptor().getSurname());
        }
        return str;
    }
}
} // namespace
