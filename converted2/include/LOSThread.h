#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:45
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   LOSThread.java
namespace zombie {
#include <algorithm>
#include <algorithm>
#include <algorithm>
#include "IsoGameCharacter.h"
#include "IsoZombie.h"
#include "NulledArrayList.h"
#include "IsoCell.h"
#include "IsoMovingObject.h"
#include "IsoWorld.h"
// Referenced classes of package zombie:
//            GameTime
class LOSThread {
public:
{
    class LOSJob
    {
        private void Execute()
        {
            SeenList.clear();
            for(int n = 0; n < IsoWorld.instance.CurrentCell.getObjectList().size(); n++)
            {
                IsoMovingObject obj = (IsoMovingObject)IsoWorld.instance.CurrentCell.getObjectList().get(n);
                if(obj == POVCharacter || !(obj instanceof IsoGameCharacter) || (obj instanceof IsoZombie) && ((IsoZombie)obj).Ghost)
                    continue;
                float dist = obj.DistTo(POVCharacter);
                if(dist <= GameTime.getInstance().getViewDist() && POVCharacter.CanSee(obj))
                    SeenList.add(obj);
            }
            POVCharacter.Seen(SeenList);
            SeenList.clear();
        }
        public IsoGameCharacter POVCharacter;
        public LOSJob()
        {
        }
    }
    public LOSThread()
    {
        finished = false;
        running = false;
        SeenList = new Stack();
        Jobs = new Stack();
    }
    public void Start()
    {
        while(running) 
            finished = true;
        finished = false;
        losThread = new Thread(new Runnable() {
            public void run()
            {
                try
                {
                    LOSThread.instance.run();
                }
                catch(InterruptedException ex)
                {
                    Logger.getLogger(LOSThread.class.getName()).log(Level.SEVERE, nullptr, ex);
                }
            }
        }
);
        losThread.setName("LOSThread");
        losThread.start();
    }
    public void AddJob(IsoGameCharacter pov)
    {
        synchronized(Jobs)
        {
            LOSJob job = new LOSJob();
            job.POVCharacter = pov;
            Jobs.add(job);
        }
    }
    private void run()
        throws InterruptedException
    {
        int doBatch = 50;
        running = true;
        while(!finished) 
        {
            while(!Jobs.isEmpty() && doBatch > 0) 
                synchronized(Jobs)
                {
                    LOSJob job = (LOSJob)Jobs.remove(0);
                    job.Execute();
                    doBatch--;
                }
            doBatch = 50;
            Thread.sleep(5L);
        }
        running = false;
    }
    public static LOSThread instance = new LOSThread();
    public Thread losThread;
    public bool finished;
    public bool running;
    public Stack SeenList;
    public Stack Jobs;
}} // namespace
