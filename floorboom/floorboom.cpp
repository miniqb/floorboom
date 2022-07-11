#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <stdio.h>

typedef struct
{
    int h, w, sum,score;
} DATA;

IMAGE f, f1, boom, qr[4], e[10], back, menu, lv[5], bom[10], winb[10],Aphrodite;
LOGFONT font;
short note[20][35];
short opcl[20][35], rf[20][35];
COORD bomdata[100];
int flength;
int click;
int level;
int num;
DATA data[5] = { {9,9,10,71},{9,12,20,88},{9,16,30,114},{16,16,50,206},{16,30,99,381} };
TCHAR tip[5][20] = { TEXT("小菜一碟~"),TEXT("不过如此！"), TEXT("小有成就！"),TEXT("炉火纯青！"),TEXT("登峰造极！！")};
void Load();
void Initialze();
void Sett();
void Menu();
void Open(int x, int y);
void  Endf(int x, int y);
void Endw();

int main()
{
    int ox = 0, oy = 0;
    int x, y, tx, ty;
    int nSelect;
    TCHAR numm[5];
    Load();
    flength = f.getheight();
    MOUSEMSG m;
    MessageBox(NULL, TEXT("欢迎！"), TEXT("Welcome!"), MB_OK);
LOOP:
    Menu();
    Initialze();
ROOP:
    initgraph(data[level].w*flength+100, data[level].h*flength);
    Sett();
    for (int i = 0; i < flength*data[level].w; i+= flength)
    {
        for(int j=0;j< flength * data[level].h;j+= flength)
            putimage(i, j, &f);
    }
   
    while (true)
    {
        _stprintf_s(numm, TEXT("%d"), num);
        clearrectangle(data[level].w * flength + 40, data[level].h * flength / 3 + 32, data[level].w * flength + 80, data[level].h * flength / 3 + 50);
        outtextxy(data[level].w * flength+40, data[level].h * flength/3+32, numm);
        m = GetMouseMsg();
        if (click == data[level].score)
        {
            Endw();
            memset(note, 0, sizeof(note));
            nSelect = MessageBox(NULL, tip[level], TEXT("THE END"), MB_OK );
            if (nSelect == IDOK)
            {
                FlushMouseMsgBuffer();
                goto LOOP;
            }
        }
        switch (m.uMsg)
        {
        case WM_MOUSEMOVE:
            if (m.x >= data[level].w * flength || m.y >= data[level].h * flength||m.x<=0||m.y<=0)
            {
                if (!opcl[oy / flength + 1][ox / flength + 1] && !rf[oy / flength + 1][ox / flength + 1] && ox / flength <= data[level].w)
                        putimage(ox, oy, &f);
                break;
            }
            if (!(opcl[(m.y / flength) + 1][(m.x / flength) + 1]))
            {
                if (rf[m.y / flength + 1][m.x / flength + 1] == 0)
                    putimage((m.x / flength) * flength, (m.y / flength) * flength, &f1);
                else if (rf[m.y / flength + 1][m.x / flength + 1] == 2)
                    putimage((m.x / flength) * flength, (m.y / flength) * flength, &qr[2]);
            }
            if (((ox != (m.x / flength) * flength) || (oy != (m.y / flength) * flength)))
            {
                if (!opcl[oy / flength + 1][ox / flength + 1] && ox / flength <= data[level].w)
                {
                    if (rf[oy / flength + 1][ox / flength + 1] == 0)
                        putimage(ox, oy, &f);
                    else if (rf[oy / flength + 1][ox / flength + 1] == 2)
                        putimage(ox, oy, &qr[3]);
                }
                ox = (m.x / flength) * flength, oy = (m.y / flength) * flength;
            }
            break;
        case WM_LBUTTONUP:
            if (m.x >= data[level].w * flength || m.y >= data[level].h * flength) break;
            x = (m.x / flength), y = (m.y / flength);
            if (rf[y + 1][x + 1] == 1||opcl[y+1][x+1]==1) break;
            if (note[y + 1][x + 1] == 9)
            {
                Endf(x, y);
                nSelect = MessageBox(NULL, TEXT("哈哈  想重新开始本盘游戏吗？"), TEXT("THE END"), MB_RETRYCANCEL);
                if (nSelect == IDCANCEL)
                {
                    FlushMouseMsgBuffer();
                    memset(note, 0, sizeof(note));
                    goto LOOP;
                }
                else
                {
                    FlushMouseMsgBuffer();
                    goto ROOP;
                }
                closegraph();
                return 0;
            }
            Open(x, y);
            break;
        case WM_RBUTTONUP:
            if (m.x >= data[level].w * flength || m.y >= data[level].h * flength) break;
            tx = (m.x / flength), ty = (m.y / flength);
            if (opcl[ty + 1][tx + 1] == 1) break;
            rf[ty+1][tx+1]++;
            if (rf[ty + 1][tx + 1] == 1)
                num--;
            else if (rf[ty + 1][tx + 1] == 2)
                num++;
            if (rf[ty+1][tx+1] == 3) 
                rf[ty+1][tx+1] = 0;
            putimage(tx * flength, ty * flength, &qr[rf[ty+1][tx+1]]);
            break;
        }
    }
    closegraph();
}

