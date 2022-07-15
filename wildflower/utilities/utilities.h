#pragma once

//		 ____ ___   __  .__.__  .__  __  .__					//
//		|    |   \_/  |_|__|  | |__|/  |_|__| ____   ______		//
//		|    |   /\   __\  |  | |  \   __\  |/ __ \ /  ___/		//
//		|    |  /  |  | |  |  |_|  ||  | |  \  ___/ \___ \		//
//		|______/   |__| |__|____/__||__| |__|\___  >____  >		//
//		                                         \/     \/		//

#include "../vitals/includes.h"

namespace U
{
	// Funcitons
	// Get current system time as a string
	std::string GetTime();

	// Returns true when user holds key
	bool KeyHold(int iKey);
	// Returns true when user releases key
	bool KeyUp(int iKey);
}