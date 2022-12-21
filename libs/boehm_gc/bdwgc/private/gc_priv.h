# 1 "gc_priv.h"
# 18 "gc_priv.h"
#ifndef GC_PRIVATE_H
#define GC_PRIVATE_H 

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#if !defined(GC_BUILD) && !defined(NOT_GCBUILD)
#define GC_BUILD 
#endif

#if (defined(__linux__) || defined(__GLIBC__) || defined(__GNU__) \
     || defined(__CYGWIN__)) && !defined(_GNU_SOURCE)

#define _GNU_SOURCE 1
#endif

#if defined(__INTERIX) && !defined(_ALL_SOURCE)
#define _ALL_SOURCE 1
#endif

#if (defined(DGUX) && defined(GC_THREADS) || defined(DGUX386_THREADS) \
     || defined(GC_DGUX386_THREADS)) && !defined(_USING_POSIX4A_DRAFT10)
#define _USING_POSIX4A_DRAFT10 1
#endif

#if defined(__MINGW32__) && !defined(__MINGW_EXCPT_DEFINE_PSDK) \
    && defined(__i386__) && defined(GC_EXTERN)

#define __MINGW_EXCPT_DEFINE_PSDK 1
#endif

# if defined(NO_DEBUGGING) && !defined(GC_ASSERTIONS) && !defined(NDEBUG)

#define NDEBUG 1
# endif

#ifndef GC_H
# include "gc.h"
#endif

#include <stdlib.h>
#if !defined(sony_news)
# include <stddef.h>
#endif

#ifdef DGUX
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
#endif

#ifdef BSD_TIME
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
#endif

#ifdef PARALLEL_MARK
#define AO_REQUIRE_CAS 
# if !defined(__GNUC__) && !defined(AO_ASSUME_WINDOWS98)
#define AO_ASSUME_WINDOWS98 
# endif
#endif

#include "gc/gc_tiny_fl.h"
#include "gc/gc_mark.h"

typedef GC_word word;
typedef GC_signed_word signed_word;
typedef unsigned int unsigned32;

typedef int GC_bool;
#define TRUE 1
#define FALSE 0

#ifndef PTR_T_DEFINED
  typedef char * ptr_t;


#define PTR_T_DEFINED 
#endif

#ifndef SIZE_MAX
# include <limits.h>
#endif
#if defined(SIZE_MAX) && !defined(CPPCHECK)
#define GC_SIZE_MAX ((size_t)SIZE_MAX)

#else
#define GC_SIZE_MAX (~(size_t)0)
#endif

#if GC_GNUC_PREREQ(3, 0) && !defined(LINT2)
#define EXPECT(expr,outcome) __builtin_expect(expr,outcome)

#else
#define EXPECT(expr,outcome) (expr)
#endif



#define SIZET_SAT_ADD(a,b) \
            (EXPECT((a) < GC_SIZE_MAX - (b), TRUE) ? (a) + (b) : GC_SIZE_MAX)

#include "gcconfig.h"

#if !defined(GC_ATOMIC_UNCOLLECTABLE) && defined(ATOMIC_UNCOLLECTABLE)

#define GC_ATOMIC_UNCOLLECTABLE 
#endif

#ifndef GC_INNER






# if defined(GC_DLL) && defined(__GNUC__) && !defined(MSWIN32) \
        && !defined(MSWINCE) && !defined(CYGWIN32)
# if GC_GNUC_PREREQ(4, 0) && !defined(GC_NO_VISIBILITY)

#define GC_INNER __attribute__((__visibility__("hidden")))
# else

#define GC_INNER 
# endif
# else
#define GC_INNER 
# endif

#define GC_EXTERN extern GC_INNER







#endif

#ifdef __cplusplus

#define REGISTER 
#else


#define REGISTER register
#endif

#if defined(CPPCHECK)
#define MACRO_BLKSTMT_BEGIN {
#define MACRO_BLKSTMT_END }
#define LOCAL_VAR_INIT_OK =0
#else
#define MACRO_BLKSTMT_BEGIN do {
#define MACRO_BLKSTMT_END } while (0)
#define LOCAL_VAR_INIT_OK 
#endif

#if defined(M68K) && defined(__GNUC__)


#define GC_ATTR_WORD_ALIGNED __attribute__((__aligned__(sizeof(word))))
#else
#define GC_ATTR_WORD_ALIGNED 
#endif

#ifndef HEADERS_H
# include "gc_hdrs.h"
#endif

#ifndef GC_ATTR_NO_SANITIZE_ADDR
# ifndef ADDRESS_SANITIZER
#define GC_ATTR_NO_SANITIZE_ADDR 
# elif GC_CLANG_PREREQ(3, 8)
#define GC_ATTR_NO_SANITIZE_ADDR __attribute__((no_sanitize("address")))
# else
#define GC_ATTR_NO_SANITIZE_ADDR __attribute__((no_sanitize_address))
# endif
#endif

#ifndef GC_ATTR_NO_SANITIZE_MEMORY
# ifndef MEMORY_SANITIZER
#define GC_ATTR_NO_SANITIZE_MEMORY 
# elif GC_CLANG_PREREQ(3, 8)
#define GC_ATTR_NO_SANITIZE_MEMORY __attribute__((no_sanitize("memory")))
# else
#define GC_ATTR_NO_SANITIZE_MEMORY __attribute__((no_sanitize_memory))
# endif
#endif

#ifndef GC_ATTR_NO_SANITIZE_THREAD
# ifndef THREAD_SANITIZER
#define GC_ATTR_NO_SANITIZE_THREAD 
# elif GC_CLANG_PREREQ(3, 8)
#define GC_ATTR_NO_SANITIZE_THREAD __attribute__((no_sanitize("thread")))
# else


#define GC_ATTR_NO_SANITIZE_THREAD \
                GC_ATTR_NOINLINE __attribute__((no_sanitize_thread))
# endif
#endif

#ifndef GC_ATTR_UNUSED
# if GC_GNUC_PREREQ(3, 4)
#define GC_ATTR_UNUSED __attribute__((__unused__))
# else
#define GC_ATTR_UNUSED 
# endif
#endif

#ifdef HAVE_CONFIG_H

#define GC_INLINE static inline
#elif defined(_MSC_VER) || defined(__INTEL_COMPILER) || defined(__DMC__) \
        || (GC_GNUC_PREREQ(3, 0) && defined(__STRICT_ANSI__)) \
        || defined(__WATCOMC__)
#define GC_INLINE static __inline
#elif GC_GNUC_PREREQ(3, 0) || defined(__sun)
#define GC_INLINE static inline
#else
#define GC_INLINE static
#endif

#ifndef GC_ATTR_NOINLINE
# if GC_GNUC_PREREQ(4, 0)
#define GC_ATTR_NOINLINE __attribute__((__noinline__))
# elif _MSC_VER >= 1400
#define GC_ATTR_NOINLINE __declspec(noinline)
# else
#define GC_ATTR_NOINLINE 
# endif
#endif

#ifndef GC_API_OSCALL

# if defined(__GNUC__)
# if GC_GNUC_PREREQ(4, 0) && !defined(GC_NO_VISIBILITY)

#define GC_API_OSCALL extern __attribute__((__visibility__("default")))
# else

#define GC_API_OSCALL extern
# endif
# else
#define GC_API_OSCALL GC_API
# endif
#endif

#ifndef GC_API_PRIV
#define GC_API_PRIV GC_API
#endif

#if defined(THREADS) && !defined(NN_PLATFORM_CTR)
# include "gc_atomic_ops.h"
# ifndef AO_HAVE_compiler_barrier
#define AO_HAVE_compiler_barrier 1
# endif
#endif

#if defined(MSWIN32) || defined(MSWINCE) || defined(CYGWIN32)
# ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
# endif
#define NOSERVICE 
# include <windows.h>
# include <winbase.h>
#endif

#include "gc_locks.h"

#define GC_WORD_MAX (~(word)0)

# ifdef STACK_GROWS_DOWN
#define COOLER_THAN >
#define HOTTER_THAN <
#define MAKE_COOLER(x,y) if ((word)((x) + (y)) > (word)(x)) {(x) += (y);} \
                            else (x) = (ptr_t)GC_WORD_MAX
#define MAKE_HOTTER(x,y) (x) -= (y)
# else
#define COOLER_THAN <
#define HOTTER_THAN >
#define MAKE_COOLER(x,y) if ((word)((x) - (y)) < (word)(x)) {(x) -= (y);} \
                            else (x) = 0
#define MAKE_HOTTER(x,y) (x) += (y)
# endif

#if defined(AMIGA) && defined(__SASC)
#define GC_FAR __far
#else
#define GC_FAR 
#endif
# 356 "gc_priv.h"
EXTERN_C_BEGIN

#ifndef GC_NO_FINALIZATION
#define GC_INVOKE_FINALIZERS() GC_notify_or_invoke_finalizers()
  GC_INNER void GC_notify_or_invoke_finalizers(void);






  GC_INNER void GC_finalize(void);






# ifndef GC_TOGGLE_REFS_NOT_NEEDED
    GC_INNER void GC_process_togglerefs(void);

# endif
# ifndef SMALL_CONFIG
    GC_INNER void GC_print_finalization_stats(void);
# endif
#else
#define GC_INVOKE_FINALIZERS() (void)0
#endif

#if !defined(DONT_ADD_BYTE_AT_END)
# ifdef LINT2


#define EXTRA_BYTES ((size_t)(GC_all_interior_pointers? 1 : 0))
# else
#define EXTRA_BYTES (size_t)GC_all_interior_pointers
# endif
#define MAX_EXTRA_BYTES 1
#else
#define EXTRA_BYTES 0
#define MAX_EXTRA_BYTES 0
#endif


# ifndef LARGE_CONFIG
#define MINHINCR 16

#define MAXHINCR 2048
# else
#define MINHINCR 64
#define MAXHINCR 4096
# endif

#define BL_LIMIT GC_black_list_spacing
# 427 "gc_priv.h"
#ifdef NEED_CALLINFO
    struct callinfo {
        word ci_pc;
# if NARGS > 0
            word ci_arg[NARGS];
# endif
# if (NFRAMES * (NARGS + 1)) % 2 == 1

            word ci_dummy;
# endif
    };
#endif

#ifdef SAVE_CALL_CHAIN


  GC_INNER void GC_save_callers(struct callinfo info[NFRAMES]);
  GC_INNER void GC_print_callers(struct callinfo info[NFRAMES]);
#endif

EXTERN_C_END







#ifndef NO_CLOCK
#ifdef BSD_TIME
#undef CLOCK_TYPE
#undef GET_TIME
#undef MS_TIME_DIFF
#define CLOCK_TYPE struct timeval
#define CLOCK_TYPE_INITIALIZER { 0, 0 }
#define GET_TIME(x) \
                do { \
                  struct rusage rusage; \
                  getrusage(RUSAGE_SELF, &rusage); \
                  x = rusage.ru_utime; \
                } while (0)
#define MS_TIME_DIFF(a,b) ((unsigned long)((long)(a.tv_sec-b.tv_sec) * 1000 \
                + (long)(a.tv_usec - b.tv_usec) / 1000 \
                - (a.tv_usec < b.tv_usec \
                   && (long)(a.tv_usec - b.tv_usec) % 1000 != 0 ? 1 : 0)))


