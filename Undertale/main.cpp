#include "stdafx.h"

int main()
{
    FRAMEWORK.SetWindowSize(640, 480);
    FRAMEWORK.Init();
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}