///
///  Copyright (c) 2008 - 2009 Advanced Micro Devices, Inc.
 
///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file amd_displaysmanager.h
/// \brief Contains AMD Only Displays Manager-related functions exposed by ADL for \WIN platforms.
///
/// This file contains AMD Only Displays Manager function exposed by ADL for \WIN platforms.
/// All functions found in this file can be used as a reference to ensure
/// the specified function pointers can be used by the appropriate runtime
/// dynamic library loaders.

#ifndef AMD_DISPLAYSMANAGER_H_
#define AMD_DISPLAYSMANAGER_H_

#include "adl_structures.h"
#include "amd_structures.h"

#ifndef EXPOSED
#define EXPOSED
#endif /* EXPOSED */

///\addtogroup ADL_API
///\defgroup DISPLAYMNGR Displays Manager Related APIs
/// This group outlines the Displays Manager related APIs.

/// \addtogroup DISPLAYMNGR
// @{


/////////////////////////////////////////////////////////////////////////////
// 
// These APIs will be removed after their integration into the related new ones
//
/////////////////////////////////////////////////////////////////////////////

 ///
/// \brief Set SLS overlap offsets for each display index.
/// 
///
/// \platform
/// \WIN7
/// \param[in] iAdapterIndex                The ADL index of the desired adapter. This function does not support -1.
/// \param[in] iSLSMapIndex                 The SLS map index to apply bezel offset.
/// \param[in] iNumOverlappedModes          the no. of overlapped modes defined. Each such mode refers to a set of targets in the array of targets
/// \param[in] lpOverlappedModes            the list of overlapped modes defined
/// \param[in] iNumTargetOffsets            the no. of targets in the list of targets
/// \param[in] lpTargetOffsets              the list of target offsets for all the overlap modes defined
/// \param[in] SLSMap                       The display SLS map information. Refer to the \ref ADLSLSMap structure for more information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// 
/// \remarks Call ADL_Flush_Driver_Data() after to persist settings on reboot.
int EXPOSED ADL_Display_Overlap_Set (int iAdapterIndex, 
                                     int iSLSMapIndex, 
                                     int iNumOverlappedModes,
                                     LPADLSLSTargetOverlap lpOverlappedModes,
									 int iNumTargetOffsets,
									 LPADLSLSOffset lpTargetOffsets,
                                     ADLSLSMap SLSMap);




///
/// \brief Get SLS middle mode for specific adapter.
/// 
///
/// \platform
/// \WIN
/// \param[in]  iAdapterIndex               The ADL index of the desired adapter. This function does not support -1.
/// \param[in]  iSLSMapIndex                The SLS map index of the desired adapter.
/// \param[out] lpMiddleModeSupported		If SLS middle mode is supported or not. 1: supported; otherwise: not supported.
/// \param[out] lpMaxNumMiddleModeToSet		The maximum number of SLS middle modes is allowed to be set. 
/// \param[out] lpNumAvailableSLSMiddlemode	Pointer to a variable that will receive the number of elements in a Available SLS middle mode list.
/// \param[out] lppAvailableSLSMiddlemode	Pointer of a pointer to a variable that contains the Available SLS middle modes. the data type is \ref ADLSLSMode.
/// \param[out] lpNumCurrentSLSMiddleMode	Pointer to a variable that will receive the number of elements in a Current SLS middle mode list.
/// \param[out] lppCurrentSLSMiddleMode		Pointer of a pointer to a variable that contains the Current SLS middle modes. the data type is \ref ADLSLSMode.
/// \param[out] lpNumDefaultSLSMiddleMode	Pointer to a variable that will receive the number of elements in a Default SLS middle mode list.
/// \param[out] lppDefaultSLSMiddleMode		Pointer of a pointer to a variable that contains the Default SLS middle modes. the data type is \ref ADLSLSMode.
/// \param[in]  iOption						Specifies the layout type of SLS grid data. It is bit vector. There are two types of SLS layouts, relative to landscape (ref \ADL_DISPLAY_SLSGRID_CAP_OPTION_RELATIVETO_LANDSCAPE) and relative to current angle (ref \ADL_DISPLAY_SLSGRID_CAP_OPTION_RELATIVETO_CURRENTANGLE).
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// 
/// \remarks 1. Currently only support one current and one default middle mode.
///			 2. This API uses the memory allocation callback function provided by the user.
int EXPOSED	ADL_Display_SLSMiddleMode_Get (int iAdapterIndex, 
											int iSLSMapIndex,
											int* lpMiddleModeSupported,
											int* lpMaxNumMiddleModeToSet,
											int* lpNumAvailableSLSMiddleMode, 
											ADLSLSMode** lppAvailableSLSMiddleMode,
											int*lpNumCurrentSLSMiddleMode,
											ADLSLSMode ** lppCurrentSLSMiddleMode,
											int*lpNumDefaultSLSMiddleMode,
											ADLSLSMode ** lppDefaultSLSMiddleMode, 
											int iOption);

///
/// \brief Set SLS middle mode for specific adapter.
/// 
///
/// \platform
/// \WIN
/// \param[in] iAdapterIndex                The ADL index of the desired adapter. This function does not support -1.
/// \param[in] iSLSMapIndex                 The SLS map index of the desired adapter.
/// \param[in] iNumCurrentSLSMiddleMode		The number of elements in a Current SLS middle mode list to be set.
/// \param[in] lpCurrentSLSMiddleMode		Pointer of a variable that contains the Current SLS middle modes. the data type is \ref ADLSLSMode.
/// \param[in] iOption						Specifies the layout type of SLS grid data. It is bit vector. There are two types of SLS layouts, relative to landscape (ref \ADL_DISPLAY_SLSGRID_CAP_OPTION_RELATIVETO_LANDSCAPE) and relative to current angle (ref \ADL_DISPLAY_SLSGRID_CAP_OPTION_RELATIVETO_CURRENTANGLE).
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// 
/// \remarks	1. Currently only support one current/default middle mode.
///				2. Driver may returns CWDDE_OK_MODE_SET_NEEDED and CWDDE_ERR_BAD_MIDDLE_MODE.
///					- for return code CWDDE_OK_MODE_SET_NEEDED, ADL needs to do Mode Set in order to make newly set middle mode replacing the old one.
///					- for return code CWDDE_ERR_BAD_MIDDLE_MODE, ADL returns ADL_FAIL.
///
int EXPOSED	ADL_Display_SLSMiddleMode_Set (int iAdapterIndex, 
											int iSLSMapIndex,
											int iNumCurrentSLSMiddleMode,
											ADLSLSMode * lpCurrentSLSMiddleMode, 
											int iOption);
											
// @}
#endif /* AMD_DISPLAYSMANAGER_H_ */

