#pragma once
#include <windows.h>
#include <thread>
#include <iostream>
#include "lazy.h"
#include "skCrypt.h"

#include "anti_vm.h"
#include "spoof.hpp"



inline  void open_binary_file(const std::string& file, std::vector<uint8_t>& data)
{
	std::ifstream fstr(file, std::ios::binary);
	fstr.unsetf(std::ios::skipws);
	fstr.seekg(0, std::ios::end);

	const auto file_size = fstr.tellg();

	fstr.seekg(NULL, std::ios::beg);
	data.reserve(static_cast<uint32_t>(file_size));
	data.insert(data.begin(), std::istream_iterator<uint8_t>(fstr), std::istream_iterator<uint8_t>());
}


bool IsProcessRunning(const wchar_t* processName)
{
	bool exists = false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry))
		while (Process32Next(snapshot, &entry))
			if (!_wcsicmp((wchar_t*)entry.szExeFile, processName))
				exists = true;

	CloseHandle(snapshot);
	return exists;
}




bool EnableTokenPriviliges(HANDLE processhandle, const char* permchar)
{
	HANDLE tokenhandle;
	LUID permissionidentifier;
	TOKEN_PRIVILEGES tokenpriv;
	if (SPOOF_CALL(OpenProcessToken)(processhandle, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &tokenhandle))
	{
		if (LookupPrivilegeValue(NULL, permchar, &permissionidentifier))
		{
			tokenpriv.PrivilegeCount = 1;
			tokenpriv.Privileges[0].Luid = permissionidentifier;
			tokenpriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			if (AdjustTokenPrivileges(tokenhandle, false, &tokenpriv, sizeof(tokenpriv), NULL, NULL)) { return true; }
			else { return false; }
		}
		else { return false; }
	}
	else { return false; }
	CloseHandle(tokenhandle);
}
int TEMP = 0;

auto JunkCode() -> void
{

	
}
void MassJunkCode()
{
	for (auto i{ 0 }; i <= 10; i++)
	{
		SPOOF_CALL(JunkCode)();
	}
}
void* pe_header[4096];

void notSafe()
{
	SPOOF_CALL(MassJunkCode)();
	DWORD old = 0;
	void* module = GetModuleHandleW(0);
	VirtualProtect(module, 4096, PAGE_READWRITE, &old);
	memcpy(module, pe_header, 4096);
	VirtualProtect(module, 4096, old, &old);
	SPOOF_CALL(MassJunkCode)();

}


typedef NTSTATUS(__stdcall* _NtQueryInformationProcess)(_In_ HANDLE, _In_  unsigned int, _Out_ PVOID, _In_ ULONG, _Out_ PULONG);
typedef NTSTATUS(__stdcall* _NtSetInformationThread)(_In_ HANDLE, _In_ THREAD_INFORMATION_CLASS, _In_ PVOID, _In_ ULONG);
typedef NTSTATUS(WINAPI* lpQueryInfo)(HANDLE, LONG, PVOID, ULONG, PULONG);

bool rape = false;

inline void crash(const char* text) {
	std::cout << skCrypt("error : ") << text << std::endl;
	LI_FN(Sleep).get()(3000);
	*(uintptr_t*)(0) = 1;
}

