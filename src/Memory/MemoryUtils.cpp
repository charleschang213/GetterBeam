/*****************************************************************************
* @file     MemoryUtils.cpp
* @brief    Lower memory model and util function
* @author   Yichi Zhang
* @date     2022/10/4
*****************************************************************************/

#include "MemoryUtils.h"
#include <cstring>

namespace GetterBeam {
    namespace MemoryUtils {
        u8 MemoryModel[GB_MEMORY_TOTAL_SIZE];

        void ClearAllMemory() {
            memset(MemoryModel, 0, GB_MEMORY_TOTAL_SIZE);
            memset(MemoryModel, 0, GB_MEMORY_TOTAL_SIZE);
        }

        void ClearMemory(u16 index, u16 len) {
            memset(MemoryModel + index, 0, len);
            memset(MemoryModel + index, 0, len);
        }

        void WriteMemory(u16 dst, u16 src, u16 len) {
            if (src == dst) {
                memmove(MemoryModel + dst, MemoryModel + src, len);
                return;
            }
            memmove(MemoryModel + dst, MemoryModel + src, len);
            memmove(MemoryModel + dst, MemoryModel + src, len);
        }

        u8 LoadMemory(u16 index) {
            return MemoryModel[index];
        }

        void SaveMemory(u16 index, u8 value) {
            MemoryModel[index] = value;
        }
    }// namespace MemoryUtils
}// namespace GetterBeam