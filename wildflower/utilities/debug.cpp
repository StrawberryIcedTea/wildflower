#include "debug.h"

//		________        ___.                 		// 
//		\______ \   ____\_ |__  __ __  ____  		// 
//		 |    |  \_/ __ \| __ \|  |  \/ ___\ 		// 
//		 |    `   \  ___/| \_\ \  |  / /_/  >		// 
//		/_______  /\___  >___  /____/\___  / 		//
//		        \/     \/    \/     /_____/   		//

#include <time.h>

void Debug::SystemAlert(LPCSTR lpTitle, LPCSTR lpMessage)
{
	// Display a alert box on the users screen
	#if defined _DEBUG // Check if the program is configured to debug mode
	MessageBox(nullptr, lpMessage, lpTitle, MB_OK | MB_ICONEXCLAMATION); 
	#endif

	return;
}

void Debug::SystemWarning(LPCSTR lpTitle, LPCSTR lpMessage)
{
	// Display a warning box on the users screen
	#if defined _DEBUG // Check if the program is configured to debug mode
	MessageBox(nullptr, lpMessage, lpTitle, MB_OK | MB_ICONERROR); 
	#endif

	return;
}

//		_________                            .__         		// 
//		\_   ___ \  ____   ____   __________ |  |   ____ 		// 
//		/    \  \/ /  _ \ /    \ /  ___/  _ \|  | _/ __ \		// 
//		\     \___(  <_> )   |  \\___ (  <_> )  |_\  ___/		// 
//		\______  /\____/|___|  /____  >____/|____/\___  >		//
//		       \/            \/     \/                \/ 		//

bool C::SetupConsole(LPCSTR lpTitle)
{
	// Allocate memory in process for console
	if (!AllocConsole())
		return false;

	// Attach console to process
	AttachConsole(GetCurrentProcessId());

	// Console name
	if (!SetConsoleTitleA(lpTitle))
		return false;

	// Open write stream to console
	if (freopen_s(&fStream, "CONOUT$", "w", stdout))
		return false;

	// Handle of the console
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!StyleConsole(hConsole))
		return false;

	return true;
}

bool C::DestroyConsole()
{
	// Check that there is a console open
	if (!fStream)
		return false;

	// Close the stream to the console
	fclose(fStream);

	// Remove console from the memory
	FreeConsole();

	return true;
}

bool C::StyleConsole(HANDLE hConsole)
{
	// Console text color
	if (!SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN))
		return false;

	return true;
}

void C::Print(std::string strMessage)
{
	// Print custom text to console with a timestamp
	std::cout << U::GetTime() + " - " + strMessage << std::endl;
}