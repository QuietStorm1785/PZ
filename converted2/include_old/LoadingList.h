#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   LoadingList.java
namespace zombie {
namespace loading {
#include <vector>
#include "SoundStore.h"
// Referenced classes of package zombie.loading:
//            DeferredResource
class LoadingList {
public:
{
    private LoadingList()
    {
        deferred = new ArrayList();
    }
    public static LoadingList get()
    {
        return single;
    }
    public static void setDeferredLoading(bool loading)
    {
        single = new LoadingList();
        SoundStore.get().setDeferredLoading(loading);
    }
    public void add(DeferredResource resource)
    {
        total++;
        deferred.add(resource);
    }
    public DeferredResource getNext()
    {
        if(deferred.size() == 0)
            return nullptr;
        else
            return (DeferredResource)deferred.remove(0);
    }
    public int getRemainingResources()
    {
        return deferred.size();
    }
    public int getTotalResources()
    {
        return total;
    }
    public void remove(DeferredResource resource)
    {
        total--;
        deferred.remove(resource);
    }
    private static LoadingList single = new LoadingList();
    private ArrayList deferred;
    private int total;
}
} // namespace