#define NS_FRAC_TIME_DIFF(a,b) ((unsigned long) \
                ((a.tv_usec < b.tv_usec \
                  && (long)(a.tv_usec - b.tv_usec) % 1000 != 0 ? 1000L : 0) \
                 + (long)(a.tv_usec - b.tv_usec) % 1000) * 1000)



#elif defined(MSWIN32) || defined(MSWINCE) || defined(WINXP_USE_PERF_COUNTER)
# if defined(MSWINRT_FLAVOR) || defined(WINXP_USE_PERF_COUNTER)
#define CLOCK_TYPE ULONGLONG
#define GET_TIME(x) \
                do { \
                  LARGE_INTEGER freq, tc; \
                  if (!QueryPerformanceFrequency(&freq)) \
                    ABORT("QueryPerformanceFrequency requires WinXP+"); \
                                                                           \
                                                                           \
                                                                           \
                  if (!QueryPerformanceCounter(&tc)) \
                    ABORT("QueryPerformanceCounter failed"); \
                  x = (CLOCK_TYPE)((double)tc.QuadPart/freq.QuadPart * 1e9); \
                } while (0)

#define MS_TIME_DIFF(a,b) ((unsigned long)(((a) - (b)) / 1000000UL))
#define NS_FRAC_TIME_DIFF(a,b) ((unsigned long)(((a) - (b)) % 1000000UL))
# else
#define CLOCK_TYPE DWORD
#define GET_TIME(x) (void)(x = GetTickCount())
#define MS_TIME_DIFF(a,b) ((unsigned long)((a) - (b)))
#define NS_FRAC_TIME_DIFF(a,b) 0UL
# endif

#elif defined(NN_PLATFORM_CTR)
#define CLOCK_TYPE long long
  EXTERN_C_BEGIN
  CLOCK_TYPE n3ds_get_system_tick(void);
  CLOCK_TYPE n3ds_convert_tick_to_ms(CLOCK_TYPE tick);
  EXTERN_C_END
#define GET_TIME(x) (void)(x = n3ds_get_system_tick())
#define MS_TIME_DIFF(a,b) ((unsigned long)n3ds_convert_tick_to_ms((a)-(b)))
#define NS_FRAC_TIME_DIFF(a,b) 0UL

#elif defined(HAVE_CLOCK_GETTIME)
# include <time.h>
#define CLOCK_TYPE struct timespec
#define CLOCK_TYPE_INITIALIZER { 0, 0 }
# if defined(_POSIX_MONOTONIC_CLOCK) && !defined(NINTENDO_SWITCH)
#define GET_TIME(x) \
                do { \
                  if (clock_gettime(CLOCK_MONOTONIC, &x) == -1) \
                    ABORT("clock_gettime failed"); \
                } while (0)
# else
#define GET_TIME(x) \
                do { \
                  if (clock_gettime(CLOCK_REALTIME, &x) == -1) \
                    ABORT("clock_gettime failed"); \
                } while (0)
# endif
#define MS_TIME_DIFF(a,b) \
                                                                    \
    ((unsigned long)((a).tv_nsec + (1000000L*1000 - (b).tv_nsec)) / 1000000UL \
     + ((unsigned long)((a).tv_sec - (b).tv_sec) * 1000UL) - 1000UL)
#define NS_FRAC_TIME_DIFF(a,b) \
    ((unsigned long)((a).tv_nsec + (1000000L*1000 - (b).tv_nsec)) % 1000000UL)

#else
# include <time.h>
# if defined(FREEBSD) && !defined(CLOCKS_PER_SEC)
# include <machine/limits.h>
#define CLOCKS_PER_SEC CLK_TCK
# endif
# if !defined(CLOCKS_PER_SEC)
#define CLOCKS_PER_SEC 1000000
# 557 "gc_priv.h"
# endif
#define CLOCK_TYPE clock_t
#define GET_TIME(x) (void)(x = clock())
#define MS_TIME_DIFF(a,b) (CLOCKS_PER_SEC % 1000 == 0 ? \
        (unsigned long)((a) - (b)) / (unsigned long)(CLOCKS_PER_SEC / 1000) \
        : ((unsigned long)((a) - (b)) * 1000) / (unsigned long)CLOCKS_PER_SEC)


#define NS_FRAC_TIME_DIFF(a,b) (CLOCKS_PER_SEC <= 1000 ? 0UL \
    : (unsigned long)(CLOCKS_PER_SEC <= (clock_t)1000000UL \
        ? (((a) - (b)) * ((clock_t)1000000UL / CLOCKS_PER_SEC) % 1000) * 1000 \
        : (CLOCKS_PER_SEC <= (clock_t)1000000UL * 1000 \
            ? ((a) - (b)) * ((clock_t)1000000UL * 1000 / CLOCKS_PER_SEC) \
            : (((a) - (b)) * (clock_t)1000000UL * 1000) / CLOCKS_PER_SEC) \
          % (clock_t)1000000UL))
#endif
# ifndef CLOCK_TYPE_INITIALIZER


#define CLOCK_TYPE_INITIALIZER 0
# endif
#endif


# if defined(SPARC) && defined(SUNOS4) \
     || (defined(M68K) && defined(NEXT)) || defined(VAX)
#define BCOPY_EXISTS 
# elif defined(AMIGA) || defined(DARWIN)
# include <string.h>
#define BCOPY_EXISTS 
# elif defined(MACOS) && defined(POWERPC)
# include <MacMemory.h>
#define bcopy(x,y,n) BlockMoveData(x, y, n)
#define bzero(x,n) BlockZero(x, n)
#define BCOPY_EXISTS 
# endif

# if !defined(BCOPY_EXISTS) || defined(CPPCHECK)
# include <string.h>
#define BCOPY(x,y,n) memcpy(y, x, (size_t)(n))
#define BZERO(x,n) memset(x, 0, (size_t)(n))
# else
#define BCOPY(x,y,n) bcopy((void *)(x),(void *)(y),(size_t)(n))
#define BZERO(x,n) bzero((void *)(x),(size_t)(n))
# endif

#ifdef PCR
# include "th/PCR_ThCtl.h"
#endif

EXTERN_C_BEGIN




# ifdef PCR
#define STOP_WORLD() \
        PCR_ThCtl_SetExclusiveMode(PCR_ThCtl_ExclusiveMode_stopNormal, \
                                   PCR_allSigsBlocked, \
                                   PCR_waitForever)
#define START_WORLD() \
        PCR_ThCtl_SetExclusiveMode(PCR_ThCtl_ExclusiveMode_null, \
                                   PCR_allSigsBlocked, \
                                   PCR_waitForever)
# else
# if defined(NN_PLATFORM_CTR) || defined(NINTENDO_SWITCH) \
       || defined(GC_WIN32_THREADS) || defined(GC_PTHREADS)
      GC_INNER void GC_stop_world(void);
      GC_INNER void GC_start_world(void);
#define STOP_WORLD() GC_stop_world()
#define START_WORLD() GC_start_world()
# else

#define STOP_WORLD() GC_ASSERT(GC_blocked_sp == NULL)
#define START_WORLD() 
# endif
# endif

#ifdef THREADS
  GC_EXTERN GC_on_thread_event_proc GC_on_thread_event;
#endif


# if defined(SMALL_CONFIG) || defined(PCR)
#define GC_on_abort(msg) (void)0
# else
    GC_API_PRIV GC_abort_func GC_on_abort;
# endif
# if defined(CPPCHECK)
#define ABORT(msg) { GC_on_abort(msg); abort(); }
# elif defined(PCR)
#define ABORT(s) PCR_Base_Panic(s)
# else
# if defined(MSWIN_XBOX1) && !defined(DebugBreak)
#define DebugBreak() __debugbreak()
# elif defined(MSWINCE) && !defined(DebugBreak) \
       && (!defined(UNDER_CE) || (defined(__MINGW32CE__) && !defined(ARM32)))





#define DebugBreak() _exit(-1)
# endif
# if defined(MSWIN32) && (defined(NO_DEBUGGING) || defined(LINT2))

#define ABORT(msg) (GC_on_abort(msg), _exit(-1))

# elif defined(MSWINCE) && defined(NO_DEBUGGING)
#define ABORT(msg) (GC_on_abort(msg), ExitProcess(-1))
# elif defined(MSWIN32) || defined(MSWINCE)
# if defined(_CrtDbgBreak) && defined(_DEBUG) && defined(_MSC_VER)
#define ABORT(msg) { GC_on_abort(msg); \
                            _CrtDbgBreak() ; }
# else
#define ABORT(msg) { GC_on_abort(msg); DebugBreak(); }



# endif
# else
#define ABORT(msg) (GC_on_abort(msg), abort())
# endif
# endif




#define ABORT_ARG1(C_msg,C_fmt,arg1) \
                MACRO_BLKSTMT_BEGIN \
                  GC_ERRINFO_PRINTF(C_msg C_fmt "\n", arg1); \
                  ABORT(C_msg); \
                MACRO_BLKSTMT_END
#define ABORT_ARG2(C_msg,C_fmt,arg1,arg2) \
                MACRO_BLKSTMT_BEGIN \
                  GC_ERRINFO_PRINTF(C_msg C_fmt "\n", arg1, arg2); \
                  ABORT(C_msg); \
                MACRO_BLKSTMT_END
#define ABORT_ARG3(C_msg,C_fmt,arg1,arg2,arg3) \
                MACRO_BLKSTMT_BEGIN \
                  GC_ERRINFO_PRINTF(C_msg C_fmt "\n", \
                                    arg1, arg2, arg3); \
                  ABORT(C_msg); \
                MACRO_BLKSTMT_END



#define ABORT_RET(msg) \
              if ((signed_word)GC_current_warn_proc == -1) {} else ABORT(msg)


# ifdef PCR
#define EXIT() PCR_Base_Exit(1,PCR_waitForever)
# else
#define EXIT() (GC_on_abort(NULL), exit(1 ))
# endif




#define WARN(msg,arg) \
    (*GC_current_warn_proc)(( char *)("GC Warning: " msg), \
                            (word)(arg))
GC_EXTERN GC_warn_proc GC_current_warn_proc;






#ifndef WARN_PRIdPTR

#define WARN_PRIdPTR "ld"
#endif




#define TRUSTED_STRING(s) (char*)COVERT_DATAFLOW(s)


#ifdef GC_READ_ENV_FILE
  GC_INNER char * GC_envfile_getenv(const char *name);
#define GETENV(name) GC_envfile_getenv(name)
#elif defined(NO_GETENV) && !defined(CPPCHECK)
#define GETENV(name) NULL
#elif defined(EMPTY_GETENV_RESULTS)

  GC_INLINE char * fixed_getenv(const char *name)
  {
    char *value = getenv(name);
    return value != NULL && *value != '\0' ? value : NULL;
  }
#define GETENV(name) fixed_getenv(name)
#else
#define GETENV(name) getenv(name)
#endif

EXTERN_C_END

#if defined(DARWIN)
# include <mach/thread_status.h>
# ifndef MAC_OS_X_VERSION_MAX_ALLOWED
# include <AvailabilityMacros.h>

# endif
# if defined(POWERPC)
# if CPP_WORDSZ == 32
#define GC_THREAD_STATE_T ppc_thread_state_t
# else
#define GC_THREAD_STATE_T ppc_thread_state64_t
#define GC_MACH_THREAD_STATE PPC_THREAD_STATE64
#define GC_MACH_THREAD_STATE_COUNT PPC_THREAD_STATE64_COUNT
# endif
# elif defined(I386) || defined(X86_64)
# if CPP_WORDSZ == 32
# if defined(i386_THREAD_STATE_COUNT) && !defined(x86_THREAD_STATE32_COUNT)

