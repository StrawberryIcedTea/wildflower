#include "hooks.h"

//		  ___ ___                __					//
//		 /   |   \  ____   ____ |  | __  ______		//
//		/    ~    \/  _ \ /  _ \|  |/ / /  ___/		//
//		\    Y    (  <_> |  <_> )    <  \___ \		//
//		 \___|_  / \____/ \____/|__|_ \/____  >		//
//		       \/                    \/     \/		//

#include <d3d9.h>

#include "menu.h"
#include "interfaces.h"

#include "../utilities/style.h"
#include "../utilities/utilities.h"

bool H::SetupHooks()
{
	// Start hooking library called at start of hooking
	MH_STATUS sInitializeHookLib = MH_Initialize();

	if (!sInitializeHookLib == MH_OK)
	{
		Debug::SystemWarning("Wildflower: Initialization Error: Setup Hooking Library", MH_StatusToString(sInitializeHookLib));
		return false;
	}

	// Set EndScene target function as virtual function 42 in direct device table
	EndScene.pTargetFunction = M::GetVirtualFunction(I::DirectDevice, 42);
	// Setup hook using the target function and the custom detour function
	if (!EndScene.CreateHook(&hEndScene))
		return false;

	return true;
}

bool H::DestroyHooks()
{
	// Remove EndScene hook
	if (!EndScene.DestroyHook())
		return false;

	// Clear heap and memory called at end of hooking
	MH_STATUS sUninitializeHookLib = MH_Uninitialize();

	if (!sUninitializeHookLib == MH_OK)
	{
		Debug::SystemWarning("Wildflower: Finalization Error: Remove Hooking Library", MH_StatusToString(sUninitializeHookLib));
		return false;
	}

	return true;
}

bool H::SetupWindow()
{
	// Create window handle
	D3DDEVICE_CREATION_PARAMETERS creationParameters;

	// Create window
	I::DirectDevice->GetCreationParameters(&creationParameters);
	hWindow = creationParameters.hFocusWindow;
	
	if (hWindow == nullptr)
		return false;

	// Store current window process
	oWindowProcess = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(GetWindowProcess)));

	if (oWindowProcess == nullptr)
		return false;

	return true;
}

bool H::DestroyWindow()
{
	// Set values to defaults
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();

	// Close ImGui
	ImGui::DestroyContext();

	return true;
}

long WINAPI H::GetWindowProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Toggle menu visability via hotkey
	if (U::KeyUp(VK_INSERT))
		Menu::bOpen = !Menu::bOpen;

	// Display menu
	if (bInitialized && Menu::bOpen && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return 1L;

	// Retrun default window
	return CallWindowProc(oWindowProcess, hWnd, msg, wParam, lParam);
}

void WINAPI H::hEndScene(IDirect3DDevice9* pDirectDevice)
{
	static auto oEndScene = EndScene.oFunction<decltype(&hEndScene)>();

	if (!bInitialized) // Setup scene with direct device
	{
		// Load ImGui defaults
		ImGui::CreateContext();

		// Initialize
		ImGui_ImplWin32_Init(hWindow);
		ImGui_ImplDX9_Init(pDirectDevice);

		bInitialized = true;
	}
	else // Render menu at the end of every scene
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();

		// Setup menu style
		if (!Style::bInitialized)
			Style::CreateStyle(pDirectDevice);

		ImGui::NewFrame();

		// Load menu
		if (Menu::bOpen)
			Menu::MenuFrame(pDirectDevice);

		ImGui::EndFrame();

		// Render the menu on the window
		ImGui::Render();

		// Render menu transforms
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	return oEndScene(pDirectDevice);
}