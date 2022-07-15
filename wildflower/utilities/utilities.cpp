#include "utilities.h"

//		 ____ ___   __  .__.__  .__  __  .__					//
//		|    |   \_/  |_|__|  | |__|/  |_|__| ____   ______		//
//		|    |   /\   __\  |  | |  \   __\  |/ __ \ /  ___/		//
//		|    |  /  |  | |  |  |_|  ||  | |  \  ___/ \___ \		//
//		|______/   |__| |__|____/__||__| |__|\___  >____  >		//
//		                                         \/     \/		//

#include <d3d9.h>

#include "../vitals/hooks.h"
#include "../vitals/interfaces.h"

std::string U::GetTime()
{
	// String to store time
	char chOutput[32];

	// Get current system time
	time_t tTime = _time64(&tTime);

	// Convert time_t to formatted time
	struct tm tStructured;
	localtime_s(&tStructured, &tTime);

	// Convert raw time into a formatted string
	strftime(chOutput, sizeof(chOutput), "%H:%M:%S", &tStructured);

	return chOutput;
}

bool U::KeyHold(int iKey)
{
	// Toggle while the user holds the key
	while (GetAsyncKeyState(iKey))
		return true;
	
	return false;
}

bool U::KeyUp(int iKey)
{
	static bool bIsPressed = false;

	// Toggle when the user lets go of key
	if (GetAsyncKeyState(iKey))
	{
		if (!bIsPressed)
			bIsPressed = true;
	}
	else if (bIsPressed) // Return true if the user pressed the key and let go
	{
		// Reset the loop
		bIsPressed = false;
		return true;
	}

	return false;
}