#define GC_THREAD_STATE_T i386_thread_state_t
#define GC_MACH_THREAD_STATE i386_THREAD_STATE
#define GC_MACH_THREAD_STATE_COUNT i386_THREAD_STATE_COUNT
# else
#define GC_THREAD_STATE_T x86_thread_state32_t
#define GC_MACH_THREAD_STATE x86_THREAD_STATE32
#define GC_MACH_THREAD_STATE_COUNT x86_THREAD_STATE32_COUNT
# endif
# else
#define GC_THREAD_STATE_T x86_thread_state64_t
#define GC_MACH_THREAD_STATE x86_THREAD_STATE64
#define GC_MACH_THREAD_STATE_COUNT x86_THREAD_STATE64_COUNT
# endif
# elif defined(ARM32) && defined(ARM_UNIFIED_THREAD_STATE) \
       && !defined(CPPCHECK)
#define GC_THREAD_STATE_T arm_unified_thread_state_t
#define GC_MACH_THREAD_STATE ARM_UNIFIED_THREAD_STATE
#define GC_MACH_THREAD_STATE_COUNT ARM_UNIFIED_THREAD_STATE_COUNT
# elif defined(ARM32)
#define GC_THREAD_STATE_T arm_thread_state_t
# ifdef ARM_MACHINE_THREAD_STATE_COUNT
#define GC_MACH_THREAD_STATE ARM_MACHINE_THREAD_STATE
#define GC_MACH_THREAD_STATE_COUNT ARM_MACHINE_THREAD_STATE_COUNT
# endif
# elif defined(AARCH64)
#define GC_THREAD_STATE_T arm_thread_state64_t
#define GC_MACH_THREAD_STATE ARM_THREAD_STATE64
#define GC_MACH_THREAD_STATE_COUNT ARM_THREAD_STATE64_COUNT
# elif !defined(CPPCHECK)
# error define GC_THREAD_STATE_T
# endif
# ifndef GC_MACH_THREAD_STATE
#define GC_MACH_THREAD_STATE MACHINE_THREAD_STATE
#define GC_MACH_THREAD_STATE_COUNT MACHINE_THREAD_STATE_COUNT
# endif

# if CPP_WORDSZ == 32
#define GC_MACH_HEADER mach_header
#define GC_MACH_SECTION section
#define GC_GETSECTBYNAME getsectbynamefromheader
# else
#define GC_MACH_HEADER mach_header_64
#define GC_MACH_SECTION section_64
#define GC_GETSECTBYNAME getsectbynamefromheader_64
# endif






# if __DARWIN_UNIX03
#define THREAD_FLD_NAME(x) __ ## x
# else
#define THREAD_FLD_NAME(x) x
# endif
# if defined(ARM32) && defined(ARM_UNIFIED_THREAD_STATE)
#define THREAD_FLD(x) ts_32.THREAD_FLD_NAME(x)
# else
#define THREAD_FLD(x) THREAD_FLD_NAME(x)
# endif
#endif

#include <setjmp.h>

#if __STDC_VERSION__ >= 201112L
# include <assert.h>
#endif

EXTERN_C_BEGIN







#if CPP_WORDSZ == 32
#define WORDS_TO_BYTES(x) ((x)<<2)
#define BYTES_TO_WORDS(x) ((x)>>2)
#define LOGWL ((word)5)
#define modWORDSZ(n) ((n) & 0x1f)
# if ALIGNMENT != 4
#define UNALIGNED_PTRS 
# endif
#endif

#if CPP_WORDSZ == 64
#define WORDS_TO_BYTES(x) ((x)<<3)
#define BYTES_TO_WORDS(x) ((x)>>3)
#define LOGWL ((word)6)
#define modWORDSZ(n) ((n) & 0x3f)
# if ALIGNMENT != 8
#define UNALIGNED_PTRS 
# endif
#endif







#define GRANULE_BYTES GC_GRANULE_BYTES
#define TINY_FREELISTS GC_TINY_FREELISTS

#define WORDSZ ((word)CPP_WORDSZ)
#define SIGNB ((word)1 << (WORDSZ-1))
#define BYTES_PER_WORD ((word)(sizeof (word)))
#define divWORDSZ(n) ((n) >> LOGWL)

#if GRANULE_BYTES == 8
#define BYTES_TO_GRANULES(n) ((n)>>3)
#define GRANULES_TO_BYTES(n) ((n)<<3)
# if CPP_WORDSZ == 64
#define GRANULES_TO_WORDS(n) (n)
# elif CPP_WORDSZ == 32
#define GRANULES_TO_WORDS(n) ((n)<<1)
# else
#define GRANULES_TO_WORDS(n) BYTES_TO_WORDS(GRANULES_TO_BYTES(n))
# endif
#elif GRANULE_BYTES == 16
#define BYTES_TO_GRANULES(n) ((n)>>4)
#define GRANULES_TO_BYTES(n) ((n)<<4)
# if CPP_WORDSZ == 64
#define GRANULES_TO_WORDS(n) ((n)<<1)
# elif CPP_WORDSZ == 32
#define GRANULES_TO_WORDS(n) ((n)<<2)
# else
#define GRANULES_TO_WORDS(n) BYTES_TO_WORDS(GRANULES_TO_BYTES(n))
# endif
#else
# error Bad GRANULE_BYTES value
#endif
# 923 "gc_priv.h"
#ifndef HBLKSIZE
# if defined(LARGE_CONFIG) || !defined(SMALL_CONFIG)
# ifdef ALPHA
#define CPP_LOG_HBLKSIZE 13
# elif defined(SN_TARGET_PSP2)
#define CPP_LOG_HBLKSIZE 16
# else
#define CPP_LOG_HBLKSIZE 12
# endif
# else
#define CPP_LOG_HBLKSIZE 10
# endif
#else
# if HBLKSIZE == 512
#define CPP_LOG_HBLKSIZE 9
# elif HBLKSIZE == 1024
#define CPP_LOG_HBLKSIZE 10
# elif HBLKSIZE == 2048
#define CPP_LOG_HBLKSIZE 11
# elif HBLKSIZE == 4096
#define CPP_LOG_HBLKSIZE 12
# elif HBLKSIZE == 8192
#define CPP_LOG_HBLKSIZE 13
# elif HBLKSIZE == 16384
#define CPP_LOG_HBLKSIZE 14
# elif !defined(CPPCHECK)
# error Bad HBLKSIZE value
# endif
#undef HBLKSIZE
#endif

#define CPP_HBLKSIZE (1 << CPP_LOG_HBLKSIZE)
#define LOG_HBLKSIZE ((size_t)CPP_LOG_HBLKSIZE)
#define HBLKSIZE ((size_t)CPP_HBLKSIZE)

#define GC_SQRT_SIZE_MAX ((((size_t)1) << (WORDSZ / 2)) - 1)




#define CPP_MAXOBJBYTES (CPP_HBLKSIZE/2)
#define MAXOBJBYTES ((size_t)CPP_MAXOBJBYTES)
#define CPP_MAXOBJWORDS BYTES_TO_WORDS(CPP_MAXOBJBYTES)
#define MAXOBJWORDS ((size_t)CPP_MAXOBJWORDS)
#define CPP_MAXOBJGRANULES BYTES_TO_GRANULES(CPP_MAXOBJBYTES)
#define MAXOBJGRANULES ((size_t)CPP_MAXOBJGRANULES)

#define divHBLKSZ(n) ((n) >> LOG_HBLKSIZE)

#define HBLK_PTR_DIFF(p,q) divHBLKSZ((ptr_t)p - (ptr_t)q)







#define modHBLKSZ(n) ((n) & (HBLKSIZE-1))

#define HBLKPTR(objptr) ((struct hblk *)(((word)(objptr)) \
                                          & ~(word)(HBLKSIZE-1)))
#define HBLKDISPL(objptr) modHBLKSZ((size_t)(objptr))


#define ROUNDUP_GRANULE_SIZE(lb) \
            (SIZET_SAT_ADD(lb, GRANULE_BYTES - 1) & ~(GRANULE_BYTES - 1))


#define ROUNDED_UP_GRANULES(lb) \
        BYTES_TO_GRANULES(SIZET_SAT_ADD(lb, GRANULE_BYTES - 1 + EXTRA_BYTES))
# if MAX_EXTRA_BYTES == 0
#define SMALL_OBJ(bytes) EXPECT((bytes) <= (MAXOBJBYTES), TRUE)
# else
#define SMALL_OBJ(bytes) \
            (EXPECT((bytes) <= (MAXOBJBYTES - MAX_EXTRA_BYTES), TRUE) \
             || (bytes) <= MAXOBJBYTES - EXTRA_BYTES)


# endif
#define ADD_SLOP(lb) \
                SIZET_SAT_ADD(lb, EXTRA_BYTES)
# 1014 "gc_priv.h"
#ifndef LOG_PHT_ENTRIES
# ifdef LARGE_CONFIG
# if CPP_WORDSZ == 32
#define LOG_PHT_ENTRIES 20



# else
#define LOG_PHT_ENTRIES 21



# endif
# elif !defined(SMALL_CONFIG)
#define LOG_PHT_ENTRIES 18






# else
#define LOG_PHT_ENTRIES 15


# endif
#endif

#define PHT_ENTRIES ((word)1 << LOG_PHT_ENTRIES)
#define PHT_SIZE (PHT_ENTRIES >> LOGWL)
typedef word page_hash_table[PHT_SIZE];

#define PHT_HASH(addr) ((((word)(addr)) >> LOG_HBLKSIZE) & (PHT_ENTRIES - 1))

#define get_pht_entry_from_index(bl,index) \
                (((bl)[divWORDSZ(index)] >> modWORDSZ(index)) & 1)
#define set_pht_entry_from_index(bl,index) \
                (void)((bl)[divWORDSZ(index)] |= (word)1 << modWORDSZ(index))

#if defined(THREADS) && defined(AO_HAVE_or)




#define set_pht_entry_from_index_concurrent(bl,index) \
                AO_or((volatile AO_t *)&(bl)[divWORDSZ(index)], \
                      (AO_t)((word)1 << modWORDSZ(index)))
#else
#define set_pht_entry_from_index_concurrent(bl,index) \
                set_pht_entry_from_index(bl, index)
#endif
# 1073 "gc_priv.h"
#define MARK_BITS_PER_HBLK (HBLKSIZE/GRANULE_BYTES)
# 1083 "gc_priv.h"
union word_ptr_ao_u {
  word w;
  signed_word sw;
  void *vp;
# ifdef PARALLEL_MARK
    volatile AO_t ao;
# endif
};




struct hblkhdr {
    struct hblk * hb_next;


    struct hblk * hb_prev;
    struct hblk * hb_block;
    unsigned char hb_obj_kind;



    unsigned char hb_flags;
#define IGNORE_OFF_PAGE 1


#define WAS_UNMAPPED 2





#define FREE_BLK 4
# ifdef ENABLE_DISCLAIM
#define HAS_DISCLAIM 8

#define MARK_UNCONDITIONALLY 0x10



# endif
# ifdef MARK_BIT_PER_GRANULE
#define LARGE_BLOCK 0x20
# endif
    unsigned short hb_last_reclaimed;







# ifdef MARK_BIT_PER_OBJ
      unsigned32 hb_inv_sz;


#define LARGE_INV_SZ (1 << 16)
# endif
    word hb_sz;




