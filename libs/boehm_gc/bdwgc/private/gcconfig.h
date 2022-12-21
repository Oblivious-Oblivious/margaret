# 1 "gcconfig.h"
# 26 "gcconfig.h"
#ifndef GCCONFIG_H
#define GCCONFIG_H 

#ifdef CPPCHECK
#undef CLOCKS_PER_SEC
#undef FIXUP_POINTER
#undef POINTER_MASK
#undef POINTER_SHIFT
#undef REDIRECT_REALLOC
#undef _MAX_PATH
#endif

#ifndef PTR_T_DEFINED
  typedef char * ptr_t;
#define PTR_T_DEFINED 
#endif

#if !defined(sony_news)
# include <stddef.h>
#endif





#ifdef __cplusplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C_BEGIN 
#define EXTERN_C_END 
#endif

EXTERN_C_BEGIN


#if defined(__clang__) && defined(__clang_major__)
#define GC_CLANG_PREREQ(major,minor) \
    ((__clang_major__ << 16) + __clang_minor__ >= ((major) << 16) + (minor))
#define GC_CLANG_PREREQ_FULL(major,minor,patchlevel) \
            (GC_CLANG_PREREQ(major, (minor) + 1) \
                || (__clang_major__ == (major) && __clang_minor__ == (minor) \
                    && __clang_patchlevel__ >= (patchlevel)))
#else
#define GC_CLANG_PREREQ(major,minor) 0
#define GC_CLANG_PREREQ_FULL(major,minor,patchlevel) 0
#endif

#ifdef LINT2






#define COVERT_DATAFLOW(w) (~(GC_word)(w)^(~(GC_word)0))
#else
#define COVERT_DATAFLOW(w) ((GC_word)(w))
#endif






#if defined(__ANDROID__) && !defined(HOST_ANDROID)

#define HOST_ANDROID 1
#endif

#if defined(TIZEN) && !defined(HOST_TIZEN)
#define HOST_TIZEN 1
#endif

#if defined(__SYMBIAN32__) && !defined(SYMBIAN)
#define SYMBIAN 
# ifdef __WINS__
#pragma data_seg(".data2")
# endif
#endif


# if (defined(linux) || defined(__linux__) || defined(HOST_ANDROID)) \
     && !defined(LINUX) && !defined(__native_client__)
#define LINUX 
# endif


# if defined(__NetBSD__)
#define NETBSD 
# endif


# if defined(__OpenBSD__)
#define OPENBSD 
# endif


# if (defined(__FreeBSD__) || defined(__DragonFly__) \
      || defined(__FreeBSD_kernel__)) && !defined(FREEBSD) \
     && !defined(GC_NO_FREEBSD)
#define FREEBSD 
# endif


# if defined(macosx) || (defined(__APPLE__) && defined(__MACH__))
#define DARWIN 
    EXTERN_C_END
# include <TargetConditionals.h>
    EXTERN_C_BEGIN
# endif


# if defined(__native_client__)
#define NACL 
# if !defined(__portable_native_client__) && !defined(__arm__)
#define I386 
#define mach_type_known 
# else

# endif
# endif
# if defined(__aarch64__)
#define AARCH64 
# if !defined(LINUX) && !defined(DARWIN) && !defined(FREEBSD) \
       && !defined(NETBSD) && !defined(NN_BUILD_TARGET_PLATFORM_NX) \
       && !defined(OPENBSD) && !defined(_WIN32)
#define NOSYS 
#define mach_type_known 
# endif
# endif
# if defined(__arm) || defined(__arm__) || defined(__thumb__)
#define ARM32 
# if defined(NACL)
#define mach_type_known 
# elif !defined(LINUX) && !defined(NETBSD) && !defined(FREEBSD) \
         && !defined(OPENBSD) && !defined(DARWIN) && !defined(_WIN32) \
         && !defined(__CEGCC__) && !defined(NN_PLATFORM_CTR) \
         && !defined(GC_NO_NOSYS) && !defined(SN_TARGET_PSP2) \
         && !defined(SYMBIAN)
#define NOSYS 
#define mach_type_known 
# endif
# endif
# if defined(sun) && defined(mc68000) && !defined(CPPCHECK)
# error SUNOS4 no longer supported
# endif
# if defined(hp9000s300) && !defined(CPPCHECK)
# error M68K based HP machines no longer supported
# endif
# if defined(OPENBSD) && defined(m68k)
#define M68K 
#define mach_type_known 
# endif
# if defined(OPENBSD) && defined(__sparc__)
#define SPARC 
#define mach_type_known 
# endif
# if defined(OPENBSD) && defined(__arm__)
#define ARM32 
#define mach_type_known 
# endif
# if defined(OPENBSD) && defined(__aarch64__)
#define AARCH64 
#define mach_type_known 
# endif
# if defined(OPENBSD) && defined(__sh__)
#define SH 
#define mach_type_known 
# endif
# if defined(NETBSD) && (defined(m68k) || defined(__m68k__))
#define M68K 
#define mach_type_known 
# endif
# if defined(NETBSD) && defined(__powerpc__)
#define POWERPC 
#define mach_type_known 
# endif
# if defined(NETBSD) && (defined(__arm32__) || defined(__arm__))
#define ARM32 
#define mach_type_known 
# endif
# if defined(NETBSD) && defined(__aarch64__)
#define AARCH64 
#define mach_type_known 
# endif
# if defined(NETBSD) && defined(__sh__)
#define SH 
#define mach_type_known 
# endif
# if defined(vax) || defined(__vax__)
#define VAX 
# ifdef ultrix
#define ULTRIX 
# else
#define BSD 
# endif
#define mach_type_known 
# endif
# if defined(NETBSD) && defined(__vax__)
#define VAX 
#define mach_type_known 
# endif
# if defined(mips) || defined(__mips) || defined(_mips)
#define MIPS 
# if defined(nec_ews) || defined(_nec_ews)
#define EWS4800 
# endif
# if !defined(LINUX) && !defined(EWS4800) && !defined(NETBSD) \
       && !defined(OPENBSD)
# if defined(ultrix) || defined(__ultrix)
#define ULTRIX 
# else
#define IRIX5 
# endif
# endif
# if defined(NETBSD) && defined(__MIPSEL__)
#undef ULTRIX
# endif
#define mach_type_known 
# endif
# if defined(__QNX__)
#define I386 
#define mach_type_known 
# endif
# if defined(__NIOS2__) || defined(__NIOS2) || defined(__nios2__)
#define NIOS2 
#define mach_type_known 
# endif
# if defined(__or1k__)
#define OR1K 
#define mach_type_known 
# endif
# if defined(DGUX) && (defined(i386) || defined(__i386__))
#define I386 
# ifndef _USING_DGUX
#define _USING_DGUX 
# endif
#define mach_type_known 
# endif
# if defined(sequent) && (defined(i386) || defined(__i386__))
#define I386 
#define SEQUENT 
#define mach_type_known 
# endif
# if (defined(sun) || defined(__sun)) && (defined(i386) || defined(__i386__))
#define I386 
#define SOLARIS 
#define mach_type_known 
# endif
# if (defined(sun) || defined(__sun)) && defined(__amd64)
#define X86_64 
#define SOLARIS 
#define mach_type_known 
# endif
# if (defined(__OS2__) || defined(__EMX__)) && defined(__32BIT__)
#define I386 
#define OS2 
#define mach_type_known 
# endif
# if defined(ibm032) && !defined(CPPCHECK)
# error IBM PC/RT no longer supported
# endif
# if (defined(sun) || defined(__sun)) && (defined(sparc) || defined(__sparc))

    EXTERN_C_END
# include <errno.h>
    EXTERN_C_BEGIN
#define SPARC 
#define SOLARIS 
#define mach_type_known 
# elif defined(sparc) && defined(unix) && !defined(sun) && !defined(linux) \
       && !defined(FREEBSD) && !defined(NETBSD) && !defined(OPENBSD)
#define SPARC 
#define DRSNX 
#define mach_type_known 
# endif
# if defined(_IBMR2)
#define POWERPC 
#define AIX 
#define mach_type_known 
# endif
# if defined(NETBSD) && defined(__sparc__)
#define SPARC 
#define mach_type_known 
# endif
# if defined(_M_XENIX) && defined(_M_SYSV) && defined(_M_I386)

#define I386 
# if defined(_SCO_ELF)
#define SCO_ELF 
# else
#define SCO 
# endif
#define mach_type_known 
# endif
# if defined(_AUX_SOURCE) && !defined(CPPCHECK)
# error A/UX no longer supported
# endif
# if defined(_PA_RISC1_0) || defined(_PA_RISC1_1) || defined(_PA_RISC2_0) \
     || defined(hppa) || defined(__hppa__)
#define HP_PA 
# if !defined(LINUX) && !defined(HPUX) && !defined(OPENBSD)
#define HPUX 
# endif
#define mach_type_known 
# endif
# if defined(__ia64) && (defined(_HPUX_SOURCE) || defined(__HP_aCC))
#define IA64 
# ifndef HPUX
#define HPUX 
# endif
#define mach_type_known 
# endif
# if (defined(__BEOS__) || defined(__HAIKU__)) && defined(_X86_)
#define I386 
#define HAIKU 
#define mach_type_known 
# endif
# if defined(__HAIKU__) && (defined(__amd64__) || defined(__x86_64__))
#define X86_64 
#define HAIKU 
#define mach_type_known 
# endif
# if defined(OPENBSD) && defined(__amd64__)
#define X86_64 
#define mach_type_known 
# endif
# if defined(LINUX) && (defined(i386) || defined(__i386__))
#define I386 
#define mach_type_known 
# endif
# if defined(LINUX) && defined(__x86_64__)
#define X86_64 
#define mach_type_known 
# endif
# if defined(LINUX) && (defined(__ia64__) || defined(__ia64))
#define IA64 
#define mach_type_known 
# endif
# if defined(LINUX) && defined(__e2k__)
#define E2K 
#define mach_type_known 
# endif
# if defined(LINUX) && defined(__aarch64__)
#define AARCH64 
#define mach_type_known 
# endif
# if defined(LINUX) && (defined(__arm) || defined(__arm__))
#define ARM32 
#define mach_type_known 
# endif
# if defined(LINUX) && defined(__cris__)
# ifndef CRIS
#define CRIS 
# endif
#define mach_type_known 
# endif
# if defined(LINUX) && defined(__loongarch__)
#define LOONGARCH 
#define mach_type_known 
# endif
# if defined(LINUX) && (defined(powerpc) || defined(__powerpc__) \
                        || defined(powerpc64) || defined(__powerpc64__))
#define POWERPC 
#define mach_type_known 
# endif
# if defined(LINUX) && defined(__mc68000__)
#define M68K 
#define mach_type_known 
# endif
# if defined(LINUX) && (defined(sparc) || defined(__sparc__))
#define SPARC 
#define mach_type_known 
# endif
# if defined(LINUX) && defined(__sh__)
#define SH 
#define mach_type_known 
# endif
# if defined(LINUX) && defined(__avr32__)
#define AVR32 
#define mach_type_known 
# endif
# if defined(LINUX) && defined(__m32r__)
#define M32R 
#define mach_type_known 
# endif
# if defined(__alpha) || defined(__alpha__)
#define ALPHA 
# if !defined(LINUX) && !defined(NETBSD) && !defined(OPENBSD) \
       && !defined(FREEBSD)
#define OSF1 
# endif
#define mach_type_known 
# endif
# if defined(_AMIGA) && !defined(AMIGA)
#define AMIGA 
# endif
# ifdef AMIGA
#define M68K 
#define mach_type_known 
# endif
# if defined(THINK_C) \
     || (defined(__MWERKS__) && !defined(__powerc) && !defined(SYMBIAN))
