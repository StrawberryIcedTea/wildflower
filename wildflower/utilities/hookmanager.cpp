#include "hookmanager.h"

//		  ___ ___                __        _____                                             		//
//		 /   |   \  ____   ____ |  | __   /     \ _____    ____ _____     ____   ___________ 		//
//		/    ~    \/  _ \ /  _ \|  |/ /  /  \ /  \\__  \  /    \\__  \   / ___\_/ __ \_  __ \		//
//		\    Y    (  <_> |  <_> )    <  /    Y    \/ __ \|   |  \/ __ \_/ /_/  >  ___/|  | \/		//
//		 \___|_  / \____/ \____/|__|_ \ \____|__  (____  /___|  (____  /\___  / \___  >__|   		//
//		       \/                    \/         \/     \/     \/     \//_____/      \/       		//

bool cHookManager::CreateHook(void* pDetour)
{
	// Check parameters are set
	if (!pTargetFunction || !pDetour)
		return false;

	// Create a detour for the process function
	MH_STATUS sCreateHook = MH_CreateHook(pTargetFunction, pDetour, &pOriginalFunction);

	if (!sCreateHook == MH_OK)
	{
		Debug::SystemWarning("Wildflower: Finalization Error: Create Hook", MH_StatusToString(sCreateHook));
		return false;
	}

	// Enable the hook in library
	MH_STATUS sEnableHook = MH_EnableHook(pTargetFunction);

	if (!sEnableHook == MH_OK)
	{
		Debug::SystemWarning("Wildflower: Finalization Error: Enable Hook", MH_StatusToString(sEnableHook));
		return false;
	}

	// Tell program that the hook has been setup
	bInitialized = true;

	return true;
}

bool cHookManager::DestroyHook()
{
	// Check that the function was created
	if (!pTargetFunction || !bInitialized)
		return false;

	// Disable the functions hook
	MH_STATUS sDisableHook = MH_DisableHook(pTargetFunction);

	if (!sDisableHook == MH_OK)
	{
		Debug::SystemWarning("Wildflower: Finalization Error: Disable Hook", MH_StatusToString(sDisableHook));
		return false;
	}

	// Remove the hook from the process
	MH_STATUS sRemoveHook = MH_RemoveHook(pTargetFunction);

	if (!sRemoveHook == MH_OK)
	{
		Debug::SystemWarning("Wildflower: Finalization Error: Remove Hook", MH_StatusToString(sRemoveHook));
		return false;
	}

	return true;
}