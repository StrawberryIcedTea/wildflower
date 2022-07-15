#pragma once

//		   _____							//
//		  /     \   ____   ____  __ __		//
//		 /  \ /  \_/ __ \ /    \|  |  \		//
//		/    Y    \  ___/|   |  \  |  /		//
//		\____|__  /\___  >___|  /____/		//
//		        \/     \/     \/			//

#include "includes.h"

namespace Menu
{
	// Variables
	static bool bOpen = true; // Console menu toggle
	
	// Functions
	// Code to display on menu
	void MenuFrame(IDirect3DDevice9* pDirectDevice);
}