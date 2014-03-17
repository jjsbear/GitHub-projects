///
///  Copyright (c) 2008 - 2009 Advanced Micro Devices, Inc.
 
///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file oem_display.h
/// \brief Contains all customer display-related functions exposed by ADL for \ALL platforms.
///
/// This file contains all OEM or other customer display-related functions exposed by ADL for \ALL platforms.
/// All functions found in this file can be used as a reference to ensure
/// the specified function pointers can be used by the appropriate runtime
/// dynamic library loaders. This header file not for public release.

#ifndef OEM_DISPLAY_H_
#define OEM_DISPLAY_H_

#include "oem_structures.h"

/// \addtogroup DISPLAY
// @{
///\brief Function to retrieve the overlay OEM matrix.
/// 
/// This function retrieves the overlay OEM matrix.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index, which can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   iMatrixType The value storing the matrix type.
/// \param[out]  lpGamutMatrix The pointer to structure storing the retrieved overlay OEM matrix.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Display_GamutMapping_Get(int iAdapterIndex, int iDisplayIndex, int iMatrixType, ADLDisplayGamutMatrix *lpGamutMatrix);

///
///\brief Function to set the overlay OEM matrix.
/// 
/// This function sets the overlay OEM matrix.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index, which can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   iMatrixType The value storing the matrix type
/// \param[in]  lpGamutMatrix The pointer to the structure used to set overlay OEM matrix.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Display_GamutMapping_Set(int iAdapterIndex, int iDisplayIndex, int iMatrixType, ADLDisplayGamutMatrix *lpGamutMatrix);

///
/// \brief Function to reset the overlay OEM matrix.
/// 
/// This function resets the overlay OEM matrix.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index, which can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   iMatrixType The matrix type.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Display_GamutMapping_Reset(int iAdapterIndex, int iDisplayIndex, int iMatrixType);

///
/// \brief Function to read/write native AUX channel of DP display 
///
/// This function reads or writes native AUX channel of DP display
/// \platform 
/// \ALL 
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in, out] lpData The pointer to the ADLDisplayNativeAUXChannelData strurcture.
///                 Defines how to set/get the data to/from the native aux channel of DP display.
///                 If the function return ADL_OK, check ADLDisplayNativeAUXChannelData.iAuxStatus for result status. 
///                 The value can be any ADL_ERR_AUX_FAILED_xxxx. Only \ref ADL_DISPLAY_AUX_STATUS_SUCESSFUL means the command is successful.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. 
int EXPOSED ADL_Display_NativeAUXChannel_Access(int iAdapterIndex, int iDisplayIndex, ADLDisplayNativeAUXChannelData* lpData);

///
/// \brief Function to get the Pixel Clock Capabilities 
///
/// This function reads the Pixel Clock Capabilities
/// \platform 
/// \ALL 
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in, out] lpPixelClockCaps The pointer to the ADLPixelClockCaps strurcture.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. 
int EXPOSED ADL_Display_PixelClockCaps_Get(int iAdapterIndex, int iDisplayIndex, ADLPixelClockCaps * lpPixelClockCaps);

///
/// \brief Function to get the Current Pixel Clocks
///
/// This function reads the Current Pixel Clocks
/// \platform 
/// \ALL 
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in, out] lpCurrentPixelClock The pointer to the ADLCurrentPixelClock strurcture.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. 
int EXPOSED ADL_Display_CurrentPixelClock_Get(int iAdapterIndex, int iDisplayIndex, ADLCurrentPixelClock * lpCurrentPixelClock);

///
/// \brief Function to set the Pixel Clock Allowable Range 
///
/// This function writes the Pixel Clock Allowable Range 
/// \platform 
/// \ALL 
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in, out] lpPixelClockRange The pointer to the ADLPixelClockRange strurcture.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.
/// 
/// \remarks Call ADL_Flush_Driver_Data() after to persist settings on reboot.
int EXPOSED ADL_Display_PixelClockAllowableRange_Set(int iAdapterIndex, int iDisplayIndex, ADLPixelClockRange * lpPixelClockRange);

