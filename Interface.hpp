#pragma once
#include <Windows.h>

/*驱动绘制接口*/

struct ImVec4
{
	float     x, y, z, w;
	ImVec4() { x = y = z = w = 0.0f; }
	ImVec4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
#ifdef IM_VEC4_CLASS_EXTRA
	IM_VEC4_CLASS_EXTRA     // Define additional constructors and implicit cast operators in imconfig.h to convert back and forth between your math types and ImVec4.
#endif
};

struct ImVec2
{
	float     x, y;
	ImVec2() { x = y = 0.0f; }
	ImVec2(float _x, float _y) { x = _x; y = _y; }
};

/*
* 初始化所有的dwm数据
*/
typedef BOOL(WINAPI* PDwm_Init)(char* key);
PDwm_Init Dwm_Init = NULL;

/*
* 提交所有要画的东西给DWM
*/
typedef VOID(WINAPI* PDwm_UpDataDraw)();
PDwm_UpDataDraw Dwm_UpDataDraw = NULL;

/*
* 打开Dwm绘制
*/
typedef VOID(WINAPI* PDwm_OpenDraw)();
PDwm_OpenDraw Dwm_OpenDraw = NULL;

/*
* 停止DWM绘制
*/
typedef VOID(WINAPI* PDwm_StopDraw)();
PDwm_StopDraw Dwm_StopDraw = NULL;

/*
* 绘制文字
*/
typedef VOID(WINAPI* PDwm_DrawText)(float X, float Y, ImVec4 Color, bool Outlined, const char* Str);
PDwm_DrawText Dwm_DrawText = NULL;

/*
* 绘制文字
*/
typedef VOID(WINAPI* PDwm_DrawTextStr)(float X, float Y, ImVec4 Color, bool Outlined, const char* Str, ...);
PDwm_DrawTextStr Dwm_DrawTextStr = NULL;

/*
* 绘制带尺寸的文字
*/
typedef VOID(WINAPI* PDwm_DrawTextSize)(float font_size, const ImVec2 pos, ImVec4 col, const char* text_begin);
PDwm_DrawTextSize Dwm_DrawTextSize = NULL;

/*
* 绘制圆
*/
typedef VOID(WINAPI* PDwm_DrawCircle)(float X, float Y, float Radius, ImVec4 Color, int Segments, float thickness);
PDwm_DrawCircle Dwm_DrawCircle = NULL;

/*
* 绘制纯色圆
*/
typedef VOID(WINAPI* PDwm_DrawCircleFilled)(float X, float Y, float Radius, ImVec4 Color, int Segments);
PDwm_DrawCircleFilled Dwm_DrawCircleFilled = NULL;

/*
* 绘制矩形
*/
typedef VOID(WINAPI* PDwm_DrawRect)(float X, float Y, float W, float H, ImVec4 Color, float thickness);
PDwm_DrawRect Dwm_DrawRect = NULL;

/*
* 用线条绘制矩形
*/
typedef VOID(WINAPI* PDwm_DrawRectEx)(float X, float Y, float W, float H, ImVec4 Color, float thickness);
PDwm_DrawRectEx Dwm_DrawRectEx = NULL;

/*
* 绘制纯色矩形
*/
typedef VOID(WINAPI* PDwm_DrawFilledRect)(float X, float Y, float W, float H, ImVec4 Color);
PDwm_DrawFilledRect Dwm_DrawFilledRect = NULL;

/*
* 绘制线条
*/
typedef VOID(WINAPI* PDwm_DrawLine)(float X1, float Y1, float X2, float Y2, ImVec4 Color, float thickness);
PDwm_DrawLine Dwm_DrawLine = NULL;

//驱动接口
typedef BOOLEAN(WINAPI* Pkernel_driverlogin)(char m_key[MAX_PATH]);
Pkernel_driverlogin kernel_driverlogin = NULL;

typedef BOOLEAN(WINAPI* Pkernel_readmem)(ULONG Pid, PVOID64 pDestAddr, PVOID64 pBuff, ULONG ReadLen);
Pkernel_readmem kernel_readmem = NULL;

typedef BOOLEAN(WINAPI* Pkernel_writemem)(ULONG Pid, PVOID64 pDestAddr, PVOID64 pBuff, ULONG WriteLen);
Pkernel_writemem kernel_writemem = NULL;

typedef PVOID64(WINAPI* Pkernel_allocprocmem)(ULONG Pid, ULONG memLen);
Pkernel_allocprocmem kernel_allocprocmem = NULL;

typedef PVOID64(WINAPI* Pkernel_allocmem_to_user)(ULONG Pid, ULONG memLen);
Pkernel_allocmem_to_user kernel_allocmem_to_user = NULL;

