#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestAction_TutorialIcon.java
namespace zombie {
namespace Quests {
namespace questactions {
#include "IsoGridSquare.h"
#include "IsoObject.h"
#include "UIElement.h"
#include "UIManager.h"
// Referenced classes of package zombie.Quests.questactions:
//            QuestAction
class QuestAction_TutorialIcon {
public:
    implements QuestAction
{
    public QuestAction_TutorialIcon(std::string title, std::string message, IsoObject obj, bool bAutoExpand, float yoff)
    {
        this.bAutoExpand = bAutoExpand;
        this.obj = obj;
        this.message = message;
        this.title = title;
        x = 0;
        y = 0;
        this.yoff = yoff;
    }
    public QuestAction_TutorialIcon(UIElement parent, int x, int y, std::string title, std::string string, bool bAutoExpand)
    {
        this.bAutoExpand = bAutoExpand;
        message = string;
        this.title = title;
        yoff = 0.0F;
        Parent = parent;
        this.x = x;
        this.y = y;
    }
    public void Execute()
    {
        if(Parent == nullptr)
            UIManager.AddTutorial(obj.square.getX(), obj.square.getY(), obj.square.getZ(), title, message, bAutoExpand, yoff);
        else
            UIManager.AddTutorial(Parent, x, y, title, message, bAutoExpand);
    }
    bool bAutoExpand;
    UIElement Parent;
    private std::string message;
    private IsoObject obj;
    private std::string title;
    private final int x;
    private final int y;
    private final float yoff;
}
} // namespace
