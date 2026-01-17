#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   UnlockTasksOnComplete.java
namespace zombie {
namespace scripting {
namespace commands {
namespace quest {
#include "QuestCreator.h"
#include "BaseCommand.h"
class UnlockTasksOnComplete : public BaseCommand {
public:
{
    public UnlockTasksOnComplete()
    {
    }
    public void init(std::string object, std::string params[])
    {
        if(object == nullptr || !object == "Quest"))
        {
            return;
        } else
        {
            count = Integer.parseInt(params[0].trim());
            return;
        }
    }
    public void begin()
    {
        QuestCreator.SetToUnlockNext(count);
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
    int count;
}
} // namespace
