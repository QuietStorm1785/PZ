#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   PrefaceState.java
namespace zombie {
namespace gameStates {
#include <fstream>
#include <iostream>
#include <algorithm>
#include <algorithm>
#include "GL11.h"
#include "zombie.h"
#include "Color.h"
#include "Core.h"
#include "Texture.h"
#include "Audio.h"
#include "AudioLoader.h"
// Referenced classes of package zombie.gameStates:
//            GameState, GameStateMachine
class PrefaceState : public GameState {
public:
{
    public PrefaceState()
    {
        alpha = 1.0F;
        alphaStep = 0.005F;
        delay = 20;
        leavedelay = 150;
        messageTime = 240F;
        messageTimeMax = 300F;
        stage = 0;
        targetAlpha = 0.0F;
    }
    public void DrawTexture(Texture tex, int x, int y, int width, int height, float alpha)
    {
        int dx = x;
        int dy = y;
        GL11.glColor4f(1.0F, 1.0F, 1.0F, alpha);
        Texture.lr = 1.0F;
        Texture.lg = 1.0F;
        Texture.lb = 1.0F;
        Texture.la = alpha;
        tex.bind();
        IndieGL.Begin();
        GL11.glTexCoord2f(tex.getXStart(), tex.getYStart());
        GL11.glVertex2f(dx, dy);
        GL11.glTexCoord2f(tex.getXEnd(), tex.getYStart());
        GL11.glVertex2f(dx + width, dy);
        GL11.glTexCoord2f(tex.getXEnd(), tex.getYEnd());
        GL11.glVertex2f(dx + width, dy + height);
        GL11.glTexCoord2f(tex.getXStart(), tex.getYEnd());
        GL11.glVertex2f(dx, dy + height);
        IndieGL.End();
    }
    public void DrawTexture(Texture tex, int x, int y, int width, int height, Color col)
    {
        int dx = x;
        int dy = y;
        GL11.glColor4f(col.r, col.g, col.b, col.a);
        tex.bind();
        IndieGL.Begin();
        GL11.glTexCoord2f(tex.getXStart(), tex.getYStart());
        GL11.glVertex2f(dx, dy);
        GL11.glTexCoord2f(tex.getXEnd(), tex.getYStart());
        GL11.glVertex2f(dx + width, dy);
        GL11.glTexCoord2f(tex.getXEnd(), tex.getYEnd());
        GL11.glVertex2f(dx + width, dy + height);
        GL11.glTexCoord2f(tex.getXStart(), tex.getYEnd());
        GL11.glVertex2f(dx, dy + height);
        IndieGL.End();
    }
    public void enter()
    {
        alpha = 0.0F;
        try
        {
            std::string str = "media/music/preface.ogg";
            musicTrack = AudioLoader.getAudio("OGG", str);
        }
        catch(IOException ex)
        {
            Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, ex);
        }
        SoundManager.instance.PlayAsMusic("preface.ogg", musicTrack, 1.0F);
        targetAlpha = 1.0F;
    }
    public void exit()
    {
        SoundManager.instance.BlendVolume(musicTrack, 0.0F);
    }
    public void render()
    {
        if(stage >= 3)
            return;
        if(alpha < targetAlpha)
        {
            alpha += alphaStep;
            if(alpha > targetAlpha)
                alpha = targetAlpha;
        } else
        if(alpha > targetAlpha)
        {
            alpha -= alphaStep;
            if(alpha < targetAlpha)
                alpha = targetAlpha;
        }
        Texture tex = Texture.getSharedTexture("media/ui/IntroText1.png");
        switch(stage)
        {
        case 1: // '\001'
            tex = Texture.getSharedTexture("media/ui/IntroText2.png");
            break;
        case 2: // '\002'
            tex = Texture.getSharedTexture("media/ui/IntroText3.png");
            break;
        }
        int x = Core.getInstance().getOffscreenWidth() / 2;
        x -= tex.getWidth() / 2;
        int y = Core.getInstance().getOffscreenHeight() / 2;
        y -= tex.getHeight() / 2;
        DrawTexture(tex, x, y, tex.getWidth(), tex.getHeight(), new Color(1.0F, 1.0F, 1.0F, alpha));
    }
    public GameStateMachine.StateAction update()
    {
        if(stage < 3)
        {
            if(delay > 0)
                delay--;
            if(alpha < targetAlpha)
            {
                alpha += alphaStep * 8F;
                if(alpha > targetAlpha)
                    alpha = targetAlpha;
            } else
            if(alpha > targetAlpha)
            {
                alpha -= alphaStep / 1.5F;
                if(alpha < targetAlpha)
                    alpha = targetAlpha;
            }
            if(alpha == 1.0F && targetAlpha == 1.0F)
                messageTime--;
            if(alpha == 0.0F && targetAlpha == 0.0F)
            {
                stage++;
                messageTime = messageTimeMax;
                targetAlpha = 1.0F;
                if(stage == 1)
                    messageTime += 40F;
                if(stage == 2)
                    messageTime += 160F;
            }
            if(messageTime <= 0.0F)
                targetAlpha = 0.0F;
        }
        if(stage == 3)
            if(leavedelay > 0)
                leavedelay--;
            else
                return GameStateMachine.StateAction.Continue;
        return GameStateMachine.StateAction.Remain;
    }
    public float alpha;
    public float alphaStep;
    public int delay;
    public int leavedelay;
    public float messageTime;
    public float messageTimeMax;
    public Audio musicTrack;
    public int stage;
    public float targetAlpha;
}
} // namespace
