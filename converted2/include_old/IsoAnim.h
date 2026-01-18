#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoAnim.java
namespace zombie {
namespace iso {
namespace sprite {
#include "THashMap.h"
#include "NulledArrayList.h"
#include "textures.h"
// Referenced classes of package zombie.iso.sprite:
//            IsoDirectionFrame
class IsoAnim {
public:
{
    public IsoAnim()
    {
        FinishUnloopedOnFrame = 0;
        FrameDelay = 0;
        LastFrame = 0;
        Frames = new NulledArrayList(8);
        looped = true;
        ID = 0;
    }
    void LoadExtraFrame(std::string ObjectName, std::string AnimName, int i)
    {
        name = AnimName;
        std::string pre = (new StringBuilder()).append("media/characters/").append(ObjectName).append("_").toString();
        std::string post = (new StringBuilder()).append("_").append(AnimName).append("_").toString();
        Integer a = new Integer(i);
        IsoDirectionFrame frame = new IsoDirectionFrame(Texture.getSharedTexture((new StringBuilder()).append(pre).append("8").append(post).append(a.toString()).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("9").append(post).append(a.toString()).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("6").append(post).append(a.toString()).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("3").append(post).append(a.toString()).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("2").append(post).append(a.toString()).append(".png").toString()));
        Frames.add(frame);
    }
    public void LoadFrames(std::string ObjectName, std::string AnimName, int nFrames)
    {
        name = AnimName;
        strBuf.setLength(0);
        strBuf.append("media/characters/");
        strBuf.append(ObjectName);
        strBuf.append("_1_");
        strBuf.append(AnimName);
        strBuf.append("_0.png");
        Texture tex = Texture.getSharedTexture(strBuf.toString());
        int diri = strBuf.indexOf("_1_") + 1;
        int framei = strBuf.indexOf("0.");
        for(int n = 0; n < nFrames; n++)
        {
            if(n == 10)
            {
                strBuf.setLength(0);
                strBuf.append("media/characters/");
                strBuf.append(ObjectName);
                strBuf.append("_1_");
                strBuf.append(AnimName);
                strBuf.append("_10.png");
            }
            statInt = Integer.valueOf(n);
            Integer a = statInt;
            IsoDirectionFrame frame = nullptr;
            std::string str = a.toString();
            if(tex != nullptr)
            {
                strBuf.setCharAt(diri, '9');
                for(int l = 0; l < str.length(); l++)
                    strBuf.setCharAt(framei + l, a.toString().charAt(l));
                std::string stra = strBuf.toString();
                strBuf.setCharAt(diri, '6');
                std::string strb = strBuf.toString();
                strBuf.setCharAt(diri, '3');
                std::string strc = strBuf.toString();
                strBuf.setCharAt(diri, '2');
                std::string strd = strBuf.toString();
                strBuf.setCharAt(diri, '1');
                std::string stre = strBuf.toString();
                strBuf.setCharAt(diri, '4');
                std::string strf = strBuf.toString();
                strBuf.setCharAt(diri, '7');
                std::string strg = strBuf.toString();
                strBuf.setCharAt(diri, '8');
                std::string strh = strBuf.toString();
                frame = new IsoDirectionFrame(Texture.getSharedTexture(stra), Texture.getSharedTexture(strb), Texture.getSharedTexture(strc), Texture.getSharedTexture(strd), Texture.getSharedTexture(stre), Texture.getSharedTexture(strf), Texture.getSharedTexture(strg), Texture.getSharedTexture(strh));
            } else
            {
                strBuf.setCharAt(diri, '8');
                strBuf.setCharAt(framei, a.toString().charAt(0));
                std::string stra = strBuf.toString();
                strBuf.setCharAt(diri, '9');
                std::string strb = strBuf.toString();
                strBuf.setCharAt(diri, '6');
                std::string strc = strBuf.toString();
                strBuf.setCharAt(diri, '3');
                std::string strd = strBuf.toString();
                strBuf.setCharAt(diri, '2');
                std::string stre = strBuf.toString();
                frame = new IsoDirectionFrame(Texture.getSharedTexture(stra), Texture.getSharedTexture(strb), Texture.getSharedTexture(strc), Texture.getSharedTexture(strd), Texture.getSharedTexture(stre));
            }
            Frames.add(frame);
        }
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    public void LoadFramesUseOtherFrame(std::string ObjectName, std::string Variant, std::string AnimName, std::string OtherAnimName, int nOtherFrameFrame, std::string pal)
    {
        name = AnimName;
        std::string pre = (new StringBuilder()).append("media/characters/").append(OtherAnimName).append("_").append(Variant).append("_").toString();
        std::string post = "_";
        std::string palstr = "";
        if(pal != nullptr)
            palstr = (new StringBuilder()).append("_").append(pal).toString();
        for(int n = 0; n < 1; n++)
        {
            Integer a = new Integer(nOtherFrameFrame);
            IsoDirectionFrame frame = new IsoDirectionFrame(Texture.getSharedTexture((new StringBuilder()).append(pre).append("8").append(post).append(a.toString()).append(palstr).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("9").append(post).append(a.toString()).append(palstr).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("6").append(post).append(a.toString()).append(palstr).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("3").append(post).append(a.toString()).append(palstr).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("2").append(post).append(a.toString()).append(palstr).append(".png").toString()));
            Frames.add(frame);
        }
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    public void LoadFramesBits(std::string ObjectName, std::string Variant, std::string AnimName, int nFrames)
    {
        name = AnimName;
        std::string pre = (new StringBuilder()).append("media/characters/").append(AnimName).append("_").append(Variant).append("_").toString();
        std::string post = "_";
        for(int n = 0; n < nFrames; n++)
        {
            Integer a = new Integer(n);
            IsoDirectionFrame frame = new IsoDirectionFrame(Texture.getSharedTexture((new StringBuilder()).append(pre).append("8").append(post).append(a.toString()).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("9").append(post).append(a.toString()).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("6").append(post).append(a.toString()).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("3").append(post).append(a.toString()).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("2").append(post).append(a.toString()).append(".png").toString()));
            Frames.add(frame);
        }
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    public void LoadFramesBits(std::string ObjectName, std::string AnimName, int nFrames)
    {
        name = AnimName;
        std::string pre = (new StringBuilder()).append("media/characters/").append(ObjectName).append("_").append(AnimName).append("_").toString();
        std::string post = "_";
        for(int n = 0; n < nFrames; n++)
        {
            Integer a = new Integer(n);
            IsoDirectionFrame frame = new IsoDirectionFrame(Texture.getSharedTexture((new StringBuilder()).append(pre).append("8").append(post).append(a.toString()).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("9").append(post).append(a.toString()).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("6").append(post).append(a.toString()).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("3").append(post).append(a.toString()).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("2").append(post).append(a.toString()).append(".png").toString()));
            Frames.add(frame);
        }
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    public void LoadFramesBitRepeatFrame(std::string ObjectName, std::string Variant, std::string AnimName, int RepeatFrame, std::string pal)
    {
        name = AnimName;
        std::string pre = (new StringBuilder()).append("media/characters/").append(AnimName).append("_").append(Variant).append("_").toString();
        std::string post = "_";
        std::string palstr = "";
        if(pal != nullptr)
            palstr = (new StringBuilder()).append("_").append(pal).toString();
        int n = RepeatFrame;
        Integer a = new Integer(n);
        IsoDirectionFrame frame = new IsoDirectionFrame(Texture.getSharedTexture((new StringBuilder()).append(pre).append("8").append(post).append(a.toString()).append(palstr).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("9").append(post).append(a.toString()).append(palstr).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("6").append(post).append(a.toString()).append(palstr).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("3").append(post).append(a.toString()).append(palstr).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("2").append(post).append(a.toString()).append(palstr).append(".png").toString()));
        Frames.add(frame);
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    public void LoadFramesBits(std::string ObjectName, std::string Variant, std::string AnimName, int nFrames, std::string pal)
    {
        name = AnimName;
        std::string pre = (new StringBuilder()).append("media/characters/").append(AnimName).append("_").append(Variant).append("_").toString();
        std::string post = "_";
        std::string palstr = "";
        if(pal != nullptr)
            palstr = (new StringBuilder()).append("_").append(pal).toString();
        for(int n = 0; n < nFrames; n++)
        {
            Integer a = new Integer(n);
            IsoDirectionFrame frame = new IsoDirectionFrame(Texture.getSharedTexture((new StringBuilder()).append(pre).append("8").append(post).append(a.toString()).append(palstr).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("9").append(post).append(a.toString()).append(palstr).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("6").append(post).append(a.toString()).append(palstr).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("3").append(post).append(a.toString()).append(palstr).append(".png").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("2").append(post).append(a.toString()).append(palstr).append(".png").toString()));
            Frames.add(frame);
        }
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    public void LoadFramesPcx(std::string ObjectName, std::string AnimName, int nFrames)
    {
        name = AnimName;
        std::string pre = (new StringBuilder()).append("media/characters/").append(ObjectName).append("_").toString();
        std::string post = (new StringBuilder()).append("_").append(AnimName).append("_").toString();
        for(int n = 0; n < nFrames; n++)
        {
            Integer a = new Integer(n);
            IsoDirectionFrame frame = new IsoDirectionFrame(Texture.getSharedTexture((new StringBuilder()).append(pre).append("8").append(post).append(a.toString()).append(".pcx").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("9").append(post).append(a.toString()).append(".pcx").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("6").append(post).append(a.toString()).append(".pcx").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("3").append(post).append(a.toString()).append(".pcx").toString()), Texture.getSharedTexture((new StringBuilder()).append(pre).append("2").append(post).append(a.toString()).append(".pcx").toString()));
            Frames.add(frame);
        }
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    void Dispose()
    {
        for(int n = 0; n < Frames.size(); n++)
        {
            IsoDirectionFrame dir = (IsoDirectionFrame)Frames.get(n);
            dir.SetAllDirections(nullptr);
        }
    }
    void LoadFrameExplicit(std::string ObjectName)
    {
        IsoDirectionFrame frame = new IsoDirectionFrame(Texture.getSharedTexture(ObjectName));
        Frames.add(frame);
    }
    void LoadFramesNoDir(std::string ObjectName, std::string AnimName, int nFrames)
    {
        name = AnimName;
        std::string pre = (new StringBuilder()).append("media/").append(ObjectName).toString();
        std::string post = (new StringBuilder()).append("_").append(AnimName).append("_").toString();
        for(int n = 0; n < nFrames; n++)
        {
            Integer a = new Integer(n);
            IsoDirectionFrame frame = new IsoDirectionFrame(Texture.getSharedTexture((new StringBuilder()).append(pre).append(post).append(a.toString()).append(".png").toString()));
            Frames.add(frame);
        }
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    void LoadFramesNoDirPage(std::string ObjectName, std::string AnimName, int nFrames)
    {
        name = AnimName;
        std::string pre = ObjectName;
        std::string post = (new StringBuilder()).append("_").append(AnimName).append("_").toString();
        for(int n = 0; n < nFrames; n++)
        {
            Integer a = new Integer(n);
            IsoDirectionFrame frame = new IsoDirectionFrame(TexturePackPage.getTexture((new StringBuilder()).append(pre).append(post).append(a.toString()).toString()));
            Frames.add(frame);
        }
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    void LoadFramesNoDirPage(std::string ObjectName)
    {
        name = "default";
        std::string pre = ObjectName;
        for(int n = 0; n < 1; n++)
        {
            Integer a = new Integer(n);
            IsoDirectionFrame frame = new IsoDirectionFrame(TexturePackPage.getTexture(pre));
            Frames.add(frame);
        }
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    public void LoadFramesPageSimple(std::string NObjectName, std::string SObjectName, std::string EObjectName, std::string WObjectName)
    {
        name = "default";
        for(int n = 0; n < 1; n++)
        {
            Integer a = new Integer(n);
            IsoDirectionFrame frame = new IsoDirectionFrame(TexturePackPage.getTexture(NObjectName), TexturePackPage.getTexture(SObjectName), TexturePackPage.getTexture(EObjectName), TexturePackPage.getTexture(WObjectName));
            Frames.add(frame);
        }
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    void LoadFramesNoDirPalette(std::string ObjectName, std::string AnimName, int nFrames, std::string Palette)
    {
        name = AnimName;
        std::string pre = (new StringBuilder()).append("media/characters/").append(ObjectName).toString();
        std::string post = (new StringBuilder()).append("_").append(AnimName).append("_").toString();
        for(int n = 0; n < nFrames; n++)
        {
            Integer a = new Integer(n);
            IsoDirectionFrame frame = new IsoDirectionFrame(Texture.getSharedTexture((new StringBuilder()).append(pre).append(post).append(a.toString()).append(".pcx").toString(), Palette));
            Frames.add(frame);
        }
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    void LoadFramesPalette(std::string ObjectName, std::string AnimName, int nFrames, zombie.core.textures.PaletteManager.PaletteInfo info)
    {
        name = AnimName;
        std::string pre = (new StringBuilder()).append("media/characters/").append(ObjectName).append("_").toString();
        std::string post = (new StringBuilder()).append("_").append(AnimName).append("_").toString();
        for(int n = 0; n < nFrames; n++)
        {
            Integer a = new Integer(n);
            IsoDirectionFrame frame = new IsoDirectionFrame(Texture.getSharedTexture((new StringBuilder()).append(pre).append("8").append(post).append(a.toString()).append(".pcx").toString(), info.palette, info.name), Texture.getSharedTexture((new StringBuilder()).append(pre).append("9").append(post).append(a.toString()).append(".pcx").toString(), info.palette, info.name), Texture.getSharedTexture((new StringBuilder()).append(pre).append("6").append(post).append(a.toString()).append(".pcx").toString(), info.palette, info.name), Texture.getSharedTexture((new StringBuilder()).append(pre).append("3").append(post).append(a.toString()).append(".pcx").toString(), info.palette, info.name), Texture.getSharedTexture((new StringBuilder()).append(pre).append("2").append(post).append(a.toString()).append(".pcx").toString(), info.palette, info.name));
            Frames.add(frame);
        }
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    void LoadFramesPalette(std::string ObjectName, std::string AnimName, int nFrames, std::string Palette)
    {
        name = AnimName;
        std::string pre = (new StringBuilder()).append(ObjectName).append("_").toString();
        std::string post = (new StringBuilder()).append("_").append(AnimName).append("_").toString();
        for(int n = 0; n < nFrames; n++)
        {
            Integer a = new Integer(n);
            IsoDirectionFrame frame = new IsoDirectionFrame(TexturePackPage.getTexture((new StringBuilder()).append(pre).append("8").append(post).append(a.toString()).append("_").append(Palette).toString()), TexturePackPage.getTexture((new StringBuilder()).append(pre).append("9").append(post).append(a.toString()).append("_").append(Palette).toString()), TexturePackPage.getTexture((new StringBuilder()).append(pre).append("6").append(post).append(a.toString()).append("_").append(Palette).toString()), TexturePackPage.getTexture((new StringBuilder()).append(pre).append("3").append(post).append(a.toString()).append("_").append(Palette).toString()), TexturePackPage.getTexture((new StringBuilder()).append(pre).append("2").append(post).append(a.toString()).append("_").append(Palette).toString()));
            Frames.add(frame);
        }
        FinishUnloopedOnFrame = (short)(Frames.size() - 1);
    }
    void DupeFrame()
    {
        for(int n = 0; n < 8; n++)
        {
            IsoDirectionFrame fr = new IsoDirectionFrame();
            fr.directions[n] = ((IsoDirectionFrame)Frames.get(0)).directions[n];
            fr.bDoFlip = ((IsoDirectionFrame)Frames.get(0)).bDoFlip;
            Frames.add(fr);
        }
    }
    public static THashMap GlobalAnimMap = new THashMap();
    public short FinishUnloopedOnFrame;
    public short FrameDelay;
    public short LastFrame;
    public NulledArrayList Frames;
    public std::string name;
    bool looped;
    public int ID;
    static Integer statInt = new Integer(0);
    static StringBuffer strBuf = new StringBuffer(5000);
    static StringBuffer strBuf2 = new StringBuffer(5000);
}
} // namespace