    word hb_descr;

# ifdef MARK_BIT_PER_GRANULE
      unsigned short * hb_map;


# endif
# ifdef PARALLEL_MARK
      volatile AO_t hb_n_marks;
# 1172 "gc_priv.h"
# else
      size_t hb_n_marks;

# endif
# ifdef USE_MARK_BYTES
#define MARK_BITS_SZ (MARK_BITS_PER_HBLK + 1)





      union {
        char _hb_marks[MARK_BITS_SZ];






        word dummy;
      } _mark_byte_union;
#define hb_marks _mark_byte_union._hb_marks
# else
#define MARK_BITS_SZ (MARK_BITS_PER_HBLK/CPP_WORDSZ + 1)
      word hb_marks[MARK_BITS_SZ];
# endif
};

#define ANY_INDEX 23



#define HBLK_WORDS (HBLKSIZE/sizeof(word))
#define HBLK_GRANULES (HBLKSIZE/GRANULE_BYTES)



#define HBLK_OBJS(sz_in_bytes) (HBLKSIZE/(sz_in_bytes))

struct hblk {
    char hb_body[HBLKSIZE];
};

#define HBLK_IS_FREE(hdr) (((hdr) -> hb_flags & FREE_BLK) != 0)

#define OBJ_SZ_TO_BLOCKS(lb) divHBLKSZ((lb) + HBLKSIZE-1)
#define OBJ_SZ_TO_BLOCKS_CHECKED(lb) \
                                divHBLKSZ(SIZET_SAT_ADD(lb, HBLKSIZE-1))




#define obj_link(p) (*(void **)(p))

#define LOG_MAX_MARK_PROCS 6
#define MAX_MARK_PROCS (1 << LOG_MAX_MARK_PROCS)





# ifdef LARGE_CONFIG
#define MAX_ROOT_SETS 8192
# elif !defined(SMALL_CONFIG)
#define MAX_ROOT_SETS 2048
# else
#define MAX_ROOT_SETS 512
# endif

#define MAX_EXCLUSIONS (MAX_ROOT_SETS/4)





struct exclusion {
    ptr_t e_start;
    ptr_t e_end;
};





struct roots {
        ptr_t r_start;
        ptr_t r_end;
# if !defined(MSWIN32) && !defined(MSWINCE) && !defined(CYGWIN32)
          struct roots * r_next;
# endif
        GC_bool r_tmp;

};

#if !defined(MSWIN32) && !defined(MSWINCE) && !defined(CYGWIN32)

#define LOG_RT_SIZE 6
#define RT_SIZE (1 << LOG_RT_SIZE)
#endif

#if (!defined(MAX_HEAP_SECTS) || defined(CPPCHECK)) \
    && (defined(CYGWIN32) || defined(MSWIN32) || defined(MSWINCE) \
        || defined(USE_PROC_FOR_LIBRARIES))
# ifdef LARGE_CONFIG
# if CPP_WORDSZ > 32
#define MAX_HEAP_SECTS 81920
# else
#define MAX_HEAP_SECTS 7680
# endif
# elif defined(SMALL_CONFIG) && !defined(USE_PROC_FOR_LIBRARIES)
# if defined(PARALLEL_MARK) && (defined(MSWIN32) || defined(CYGWIN32))
#define MAX_HEAP_SECTS 384
# else
#define MAX_HEAP_SECTS 128
# endif
# elif CPP_WORDSZ > 32
#define MAX_HEAP_SECTS 1024
# else
#define MAX_HEAP_SECTS 512
# endif
#endif

typedef struct GC_ms_entry {
    ptr_t mse_start;
    union word_ptr_ao_u mse_descr;


} mse;

typedef int mark_state_t;



struct disappearing_link;
struct finalizable_object;

struct dl_hashtbl_s {
    struct disappearing_link **head;
    word entries;
    unsigned log_size;
};

struct fnlz_roots_s {
  struct finalizable_object **fo_head;

  struct finalizable_object *finalize_now;
};

union toggle_ref_u {

  void *strong_ref;
  GC_hidden_pointer weak_ref;
};




typedef struct {
    word ed_bitmap;
    GC_bool ed_continued;
} typed_ext_descr_t;

struct HeapSect {
    ptr_t hs_start;
    size_t hs_bytes;
};
# 1358 "gc_priv.h"
struct _GC_arrays {
  word _heapsize;
  word _requested_heapsize;
#define GC_heapsize_on_gc_disable GC_arrays._heapsize_on_gc_disable
  word _heapsize_on_gc_disable;
  ptr_t _last_heap_addr;
  word _large_free_bytes;


  word _large_allocd_bytes;




  word _max_large_allocd_bytes;



  word _bytes_allocd_before_gc;


#define GC_our_mem_bytes GC_arrays._our_mem_bytes
  word _our_mem_bytes;
# ifndef SEPARATE_GLOBALS
#define GC_bytes_allocd GC_arrays._bytes_allocd
    word _bytes_allocd;

# endif
  word _bytes_dropped;




  word _bytes_finalized;



  word _bytes_freed;


  word _finalizer_bytes_freed;



  bottom_index *_all_bottom_indices;


  bottom_index *_all_bottom_indices_end;


  ptr_t _scratch_free_ptr;
  hdr *_hdr_free_list;
  ptr_t _scratch_end_ptr;

# if defined(IRIX5) || (defined(USE_PROC_FOR_LIBRARIES) && !defined(LINUX))
#define USE_SCRATCH_LAST_END_PTR 
#define GC_scratch_last_end_ptr GC_arrays._scratch_last_end_ptr
    ptr_t _scratch_last_end_ptr;



# endif
  mse *_mark_stack;



  mse *_mark_stack_limit;
# ifdef PARALLEL_MARK
    mse *volatile _mark_stack_top;


# else
    mse *_mark_stack_top;
# endif
  word _composite_in_use;

  word _atomic_in_use;

#define GC_last_heap_growth_gc_no GC_arrays._last_heap_growth_gc_no
  word _last_heap_growth_gc_no;

# ifdef USE_MUNMAP
#define GC_unmapped_bytes GC_arrays._unmapped_bytes
    word _unmapped_bytes;
# ifdef COUNT_UNMAPPED_REGIONS
#define GC_num_unmapped_regions GC_arrays._num_unmapped_regions
      signed_word _num_unmapped_regions;
# endif
# else
#define GC_unmapped_bytes 0
# endif
  bottom_index * _all_nils;
#define GC_scan_ptr GC_arrays._scan_ptr
  struct hblk * _scan_ptr;
# ifdef PARALLEL_MARK
#define GC_main_local_mark_stack GC_arrays._main_local_mark_stack
    mse *_main_local_mark_stack;
#define GC_first_nonempty GC_arrays._first_nonempty
    volatile AO_t _first_nonempty;


# endif
#define GC_mark_stack_size GC_arrays._mark_stack_size
  size_t _mark_stack_size;
#define GC_mark_state GC_arrays._mark_state
  mark_state_t _mark_state;
#define GC_mark_stack_too_small GC_arrays._mark_stack_too_small
  GC_bool _mark_stack_too_small;


#define GC_objects_are_marked GC_arrays._objects_are_marked
  GC_bool _objects_are_marked;

# ifdef ENABLE_TRACE
#define GC_trace_addr GC_arrays._trace_addr
    ptr_t _trace_addr;
# endif
#define GC_capacity_heap_sects GC_arrays._capacity_heap_sects
  size_t _capacity_heap_sects;
#define GC_n_heap_sects GC_arrays._n_heap_sects
  word _n_heap_sects;
# if defined(MSWIN32) || defined(MSWINCE) || defined(CYGWIN32)
#define GC_n_heap_bases GC_arrays._n_heap_bases
    word _n_heap_bases;
# endif
# ifdef USE_PROC_FOR_LIBRARIES
#define GC_n_memory GC_arrays._n_memory
    word _n_memory;
# endif
# ifdef GC_GCJ_SUPPORT
#define GC_gcjobjfreelist GC_arrays._gcjobjfreelist
    ptr_t *_gcjobjfreelist;
# endif
#define GC_fo_entries GC_arrays._fo_entries
  word _fo_entries;
# ifndef GC_NO_FINALIZATION
#define GC_dl_hashtbl GC_arrays._dl_hashtbl
#define GC_fnlz_roots GC_arrays._fnlz_roots
#define GC_log_fo_table_size GC_arrays._log_fo_table_size
# ifndef GC_LONG_REFS_NOT_NEEDED
#define GC_ll_hashtbl GC_arrays._ll_hashtbl
      struct dl_hashtbl_s _ll_hashtbl;
# endif
    struct dl_hashtbl_s _dl_hashtbl;
    struct fnlz_roots_s _fnlz_roots;
    unsigned _log_fo_table_size;
# ifndef GC_TOGGLE_REFS_NOT_NEEDED
#define GC_toggleref_arr GC_arrays._toggleref_arr
#define GC_toggleref_array_size GC_arrays._toggleref_array_size
#define GC_toggleref_array_capacity GC_arrays._toggleref_array_capacity
      union toggle_ref_u *_toggleref_arr;
      size_t _toggleref_array_size;
      size_t _toggleref_array_capacity;
# endif
# endif
# ifdef TRACE_BUF
#define GC_trace_buf_ptr GC_arrays._trace_buf_ptr
    int _trace_buf_ptr;
# endif
# ifdef ENABLE_DISCLAIM
#define GC_finalized_kind GC_arrays._finalized_kind
    int _finalized_kind;
# endif
#define n_root_sets GC_arrays._n_root_sets
#define GC_excl_table_entries GC_arrays._excl_table_entries
  int _n_root_sets;

  size_t _excl_table_entries;
# ifdef THREADS
#define GC_roots_were_cleared GC_arrays._roots_were_cleared
    GC_bool _roots_were_cleared;
# endif
#define GC_explicit_typing_initialized GC_arrays._explicit_typing_initialized
#define GC_ed_size GC_arrays._ed_size
#define GC_avail_descr GC_arrays._avail_descr
#define GC_ext_descriptors GC_arrays._ext_descriptors
# ifdef AO_HAVE_load_acquire
    volatile AO_t _explicit_typing_initialized;
# else
    GC_bool _explicit_typing_initialized;
# endif
  size_t _ed_size;
  size_t _avail_descr;
  typed_ext_descr_t *_ext_descriptors;

  GC_mark_proc _mark_procs[MAX_MARK_PROCS];



