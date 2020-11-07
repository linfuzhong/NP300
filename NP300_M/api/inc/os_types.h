/******************************************************************************/
/** \file os_types.h
 **
 ** os type common define.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2020-11-07  1.0  LFZ First version.
 **
 ******************************************************************************/

#ifndef __OS_TYPES_H__
#define __OS_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#define SMALL_LETTER_TYPE

//#define CAPITALIZE_TYPE           
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
#ifndef MIN
#define MIN( x, y )  			   ((x) < (y) ? (x) : (y))
#endif

#ifndef MAX
#define MAX( x, y )  			   ((x) > (y) ? (x) : (y))
#endif

#ifndef NULL
#define NULL                 ((void *)0)
#endif

#ifndef	BYTE_BIT
#define BYTE_BIT(i)          ((unsigned char) (0x01  << (i)))
#endif

#ifndef	WORD_BIT
#define WORD_BIT(i)          ((unsigned short)(0x01u << (i)))
#endif

#ifndef	ARRAY_SIZE
#define ARRAY_SIZE(x)  	     (sizeof(x) / sizeof(x[0]))
#endif

/* Small exact-width signed/unsigned integer types */
#ifdef  SMALL_LETTER_TYPE
#ifndef bool
#define bool                 _Bool
#endif

#ifndef true
#define true                 (1)
#endif

#ifndef false
#define false                (0)
#endif 

typedef   signed char        int8;
typedef unsigned char        uint8;

typedef   signed short       int16;
typedef unsigned short       uint16;

typedef   signed long        int32;
typedef unsigned long        uint32;

typedef   signed long  long  int64;
typedef unsigned long  long  uint64;
#endif

/* Capitalize exact-width signed/unsigned integer types */
#ifdef  CAPITALIZE_TYPE
#ifndef BOOL
#define BOOL                 _Bool
#endif

#ifndef TRUE
#define TRUE                 (1)
#endif

#ifndef FALSE
#define FALSE                (0)
#endif 

typedef   signed char        INT8;
typedef unsigned char        UINT8;

typedef   signed short       INT16;
typedef unsigned short       UINT16;

typedef   signed long        INT32;
typedef unsigned long        UINT32;

typedef   signed long  long  INT64;
typedef unsigned long  long  UINT64;
#endif

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/** function pointer type to void/void function */
typedef void   (*func_cb_void)(void);

/** function pointer type to void/uint8_t function */
typedef void   (*func_cb_u8)(uint8);

/** function pointer type to void/uint16_t function */
typedef void   (*func_cb_u16)(uint16);

/** function pointer type to void/uint32_t function */
typedef void   (*func_cb_u32)(uint32);

#ifdef __cplusplus  // close out "C" linkage in case of c++ compiling
}
#endif

#endif /* __OS_TYPES_H__ */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/



