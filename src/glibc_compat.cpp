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
extern "C" long int __real___fdelt_warn(long int) __attribute__((weak));
extern "C" long int __wrap___fdelt_warn(long int a)
{
  if (a >= FD_SETSIZE)
    __chk_fail ();

  return a / __NFDBITS;
}
extern "C" long int __fdelt_chk(long int) __attribute__((weak, alias("__wrap___fdelt_warn")));
