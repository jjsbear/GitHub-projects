///
///  Copyright (c) 2008 - 2009 Advanced Micro Devices, Inc.
 
///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file amd_adl.h
/// \brief Contains all AMD internal main functions exposed by ADL for \ALL platforms.
///
/// This file contains all AMD internal main functions exposed by ADL for \ALL platforms.
/// All functions in this file can be used as a reference to ensure
/// the specified function pointers can be used by the appropriate runtime
/// dynamic library loaders. This header file is for AMD internal use only.

#ifndef AMD_ADL_H_
#define AMD_ADL_H_

#ifndef EXPOSED
#define EXPOSED
#endif /* EXPOSED */

#include "adl_defines.h"
#include "amd_defines.h"
#include "adl_structures.h"
#include "amd_structures.h"

#include "amd_adapter.h"
#include "amd_display.h"

/// Log error callback
typedef int ( __stdcall *ADL_MAIN_LOGERROR_CALLBACK )(char*, int);

/// Log debug callback
typedef int ( __stdcall *ADL_MAIN_LOGDEBUG_CALLBACK )(char*, int);

///
/// \brief ADL local interface. Function to set the log error callback pointer.
/// 
/// This function sets the log error call function pointer. This pointer can then be used to retrieve more detailed error information.
/// \param[in]  callback The ADL_MAIN_LOGERROR_CALLBACK function pointer to be set.
/// \platform 
/// \ALL
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Main_LogError_Set ( ADL_MAIN_LOGERROR_CALLBACK callback );

///
/// \brief ADL local interface. Function to set the log debug callback pointer.
/// 
/// This function sets the log debug call function pointer. This pointer can then be used to retrieve more detailed error information.
/// \param[in]  callback The ADL_MAIN_LOGDEBUG_CALLBACK function pointer to be set.
/// \platform 
/// \ALL
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Main_LogDebug_Set ( ADL_MAIN_LOGDEBUG_CALLBACK callback );


///
/// \brief ADL local interface. Function to determine whether a function is exposed in a DLL module.
/// 
/// This function checks whether a specified function is defined and exposed in a particular DLL module (valid). Only valid functions can be successfully called.
/// \param[in]  lpModule The pointer to the handle of the desired DLL module.
/// \param[in]  lpProcName The pointer to the name of the desired function.
/// \platform 
/// \ALL
/// \return If the specified function is valid, the return value is 1. Otherwise it is 0. 
int EXPOSED ADL_Main_Control_IsFunctionValid ( void* lpModule, char* lpProcName );

///
/// \brief ADL local interface. Function to determine the validity of and retrieve the function pointer (similar to the GetProcAdress API) for a specified function.
/// 
/// This function returns the function pointer of a specified function if it is valid (defined and exposed in a DLL module). Call this function to ensure that a function is valid before calling it.
/// \param[in]  lpModule The pointer to the desired handle of the DLL.
/// \param[in]  lpProcName The pointer to the desired function name.
/// \platform 
/// \ALL
/// \return If the specified function is valid, the return value is a function pointer. Otherwise it is NULL.
EXPOSED void* ADL_Main_Control_GetProcAddress ( void* lpModule, char* lpProcName );


#endif /* AMD_ADL_H_ */
