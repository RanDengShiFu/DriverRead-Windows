// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Interface.hpp"

//BUG反馈：QQ群 943445569

int main(int argc, char* argv[])
{
    //注意驱动注入 只目前只支持64位dll的注入64位进程

    //64位初始化接口
    if (InitInterface("DriverCore_x64.dll"))
    {
        printf("驱动接口初始化成功\n");
    }
    else
    {
        printf("接口初始化失败\n");
        system("pause");
        return 0;
    }

    //32位初始化接口
    //if (InitInterface("DriverCore_x32.dll"))
    //{
    //    printf("驱动接口初始化成功\n");
    //}
    //else
    //{
    //    printf("接口初始化失败\n");
    //    system("pause");
    //    return 0;
    //}

    //登录例子
    char m_key[MAX_PATH] = "sahduwdsawdwdwdwdfgvdsdhu";
    if (kernel_driverlogin(m_key))
    {
        printf("驱动加载\r\n");
    }
    else
    {
        printf("驱动加载失败\r\n");
        system("pause");
        return 0;
    }

    //dwm例子
    char dwmkey[] = { 'd', 's', 'j', 'a', 'o', 'i', 'h', 'd', 'f', 'w', 'o', '3', 'i', 'd', 'w', 'd', 'a', 's', 'd', 'w', '\0' };
    if (Dwm_Init(dwmkey))
    {
        printf("DWM Open Sucess!\r\n");
    }
    else
    {
        printf("DWM Open Fail!\r\n");
    }

    Dwm_OpenDraw();
    while (true)
    {
        DWORD value = 0;
        kernel_readmem(GetCurrentProcessId(), GetModuleHandleA(NULL), &value, sizeof(value));
        ImVec4 Color0(0, 0, 100, 100);
        ImVec4 Color1(100, 100, 50, 50);
        Dwm_DrawLine(100, 100, 200, 200, Color0, 5);
        Dwm_DrawLine(200, 100, 300, 500, Color1, 5);
        Dwm_DrawTextStr(50, 50, Color0, true, "%s", "龟哥");
        Dwm_DrawText(150, 150, Color1, true, "TEST AAAAAAAA");
        Dwm_DrawTextSize(10.0f, ImVec2(400, 100), ImVec4(0, 1, 0, 1), "测试");
        Dwm_UpDataDraw();
    }

    system("pause");
    return 0;
}