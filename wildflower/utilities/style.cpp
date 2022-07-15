#include "style.h"

//		  _________ __          .__          		//
//		 /   _____//  |_ ___.__.|  |   ____  		//
//		 \_____  \\   __<   |  ||  | _/ __ \ 		//
//		 /        \|  |  \___  ||  |_\  ___/ 		//
//		/_______  /|__|  / ____||____/\___  >		//
//		        \/       \/               \/ 		//

bool Style::CreateStyle(IDirect3DDevice9* pDirectDevice)
{
	// Check if style has been loaded already
	if (bInitialized)
		return false;

	// Menu configurations
	ImGui::StyleColorsDark();

	bInitialized = true;

	return true;
}