///
/// \brief Function to get the brightness information of monitor.
///
/// This function gets the brightness information of monitor.
/// \platform 
/// \ALL 
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[out] piCurrent The pointer to the data to get the current brightness of monitor.
/// \param[out] piMax The pointer to the data to get the max brightness of monitor.
/// \param[out] piMax The pointer to the data to get the min brightness of monitor.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.
int EXPOSED ADL_Display_BackLight_Get(int iAdapterIndex, int iDisplayIndex, int *piCurrent, int *piMax, int*piMin);

///
/// \brief Function to Set the brightness information of monitor.
///
/// This function sets the brightness information of monitor.
/// \platform 
/// \ALL 
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[int] iValue The data to set the brightness of monitor.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.
int EXPOSED ADL_Display_BackLight_Set(int iAdapterIndex, int iDisplayIndex, int iValue);

///
/// \brief Function to write and read large I2C packets up to \ref ADL_DL_I2C_MAXLARGEPAYLOADSIZE
/// 
/// This function writes and reads I2C.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in,out]  plI2C A pointer to the ADLI2CLargePayload structure.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Display_WriteAndReadI2CLargePayload(int iAdapterIndex, ADLI2CLargePayload *plI2C);


///
///\brief Function to set the display monitor power state.
/// 
/// This function sets the display monitor power state on given adapter.
/// \platform
/// \VISTAWIN7  
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   nState The desired monitor power state to be set.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks
/// -# This API is only expected to be called when the Monitor is already be driven by the adapter (adapter attaches to desktop)
///	   - If the Adapter (referred by iAdapterIndex) is active (attached to a desktop), but Monitor is currently NOT driven by the GPU, this API will not do anything to the monitor, and API may still return \ref ADL_OK
///	   - If the Adapter (referred by iAdapterIndex) is NOT active (does not attach to a desktop), API may fail and return \ref ADL_ERR
/// \n\n
/// -# Power ON/OFF the monitor while the Monitor is already at ON/OFF state
///    - If Monitor is currently ON, and client calls this API to try Power-ON the monitor, this API will return \ref ADL_OK. User may experience a flash on some monitor because of Display Engine may be power-cycle-toggled. 
///    - If Monitor is currently OFF, and client calls this API to try Power-OFF the monitor, this API will return \ref ADL_OK
/// \n\n
/// -# Power ON the monitor while the Monitor is in time-out (power-saving) state
///    - If Monitor is currently time-out (powered-off by the OS), client calls this API to Power-ON the monitor, driver will Power-ON the monitor, and API will return \ref ADL_OK



int EXPOSED ADL_Display_MonitorPowerState_Set ( int iAdapterIndex, int iDisplayIndex, ADL_Display_MonitorPowerState nState);

// @}


///\ingroup DISPLAYAPI
///\defgroup SPLITAPIS Split Display APIs
/// This group outlines the Split Display related APIs.
 
/// \addtogroup SPLITAPIS
///
// @{

#if defined (_WIN32) || defined(_WIN64)



///
/// \brief Function to retrieve the current Split Display setting for the input display. (Win7).
/// 
/// This function retrieves the Split Display capabilities and settings base on the input display ID.
/// \platform
/// \Win7
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in] displayID The display IDs. Refer to the ADLDisplayID structure for more information. 
/// \param[out] lpSplitDisplayCaps The pointer to the retrieved Split Display capabilities. Refer to the ADLSplitDisplayCaps structure for more information. 
/// \param[out] lpCurrentState The pointer to the retrieved the current Split Display state which is enable or disable. Refer to the ADLSplitDisplayState structure for more information. 
/// \param[out] lpCurrentMode The pointer to the retrieved the current Split Display mode which is 4:3 Left or 1:1. Refer to the ADLSplitDisplayMode structure for more information. 
/// \param[out] lpCurrentType The pointer to the retrieved the current Split Display type. Refer to the ADLSplitDisplayType structure for more information. 
/// \param[out] lpNumSiblingType The pointer to the retrieved the the number of sibling type usually one.
/// \param[out] lppSiblingType The pointer to the pointer to the retrieved array of sibling types. Refer to the ADLSplitDisplayType structure for more information. 
/// \param[out] lpDefaultState The pointer to the retrieved the defalut Split Display state which is enable or disable. Refer to the ADLSplitDisplayState structure for more information. 
/// \param[out] lpDefaultMode The pointer to the retrieved the default Split Display mode which is 4:3 Left or 1:1. Refer to the ADLSplitDisplayMode structure for more information. 
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks	This API is in Prototype stage. Do not use for shipping products!
///				Application must free the memory after calling this function.

