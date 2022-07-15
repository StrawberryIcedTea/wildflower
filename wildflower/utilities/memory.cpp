#include "memory.h"

//		   _____                                      		//
//		  /     \   ____   _____   ___________ ___.__.		//
//		 /  \ /  \_/ __ \ /     \ /  _ \_  __ <   |  |		//
//		/    Y    \  ___/|  Y Y  (  <_> )  | \/\___  |		//
//		\____|__  /\___  >__|_|  /\____/|__|   / ____|		//
//		        \/     \/      \/              \/     		//

#include <vector>

// Code adpated from Qo0, 2022
uintptr_t M::GetPattern(const char* chModule, const char* chPattern)
{
	if (!chPattern || !chModule)
		return 0;

	const HMODULE hModule = GetModuleHandleA(chModule);

	if (!hModule)
		return 0;

	const auto uModuleAddress = reinterpret_cast<uint8_t*>(hModule);

	const PIMAGE_DOS_HEADER pDosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(hModule);
	const PIMAGE_NT_HEADERS pNtHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(uModuleAddress + pDosHeader->e_lfanew);

	const uintptr_t uPattern = GetMemoryAddress(uModuleAddress, pNtHeader->OptionalHeader.SizeOfImage, chPattern);

	if (!uPattern)
		return 0;

	return uPattern;
}

uintptr_t M::GetMemoryAddress(uint8_t* uRegionStart, uintptr_t uRegionSize, const char* chPattern)
{
	std::vector<int> vecBytes = PatternToBytes(chPattern);

	for (unsigned int i = 0; i < uRegionSize - vecBytes.size(); ++i)
	{
		bool bByteFound = true;

		for (unsigned int j = 0; j < vecBytes.size(); ++j)
		{
			if (uRegionStart[i + j] != vecBytes[j] && vecBytes[j] != -1)
			{
				bByteFound = false;
				break;
			}
		}

		if (bByteFound)
			return reinterpret_cast<std::uintptr_t>(&uRegionStart[i]);
	}

	return 0;
}

std::vector<int> M::PatternToBytes(const char* chPattern)
{
	std::vector<int> vecBytes = { };
	
	char* chStart = const_cast<char*>(chPattern);
	char* chEnd = chStart + strlen(chPattern);

	for (char* chCurrent = chStart; chCurrent < chEnd; ++chCurrent)
	{
		if (*chCurrent == '?')
		{
			++chCurrent;

			if (*chCurrent == '?')
				++chCurrent;

			vecBytes.push_back(-1);
		}
		else
			vecBytes.push_back(strtoul(chCurrent, &chCurrent, 16));
	}

	return vecBytes;
}
// End of adapted code