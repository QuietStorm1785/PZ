#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestAction_StartConversation.java
namespace zombie {
namespace Quests {
namespace questactions {
#include "Talker.h"
// Referenced classes of package zombie.Quests.questactions:
//            QuestAction
class QuestAction_StartConversation {
public:
    implements QuestAction
{
    public QuestAction_StartConversation(std::string conversation, Talker a, Talker b)
    {
        Conversation = conversation;
        A = a;
        B = b;
    }
    public void Execute()
    {
    }
    Talker A;
    Talker B;
    std::string Conversation;
}
} // namespace
