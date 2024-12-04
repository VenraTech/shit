#include <windows.h>

#pragma once

#include "soprano.h"

class MsgConfirm
{
public:
	MsgConfirm(HINSTANCE hInstance, int nCmdShow);
	~MsgConfirm();
	void Show();

private:
	LPCWSTR MSG_PTBR = L"Criado Por CYBERWARE.\n\nAVISO:\n"
		L"Este software é um MALWARE que pode causar danos graves, incluindo perda de dados e inutilização do sistema.\n"
		L"O autor não se responsabiliza por quaisquer danos causados.\n\n"
		L"Deseja realmente continuar?";
	LPCWSTR MSG_BUTTONEXIT_PTBR = L"Não, Sair!";
	LPCWSTR MSG_BUTTON2_PTBR = L"Sim, Executar!";

	LPCWSTR MSG_ING = L"Created by CYBERWARE.\n\nWARNING:\n"
		L"This software is MALWARE that can cause severe damage, including data loss and system failure.\n"
		L"The author is not responsible for any damage caused.\n\n"
		L"Do you really want to continue?";
	LPCWSTR MSG_BUTTONEXIT_ING = L"No, Exit!";
	LPCWSTR MSG_BUTTON2_ING = L"Yes, Run!";

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void CreateButtons(HWND hWnd);
	void UpdateText();
	void SwitchLanguage();
	void PaintGradient(HWND hWnd);
	void UpdateGradientColors();

	HWND hWnd;
	HWND buttonTraductor, buttonExitApp, buttonYesOps;
	HWND textWarning;
	bool isPTBR;
	LPCWSTR textBoxWarn;

	int red1, green1, blue1;
	int red2, green2, blue2;
};

MsgConfirm::MsgConfirm(HINSTANCE hInstance, int nCmdShow) : isPTBR(true), textBoxWarn(L"")
{
	red1 = rand() % 255;
	green1 = rand() % 255;
	blue1 = rand() % 255;
	red2 = rand() % 255;
	green2 = rand() % 255;
	blue2 = rand() % 255;

	WNDCLASSW wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"WindowsEffect";
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = NULL;

	RegisterClassW(&wc);

	int windowWidth = 777;
	int windowHeight = 350;

	int screenWidth = GetSystemMetrics(0);
	int screenHeight = GetSystemMetrics(1);

	int xPos = (screenWidth - windowWidth) / 2;
	int yPos = (screenHeight - windowHeight) / 2;

	hWnd = CreateWindowExW(
		WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
		wc.lpszClassName,
		L"Soprano",
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_VISIBLE,
		xPos, yPos, windowWidth, windowHeight,
		nullptr, nullptr, hInstance, this);

	CreateButtons(hWnd);
	UpdateText();

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetTimer(hWnd, 1, 100, nullptr);
}

MsgConfirm::~MsgConfirm()
{
	DestroyWindow(hWnd);
}

void MsgConfirm::CreateButtons(HWND hWnd)
{
	buttonTraductor = CreateWindowW(L"BUTTON", L"Traduzir Para PTBR  |  Translate to ENG",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		210, 12, 267, 32, hWnd, (HMENU)1, nullptr, nullptr);

	buttonExitApp = CreateWindowW(L"BUTTON", MSG_BUTTONEXIT_PTBR,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		96, 224, 122, 82, hWnd, (HMENU)2, nullptr, nullptr);
	SetClassLongPtr(buttonExitApp, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(255, 255, 0)));

	buttonYesOps = CreateWindowW(L"BUTTON", MSG_BUTTON2_PTBR,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		473, 224, 122, 82, hWnd, (HMENU)3, nullptr, nullptr);
	SetClassLongPtr(buttonYesOps, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(255, 0, 0)));

	textWarning = CreateWindowW(L"STATIC", 0,
		WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER,
		10, 60, 740, 150, hWnd, nullptr, nullptr, nullptr);
	SetClassLongPtr(textWarning, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(220, 220, 220)));
	SetWindowTextW(textWarning, textBoxWarn);

	ShowWindow(buttonTraductor, SW_SHOW);
	ShowWindow(buttonExitApp, SW_SHOW);
	ShowWindow(buttonYesOps, SW_SHOW);
}

void MsgConfirm::UpdateText()
{
	if (isPTBR)
	{
		textBoxWarn = MSG_ING;
		SetWindowTextW(buttonExitApp, MSG_BUTTONEXIT_ING);
		SetWindowTextW(buttonYesOps, MSG_BUTTON2_ING);
	}
	else
	{
		textBoxWarn = MSG_PTBR;
		SetWindowTextW(buttonExitApp, MSG_BUTTONEXIT_PTBR);
		SetWindowTextW(buttonYesOps, MSG_BUTTON2_PTBR);
	}

	SetWindowTextW(textWarning, textBoxWarn);
}

void MsgConfirm::SwitchLanguage()
{
	isPTBR = !isPTBR;
	UpdateText();
}

void MsgConfirm::PaintGradient(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	RECT rect;
	GetClientRect(hWnd, &rect);

	TRIVERTEX vertex[2];

	vertex[0].x = rect.left;
	vertex[0].y = rect.top;
	vertex[0].Red = red1 * 256;
	vertex[0].Green = green1 * 256;
	vertex[0].Blue = blue1 * 256;
	vertex[0].Alpha = 0x0000;

	vertex[1].x = rect.right;
	vertex[1].y = rect.bottom;
	vertex[1].Red = red2 * 256;
	vertex[1].Green = green2 * 256;
	vertex[1].Blue = blue2 * 256;
	vertex[1].Alpha = 0x0000;

	GRADIENT_RECT gRect = { 0, 1 };

	GradientFill(hdc, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_V);

	EndPaint(hWnd, &ps);
}

void MsgConfirm::UpdateGradientColors()
{
	red1 = rand() % 256;
	green1 = rand() % 256;
	blue1 = rand() % 256;

	red2 = rand() % 256;
	green2 = rand() % 256;
	blue2 = rand() % 256;

	InvalidateRect(hWnd, nullptr, TRUE);

	Sleep(10);
}

void MsgConfirm::Show()
{
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK MsgConfirm::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static MsgConfirm* pThis;

	if (message == WM_NCCREATE) {
		pThis = static_cast<MsgConfirm*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
		return TRUE;
	}

	switch (message)
	{
	case WM_COMMAND:
		if (LOWORD(wParam) == 1)
		{
			// Button Traductor
			pThis->SwitchLanguage();
		}
		else if (LOWORD(wParam) == 2)
		{
			// Button Exit
			exit(0);
		}
		else if (LOWORD(wParam) == 3)
		{
			PostMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_PAINT:
		pThis->PaintGradient(hWnd);
		break;

	case WM_TIMER:
		pThis->UpdateGradientColors();
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}