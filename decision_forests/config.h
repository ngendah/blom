// https://sourceforge.net/p/predef/wiki/Architectures/
#ifndef ANDROID_ABI

  #if defined(__x86_64__) || defined(__x86_64) || \
    defined(__amd64__) || defined(__amd64) || \
    defined(_M_X64) || defined(_M_AMD64) || \
    defined(__arm64) || defined(__arm64__) || \
    defined(_M_ARM64) || defined(__aarch64__)
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
