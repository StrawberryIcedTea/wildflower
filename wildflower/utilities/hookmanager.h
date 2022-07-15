#pragma once

//		  ___ ___                __        _____                                             		//
//		 /   |   \  ____   ____ |  | __   /     \ _____    ____ _____     ____   ___________ 		//
//		/    ~    \/  _ \ /  _ \|  |/ /  /  \ /  \\__  \  /    \\__  \   / ___\_/ __ \_  __ \		//
//		\    Y    (  <_> |  <_> )    <  /    Y    \/ __ \|   |  \/ __ \_/ /_/  >  ___/|  | \/		//
//		 \___|_  / \____/ \____/|__|_ \ \____|__  (____  /___|  (____  /\___  / \___  >__|   		//
//		       \/                    \/         \/     \/     \/     \//_____/      \/       		//

#include "../vitals/includes.h"

#include "../../dependencies/minhook/minhook.h"

class cHookManager
{
public:

	// Variables
	void* pTargetFunction = nullptr; // Stores target function

	// Functions
	// Creates hooks for custom functions
	bool CreateHook(void* pDetour);
	// Destroys hooks
	bool DestroyHook();

	// template for storing original state of detours
	template <typename Function>
	Function oFunction() { return static_cast<Function>(pOriginalFunction); }

private:

	// Variables
	bool bInitialized = false; // Check if the hooks have been setup

	void* pOriginalFunction = nullptr; // Stores original function
};