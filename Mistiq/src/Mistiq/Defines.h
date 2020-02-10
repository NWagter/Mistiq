#pragma once

#ifdef MSTQ_PLATFORM_WINDOWS
    #ifdef MSTQ_BUILD_DLL
        #define MSTQ_API __declspec(dllexport)
    #else
        #define MSTQ_API __declspec(dllimport)
    #endif
#else
    #error Mistiq only supports Windows!
#endif