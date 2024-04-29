#ifndef ANDROID_ABI

  #if _WIN64 || __x86_64__ || __ppc64__
    #define YGGDRASIL_EXAMPLE_IDX_64_BITS
  #else
    #define YGGDRASIL_EXAMPLE_IDX_32_BITS
  #endif

#else

  #ifdef ANDROID_ABI=="armeabi-v7a"
    #define YGGDRASIL_EXAMPLE_IDX_32_BITS
  #else
    #define YGGDRASIL_EXAMPLE_IDX_64_BITS
  #endif

#endif
