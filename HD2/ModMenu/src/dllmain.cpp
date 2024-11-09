#define SETUP_AND_DESTROY
#include <windows.h>
#include <thread>
#include "gui.h"

/*

 QUICK NOTE : THE PROJECT CAN ONLY BE USED WITH RELEASE MODE BY DEFAULT

 IF YOU WANT DEBUG MODE THEN YOU WILL HAVE TO GO TO ext\minhook THEN THE MODE YOU WANT THEN RIGHT CLICK THE LIB FILE 
 AND CLICK INCLUDE IN PROJECT THEN GO TO THE OPOSITE ONE AND RIGHT CLICK IT THEN CLICK EXCLUDE FROM PROJECT

 MAKE SURE YOU ARE ON X64 AND NOT X86

*/

void menu(const HMODULE instance)
{
	try
	{
		Setup();
	}
	catch (const std::exception& error)
	{
		MessageBeep(MB_ICONERROR);
		MessageBox(
			0,
			error.what(),
			"Menu Error",
			MB_OK | MB_ICONEXCLAMATION
		);

		goto UNLOAD;
	}

	while (!GetAsyncKeyState(VK_NUMPAD1))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

UNLOAD:
	Destroy();
	FreeLibraryAndExitThread(instance, 0);
}

BOOL WINAPI DllMain(
	const HMODULE instance,
	const std::uintptr_t reason,
	const void* reserved
)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(instance);

		const auto thread = CreateThread(
			nullptr,
			0,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(menu),
			instance,
			0,
			nullptr
		);

		if (thread)
		{
			CloseHandle(thread);
		}
	}
}