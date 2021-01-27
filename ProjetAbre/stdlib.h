/* Sorry for the very cryptic file. It is cryptic not because I want it to  */
/* be cryptic, but because it must be written in such manner. I have very   */
/* strong reasons for usage of (very awkward) casting arrays to functions.  */
/* Namely, such definitions allow that a function which is not called in    */
/* the program will not be included in the program, and a function which is */
/* called more than once will be included just once. The first property     */
/* would not be true if a function is implemented as a "normal" function in */
/* the header file, and the second property would not be true if a function */
/* is implemented as a smart inline macro. In "normal" C compilers, such    */
/* problems are solved using an external library of object files which      */
/* contain implementations of all functions, and they would be linked with  */
/* the program when necessary. But note that TI-GCC linker does not support */
/* external libraries of object files, so for a while, such "cryptic"       */
/* definitions are the only solution! True sources of all routines are      */
/* presented in a file named "SOURCES".                                     */

#ifndef __STDLIB
#define __STDLIB

#ifndef NOSTUB
#ifndef DOORS
#ifndef USE_KERNEL
#include <nostub.h>
#else
#include <doors.h>
#endif
#endif
#endif

#undef NULL
#undef size_t
#define NULL ((void*)0)
#define size_t unsigned long

#ifndef __SABS
#define __SABS

#define abs(x) ({typeof(x) __x=(x); __x>=0?__x:-__x;})

#endif

long labs(long);     /* These two functions are open-coded in GCC itself */
void *alloca(long);  /* Only prototypes are necessary...                 */

typedef struct
  {
    short quot, rem;
  } div_t;

typedef struct
  {
    long quot, rem;
  } ldiv_t;

#define div(n,d) \
  ({short __n=(n),__d=(d); div_t __r; __r.quot=__n/__d; __r.rem=__n%__d; __r;})

#ifndef DOORS

#define ldiv(n,d) \
  ({ldiv_t __r; long __n=(n),__d=(d); \
    asm("move.l 0xC8,%%a5;" \
        "move.l %2,%%d1;" \
        "move.l %3,%%d0;" \
        "move.l (%%a5,2720),%%a0;" \
        "jsr (%%a0);" \
        "move.l %%d1,%0;" \
        "move.l %2,%%d1;" \
        "move.l %3,%%d0;" \
        "move.l (%%a5,2724),%%a0;" \
        "jsr (%%a0);" \
        "move.l %%d1,%1" : \
      "=g"(__r.quot),"=g"(__r.rem) : "g"(__n),"g"(__d): \
      "a0","a1","a5","d0","d1","d2"); __r;})

#else

#define ldiv(n,d) \
  ({ldiv_t __r; long __n=(n),__d=(d); \
    asm("move.l %2,%%d1;" \
        "move.l %3,%%d0;" \
        "jsr _ROM_CALL_2A8;" \
        "move.l %%d1,%0;" \
        "move.l %2,%%d1;" \
        "move.l %3,%%d0;" \
        "jsr _ROM_CALL_2A9;" \
        "move.l %%d1,%1" : \
      "=g"(__r.quot),"=g"(__r.rem): \
      "g"(__n),"g"(__d):"a0","a1","d0","d1","d2"); __r;})

#endif

#define max(a,b) ({typeof(a) __a=(a); typeof(b) __b=(b); (__a>__b)?__a:__b;})
#define min(a,b) ({typeof(a) __a=(a); typeof(b) __b=(b); (__a<__b)?__a:__b;})

typedef void (*atexit_t)(void);

#define atexit ((short(*)(atexit_t))(long[]){0x4878001C,0x207800C8,0x20680288, \
  0x4E90588F,0x20086748,0x224E08C0,0x1F2040,0x20290004,0x22092251,0xC800020, \
  0x65F0,0x22412348,0x430FC,0x4EB920EF,0x420FC,0x487AFFF8,0x20FC2078, \
  0xC820FC,0x2068028C,0x20FC4E90,0x584F30FC,0x4EF92080,0x42804E75,0x70014E75})

typedef void __voidfn__(void);

#define __exit ((volatile __voidfn__*)(long[]){0x4E5E0C97,0x200000, \
      0x65F62078,0xC82268,0x4242468,0x9A82669,0xFFF84E75})

#define exit(n) ({(n)?_rom_call(void,(short),152)(n):0; __exit(); return;})

#define abort() \
  (_rom_call(void,(),E6)("ABNORMAL PROGRAM TERMINATION"),exit(0));

