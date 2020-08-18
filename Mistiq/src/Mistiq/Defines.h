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

#ifdef _DEBUG
    #define MSTQ_OPTICK_FRAME(o) OPTICK_FRAME(o);
    #define MSTQ_OPTICK_EVENT(o) OPTICK_EVENT(o);
#else
    #define MSTQ_OPTICK_FRAME(o)
    #define MSTQ_OPTICK_EVENT(o)
#endif