#define M68K 
#define MACOS 
#define mach_type_known 
# endif
# if defined(__MWERKS__) && defined(__powerc) && !defined(__MACH__) \
     && !defined(SYMBIAN)
#define POWERPC 
#define MACOS 
#define mach_type_known 
# endif
# if defined(OPENBSD) && defined(__powerpc__)
#define POWERPC 
#define mach_type_known 
# endif
# if defined(DARWIN)
# if defined(__ppc__) || defined(__ppc64__)
#define POWERPC 
#define mach_type_known 
# elif defined(__x86_64__) || defined(__x86_64)
#define X86_64 
#define mach_type_known 
# elif defined(__i386__)
#define I386 
#define mach_type_known 
# elif defined(__arm__)
#define ARM32 
#define mach_type_known 
# elif defined(__aarch64__)
#define AARCH64 
#define mach_type_known 
# endif
# endif
# if defined(__rtems__) && (defined(i386) || defined(__i386__))
#define I386 
#define RTEMS 
#define mach_type_known 
# endif
# if defined(NeXT) && defined(mc68000)
#define M68K 
#define NEXT 
#define mach_type_known 
# endif
# if defined(NeXT) && (defined(i386) || defined(__i386__))
#define I386 
#define NEXT 
#define mach_type_known 
# endif
# if defined(OPENBSD) && (defined(i386) || defined(__i386__))
#define I386 
#define mach_type_known 
# endif
# if defined(NETBSD) && (defined(i386) || defined(__i386__))
#define I386 
#define mach_type_known 
# endif
# if defined(NETBSD) && defined(__x86_64__)
#define X86_64 
#define mach_type_known 
# endif
# if defined(FREEBSD) && (defined(i386) || defined(__i386__))
#define I386 
#define mach_type_known 
# endif
# if defined(FREEBSD) && (defined(__amd64__) || defined(__x86_64__))
#define X86_64 
#define mach_type_known 
# endif
# if defined(FREEBSD) && defined(__sparc__)
#define SPARC 
#define mach_type_known 
# endif
# if defined(FREEBSD) && (defined(powerpc) || defined(__powerpc__))
#define POWERPC 
#define mach_type_known 
# endif
# if defined(FREEBSD) && defined(__arm__)
#define ARM32 
#define mach_type_known 
# endif
# if defined(FREEBSD) && defined(__aarch64__)
#define AARCH64 
#define mach_type_known 
# endif
# if defined(FREEBSD) && (defined(mips) || defined(__mips) || defined(_mips))
#define MIPS 
#define mach_type_known 
# endif
# if defined(bsdi) && (defined(i386) || defined(__i386__))
#define I386 
#define BSDI 
#define mach_type_known 
# endif
# if !defined(mach_type_known) && defined(__386BSD__)
#define I386 
#define THREE86BSD 
#define mach_type_known 
# endif
# if defined(_CX_UX) && defined(_M88K)
#define M88K 
#define CX_UX 
#define mach_type_known 
# endif
# if defined(DGUX) && defined(m88k)
#define M88K 

#define mach_type_known 
# endif
# if defined(_WIN32_WCE) || defined(__CEGCC__) || defined(__MINGW32CE__)

# if defined(SH3) || defined(SH4)
#define SH 
# endif
# if defined(x86) || defined(__i386__)
#define I386 
# endif
# if defined(_M_ARM) || defined(ARM) || defined(_ARM_)
#define ARM32 
# endif
#define MSWINCE 
#define mach_type_known 
# else
# if ((defined(_MSDOS) || defined(_MSC_VER)) && (_M_IX86 >= 300)) \
       || (defined(_WIN32) && !defined(__CYGWIN32__) && !defined(__CYGWIN__) \
           && !defined(__INTERIX) && !defined(SYMBIAN))
# if defined(__LP64__) || defined(_M_X64)
#define X86_64 
# elif defined(_M_ARM)
#define ARM32 
# elif defined(_M_ARM64)
#define AARCH64 
# else
#define I386 
# endif
# ifdef _XBOX_ONE
#define MSWIN_XBOX1 
# else
# ifndef MSWIN32
#define MSWIN32 
# endif
# if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP)
#define MSWINRT_FLAVOR 
# endif
# endif
#define mach_type_known 
# endif
# if defined(_MSC_VER) && defined(_M_IA64)
#define IA64 
#define MSWIN32 

# endif
# endif
# if defined(__DJGPP__)
#define I386 
# ifndef DJGPP
#define DJGPP 
# endif
#define mach_type_known 
# endif
# if defined(__CYGWIN32__) || defined(__CYGWIN__)
# if defined(__LP64__)
#define X86_64 
# else
#define I386 
# endif
#define CYGWIN32 
#define mach_type_known 
# endif
# if defined(__INTERIX)
#define I386 
#define INTERIX 
#define mach_type_known 
# endif
# if defined(__MINGW32__) && !defined(mach_type_known)
#define I386 
#define MSWIN32 
#define mach_type_known 
# endif
# if defined(__BORLANDC__)
#define I386 
#define MSWIN32 
#define mach_type_known 
# endif
# if defined(_UTS) && !defined(mach_type_known)
#define S370 
#define UTS4 
#define mach_type_known 
# endif
# if defined(__pj__) && !defined(CPPCHECK)
# error PicoJava no longer supported


# endif
# if defined(__embedded__) && defined(PPC)
#define POWERPC 
#define NOSYS 
#define mach_type_known 
# endif

# if defined(__WATCOMC__) && defined(__386__)
#define I386 
# if !defined(OS2) && !defined(MSWIN32) && !defined(DOS4GW)
# if defined(__OS2__)
#define OS2 
# else
# if defined(__WINDOWS_386__) || defined(__NT__)
#define MSWIN32 
# else
#define DOS4GW 
# endif
# endif
# endif
#define mach_type_known 
# endif
# if defined(__s390__) && defined(LINUX)
#define S390 
#define mach_type_known 
# endif
# if defined(__GNU__)
# if defined(__i386__)

#define HURD 
#define I386 
#define mach_type_known 
# endif
# endif
# if defined(__TANDEM)


#define MIPS 
#define NONSTOP 
#define mach_type_known 
# endif
# if defined(__arc__) && defined(LINUX)
#define ARC 
#define mach_type_known 
# endif
# if defined(__hexagon__) && defined(LINUX)
#define HEXAGON 
#define mach_type_known 
# endif
# if defined(__tile__) && defined(LINUX)
# ifdef __tilegx__
#define TILEGX 
# else
#define TILEPRO 
# endif
#define mach_type_known 
# endif
# if defined(__riscv) && (defined(FREEBSD) || defined(LINUX) \
                          || defined(OPENBSD))
#define RISCV 
#define mach_type_known 
# endif

# if defined(SN_TARGET_PSP2)
#define mach_type_known 
# endif

# if defined(NN_PLATFORM_CTR)
#define mach_type_known 
# endif

# if defined(NN_BUILD_TARGET_PLATFORM_NX)
#define NINTENDO_SWITCH 
#define mach_type_known 
# endif

# if defined(SYMBIAN)
#define mach_type_known 
# endif

# if defined(__EMSCRIPTEN__)
#define EMSCRIPTEN 
#define I386 
#define mach_type_known 
# endif
# 715 "gcconfig.h"
# if !defined(mach_type_known) && !defined(CPPCHECK)
# error The collector has not been ported to this machine/OS combination
# endif
# 898 "gcconfig.h"
# if GC_GNUC_PREREQ(2, 8) \
     && !GC_GNUC_PREREQ(11, 0) \
     && !defined(__INTEL_COMPILER) && !defined(__PATHCC__) \
     && !defined(__FUJITSU) \
     && !(defined(POWERPC) && defined(DARWIN)) \
     && !defined(E2K) && !defined(RTEMS) \
     && !defined(__ARMCC_VERSION) \
     && (!defined(__clang__) \
         || GC_CLANG_PREREQ(8, 0) )
#define HAVE_BUILTIN_UNWIND_INIT 
# endif




# ifdef CYGWIN32
#define OS_TYPE "CYGWIN32"
#define RETRY_GET_THREAD_CONTEXT 
# ifdef USE_WINALLOC
#define GWW_VDB 
# elif defined(USE_MMAP)
#define USE_MMAP_ANON 
# endif
# endif

# ifdef DARWIN
#define OS_TYPE "DARWIN"
#define DYNAMIC_LOADING 


#define DATASTART ((ptr_t)get_etext())
#define DATAEND ((ptr_t)get_end())
#define USE_MMAP_ANON 
    EXTERN_C_END
# include <unistd.h>
    EXTERN_C_BEGIN
#define GETPAGESIZE() (unsigned)getpagesize()


#define NO_PTHREAD_TRYLOCK 
# endif

# ifdef FREEBSD
#define OS_TYPE "FREEBSD"
#define FREEBSD_STACKBOTTOM 
# ifdef __ELF__
#define DYNAMIC_LOADING 
# endif
# if !defined(ALPHA) && !defined(SPARC)
      extern char etext[];
#define DATASTART GC_FreeBSDGetDataStart(0x1000, (ptr_t)etext)
#define DATASTART_USES_BSDGETDATASTART 
# ifndef GC_FREEBSD_THREADS
#define MPROTECT_VDB 
# endif
# endif
# endif

# ifdef HAIKU
#define OS_TYPE "HAIKU"
#define DYNAMIC_LOADING 
#define MPROTECT_VDB 
    EXTERN_C_END
# include <OS.h>
    EXTERN_C_BEGIN
#define GETPAGESIZE() (unsigned)B_PAGE_SIZE
# endif

# ifdef HPUX
#define OS_TYPE "HPUX"
    extern int __data_start[];
#define DATASTART ((ptr_t)(__data_start))
# ifdef USE_MMAP
#define USE_MMAP_ANON 
# endif
#define DYNAMIC_LOADING 
    EXTERN_C_END
# include <unistd.h>
    EXTERN_C_BEGIN
#define GETPAGESIZE() (unsigned)sysconf(_SC_PAGE_SIZE)
# endif

# ifdef LINUX
#define OS_TYPE "LINUX"
    EXTERN_C_END
# include <features.h>
    EXTERN_C_BEGIN
# if defined(FORCE_MPROTECT_BEFORE_MADVISE) \
       || defined(PREFER_MMAP_PROT_NONE)
#define COUNT_UNMAPPED_REGIONS 
# endif
#define RETRY_TKILL_ON_EAGAIN 
# if !defined(MIPS) && !defined(POWERPC)
#define LINUX_STACKBOTTOM 
# endif
# if defined(__ELF__) && !defined(IA64)
#define DYNAMIC_LOADING 
# endif
# if defined(__ELF__) && !defined(ARC) && !defined(RISCV) \
       && !defined(S390) && !defined(TILEGX) && !defined(TILEPRO)
      extern int _end[];
#define DATAEND ((ptr_t)(_end))
# endif
# if !defined(REDIRECT_MALLOC) && !defined(E2K)

#define MPROTECT_VDB 
# else
# 1013 "gcconfig.h"
# endif
# endif

# ifdef MACOS
#define OS_TYPE "MACOS"
# ifndef __LOWMEM__
      EXTERN_C_END
# include <LowMem.h>
      EXTERN_C_BEGIN
# endif

#define STACKBOTTOM ((ptr_t)LMGetCurStackBase())
#define DATAEND 
# endif

# ifdef MSWIN32
#define OS_TYPE "MSWIN32"

#define DATAEND 
#define GWW_VDB 
# endif

# ifdef MSWINCE
#define OS_TYPE "MSWINCE"
#define DATAEND 
# endif

# ifdef NETBSD
#define OS_TYPE "NETBSD"
#define HEURISTIC2 
# ifdef __ELF__
#define SEARCH_FOR_DATA_START 
#define DYNAMIC_LOADING 
# elif !defined(MIPS)
      extern char etext[];