#define bsearch ((void*(*)(void*,void*,short,short,long(*)(void*,void*))) \
  (long[]){0x4E560000,0x48E71F38,0x286E0008,0x266E000C,0x3E2E0012, \
  0x246E0014,0x42463A2E,0x105345,0x3606D645,0xE24B3003,0xC0C7280B, \
  0xD8802F04,0x2F0C4E92,0x508F4A40,0x6F063C03,0x5246600C,0x4A406D04, \
  0x2044600A,0x3A035345,0xBA4664D0,0x91C84CEE,0x1CF8FFE0,0x4E5E4E75})

#define qsort ((void(*)(void*,short,short,long(*)(void*,void*)))(long[]) \
  {0x4E56FFEC,0x48E71F3C,0x302E000C,0x326E000E,0x3840340C,0xE2423842, \
  0x67000088,0x3D49FFEE,0xC1EEFFEE,0x3D40FFEE,0x9BCD380C,0x3409C9C2, \
  0x3E04B86E,0xFFEE6462,0x42AEFFF0,0x3D44FFF2,0x262E0008,0xD6AEFFF0, \
  0x240D3407,0x2A42968D,0xB6AE0008,0x653C7C00,0x7A002643,0x3C072443, \
  0xD5C62F0A,0x2F032D49,0xFFF4206E,0x104E90,0x508F226E,0xFFF44A80, \
  0x6F183209,0x670A1013,0x16D214C0,0x534166F6,0x3A079685,0xB6AE0008, \
  0x64C8D849,0xB86EFFEE,0x65A2340C,0xE24A3842,0x66884CEE,0x3CF8FFC8, \
  0x4E5E4E75})

#define RAND_MAX 32767

#define rand ((short(*)(void))(short[]){0x41FA,48,0x243C,0x41C6,0x4E6D,0x2210, \
  0x2002,0xC0C1,0x4842,0xC4C1,0x4841,0xC2FC,0x4E6D,0xD441,0x4842,0x4242, \
  0xD082,0x680,0,0x3039,0x2080,0xE088,0x240,0x7FFF,0x4E75,0,1})

#define srand(x) (*(long*)((char*)rand+50)=(x))
#define random(x) ((short)((long)(unsigned short)rand()*(unsigned short)(x)/32768))
#define randomize() srand(*(char*)0x600017)

#define atoi ((short(*)(char*))(long[]){0x4E560000,0x2F03206E,0x84241, \
  0x42436002,0x52881010,0xC000020,0x67F60C00,0x2D6706,0xC0000AD,0x66085288, \
  0x363CFFFF,0x60180C00,0x2B6612,0x5288600E,0x3001E748,0xD041D240, \
  0xD2420641,0xFFD04242,0x14183002,0x640FFD0,0xC400009,0x63E23001, \
  0x4A436702,0x4440261F,0x4E5E4E75})

#define atol ((long(*)(char*))(long[]){0x4E560000,0x2F042F03,0x226E0008, \
  0x42447400,0x60025289,0x10110C00,0x2067F6,0xC00002D,0x67060C00,0xAD6608, \
  0x5289383C,0xFFFF6008,0xC00002B,0x66025289,0x42411219,0x30010640, \
  0xFFD00C40,0x96224,0x76002002,0xD080E78A,0x2042D1C0,0x360141F0,0x38D02408, \
  0x42411219,0x30010640,0xFFD00C40,0x963DE,0x20024A44,0x67024480,0x261F281F, \
  0x4E5E4E75})

#ifndef __ATOF
#define __ATOF

#define atof ((float(*)(char*))(short[]){0x4E56,0xFFB0,0x48E7,0x1F3C,0x2878, \
  0xC8,0x266C,0x424,0x2813,0x486E,0xFFB0,0x206C,0x550,0x4E90,0x4A40,0x670C, \
  0x203C,0x7FFF,0xAA00,0x4281,0x4242,0x603C,0x2EAE,8,0x206C,0xF28,0x4E90, \
  0x2053,0x1A10,0xC05,0x7A,0x6602,0x5348,0x2E88,0x206C,0xBE4,0x4E90,0x2684, \
  0x206C,0x554,0x4E90,0x202E,0xFFF6,0x222E,0xFFFA,0x342E,0xFFFE,0xC05,0x7A, \
  0x6604,0x8C0,0x1F,0x4CEE,0x3CF8,0xFF8C,0x4E5E,0x4E75})

#endif

