#include <sstream>
#include "Helper.h"
#include "Addresses.h"
#include "Byond.h"

FILE* fileHandle = NULL;

void OpenConsole()
{
	AllocConsole();
	fileHandle = freopen("CONOUT$", "w", stdout);
}

void CloseConsole()
{
	FreeConsole();
	auto kek = fileHandle;
	fclose(fileHandle);
}

DWORD WINAPI Main(HMODULE mainThread) {
	SuspendThread(mainThread);

#ifdef DEBUG_CONSOLE
	OpenConsole();
#endif

	HMODULE byondcoreModule = GetModuleHandle("byondcore.dll");
	ByondIntegration::LoadByondFunctions();
	ByondIntegration::LoadDungClient(byondcoreModule);

	char* fullbrightAddr = (char*)AOBScan(byondcoreModule, Addresses::Fullbright_pattern);
	char* wallhackAddr = (char*)AOBScan(byondcoreModule, Addresses::Wallhack_pattern);

	bool isfullbrightActivate = false; bool iswallhackActivate = false;

	ResumeThread(mainThread);
	Log("Version: " + ByondIntegration::GetByondVersion());
	Log("Ip: " + ByondIntegration::GetServerIp());

	while (!GetAsyncKeyState(VK_END))
	{
		// Wallhack
		if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
			iswallhackActivate = !iswallhackActivate;

			int size = sizeof(Addresses::Wallhack_on) - 1;

			if (iswallhackActivate) {
				Log("Enable wallhack");
				Patch(wallhackAddr, Addresses::Wallhack_on, size);
				continue;
			}

			Log("Disable wallhack");
			Patch(wallhackAddr, Addresses::Wallhack_off, size);
		}

		// Fullbright
		if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
			isfullbrightActivate = !isfullbrightActivate;

			int size = sizeof(Addresses::Fullbright_on) - 1;

			if (isfullbrightActivate) {
				Log("Enable fullbright");
				Patch(fullbrightAddr, Addresses::Fullbright_on, size);
				continue;
			}
			
			Log("Disable fullbright");
			Patch(fullbrightAddr, Addresses::Fullbright_off, size);
		}
	}

#ifdef DEBUG_CONSOLE
	CloseConsole();
#endif

	FreeLibraryAndExitThread(mainThread, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Main, hModule, 0, nullptr));
		break;
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

