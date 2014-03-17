///
///  Copyright (c) 2012 Advanced Micro Devices, Inc.
 
///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file amd_overdrive6.h
/// \brief Contains all Overdrive6-related functions exposed by ADL for \ALL platforms.
///
/// This file contains all Overdrive6-related functions exposed by ADL for \ALL platforms.
/// All functions found in this file can be used as a reference to ensure
/// the specified function pointers can be used by the appropriate runtime
/// dynamic library loaders.

#ifndef AMD_OVERDRIVE6_H_
#define AMD_OVERDRIVE6_H_

#include "adl_structures.h"

#ifndef EXPOSED
#define EXPOSED
#endif /* EXPOSED */

/// \addtogroup OVERDRIVE6
// @{

///
/// \brief Function to retrieve the current Overdrive capabilities.
/// 
/// This function retrieves the current Overdrive capabilities for a specified adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in,out] lpODCapabilities The pointer to the ADLOD6Capabilities structure storing the retrieved Overdrive parameters.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results 

int EXPOSED ADL_Overdrive6_Capabilities_Get(int iAdapterIndex, ADLOD6Capabilities *lpODCapabilities);

///
/// \brief Function to retrieve the current or default Overdrive performance levels.
/// 
/// This function retrieves the current or default Overdrive performance levels for a specified adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iStateType The state which for which performance levels will be retrieved.
/// \param[in,out] lpStateInfo Pointer to the retrieved performance level info.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results 

int EXPOSED ADL_Overdrive6_StateInfo_Get(int iAdapterIndex, int iStateType, ADLOD6StateInfo *lpStateInfo);

///
/// \brief Function to set the current Overdrive performance levels.
/// 
/// This function sets the current Overdrive performance levels for a specified adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iStateType The state which will have performace levels changed.
/// \param[in]  lpStateInfo Pointer to the performance level to be set.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results 

int EXPOSED ADL_Overdrive6_State_Set(int iAdapterIndex, int iStateType, ADLOD6StateInfo *lpStateInfo);

///
/// \brief Function to reset the current Overdrive performance levels to default.
/// 
/// This function resets the current Overdrive performance levels for a specified adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iStateType The state which will be reset to default performance level.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results 

int EXPOSED ADL_Overdrive6_State_Reset(int iAdapterIndex, int iStateType);

///
/// \brief Function to retrieve current power management-related activity.
/// 
/// This function retrieves current power management-related activity for a specified adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in,out] lpCurrentStatus The pointer to the ADLOD6CurrentStatus structure storing the retrieved power management activity information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results 

int EXPOSED ADL_Overdrive6_CurrentStatus_Get(int iAdapterIndex, ADLOD6CurrentStatus *lpCurrentStatus);

///
/// \brief Function to retrieve capabilities of the thermal controller.
/// 
/// This function retrieves thermal controller capabilities for a specified adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in,out] lpThermalControllerInfo The pointer to the ADLThermalControllerInfo structure storing the retrieved thermal device information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results 

int EXPOSED ADL_Overdrive6_ThermalController_Caps(int iAdapterIndex, ADLOD6ThermalControllerCaps *lpThermalControllerCaps);

///
/// \brief Function to retrieve thermal controller temperatures.
/// 
/// This function retrieves thermal controller temperature information for a specified adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in,out] lpTemperature The pointer to the retrieved temperature.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results 

int EXPOSED ADL_Overdrive6_Temperature_Get(int iAdapterIndex, int *lpTemperature);

///
/// \brief Function to retrieve the fan speed reported by the thermal controller.
/// 
/// This function retrieves the reported fan speed from a specified adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in,out] lpFanSpeedInfo The pointer to the ADLOD6FanSpeedInfo structure storing the retrieved fan speed.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results 

int EXPOSED ADL_Overdrive6_FanSpeed_Get(int iAdapterIndex, ADLOD6FanSpeedInfo *lpFanSpeedInfo);

///
/// \brief Function to set the fan speed.
/// 
/// This function sets the fan speed for a specified adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  lpFanSpeedValue The new fan speed value to be set.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results 

int EXPOSED ADL_Overdrive6_FanSpeed_Set(int iAdapterIndex, ADLOD6FanSpeedValue *lpFanSpeedValue);

///
/// \brief Function to set the fan speed to the default fan speed value.
/// 
/// This function sets the current fan speed for a specified adapter to the default fan speed.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results 

int EXPOSED ADL_Overdrive6_FanSpeed_Reset(int iAdapterIndex);

///  \brief Function to check for  PowerControl capabilities
///
/// The output parameter of the function lets the caller know about whether or not Power control
/// feature is supported.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpSupported The pointer to the  caps of adapter settings
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 

int EXPOSED ADL_Overdrive6_PowerControl_Caps (int iAdapterIndex, int *lpSupported);

///  \brief Function to get values  of  PowerControl information
/// 
/// The output parameter of the function lets the caller know about Power control adjust limit , step values and default value.
/// parameters.
/// \param[in]  iAdapterIndex The ADL index handle  of the desired adapter 
/// \param[in,out]  lpPowerControlInfo The pointer to the ADLOD6PowerControlInfo containing value of Power ///control 
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. 

int EXPOSED ADL_Overdrive6_PowerControlInfo_Get(int iAdapterIndex, ADLOD6PowerControlInfo *lpPowerControlInfo);

///  \brief Function to get values  of  PowerControl
///
/// The parameter of the function lets the caller to get new value of the Power control
/// \param[in]  iAdapterIndex The ADL index handle  of the desired adapter 
/// \param[out]  lpCurrentValue pointer to the current value of Power control 
/// \param[out]  lpDefaultValue pointer to the Default value of Power control 
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 

int EXPOSED ADL_Overdrive6_PowerControl_Get(int iAdapterIndex, int *lpCurrentValue, int *lpDefaultValue);

///  \brief Function to set values  of  PowerControl
///
/// The parameter of the function lets the caller to set new value to the Power control
/// \param[in]  iAdapterIndex The ADL index handle  of the desired adapter 
/// \param[in]  iValue New  value of Power control 
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 

int EXPOSED ADL_Overdrive6_PowerControl_Set(int iAdapterIndex, int iValue);

// @}

#endif /* AMD_OVERDRIVE6_H_ */
