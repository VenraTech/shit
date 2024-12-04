#include "soprano.h"
#define PI 3.14159265358979

namespace PolygonsFormsGdi
{
    typedef struct { float x; float y; float z; } VERTEX;
    typedef struct { int vtx0; int vtx1; } EDGE;

    VOID RotateX(VERTEX* vtx, float angle)
    {
        vtx->y = cos(angle) * vtx->y - sin(angle) * vtx->z;
        vtx->z = sin(angle) * vtx->y + cos(angle) * vtx->z;
    }

    VOID RotateY(VERTEX* vtx, float angle)
    {
        vtx->x = cos(angle) * vtx->x + sin(angle) * vtx->z;
        vtx->z = -sin(angle) * vtx->x + cos(angle) * vtx->z;
    }

    VOID RotateZ(VERTEX* vtx, float angle)
    {
        vtx->x = cos(angle) * vtx->x - sin(angle) * vtx->y;
        vtx->y = sin(angle) * vtx->x + cos(angle) * vtx->y;
    }

    void DrawEdge(HDC dc, LPCWSTR icon, int x0, int y0, int x1, int y1, int r)
    {
        int dx = abs(x1 - x0);
        int dy = -abs(y1 - y0);

        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;

        int error = dx - dy;

        int i = 0;

        while (true)
        {
            if (i == 0)
            {
                DrawIcon(dc, x0, y0, LoadIcon(NULL, icon));
                i = 10;
            }
            else
            {
                i--;
            }

            if (x0 == x1 && y0 == y1)
            {
                break;
            }

            int e2 = 2 * error;

            if (e2 >= dy)
            {
                if (x0 == x1)
                {
                    break;
                }

                error += dy;
                x0 += sx;
            }

            if (e2 <= dx)
            {
                if (y0 == y1)
                {
                    break;
                }

                error += dx;
                y0 += sy;
            }
        }
    }

    DWORD WINAPI Hexagon(LPVOID lpvd)
    {
        float size = (PayloadsGdi::w + PayloadsGdi::h) / 10;
        float radius = size / 2;

        int cx = size;
        int cy = size;

        int xdv = 10;
        int ydv = 10;

        float angleX = 0.01;
        float angleY = 0.01;
        float angleZ = 0.01;

        VERTEX vtx[6];
        for (int i = 0; i < 6; i++) {
            float angle = (PI / 3) * i;
            vtx[i].x = radius * cos(angle);
            vtx[i].y = radius * sin(angle);
            vtx[i].z = 0;
        }

        EDGE edges[] =
        {
            {0, 1},
            {1, 2},
            {2, 3},
            {3, 4},
            {4, 5},
            {5, 0}
        };

        LPCWSTR icons[] = { IDI_ERROR, IDI_EXCLAMATION, IDI_ASTERISK, IDI_APPLICATION };

        int index = rand() % 4;

        int totvtx = sizeof(vtx) / sizeof(vtx[0]);
        int totedg = sizeof(edges) / sizeof(edges[0]);

        while (true)
        {
            for (int i = 0; i < totvtx; i++)
            {
                RotateX(&vtx[i], angleX);
                RotateY(&vtx[i], angleY);
                RotateZ(&vtx[i], angleZ);
            }

            for (int i = 0; i < totedg; i++)
            {
                DrawEdge(PayloadsGdi::dc, icons[index],
                    vtx[edges[i].vtx0].x + cx, vtx[edges[i].vtx0].y + cy,
                    vtx[edges[i].vtx1].x + cx, vtx[edges[i].vtx1].y + cy, 20);
            }

            Sleep(40);
            if (rand() % 5 == 0) System::cls();

            cx += xdv;
            cy += ydv;

            if (cx > PayloadsGdi::w - (size / 2) || cx < -(size / 2))
            {
                xdv *= -1;
                index = rand() % 4;
            }

            if (cy > PayloadsGdi::h - (size / 2) || cy < -(size / 2))
            {
                ydv *= -1;
                index = rand() % 4;
            }
        }

        return 0;
    }

    DWORD WINAPI Triangle(LPVOID lpvd)
    {
        float size = (PayloadsGdi::w + PayloadsGdi::h) / 10;

        int cx = size;
        int cy = size;

        int xdv = 10;
        int ydv = 10;

        float angleX = 0.01;
        float angleY = 0.01;
        float angleZ = 0.01;

        VERTEX vtx[] =
        {
            {size, 0, 0},
            {size / 2, size, 0},
            {0, 0, 0}
        };

        EDGE edges[] =
        {
            {0, 1},
            {1, 2},
            {2, 0}
        };

        LPCWSTR icons[] = { IDI_ERROR, IDI_EXCLAMATION, IDI_ASTERISK, IDI_APPLICATION };

        int index = rand() % 4;

        int totvtx = sizeof(vtx) / sizeof(vtx[0]);
        int totedg = sizeof(edges) / sizeof(edges[0]);

        while (true)
        {
            for (int i = 0; i < totvtx; i++)
            {
                RotateX(&vtx[i], angleX);
                RotateY(&vtx[i], angleY);
                RotateZ(&vtx[i], angleZ);
            }

            for (int i = 0; i < totedg; i++)
            {
                DrawEdge(PayloadsGdi::dc, icons[index],
                    vtx[edges[i].vtx0].x + cx, vtx[edges[i].vtx0].y + cy,
                    vtx[edges[i].vtx1].x + cx, vtx[edges[i].vtx1].y + cy, 20);
            }

            Sleep(40);
            if (rand() % 5 == 0) System::cls();

            cx += xdv;
            cy += ydv;

            if (cx > PayloadsGdi::w - (size / 2) || cx < -(size / 2))
            {
                xdv *= -1;
                index = rand() % 4;
            }

            if (cy > PayloadsGdi::h - (size / 2) || cy < -(size / 2))
            {
                ydv *= -1;
                index = rand() % 4;
            }
        }

        return 0;
    }
}