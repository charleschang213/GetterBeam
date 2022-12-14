/*****************************************************************************
* @file     MemoryUtils_Test.cpp
* @author   Yichi Zhang
* @date     2022/10/4
*****************************************************************************/

#include "MemoryUtils.h"
#include <gtest/gtest.h>

TEST(MemoryUtilsTest, ClearAllMemory) {
    GetterBeam::MemoryUtils::ClearAllMemory();
    u16 index = GB_MEMORY_TOTAL_SIZE / 2;
    EXPECT_EQ(0, GetterBeam::MemoryUtils::MemoryModel[index]);
}

TEST(MemoryUtilsTest, SaveMemory) {
    GetterBeam::MemoryUtils::ClearAllMemory();
    u16 index = GB_MEMORY_TOTAL_SIZE / 2;
    u8 value = 0x11;
    GetterBeam::MemoryUtils::SaveMemory(index, value);
    EXPECT_EQ(value, GetterBeam::MemoryUtils::MemoryModel[index]);
}

TEST(MemoryUtilsTest, WriteMemory) {
    GetterBeam::MemoryUtils::ClearAllMemory();
    u16 index1 = 0x4;
    u16 index2 = 0xc;
    u8 value = 0x11;
    GetterBeam::MemoryUtils::SaveMemory(index1, value);
    GetterBeam::MemoryUtils::SaveMemory(index1 + 1, value);
    GetterBeam::MemoryUtils::WriteMemory(index2, index1, 2);
    EXPECT_EQ(value, GetterBeam::MemoryUtils::MemoryModel[index2]);
    EXPECT_EQ(value, GetterBeam::MemoryUtils::MemoryModel[index2 + 1]);
}

TEST(MemoryUtilsTest, ClearMemory) {
    GetterBeam::MemoryUtils::ClearAllMemory();
    u16 index = 0x4;
    u8 value = 0x11;
    GetterBeam::MemoryUtils::SaveMemory(index, value);
    EXPECT_EQ(value, GetterBeam::MemoryUtils::MemoryModel[index]);
    GetterBeam::MemoryUtils::ClearMemory(index, 1);
    EXPECT_EQ(0, GetterBeam::MemoryUtils::MemoryModel[index]);
}

TEST(MemoryUtilsTest, LoadMemory) {
    GetterBeam::MemoryUtils::ClearAllMemory();
    u16 index = 0x4;
    u8 value = 0x11;
    GetterBeam::MemoryUtils::SaveMemory(index, value);
    EXPECT_EQ(value, GetterBeam::MemoryUtils::LoadMemory(index));
}