﻿#include <iostream>
#include<string>
#include<vector>
#include"mywindows.h"
#include"Functions.h"
#include<math.h>
using namespace std;
void No_Arrival_Time_SJF(vector <Process> &list)
{
    int temp = 0;
    int x = 30, y = 5;
    int AmountTime = Cal_Amount_Time(list);
    for (int i = 0; i < list.size(); i++)//vi da sap xep theo thu tu tang dan roi nen h ta chi can cong vo thoi k can so sanh hay gi het
    {
        if (i != 0)
        {
            temp += list[i - 1].burst;
            list[i].waiting_time = temp;
            list[i].turn = temp + list[i].burst;//cong thuc tinh thoi gian hoan thanh la thoi gian cho + thoi gian burst

        }
        else
        {
            list[i].turn = list[i].burst;//khong can tinh thoi gian cho cua tien trinh dau tien vi no = 0 san roi

        }
        int w = max(4, round(list[i].burst / (AmountTime * 1.0) * 10) * 2 + 1);
        Box_E(x, y, w, 2, 240, list[i].id);
        if (x != 30)
        {
            gotoXY(x + w, y + 3);
            cout << list[i].turn;
        }
        else
        {
            gotoXY(x, y + 3);
            cout << 0;
            gotoXY(x + w, y + 3);
            cout << list[i].turn;
        }
        x += w;
    }
}
void SJF_NonPreempting(vector<Process> &Processes)//Không ưu tiên - Độc quyền
{
    int AmountTime = Cal_Amount_Time(Processes);
    int check_p_running = 0;
    vector<Process>Clone=Copy_Vector(Processes);
    vector<Process> ReadyList;
    vector<int>FlagTime;
    Process P_Running;
    P_Running.remain = 999;
    int x = 30, y = 5;
    int width_tmp = 0;
    for (int timer = 0; timer < AmountTime; timer++)
    {
        if (Clone.size() != 0)
        {
            if (Clone[0].arrive == timer)
            {
                ReadyList.push_back(Clone[0]);
                Clone.erase(Clone.begin());
                Clone.shrink_to_fit();
            }
        }
        if (check_p_running == 0 || P_Running.remain == 0)
        {
            if (P_Running.remain == 0)
            {
                int id = find_index_in_processes(Processes, P_Running.id);

                Processes[id].waiting_time = timer - Processes[id].arrive - Processes[id].burst;
                Processes[id].turn = Processes[id].waiting_time + Processes[id].burst;
            }
            int im = Index_Min_Process_ReadyList(ReadyList);
            P_Running = ReadyList[im];
            ReadyList.erase(ReadyList.begin() + im);
            ReadyList.shrink_to_fit();
            check_p_running = 1;
            int w = max(4, round(P_Running.burst / (AmountTime * 1.0) * 10) * 2 + 1);
            Box_E(x + width_tmp + 1, y, w, 2, 240, P_Running.id);
            gotoXY(x + width_tmp + 1, y + 3);
            cout << timer;
            width_tmp += w;
        }


        P_Running.remain--;
        if (ReadyList.size() == 0 && Clone.size() == 0)
            break;
    }
    int id = find_index_in_processes(Processes, P_Running.id);

    Processes[id].waiting_time =AmountTime - Processes[id].arrive - Processes[id].burst;
    Processes[id].turn = Processes[id].waiting_time + Processes[id].burst;
    gotoXY(x + width_tmp + 1, y + 3);
    cout << AmountTime;
}