#define DATASTART ((ptr_t)(etext))
# endif
# endif

# ifdef NEXT
#define OS_TYPE "NEXT"
#define DATASTART ((ptr_t)get_etext())
#define DATASTART_IS_FUNC 
#define DATAEND 
# endif

# ifdef OPENBSD
#define OS_TYPE "OPENBSD"
# ifndef GC_OPENBSD_THREADS
#define HEURISTIC2 
# endif
# ifdef __ELF__
      extern int __data_start[];
#define DATASTART ((ptr_t)__data_start)
      extern int _end[];
#define DATAEND ((ptr_t)(&_end))
#define DYNAMIC_LOADING 
# else
      extern char etext[];
#define DATASTART ((ptr_t)(etext))
# endif
# endif

# ifdef SOLARIS
#define OS_TYPE "SOLARIS"
    extern int _etext[], _end[];
    ptr_t GC_SysVGetDataStart(size_t, ptr_t);
#define DATASTART_IS_FUNC 
#define DATAEND ((ptr_t)(_end))
# if !defined(USE_MMAP) && defined(REDIRECT_MALLOC)
#define USE_MMAP 1




# endif
# ifdef USE_MMAP
#define HEAP_START (ptr_t)0x40000000
# else
#define HEAP_START DATAEND
# endif
# ifndef GC_THREADS
#define MPROTECT_VDB 
# endif
#define DYNAMIC_LOADING 
# 1107 "gcconfig.h"
    EXTERN_C_END
# include <sys/vmparam.h>
# include <unistd.h>
    EXTERN_C_BEGIN
# ifdef USERLIMIT

#define STACKBOTTOM ((ptr_t)USRSTACK)
# else
#define HEURISTIC2 
# endif
# endif

#define STACK_GRAN 0x1000000

# ifdef SYMBIAN
#define MACH_TYPE "SYMBIAN"
#define OS_TYPE "SYMBIAN"
#define CPP_WORDSZ 32
#define DATASTART (ptr_t)ALIGNMENT
#define DATAEND (ptr_t)ALIGNMENT
# endif

# ifdef M68K
#define MACH_TYPE "M68K"
#define ALIGNMENT 2
# ifdef OPENBSD

# endif
# ifdef NETBSD

# endif
# ifdef LINUX
# ifdef __ELF__
# if defined(__GLIBC__) && __GLIBC__ >= 2
#define SEARCH_FOR_DATA_START 
# else
            extern char **__environ;
#define DATASTART ((ptr_t)(&__environ))
# 1153 "gcconfig.h"
# endif
# else
          extern int etext[];
#define DATASTART ((ptr_t)((((word)(etext)) + 0xfff) & ~0xfff))
# endif
# endif
# ifdef AMIGA
#define OS_TYPE "AMIGA"


#define DATAEND 
#define GETPAGESIZE() 4096
# endif
# ifdef MACOS
#define GETPAGESIZE() 4096
# endif
# ifdef NEXT
#define STACKBOTTOM ((ptr_t)0x4000000)
# endif
# endif

# ifdef POWERPC
#define MACH_TYPE "POWERPC"
# ifdef MACOS
#define ALIGNMENT 2
# endif
# ifdef LINUX
# if defined(__powerpc64__)
#define CPP_WORDSZ 64
# ifndef HBLKSIZE
#define HBLKSIZE 4096
# endif
# else
#define ALIGNMENT 4
# endif


# if defined(__bg__)


#define HEURISTIC2 
#define NO_PTHREAD_GETATTR_NP 
# else
#define LINUX_STACKBOTTOM 
# endif
#define SEARCH_FOR_DATA_START 
# ifndef SOFT_VDB
#define SOFT_VDB 
# endif
# endif
# ifdef DARWIN
# if defined(__ppc64__)
#define CPP_WORDSZ 64
#define STACKBOTTOM ((ptr_t)0x7fff5fc00000)
#define CACHE_LINE_SIZE 64
# ifndef HBLKSIZE
#define HBLKSIZE 4096
# endif
# else
#define ALIGNMENT 4
#define STACKBOTTOM ((ptr_t)0xc0000000)
# endif
#define MPROTECT_VDB 
# if defined(USE_PPC_PREFETCH) && defined(__GNUC__)

#define PREFETCH(x) \
          __asm__ __volatile__ ("dcbt 0,%0" : : "r" ((const void *) (x)))
#define GC_PREFETCH_FOR_WRITE(x) \
          __asm__ __volatile__ ("dcbtst 0,%0" : : "r" ((const void *) (x)))
# endif
# endif
# ifdef OPENBSD
# if defined(__powerpc64__)
#define CPP_WORDSZ 64
# else
#define ALIGNMENT 4
# endif
# endif
# ifdef FREEBSD
# if defined(__powerpc64__)
#define CPP_WORDSZ 64
# ifndef HBLKSIZE
#define HBLKSIZE 4096
# endif
# else
#define ALIGNMENT 4
# endif
# endif
# ifdef NETBSD
#define ALIGNMENT 4
# endif
# ifdef SN_TARGET_PS3
#define OS_TYPE "SN_TARGET_PS3"
#define NO_GETENV 
#define CPP_WORDSZ 32
      extern int _end[];
      extern int __bss_start;
#define DATASTART ((ptr_t)(__bss_start))
#define DATAEND ((ptr_t)(_end))
#define STACKBOTTOM ((ptr_t)ps3_get_stack_bottom())
#define NO_PTHREAD_TRYLOCK 


# endif
# ifdef AIX
#define OS_TYPE "AIX"
#undef ALIGNMENT
#undef IA64


# ifdef __64BIT__
#define CPP_WORDSZ 64
#define STACKBOTTOM ((ptr_t)0x1000000000000000)
# else
#define CPP_WORDSZ 32
#define STACKBOTTOM ((ptr_t)((ulong)&errno))
# endif
#define USE_MMAP_ANON 







      extern int _data[], _end[];
#define DATASTART ((ptr_t)((ulong)_data))
#define DATAEND ((ptr_t)((ulong)_end))
      extern int errno;
#define MPROTECT_VDB 
#define DYNAMIC_LOADING 

# endif
# ifdef NOSYS
#define OS_TYPE "NOSYS"
#define ALIGNMENT 4
      extern void __end[], __dso_handle[];
#define DATASTART ((ptr_t)__dso_handle)
#define DATAEND ((ptr_t)(__end))

#undef STACK_GRAN
#define STACK_GRAN 0x10000000
#define HEURISTIC1 
# endif
# endif

# ifdef NACL
#define OS_TYPE "NACL"
# if defined(__GLIBC__)
#define DYNAMIC_LOADING 
# endif
#define DATASTART ((ptr_t)0x10020000)
    extern int _end[];
#define DATAEND ((ptr_t)_end)
#undef STACK_GRAN
#define STACK_GRAN 0x10000
#define HEURISTIC1 
#define NO_PTHREAD_GETATTR_NP 
#define USE_MMAP_ANON 
#define GETPAGESIZE() 65536
#define MAX_NACL_GC_THREADS 1024
# endif

# ifdef VAX
#define MACH_TYPE "VAX"
#define ALIGNMENT 4
    extern char etext[];
#define DATASTART ((ptr_t)(etext))
# ifdef BSD
#define OS_TYPE "BSD"
#define HEURISTIC1 

# endif
# ifdef ULTRIX
#define OS_TYPE "ULTRIX"
#define STACKBOTTOM ((ptr_t)0x7fffc800)
# endif
# endif

# ifdef SPARC
#define MACH_TYPE "SPARC"
# if defined(__arch64__) || defined(__sparcv9)
#define CPP_WORDSZ 64
#define ELF_CLASS ELFCLASS64
# else
#define ALIGNMENT 4
#define CPP_WORDSZ 32
# endif


# ifdef SOLARIS
#define DATASTART GC_SysVGetDataStart(0x10000, (ptr_t)_etext)
#define PROC_VDB 
#define GETPAGESIZE() (unsigned)sysconf(_SC_PAGESIZE)


# endif
# ifdef DRSNX
#define OS_TYPE "DRSNX"
        extern int etext[];
        ptr_t GC_SysVGetDataStart(size_t, ptr_t);
#define DATASTART GC_SysVGetDataStart(0x10000, (ptr_t)etext)
#define DATASTART_IS_FUNC 
#define MPROTECT_VDB 
#define STACKBOTTOM ((ptr_t)0xdfff0000)
#define DYNAMIC_LOADING 
# endif
# ifdef LINUX
# if !defined(__ELF__) && !defined(CPPCHECK)
# error Linux SPARC a.out not supported
# endif
#define SVR4 
      extern int _etext[];
      ptr_t GC_SysVGetDataStart(size_t, ptr_t);
# ifdef __arch64__
#define DATASTART GC_SysVGetDataStart(0x100000, (ptr_t)_etext)
# else
#define DATASTART GC_SysVGetDataStart(0x10000, (ptr_t)_etext)
# endif
#define DATASTART_IS_FUNC 
# endif
# ifdef OPENBSD

# endif
# ifdef NETBSD

# endif
# ifdef FREEBSD
        extern char etext[];
        extern char edata[];
# if !defined(CPPCHECK)
          extern char end[];
# endif
#define NEED_FIND_LIMIT 
#define DATASTART ((ptr_t)(&etext))
        void * GC_find_limit(void *, int);
#define DATAEND (ptr_t)GC_find_limit(DATASTART, TRUE)
#define DATAEND_IS_FUNC 
#define GC_HAVE_DATAREGION2 
#define DATASTART2 ((ptr_t)(&edata))
#define DATAEND2 ((ptr_t)(&end))
# endif
# endif

# ifdef I386
#define MACH_TYPE "I386"
# if (defined(__LP64__) || defined(_WIN64)) && !defined(CPPCHECK)
# error This should be handled as X86_64
# else
#define CPP_WORDSZ 32
#define ALIGNMENT 4



# endif
# ifdef SEQUENT
#define OS_TYPE "SEQUENT"
        extern int etext[];
#define DATASTART ((ptr_t)((((word)(etext)) + 0xfff) & ~0xfff))
#define STACKBOTTOM ((ptr_t)0x3ffff000)
# endif
# ifdef EMSCRIPTEN
#define OS_TYPE "EMSCRIPTEN"
#define DATASTART (ptr_t)ALIGNMENT
#define DATAEND (ptr_t)ALIGNMENT
#define USE_MMAP_ANON 
#undef USE_MUNMAP
# endif
# if defined(__QNX__)
#define OS_TYPE "QNX"
#define SA_RESTART 0
#define HEURISTIC1 
      extern char etext[];
      extern int _end[];
#define DATASTART ((ptr_t)etext)
#define DATAEND ((ptr_t)_end)
# endif
# ifdef HAIKU
      extern int etext[];
#define DATASTART ((ptr_t)((((word)(etext)) + 0xfff) & ~0xfff))
# endif
# ifdef SOLARIS
#define DATASTART GC_SysVGetDataStart(0x1000, (ptr_t)_etext)


# ifdef SOLARIS25_PROC_VDB_BUG_FIXED
#define PROC_VDB 
# endif
# endif
# ifdef SCO
#define OS_TYPE "SCO"
        extern int etext[];
#define DATASTART ((ptr_t)((((word)(etext)) + 0x3fffff) & ~0x3fffff) \
                                 + ((word)(etext) & 0xfff))
#define STACKBOTTOM ((ptr_t)0x7ffffffc)
# endif
# ifdef SCO_ELF
#define OS_TYPE "SCO_ELF"
        extern int etext[];
#define DATASTART ((ptr_t)(etext))
#define STACKBOTTOM ((ptr_t)0x08048000)
#define DYNAMIC_LOADING 
#define ELF_CLASS ELFCLASS32
# endif
# ifdef DGUX
#define OS_TYPE "DGUX"
        extern int _etext, _end;
        ptr_t GC_SysVGetDataStart(size_t, ptr_t);