int EXPOSED ADL_Display_SplitDisplay_Get (int iAdapterIndex, 
											ADLDisplayID displayID, 
											ADLSplitDisplayCaps* lpSplitDisplayCaps, 
											ADLSplitDisplayState* lpCurrentState, 
											ADLSplitDisplayMode* lpCurrentMode,
											ADLSplitDisplayType* lpCurrentType,	
											int* lpNumSiblingType, 
											ADLSplitDisplayType** lppSiblingType, 
											ADLSplitDisplayState* lpDefaultState, 
											ADLSplitDisplayMode* lpDefaultMode );


///
/// \brief Function to set the current Split Display settings for the input display. (Win7).
/// 
/// This function allows user to enable or disable Split Display. In addition, it allows user to set the Split Display mode.
/// Make sure to disable related extended/cloned display devices before enabling Split display mode.
/// \platform
/// \Win7
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in] displayID The display IDs. Refer to the ADLDisplayID structure for more information. 
/// \param[in] currentState The current Split Display state which is enable or disable to be set. Refer to the ADLSplitDisplayState structure for more information. 
/// \param[in] currentMode The current Split Display mode which is 4:3 Left or 1:1 to be set. Refer to the ADLSplitDisplayMode structure for more information. 
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks	This API is in Prototype stage. Do not use for shipping products!
int EXPOSED ADL_Display_SplitDisplay_Set (int iAdapterIndex, 
											ADLDisplayID displayID, 
											ADLSplitDisplayState currentState,
											ADLSplitDisplayMode currentMode);




///
/// \brief Function to check the current desktop configuration if it is valid for Split Display. (Win7).
/// 
/// This function checks the current desktop configuration to see it is valid for Split Display. 
/// If it is not a valid desktop configuration, this function will restore the desktop configuration.
/// \platform
/// \Win7
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in] displayID The display IDs. Refer to the ADLDisplayID structure for more information. 
/// \param[out] lpResultMask The result mask value. Refer to ADL_DISPLAY_SPLITDISPLAY_DESKTOPCONFIGURATION_XXX.
/// \param[out] lpResultValue Result after the Restore Desktop Configuration. Refer to ADL_DISPLAY_SPLITDISPLAY_DESKTOPCONFIGURATION_XXX.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks	This API is in Prototype stage. Do not use for shipping products!
int EXPOSED ADL_Display_SplitDisplay_RestoreDesktopConfiguration (int iAdapterIndex, 
																	ADLDisplayID displayID, 
																	int* lpResultMask, 
																	int* lpResultValue );



///
/// \brief Function to check the adapter if it supports Split Display. (Win7).
/// 
/// This function checks the adapter if it supports Split Display. 
/// If it doesn't support split display, the caller can avoid further actions (i.e. checking each display for this adapter).
/// \platform
/// \Win7
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpResultMask The result mask value. Refer to ADL_DISPLAY_SPLITDISPLAY_CAPS_SUPPORTED.
/// \param[out] lpResultValue Result. Refer to ADL_DISPLAY_SPLITDISPLAY_CAPS_SUPPORTED.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks	This API is in Prototype stage. Do not use for shipping products!
int EXPOSED ADL_Display_SplitDisplay_Caps (int iAdapterIndex, 
											int* lpResultMask, 
											int* lpResultValue );

											
											
///
///\brief Function to get the packet information. \b HDMI \b only
/// 
/// This function retrieves the packet information.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[out]  lpInfoPacket The pointer to structure storing the retrieved the packet information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Display_InfoPacket_Get(int iAdapterIndex, int iDisplayIndex, ADLDisplayDataPacket *lpInfoPacket);


///
///\brief Function to set the packet information. \b HDMI \b only
/// 
/// This function sets the packet information.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   lpInfoPacket The pointer to the structure that sets the packet information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Display_InfoPacket_Set(int iAdapterIndex, int iDisplayIndex, ADLDisplayDataPacket * lpInfoPacket);

