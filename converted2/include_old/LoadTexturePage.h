#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   LoadTexturePage.java
namespace zombie {
namespace scripting {
namespace commands {
#include <algorithm>
#include "FrameLoader.h"
#include "TexturePackPage.h"
// Referenced classes of package zombie.scripting.commands:
//            BaseCommand
class LoadTexturePage : public BaseCommand {
public:
{
    class WatchPair
    {
        public std::string name;
        public std::string token;
        public WatchPair(std::string name, std::string token)
        {
            this.name = name;
            this.token = token;
        }
    }
    public LoadTexturePage()
    {
        page = nullptr;
        Pairs = new Stack();
    }
    public void init(std::string object, std::string params[])
    {
        page = params[0];
        if(params.length > 1)
        {
            std::string name = nullptr;
            std::string token = nullptr;
            bool bAlt = false;
            for(int n = 1; n < params.length; n++)
            {
                if(!bAlt)
                {
                    token = nullptr;
                    name = params[n];
                } else
                {
                    token = params[n];
                    Pairs.add(new WatchPair(name, token));
                    name = nullptr;
                    token = nullptr;
                }
                bAlt = !bAlt;
            }
        }
    }
    public void begin()
    {
        if(FrameLoader.bServer)
            return;
        if(!Pairs.isEmpty())
            TexturePackPage.getPackPage(page, Pairs);
        else
            TexturePackPage.getPackPage(page);
    }
    public void Finish()
    {
    }
    public bool IsFinished()
    {
        return true;
    }
    public void update()
    {
    }
    public bool DoesInstantly()
    {
        return true;
    }
    std::string page;
    public Stack Pairs;
}
} // namespace
