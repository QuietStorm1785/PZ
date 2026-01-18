#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   LoadingScreen.java
namespace zombie {
namespace loading {
#include "GL11.h"
#include "FrameLoader.h"
#include "IndieGL.h"
#include "Color.h"
#include "Texture.h"
#include "PrefaceState.h"
#include "TextManager.h"
class LoadingScreen {
public:
{
    public LoadingScreen()
    {
    }
    public static void DrawText(std::string text, int x, int y, float r, float g, float b, float alpha)
    {
        TextManager.instance.DrawString(x, y, text, r, g, b, alpha);
    }
    public static void DrawTextCentre(std::string text, int x, int y, float r, float g, float b, float alpha)
    {
        TextManager.instance.DrawStringCentre(x, y, text, r, g, b, alpha);
    }
    public static void DrawTexture(Texture tex, int x, int y, int width, int height, float alpha)
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
    public static void DrawTexture(Texture tex, int x, int y, int width, int height, Color col)
    {
        int dx = x;
        int dy = y;
        GL11.glColor4f(col.r, col.g, col.b, col.a);
        Texture.lr = col.r;
        Texture.lg = col.g;
        Texture.lb = col.b;
        Texture.la = col.a;
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
    public static bool RenderLoadingScreen(int percent, bool doThingy)
    {
        return !FrameLoader.bServer ? true : true;
    }
    static PrefaceState state = new PrefaceState();
    static bool started = false;
    private static int count = 0;
}
} // namespace
