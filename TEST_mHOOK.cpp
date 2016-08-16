// TEST_mHOOK.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Minhook.h"

#pragma comment(lib, "libMinHook.x86.lib")
typedef int (WINAPI *MESSAGEBOXW)(HWND, LPCWSTR, LPCWSTR, UINT);
MESSAGEBOXW fpMessageBoxW = NULL;
int WINAPI DetourMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
	return fpMessageBoxW(hWnd, L"Hooked!", lpCaption, uType);
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Initialize MinHook.
		if (MH_Initialize() != MH_OK)
		{
			return 1;
		}

		// Create a hook for MessageBoxW, in disabled state.
		if (MH_CreateHook(&MessageBoxW, &DetourMessageBoxW, (LPVOID*)&fpMessageBoxW) != MH_OK)
		{
			return 1;
		}

		// Enable the hook for MessageBoxW.
		if (MH_EnableHook(&MessageBoxW) != MH_OK)
		{
			return 1;
		}

		// Expected to tell "Hooked!".
		MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

		// Disable the hook for MessageBoxW.
		if (MH_DisableHook(&MessageBoxW) != MH_OK)
		{
			return 1;
		}

		// Expected to tell "Not hooked...".
		MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

		// Uninitialize MinHook.
		if (MH_Uninitialize() != MH_OK)
		{
			return 1;
		}

		return 0;// Initialize MinHook.
}