void SJF_Preempting(vector<Process> &Processes)//ưu tiên - Khong Độc quyền
{
    int AmountTime = Cal_Amount_Time(Processes);
    int check_p_running = 0;
    int check_ReadyList_Add = 0;
    int timer;
    int x = 30, y = 5;
    int w = 0;
    int width_tmp = 0;
    int id_tmp = 0;
    int id = -1;
    vector<Process>Clone = Copy_Vector(Processes);
    vector<Process> ReadyList;
    Process P_Running;

    P_Running.remain = 9999;
    P_Running.id = 0;
    P_Running.burst = 9999;
    Process tmp = P_Running;

    for (timer = 0; timer < AmountTime; timer++)
    {

        if (Clone.size() != 0)
        {
            if (Clone[0].arrive == timer)
            {
                ReadyList.push_back(Clone[0]); //switch from Prs to RL
                Clone.erase(Clone.begin());
                Clone.shrink_to_fit();
                check_ReadyList_Add = 1;
            }
        }

        if (check_p_running && check_ReadyList_Add)
        {
            ReadyList.push_back(P_Running);
            P_Running = tmp;
            check_p_running = 0;
            check_ReadyList_Add = 0;

        }

        if (check_p_running == 0)
        {
            int im = Index_Min_Process_ReadyList(ReadyList);
            P_Running = ReadyList[im];
            ReadyList.erase(ReadyList.begin() + im);
            ReadyList.shrink_to_fit();
            check_p_running = 1;
            if (id_tmp != P_Running.id)
            {
                w = max(4, round(w / (AmountTime * 1.0) * 10) * 2 + 1);

                Box_E(x, y, w, 2, 240, P_Running.id);
                gotoXY(x, y + 3);
                cout << timer;
                x += w;
                w = 0;
            }
            id_tmp = P_Running.id;
            


        }

        P_Running.remain--;
        w++;
        width_tmp++;
        w = max(4, round(width_tmp / (AmountTime * 1.0) * 10) * 2 + 1);
        if (P_Running.remain == 0)
        {
            check_p_running = 0;
            id = find_index_in_processes(Processes, P_Running.id);
            
            Processes[id].waiting_time = timer + 1 - Processes[id].arrive - Processes[id].burst;
            Processes[id].turn = Processes[id].waiting_time + Processes[id].burst;
        }

        if (ReadyList.size() == 0 && Clone.size() == 0)
            break;
    }
    id = find_index_in_processes(Processes, P_Running.id);

    Processes[id].waiting_time = AmountTime - Processes[id].arrive - Processes[id].burst;
    Processes[id].turn = Processes[id].waiting_time + Processes[id].burst;
    gotoXY(x, y + 3);
    cout << AmountTime;
}
int main()
{
    int n(0);
    resizeConsole(120, 29);
    vector<Process>Processes;
    string nd[5] = { "Nhap Process","SJF Khong Arrival Time","SJF Doc Quyen","SJF Khong Doc Quyen","Dung chuong trinh" };
    int sl = 5;
    int h = 2, w = MaxLengthString(nd, sl) + 2;
    int x = 3, y = 5;
    int xptr = x, yptr = y;
    int xpre = xptr, ypre = yptr;
    int b_color = 240, b_color_bright = 192;
loop:
    SetConsoleTitle(L"Thuat Toan SJF - Team ERROR");
    xptr = x, yptr = y;
    xpre = xptr, ypre = yptr;
    int checkLuaChon = 1;
    ShowCur(0);
    Box(1, 4, 118, 21, b_color, " ");
    Box_E(37, 0, 46, 2, b_color, "Thuat Toan SJF ERROR");
    n_Box_divide(x, y, w, h, b_color, nd, sl);
    while (1)
    {
        if (checkLuaChon)
        {
            gotoXY(xpre, ypre);
            highlight(xpre, ypre, w, h, b_color, nd[Cal(y, ypre, h)]);
            xpre = xptr;
            ypre = yptr;
            highlight(xptr, yptr, w, h, b_color_bright, nd[Cal(y, yptr, h)]);
            checkLuaChon = false;
            SetConsoleTitle(L"Thuat Toan SJF - Team ERROR");
        }if (_kbhit())
        {
            char c = _getch();
            if (c == -32)
            {

                c = _getch();
                if (c == 72)
                {
                    Beep(800, 50);
                    checkLuaChon = true; // đã bấm
                    if (yptr != y)
                        yptr -= h;
                    else
                    {
                        yptr = y + h * (sl - 1);
                    }
                }
                else if (c == 80)
                {
                    Beep(800, 50);
                    checkLuaChon = true; // đã bấm
                    if (yptr != y + h * (sl - 1))
                        yptr += h;
                    else
                    {
                        yptr = y;
                    }
                }
            }
            else if (c == 13)
            {
                int choice = Cal(y, yptr, h);
                if (choice >= 0 && choice < sl - 1)
                {
                    switch (choice)
                    {
                    case 0:
                        Processes = UI_add();
                        n = Processes.size();
                        sort(Processes, 0, n - 1);
                        break;
                    case 1:
                        Processes = UI_add_No_Arr();
                        n = Processes.size();
                        sort_No_Arr(Processes, 0, n - 1);
                        Box(1, 4, 118, 21, b_color, " ");
                        n_Box_divide(x, y, w, h, b_color, nd, sl);
                        No_Arrival_Time_SJF(Processes);
                        PrintProcess(Processes);
                        _getch();
                        break;
                    case 2:
                        SJF_NonPreempting(Processes);
                        PrintProcess(Processes);
                        _getch();
                        break;
                    case 3:
                        SJF_Preempting(Processes);
                        PrintProcess(Processes);
                        _getch();
                        break;
                    default:
                        break;
                    }
                }
                else
                    break;
                checkLuaChon = true;
                goto loop;
            }
        }

    }
    return 0;
}

