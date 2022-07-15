#include "interfaces.h"

//		.___        __                 _____									//
//		|   | _____/  |_  ____________/ ____\____    ____  ____   ______		//
//		|   |/    \   __\/ __ \_  __ \   __\\__  \ _/ ___\/ __ \ /  ___/		//
//		|   |   |  \  | \  ___/|  | \/|  |   / __ \\  \__\  ___/ \___ \			//
//		|___|___|  /__|  \___  >__|   |__|  (____  /\___  >___  >____  >		//
//		         \/          \/                  \/     \/    \/     \/			//

bool I::SetupInterfaces()
{
	// Find interfaces in memory using modules
	DirectDevice = **reinterpret_cast<IDirect3DDevice9***>(M::GetPattern("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 0x1);
	// Check that the interface was found
	if (DirectDevice == nullptr)
		return false;

	return true;
}