  char _modws_valid_offsets[sizeof(word)];


# if !defined(MSWIN32) && !defined(MSWINCE) && !defined(CYGWIN32)
#define GC_root_index GC_arrays._root_index
    struct roots * _root_index[RT_SIZE];
# endif
# ifdef SAVE_CALL_CHAIN
#define GC_last_stack GC_arrays._last_stack
    struct callinfo _last_stack[NFRAMES];




# endif
# ifndef SEPARATE_GLOBALS
#define GC_objfreelist GC_arrays._objfreelist
    void *_objfreelist[MAXOBJGRANULES+1];

#define GC_aobjfreelist GC_arrays._aobjfreelist
    void *_aobjfreelist[MAXOBJGRANULES+1];

# endif
  void *_uobjfreelist[MAXOBJGRANULES+1];




# ifdef GC_ATOMIC_UNCOLLECTABLE
#define GC_auobjfreelist GC_arrays._auobjfreelist
    void *_auobjfreelist[MAXOBJGRANULES+1];

# endif
  size_t _size_map[MAXOBJBYTES+1];



# ifdef MARK_BIT_PER_GRANULE
#define GC_obj_map GC_arrays._obj_map
    unsigned short * _obj_map[MAXOBJGRANULES + 1];
# 1597 "gc_priv.h"
#define OBJ_MAP_LEN BYTES_TO_GRANULES(HBLKSIZE)
# endif
#define VALID_OFFSET_SZ HBLKSIZE
  char _valid_offsets[VALID_OFFSET_SZ];


# ifndef GC_DISABLE_INCREMENTAL
#define GC_grungy_pages GC_arrays._grungy_pages
    page_hash_table _grungy_pages;

#define GC_dirty_pages GC_arrays._dirty_pages
    volatile page_hash_table _dirty_pages;

# endif
# if (defined(CHECKSUMS) && (defined(GWW_VDB) || defined(SOFT_VDB))) \
     || defined(PROC_VDB)
#define GC_written_pages GC_arrays._written_pages
    page_hash_table _written_pages;
# endif
#define GC_heap_sects GC_arrays._heap_sects
  struct HeapSect *_heap_sects;

# if defined(USE_PROC_FOR_LIBRARIES)
#define GC_our_memory GC_arrays._our_memory
    struct HeapSect _our_memory[MAX_HEAP_SECTS];



# endif
# if defined(MSWIN32) || defined(MSWINCE) || defined(CYGWIN32)
#define GC_heap_bases GC_arrays._heap_bases
    ptr_t _heap_bases[MAX_HEAP_SECTS];

# endif
# ifdef MSWINCE
#define GC_heap_lengths GC_arrays._heap_lengths
    word _heap_lengths[MAX_HEAP_SECTS];

# endif
  struct roots _static_roots[MAX_ROOT_SETS];
  struct exclusion _excl_table[MAX_EXCLUSIONS];

  bottom_index * _top_index[TOP_SZ];
};

GC_API_PRIV GC_FAR struct _GC_arrays GC_arrays;

#define GC_all_nils GC_arrays._all_nils
#define GC_atomic_in_use GC_arrays._atomic_in_use
#define GC_bytes_allocd_before_gc GC_arrays._bytes_allocd_before_gc
#define GC_bytes_dropped GC_arrays._bytes_dropped
#define GC_bytes_finalized GC_arrays._bytes_finalized
#define GC_bytes_freed GC_arrays._bytes_freed
#define GC_composite_in_use GC_arrays._composite_in_use
#define GC_excl_table GC_arrays._excl_table
#define GC_finalizer_bytes_freed GC_arrays._finalizer_bytes_freed
#define GC_heapsize GC_arrays._heapsize
#define GC_large_allocd_bytes GC_arrays._large_allocd_bytes
#define GC_large_free_bytes GC_arrays._large_free_bytes
#define GC_last_heap_addr GC_arrays._last_heap_addr
#define GC_mark_stack GC_arrays._mark_stack
#define GC_mark_stack_limit GC_arrays._mark_stack_limit
#define GC_mark_stack_top GC_arrays._mark_stack_top
#define GC_mark_procs GC_arrays._mark_procs
#define GC_max_large_allocd_bytes GC_arrays._max_large_allocd_bytes
#define GC_modws_valid_offsets GC_arrays._modws_valid_offsets
#define GC_requested_heapsize GC_arrays._requested_heapsize
#define GC_all_bottom_indices GC_arrays._all_bottom_indices
#define GC_all_bottom_indices_end GC_arrays._all_bottom_indices_end
#define GC_scratch_free_ptr GC_arrays._scratch_free_ptr
#define GC_hdr_free_list GC_arrays._hdr_free_list
#define GC_scratch_end_ptr GC_arrays._scratch_end_ptr
#define GC_size_map GC_arrays._size_map
#define GC_static_roots GC_arrays._static_roots
#define GC_top_index GC_arrays._top_index
#define GC_uobjfreelist GC_arrays._uobjfreelist
#define GC_valid_offsets GC_arrays._valid_offsets

#define beginGC_arrays ((ptr_t)(&GC_arrays))
#define endGC_arrays (((ptr_t)(&GC_arrays)) + (sizeof GC_arrays))


#ifndef MAXOBJKINDS
#define MAXOBJKINDS 16
#endif
GC_EXTERN struct obj_kind {
  void **ok_freelist;


  struct hblk **ok_reclaim_list;



  word ok_descriptor;

  GC_bool ok_relocate_descr;



  GC_bool ok_init;

# ifdef ENABLE_DISCLAIM
    GC_bool ok_mark_unconditionally;



    int (GC_CALLBACK *ok_disclaim_proc)(void * );




#define OK_DISCLAIM_INITZ , FALSE, 0
# else
#define OK_DISCLAIM_INITZ 
# endif
} GC_obj_kinds[MAXOBJKINDS];

#define beginGC_obj_kinds ((ptr_t)(&GC_obj_kinds))
#define endGC_obj_kinds (beginGC_obj_kinds + (sizeof GC_obj_kinds))






#ifdef SEPARATE_GLOBALS
  extern word GC_bytes_allocd;

  extern ptr_t GC_objfreelist[MAXOBJGRANULES+1];

#define beginGC_objfreelist ((ptr_t)(&GC_objfreelist))
#define endGC_objfreelist (beginGC_objfreelist + sizeof(GC_objfreelist))

  extern ptr_t GC_aobjfreelist[MAXOBJGRANULES+1];

#define beginGC_aobjfreelist ((ptr_t)(&GC_aobjfreelist))
#define endGC_aobjfreelist (beginGC_aobjfreelist + sizeof(GC_aobjfreelist))
#endif


#define PTRFREE 0
#define NORMAL 1
#define UNCOLLECTABLE 2
#ifdef GC_ATOMIC_UNCOLLECTABLE
#define AUNCOLLECTABLE 3
#define IS_UNCOLLECTABLE(k) (((k) & ~1) == UNCOLLECTABLE)
#define GC_N_KINDS_INITIAL_VALUE 4
#else
#define IS_UNCOLLECTABLE(k) ((k) == UNCOLLECTABLE)
#define GC_N_KINDS_INITIAL_VALUE 3
#endif

GC_EXTERN unsigned GC_n_kinds;

GC_EXTERN size_t GC_page_size;



#define ROUNDUP_PAGESIZE(lb) \
            (SIZET_SAT_ADD(lb, GC_page_size - 1) & ~(GC_page_size - 1))


#ifdef MMAP_SUPPORTED
#define ROUNDUP_PAGESIZE_IF_MMAP(lb) ROUNDUP_PAGESIZE(lb)
#else
#define ROUNDUP_PAGESIZE_IF_MMAP(lb) (lb)
#endif

#if defined(MSWIN32) || defined(MSWINCE) || defined(CYGWIN32)
  GC_EXTERN SYSTEM_INFO GC_sysinfo;
  GC_INNER GC_bool GC_is_heap_base(void *p);
#endif

GC_EXTERN word GC_black_list_spacing;






#ifdef GC_GCJ_SUPPORT
  extern struct hblk * GC_hblkfreelist[];
  extern word GC_free_bytes[];
#endif

GC_EXTERN word GC_root_size;

GC_EXTERN GC_bool GC_debugging_started;



struct blocking_data {
    GC_fn_type fn;
    void * client_data;
};


struct GC_traced_stack_sect_s {
  ptr_t saved_stack_ptr;
# ifdef IA64
    ptr_t saved_backing_store_ptr;
    ptr_t backing_store_end;
# endif
  struct GC_traced_stack_sect_s *prev;
};

#ifdef THREADS


  GC_INNER void GC_push_all_stack_sections(ptr_t lo, ptr_t hi,
                        struct GC_traced_stack_sect_s *traced_stack_sect);
  GC_EXTERN word GC_total_stacksize;
#else
  GC_EXTERN ptr_t GC_blocked_sp;
  GC_EXTERN struct GC_traced_stack_sect_s *GC_traced_stack_sect;



#endif

#ifdef IA64
  GC_EXTERN ptr_t GC_register_stackbottom;
#endif

#if defined(E2K) || defined(IA64)

  GC_INNER void GC_push_all_register_sections(ptr_t bs_lo, ptr_t bs_hi,
                  int eager, struct GC_traced_stack_sect_s *traced_stack_sect);
#endif
# 1841 "gc_priv.h"
#ifdef USE_MARK_BYTES
#define mark_bit_from_hdr(hhdr,n) ((hhdr)->hb_marks[n])
#define set_mark_bit_from_hdr(hhdr,n) ((hhdr)->hb_marks[n] = 1)
#define clear_mark_bit_from_hdr(hhdr,n) ((hhdr)->hb_marks[n] = 0)
#else


# if defined(PARALLEL_MARK) || (defined(THREAD_SANITIZER) && defined(THREADS))




#define OR_WORD(addr,bits) AO_or((volatile AO_t *)(addr), (AO_t)(bits))
# else
#define OR_WORD(addr,bits) (void)(*(addr) |= (bits))
# endif
#define mark_bit_from_hdr(hhdr,n) \
              (((hhdr)->hb_marks[divWORDSZ(n)] >> modWORDSZ(n)) & (word)1)
#define set_mark_bit_from_hdr(hhdr,n) \
              OR_WORD((hhdr)->hb_marks+divWORDSZ(n), (word)1 << modWORDSZ(n))
#define clear_mark_bit_from_hdr(hhdr,n) \
              ((hhdr)->hb_marks[divWORDSZ(n)] &= ~((word)1 << modWORDSZ(n)))
#endif

#ifdef MARK_BIT_PER_OBJ
#define MARK_BIT_NO(offset,sz) (((word)(offset))/(sz))


#define MARK_BIT_OFFSET(sz) 1

#define IF_PER_OBJ(x) x
#define FINAL_MARK_BIT(sz) ((sz) > MAXOBJBYTES? 1 : HBLK_OBJS(sz))

#else
#define MARK_BIT_NO(offset,sz) BYTES_TO_GRANULES((word)(offset))
#define MARK_BIT_OFFSET(sz) BYTES_TO_GRANULES(sz)
#define IF_PER_OBJ(x) 
#define FINAL_MARK_BIT(sz) \
                ((sz) > MAXOBJBYTES ? MARK_BITS_PER_HBLK \
                                : BYTES_TO_GRANULES((sz) * HBLK_OBJS(sz)))
#endif



GC_INNER ptr_t GC_approx_sp(void);

GC_INNER GC_bool GC_should_collect(void);

GC_INNER struct hblk * GC_next_block(struct hblk *h, GC_bool allow_free);




GC_INNER struct hblk * GC_prev_block(struct hblk * h);




GC_INNER void GC_mark_init(void);
GC_INNER void GC_clear_marks(void);

GC_INNER void GC_invalidate_mark_state(void);




GC_INNER GC_bool GC_mark_some(ptr_t cold_gc_frame);




GC_INNER void GC_initiate_gc(void);





GC_INNER GC_bool GC_collection_in_progress(void);


#define GC_PUSH_ALL_SYM(sym) \
                GC_push_all(( void *)&(sym), \
                            ( void *)(&(sym) + 1))

GC_INNER void GC_push_all_stack(ptr_t b, ptr_t t);



#ifdef NO_VDB_FOR_STATIC_ROOTS
#define GC_push_conditional_static(b,t,all) \
                ((void)(all), GC_push_all(b, t))
#else



  GC_INNER void GC_push_conditional_static(void *b, void *t, GC_bool all);
#endif