#define strtoul ((unsigned long(*)(char*,char**,short))(long[]){0x4E560000, \
  0x48E71F3C,0x2A6E0008,0x286E000C,0x3A2E0010,0x264D4243,0x161B0C43, \
  0x2067F8,0xC43002B,0x66044243,0x161B4A45,0x67060C45,0x10661E,0xC430030, \
  0x66181013,0xC000078,0x67060C00,0x58660A,0x4243162B,0x1548B,0x7A104A45, \
  0x660A7A0A,0xC430030,0x66027A08,0x344572FF,0x200A2078,0xC82068,0xAA84E90, \
  0x244172FF,0x200A2078,0xC82068,0xAAC4E90,0x3E0191C8,0x42447C00,0x6032BA43, \
  0x63724A44,0x6D0AB5C8,0x65066608,0xBE436404,0x78FF6018,0x78012008, \
  0xC0C52208,0x4841C2C5,0x48414241,0xD0812040,0x3C03D1C6,0x4243161B, \
  0x30030640,0xFFD00C40,0x96204,0x360060BE,0x42423203,0x641FFBF,0xC410019, \
  0x630C3003,0x640FF9F,0xC400019,0x62027401,0x4A426714,0x30030640, \
  0xFFA90C41,0x1962D0,0x30030640,0xFFC960C8,0x4A446C04,0x307CFFFF, \
  0xB8FC0000,0x670C4A44,0x6706538B,0x288B6002,0x288D2008,0x4CDF3CF8, \
  0x4E5E4E75})

#define strtol ((long(*)(char*,char**,short))(long[]){0x4E56FFF8,0x48E71F3C, \
  0x3C2E0010,0x266E0008,0x387C0000,0x4243161B,0x0C430020,0x67F80C43, \
  0x2D6706,0xC4300AD,0x6606387C,0x16006,0xC43002B,0x66044243,0x161B4A46, \
  0x67060C46,0x10661E,0xC430030,0x66181013,0xC000078,0x67060C00,0x58660A, \
  0x4243162B,0x1548B,0x7C104A46,0x660A7C0A,0xC430030,0x66027C08,0x283C7FFF, \
  0xFFFF3E0C,0x6706283C,0x80000000,0x34462204,0x200A2078,0xC82068,0xAA84E90, \
  0x24412204,0x200A2078,0xC82068,0xAAC4E90,0x3D41FFFA,0x78004245,0x42AEFFFC, \
  0x6038BC43,0x63784A45,0x6D0CB5C4,0x6508660A,0xB66EFFFA,0x63047AFF, \
  0x601C7A01,0x2004C0C6,0x22044841,0xC2C64841,0x4241D081,0x28003D43, \
  0xFFFED8AE,0xFFFC4243,0x161B3003,0x640FFD0,0xC400009,0x62043600, \
  0x60B84242,0x32030641,0xFFBF0C41,0x19630C,0x30030640,0xFF9F0C40,0x196202, \
  0x74014A42,0x67143003,0x640FFA9,0xC410019,0x62D03003,0x640FFC9,0x60C84A45, \
  0x6C12283C,0x7FFFFFFF,0x3E0C670E,0x283C8000,0x6006,0x3E0C6702,0x44844AAE, \
  0xC6716,0x4A45670A,0x538B2A6E,0xC2A8B,0x60082A6E,0xC2AAE,0x82004, \
  0x4CDF3CF8,0x4E5E4E75})

#ifndef __FLOAT_INTERFACE
#define __FLOAT_INTERFACE

#define __BC ((float(*)())(short[]){0x4E56,-10,0x2F2E,26,0x2F2E,22,0x2F2E, \
  18,0x2F2E,14,0x2F2E,10,0x302E,8,0x2078,200,0x2070,0,0x4E90,0x202E,-10, \
  0x222E,-6,0x342E,-2,0x4E5E,0x4E75})

#define _tios_float_1(f,x,t) ((float(*)(short,t))__BC)(4*0x##f,x)
#define _tios_float_2(f,x,y,t1,t2) ((float(*)(short,t1,t2))__BC)(4*0x##f,x,y)

#endif

#ifndef __FABS
#define __FABS

#define fabs(x) _tios_float_1(106,x,float)

#endif

#ifndef __STDALLOC
#define __STDALLOC

#define malloc _rom_call(void*,(long),A2)
#define free _rom_call(void,(void*),A3)

#define calloc ((void*(*)(short,short))(short[]){0x4E56,0,0x302E,8,0xC0EE,10, \
  0x2F00,0x2078,0xC8,0x2068,0x288,0x4E90,0x2008,0x6710,0x4267,0x2F08,0x2078, \
  0xC8,0x2068,0x9F0,0x4E90,0x6006,0x207C,0,0,0x4E5E,0x4E75})

#define realloc ((void*(*)(void*,long))(long[]){0x4E560000,0x48E71030, \
  0x206E0008,0x266E000C,0x3628FFFE,0x247800C8,0x3F03206A,0x027C4E90, \
  0x486B0002,0x3F03206A,0x2744E90,0x206A0264,0x4A406606,0x4E9091C8, \
  0x60044E90,0x54884CEE,0xC08FFF4,0x4E5E4E75})

#ifdef DOORS

void *malloc(long);
void free(void*);

#endif

#endif

#endif
