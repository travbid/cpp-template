#pragma once

#if defined _WIN32 || defined __CYGWIN__
   #ifdef CPPSAMPLE_BUILD
      #define EXPORT __declspec(dllexport)
   #else
      #define EXPORT __declspec(dllimport)
   #endif
#else
   #define EXPORT __attribute__ ((visibility ("default")))
#endif