#if defined(WRAP_MARK_SOME) && defined(PARALLEL_MARK)


  GC_INNER void GC_push_conditional_eager(void *bottom, void *top,
                                          GC_bool all);
#endif







GC_INNER void GC_push_roots(GC_bool all, ptr_t cold_gc_frame);


GC_API_PRIV GC_push_other_roots_proc GC_push_other_roots;
# 1965 "gc_priv.h"
#ifdef THREADS
  void GC_push_thread_structures(void);
#endif
GC_EXTERN void (*GC_push_typed_structures)(void);



GC_INNER void GC_with_callee_saves_pushed(void (*fn)(ptr_t, void *),
                                          volatile ptr_t arg);

#if defined(E2K) || defined(IA64) || defined(SPARC)


  ptr_t GC_save_regs_in_stack(void);
#endif

#ifdef E2K




  GC_INNER size_t GC_get_procedure_stack(ptr_t, size_t);

# if defined(CPPCHECK)
#define PS_ALLOCA_BUF(sz) NULL
#define ALLOCA_SAFE_LIMIT 0
# else
#define PS_ALLOCA_BUF(sz) alloca(sz)
# ifndef ALLOCA_SAFE_LIMIT
#define ALLOCA_SAFE_LIMIT (HBLKSIZE*256)
# endif
# endif






#define GET_PROCEDURE_STACK_LOCAL(pbuf,psz) \
        do { \
          size_t capacity = 0; \
          GC_ASSERT(GC_page_size != 0); \
          for (*(pbuf) = NULL; ; capacity = *(psz)) { \
            *(psz) = GC_get_procedure_stack(*(pbuf), capacity); \
            if (*(psz) <= capacity) break; \
            if (*(psz) > ALLOCA_SAFE_LIMIT \
                || EXPECT(capacity != 0, FALSE)) { \
                                                                \
              if (EXPECT(capacity > ALLOCA_SAFE_LIMIT, FALSE)) \
                GC_unmap_procedure_stack_buf(*(pbuf),capacity); \
              *(psz) = ROUNDUP_PAGESIZE(*(psz)); \
              *(pbuf) = GC_mmap_procedure_stack_buf(*(psz)); \
            } else { \
                                                                \
              *(pbuf) = PS_ALLOCA_BUF(*(psz)); \
            } \
          } \
          if (capacity > ALLOCA_SAFE_LIMIT \
              && EXPECT(((capacity - *(psz)) \
                         & ~(GC_page_size-1)) != 0, FALSE)) { \
                                                                \
                                                                \
            *(psz) = capacity - (GC_page_size - 1); \
          } \
        } while (0)


#define FREE_PROCEDURE_STACK_LOCAL(buf,sz) \
        (void)((sz) > ALLOCA_SAFE_LIMIT \
                ? (GC_unmap_procedure_stack_buf(buf, sz), 0) : 0)

  GC_INNER ptr_t GC_mmap_procedure_stack_buf(size_t);
  GC_INNER void GC_unmap_procedure_stack_buf(ptr_t, size_t);

# ifdef THREADS







    GC_INNER size_t GC_alloc_and_get_procedure_stack(ptr_t *pbuf);
# endif
#endif

#if defined(E2K) && defined(USE_PTR_HWTAG)

# if defined(__ptr64__)
#define LOAD_TAGGED_VALUE(v,tag,p) \
        do { \
          word val; \
          __asm__ __volatile__ ( \
            "ldd, sm %[adr], 0x0, %[val]\n\t" \
            "gettagd %[val], %[tag]\n" \
            : [val] "=r" (val), \
              [tag] "=r" (tag) \
            : [adr] "r" (p)); \
          v = val; \
        } while (0)
# elif !defined(CPPCHECK)
# error Unsupported -march for e2k target
# endif

#define LOAD_WORD_OR_CONTINUE(v,p) \
        { \
          int tag LOCAL_VAR_INIT_OK; \
          LOAD_TAGGED_VALUE(v, tag, p); \
          if (tag != 0) continue; \
        }
#else
#define LOAD_WORD_OR_CONTINUE(v,p) (void)(v = *(word *)(p))
#endif

#if defined(AMIGA) || defined(MACOS) || defined(GC_DARWIN_THREADS)
  void GC_push_one(word p);






#endif

#ifdef GC_WIN32_THREADS

  GC_INNER void GC_push_many_regs(const word *regs, unsigned count);
#endif

#if defined(PRINT_BLACK_LIST) || defined(KEEP_BACK_PTRS)
  GC_INNER void GC_mark_and_push_stack(ptr_t p, ptr_t source);

#else
  GC_INNER void GC_mark_and_push_stack(ptr_t p);
#endif

GC_INNER void GC_clear_hdr_marks(hdr * hhdr);

GC_INNER void GC_set_hdr_marks(hdr * hhdr);

GC_INNER void GC_set_fl_marks(ptr_t p);


#if defined(GC_ASSERTIONS) && defined(THREAD_LOCAL_ALLOC)
  void GC_check_fl_marks(void **);



#endif
void GC_add_roots_inner(ptr_t b, ptr_t e, GC_bool tmp);
#ifdef USE_PROC_FOR_LIBRARIES
  GC_INNER void GC_remove_roots_subregion(ptr_t b, ptr_t e);
#endif
GC_INNER void GC_exclude_static_roots_inner(void *start, void *finish);
#if defined(DYNAMIC_LOADING) || defined(MSWIN32) || defined(MSWINCE) \
    || defined(CYGWIN32) || defined(PCR)
  GC_INNER void GC_register_dynamic_libraries(void);

#endif
GC_INNER void GC_cond_register_dynamic_libraries(void);




ptr_t GC_get_main_stack_base(void);
#ifdef IA64
  GC_INNER ptr_t GC_get_register_stack_base(void);

#endif

void GC_register_data_segments(void);

#ifdef THREADS

  GC_INNER void GC_thr_init(void);
  GC_INNER void GC_init_parallel(void);
#else
  GC_INNER GC_bool GC_is_static_root(void *p);


# ifdef TRACE_BUF
    void GC_add_trace_entry(char *kind, word arg1, word arg2);
# endif
#endif


#ifdef PRINT_BLACK_LIST
  GC_INNER void GC_add_to_black_list_normal(word p, ptr_t source);


#define GC_ADD_TO_BLACK_LIST_NORMAL(bits,source) \
                if (GC_all_interior_pointers) { \
                  GC_add_to_black_list_stack((word)(bits), (source)); \
                } else \
                  GC_add_to_black_list_normal((word)(bits), (source))
  GC_INNER void GC_add_to_black_list_stack(word p, ptr_t source);
#define GC_ADD_TO_BLACK_LIST_STACK(bits,source) \
            GC_add_to_black_list_stack((word)(bits), (source))
#else
  GC_INNER void GC_add_to_black_list_normal(word p);
#define GC_ADD_TO_BLACK_LIST_NORMAL(bits,source) \
                if (GC_all_interior_pointers) { \
                  GC_add_to_black_list_stack((word)(bits)); \
                } else \
                  GC_add_to_black_list_normal((word)(bits))
  GC_INNER void GC_add_to_black_list_stack(word p);
#define GC_ADD_TO_BLACK_LIST_STACK(bits,source) \
            GC_add_to_black_list_stack((word)(bits))
#endif

GC_INNER void GC_promote_black_lists(void);

GC_INNER void GC_unpromote_black_lists(void);




GC_INNER ptr_t GC_scratch_alloc(size_t bytes);




#ifdef GWW_VDB

#else
#define GC_scratch_recycle_no_gww GC_scratch_recycle_inner
#endif
GC_INNER void GC_scratch_recycle_inner(void *ptr, size_t bytes);



#ifdef MARK_BIT_PER_GRANULE
  GC_INNER GC_bool GC_add_map_entry(size_t sz);



#endif

GC_INNER void GC_register_displacement_inner(size_t offset);




GC_INNER void GC_new_hblk(size_t size_in_granules, int kind);



GC_INNER ptr_t GC_build_fl(struct hblk *h, size_t words, GC_bool clear,
                           ptr_t list);







GC_INNER struct hblk * GC_allochblk(size_t size_in_bytes, int kind,
                                    unsigned flags);




GC_INNER ptr_t GC_alloc_large(size_t lb, int k, unsigned flags);
# 2237 "gc_priv.h"
GC_INNER void GC_freehblk(struct hblk * p);




GC_INNER GC_bool GC_expand_hp_inner(word n);
GC_INNER void GC_start_reclaim(GC_bool abort_if_found);





GC_INNER void GC_continue_reclaim(word sz, int kind);





GC_INNER GC_bool GC_reclaim_all(GC_stop_func stop_func, GC_bool ignore_old);


GC_INNER ptr_t GC_reclaim_generic(struct hblk * hbp, hdr *hhdr, size_t sz,
                                  GC_bool init, ptr_t list,
                                  signed_word *count);





GC_INNER GC_bool GC_block_empty(hdr * hhdr);

GC_INNER int GC_CALLBACK GC_never_stop_func(void);

GC_INNER GC_bool GC_try_to_collect_inner(GC_stop_func f);





#define GC_gcollect_inner() \
                (void)GC_try_to_collect_inner(GC_never_stop_func)

#ifdef THREADS
  GC_EXTERN GC_bool GC_in_thread_creation;



#endif

GC_EXTERN GC_bool GC_is_initialized;

GC_INNER void GC_collect_a_little_inner(int n);





GC_INNER void * GC_generic_malloc_inner(size_t lb, int k);


#if defined(DBG_HDRS_ALL) || defined(GC_GCJ_SUPPORT) \
    || !defined(GC_NO_FINALIZATION)
  GC_INNER void * GC_generic_malloc_inner_ignore_off_page(size_t lb, int k);





#endif

GC_INNER GC_bool GC_collect_or_expand(word needed_blocks,
                                      GC_bool ignore_off_page, GC_bool retry);

GC_INNER ptr_t GC_allocobj(size_t sz, int kind);




#ifdef GC_ADD_CALLER



# ifdef GC_HAVE_RETURN_ADDR_PARENT
#define GC_DBG_EXTRAS GC_RETURN_ADDR_PARENT, NULL, 0
# else
#define GC_DBG_EXTRAS GC_RETURN_ADDR, NULL, 0
# endif
#else
#define GC_DBG_EXTRAS "unknown", 0
#endif

#ifdef GC_COLLECT_AT_MALLOC
  extern size_t GC_dbg_collect_at_malloc_min_lb;

#define GC_DBG_COLLECT_AT_MALLOC(lb) \
                (void)((lb) >= GC_dbg_collect_at_malloc_min_lb ? \
                            (GC_gcollect(), 0) : 0)
#else
#define GC_DBG_COLLECT_AT_MALLOC(lb) (void)0
#endif


#if defined(THREAD_LOCAL_ALLOC) && defined(GC_GCJ_SUPPORT)
    GC_INNER void * GC_core_gcj_malloc(size_t, void *);
#endif

GC_INNER void GC_init_headers(void);
GC_INNER struct hblkhdr * GC_install_header(struct hblk *h);



GC_INNER GC_bool GC_install_counts(struct hblk * h, size_t sz);



GC_INNER void GC_remove_header(struct hblk * h);

GC_INNER void GC_remove_counts(struct hblk * h, size_t sz);

GC_INNER hdr * GC_find_header(ptr_t h);

#ifdef USE_PROC_FOR_LIBRARIES
  GC_INNER void GC_add_to_our_memory(ptr_t p, size_t bytes);

