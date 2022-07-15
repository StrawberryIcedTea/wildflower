#pragma once

//		.___        __                 _____									//
//		|   | _____/  |_  ____________/ ____\____    ____  ____   ______		//
//		|   |/    \   __\/ __ \_  __ \   __\\__  \ _/ ___\/ __ \ /  ___/		//
//		|   |   |  \  | \  ___/|  | \/|  |   / __ \\  \__\  ___/ \___ \			//
//		|___|___|  /__|  \___  >__|   |__|  (____  /\___  >___  >____  >		//
//		         \/          \/                  \/     \/    \/     \/			//

#include "includes.h"

#include "../utilities/memory.h"

namespace I
{
	// Variables
	inline IDirect3DDevice9* DirectDevice; // Direct device interface

	// Functions
	// Setup interfaces 
	bool SetupInterfaces();
}