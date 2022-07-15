#pragma once

//		   _____                                      		//
//		  /     \   ____   _____   ___________ ___.__.		//
//		 /  \ /  \_/ __ \ /     \ /  _ \_  __ <   |  |		//
//		/    Y    \  ___/|  Y Y  (  <_> )  | \/\___  |		//
//		\____|__  /\___  >__|_|  /\____/|__|   / ____|		//
//		        \/     \/      \/              \/     		//

#include <vector>

#include "../vitals/includes.h"

namespace M
{
	// Functions
	// Gets function pattern from address
	uintptr_t GetPattern(const char* chModule, const char* chPattern);
	// Finds memory address
	uintptr_t GetMemoryAddress(uint8_t* uRegionStart, uintptr_t uRegionSize, const char* chPattern);

	// Translates memory patterns to bytes used for finding function adresses
	std::vector<int> PatternToBytes(const char* chPattern);

	// Store VFunctions
	inline void* GetVirtualFunction(void* pClass, int iIndex)
	{
		return (*static_cast<void***>(pClass))[iIndex];
	}
}