#define DATASTART GC_SysVGetDataStart(0x1000, (ptr_t)(&_etext))
#define DATASTART_IS_FUNC 
#define DATAEND ((ptr_t)(&_end))
#define HEURISTIC2 
        EXTERN_C_END
# include <unistd.h>
        EXTERN_C_BEGIN
#define GETPAGESIZE() (unsigned)sysconf(_SC_PAGESIZE)
#define DYNAMIC_LOADING 
# ifndef USE_MMAP
#define USE_MMAP 1
# endif
#define MAP_FAILED (void *) ((word)-1)
#define HEAP_START (ptr_t)0x40000000
# endif
# ifdef LINUX
#define HEAP_START (ptr_t)0x1000


# ifdef __ELF__
# if defined(__GLIBC__) && __GLIBC__ >= 2 \
                || defined(HOST_ANDROID) || defined(HOST_TIZEN)
#define SEARCH_FOR_DATA_START 
# else
                 extern char **__environ;
#define DATASTART ((ptr_t)(&__environ))
# 1495 "gcconfig.h"
# endif
# if !defined(GC_NO_SIGSETJMP) && (defined(HOST_TIZEN) \
                    || (defined(HOST_ANDROID) \
                        && !(GC_GNUC_PREREQ(4, 8) || GC_CLANG_PREREQ(3, 2) \
                             || __ANDROID_API__ >= 18)))




#define GC_NO_SIGSETJMP 1
# endif
# else
             extern int etext[];
#define DATASTART ((ptr_t)((((word)(etext)) + 0xfff) & ~0xfff))
# endif
# ifdef USE_I686_PREFETCH
#define PREFETCH(x) \
            __asm__ __volatile__ ("prefetchnta %0" : : "m"(*(char *)(x)))




# ifdef FORCE_WRITE_PREFETCH


#define GC_PREFETCH_FOR_WRITE(x) \
              __asm__ __volatile__ ("prefetcht0 %0" : : "m"(*(char *)(x)))
# else
#define GC_NO_PREFETCH_FOR_WRITE 
# endif
# elif defined(USE_3DNOW_PREFETCH)
#define PREFETCH(x) \
            __asm__ __volatile__ ("prefetch %0" : : "m"(*(char *)(x)))
#define GC_PREFETCH_FOR_WRITE(x) \
            __asm__ __volatile__ ("prefetchw %0" : : "m"(*(char *)(x)))
# endif
# if defined(__GLIBC__) && !defined(__UCLIBC__) \
           && !defined(GLIBC_TSX_BUG_FIXED)

#define GLIBC_2_19_TSX_BUG 
          EXTERN_C_END
# include <gnu/libc-version.h>
          EXTERN_C_BEGIN
# endif
# ifndef SOFT_VDB
#define SOFT_VDB 
# endif
# endif
# ifdef CYGWIN32
#define WOW64_THREAD_CONTEXT_WORKAROUND 
#define DATASTART ((ptr_t)GC_DATASTART)
#define DATAEND ((ptr_t)GC_DATAEND)
# ifndef USE_WINALLOC

# endif
# endif
# ifdef INTERIX
#define OS_TYPE "INTERIX"
      extern int _data_start__[];
      extern int _bss_end__[];
#define DATASTART ((ptr_t)_data_start__)
#define DATAEND ((ptr_t)_bss_end__)
#define STACKBOTTOM ({ ptr_t rv; \
                            __asm__ __volatile__ ("movl %%fs:4, %%eax" \
                                                  : "=a" (rv)); \
                            rv; })
#define USE_MMAP_ANON 
# endif
# ifdef OS2
#define OS_TYPE "OS2"



#define DATAEND 
# endif
# ifdef MSWIN32
#define WOW64_THREAD_CONTEXT_WORKAROUND 
#define RETRY_GET_THREAD_CONTEXT 
#define MPROTECT_VDB 
# endif
# ifdef MSWINCE

# endif
# ifdef DJGPP
#define OS_TYPE "DJGPP"
        EXTERN_C_END
# include "stubinfo.h"
        EXTERN_C_BEGIN
        extern int etext[];
        extern int _stklen;
        extern int __djgpp_stack_limit;
#define DATASTART ((ptr_t)((((word)(etext)) + 0x1ff) & ~0x1ff))

#define STACKBOTTOM ((ptr_t)((word)__djgpp_stack_limit + _stklen))

# endif
# ifdef OPENBSD

# endif
# ifdef FREEBSD
# ifdef __GLIBC__
            extern int _end[];
#define DATAEND ((ptr_t)(_end))
# endif
# endif
# ifdef NETBSD

# endif
# ifdef THREE86BSD
#define OS_TYPE "THREE86BSD"
#define HEURISTIC2 
        extern char etext[];
#define DATASTART ((ptr_t)(etext))
# endif
# ifdef BSDI
#define OS_TYPE "BSDI"
#define HEURISTIC2 
        extern char etext[];
#define DATASTART ((ptr_t)(etext))
# endif
# ifdef NEXT
#define STACKBOTTOM ((ptr_t)0xc0000000)
# endif
# ifdef RTEMS
#define OS_TYPE "RTEMS"
        EXTERN_C_END
# include <sys/unistd.h>
        EXTERN_C_BEGIN
        extern int etext[];
        void *rtems_get_stack_bottom(void);
#define InitStackBottom rtems_get_stack_bottom()
#define DATASTART ((ptr_t)etext)
#define STACKBOTTOM ((ptr_t)InitStackBottom)
# endif
# ifdef DOS4GW
#define OS_TYPE "DOS4GW"
      extern long __nullarea;
      extern char _end;
      extern char *_STACKTOP;



      #pragma aux __nullarea "*";
      #pragma aux _end "*";
#define STACKBOTTOM ((ptr_t)_STACKTOP)

#define DATASTART ((ptr_t)(&__nullarea))
#define DATAEND ((ptr_t)(&_end))
# endif
# ifdef HURD
#define OS_TYPE "HURD"
#define HEURISTIC2 
#define SEARCH_FOR_DATA_START 
      extern int _end[];
#define DATAEND ((ptr_t)(_end))

#define DYNAMIC_LOADING 
#define USE_MMAP_ANON 
# endif
# ifdef DARWIN
#define DARWIN_DONT_PARSE_STACK 1
#define STACKBOTTOM ((ptr_t)0xc0000000)
#define MPROTECT_VDB 
# if TARGET_OS_IPHONE && !defined(NO_DYLD_BIND_FULLY_IMAGE)

#define NO_DYLD_BIND_FULLY_IMAGE 
# endif
# endif
# endif

# ifdef NS32K
#define MACH_TYPE "NS32K"
#define ALIGNMENT 4
    extern char **environ;
#define DATASTART ((ptr_t)(&environ))




#define STACKBOTTOM ((ptr_t)0xfffff000)
# endif

# ifdef LOONGARCH
#define MACH_TYPE "LoongArch"
#define CPP_WORDSZ _LOONGARCH_SZPTR
# ifdef LINUX
#pragma weak __data_start
      extern int __data_start[];
#define DATASTART ((ptr_t)(__data_start))
# endif
# endif

# ifdef MIPS
#define MACH_TYPE "MIPS"
# ifdef LINUX
#pragma weak __data_start
      extern int __data_start[];
#define DATASTART ((ptr_t)(__data_start))
# ifdef _MIPS_SZPTR
#define CPP_WORDSZ _MIPS_SZPTR
# else
#define ALIGNMENT 4
# endif
# ifndef HBLKSIZE
#define HBLKSIZE 4096
# endif
# if __GLIBC__ == 2 && __GLIBC_MINOR__ >= 2 || __GLIBC__ > 2
#define LINUX_STACKBOTTOM 
# else
#define STACKBOTTOM ((ptr_t)0x7fff8000)
# endif
# endif
# ifdef EWS4800
#define OS_TYPE "EWS4800"
#define HEURISTIC2 
# if defined(_MIPS_SZPTR) && (_MIPS_SZPTR == 64)
        extern int _fdata[], _end[];
#define DATASTART ((ptr_t)_fdata)
#define DATAEND ((ptr_t)_end)
#define CPP_WORDSZ _MIPS_SZPTR
# else
        extern int etext[], edata[];
# if !defined(CPPCHECK)
          extern int end[];
# endif
        extern int _DYNAMIC_LINKING[], _gp[];
#define DATASTART ((ptr_t)((((word)(etext) + 0x3ffff) & ~0x3ffff) \
                                  + ((word)(etext) & 0xffff)))
#define DATAEND ((ptr_t)(edata))
#define GC_HAVE_DATAREGION2 
#define DATASTART2 (_DYNAMIC_LINKING \
                ? (ptr_t)(((word)_gp + 0x8000 + 0x3ffff) & ~0x3ffff) \
                : (ptr_t)edata)
#define DATAEND2 ((ptr_t)(end))
#define ALIGNMENT 4
# endif
# endif
# ifdef ULTRIX
#define OS_TYPE "ULTRIX"
#define HEURISTIC2 
#define DATASTART ((ptr_t)0x10000000)


#define ALIGNMENT 4
# endif
# ifdef IRIX5
#define OS_TYPE "IRIX5"
#define HEURISTIC2 
        extern int _fdata[];
#define DATASTART ((ptr_t)(_fdata))
# ifdef USE_MMAP
#define HEAP_START (ptr_t)0x30000000
# else
#define HEAP_START DATASTART
# endif







# ifdef _MIPS_SZPTR
#define CPP_WORDSZ _MIPS_SZPTR
# else
#define ALIGNMENT 4
# endif
#define DYNAMIC_LOADING 
# endif
# ifdef MSWINCE
#define ALIGNMENT 4
# endif
# ifdef NETBSD
#define ALIGNMENT 4
# ifndef __ELF__
#define DATASTART ((ptr_t)0x10000000)
#define STACKBOTTOM ((ptr_t)0x7ffff000)
# endif
# endif
# ifdef OPENBSD
#define CPP_WORDSZ 64
# endif
# ifdef FREEBSD
#define ALIGNMENT 4
# endif
# ifdef NONSTOP
#define OS_TYPE "NONSTOP"
#define CPP_WORDSZ 32
#define DATASTART ((ptr_t)0x08000000)
      extern char **environ;
#define DATAEND ((ptr_t)(environ - 0x10))
#define STACKBOTTOM ((ptr_t)0x4fffffff)
# endif
# endif

# ifdef NIOS2
#define MACH_TYPE "NIOS2"
#define CPP_WORDSZ 32
# ifndef HBLKSIZE
#define HBLKSIZE 4096
# endif
# ifdef LINUX
      extern int __data_start[];
#define DATASTART ((ptr_t)(__data_start))
# endif
# endif

# ifdef OR1K
#define MACH_TYPE "OR1K"
#define CPP_WORDSZ 32
# ifndef HBLKSIZE
#define HBLKSIZE 4096
# endif
# ifdef LINUX
      extern int __data_start[];
#define DATASTART ((ptr_t)(__data_start))
# endif
# endif

# ifdef HP_PA
#define MACH_TYPE "HP_PA"
# ifdef __LP64__
#define CPP_WORDSZ 64
# else
#define CPP_WORDSZ 32
# endif
#define STACK_GROWS_UP 
# ifdef HPUX
# ifndef GC_THREADS
#define MPROTECT_VDB 
# endif
# ifdef USE_HPUX_FIXED_STACKBOTTOM
# 1839 "gcconfig.h"
#define STACKBOTTOM ((ptr_t)0x7b033000)
# elif defined(USE_ENVIRON_POINTER)



        extern char ** environ;
#define STACKBOTTOM ((ptr_t)environ)
# elif !defined(HEURISTIC2)

