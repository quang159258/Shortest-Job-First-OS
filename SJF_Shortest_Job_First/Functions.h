﻿#pragma once
#include<string>
#include<iostream>
using namespace std;


        struct Process
        {
            int arrive;
            int id;
            int burst;
            int remain;
            int waiting_time;
            int turn;
        };

int MaxLengthString(string nd[], int sl)
{
    int R = nd[0].length();
    for (int i = 1; i < sl; i++)
        R = R <= nd[i].length() ? nd[i].length() : R;
    return R;
}
int Cal(int y, int yptr, int h)
{
    int R = (yptr - y) / h;
    return R;
}
void swap(Process& a, Process& b)
{
    Process c = a;
    a = b;
    b = c;
}
int isDigit(string a)
{
    if (a[0] == '-')
        a.erase(0, 1);
    for (char c : a)
        if (!isdigit(c))
            return false;
    return true;
}
void sort(vector<Process>& list, int left, int right)
{
    if (left < right)
    {
        int l = left, r = right;
        int pivot = list[(left + right) / 2].arrive;

        while (l <= r)
        {
            while (list[l].arrive < pivot)
                l++;
            while (list[r].arrive > pivot)
                r--;
            if (l <= r)
            {
                swap(list[l], list[r]);
                l++;
                r--;
            }
        }

        if (left < r)
            sort(list, left, r);
        if (l < right)
            sort(list, l, right);
    }
}
void sort_No_Arr(vector<Process>& list, int left, int right)//truyen chi so dau va cuoi cua vector
{
    if (left < right)
    {
        int l = left, r = right;
        int pivot = list[(left + right) / 2].burst;

        while (l <= r)
        {
            while (list[l].burst < pivot)
                l++;
            while (list[r].burst > pivot)
                r--;
            if (l <= r)
            {
                swap(list[l], list[r]);
                l++;
                r--;
            }
        }

        if (left < r)
            sort_No_Arr(list, left, r);
        if (l < right)
            sort_No_Arr(list, l, right);
    }
}
int Cal_Amount_Time(vector<Process> Processes)
{
    int n = Processes.size();
    int R(0);
    for (int i = 0; i < n; i++)
        R += Processes[i].burst;
    return R;
}
int Index_Min_Process_ReadyList(vector<Process> ReadyList)
{
    int n = ReadyList.size();
    int min = 9999;
    int im = -1;
    for (int i = 0; i < n; i++)
    {
        if (min > ReadyList[i].burst)
        {
            min = ReadyList[i].burst;
            im = i;
        }
    }
    return im;
}
vector<Process> UI_add()
{
    ShowCur(1);
    Box(1, 4, 118, 21, 240, " ");
    string n_str;
    int n_i;
    int x = 3, y = 5;
    while (1)
    {
        gotoXY(x, y);
        clreol();
        cout << "Nhap so tien trinh: ";
        getline(cin, n_str);
        if (n_str != "")
            if (isDigit(n_str) && stoi(n_str) > 0)
            {
                n_i = stoi(n_str);
                break;
            }
    }
    vector<Process> L;
    L.resize(n_i);
    int tmp_length(0);
    int xpre(0);
    int min = 999;
    for (int i = 0; i < n_i; i++)
    {
        L[i].id = i + 1;
        gotoXY(x + 5, y + 1);
        cout << "Nhap tien trinh p" << i + 1;
        gotoXY(x + 5, y + 2);
        cout << "Arrival Time";
        gotoXY(x + 20, y + 2);
        cout << "Burst Time";
        while (1)
        {
            gotoXY(x, y + 3);
            cout << "Nhap:                                                                          ";
            gotoXY(x + 5, y + 3);
            getline(cin, n_str);
            if (n_str != "")
                if (isDigit(n_str) && stoi(n_str) >= 0)
                {
                    L[i].arrive = stoi(n_str);
                    min = min < L[i].arrive ? min : L[i].arrive;
                    break;
                }
        }
        
        while (1)
        {
            gotoXY(x + 20, y + 3);
            getline(cin, n_str);
            if (n_str != "")
                if (isDigit(n_str) && stoi(n_str) > 0)
                {
                    L[i].burst = stoi(n_str);
                    L[i].remain = L[i].burst;
                    break;
                }
        }
    }
    for (int i = 0; i < n_i; i++)
        L[i].arrive -= min;
    ShowCur(0);
    return L;
}
vector<Process> UI_add_No_Arr()
{
    ShowCur(1);
    Box(1, 4, 118, 21, 240, " ");
    string n_str;
    int n_i;
    int x = 3, y = 5;
    while (1)
    {
        gotoXY(x, y);
        clreol();
        cout << "Nhap so tien trinh: ";
        getline(cin, n_str);
        if (n_str != "")
            if (isDigit(n_str) && stoi(n_str) > 0)
            {
                n_i = stoi(n_str);
                break;
            }
    }
    vector<Process> L;
    L.resize(n_i);
    int tmp_length(0);
    int xpre(0);
    for (int i = 0; i < n_i; i++)
    {
        L[i].id = i + 1;
        gotoXY(x + 5, y + 1);
        cout << "Nhap tien trinh p" << i + 1;
        gotoXY(x + 5, y + 2);
        cout << "Burst Time:                  ";
        while (1)
        {
            gotoXY(x + 17, y + 2);
            getline(cin, n_str);
            if (n_str != "")
                if (isDigit(n_str) && stoi(n_str) > 0)
                {
                    L[i].burst = stoi(n_str);
                    break;
                }
        }
    }
    ShowCur(0);
    return L;
}
int find_index_in_processes(vector <Process> Proccesses, int im)
{
    int size = Proccesses.size();;
    for (int i = 0; i < size; i++)
    {
        if (im == Proccesses[i].id)
            return i;
    }
}
void Cal_waiting_turn(Process &P,int time)
{
        P.waiting_time = time - P.arrive-P.burst;
        P.turn = P.waiting_time + P.burst;
}
vector<Process> Copy_Vector(vector<Process> Processes)
{
    vector<Process>Clone;
    for (int i = 0; i < Processes.size(); i++)
        Clone.push_back(Processes[i]);
    return Clone;
}
void EraseVector(vector<Process>& Processes, vector<Process>::iterator p)
{
    Processes.erase(p);
    Processes.shrink_to_fit();
}
void PrintProcess(vector<Process> Processes)
{
    int x = 26, y = 10;
    int n = Processes.size();
    Box(x+4, y, 50,  n+1, 240, " ");
    gotoXY(x + 10, y);
    cout << "Arrival";
    gotoXY(x + 20, y);
    cout << "Burst";
    gotoXY(x + 30, y);
    cout << "Waiting";
    gotoXY(x + 40, y++);
    cout << "Turn Around";
    for (int i = 0; i < n; i++)
    {
        gotoXY(x + 5, y);
        cout << "P" << Processes[i].id;
        gotoXY(x + 10, y);
        cout << Processes[i].arrive;
        gotoXY(x + 20, y);
        cout << Processes[i].burst;
        gotoXY(x + 30, y);
        cout <<  Processes[i].waiting_time;
        gotoXY(x + 40, y);
        cout <<  Processes[i].turn;
        y += 1;
    }
}
void init_P0(Process& p0, vector<Process> Processes,int timer)
{
    p0.id = 0;
    p0.burst = Processes[0].arrive-timer;
    p0.remain = Processes[0].arrive - timer;
}