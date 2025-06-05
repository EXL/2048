#ifndef _STDINT_H_
#define _STDINT_H_

/* TYPE DEFINITIONS */
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef signed char int_least8_t;
typedef short int_least16_t;
typedef int int_least32_t;

typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned int uint_least32_t;

typedef signed char int_fast8_t;
typedef short int_fast16_t;
typedef int int_fast32_t;

typedef unsigned char uint_fast8_t;
typedef unsigned short uint_fast16_t;
typedef unsigned int uint_fast32_t;

typedef int intptr_t;
typedef unsigned int uintptr_t;

typedef long long intmax_t;
typedef unsigned long long uintmax_t;

/* LIMIT MACROS */
#define INT8_MIN (-0x7f - 1)
#define INT16_MIN (-0x7fff - 1)
#define INT32_MIN (-0x7fffffff - 1)

#define INT8_MAX 0x7f
#define INT16_MAX 0x7fff
#define INT32_MAX 0x7fffffff

#define UINT8_MAX 0xff
#define UINT16_MAX 0xffff
#define UINT32_MAX 0xffffffff

#define INT_LEAST8_MIN (-0x7f - 1)
#define INT_LEAST16_MIN (-0x7fff - 1)
#define INT_LEAST32_MIN (-0x7fffffff - 1)

#define INT_LEAST8_MAX 0x7f
#define INT_LEAST16_MAX 0x7fff
#define INT_LEAST32_MAX 0x7fffffff

#define UINT_LEAST8_MAX 0xff
#define UINT_LEAST16_MAX 0xffff
#define UINT_LEAST32_MAX 0xffffffff

#define INT_FAST8_MIN (-0x7f - 1)
#define INT_FAST16_MIN (-0x7fff - 1)
#define INT_FAST32_MIN (-0x7fffffff - 1)

#define INT_FAST8_MAX 0x7f
#define INT_FAST16_MAX 0x7fff
#define INT_FAST32_MAX 0x7fffffff

#define UINT_FAST8_MAX 0xff
#define UINT_FAST16_MAX 0xffff
#define UINT_FAST32_MAX 0xffffffff

#define INTPTR_MIN (-0x7fffffff - 1)
#define INTPTR_MAX 0x7fffffff
#define UINTPTR_MAX 0xffffffff

#define INT8_C(x) (x)
#define INT16_C(x) (x)
#define INT32_C(x) ((x) + (INT32_MAX - INT32_MAX))
#define INT64_C(x) ((x) + (INT64_MAX - INT64_MAX))

#define UINT8_C(x) (x)
#define UINT16_C(x) (x)
#define UINT32_C(x) ((x) + (UINT32_MAX - UINT32_MAX))
#define UINT64_C(x) ((x) + (UINT64_MAX - UINT64_MAX))

#define PTRDIFF_MIN INT32_MIN
#define PTRDIFF_MAX INT32_MAX

#define SIG_ATOMIC_MIN INT32_MIN
#define SIG_ATOMIC_MAX INT32_MAX

#define SIZE_MAX UINT32_MAX

#define WCHAR_MIN 0
#define WCHAR_MAX UINT16_MAX

#define WINT_MIN 0
#define WINT_MAX UINT16_MAX

#endif