#define HPUX_MAIN_STACKBOTTOM 
# endif
# ifndef __GNUC__
#define PREFETCH(x) do { \
                              register long addr = (long)(x); \
                              (void) _asm ("LDW", 0, 0, addr, 0); \
                            } while (0)
# endif
# endif
# ifdef LINUX
#define SEARCH_FOR_DATA_START 
# endif
# ifdef OPENBSD

# endif
# endif

# ifdef ALPHA
#define MACH_TYPE "ALPHA"
#define CPP_WORDSZ 64
# ifdef NETBSD
#define ELFCLASS32 32
#define ELFCLASS64 64
#define ELF_CLASS ELFCLASS64
# endif
# ifdef OPENBSD

# endif
# ifdef FREEBSD


        extern char etext[];
        extern char edata[];
# if !defined(CPPCHECK)
          extern char end[];
# endif
#define NEED_FIND_LIMIT 
#define DATASTART ((ptr_t)(&etext))
        void * GC_find_limit(void *, int);
#define DATAEND (ptr_t)GC_find_limit(DATASTART, TRUE)
#define DATAEND_IS_FUNC 
#define GC_HAVE_DATAREGION2 
#define DATASTART2 ((ptr_t)(&edata))
#define DATAEND2 ((ptr_t)(&end))
# endif
# ifdef OSF1
#define OS_TYPE "OSF1"
#define DATASTART ((ptr_t)0x140000000)
        extern int _end[];
#define DATAEND ((ptr_t)(&_end))
        extern char ** environ;
        EXTERN_C_END
# include <unistd.h>
        EXTERN_C_BEGIN



#define STACKBOTTOM ((ptr_t)(((word)(environ) | (getpagesize()-1))+1))





        extern int __start[];
#define HEURISTIC2_LIMIT ((ptr_t)((word)(__start) & ~(getpagesize()-1)))
# ifndef GC_OSF1_THREADS

#define MPROTECT_VDB 
# endif
#define DYNAMIC_LOADING 
# endif
# ifdef LINUX
# ifdef __ELF__
#define SEARCH_FOR_DATA_START 
# else
#define DATASTART ((ptr_t)0x140000000)
          extern int _end[];
#define DATAEND ((ptr_t)(_end))
# endif
# endif
# endif

# ifdef IA64
#define MACH_TYPE "IA64"
# ifdef HPUX
# ifdef _ILP32
#define CPP_WORDSZ 32

#define ALIGNMENT 4
# else
# if !defined(_LP64) && !defined(CPPCHECK)
# error Unknown ABI
# endif
#define CPP_WORDSZ 64

#define ALIGNMENT 8
# endif

        extern char ** environ;
#define STACKBOTTOM ((ptr_t)environ)
#define HPUX_STACKBOTTOM 




#define BACKING_STORE_DISPLACEMENT 0x1000000
#define BACKING_STORE_ALIGNMENT 0x1000
#define BACKING_STORE_BASE GC_register_stackbottom

# endif
# ifdef LINUX
#define CPP_WORDSZ 64





#define BACKING_STORE_BASE GC_register_stackbottom
#define SEARCH_FOR_DATA_START 
# ifdef __GNUC__
#define DYNAMIC_LOADING 
# else



# endif
# ifdef __GNUC__
# ifndef __INTEL_COMPILER
#define PREFETCH(x) \
              __asm__ ("        lfetch  [%0]": : "r"(x))
#define GC_PREFETCH_FOR_WRITE(x) \
              __asm__ ("        lfetch.excl     [%0]": : "r"(x))
#define CLEAR_DOUBLE(x) \
              __asm__ ("        stf.spill       [%0]=f0": : "r"((void *)(x)))
# else
            EXTERN_C_END
# include <ia64intrin.h>
            EXTERN_C_BEGIN
#define PREFETCH(x) __lfetch(__lfhint_none, (x))
#define GC_PREFETCH_FOR_WRITE(x) __lfetch(__lfhint_nta, (x))
#define CLEAR_DOUBLE(x) __stf_spill((void *)(x), 0)
# endif
# endif
# endif
# ifdef MSWIN32

# if defined(_WIN64)
#define CPP_WORDSZ 64
# else
#define CPP_WORDSZ 32
#define ALIGNMENT 8
# endif
# endif
# endif

# ifdef E2K
#define MACH_TYPE "E2K"
# ifdef __LP64__
#define CPP_WORDSZ 64
# else
#define CPP_WORDSZ 32
# endif
# ifndef HBLKSIZE
#define HBLKSIZE 4096
# endif
# ifdef LINUX
      extern int __dso_handle[];
#define DATASTART ((ptr_t)__dso_handle)
# ifdef REDIRECT_MALLOC
#define NO_PROC_FOR_LIBRARIES 
# endif
# endif
# endif

# ifdef M88K
#define MACH_TYPE "M88K"
#define ALIGNMENT 4
#define STACKBOTTOM ((char*)0xf0000000)
    extern int etext[];
# ifdef CX_UX
#define OS_TYPE "CX_UX"
#define DATASTART ((ptr_t)((((word)(etext) + 0x3fffff) & ~0x3fffff) \
                                  + 0x10000))
# endif
# ifdef DGUX
#define OS_TYPE "DGUX"
        ptr_t GC_SysVGetDataStart(size_t, ptr_t);
#define DATASTART GC_SysVGetDataStart(0x10000, (ptr_t)etext)
#define DATASTART_IS_FUNC 
# endif
# endif

# ifdef S370


#define MACH_TYPE "S370"
#define ALIGNMENT 4
# ifdef UTS4
#define OS_TYPE "UTS4"
        extern int etext[];
        extern int _etext[];
        extern int _end[];
        ptr_t GC_SysVGetDataStart(size_t, ptr_t);
#define DATASTART GC_SysVGetDataStart(0x10000, (ptr_t)_etext)
#define DATASTART_IS_FUNC 
#define DATAEND ((ptr_t)(_end))
#define HEURISTIC2 
# endif
# endif

# ifdef S390
#define MACH_TYPE "S390"
# ifndef __s390x__
#define CPP_WORDSZ 32
# else
#define CPP_WORDSZ 64
# ifndef HBLKSIZE
#define HBLKSIZE 4096
# endif
# endif
# ifdef LINUX
        extern int __data_start[] __attribute__((__weak__));
#define DATASTART ((ptr_t)(__data_start))
        extern int _end[] __attribute__((__weak__));
#define DATAEND ((ptr_t)(_end))
#define CACHE_LINE_SIZE 256
#define GETPAGESIZE() 4096
# ifndef SOFT_VDB
#define SOFT_VDB 
# endif
# endif
# endif

# ifdef AARCH64
#define MACH_TYPE "AARCH64"
# ifdef __ILP32__
#define CPP_WORDSZ 32
# else
#define CPP_WORDSZ 64
# endif
# ifndef HBLKSIZE
#define HBLKSIZE 4096
# endif
# ifdef LINUX
# if defined(HOST_ANDROID)
#define SEARCH_FOR_DATA_START 
# else
        extern int __data_start[] __attribute__((__weak__));
#define DATASTART ((ptr_t)__data_start)
# endif
# endif
# ifdef DARWIN

#define DARWIN_DONT_PARSE_STACK 1
#define STACKBOTTOM ((ptr_t)0x16fdfffff)



# if TARGET_OS_IPHONE && !defined(NO_DYLD_BIND_FULLY_IMAGE)
#define NO_DYLD_BIND_FULLY_IMAGE 
# endif
# endif
# ifdef FREEBSD

# endif
# ifdef NETBSD
#define ELF_CLASS ELFCLASS64
# endif
# ifdef OPENBSD

# endif
# ifdef NINTENDO_SWITCH
#define OS_TYPE "NINTENDO_SWITCH"
      extern int __bss_end[];
#define NO_HANDLE_FORK 1
#define DATASTART (ptr_t)ALIGNMENT
#define DATAEND (ptr_t)(&__bss_end)
      void *switch_get_stack_bottom(void);
#define STACKBOTTOM ((ptr_t)switch_get_stack_bottom())
# ifndef HAVE_CLOCK_GETTIME
#define HAVE_CLOCK_GETTIME 1
# endif
# endif
# ifdef MSWIN32

# endif
# ifdef NOSYS
#define OS_TYPE "NOSYS"

      extern int __data_start[];
#define DATASTART ((ptr_t)__data_start)
      extern void *__stack_base__;
#define STACKBOTTOM ((ptr_t)__stack_base__)
# endif
# endif

# ifdef ARM32
# if defined(NACL)
#define MACH_TYPE "NACL"
# else
#define MACH_TYPE "ARM32"
# endif
#define CPP_WORDSZ 32
# ifdef NETBSD

# endif
# ifdef LINUX
# if defined(__GLIBC__) && __GLIBC__ >= 2 \
                || defined(HOST_ANDROID) || defined(HOST_TIZEN)
#define SEARCH_FOR_DATA_START 
# else
            extern char **__environ;
#define DATASTART ((ptr_t)(&__environ))
# 2169 "gcconfig.h"
# endif
# endif
# ifdef MSWINCE

# endif
# ifdef FREEBSD

# endif
# ifdef DARWIN

#define DARWIN_DONT_PARSE_STACK 1
#define STACKBOTTOM ((ptr_t)0x30000000)

# if TARGET_OS_IPHONE && !defined(NO_DYLD_BIND_FULLY_IMAGE)
#define NO_DYLD_BIND_FULLY_IMAGE 
# endif
# endif
# ifdef OPENBSD

# endif
# ifdef SN_TARGET_PSP2
#define OS_TYPE "SN_TARGET_PSP2"
#define NO_HANDLE_FORK 1
#define DATASTART (ptr_t)ALIGNMENT
#define DATAEND (ptr_t)ALIGNMENT
      void *psp2_get_stack_bottom(void);
#define STACKBOTTOM ((ptr_t)psp2_get_stack_bottom())
# endif
# ifdef NN_PLATFORM_CTR
#define OS_TYPE "NN_PLATFORM_CTR"
      extern unsigned char Image$$ZI$$ZI$$Base[];
#define DATASTART (ptr_t)(Image$$ZI$$ZI$$Base)
      extern unsigned char Image$$ZI$$ZI$$Limit[];
#define DATAEND (ptr_t)(Image$$ZI$$ZI$$Limit)
      void *n3ds_get_stack_bottom(void);
#define STACKBOTTOM ((ptr_t)n3ds_get_stack_bottom())
# endif
# ifdef MSWIN32

# endif
# ifdef NOSYS
#define OS_TYPE "NOSYS"

      extern int __data_start[];
#define DATASTART ((ptr_t)(__data_start))

      extern void *__stack_base__;
#define STACKBOTTOM ((ptr_t)(__stack_base__))
# endif
#endif

# ifdef CRIS
#define MACH_TYPE "CRIS"
#define CPP_WORDSZ 32
#define ALIGNMENT 1
# ifdef LINUX
#define SEARCH_FOR_DATA_START 
# endif
# endif

# if defined(SH) && !defined(SH4)
#define MACH_TYPE "SH"
#define ALIGNMENT 4
# ifdef LINUX
#define SEARCH_FOR_DATA_START 
# endif
# ifdef NETBSD

# endif
# ifdef OPENBSD

# endif
# ifdef MSWINCE

# endif
# endif

# ifdef SH4
#define MACH_TYPE "SH4"
#define ALIGNMENT 4
# ifdef MSWINCE

# endif
# endif

# ifdef AVR32
#define MACH_TYPE "AVR32"
#define CPP_WORDSZ 32
# ifdef LINUX
#define SEARCH_FOR_DATA_START 
# endif
# endif

# ifdef M32R
#define MACH_TYPE "M32R"
#define CPP_WORDSZ 32
# ifdef LINUX
#define SEARCH_FOR_DATA_START 
# endif
# endif

