#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   BucketManager.java
namespace zombie {
namespace core {
namespace bucket {
#include "THashMap.h"
// Referenced classes of package zombie.core.bucket:
//            Bucket
class BucketManager {
public:
{
    public BucketManager()
    {
    }
    public static void ActivateBucket(std::string s)
    {
    }
    public static Bucket Active()
    {
        return SharedBucket;
    }
    public static void AddBucket(std::string name, Bucket bucket)
    {
        bucket.setName(name);
    }
    public static void DisposeBucket(std::string s)
    {
    }
    public static Bucket Shared()
    {
        return SharedBucket;
    }
    static THashMap BucketMap = new THashMap();
    static Bucket ActiveBucket = nullptr;
    static Bucket SharedBucket = new Bucket();
}
} // namespace
