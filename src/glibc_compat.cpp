#include "bitcoin-config.h"
#include <cstddef>
#include <sys/select.h>

extern "C" void* memmove(void* a, const void* b, size_t c);
extern "C" void* __real_memcpy(void* a, const void* b, size_t c) __attribute__((weak));
extern "C" void* __wrap_memcpy(void* a, const void* b, size_t c)
{
  if (__real_memcpy)
    return __real_memcpy(a, b, c);
  return memmove(a, b, c);
}

extern "C" void __chk_fail (void) __attribute__((__noreturn__));
extern "C" FDELT_TYPE __real___fdelt_warn(FDELT_TYPE) __attribute__((weak));
extern "C" FDELT_TYPE __wrap___fdelt_warn(FDELT_TYPE a)
{
  if (a >= FD_SETSIZE)
    __chk_fail ();

  return a / __NFDBITS;
}
extern "C" FDELT_TYPE __fdelt_chk(FDELT_TYPE) __attribute__((weak, alias("__wrap___fdelt_warn")));
