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
        }

        void ClearMemory(size_t index, size_t len) {
            if (index < 0 || index + len >= GB_MEMORY_TOTAL_SIZE) {
                return;
            }
            memset(MemoryModel + index, 0, len);
        }

        void WriteMemory(size_t dst, size_t src, size_t len) {
            if (src < 0 || src + len >= GB_MEMORY_TOTAL_SIZE) {
                return;
            }
            if (dst < 0 || dst + len >= GB_MEMORY_TOTAL_SIZE) {
                return;
            }
            if (src == dst) {
                return;
            }
            memmove(MemoryModel + dst, MemoryModel + src, len);
        }

        u8 *LoadMemory(size_t index) {
            if (index < 0 || index >= GB_MEMORY_TOTAL_SIZE) {
                return nullptr;
            }
            return MemoryModel + index;
        }

        void SaveMemory(size_t index, u8 value) {
            if (index < 0 || index >= GB_MEMORY_TOTAL_SIZE) {
                return;
            }
            MemoryModel[index] = value;
        }
    }// namespace MemoryUtils
}// namespace GetterBeam