void Load()
{
    loadimage(&f, TEXT("f.yjl"));
    loadimage(&f1, TEXT("f1.yjl"));
    loadimage(&e[9], TEXT("boom.yjl"));
    loadimage(&e[0], TEXT("e0.yjl"));
    loadimage(&e[1], TEXT("e1.yjl"));
    loadimage(&e[2], TEXT("e2.yjl"));
    loadimage(&e[3], TEXT("e3.yjl"));
    loadimage(&e[4], TEXT("e4.yjl"));
    loadimage(&e[5], TEXT("e5.yjl"));
    loadimage(&e[6], TEXT("e6.yjl"));
    loadimage(&e[7], TEXT("e7.yjl"));
    loadimage(&e[8], TEXT("e8.yjl"));
    loadimage(&qr[0], TEXT("f1.yjl"));
    loadimage(&qr[1], TEXT("r.yjl"));
    loadimage(&qr[2], TEXT("q1.yjl"));
    loadimage(&qr[3], TEXT("q.yjl"));
    loadimage(&lv[0], TEXT("lv0.yjl"));
    loadimage(&lv[1], TEXT("lv1.yjl"));
    loadimage(&lv[2], TEXT("lv2.yjl"));
    loadimage(&lv[3], TEXT("lv3.yjl"));
    loadimage(&lv[4], TEXT("lv4.yjl"));
    loadimage(&menu, TEXT("menu.yjl"));
    loadimage(&boom, TEXT("boom0.yjl"));
    loadimage(&bom[0], TEXT("boom.yjl"));
    loadimage(&bom[1], TEXT("bom1.yjl"));
    loadimage(&bom[2], TEXT("bom2.yjl"));
    loadimage(&bom[3], TEXT("bom3.yjl"));
    loadimage(&bom[4], TEXT("bom4.yjl"));
    loadimage(&bom[5], TEXT("bom5.yjl"));
    loadimage(&bom[6], TEXT("bom6.yjl"));
    loadimage(&bom[7], TEXT("bom7.yjl"));
    loadimage(&winb[0], TEXT("winb0.yjl"));
    loadimage(&winb[1], TEXT("winb1.yjl"));
    loadimage(&winb[2], TEXT("winb2.yjl"));
    loadimage(&winb[3], TEXT("winb3.yjl"));
    loadimage(&winb[4], TEXT("winb4.yjl"));
}

void Sett()
{
    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 2);
    setlinecolor(RGB(67, 116, 87));
    setbkcolor(RGB(210, 211, 192));
    cleardevice();
    line(data[level].w * flength + 1, 0, data[level].w * flength + 1, data[level].h * flength);
    settextcolor(RGB(88, 88, 88));
    gettextstyle(&font);						
    font.lfHeight = 23;					
    _tcscpy_s(font.lfFaceName, _T("微软雅黑"));	
    font.lfQuality = PROOF_QUALITY;	
    settextstyle(&font);			
    putimage(data[level].w * flength + 35, data[level].h * flength / 3, &boom);
}

void Initialze()
{
    int x, y, sum = 0;
    srand((unsigned)time(NULL));
    for (int i = 0; i <data[level].sum; i++)
    {
        x = rand() % data[level].w + 1;
        y = rand() % data[level].h + 1;
        while (note[y][x])
        {
            x = rand() % data[level].w + 1;
            y = rand() % data[level].h + 1;
        }
        note[y][x] = 9;
        bomdata[i].X = x;
        bomdata[i].Y = y;
    }
    for (int i = 1; i <= data[level].h; i++)
    {
        for (int j = 1; j <= data[level].w; j++)
        {
            if (note[i][j]!=9)
            {
                if (note[i][j + 1]==9)
                    note[i][j]++;
                if (note[i][j - 1]==9)
                    note[i][j]++;
                if (note[i + 1][j + 1]==9)
                    note[i][j]++;
                if (note[i + 1][j - 1]==9)
                    note[i][j]++;
                if (note[i + 1][j]==9)
                    note[i][j]++;
                if (note[i - 1][j]==9)
                    note[i][j]++;
                if (note[i - 1][j - 1]==9)
                    note[i][j]++;
                if (note[i - 1][j + 1]==9)
                    note[i][j]++;
            }
        }
    }
}