# ifdef X86_64
#define MACH_TYPE "X86_64"
# ifdef __ILP32__
#define CPP_WORDSZ 32
# else
#define CPP_WORDSZ 64
# endif
# ifndef HBLKSIZE
#define HBLKSIZE 4096
# endif
# ifndef CACHE_LINE_SIZE
#define CACHE_LINE_SIZE 64
# endif
# ifdef PLATFORM_GETMEM
#define OS_TYPE "PLATFORM_GETMEM"
#define DATASTART (ptr_t)ALIGNMENT
#define DATAEND (ptr_t)ALIGNMENT
      EXTERN_C_END
# include <pthread.h>
      EXTERN_C_BEGIN
      void *platform_get_stack_bottom(void);
#define STACKBOTTOM ((ptr_t)platform_get_stack_bottom())
# endif
# ifdef LINUX
#define SEARCH_FOR_DATA_START 
# if defined(__GLIBC__) && !defined(__UCLIBC__)



#define USE_MMAP_ANON 
# endif
# if defined(__GLIBC__) && !defined(__UCLIBC__) \
           && !defined(GETCONTEXT_FPU_BUG_FIXED)




#define GETCONTEXT_FPU_EXCMASK_BUG 
# endif
# if defined(__GLIBC__) && !defined(__UCLIBC__) \
           && !defined(GLIBC_TSX_BUG_FIXED)

#define GLIBC_2_19_TSX_BUG 
          EXTERN_C_END
# include <gnu/libc-version.h>
          EXTERN_C_BEGIN
# endif
# ifndef SOFT_VDB
#define SOFT_VDB 
# endif
# endif
# ifdef DARWIN
#define DARWIN_DONT_PARSE_STACK 1
#define STACKBOTTOM ((ptr_t)0x7fff5fc00000)
#define MPROTECT_VDB 
# if TARGET_OS_IPHONE && !defined(NO_DYLD_BIND_FULLY_IMAGE)

#define NO_DYLD_BIND_FULLY_IMAGE 
# endif
# endif
# ifdef FREEBSD
# ifdef __GLIBC__
            extern int _end[];
#define DATAEND ((ptr_t)(_end))
# endif
# if defined(__DragonFly__)


#define COUNT_UNMAPPED_REGIONS 
# endif
# endif
# ifdef NETBSD

# endif
# ifdef OPENBSD

# endif
# ifdef HAIKU
#define HEURISTIC2 
#define SEARCH_FOR_DATA_START 
# endif
# ifdef SOLARIS
#define ELF_CLASS ELFCLASS64
#define DATASTART GC_SysVGetDataStart(0x1000, (ptr_t)_etext)
# ifdef SOLARIS25_PROC_VDB_BUG_FIXED
#define PROC_VDB 
# endif
# endif
# ifdef CYGWIN32
# ifndef USE_WINALLOC
# if defined(THREAD_LOCAL_ALLOC)



# else
#define MPROTECT_VDB 
# endif
# endif
# endif
# ifdef MSWIN_XBOX1
#define OS_TYPE "MSWIN_XBOX1"
#define NO_GETENV 
#define DATASTART (ptr_t)ALIGNMENT
#define DATAEND (ptr_t)ALIGNMENT
      LONG64 durango_get_stack_bottom(void);
#define STACKBOTTOM ((ptr_t)durango_get_stack_bottom())
#define GETPAGESIZE() 4096
# ifndef USE_MMAP
#define USE_MMAP 1
# endif

#define PROT_NONE 0
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 4
#define MAP_PRIVATE 2
#define MAP_FIXED 0x10
#define MAP_FAILED ((void *)-1)
# endif
# ifdef MSWIN32
#define RETRY_GET_THREAD_CONTEXT 
# if !defined(__GNUC__) || defined(__INTEL_COMPILER) \
           || (GC_GNUC_PREREQ(4, 7) && !defined(__MINGW64__))


#define MPROTECT_VDB 
# endif
# endif
# endif

# ifdef ARC
#define MACH_TYPE "ARC"
#define CPP_WORDSZ 32
#define CACHE_LINE_SIZE 64
# ifdef LINUX
      extern int __data_start[] __attribute__((__weak__));
#define DATASTART ((ptr_t)__data_start)
# endif
# endif

# ifdef HEXAGON
#define MACH_TYPE "HEXAGON"
#define CPP_WORDSZ 32
# ifdef LINUX
# if defined(__GLIBC__)
#define SEARCH_FOR_DATA_START 
# elif !defined(CPPCHECK)
# error Unknown Hexagon libc configuration
# endif
# endif
# endif

# ifdef TILEPRO
#define MACH_TYPE "TILEPro"
#define CPP_WORDSZ 32
#define PREFETCH(x) __insn_prefetch(x)
#define CACHE_LINE_SIZE 64
# ifdef LINUX
      extern int __data_start[];
#define DATASTART ((ptr_t)__data_start)
# endif
# endif

# ifdef TILEGX
#define MACH_TYPE "TILE-Gx"
#define CPP_WORDSZ (__SIZEOF_POINTER__ * 8)
# if CPP_WORDSZ < 64
#define CLEAR_DOUBLE(x) (*(long long *)(x) = 0)
# endif
#define PREFETCH(x) __insn_prefetch_l1(x)
#define CACHE_LINE_SIZE 64
# ifdef LINUX
      extern int __data_start[];
#define DATASTART ((ptr_t)__data_start)
# endif
# endif

# ifdef RISCV
#define MACH_TYPE "RISC-V"
#define CPP_WORDSZ __riscv_xlen
# ifdef FREEBSD

# endif
# ifdef LINUX
      extern int __data_start[] __attribute__((__weak__));
#define DATASTART ((ptr_t)__data_start)
# endif
# ifdef OPENBSD

# endif
# endif

#if defined(__GLIBC__) && !defined(DONT_USE_LIBC_PRIVATES)

#define USE_LIBC_PRIVATES 
#endif

#ifdef NO_RETRY_GET_THREAD_CONTEXT
#undef RETRY_GET_THREAD_CONTEXT
#endif

#if defined(LINUX_STACKBOTTOM) && defined(NO_PROC_STAT) \
    && !defined(USE_LIBC_PRIVATES)


#undef LINUX_STACKBOTTOM
#define HEURISTIC2 


#endif

#if defined(USE_MMAP_ANON) && !defined(USE_MMAP)
#define USE_MMAP 1
#elif (defined(LINUX) || defined(OPENBSD)) && defined(USE_MMAP)


#define USE_MMAP_ANON 
#endif

#if defined(GC_LINUX_THREADS) && defined(REDIRECT_MALLOC) \
    && !defined(USE_PROC_FOR_LIBRARIES) && !defined(NO_PROC_FOR_LIBRARIES)
# 2512 "gcconfig.h"
#define USE_PROC_FOR_LIBRARIES 
#endif

#ifndef STACK_GROWS_UP
#define STACK_GROWS_DOWN 
#endif

#ifndef CPP_WORDSZ
#define CPP_WORDSZ 32
#endif

#ifndef OS_TYPE
#define OS_TYPE ""
#endif

#ifndef DATAEND
# if !defined(CPPCHECK)
    extern int end[];
# endif
#define DATAEND ((ptr_t)(end))
#endif




#if defined(HOST_ANDROID) && defined(__clang__) \
    && !defined(BROKEN_UUENDUU_SYM)
#undef DATAEND
#pragma weak __end__
  extern int __end__[];
#define DATAEND (__end__ != 0 ? (ptr_t)__end__ : (ptr_t)_end)
#endif

#if (defined(SVR4) || defined(HOST_ANDROID) || defined(HOST_TIZEN)) \
    && !defined(GETPAGESIZE)
  EXTERN_C_END
# include <unistd.h>
  EXTERN_C_BEGIN
#define GETPAGESIZE() (unsigned)sysconf(_SC_PAGESIZE)
#endif

#ifndef GETPAGESIZE
# if defined(AIX) || defined(IRIX5) || defined(LINUX) || defined(SOLARIS) \
     || defined(NETBSD) || defined(FREEBSD) || defined(HPUX)
    EXTERN_C_END
# include <unistd.h>
    EXTERN_C_BEGIN
# endif
#define GETPAGESIZE() (unsigned)getpagesize()
#endif

#if defined(HOST_ANDROID) && !(__ANDROID_API__ >= 23) \
    && ((defined(MIPS) && (CPP_WORDSZ == 32)) \
        || defined(ARM32) || defined(I386) )


#define USE_TKILL_ON_ANDROID 
#endif

#if defined(SOLARIS) || defined(DRSNX) || defined(UTS4)


#define SVR4 
#endif

#if defined(MPROTECT_VDB) && defined(__GLIBC__) \
    && (__GLIBC__ < 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ < 2))
# error glibc too old?
#endif

#if defined(SOLARIS) || defined(DRSNX)


#define SOLARISDL 

#define SUNOS5SIGS 
#endif

#if defined(HPUX)
#define SUNOS5SIGS 
#endif

#if defined(FREEBSD) && (defined(__DragonFly__) || __FreeBSD__ >= 4 \
                         || __FreeBSD_kernel__ >= 4 || defined(__GLIBC__))
#define SUNOS5SIGS 
#endif

#if defined(FREEBSD) || defined(HAIKU) || defined(HURD) || defined(IRIX5) \
    || defined(NETBSD) || defined(OPENBSD) || defined(OSF1) \
    || defined(SUNOS5SIGS)
#define USE_SEGV_SIGACT 
# if defined(IRIX5) && defined(_sigargs) \
     || (defined(FREEBSD) && defined(SUNOS5SIGS)) \
     || defined(HPUX) || defined(HURD) || defined(NETBSD)

#define USE_BUS_SIGACT 
# endif
#endif

#if !defined(GC_EXPLICIT_SIGNALS_UNBLOCK) && defined(SUNOS5SIGS) \
    && !defined(GC_NO_PTHREAD_SIGMASK)
#define GC_EXPLICIT_SIGNALS_UNBLOCK 
#endif

#if !defined(NO_SIGNALS_UNBLOCK_IN_MAIN) && defined(GC_NO_PTHREAD_SIGMASK)
#define NO_SIGNALS_UNBLOCK_IN_MAIN 
#endif

#if !defined(NO_MARKER_SPECIAL_SIGMASK) \
    && (defined(NACL) || defined(GC_WIN32_PTHREADS))


#define NO_MARKER_SPECIAL_SIGMASK 
#endif

#ifdef GC_NETBSD_THREADS
#define SIGRTMIN 33
#define SIGRTMAX 63


#define GC_NETBSD_THREADS_WORKAROUND 
#endif

#ifdef GC_OPENBSD_THREADS
  EXTERN_C_END
# include <sys/param.h>
  EXTERN_C_BEGIN


# if OpenBSD < 201211
#define GC_OPENBSD_UTHREADS 1
# endif
#endif

#if defined(SVR4) || defined(LINUX) || defined(IRIX5) || defined(HPUX) \
    || defined(OPENBSD) || defined(NETBSD) || defined(FREEBSD) \
    || defined(DGUX) || defined(BSD) || defined(HAIKU) || defined(HURD) \
    || defined(AIX) || defined(DARWIN) || defined(OSF1)
#define UNIX_LIKE 
#endif

#if defined(CPPCHECK)
#undef CPP_WORDSZ
#define CPP_WORDSZ (__SIZEOF_POINTER__ * 8)
#elif CPP_WORDSZ != 32 && CPP_WORDSZ != 64
# error Bad word size
#endif

#ifndef ALIGNMENT
# if !defined(CPP_WORDSZ) && !defined(CPPCHECK)
# error Undefined both ALIGNMENT and CPP_WORDSZ
# endif
#define ALIGNMENT (CPP_WORDSZ >> 3)
#endif

