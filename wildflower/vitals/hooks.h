#pragma once

//		  ___ ___                __					//
//		 /   |   \  ____   ____ |  | __  ______		//
//		/    ~    \/  _ \ /  _ \|  |/ / /  ___/		//
//		\    Y    (  <_> |  <_> )    <  \___ \		//
//		 \___|_  / \____/ \____/|__|_ \/____  >		//
//		       \/                    \/     \/		//

#include "includes.h"

#include "../utilities/memory.h"
#include "../utilities/hookmanager.h"

#include "../../dependencies/minhook/minhook.h"

namespace H
{
	// Variables
	static bool bInitialized = false; // Check if the menu dependencies have been setup

	static HWND hWindow = nullptr; // Stores focus window
	static WNDPROC oWindowProcess = nullptr; // Stores the window process

	// Functions
	// Setup hooks
	bool SetupHooks();
	// Remove hooks while dll terminates
	bool DestroyHooks();

	// Create direct device window
	bool SetupWindow();
	// Destroy direct device window and uninitialize ImGui
	bool DestroyWindow();

	// Manage the window display
	long WINAPI GetWindowProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Hooks
	// End scene hook for rendering visuals
	inline cHookManager EndScene;
	// Detour Function
	void WINAPI hEndScene(IDirect3DDevice9* pDirectDevice);
}