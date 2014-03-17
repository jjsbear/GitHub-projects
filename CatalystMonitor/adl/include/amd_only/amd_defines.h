//
//  Copyright (c) 2008 - 2009 Advanced Micro Devices, Inc.
 
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
//  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file amd_defines.h
/// \brief Contains all definitions used by the internal AMD Driver Library interfaces for \ALL platforms.
///
/// This file contains all definitions used by internal AMD.
///

#ifndef AMD_DEFINES_H_
#define AMD_DEFINES_H_

#ifndef ADL_DEFINES_H_
#include "adl_defines.h"
#endif

/// \defgropup define_audiomappinginfo_get_policy
/// Used in ADL_Display_AudioMappingInfo_Get and ADL_ScreenPoint_AudioMappingInfo_Get
/// to indicate how the result AudioMappingInfo list is built.
/// @{
typedef enum _AUDIO_MAPPING_INFO_GET_POLICY
{
	/// Audio mapping that exactly match input criteria will be returned
	AUDIO_MAPPING_INFO_GET_POLICY_EXACT		= 0,
	/// Audio mapping that is nearest in distance will be returned
	AUDIO_MAPPING_INFO_GET_POLICY_NEAREST	= 1
} AUDIO_MAPPING_INFO_GET_POLICY;
/// @}


/// The bit mask identifies SLS map is active (this should be moved to group define_eyefinity_constants)
#define ADL_DISPLAY_SLSMAP_ACTIVE	0x00000001

// following definitions are used for ECC feature implementation
#define ECC_MODE_OFF 0
#define ECC_MODE_ON 2

// following definitions are used for SDI feature implementation
/// SDI off state
#define ADL_SDI_OFF 0
/// SDI on state
#define ADL_SDI_ON 1

#define ADL_ERR_APL_AREA_MISSING -13
#define ADL_ERR_APL_FORBIDDEN -14
#define ADL_ERR_APL_PROFILE_MISSING -15
#define ADL_ERR_APL_PROPERTY_MISSING -16
#define ADL_ERR_APL_APPLICATION_MISSING -17
#define ADL_ERR_APL_DUPLICATED_PROFILE -18
#define ADL_ERR_APL_UNEXPECTED_TYPE -19


/// \defgroup define_maximizewindowmode_values
/// Used by \ref ADL_MaximizeWindowMode_Get and \ref ADL_MaximizeWindowMode_Get functions
/// @{
/// Maximize windows to the display border in which they reside
#define ADL_MAXIMIZEWINDOWMODE_DISPLAY 0
/// Maximize windows to the entire desktop area (X Screen) even if multiple displays are configured on the desktop.
#define ADL_MAXIMIZEWINDOWMODE_DESKTOP 1
/// @}

/// \name Definitions for iFlag parameter in the \ref AdapterExtInfo structure
/// @{
/// Indicates that iMaxSurfaceWidth and iMaxSurfaceHeight contains valid information
#define ADL_EXTINFO_MAXSURFACE (1 << 0)
/// @}

/// \name Definitions for iVideoItemIndex parameter in the \ref ADLMMVideoSetData structure
/// @{
#define ADL_ADJUST_PROPERTY_Brightness				0
#define ADL_ADJUST_PROPERTY_Contrast				1
#define ADL_ADJUST_PROPERTY_Hue						2
#define ADL_ADJUST_PROPERTY_Saturation				3
#define ADL_ADJUST_PROPERTY_Gamma					4
#define ADL_ADJUST_PROPERTY_InvGamma				5
#define ADL_ADJUST_PROPERTY_PullDown				6
#define ADL_ADJUST_PROPERTY_TrueWhite				7
#define ADL_ADJUST_PROPERTY_Denoise					8
#define ADL_ADJUST_PROPERTY_Detail					9
#define ADL_ADJUST_PROPERTY_ColorVibrance			10
#define ADL_ADJUST_PROPERTY_Fleshtone				11
#define ADL_ADJUST_PROPERTY_DynamicContrast			12
#define ADL_ADJUST_PROPERTY_LRTC					13
#define ADL_ADJUST_PROPERTY_FrameRateConv			14
#define ADL_ADJUST_PROPERTY_BlueStretch				15
#define ADL_ADJUST_PROPERTY_StaticGamma				16
#define ADL_ADJUST_PROPERTY_DynamicRange			17
#define ADL_ADJUST_PROPERTY_OverridePA				18
#define ADL_ADJUST_PROPERTY_DemoMode				19
#define ADL_ADJUST_PROPERTY_Deblocking				20
#define ADL_ADJUST_PROPERTY_MosquitoNoiseRemoval	21
#define ADL_ADJUST_PROPERTY_InternetVideo			22
/// @}

/// \name Definitions for registry value types
/// Used by \ref ADL_Adapter_DriverSettings_Get and \ref ADL_Adapter_DriverSettings_Set functions
/// @{
#define ADL_REG_SZ                           0x00000001 // Unicode nul terminated string
#define ADL_REG_BINARY                       0x00000003 // Free form binary
#define ADL_REG_DWORD                        0x00000004 // 32-bit number
/// @}

