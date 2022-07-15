#pragma once

//		  _________ __          .__          		//
//		 /   _____//  |_ ___.__.|  |   ____  		//
//		 \_____  \\   __<   |  ||  | _/ __ \ 		//
//		 /        \|  |  \___  ||  |_\  ___/ 		//
//		/_______  /|__|  / ____||____/\___  >		//
//		        \/       \/               \/ 		//

#include "../vitals/includes.h"

namespace Style
{
	// Variables
	static bool bInitialized = false; // Check if style has been created

	// Functions
	// Defines the style of the menu
	bool CreateStyle(IDirect3DDevice9* pDirectDevice);
}