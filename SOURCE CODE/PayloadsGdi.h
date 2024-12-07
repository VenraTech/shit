typedef struct IUnknown IUnknown;

#pragma once

#include "soprano.h"

namespace PayloadsGdi
{
	VOID ClearEffect(void)
	{
		RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
	}

	DWORD WINAPI Load1(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = -h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		VOID* ppvBits;
		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, &ppvBits, NULL, 0);
		SelectObject(dcCopy, bmp);

		double time = 0.0;
		double radius = 0.0;
		while (1)
		{
			RGBQUAD* rgbquad = (RGBQUAD*)ppvBits;
			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;
					double angle = atan2(y - h / 2.0, x - w / 2.0);
					radius = sqrt((x - w / 2.0) * (x - w / 2.0) + (y - h / 2.0) * (y - h / 2.0));
					double wave = sin(angle * 5.0 + time) * 0.5 + 0.5;

					rgbquad[index].rgbRed = (BYTE)(sin(radius * 0.1 + time) * 128 + 128);
					rgbquad[index].rgbGreen = (BYTE)((rand() % 2 == 0 ? sin(angle * 21.0 + time + 2.0) : cos(angle * 5.0 + time + 2.0)) * 322 + 128);
					rgbquad[index].rgbBlue = (BYTE)(sin(angle * 5.0 + time + 4.0) * 128 + 128);
				}
			}
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
			Sleep(50);
			time += 0.1;
		}
		DeleteObject(bmp);
		ReleaseDC(NULL, dc);
		DeleteDC(dcCopy);
		return 0;
	}


	DWORD WINAPI Load2(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = -h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		VOID* ppvBits;
		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, &ppvBits, NULL, 0);
		SelectObject(dcCopy, bmp);

		double time = 0.0;
		while (1)
		{
			RGBQUAD* rgbquad = (RGBQUAD*)ppvBits;
			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;
					double distance = sqrt((x + w / 222) * (x + w / 222) + (y + h / 222) * (y + h / 32.0));
					double wave = sin(distance * 0.1 - time);
					rgbquad[index].rgbRed = (BYTE)(sin(time * x * 0.05) * 211 + 128);
					rgbquad[index].rgbGreen = (BYTE)(sin(time - y * 0.05) * 128 - 128);
					rgbquad[index].rgbBlue = (BYTE)(sin(time * x * 32) * 128 + 128);
				}
			}
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
			Sleep(50);
			time += 0.1;
		}
		DeleteObject(bmp);
		ReleaseDC(NULL, dc);
		DeleteDC(dcCopy);
		return 0;

	}


	DWORD WINAPI Load3(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = -h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		VOID* ppvBits;
		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, &ppvBits, NULL, 0);
		SelectObject(dcCopy, bmp);

		double time = 0.0;
		while (1)
		{
			RGBQUAD* rgbquad = (RGBQUAD*)ppvBits;
			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;
					double wave = sin((x - time) * 0.05);
					rgbquad[index].rgbRed = (BYTE)((sin(time + x * 0.1) * 127 + 128) * wave);
					rgbquad[index].rgbGreen = (BYTE)((sin(time + y * 0.1) * 127 + 128) * wave);
					rgbquad[index].rgbBlue = (BYTE)((sin(time + x * 0.1) * 127 + 128) * wave);
				}
			}
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
			Sleep(50);
			time += 0.1;
		}
		DeleteObject(bmp);
		ReleaseDC(NULL, dc);
		DeleteDC(dcCopy);
		return 0;

	}

	DWORD WINAPI Load4(LPVOID lpvd)
	{
		while (1)
		{
			HDC dc = GetDC(NULL);
			HDC dcCopy = CreateCompatibleDC(dc);
			int w = GetSystemMetrics(0);
			int h = GetSystemMetrics(1);

			for (int e = 32; e <= 44239; e++)
			{
				BitBlt(dc, rand() % e, rand() % 2, w, h, dc, rand() % 32, rand() % e, SRCERASE);
				BitBlt(dc, rand() % e, rand() % e, 30 + w, h, dc, rand() % 32, rand() % 40, SRCCOPY);
				BitBlt(dc, rand() % e, rand() % 2, w, h, dc, rand() % 32, rand() % e, SRCINVERT);
				e--;  // :D
			}

			Sleep(50);
		}

		return 0;
	}

	DWORD WINAPI Load5(LPVOID lpvd)
	{
		while (1)
		{
			HDC dc = GetDC(NULL);
			HDC dcCopy = CreateCompatibleDC(dc);
			int w = GetSystemMetrics(0);
			int h = GetSystemMetrics(1);

			POINT pt;
			GetCursorPos(&pt);
			DrawIcon(dc, pt.x, pt.y, LoadIcon(0, IDI_ERROR));

			HWND deskt = GetDesktopWindow();
			RECT rec;
			GetWindowRect(deskt, &rec);
			int x = rec.right - rec.left;
			int y = rec.bottom - rec.top;

			StretchBlt(dc, -12.5, +12.5, x + 25, y - 25, dc, 0, 0, x, y, SRCCOPY);
			StretchBlt(dc, +13, +13, x - 25, y - 25, dc, 0, 0, x, y, SRCCOPY);
			BitBlt(dc, 32, 0, x, y, dc, 0, 32, 0x111111);
			BitBlt(dc, 1, 0, x, y, dc, 0, 32, 0x111111);

			Sleep(1);
		}

		return 0;
	}

	DWORD WINAPI LoadIconEffect(LPVOID lp)
	{
		while (1)
		{
			for (int i = 0; i <= 1000; i++)
			{
				HDC dc = GetDC(NULL);
				HDC dcCopy = CreateCompatibleDC(dc);
				int w = GetSystemMetrics(0);
				int h = GetSystemMetrics(1);

				CURSORINFO curinf;
				DrawIcon(dc, rand() % w, rand() % h, LoadIcon(0, IDI_ERROR));
				DrawIcon(dc, rand() % w, rand() % h, LoadIcon(0, IDI_APPLICATION));
				DrawIcon(dc, rand() % w, rand() % h, LoadIcon(0, IDI_WARNING));
				DrawIcon(dc, rand() % w, rand() % h, LoadIcon(0, IDI_ASTERISK));
				DrawIcon(dc, rand() % w, rand() % h, LoadIcon(0, IDI_INFORMATION));

				GetCursorInfo(&curinf);
				curinf.cbSize = sizeof(curinf);
				DrawIcon(dc, curinf.ptScreenPos.x, curinf.ptScreenPos.y, curinf.hCursor);


				Sleep(80);

				if (i == 1000)
					ClearEffect();
			}
		}
		return 0;
	}

	DWORD WINAPI Load6(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);

		BITMAPINFO bmpi = { 0 };
		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = -h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		VOID* ppvBits;
		HBITMAP hBitmap = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, &ppvBits, NULL, 0);
		SelectObject(dcCopy, hBitmap);

		int radius = 50;

		while (1)
		{
			StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, h, SRCCOPY);

			RGBQUAD* rgbquad = (RGBQUAD*)ppvBits;

			int centerX = w / 2;
			int centerY = h / 2;

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int dx = x - centerX;
					int dy = y - centerY;
					double distance = sqrt(dx * dx * dy * dy);

					if (distance <= radius)
					{
						int index = y * w + x;
						BYTE transparency = (BYTE)((distance / radius) * 255);
						rgbquad[index].rgbReserved = transparency;
					}
				}
			}

			BLENDFUNCTION blendFunction = { 0 };
			blendFunction.BlendOp = AC_SRC_OVER;
			blendFunction.BlendFlags = 0;
			blendFunction.SourceConstantAlpha = 100;
			blendFunction.AlphaFormat = AC_SRC_ALPHA;

			AlphaBlend(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, blendFunction);

			radius += 1000;
			if (radius > 80000)
			{
				ClearEffect();
				Sleep(300);
				radius = 0;
			}
		}

		DeleteObject(hBitmap);
		DeleteDC(dcCopy);
		ReleaseDC(NULL, dc);
		return 0;
	}
}