#ifdef PCR
#undef DYNAMIC_LOADING
#undef STACKBOTTOM
#undef HEURISTIC1
#undef HEURISTIC2
#undef PROC_VDB
#undef MPROTECT_VDB
#define PCR_VDB 
#endif

#if !defined(STACKBOTTOM) && (defined(ECOS) || defined(NOSYS)) \
    && !defined(CPPCHECK)
# error Undefined STACKBOTTOM
#endif

#ifdef IGNORE_DYNAMIC_LOADING
#undef DYNAMIC_LOADING
#endif

#if defined(SMALL_CONFIG) && !defined(GC_DISABLE_INCREMENTAL)

#define GC_DISABLE_INCREMENTAL 
#endif

#if (defined(MSWIN32) || defined(MSWINCE)) && !defined(USE_WINALLOC)

#define USE_WINALLOC 1
#endif

#ifdef USE_WINALLOC
#undef USE_MMAP
#endif

#if defined(DARWIN) || defined(FREEBSD) || defined(HAIKU) \
    || defined(IRIX5) || defined(LINUX) || defined(NETBSD) \
    || defined(OPENBSD) || defined(SOLARIS) \
    || ((defined(CYGWIN32) || defined(USE_MMAP) || defined(USE_MUNMAP)) \
        && !defined(USE_WINALLOC))

#define MMAP_SUPPORTED 
#endif





#if defined(USE_MUNMAP) && !defined(MUNMAP_THRESHOLD) \
    && (defined(SN_TARGET_PS3) \
        || defined(SN_TARGET_PSP2) || defined(MSWIN_XBOX1))
#define MUNMAP_THRESHOLD 3
#endif

#if defined(USE_MUNMAP) && defined(COUNT_UNMAPPED_REGIONS) \
    && !defined(GC_UNMAPPED_REGIONS_SOFT_LIMIT)





# if defined(__DragonFly__)
#define GC_UNMAPPED_REGIONS_SOFT_LIMIT (1000000 / 4)
# else
#define GC_UNMAPPED_REGIONS_SOFT_LIMIT 16384
# endif
#endif

#if defined(GC_DISABLE_INCREMENTAL) || defined(DEFAULT_VDB)
#undef GWW_VDB
#undef MPROTECT_VDB
#undef PCR_VDB
#undef PROC_VDB
#undef SOFT_VDB
#endif

#ifdef NO_GWW_VDB
#undef GWW_VDB
#endif

#ifdef NO_MPROTECT_VDB
#undef MPROTECT_VDB
#endif

#ifdef NO_SOFT_VDB
#undef SOFT_VDB
#endif

#if defined(SOFT_VDB) && defined(SOFT_VDB_LINUX_VER_STATIC_CHECK)
  EXTERN_C_END
# include <linux/version.h>
  EXTERN_C_BEGIN
# if LINUX_VERSION_CODE < KERNEL_VERSION(3, 18, 0)

#undef SOFT_VDB
# endif
#endif

#ifdef GC_DISABLE_INCREMENTAL
#undef CHECKSUMS
#endif

#ifdef USE_GLOBAL_ALLOC

#undef GWW_VDB
#endif

#if defined(BASE_ATOMIC_OPS_EMULATED)


#undef MPROTECT_VDB
#endif

#if defined(USE_PROC_FOR_LIBRARIES) && defined(GC_LINUX_THREADS)

#undef MPROTECT_VDB
#endif

#if defined(MPROTECT_VDB) && defined(GC_PREFER_MPROTECT_VDB)

#undef PCR_VDB
#undef PROC_VDB

#endif

#ifdef PROC_VDB

#undef MPROTECT_VDB

#undef SOFT_VDB
#endif

#if defined(MPROTECT_VDB) && !defined(MSWIN32) && !defined(MSWINCE)
# include <signal.h>
#endif

#if defined(SIGBUS) && !defined(HAVE_SIGBUS) && !defined(CPPCHECK)
#define HAVE_SIGBUS 
#endif

#ifndef SA_SIGINFO
#define NO_SA_SIGACTION 
#endif

#if (defined(NO_SA_SIGACTION) || defined(GC_NO_SIGSETJMP)) \
    && defined(MPROTECT_VDB) && !defined(DARWIN) \
    && !defined(MSWIN32) && !defined(MSWINCE)
#undef MPROTECT_VDB
#endif

#if !defined(PCR_VDB) && !defined(PROC_VDB) && !defined(MPROTECT_VDB) \
    && !defined(GWW_VDB) && !defined(SOFT_VDB) && !defined(DEFAULT_VDB) \
    && !defined(GC_DISABLE_INCREMENTAL)
#define DEFAULT_VDB 
#endif

#if !defined(PROC_VDB) && !defined(SOFT_VDB) \
    && !defined(NO_VDB_FOR_STATIC_ROOTS)

#define NO_VDB_FOR_STATIC_ROOTS 
#endif

#if ((defined(UNIX_LIKE) && (defined(DARWIN) || defined(HAIKU) \
                             || defined(HURD) || defined(OPENBSD) \
                             || defined(ARM32) \
                             || defined(AVR32) || defined(MIPS) \
                             || defined(NIOS2) || defined(OR1K))) \
     || (defined(LINUX) && !defined(__gnu_linux__)) \
     || (defined(RTEMS) && defined(I386)) || defined(HOST_ANDROID)) \
    && !defined(NO_GETCONTEXT)
#define NO_GETCONTEXT 1
#endif

#ifndef PREFETCH
# if GC_GNUC_PREREQ(3, 0) && !defined(NO_PREFETCH)
#define PREFETCH(x) __builtin_prefetch((x), 0, 0)
# else
#define PREFETCH(x) (void)0
# endif
#endif

#ifndef GC_PREFETCH_FOR_WRITE
# if GC_GNUC_PREREQ(3, 0) && !defined(GC_NO_PREFETCH_FOR_WRITE)
#define GC_PREFETCH_FOR_WRITE(x) __builtin_prefetch((x), 1)
# else
#define GC_PREFETCH_FOR_WRITE(x) (void)0
# endif
#endif

#ifndef CACHE_LINE_SIZE
#define CACHE_LINE_SIZE 32
#endif

#ifndef STATIC
# ifdef GC_ASSERTIONS
#define STATIC 
# else
#define STATIC static
# endif
#endif



#if defined(HEURISTIC2) || defined(SEARCH_FOR_DATA_START) \
    || defined(HPUX_MAIN_STACKBOTTOM) || defined(IA64) \
    || (defined(CYGWIN32) && defined(I386) && defined(USE_MMAP) \
        && !defined(USE_WINALLOC)) \
    || (defined(NETBSD) && defined(__ELF__)) \
    || (defined(OPENBSD) && !defined(GC_OPENBSD_UTHREADS)) \
    || ((defined(SVR4) || defined(AIX) || defined(DGUX) \
         || defined(DATASTART_USES_BSDGETDATASTART) \
         || (defined(LINUX) && defined(SPARC))) && !defined(PCR))
#define NEED_FIND_LIMIT 
#endif

#if defined(LINUX) && (defined(USE_PROC_FOR_LIBRARIES) || defined(IA64) \
                       || !defined(SMALL_CONFIG))
#define NEED_PROC_MAPS 
#endif

#if defined(LINUX) || defined(HURD) || defined(__GLIBC__)
#define REGISTER_LIBRARIES_EARLY 





#endif

#if defined(SEARCH_FOR_DATA_START)
  extern ptr_t GC_data_start;
#define DATASTART GC_data_start
#endif

#ifndef HEAP_START
#define HEAP_START ((ptr_t)0)
#endif

#ifndef CLEAR_DOUBLE
#define CLEAR_DOUBLE(x) (((word*)(x))[0] = 0, ((word*)(x))[1] = 0)
#endif

#if defined(GC_LINUX_THREADS) && defined(REDIRECT_MALLOC) \
    && !defined(INCLUDE_LINUX_THREAD_DESCR)


#define INCLUDE_LINUX_THREAD_DESCR 
#endif

#if !defined(CPPCHECK)
# if defined(GC_IRIX_THREADS) && !defined(IRIX5)
# error Inconsistent configuration
# endif
# if defined(GC_LINUX_THREADS) && !defined(LINUX) && !defined(NACL)
# error Inconsistent configuration
# endif
# if defined(GC_NETBSD_THREADS) && !defined(NETBSD)
# error Inconsistent configuration
# endif
# if defined(GC_FREEBSD_THREADS) && !defined(FREEBSD)
# error Inconsistent configuration
# endif
# if defined(GC_SOLARIS_THREADS) && !defined(SOLARIS)
# error Inconsistent configuration
# endif
# if defined(GC_HPUX_THREADS) && !defined(HPUX)
# error Inconsistent configuration
# endif
# if defined(GC_AIX_THREADS) && !defined(_AIX)
# error Inconsistent configuration
# endif
# if defined(GC_WIN32_THREADS) && !defined(CYGWIN32) && !defined(MSWIN32) \
     && !defined(MSWINCE) && !defined(MSWIN_XBOX1)
# error Inconsistent configuration
# endif
# if defined(GC_WIN32_PTHREADS) && defined(CYGWIN32)
# error Inconsistent configuration
# endif
#endif

#if defined(PCR) || defined(GC_WIN32_THREADS) || defined(GC_PTHREADS) \
    || ((defined(NN_PLATFORM_CTR) || defined(NINTENDO_SWITCH) \
         || defined(SN_TARGET_PS3) \
         || defined(SN_TARGET_PSP2)) && defined(GC_THREADS))
#define THREADS 
#endif

#if defined(PARALLEL_MARK) && !defined(THREADS) && !defined(CPPCHECK)
# error Invalid config: PARALLEL_MARK requires GC_THREADS
#endif

#if defined(GWW_VDB) && !defined(USE_WINALLOC) && !defined(CPPCHECK)
# error Invalid config: GWW_VDB requires USE_WINALLOC
#endif

#if defined(GC_PTHREADS) && !defined(GC_DARWIN_THREADS) \
    && !defined(GC_WIN32_THREADS) && !defined(PLATFORM_STOP_WORLD) \
    && !defined(SN_TARGET_PSP2)
#define PTHREAD_STOP_WORLD_IMPL 
#endif

#if defined(PTHREAD_STOP_WORLD_IMPL) && !defined(NACL) \
    && !defined(GC_OPENBSD_UTHREADS)
#define SIGNAL_BASED_STOP_WORLD 
#endif

#if (defined(E2K) || defined(HP_PA) || defined(IA64) || defined(M68K) \
     || defined(NO_SA_SIGACTION)) && defined(SIGNAL_BASED_STOP_WORLD)
#define SUSPEND_HANDLER_NO_CONTEXT 
#endif

#if (((defined(MSWIN32) || defined(MSWINCE)) && !defined(__GNUC__)) \
        || (defined(MSWIN32) && defined(I386)) \
        || (defined(USE_PROC_FOR_LIBRARIES) && defined(THREADS))) \
    && !defined(NO_CRT) && !defined(NO_WRAP_MARK_SOME)
# 2988 "gcconfig.h"
#define WRAP_MARK_SOME 
#endif

#if defined(PARALLEL_MARK) && !defined(DEFAULT_STACK_MAYBE_SMALL) \
    && (defined(HPUX) || defined(GC_DGUX386_THREADS) \
        || defined(NO_GETCONTEXT) )

#define DEFAULT_STACK_MAYBE_SMALL 
#endif

#ifdef PARALLEL_MARK

#define MIN_STACK_SIZE (8 * HBLKSIZE * sizeof(word))
#endif

#if defined(HOST_ANDROID) && !defined(THREADS) \
    && !defined(USE_GET_STACKBASE_FOR_MAIN)



#define USE_GET_STACKBASE_FOR_MAIN 
#endif