#else
#define GC_add_to_our_memory(p,bytes) \
                (GC_our_mem_bytes += (bytes), (void)(p))
#endif

GC_INNER void GC_print_all_errors(void);



GC_EXTERN void (*GC_check_heap)(void);



GC_EXTERN void (*GC_print_all_smashed)(void);


GC_EXTERN void (*GC_print_heap_obj)(ptr_t p);




#if defined(LINUX) && defined(__ELF__) && !defined(SMALL_CONFIG)
  void GC_print_address_map(void);

#endif

#ifndef SHORT_DBG_HDRS
  GC_EXTERN GC_bool GC_findleak_delay_free;



  GC_INNER GC_bool GC_check_leaked(ptr_t base);
#endif

#ifdef AO_HAVE_store
  GC_EXTERN volatile AO_t GC_have_errors;
#define GC_SET_HAVE_ERRORS() AO_store(&GC_have_errors, (AO_t)TRUE)
#define get_have_errors() ((GC_bool)AO_load(&GC_have_errors))

#else
  GC_EXTERN GC_bool GC_have_errors;
#define GC_SET_HAVE_ERRORS() (void)(GC_have_errors = TRUE)
#define get_have_errors() GC_have_errors
#endif





#define VERBOSE 2
#if !defined(NO_CLOCK) || !defined(SMALL_CONFIG)

  extern int GC_print_stats;

#else
#define GC_print_stats 0


#endif

#ifdef KEEP_BACK_PTRS
  GC_EXTERN long GC_backtraces;
#endif

#if defined(THREADS) || defined(LINT2)


#define GC_RAND_MAX ((int)(~0U >> 1))
# if defined(AO_HAVE_store) && defined(THREAD_SANITIZER)
#define GC_RAND_STATE_T volatile AO_t
#define GC_RAND_NEXT(pseed) GC_rand_next(pseed)
    GC_INLINE int GC_rand_next(GC_RAND_STATE_T *pseed)
    {
      AO_t next = (AO_t)((AO_load(pseed) * 1103515245U + 12345)
                         & (unsigned)GC_RAND_MAX);
      AO_store(pseed, next);
      return (int)next;
    }
# else
#define GC_RAND_STATE_T unsigned
#define GC_RAND_NEXT(pseed) \
                (int)(*(pseed) = (*(pseed) * 1103515245U + 12345) \
                                 & (unsigned)GC_RAND_MAX)
# endif
#endif

GC_EXTERN GC_bool GC_print_back_height;

#ifdef MAKE_BACK_GRAPH
  void GC_print_back_graph_stats(void);
#endif

#ifdef THREADS
  GC_INNER void GC_free_inner(void * p);
#endif



#ifdef DBG_HDRS_ALL
  GC_INNER void * GC_debug_generic_malloc_inner(size_t lb, int k);
  GC_INNER void * GC_debug_generic_malloc_inner_ignore_off_page(size_t lb,
                                                                int k);
#define GC_INTERNAL_MALLOC GC_debug_generic_malloc_inner
#define GC_INTERNAL_MALLOC_IGNORE_OFF_PAGE \
               GC_debug_generic_malloc_inner_ignore_off_page
# ifdef THREADS
    GC_INNER void GC_debug_free_inner(void * p);
#define GC_INTERNAL_FREE GC_debug_free_inner
# else
#define GC_INTERNAL_FREE GC_debug_free
# endif
#else
#define GC_INTERNAL_MALLOC GC_generic_malloc_inner
#define GC_INTERNAL_MALLOC_IGNORE_OFF_PAGE \
               GC_generic_malloc_inner_ignore_off_page
# ifdef THREADS
#define GC_INTERNAL_FREE GC_free_inner
# else
#define GC_INTERNAL_FREE GC_free
# endif
#endif

#ifdef USE_MUNMAP

  GC_INNER void GC_unmap_old(unsigned threshold);
  GC_INNER void GC_merge_unmapped(void);
  GC_INNER void GC_unmap(ptr_t start, size_t bytes);
  GC_INNER void GC_remap(ptr_t start, size_t bytes);
  GC_INNER void GC_unmap_gap(ptr_t start1, size_t bytes1, ptr_t start2,
                             size_t bytes2);


  GC_INLINE ptr_t GC_unmap_end(ptr_t start, size_t bytes)
  {
     return (ptr_t)((word)(start + bytes) & ~(GC_page_size - 1));
  }
#endif

#ifdef CAN_HANDLE_FORK
  GC_EXTERN int GC_handle_fork;
# 2514 "gc_priv.h"
#endif

#ifdef GC_DISABLE_INCREMENTAL
#define GC_incremental FALSE
#define GC_auto_incremental FALSE
#define GC_manual_vdb FALSE
#define GC_dirty(p) (void)(p)
#define REACHABLE_AFTER_DIRTY(p) (void)(p)

#else
  GC_EXTERN GC_bool GC_incremental;





  GC_INNER void GC_read_dirty(GC_bool output_unneeded);



  GC_INNER GC_bool GC_page_was_dirty(struct hblk *h);


  GC_INNER void GC_remove_protection(struct hblk *h, word nblocks,
                                   GC_bool pointerfree);
# 2549 "gc_priv.h"
# if !defined(NO_VDB_FOR_STATIC_ROOTS) && !defined(PROC_VDB)
    GC_INNER GC_bool GC_is_vdb_for_static_roots(void);

# endif

# ifdef CAN_HANDLE_FORK
# if defined(PROC_VDB) || defined(SOFT_VDB)
      GC_INNER void GC_dirty_update_child(void);



# else
#define GC_dirty_update_child() (void)0
# endif
# endif

  GC_INNER GC_bool GC_dirty_init(void);




  GC_EXTERN GC_bool GC_manual_vdb;




#define GC_auto_incremental (GC_incremental && !GC_manual_vdb)

  GC_INNER void GC_dirty_inner(const void *p);
#define GC_dirty(p) (GC_manual_vdb ? GC_dirty_inner(p) : (void)0)
#define REACHABLE_AFTER_DIRTY(p) GC_reachable_here(p)
#endif


#define GC_base_C(p) ((const void *)GC_base(( void *)(p)))


void GC_print_block_list(void);
void GC_print_hblkfreelist(void);
void GC_print_heap_sects(void);
void GC_print_static_roots(void);

#ifdef KEEP_BACK_PTRS
  GC_INNER void GC_store_back_pointer(ptr_t source, ptr_t dest);
  GC_INNER void GC_marked_for_finalization(ptr_t dest);
#define GC_STORE_BACK_PTR(source,dest) GC_store_back_pointer(source, dest)
#define GC_MARKED_FOR_FINALIZATION(dest) GC_marked_for_finalization(dest)
#else
#define GC_STORE_BACK_PTR(source,dest) (void)(source)
#define GC_MARKED_FOR_FINALIZATION(dest) 
#endif


void GC_noop6(word, word, word, word, word, word);

#ifndef GC_ATTR_FORMAT_PRINTF
# if GC_GNUC_PREREQ(3, 0)
#define GC_ATTR_FORMAT_PRINTF(spec_argnum,first_checked) \
        __attribute__((__format__(__printf__, spec_argnum, first_checked)))
# else
#define GC_ATTR_FORMAT_PRINTF(spec_argnum,first_checked) 
# endif
#endif





GC_API_PRIV void GC_printf(const char * format, ...)
                        GC_ATTR_FORMAT_PRINTF(1, 2);




GC_API_PRIV void GC_err_printf(const char * format, ...)
                        GC_ATTR_FORMAT_PRINTF(1, 2);



GC_API_PRIV void GC_log_printf(const char * format, ...)
                        GC_ATTR_FORMAT_PRINTF(1, 2);

#ifndef GC_ANDROID_LOG
#define GC_PRINT_STATS_FLAG (GC_print_stats != 0)
#define GC_INFOLOG_PRINTF GC_COND_LOG_PRINTF

#define GC_verbose_log_printf GC_log_printf
#else
  extern GC_bool GC_quiet;
#define GC_PRINT_STATS_FLAG (!GC_quiet)

# ifndef GC_INFOLOG_PRINTF
#define GC_INFOLOG_PRINTF if (GC_quiet) {} else GC_info_log_printf
# endif
  GC_INNER void GC_info_log_printf(const char *format, ...)
                        GC_ATTR_FORMAT_PRINTF(1, 2);
  GC_INNER void GC_verbose_log_printf(const char *format, ...)
                        GC_ATTR_FORMAT_PRINTF(1, 2);
#endif

#if defined(SMALL_CONFIG) || defined(GC_ANDROID_LOG)
#define GC_ERRINFO_PRINTF GC_INFOLOG_PRINTF
#else
#define GC_ERRINFO_PRINTF GC_log_printf
#endif


#define GC_COND_LOG_PRINTF \
                if (EXPECT(!GC_print_stats, TRUE)) {} else GC_log_printf
#define GC_VERBOSE_LOG_PRINTF \
    if (EXPECT(GC_print_stats != VERBOSE, TRUE)) {} else GC_verbose_log_printf
#ifndef GC_DBGLOG_PRINTF
#define GC_DBGLOG_PRINTF if (!GC_PRINT_STATS_FLAG) {} else GC_log_printf
#endif

void GC_err_puts(const char *s);





#define TO_KiB_UL(v) ((unsigned long)(((v) + ((1 << 9) - 1)) >> 10))

GC_EXTERN unsigned GC_fail_count;



GC_EXTERN long GC_large_alloc_warn_interval;

GC_EXTERN signed_word GC_bytes_found;



#ifndef GC_GET_HEAP_USAGE_NOT_NEEDED
  GC_EXTERN word GC_reclaimed_bytes_before_gc;


#endif

#ifdef USE_MUNMAP
  GC_EXTERN unsigned GC_unmap_threshold;
  GC_EXTERN GC_bool GC_force_unmap_on_gcollect;
#endif

#ifdef MSWIN32
  GC_EXTERN GC_bool GC_no_win32_dlls;
  GC_EXTERN GC_bool GC_wnt;

#endif

#ifdef THREADS
# if (defined(MSWIN32) && !defined(CONSOLE_LOG)) || defined(MSWINCE)
    GC_EXTERN CRITICAL_SECTION GC_write_cs;
# ifdef GC_ASSERTIONS
      GC_EXTERN GC_bool GC_write_disabled;



# endif
# endif
# if defined(GC_DISABLE_INCREMENTAL) || defined(HAVE_LOCKFREE_AO_OR)
#define GC_acquire_dirty_lock() (void)0
#define GC_release_dirty_lock() (void)0
# else



#define GC_acquire_dirty_lock() \
        do { \
        } while (AO_test_and_set_acquire(&GC_fault_handler_lock) == AO_TS_SET)
#define GC_release_dirty_lock() AO_CLEAR(&GC_fault_handler_lock)
    GC_EXTERN volatile AO_TS_t GC_fault_handler_lock;

# endif
# ifdef MSWINCE
    GC_EXTERN GC_bool GC_dont_query_stack_min;

# endif
#elif defined(IA64)
  GC_EXTERN ptr_t GC_save_regs_ret_val;

#endif

#ifdef THREAD_LOCAL_ALLOC
  GC_EXTERN GC_bool GC_world_stopped;
  GC_INNER void GC_mark_thread_local_free_lists(void);
#endif

#if defined(GLIBC_2_19_TSX_BUG) && defined(THREADS)

  GC_INNER int GC_parse_version(int *pminor, const char *pverstr);
