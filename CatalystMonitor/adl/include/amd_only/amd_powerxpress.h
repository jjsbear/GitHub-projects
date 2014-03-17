///
///  Copyright (c) 2008 - 2009 Advanced Micro Devices, Inc.

///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file amd_powerxpress.h
/// \brief Contains all AMD internal PowerExpress-related functions exposed by ADL for \ALL platforms.
///
/// This file contains all AMD internal PowerExpress-related functions exposed by ADL for \ALL platforms.
/// All functions found in this file can be used as a reference to ensure
/// the specified function pointers can be used by the appropriate runtime
/// dynamic library loaders. This header file is for AMD internal use only.

#ifndef AMD_POWERXPRESS_H_
#define AMD_POWERXPRESS_H_

#ifndef EXPOSED
#define EXPOSED
#endif /* EXPOSED */

///\brief Function to get default state of PowerXpress.
///
/// This prototype function retrieves the current and default PowerXpress state. This function should
/// only be used for fixed mode PowerXpress 3.0. This function supersedes \ref ADL_Display_PowerXpressActiveGPU_Get
///
/// \platform
/// \Linux
///\param[in] iAdapterIndex The ADL index handle of the desired adapter.
///\param[out] lpActiveGPU The pointer to the value storing the active GPU in PowerXpress: \ref ADL_DL_POWERXPRESS_GPU_INTEGRATED or
/// \ref ADL_DL_POWERXPRESS_GPU_DISCRETE
///\param[out] lpDeafultGPU The pointer to the value storing the default GPU in PowerXpress: \ref ADL_DL_POWERxPRESS_GPU_INTEGRATED or
/// \ref ADL_DL_POWERXPRESS_GPU_DISCRETE
///\return If the function succeeds, the return value is \ref ADL_OK. Otherwise the review value is ADL error code. \ref define_adl_results
int EXPOSED ADL_Display_PowerXpressActvieGPUR2_Get(int iAdapterIndex, int *lpActiveGPU, int *lpDefaultGPU);

///
/// \brief  This function gets the capability of current Extended Battery Mode.
///
/// This function gets the capability of Extended Battery Mode.
/// \platform 
/// \WIN7
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lpbSupprted The capability of Extended Battery Mode to be get.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_PowerXpress_ExtendedBatteryMode_Caps(int iAdapterIndex, int *lpbSupprted);


///
/// \brief  This function gets current Extended Battery Mode state.
///
/// This function gets current Extended Battery Mode state.
/// \platform 
/// \WIN7
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lpbEnable The current state of extended battery mode to be get.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_PowerXpress_ExtendedBatteryMode_Get(int iAdapterIndex, int *lpbEnable);


///
/// \brief  This function sets "Extended Battery Mode" state.
///
/// This function sets "Extended Battery Mode" state.
/// \platform 
/// \WIN7
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   bEnable The state of extended battery mode to be set.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_PowerXpress_ExtendedBatteryMode_Set(int iAdapterIndex, int bEnable);

#endif /* AMD_POWERXPRESS_H_ */
