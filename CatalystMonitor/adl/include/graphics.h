///
///  Copyright (c) 2008 - 2009 Advanced Micro Devices, Inc.
 
///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file adapter.h
/// \brief Contains all graphics-related functions exposed by ADL for \ALL platforms.
///
/// This file contains all graphics-related functions exposed by ADL for \ALL platforms.
/// All functions found in this file can be used as a reference when creating
/// specific function pointers to be used by the appropriate runtime
/// dynamic library loaders.

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

///////////////////////////////////////////////////////////////////////////
// ADLPlatform Enumeration
///////////////////////////////////////////////////////////////////////////
enum ADLPlatForm
{
    GRAPHICS_PLATFORM_DESKTOP  = 0,
    GRAPHICS_PLATFORM_MOBILE   = 1,
};


/// \addtogroup MAINAPI
// @{

///
/// \brief Function to retrieve the type of graphics platform the system is currently running.
/// 
/// This function determines whether the current graphics platform is a mobile, desktop, or another platform.
/// \ALL
/// \param[out] lpPlatForm The pointer to the retrieved graphics platform for the system. \n
///  0:  UNKNOWN \n
///  1:  DESKTOP \n
///  2:  MOBILE 	\n
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results 
int EXPOSED ADL_Graphics_Platform_Get(int *lpPlatForm);
// @}


#endif /* GRAPHICS_H_ */

