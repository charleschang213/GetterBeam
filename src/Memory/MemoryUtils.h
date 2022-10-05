/*****************************************************************************
* @file     MemoryUtils.h
* @brief    Lower memory model and util function
* @author   Yichi Zhang
* @date     2022/10/4
*****************************************************************************/

#ifndef GETTERBEAM_MEMORYUTILS_H
#define GETTERBEAM_MEMORYUTILS_H
#include "GBTypedef.h"

#define GB_MEMORY_TOTAL_SIZE (1024 * 64)

namespace GetterBeam {
    namespace MemoryUtils {
        /** CPU Memory Modeled by u8 array */
        extern u8 MemoryModel[GB_MEMORY_TOTAL_SIZE];

        /**
         * Clear all memories, set all block to 0
         */
        void ClearAllMemory();

        /**
         * Clear a piece of memory and set to 0
         * do nothing when there's range conflicts
         * @param index starting index
         * @param len length
         */
        void ClearMemory(size_t index, size_t len);

        /**
         * Copy piece of memory
         * do nothing when there's range conflicts
         * @param dst destination
         * @param src source
         * @param len data length
         */
        void WriteMemory(size_t dst, size_t src, size_t len);

        /**
         * Get the data from a data block
         * @param index data block index
         * @return the data pointer, return nullptr when out of range
         */
        u8 *LoadMemory(size_t index);

        /**
         * Save Data to a data block
         * @param index data block index
         * @param value data value to save
         */
        void SaveMemory(size_t index, u8 value);
    }// namespace MemoryUtils
}// namespace GetterBeam

#endif//GETTERBEAM_MEMORYUTILS_H
