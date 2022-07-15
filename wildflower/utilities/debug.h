#pragma once

//		________        ___.                 		// 
//		\______ \   ____\_ |__  __ __  ____  		// 
//		 |    |  \_/ __ \| __ \|  |  \/ ___\ 		// 
//		 |    `   \  ___/| \_\ \  |  / /_/  >		// 
//		/_______  /\___  >___  /____/\___  / 		//
//		        \/     \/    \/     /_____/   		//

#include "utilities.h"

#include "../vitals/includes.h"

namespace Debug
{
	// Functions
	// Call system alert boxes in debig mode only
	void SystemAlert(LPCSTR lpTitle, LPCSTR lpMessage);
	// Call system warning boxes in debig mode only
	void SystemWarning(LPCSTR lpTitle, LPCSTR lpMessage);
}

namespace C
{
	// Variables
	inline FILE* fStream; // File stream of console

	// Functions
	// Attach a console to the application for debugging
	bool SetupConsole(LPCSTR strTitle);
	// Detach console
	bool DestroyConsole();

	// Adds formmating to the debugging window
	bool StyleConsole(HANDLE hConsole);

	// Relay a message to the console
	void Print(std::string strMessage);
}