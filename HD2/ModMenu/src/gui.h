#ifndef GUI
#define GUI

#include <d3d11.h>
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_win32.h"
#include "../ext/imgui/imgui_impl_dx11.h"
#include "../ext/minhook/minhook.h"

#ifdef SETUP_AND_DESTROY
void Setup();
void Destroy();
#else
WNDPROC oWndProc;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

typedef long(__stdcall* present)(IDXGISwapChain*, UINT, UINT);
present p_present;
present p_present_target;

bool open = false;
void Setup();
void Destroy();
void HookDirectX_And_Render_Menu();
void getPresentPointer();
void DestroyDirectX();
void RenderMenu();
void DestroyMenu();

MH_STATUS status;

bool init = false;
HWND window = NULL;
ID3D11Device* p_device = NULL;
ID3D11DeviceContext* p_context = NULL;
ID3D11RenderTargetView* mainRenderTargetView = NULL;
static long __stdcall detour_present(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags);
#endif
#endif