/// \name Definitions for driver path options
/// Used by \ref ADL_Adapter_DriverSettings_Get and \ref ADL_Adapter_DriverSettings_Set functions
/// @{
#define ADL_REG_CURRENT_DEVICE               0x00000000
#define ADL_REG_DEVICE_FUNCTION_1            0x00000001
#define ADL_REG_DEVICE_FUNCTION_2            0x00000002
#define ADL_REG_ALL_MVPUDEVICES              0x00000004
#define ADL_REG_ALL_DEVICES                  0x0000FFFF
/// @}

/// Indicates that an actual value is not being passed in
#define ADL_UNSET -1

/// \defgroup define_overdrive6_capabilities 
/// These defines the capabilities supported by Overdrive 6. It is used by \ref ADL_Overdrive6_Capabilities_Get
/// @{
/// Indicate that core (engine) clock can be changed.
#define ADL_OD6_CAPABILITY_SCLK_CUSTOMIZATION               0x00000001
/// Indicate that memory clock can be changed.
#define ADL_OD6_CAPABILITY_MCLK_CUSTOMIZATION               0x00000002
/// Indicate that graphics activity reporting is supported.
#define ADL_OD6_CAPABILITY_GPU_ACTIVITY_MONITOR             0x00000004
/// @}

/// \defgroup define_overdrive6_supported_states 
/// These defines the power states supported by Overdrive 6. It is used by \ref ADL_Overdrive6_Capabilities_Get
/// @{
/// Indicate that overdrive is supported in the performance state (aka AC overdrive).
#define ADL_OD6_SUPPORTEDSTATE_PERFORMANCE                  0x00000001
/// Indicate that overdrive is supported in the power saving state (aka DC overdrive).
#define ADL_OD6_SUPPORTEDSTATE_POWER_SAVING                 0x00000002
/// @}

/// \defgroup define_overdrive6_getstateinfo 
/// These defines the power states to get information about. It is used by \ref ADL_Overdrive6_StateInfo_Get
/// @{
/// Get default AC clocks.
#define ADL_OD6_GETSTATEINFO_DEFAULT_PERFORMANCE            0x00000001
/// Get default DC clocks.
#define ADL_OD6_GETSTATEINFO_DEFAULT_POWER_SAVING           0x00000002
/// Get clocks for current state.
#define ADL_OD6_GETSTATEINFO_CURRENT                        0x00000003
/// Get AC overdrive clocks.
#define ADL_OD6_GETSTATEINFO_CUSTOM_PERFORMANCE             0x00000004
/// Get DC overdrive clocks.
#define ADL_OD6_GETSTATEINFO_CUSTOM_POWER_SAVING            0x00000005
/// @}

/// \defgroup define_overdrive6_setstate 
/// These defines which power state to set customized clocks on. It is used by \ref ADL_Overdrive6_State_Set
/// @{
/// Set AC overdrive clocks.
#define ADL_OD6_SETSTATE_PERFORMANCE                        0x00000001
/// Set DC overdrive clocks.
#define ADL_OD6_SETSTATE_POWER_SAVING                       0x00000002
/// @}

/// \defgroup define_overdrive6_thermalcontroller_caps 
/// These defines the capabilities of the thermal controller. It is used by \ref ADL_Overdrive6_ThermalController_Caps
/// @{
/// Thermal controller is supported.
#define ADL_OD6_TCCAPS_THERMAL_CONTROLLER                   0x00000001
/// Fan speed control is supported.
#define ADL_OD6_TCCAPS_FANSPEED_CONTROL                     0x00000002
/// Fan speed percentage can be read.
#define ADL_OD6_TCCAPS_FANSPEED_PERCENT_READ                0x00000100
/// Fan speed percentage can be set.
#define ADL_OD6_TCCAPS_FANSPEED_PERCENT_WRITE               0x00000200
/// Fan speed RPM can be read.
#define ADL_OD6_TCCAPS_FANSPEED_RPM_READ                    0x00000400
/// Fan speed RPM can be set.
#define ADL_OD6_TCCAPS_FANSPEED_RPM_WRITE                   0x00000800
/// @}

/// \defgroup define_overdrive6_fanspeed_type 
/// These defines the fan speed type being reported. It is used by \ref ADL_Overdrive6_FanSpeed_Get
/// @{
/// Fan speed reported in percentage.
#define ADL_OD6_FANSPEED_TYPE_PERCENT                       0x00000001
/// Fan speed reported in RPM.
#define ADL_OD6_FANSPEED_TYPE_RPM                           0x00000002
/// Fan speed is customized by user.
#define ADL_OD6_FANSPEED_USER_DEFINED                       0x00000100
/// @}

///////////////////////////////////////////////////////////////////////////
// ADL_ADAPTER_CAPS Definitions 
// for ADLAdapterCaps.iCapsMask and ADLAdapterCaps.iCapsValue
// (bit-vector)
///////////////////////////////////////////////////////////////////////////
/// \defgroup define_adapter_caps Adapter Caps Mask Values
// @{
#define ADL_ADAPTERCAPS_LDADISPLAY_SUPPORT 0x00000001 //LDA support(local display)
#define ADL_ADAPTERCAPS_SINGLEGPUSLS_SUPPORT 0x0002 //Single GPU SLS support
#define ADL_ADAPTERCAPS_MULTIPLEGPUSLS_SUPPORT 0x0004 //Multiple GPU SLS support

// @}
#endif /* AMD_DEFINES_H_ */
