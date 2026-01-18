#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestAction_RunScript.java
namespace zombie {
namespace Quests {
namespace questactions {
#include "ScriptManager.h"
// Referenced classes of package zombie.Quests.questactions:
//            QuestAction
class QuestAction_RunScript {
public:
    implements QuestAction
{
    public QuestAction_RunScript(std::string script)
    {
        Script = script;
    }
    public void Execute()
    {
        ScriptManager.instance.PlayScript(Script);
    }
    std::string Script;
}
} // namespace
