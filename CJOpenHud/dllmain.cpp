// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "CJOpenHud.h"
#include <thread>

int main()
{
    CJOpenHud inst_hud;
    //wait for the flag for exit to be set
    while (!inst_hud.exit)
        Sleep(500);
    //when this function returns the destructor of main will be called and all of the singletons inside it will also be destroyed and deconstructed
    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        //create a thread and detach it so anything we do inside of main is non-blocking for the loading thread
        std::thread main_thread(main);
        main_thread.detach();
        break;
    }
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        CJOpenHud::get_instance()->exit = true;
        break;
    }
    return TRUE;
}