#if ((defined(FREEBSD) && defined(__GLIBC__)) \
     || defined(LINUX) || defined(NETBSD) || defined(HOST_ANDROID)) \
    && !defined(NO_PTHREAD_GETATTR_NP)
#define HAVE_PTHREAD_GETATTR_NP 1
#elif defined(FREEBSD) && !defined(__GLIBC__) \
      && !defined(NO_PTHREAD_ATTR_GET_NP)
#define HAVE_PTHREAD_NP_H 1
#define HAVE_PTHREAD_ATTR_GET_NP 1
#endif

#if !defined(HAVE_CLOCK_GETTIME) && defined(_POSIX_TIMERS) \
    && (defined(CYGWIN32) || (defined(LINUX) && defined(__USE_POSIX199309)))
#define HAVE_CLOCK_GETTIME 1
#endif

#if defined(UNIX_LIKE) && defined(THREADS) && !defined(NO_CANCEL_SAFE) \
    && !defined(HOST_ANDROID)
# 3041 "gcconfig.h"
#define CANCEL_SAFE 
#endif

#ifdef CANCEL_SAFE
#define IF_CANCEL(x) x
#else
#define IF_CANCEL(x) 
#endif

#if !defined(CAN_HANDLE_FORK) && !defined(NO_HANDLE_FORK) \
    && !defined(HAVE_NO_FORK) \
    && ((defined(GC_PTHREADS) && !defined(NACL) \
         && !defined(GC_WIN32_PTHREADS) && !defined(USE_WINALLOC)) \
        || (defined(DARWIN) && defined(MPROTECT_VDB)) || defined(HANDLE_FORK))


#define CAN_HANDLE_FORK 
#endif

#if defined(CAN_HANDLE_FORK) && !defined(CAN_CALL_ATFORK) \
    && !defined(GC_NO_CAN_CALL_ATFORK) && !defined(HOST_TIZEN) \
    && !defined(HURD) && (!defined(HOST_ANDROID) || __ANDROID_API__ >= 21)

#define CAN_CALL_ATFORK 
#endif

#if !defined(CAN_HANDLE_FORK) && !defined(HAVE_NO_FORK) \
    && !(defined(CYGWIN32) || defined(SOLARIS) || defined(UNIX_LIKE))
#define HAVE_NO_FORK 
#endif

#if !defined(USE_MARK_BITS) && !defined(USE_MARK_BYTES) \
    && defined(PARALLEL_MARK)

#define USE_MARK_BYTES 
#endif

#if (defined(MSWINCE) && !defined(__CEGCC__) || defined(MSWINRT_FLAVOR)) \
    && !defined(NO_GETENV)
#define NO_GETENV 
#endif

#if (defined(NO_GETENV) || defined(MSWINCE)) && !defined(NO_GETENV_WIN32)
#define NO_GETENV_WIN32 
#endif

#if !defined(MSGBOX_ON_ERROR) && !defined(NO_MSGBOX_ON_ERROR) \
    && !defined(SMALL_CONFIG) && defined(MSWIN32) \
    && !defined(MSWINRT_FLAVOR) && !defined(MSWIN_XBOX1)


#define MSGBOX_ON_ERROR 
#endif

#ifndef STRTOULL
# if defined(_WIN64) && !defined(__GNUC__)
#define STRTOULL _strtoui64
# elif defined(_LLP64) || defined(__LLP64__) || defined(_WIN64)
#define STRTOULL strtoull
# else

#define STRTOULL strtoul
# endif
#endif

#ifndef GC_WORD_C
# if defined(_WIN64) && !defined(__GNUC__)
#define GC_WORD_C(val) val ##ui64
# elif defined(_LLP64) || defined(__LLP64__) || defined(_WIN64)
#define GC_WORD_C(val) val ##ULL
# else
#define GC_WORD_C(val) ((word)val ##UL)
# endif
#endif

#if defined(__has_feature)

# if __has_feature(address_sanitizer)
#define ADDRESS_SANITIZER 
# endif
# if __has_feature(memory_sanitizer)
#define MEMORY_SANITIZER 
# endif
# if __has_feature(thread_sanitizer) && defined(THREADS)
#define THREAD_SANITIZER 
# endif
#else
# ifdef __SANITIZE_ADDRESS__

#define ADDRESS_SANITIZER 
# endif
# if defined(__SANITIZE_THREAD__) && defined(THREADS)

#define THREAD_SANITIZER 
# endif
#endif

#if defined(SPARC)
#define ASM_CLEAR_CODE 

#endif
# 3151 "gcconfig.h"
#if defined(SPARC)
#define CAN_SAVE_CALL_ARGS 
#endif
#if (defined(I386) || defined(X86_64)) \
    && (defined(LINUX) || defined(__GLIBC__))


#define CAN_SAVE_CALL_ARGS 
#endif

#if defined(SAVE_CALL_COUNT) && !defined(GC_ADD_CALLER) \
    && defined(GC_CAN_SAVE_CALL_STACKS)
#define SAVE_CALL_CHAIN 
#endif
#ifdef SAVE_CALL_CHAIN
# if defined(SAVE_CALL_NARGS) && defined(CAN_SAVE_CALL_ARGS)
#define NARGS SAVE_CALL_NARGS
# else
#define NARGS 0
# endif
#endif
#ifdef SAVE_CALL_CHAIN
# if !defined(SAVE_CALL_COUNT) || defined(CPPCHECK)
#define NFRAMES 6

# else
#define NFRAMES ((SAVE_CALL_COUNT + 1) & ~1)
# endif
#define NEED_CALLINFO 
#endif
#ifdef GC_ADD_CALLER
#define NFRAMES 1
#define NARGS 0
#define NEED_CALLINFO 
#endif

#if (defined(FREEBSD) || (defined(DARWIN) && !defined(_POSIX_C_SOURCE)) \
        || (defined(SOLARIS) && (!defined(_XOPEN_SOURCE) \
                                 || defined(__EXTENSIONS__))) \
        || defined(LINUX)) && !defined(HAVE_DLADDR)
#define HAVE_DLADDR 1
#endif

#if defined(MAKE_BACK_GRAPH) && !defined(DBG_HDRS_ALL)
#define DBG_HDRS_ALL 1
#endif

#if defined(POINTER_MASK) && !defined(POINTER_SHIFT)
#define POINTER_SHIFT 0
#endif

#if defined(POINTER_SHIFT) && !defined(POINTER_MASK)
#define POINTER_MASK ((word)(-1))
#endif

#if !defined(FIXUP_POINTER) && defined(POINTER_MASK)
#define FIXUP_POINTER(p) (p = ((p) & POINTER_MASK) << POINTER_SHIFT)
#endif

#if defined(FIXUP_POINTER)
#define NEED_FIXUP_POINTER 
#else
#define FIXUP_POINTER(p) 
#endif

#if !defined(MARK_BIT_PER_GRANULE) && !defined(MARK_BIT_PER_OBJ)
#define MARK_BIT_PER_GRANULE 
#endif


#if !defined(CPPCHECK)
# if defined(MARK_BIT_PER_GRANULE) && defined(MARK_BIT_PER_OBJ)
# error Define only one of MARK_BIT_PER_GRANULE and MARK_BIT_PER_OBJ
# endif
# if defined(STACK_GROWS_UP) && defined(STACK_GROWS_DOWN)
# error Only one of STACK_GROWS_UP and STACK_GROWS_DOWN should be defined
# endif
# if !defined(STACK_GROWS_UP) && !defined(STACK_GROWS_DOWN)
# error One of STACK_GROWS_UP and STACK_GROWS_DOWN should be defined
# endif
# if defined(REDIRECT_MALLOC) && defined(THREADS) && !defined(LINUX) \
     && !defined(REDIRECT_MALLOC_IN_HEADER)
# error REDIRECT_MALLOC with THREADS works at most on Linux
# endif
#endif

#ifdef GC_PRIVATE_H
# 3254 "gcconfig.h"
#define hblk GC_hblk_s
  struct hblk;
# if defined(PCR)
    char * real_malloc(size_t bytes);
#define GET_MEM(bytes) HBLKPTR(real_malloc(SIZET_SAT_ADD(bytes, \
                                                            GC_page_size)) \
                                          + GC_page_size-1)
# elif defined(OS2)
    void * os2_alloc(size_t bytes);
#define GET_MEM(bytes) HBLKPTR((ptr_t)os2_alloc( \
                                            SIZET_SAT_ADD(bytes, \
                                                          GC_page_size)) \
                                  + GC_page_size-1)
# elif defined(NEXT) || defined(DOS4GW) || defined(NONSTOP) \
        || (defined(AMIGA) && !defined(GC_AMIGA_FASTALLOC)) \
        || (defined(SOLARIS) && !defined(USE_MMAP)) || defined(RTEMS) \
        || defined(__CC_ARM)
#define GET_MEM(bytes) HBLKPTR((size_t)calloc(1, \
                                            SIZET_SAT_ADD(bytes, \
                                                          GC_page_size)) \
                                  + GC_page_size - 1)
# elif defined(MSWIN_XBOX1)
    ptr_t GC_durango_get_mem(size_t bytes);
#define GET_MEM(bytes) (struct hblk *)GC_durango_get_mem(bytes)
# elif defined(MSWIN32) || defined(CYGWIN32)
    ptr_t GC_win32_get_mem(size_t bytes);
#define GET_MEM(bytes) (struct hblk *)GC_win32_get_mem(bytes)
# elif defined(MACOS)
# if defined(USE_TEMPORARY_MEMORY)
      Ptr GC_MacTemporaryNewPtr(size_t size, Boolean clearMemory);
#define GET_MEM(bytes) HBLKPTR(GC_MacTemporaryNewPtr( \
                                        SIZET_SAT_ADD(bytes, \
                                                      GC_page_size), true) \
                        + GC_page_size-1)
# else
#define GET_MEM(bytes) HBLKPTR(NewPtrClear(SIZET_SAT_ADD(bytes, \
                                                              GC_page_size)) \
                                    + GC_page_size-1)
# endif
# elif defined(MSWINCE)
    ptr_t GC_wince_get_mem(size_t bytes);
#define GET_MEM(bytes) (struct hblk *)GC_wince_get_mem(bytes)
# elif defined(AMIGA) && defined(GC_AMIGA_FASTALLOC)
    void *GC_amiga_get_mem(size_t bytes);
#define GET_MEM(bytes) HBLKPTR((size_t)GC_amiga_get_mem( \
                                            SIZET_SAT_ADD(bytes, \
                                                          GC_page_size)) \
                          + GC_page_size-1)
# elif defined(PLATFORM_GETMEM)
    void *platform_get_mem(size_t bytes);
#define GET_MEM(bytes) (struct hblk*)platform_get_mem(bytes)
# elif defined(SN_TARGET_PS3)
    void *ps3_get_mem(size_t bytes);
#define GET_MEM(bytes) (struct hblk*)ps3_get_mem(bytes)
# elif defined(SN_TARGET_PSP2)
    void *psp2_get_mem(size_t bytes);
#define GET_MEM(bytes) (struct hblk*)psp2_get_mem(bytes)
# elif defined(NINTENDO_SWITCH)
    void *switch_get_mem(size_t bytes);
#define GET_MEM(bytes) (struct hblk*)switch_get_mem(bytes)
# elif defined(HAIKU)
    ptr_t GC_haiku_get_mem(size_t bytes);
#define GET_MEM(bytes) (struct hblk*)GC_haiku_get_mem(bytes)
# elif defined(EMSCRIPTEN_TINY)
    void *emmalloc_memalign(size_t alignment, size_t size);
#define GET_MEM(bytes) (struct hblk*)emmalloc_memalign(GC_page_size, bytes)
# else
    ptr_t GC_unix_get_mem(size_t bytes);
#define GET_MEM(bytes) (struct hblk *)GC_unix_get_mem(bytes)
# endif
#endif

EXTERN_C_END

#endif