void Menu()
{
    int f = 0;
    initgraph(400, 500);
    putimage(0, 0, &menu);
    MOUSEMSG m;
    while (true)
    {
        m = GetMouseMsg();
        switch (m.uMsg)
        {
        case WM_MOUSEMOVE:
            if (m.x >= 75 && m.x <= (f ? 325 : 155))
            {
                if (m.y >= 90 && m.y <= 130)
                {
                    f = 1;
                    putimage(0, 0, &menu);
                    putimage(155, 90, &lv[0]);
                }
                else if (m.y >= 160 && m.y <= 200)
                {
                    f = 1;
                    putimage(0, 0, &menu);
                    putimage(155, 160, &lv[1]);
                }
                else if (m.y >= 230 && m.y <= 270)
                {
                    f = 1;
                    putimage(0, 0, &menu);
                    putimage(155, 230, &lv[2]);
                }
                else if (m.y >= 300 && m.y <= 340)
                {
                    f = 1;
                    putimage(0, 0, &menu);
                    putimage(155, 300, &lv[3]);
                }
                else if (m.y >= 370 && m.y <= 410)
                {
                    f = 1;
                    putimage(0, 0, &menu);
                    putimage(155, 370, &lv[4]);
                }
                else
                {
                    f = 0;
                    putimage(0, 0, &menu);
                }
            }
            else
            {
                f = 0;
                putimage(0, 0, &menu);
            }
            break;
        case WM_LBUTTONUP:
            if (m.x >= 75 && m.x <= (f ? 325 : 155))
            {
                if (m.y >= 90 && m.y <= 130)
                {
                    level = 0;
                    num = data[level].sum;
                    return;
                }
                else if (m.y >= 160 && m.y <= 200)
                {
                    level = 1;
                    num = data[level].sum;
                    return;
                }
                else if (m.y >= 230 && m.y <= 270)
                {
                    level = 2;
                    num = data[level].sum;
                    return;
                }
                else if (m.y >= 300 && m.y <= 340)
                {
                    level = 3;
                    num = data[level].sum;
                    return;
                }
                else if (m.y >= 370 && m.y <= 410)
                {
                    level = 4;
                    num = data[level].sum;
                    return;
                }
                else
                {
                    f = 0;
                    putimage(0, 0, &menu);
                }
            }
            break;
        }
    }
}

void Open(int x,int y)
{
    if (note[y + 1][x + 1] != 0 || y + 1 == 0 || y  == data[level].h || x + 1 == 0 || x  == data[level].w || rf[y + 1][x + 1] == 1|| opcl[y + 1][x + 1] == 1)
    {
        if (rf[y + 1][x + 1] == 1 || y + 1 == 0 || y  == data[level].h || x + 1 == 0 || x == data[level].w || opcl[y + 1][x + 1] == 1)
        {
            return;
        }
        else
        {
            if (opcl[y + 1][x + 1] == 0) click++;
            opcl[y + 1][x + 1] = 1;
            putimage(x * flength, y * flength, &e[note[y + 1][x + 1]]);
            return;
        }
    }
    if (note[y + 1][x + 1] == 0)
    {
        if (opcl[y + 1][x + 1] == 0) click++;
        opcl[y + 1][x + 1] = 1;
        putimage(x * flength, y * flength, &e[note[y + 1][x + 1]]);
    }
    Open(x, y - 1);
    Open(x + 1, y);
    Open(x, y + 1);
    Open(x - 1, y);
    Open(x - 1, y - 1);
    Open(x + 1, y - 1);
    Open(x - 1, y + 1);
    Open(x + 1, y + 1);
}

void Endf(int x, int y)
{
    putimage(x * flength, y * flength, &e[note[y + 1][x + 1]]);
    for (int i = 0; i < 8; i++)
    {
        putimage(x * flength, y * flength, &bom[i]);
        Sleep(70);
    }
    Sleep(1000);
    BeginBatchDraw();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < data[level].sum; j++)
        {
            if (bomdata[j].X-1 == x && bomdata[j].Y-1 == y) continue;
            putimage((bomdata[j].X - 1) * flength, (bomdata[j].Y - 1) * flength, &bom[i]);
        }
        FlushBatchDraw();
        Sleep(70);
        if (i == 0) Sleep(1000);
    }
    EndBatchDraw();
    Sleep(500);
    memset(opcl, 0, sizeof(opcl));
    memset(rf, 0, sizeof(rf));
    click = 0;
    num = data[level].sum;
    FlushMouseMsgBuffer();
}

void Endw()
{
    Sleep(200);
    BeginBatchDraw();
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < data[level].sum; j++)
        {
            putimage((bomdata[j].X - 1) * flength, (bomdata[j].Y - 1) * flength, &winb[i]);
        }
        FlushBatchDraw();
        Sleep(90);
    }
    EndBatchDraw();
    Sleep(500);
    memset(opcl, 0, sizeof(opcl));
    memset(rf, 0, sizeof(rf));
    click = 0;
    num = data[level].sum;
    FlushMouseMsgBuffer();
}