typedef BOOLEAN(WINAPI* Pkernel_loadDll)(ULONG Pid, PVOID64 pDllBuf, ULONG DllLen);
Pkernel_loadDll kernel_loadDll = NULL;

typedef BOOLEAN(WINAPI* Pkernel_getprocessmodule)(ULONG Pid, const char* pModuleName, PULONG64 pModuleBase);
Pkernel_getprocessmodule kernel_getprocessmodule = NULL;

typedef ULONG32(WINAPI* Pgetpidbyname)(const wchar_t* processName);
Pgetpidbyname getpidbyname = NULL;

typedef BOOL(WINAPI* Preleasehidefile)(void* buf, int buflen, const char* filepath);
Preleasehidefile releasehidefile = NULL;

#define CheckParameters(Parameter) if(Parameter == 0){goto __erro;} 

BOOL InitInterface(const char* coredllpath)
{
	HMODULE core = NULL;
	core = LoadLibraryA(coredllpath);
	if (!core)
	{
		goto __erro;
	}

	Dwm_Init = (PDwm_Init)GetProcAddress(core, "Dwm_Init");
	CheckParameters(Dwm_Init);

	Dwm_UpDataDraw = (PDwm_UpDataDraw)GetProcAddress(core, "Dwm_UpDataDraw");
	CheckParameters(Dwm_UpDataDraw);

	Dwm_OpenDraw = (PDwm_OpenDraw)GetProcAddress(core, "Dwm_OpenDraw");
	CheckParameters(Dwm_OpenDraw);

	Dwm_StopDraw = (PDwm_StopDraw)GetProcAddress(core, "Dwm_StopDraw");
	CheckParameters(Dwm_Init);

	Dwm_DrawText = (PDwm_DrawText)GetProcAddress(core, "Dwm_DrawText");
	CheckParameters(Dwm_DrawText);

	Dwm_DrawTextStr = (PDwm_DrawTextStr)GetProcAddress(core, "Dwm_DrawTextStr");
	CheckParameters(Dwm_DrawTextStr);

	Dwm_DrawTextSize = (PDwm_DrawTextSize)GetProcAddress(core, "Dwm_DrawTextSize");
	CheckParameters(Dwm_DrawTextSize);

	Dwm_DrawCircle = (PDwm_DrawCircle)GetProcAddress(core, "Dwm_DrawCircle");
	CheckParameters(Dwm_DrawCircle);

	Dwm_DrawCircleFilled = (PDwm_DrawCircleFilled)GetProcAddress(core, "Dwm_DrawCircleFilled");
	CheckParameters(Dwm_DrawCircleFilled);

	Dwm_DrawRect = (PDwm_DrawRect)GetProcAddress(core, "Dwm_DrawRect");
	CheckParameters(Dwm_DrawRect);

	Dwm_DrawRectEx = (PDwm_DrawRectEx)GetProcAddress(core, "Dwm_DrawRectEx");
	CheckParameters(Dwm_DrawRectEx);

	Dwm_DrawLine = (PDwm_DrawLine)GetProcAddress(core, "Dwm_DrawLine");
	CheckParameters(Dwm_DrawLine);

	kernel_driverlogin = (Pkernel_driverlogin)GetProcAddress(core, "kernel_driverlogin");
	CheckParameters(kernel_driverlogin);

	kernel_readmem = (Pkernel_readmem)GetProcAddress(core, "kernel_readmem");
	CheckParameters(kernel_readmem);

	kernel_writemem = (Pkernel_readmem)GetProcAddress(core, "kernel_writemem");
	CheckParameters(kernel_writemem);

	kernel_allocprocmem = (Pkernel_allocprocmem)GetProcAddress(core, "kernel_allocprocmem");
	CheckParameters(kernel_allocprocmem);

	kernel_allocmem_to_user = (Pkernel_allocmem_to_user)GetProcAddress(core, "kernel_allocmem_to_user");
	CheckParameters(kernel_allocmem_to_user);

	kernel_loadDll = (Pkernel_loadDll)GetProcAddress(core, "kernel_loadDll");
	CheckParameters(kernel_loadDll);

	kernel_getprocessmodule = (Pkernel_getprocessmodule)GetProcAddress(core, "kernel_getprocessmodule");
	CheckParameters(kernel_getprocessmodule);

	getpidbyname = (Pgetpidbyname)GetProcAddress(core, "getpidbyname");
	CheckParameters(getpidbyname);

	releasehidefile = (Preleasehidefile)GetProcAddress(core, "releasehidefile");
	CheckParameters(releasehidefile);

__sucess:
	return TRUE;

__erro:
	if (core)
	{
		FreeLibrary(core);
	}
	return FALSE;
}
