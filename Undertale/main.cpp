#include "stdafx.h"

int main()
{
    FRAMEWORK.Init(640, 480, "Undertale");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}