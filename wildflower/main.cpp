
//		 █     █░ ██▓ ██▓    ▓█████▄   █████▒██▓     ▒█████   █     █░▓█████  ██▀███  		//		                    		//
//		▓█░ █ ░█░▓██▒▓██▒    ▒██▀ ██▌▓██   ▒▓██▒    ▒██▒  ██▒▓█░ █ ░█░▓█   ▀ ▓██ ▒ ██▒		//			 PROJECT HONEY			//
//		▒█░ █ ░█ ▒██▒▒██░    ░██   █▌▒████ ░▒██░    ▒██░  ██▒▒█░ █ ░█ ▒███   ▓██ ░▄█ ▒		//			   WILDFLOWER  			//
//		░█░ █ ░█ ░██░▒██░    ░▓█▄   ▌░▓█▒  ░▒██░    ▒██   ██░░█░ █ ░█ ▒▓█  ▄ ▒██▀▀█▄  		//									//
//		░░██▒██▓ ░██░░██████▒░▒████▓ ░▒█░   ░██████▒░ ████▓▒░░░██▒██▓ ░▒████▒░██▓ ▒██▒		//	  CERTIFIED RUDEBOY SYNTAX 💯	//
//		░ ▓░▒ ▒  ░▓  ░ ▒░▓  ░ ▒▒▓  ▒  ▒ ░   ░ ▒░▓  ░░ ▒░▒░▒░ ░ ▓░▒ ▒  ░░ ▒░ ░░ ▒▓ ░▒▓░		//									//
//		  ▒ ░ ░   ▒ ░░ ░ ▒  ░ ░ ▒  ▒  ░     ░ ░ ▒  ░  ░ ▒ ▒░   ▒ ░ ░   ░ ░  ░  ░▒ ░ ▒░		//		     AUTHOR : ENZO		    //
//		  ░   ░   ▒ ░  ░ ░    ░ ░  ░  ░ ░     ░ ░   ░ ░ ░ ▒    ░   ░     ░     ░░   ░ 		//									//
//		    ░     ░      ░  ░   ░               ░  ░    ░ ░      ░       ░  ░   ░     		//		    MADE : 21.06.22			//
//	                          ░                                                       		//									//

#include <thread>

#include "vitals/hooks.h"
#include "vitals/includes.h"
#include "vitals/interfaces.h"
#include "vitals/menu.h"

DWORD WINAPI DllInitialization(LPVOID lpModule)
{
	// Wait for all modules in csgo to be loaded before tampering with the memory
	while (!GetModuleHandleA("serverbrowser.dll"))
		std::this_thread::sleep_for(std::chrono::microseconds(500));

	// Attach console to process
	#if defined _DEBUG // Check if the program is configured to debug mode
	if (C::SetupConsole("Debug Window"))
		C::Print("Console setup");
	else
		Debug::SystemAlert("Wildflower: Initialization Error", "Could not attach the console to the program.");
	#endif

	// Setup interfaces
	if (I::SetupInterfaces())
		C::Print("Interfaces setup");
	else
		C::Print("Interfaces failed to setup");

	// Setup window
	if (H::SetupWindow())
		C::Print("Window setup");
	else
		C::Print("Window failed to setup");

	// Setup hooks
	if (H::SetupHooks())
		C::Print("Hooks setup");
	else
		C::Print("Hooks failed to setup");

	// Notify the end of the initialization and wait for the user to exit the thread
	C::Print("Initialization successful");

	// Panic key starts finalization
	while (!U::KeyHold(VK_DELETE))
		std::this_thread::sleep_for(std::chrono::microseconds(500));

	// Exit thread and call process detach
	FreeLibraryAndExitThread((HMODULE)lpModule, EXIT_SUCCESS);

	return 0U;
}

DWORD WINAPI DllFinalization()
{
	// Close file stream and remove console from memory
	#if defined _DEBUG // Check if the program is configured to debug mode
	if (!C::DestroyConsole())
		Debug::SystemWarning("Wildflower: Finalization Error", "Error destroying the attached console.");
	#endif

	// Close ImGui and Dx9
	if (!H::DestroyWindow())
		Debug::SystemWarning("Wildflower: Finalization Error", "Error destroying ImGui functions.");

	// Remove hooks from process
	if (!H::DestroyHooks())
		Debug::SystemWarning("Wildflower: Finalization Error", "Error destroying the hooked functions.");
	
	return 0U;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH: // DLL Initialization 
	{
		// Prevent library calls from the threads to DLLMain
		DisableThreadLibraryCalls(hModule);

		// Check if DLL is being executed in csgo.exe process
		if (GetModuleHandleA("csgo.exe") == nullptr)
		{
			Debug::SystemWarning("Wildflower: Process Attach Error", "Cannot inject DLL, ensure that CS:GO is open and is the target process.");
			return FALSE;
		}

		// Create thread to run functions in process
		HANDLE hThread = CreateThread(0, 0U, DllInitialization, hModule, 0UL, 0);

		// Close handle if threads have finished processing
		if (hThread != nullptr)
			CloseHandle(hThread);

		return TRUE;
		break;
	}

	case DLL_PROCESS_DETACH: // DLL Finalization
	{
		// Final DLL clean-up
		DllFinalization();

		break;
	}
	}

	return FALSE;
}