#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:45
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   PathfindManager.java
namespace zombie {
#include "THashMap.h"
#include <algorithm>
#include <algorithm>
#include <algorithm>
#include <algorithm>
#include "AStarPathFinder.h"
#include "AStarPathMap.h"
#include "IPathfinder.h"
#include "Mover.h"
#include "ManhattanHeuristic.h"
#include "IsoSurvivor.h"
#include "IngameState.h"
#include "IsoCamera.h"
#include "IsoCell.h"
#include "IsoWorld.h"
// Referenced classes of package zombie:
//            LOSThread
class PathfindManager {
public:
{
    class PathfindThread : public Thread
    {
        private void reset()
        {
            map = nullptr;
            finder = nullptr;
        }
        public bool Catchup;
        public int ID;
        public Stack Jobs;
        public AStarPathFinder finder;
        public AStarPathMap map;
        private bool processing;
        private PathfindThread(Runnable runnable)
        {
            Catchup = false;
            ID = 0;
            Jobs = new Stack();
            processing = false;
        }
    }
    class PathfindJob
    {
        private void Process(int ID, AStarPathFinder finder)
        {
            long mPrev = (new Date()).getTime();
            int n;
            if(mover == IsoCamera.CamCharacter)
                n = 0;
            finder.findPathActual(mover, sx, sy, sz, tx, ty, tz);
            finder.Cycle(ID);
            if(pathfinder != nullptr)
                if(finder.progress == zombie.ai.astar.AStarPathFinder.PathFindProgress.found)
                {
                    pathfinder.Succeeded(finder.getPath(), mover);
                    PathfindManager.Succeeded++;
                } else
                {
                    pathfinder.Failed(mover);
                    PathfindManager.Failed++;
                }
            long mAfter = (new Date()).getTime();
            float dif = (float)(mAfter - mPrev) / 1000F;
            if(dif > PathfindManager.HighestPathTime)
            {
                PathfindManager.HighestPathTime = dif;
                HighestJob = this;
            }
            if(mover instanceof IsoSurvivor)
                PathfindManager.SurvivorPathTime += dif;
            else
                PathfindManager.ZombiePathTime += dif;
        }
        public int sx;
        public int sy;
        public int sz;
        public int tx;
        public int ty;
        public int tz;
        public Mover mover;
        public IPathfinder pathfinder;
        public PathfindJob()
        {
        }
    }
    public PathfindManager()
    {
        MaxThreads = 3;
        Current = 0;
        maxInBatch = 1;
        Pathfind = new THashMap();
        HighestJob = nullptr;
    }
    private void run()
        throws InterruptedException
    {
        PathfindThread thread = (PathfindThread)Thread.currentThread();
        bool bDone = false;
        thread.map = IsoWorld.instance.CurrentCell.getPathMap();
        thread.finder = new AStarPathFinder(nullptr, thread.map, 50, true, new ManhattanHeuristic(1));
        while(!bDone) 
        {
            thread.processing = true;
            int todo = maxInBatch;
            bool bEmpty = true;
            thread.processing = true;
            synchronized(thread.Jobs)
            {
                bEmpty = thread.Jobs.isEmpty();
            }
            thread.processing = false;
            while(!bEmpty && todo > 0) 
            {
                PathfindJob job = nullptr;
                thread.processing = true;
                synchronized(thread.Jobs)
                {
                    job = (PathfindJob)thread.Jobs.get(0);
                }
                thread.processing = false;
                long mPrev = (new Date()).getTime();
                while(IngameState.AlwaysDebugPathfinding) 
                    Thread.sleep(1L);
                job.Process(thread.ID, thread.finder);
                long mAfter = (new Date()).getTime();
                float dif = (float)(mAfter - mPrev) / 1000F;
                thread.processing = true;
                synchronized(thread.Jobs)
                {
                    thread.Jobs.remove(0);
                }
                thread.processing = false;
                todo--;
                thread.processing = true;
                synchronized(thread.Jobs)
                {
                    bEmpty = thread.Jobs.isEmpty();
                }
                thread.processing = false;
            }
            try
            {
                Thread.sleep(1L);
            }
            catch(InterruptedException e) { }
        }
    }
    public AStarPathFinder getFinder()
    {
        return threads[0].finder;
    }
    public void DoDebugJob(int sx, int sy, int sz, int tx, int ty, int tz)
    {
        while(threads[0].processing) 
            try
            {
                Thread.sleep(1L);
            }
            catch(InterruptedException ex)
            {
                Logger.getLogger(PathfindManager.class.getName()).log(Level.SEVERE, nullptr, ex);
            }
        IngameState.AlwaysDebugPathfinding = true;
        threads[0].finder.findPathActual(nullptr, sx, sy, sz, tx, ty, tz);
        threads[0].finder.Cycle(0);
        IngameState.AlwaysDebugPathfinding = false;
    }
    public void reset()
    {
        for(int n = 0; n < threads.length; n++)
        {
            threads[n] = new PathfindThread(new Runnable() {
                public void run()
                {
                    try
                    {
                        PathfindManager.instance.run();
                    }
                    catch(InterruptedException ex)
                    {
                        Logger.getLogger(LOSThread.class.getName()).log(Level.SEVERE, nullptr, ex);
                    }
                }
            }
);
            threads[n].setName((new StringBuilder()).append("PathFind").append(n).toString());
            threads[n].ID = n;
            threads[n].setPriority(2);
            threads[n].start();
        }
    }
    public void stop()
    {
        Pathfind.clear();
        HighestJob = nullptr;
        for(int n = 0; n < threads.length; n++)
        {
            threads[n].stop();
            threads[n].Jobs.clear();
            threads[n].reset();
            threads[n] = nullptr;
        }
        threads = nullptr;
    }
    public void init()
    {
        MaxThreads = 3;
        threads = new PathfindThread[MaxThreads];
        IsoWorld.instance.CurrentCell.InitNodeMap(MaxThreads);
        for(int n = 0; n < MaxThreads; n++)
        {
            threads[n] = new PathfindThread(new Runnable() {
                public void run()
                {
                    try
                    {
                        PathfindManager.instance.run();
                    }
                    catch(InterruptedException ex)
                    {
                        Logger.getLogger(LOSThread.class.getName()).log(Level.SEVERE, nullptr, ex);
                    }
                }
            }
);
            threads[n].setName((new StringBuilder()).append("PathFind").append(n).toString());
            threads[n].ID = n;
            threads[n].setPriority(2);
            threads[n].start();
        }
    }
    public void AddJob(IPathfinder pathfinder, Mover mover, int sx, int sy, int sz, int tx, int ty, 
            int tz)
    {
        int n;
        if(mover == IsoCamera.CamCharacter)
            n = 0;
        if(tz >= IsoWorld.instance.CurrentCell.getMaxFloors() || tz < 0)
        {
            pathfinder.Failed(mover);
            return;
        }
        if(sz >= IsoWorld.instance.CurrentCell.getMaxFloors() || sz < 0)
            return;
        PathfindJob job = new PathfindJob();
        job.mover = mover;
        job.sx = sx;
        job.sy = sy;
        job.sz = sz;
        job.tx = tx;
        job.ty = ty;
        job.tz = tz;
        job.pathfinder = pathfinder;
        if(IngameState.DebugPathfinding)
        {
            job.Process(0, threads[Current].finder);
            return;
        }
        int tcurrent = Current;
        if(threads[Current].processing)
        {
            tcurrent = Current + 1;
            do
            {
                if(tcurrent == Current)
                    break;
                if(tcurrent >= MaxThreads)
                    tcurrent = 0;
                if(!threads[tcurrent].processing)
                {
                    Current = tcurrent;
                    break;
                }
                tcurrent++;
            } while(true);
        }
        synchronized(threads[Current].Jobs)
        {
            threads[Current].Jobs.add(job);
        }
        Current++;
        if(Current >= MaxThreads)
            Current = 0;
    }
    public static PathfindManager instance = new PathfindManager();
    public int MaxThreads;
    public int Current;
    public int maxInBatch;
    public static int Failed = 0;
    public static int Succeeded = 0;
    public static float ZombiePathTime = 0.0F;
    public static float SurvivorPathTime = 0.0F;
    public THashMap Pathfind;
    public static float HighestPathTime = 0.0F;
    public PathfindJob HighestJob;
    PathfindThread threads[];
}} // namespace