#endif
 

// @}


/// \addtogroup COLOR
///
// @{

///\brief Function to get the current ADLGamutInfo setting for the display. 
/// This function get the ADLGamutInfo setting for a specified display.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  gamut         The gamut reference - whether it is related to graphics or video, source or destination
/// \param[out]  ADLGamutInfo  driver supplies the mask of supported gamut spaces and white points, driver supports this feature from NI ASIC.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Display_Gamut_Caps( int iAdapterIndex, int iDisplayIndex, ADLGamutReference gamut,  ADLGamutInfo *lpCap);

///\brief Function to get the current ADLGamutData setting for the display. 
/// This function get the ADLGamutData setting for a specified display.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  gamut       . The gamut reference - whether it is related to graphics or video, source or destination
/// \param[out]  ADLGamutData  driver supplies the currently used gamut, driver supports this feature from NI ASIC.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Display_Gamut_Get( int iAdapterIndex, int iDisplayIndex, ADLGamutReference gamut,  ADLGamutData *lpSource );

///\brief Function to set the current ADLGamutData setting for the display. 
/// This function sets the ADLGamutData setting for a specified display.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  gamut         The gamut reference - whether it is related to graphics or video, source or destination
/// \param[in ]  ADLGamutData  to be set, the method sets the new gamut or saves the requested gamut if the current destination if gamut from EDID.
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Display_Gamut_Set( int iAdapterIndex, int iDisplayIndex, ADLGamutReference gamut,  const ADLGamutData *lpSource );

/// DEPRECATED - Replaced with ADL_Display_RegammaR1_Set
/// \brief 
/// \Function to set requested re gamma coefficients setting for the display. 
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  lpRegamma coefficients to be used to build the display gamma curve
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Display_ReGammaCoefficients_Set( int iAdapterIndex, int iDisplayIndex, const ADLReGammaCoefficients *lpRegamma );

/// DEPRECATED - Replaced with ADL_Display_RegammaR1_Get
/// \brief 
/// \Function to get the re gamma coefficients setting for the display. 
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  lpRegamma coefficients currently in use to build ideal re gamma curve
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Display_ReGammaCoefficients_Get( int iAdapterIndex, int iDisplayIndex,  ADLReGammaCoefficients *lpRegamma );


///\brief Function to set given re gamma  for the display. It could be a display gamma or coefficients
/// This function sets the ADL_Display_Regamma_Set setting for a specified display.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  lpRegamma it has  2 options :  coefficients to build the display gamma curve or direct display gamma curve
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Display_Regamma_Set( int iAdapterIndex, int iDisplayIndex, const ADLRegamma *lpRegamma );

///\brief Function to get the current re gamma for the given display
/// This function gets the ADL_Display_Regamma_Get setting for a specified display.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  lpRegamma used by driver. It has  2 options :  coefficients to build the display gamma curve or direct display gamma curve
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Display_Regamma_Get( int iAdapterIndex, int iDisplayIndex,  ADLRegamma *lpRegamma );

///\brief 
/// This function sets the given re-gamma for the display. The gamma may come direct from the panel's information or from set coefficients that will build an ideal gamma curve. 
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[in ]  lpRegammaEx The gamma curve; where the curve is either coming direct from display information or will be built by coefficients. 
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Display_RegammaR1_Set( int iAdapterIndex, int iDisplayIndex, const ADLRegammaEx *lpRegammaEx );

///\brief 
/// This function get the current regamma setting for the given display.  The value of this gamma may have originally been set from values direct from the display or coefficients that built the original curve.
/// \platform
/// \ALL
/// \param[in ]  iAdapterIndex The index of the desired adapter.
/// \param[in ]  iDisplayIndex The index of the desired display.
/// \param[out]  lpRegammaEx The gamma curve; where the curve either came directly from the display or built by coefficients. 
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Display_RegammaR1_Get( int iAdapterIndex, int iDisplayIndex,  ADLRegammaEx *lpRegammaEx );




 
   
  // @}


#endif /* OEM_DISPLAY_H_ */