#endif

#if defined(MPROTECT_VDB) && defined(GWW_VDB)
    GC_INNER GC_bool GC_gww_dirty_init(void);



#endif

#if defined(CHECKSUMS) || defined(PROC_VDB)
  GC_INNER GC_bool GC_page_was_ever_dirty(struct hblk * h);

#endif

#ifdef CHECKSUMS
# if defined(MPROTECT_VDB) && !defined(DARWIN)
    void GC_record_fault(struct hblk * h);
# endif
  void GC_check_dirty(void);
#endif

GC_INNER void GC_default_print_heap_obj_proc(ptr_t p);

GC_INNER void GC_setpagesize(void);

GC_INNER void GC_initialize_offsets(void);

GC_INNER void GC_bl_init(void);
GC_INNER void GC_bl_init_no_interiors(void);

GC_INNER void GC_start_debugging_inner(void);




GC_INNER void *GC_store_debug_info_inner(void *p, word sz, const char *str,
                                         int linenum);

#ifdef REDIRECT_MALLOC
# ifdef GC_LINUX_THREADS
    GC_INNER GC_bool GC_text_mapping(char *nm, ptr_t *startp, ptr_t *endp);

# endif
#elif defined(USE_WINALLOC)
  GC_INNER void GC_add_current_malloc_heap(void);
#endif

#ifdef MAKE_BACK_GRAPH
  GC_INNER void GC_build_back_graph(void);
  GC_INNER void GC_traverse_back_graph(void);
#endif

#ifdef MSWIN32
  GC_INNER void GC_init_win32(void);
#endif

#if !defined(MSWIN32) && !defined(MSWINCE) && !defined(CYGWIN32)
  GC_INNER void * GC_roots_present(ptr_t);


#endif

#ifdef GC_WIN32_THREADS
  GC_INNER void GC_get_next_stack(char *start, char * limit, char **lo,
                                  char **hi);
# if defined(MPROTECT_VDB) && !defined(CYGWIN32)
    GC_INNER void GC_set_write_fault_handler(void);
# endif
# if defined(WRAP_MARK_SOME) && !defined(GC_PTHREADS)
    GC_INNER GC_bool GC_started_thread_while_stopped(void);

# endif
#endif

#ifdef THREADS
# ifndef GC_NO_FINALIZATION
    GC_INNER void GC_reset_finalizer_nested(void);
    GC_INNER unsigned char *GC_check_finalizer_nested(void);
# endif
  GC_INNER void GC_do_blocking_inner(ptr_t data, void * context);
  GC_INNER void GC_push_all_stacks(void);
# ifdef USE_PROC_FOR_LIBRARIES
    GC_INNER GC_bool GC_segment_is_thread_stack(ptr_t lo, ptr_t hi);
# endif
# if (defined(HAVE_PTHREAD_ATTR_GET_NP) || defined(HAVE_PTHREAD_GETATTR_NP)) \
     && defined(IA64)
    GC_INNER ptr_t GC_greatest_stack_base_below(ptr_t bound);
# endif
#endif

#ifdef DYNAMIC_LOADING
  GC_INNER GC_bool GC_register_main_static_data(void);
# ifdef DARWIN
    GC_INNER void GC_init_dyld(void);
# endif
#endif

#ifdef SEARCH_FOR_DATA_START
  GC_INNER void GC_init_linux_data_start(void);
  void * GC_find_limit(void *, int);
#endif

#ifdef UNIX_LIKE
  GC_INNER void GC_set_and_save_fault_handler(void (*handler)(int));
#endif

#ifdef NEED_PROC_MAPS
# if defined(DYNAMIC_LOADING) && defined(USE_PROC_FOR_LIBRARIES)
    GC_INNER const char *GC_parse_map_entry(const char *maps_ptr,
                                            ptr_t *start, ptr_t *end,
                                            const char **prot,
                                            unsigned *maj_dev,
                                            const char **mapping_name);
# endif
# if defined(IA64) || defined(INCLUDE_LINUX_THREAD_DESCR)
    GC_INNER GC_bool GC_enclosing_mapping(ptr_t addr,
                                          ptr_t *startp, ptr_t *endp);
# endif
  GC_INNER const char *GC_get_maps(void);
#endif

#ifdef GC_ASSERTIONS
#define GC_ASSERT(expr) \
              do { \
                if (!(expr)) { \
                  GC_err_printf("Assertion failure: %s:%d\n", \
                                __FILE__, __LINE__); \
                  ABORT("assertion failure"); \
                } \
              } while (0)
  GC_INNER word GC_compute_large_free_bytes(void);
  GC_INNER word GC_compute_root_size(void);
#else
#define GC_ASSERT(expr) 
#endif


#if _MSC_VER >= 1700
#define GC_STATIC_ASSERT(expr) \
                static_assert(expr, "static assertion failed: " #expr)
#elif defined(static_assert) && __STDC_VERSION__ >= 201112L
#define GC_STATIC_ASSERT(expr) static_assert(expr, #expr)
#elif defined(mips) && !defined(__GNUC__)


#define GC_STATIC_ASSERT(expr) \
    do { if (0) { char j[(expr)? 1 : -1]; j[0]='\0'; j[0]=j[0]; } } while(0)
#else

#define GC_STATIC_ASSERT(expr) (void)sizeof(char[(expr)? 1 : -1])
#endif


#if GC_GNUC_PREREQ(4, 0)

#define NONNULL_ARG_NOT_NULL(arg) (*(volatile void **)&(arg) != NULL)
#else
#define NONNULL_ARG_NOT_NULL(arg) (NULL != (arg))
#endif

#define COND_DUMP_CHECKS \
          do { \
            GC_ASSERT(GC_compute_large_free_bytes() == GC_large_free_bytes); \
            GC_ASSERT(GC_compute_root_size() == GC_root_size); \
          } while (0)

#ifndef NO_DEBUGGING
  GC_EXTERN GC_bool GC_dump_regularly;

#define COND_DUMP if (EXPECT(GC_dump_regularly, FALSE)) { \
                        GC_dump_named(NULL); \
                   } else COND_DUMP_CHECKS
#else
#define COND_DUMP COND_DUMP_CHECKS
#endif

#if defined(PARALLEL_MARK)





#define GC_markers_m1 GC_parallel



  GC_EXTERN GC_bool GC_parallel_mark_disabled;
# 2940 "gc_priv.h"
  GC_INNER void GC_wait_for_markers_init(void);
  GC_INNER void GC_acquire_mark_lock(void);
  GC_INNER void GC_release_mark_lock(void);
  GC_INNER void GC_notify_all_builder(void);
  GC_INNER void GC_wait_for_reclaim(void);

  GC_EXTERN signed_word GC_fl_builder_count;

  GC_INNER void GC_notify_all_marker(void);
  GC_INNER void GC_wait_marker(void);
  GC_EXTERN word GC_mark_no;

  GC_INNER void GC_help_marker(word my_mark_no);





  GC_INNER void GC_start_mark_threads_inner(void);
#endif

#if defined(SIGNAL_BASED_STOP_WORLD) && !defined(SIG_SUSPEND)






# ifdef THREAD_SANITIZER






#define SIG_SUSPEND SIGSYS
# elif (defined(GC_LINUX_THREADS) || defined(GC_DGUX386_THREADS)) \
       && !defined(GC_USESIGRT_SIGNALS)
# if defined(SPARC) && !defined(SIGPWR)


#define SIG_SUSPEND SIGLOST
# else

#define SIG_SUSPEND SIGPWR
# endif
# elif defined(GC_FREEBSD_THREADS) && defined(__GLIBC__) \
       && !defined(GC_USESIGRT_SIGNALS)
#define SIG_SUSPEND (32+6)
# elif (defined(GC_FREEBSD_THREADS) || defined(HURD) || defined(RTEMS)) \
       && !defined(GC_USESIGRT_SIGNALS)
#define SIG_SUSPEND SIGUSR1

# elif defined(GC_OPENBSD_THREADS) && !defined(GC_USESIGRT_SIGNALS)
# ifndef GC_OPENBSD_UTHREADS
#define SIG_SUSPEND SIGXFSZ
# endif
# elif defined(_SIGRTMIN) && !defined(CPPCHECK)
#define SIG_SUSPEND _SIGRTMIN + 6
# else
#define SIG_SUSPEND SIGRTMIN + 6
# endif
#endif

#if defined(GC_PTHREADS) && !defined(GC_SEM_INIT_PSHARED)
#define GC_SEM_INIT_PSHARED 0
#endif





#if (defined(UNIX_LIKE) || (defined(NEED_FIND_LIMIT) && defined(CYGWIN32))) \
    && !defined(GC_NO_SIGSETJMP)
# if defined(SUNOS5SIGS) && !defined(FREEBSD) && !defined(LINUX)
    EXTERN_C_END
# include <sys/siginfo.h>
    EXTERN_C_BEGIN
# endif


#define SETJMP(env) sigsetjmp(env, 1)
#define LONGJMP(env,val) siglongjmp(env, val)
#define JMP_BUF sigjmp_buf
#else
# ifdef ECOS
#define SETJMP(env) hal_setjmp(env)
# else
#define SETJMP(env) setjmp(env)
# endif
#define LONGJMP(env,val) longjmp(env, val)
#define JMP_BUF jmp_buf
#endif

#if defined(DATASTART_USES_BSDGETDATASTART)
  EXTERN_C_END
# include <machine/trap.h>
  EXTERN_C_BEGIN
  GC_INNER ptr_t GC_FreeBSDGetDataStart(size_t, ptr_t);
#define DATASTART_IS_FUNC 
#endif

#if defined(NEED_FIND_LIMIT) \
     || (defined(WRAP_MARK_SOME) && !defined(MSWIN32) && !defined(MSWINCE)) \
     || (defined(USE_PROC_FOR_LIBRARIES) && defined(THREADS))
  GC_EXTERN JMP_BUF GC_jmp_buf;



  GC_INNER void GC_setup_temporary_fault_handler(void);

  GC_INNER void GC_reset_fault_handler(void);
#endif


#if defined(CANCEL_SAFE)
# if defined(GC_ASSERTIONS) \
     && (defined(USE_COMPILER_TLS) \
         || (defined(LINUX) && !defined(ARM32) && GC_GNUC_PREREQ(3, 3) \
             || defined(HPUX) ))
    extern __thread unsigned char GC_cancel_disable_count;
#define NEED_CANCEL_DISABLE_COUNT 
#define INCR_CANCEL_DISABLE() ++GC_cancel_disable_count
#define DECR_CANCEL_DISABLE() --GC_cancel_disable_count
#define ASSERT_CANCEL_DISABLED() GC_ASSERT(GC_cancel_disable_count > 0)
# else
#define INCR_CANCEL_DISABLE() 
#define DECR_CANCEL_DISABLE() 
#define ASSERT_CANCEL_DISABLED() (void)0
# endif
#define DISABLE_CANCEL(state) \
        do { pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &state); \
          INCR_CANCEL_DISABLE(); } while (0)
#define RESTORE_CANCEL(state) \
        do { ASSERT_CANCEL_DISABLED(); \
          pthread_setcancelstate(state, NULL); \
          DECR_CANCEL_DISABLE(); } while (0)
#else
#define DISABLE_CANCEL(state) (void)0
#define RESTORE_CANCEL(state) (void)0
#define ASSERT_CANCEL_DISABLED() (void)0
#endif

EXTERN_C_END

#endif