inline DWORD anti_suspend() //aka anti pause
{
	static DWORD TimeTest1 = 0, TimeTest2 = 0;
	TimeTest1 = TimeTest2;
	TimeTest2 = LI_FN(GetTickCount).forwarded_safe_cached()();
	if (TimeTest1 != 0)
		if (TimeTest2 - TimeTest1 > 6000) {
			crash(skCrypt("Time"));
			*(uintptr_t*)(0) = 1;
		}
	return 0;
}
inline bool hide_thread(HANDLE thread)
{
	typedef NTSTATUS(NTAPI* pNtSetInformationThread)(HANDLE, UINT, PVOID, ULONG);
	NTSTATUS Status;

	pNtSetInformationThread NtSIT = (pNtSetInformationThread)LI_FN(GetProcAddress).forwarded_safe_cached()((LI_FN(GetModuleHandleA).forwarded_safe_cached())(skCrypt("ntdll.dll")), skCrypt("NtSetInformationThread"));

	if (NtSIT == NULL) return false;
	if (thread == NULL)
		Status = NtSIT(LI_FN(GetCurrentThread).forwarded_safe_cached(), 0x11, 0, 0);
	else
		Status = NtSIT(thread, 0x11, 0, 0);

	if (Status != 0x00000000)
		return false;
	else
		return true;
}
inline int hide_loader_thread()
{
	unsigned long thread_hide_from_debugger = 0x11;

	const auto ntdll = LI_FN(LoadLibraryA).forwarded_safe_cached()(skCrypt("ntdll.dll"));

	if (ntdll == INVALID_HANDLE_VALUE || ntdll == NULL) { return false; }

	_NtQueryInformationProcess NtQueryInformationProcess = NULL;
	NtQueryInformationProcess = (_NtQueryInformationProcess)LI_FN(GetProcAddress).forwarded_safe_cached()(ntdll, skCrypt("NtQueryInformationProcess"));

	if (NtQueryInformationProcess == NULL) { return false; }

	(_NtSetInformationThread)(LI_FN(GetCurrentThread).forwarded_safe_cached(), thread_hide_from_debugger, 0, 0, 0);

	return true;
}
inline int thread_context()
{
	int found = false;
	CONTEXT ctx = { 0 };
	void* h_thread = LI_FN(GetCurrentThread).forwarded_safe_cached();

	ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	if (LI_FN(GetThreadContext).forwarded_safe_cached()(h_thread, &ctx))
	{
		if ((ctx.Dr0 != 0x00) || (ctx.Dr1 != 0x00) || (ctx.Dr2 != 0x00) || (ctx.Dr3 != 0x00) || (ctx.Dr6 != 0x00) || (ctx.Dr7 != 0x00))
		{
			found = true;
		}
	}

	return found;
}
inline int ollydbg_exploit() {
	__try {
		LI_FN(OutputDebugStringA).forwarded_safe_cached()(skCrypt("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"));
	}
	__except (EXCEPTION_EXECUTE_HANDLER) { ; }

	return 0;
}
inline int last_error()
{
	LI_FN(SetLastError).forwarded_safe_cached()(0);
	const auto last_error = LI_FN(GetLastError).forwarded_safe_cached()();

	return last_error != 0;
}
inline int remote_is_present()
{
	int debugger_present = false;

	LI_FN(CheckRemoteDebuggerPresent).forwarded_safe_cached()(LI_FN(GetCurrentProcess).forwarded_safe_cached()(), &debugger_present);

	return debugger_present;
}
inline bool check1()
{
	UCHAR* pMem = NULL;
	SYSTEM_INFO SystemInfo = { 0 };
	DWORD OldProtect = 0;
	PVOID pAllocation = NULL;

	LI_FN(GetSystemInfo).forwarded_safe_cached()(&SystemInfo);

	pAllocation = LI_FN(VirtualAlloc).forwarded_safe_cached()(NULL, SystemInfo.dwPageSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (pAllocation == NULL)
		return FALSE;

	RtlFillMemory(pAllocation, 1, 0xC3);

	if (LI_FN(VirtualProtect).forwarded_safe_cached()(pAllocation, SystemInfo.dwPageSize, PAGE_EXECUTE_READWRITE | PAGE_GUARD, &OldProtect) == 0)
		return FALSE;

	__try
	{
		((void(*)())pAllocation)();
	}
	__except (GetExceptionCode() == STATUS_GUARD_PAGE_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		LI_FN(VirtualFree).forwarded_safe_cached()(pAllocation, NULL, MEM_RELEASE);
		return FALSE;
	}

	LI_FN(VirtualFree).forwarded_safe_cached()(pAllocation, NULL, MEM_RELEASE);
	return TRUE;
}
inline bool check2()
{
	PCONTEXT ctx = PCONTEXT(LI_FN(VirtualAlloc).forwarded_safe_cached()(NULL, sizeof(ctx), MEM_COMMIT, PAGE_READWRITE));
	RtlSecureZeroMemory(ctx, sizeof(CONTEXT));

	ctx->ContextFlags = CONTEXT_DEBUG_REGISTERS;

	if (LI_FN(GetThreadContext).forwarded_safe_cached()(LI_FN(GetCurrentThread).forwarded_safe_cached()(), ctx) == 0)
		return -1;


	if (ctx->Dr0 != 0 || ctx->Dr1 != 0 || ctx->Dr2 != 0 || ctx->Dr3 != 0)
		return TRUE;
	else
		return FALSE;
}
inline int null_size()
{
	/*const auto peb = (PPEB)__readgsqword(0x60);

	const auto in_load_order_module_list = (PLIST_ENTRY)peb->Ldr->Reserved2[1];
	const auto table_entry = CONTAINING_RECORD(in_load_order_module_list, LDR_DATA_TABLE_ENTRY, Reserved1[0]);
	const auto p_size_of_image = (PULONG)&table_entry->Reserved3[1];
	*p_size_of_image = (ULONG)((INT_PTR)table_entry->DllBase + 0x100000);*/

	return 0;
}
inline bool system_check()
{
	typedef NTSTATUS(__stdcall* td_NtQuerySystemInformation)(
		ULONG           SystemInformationClass,
		PVOID           SystemInformation,
		ULONG           SystemInformationLength,
		PULONG          ReturnLength
		);

	struct SYSTEM_CODEINTEGRITY_INFORMATION {
		ULONG Length;
		ULONG CodeIntegrityOptions;
	};

	static td_NtQuerySystemInformation NtQuerySystemInformation = (td_NtQuerySystemInformation)LI_FN(GetProcAddress).forwarded_safe_cached()(LI_FN(GetModuleHandleA).forwarded_safe_cached()(skCrypt("ntdll.dll")), skCrypt("NtQuerySystemInformation"));

	SYSTEM_CODEINTEGRITY_INFORMATION Integrity = { sizeof(SYSTEM_CODEINTEGRITY_INFORMATION), 0 };
	NTSTATUS status = NtQuerySystemInformation(103, &Integrity, sizeof(Integrity), NULL);

	return (status && (Integrity.CodeIntegrityOptions & 1));
}
int is_debugger_present()
{
	return LI_FN(IsDebuggerPresent).forwarded_safe_cached()();
}
inline void window_check()
{
	//if (LI_FN(FindWindowA).forwarded_safe_cached()(skCrypt("Window"), NULL)) *(uintptr_t*)(0) = 0;
	//if (LI_FN(FindWindowA).forwarded_safe_cached()(skCrypt("Qt5QWindowIcon"), NULL)) *(uintptr_t*)(0) = 0;
	//if (LI_FN(FindWindowA).forwarded_safe_cached()(skCrypt("ProcessHacker"), NULL)) *(uintptr_t*)(0) = 0; 
	if (LI_FN(FindWindowA).forwarded_safe_cached()(skCrypt("PROCEXPL"), NULL)) *(uintptr_t*)(0) = 0;
	if (LI_FN(FindWindowA).forwarded_safe_cached()(skCrypt("dbgviewClass"), NULL)) *(uintptr_t*)(0) = 0;
	if (LI_FN(FindWindowA).forwarded_safe_cached()(skCrypt("XTPMainFrame"), NULL)) *(uintptr_t*)(0) = 0;
	if (LI_FN(FindWindowA).forwarded_safe_cached()(skCrypt("WdcWindow"), skCrypt("Resource Monitor"))) *(uintptr_t*)(0) = 0;
}
inline bool close_handle()
{
	__try {
		LI_FN(CloseHandle).forwarded_safe_cached()((HANDLE)0x13333337);
	}
	__except (STATUS_INVALID_HANDLE) {
		return TRUE;
	}
}
inline bool thread_hide_debugger()
{
	typedef NTSTATUS(WINAPI* pNtSetInformationThread)(IN HANDLE, IN UINT, IN PVOID, IN ULONG);

	const int ThreadHideFromDebugger = 0x11;
	pNtSetInformationThread NtSetInformationThread = NULL;

	NTSTATUS Status;
	BOOL IsBeingDebug = FALSE;

	HMODULE hNtDll = LI_FN(LoadLibraryA).forwarded_safe_cached()(skCrypt("ntdll.dll"));
	NtSetInformationThread = (pNtSetInformationThread)LI_FN(GetProcAddress).forwarded_safe_cached()(hNtDll, skCrypt("NtSetInformationThread"));
	Status = NtSetInformationThread(LI_FN(GetCurrentThread).forwarded_safe_cached()(), ThreadHideFromDebugger, NULL, 0);

	if (Status)
		*(uintptr_t*)(0) = 1;

	return IsBeingDebug;
}
inline void hardware_register()
{
	BOOL found = FALSE;
	CONTEXT ctx = { 0 };
	HANDLE hThread = LI_FN(GetCurrentThread).forwarded_safe_cached()();

	ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	if (LI_FN(GetThreadContext).forwarded_safe_cached()(hThread, &ctx))
	{
		if ((ctx.Dr0 != 0x00) || (ctx.Dr1 != 0x00) || (ctx.Dr2 != 0x00) || (ctx.Dr3 != 0x00) || (ctx.Dr6 != 0x00) || (ctx.Dr7 != 0x00))
		{
			found = TRUE;
		}
	}

	if (found)
	{
		crash(skCrypt("rgst"));
	}
}



inline int hardware_breakpoints()
{
	unsigned int NumBps = 0;

	CONTEXT ctx;
	RtlSecureZeroMemory(&ctx, sizeof(CONTEXT));

	ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

	HANDLE hThread = LI_FN(GetCurrentThread).forwarded_safe_cached()();

	if (LI_FN(GetThreadContext).forwarded_safe_cached()(hThread, &ctx) == 0)
		crash(skCrypt("brkp"));

	if (ctx.Dr0 != 0)
		++NumBps;
	if (ctx.Dr1 != 0)
		++NumBps;
	if (ctx.Dr2 != 0)
		++NumBps;
	if (ctx.Dr3 != 0)
		++NumBps;

	return NumBps;
}

void security_loop()
{

	hide_thread(LI_FN(GetCurrentThread).forwarded_safe_cached()());
	thread_hide_debugger();
	hide_loader_thread();
	while (true)
	{
		//	anti_inject();
		anti_suspend();
		check_processes();
		window_check();

		ollydbg_exploit();
		hardware_breakpoints();
		hardware_register(); 
		vmware_check();	
		virtual_box_drivers();
		virtual_box_registry();


		if (check1()) *(uintptr_t*)(0) = 0;
		if (check2()) *(uintptr_t*)(0) = 0;
		if (last_error()) *(uintptr_t*)(0) = 0;
		if (close_handle()) *(uintptr_t*)(0) = 0;
		if (thread_context()) *(uintptr_t*)(0) = 0;
		if (remote_is_present()) *(uintptr_t*)(0) = 0;
		if (is_debugger_present()) *(uintptr_t*)(0) = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}