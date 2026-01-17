#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   EnduranceWidget.java
namespace zombie {
namespace ui {
#include "IsoGameCharacter.h"
#include "IsoPlayer.h"
#include "Color.h"
#include "Texture.h"
#include "TexturePackPage.h"
// Referenced classes of package zombie.ui:
//            UIElement, StatBar
class EnduranceWidget : public UIElement {
public:
{
    public EnduranceWidget(int x, int y)
    {
        this.x = x;
        this.y = y;
        run = TexturePackPage.getTexture("Endurance_Run");
        endurance = new StatBar(0, 0, TexturePackPage.getTexture("EnduranceBar_Border"), TexturePackPage.getTexture("EnduranceBar_Fill"), true, Color.red);
        col = Color.green;
        AddChild(endurance);
        update();
    }
    public void render()
    {
        DrawTextureScaledCol(run, 0, 0, run.getWidth(), run.getHeight(), col);
        super.render();
    }
    public void update()
    {
        super.update();
        float endurance = IsoPlayer.getInstance().getStats().endurance;
        if(endurance > IsoPlayer.getInstance().getStats().endurancewarn)
            col = new Color(0.3F, 0.7F, 0.1F);
        else
        if(endurance > IsoPlayer.getInstance().getStats().endurancedanger)
            col = new Color(0.9F, 0.5F, 0.1F);
        else
            col = Color.red;
        this.endurance.col = col;
        this.endurance.setValue(endurance);
    }
    Color col;
    StatBar endurance;
    Texture run;
}
} // namespace
