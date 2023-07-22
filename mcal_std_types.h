/* 
 * File     : mcal_std_types.h
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 21, 2023, 6:13 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/**************************Includes-Section*****************************/
#include "std_libraries.h"
#include "compiler.h"
/***********************************************************************/

/********************Data Types Declarations-Section********************/
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;

typedef uint8 Std_ReturnType;
/***********************************************************************/

/**********************Macro Declarations-Section***********************/
#define STD_HIGH       0x01
#define STD_LOW        0x00

#define STD_ON         0x01
#define STD_OFF        0x00

#define STD_ACTIVE     0x01
#define STD_IDLE       0x00

#define E_OK         (Std_ReturnType)0x01
#define E_NOT_OK     (Std_ReturnType)0x00

#define ZERO_INT 0
/***********************************************************************/

/******************Macro Function Declarations-Section******************/

/***********************************************************************/

/**********Software Interfaces Functions Declarations-Section***********/

/***********************************************************************/
#endif	/* MCAL_STD_TYPES_H */

