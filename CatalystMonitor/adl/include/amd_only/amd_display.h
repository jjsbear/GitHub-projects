///
///  Copyright (c) 2008 - 2009 Advanced Micro Devices, Inc.
 
///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file amd_display.h
/// \brief Contains all AMD internal display-related functions exposed by ADL for \ALL platforms.
///
/// This file contains all AMD internal display-related functions exposed by ADL for \ALL platforms.
/// All functions found in this file can be used as a reference to ensure
/// the specified function pointers can be used by the appropriate runtime
/// dynamic library loaders. This header file is for AMD internal use only.

#ifndef AMD_DISPLAY_H_
#define AMD_DISPLAY_H_

///
/// \brief ADL local interface. Function to retrieve the maximum resolution* and maximum refresh rate* information for a display.
///		* Note: These values may not be valid combinations in some applications.
///
/// This function retrieves the maximum horizontal and vertical resolution as well as the maximum refresh rate for a specified display and adapter.
/// \param[in]  iAdapterIndex 	The ADL index handle of the graphics adapter corresponding to the desired display.
/// \param[in]  iDisplayIndex 	The ADL index handle of the desired display.
/// \param[out] lpMaxHRes	The pointer to the maximum horizontal resolution for the specified display.
/// \param[out] lpMaxVRes	The pointer to the maximum vertical resolution for the specified display.
/// \param[out] lpMaxRefresh	The pointer to the maximum refresh rate for the specfied display.
/// \platform
/// \ALL
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Display_Limits_Get(int iAdapterIndex, int iDisplayIndex, int* lpMaxHRes, int* lpMaxVRes, int* lpMaxRefresh);

///
///\brief Function to retrieve display mode timing override information.
/// 
/// This function retrieves display mode timing override information for a specified display.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in]   lpModeIn The pointer to the structure storing the desired display mode.
/// \param[out]  lpModeInfoOut The pointer to the structure storing the retrieved display mode information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Display_ModeTimingOverrideInfo_Get(int iAdapterIndex, int iDisplayIndex, ADL_DL_DISPLAY_MODE *lpModeIn, ADL_DL_DISPLAYMODEINFO *lpModeInfoOut);

///
///\brief Function to retireve the vector of a display.
/// 
/// This function retrieves the vector of a specified display.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iType The type of display.
/// \param[out]  lpVector The pointer to the retrieved vector of the specified display.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Display_Vector_Get(int iAdapterIndex, int iType, int *lpVector);

///
///\brief Function to get index value of a display.
/// 
/// This function retrieves index value of a specified display.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[out]  lpType The pointer to the display type.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Display_EnumDisplays_Get(int iAdapterIndex, int iDisplayIndex, int * lpType);

///
///\brief Function to override the EDID data for a display
/// 
/// This function overrides the EDID data for a specified display
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure.
/// \param[in,out]  lpEDIDData The pointer to the ADLDisplayEDIDData structure storing the override EDID data.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks This API is in Prototype stage. Do not use for shipping products!
int EXPOSED ADL_Display_EdidData_Set(int iAdapterIndex, int iDisplayIndex, ADLDisplayEDIDData *lpEDIDData);

///
///\brief Function to get audio mapping info associated with a display
/// 
/// This function retrieves audio mapping info associated with a display
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iDisplayIndex The desired display index. It can be retrieved from the ADLDisplayInfo data structure. -1 means retrieve all displays that belongs to the adapter
/// \param[in]   policy Indicate how the result AudioMappingInfo list is built. \ref define_audiomappinginfo_get_policy
/// \param[out]  lpNumAudioMappingInfos The pointer to the number of AduioMappingInfos returned
/// \param[out]  *lppAudioMappingInfos The pointer to an empty memory buffer(NULL).  This function will use the callback to allocate the appropriate buffer size.  This buffer will contain a list of AudioMappingInfos. If no AudioMappingInfos were found, this memory buffer will remain empty, or NULL.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks If explicit AdapterIndex and DisplayIndex are passed in (not -1), and the specific display is disabled, and the policy is AUDIO_MAPPING_INFO_GET_POLICY_NEAREST, the AudioMappingInfo for that display will be returned regardless whether the display supports audio or not.
int EXPOSED ADL_Display_AudioMappingInfo_Get ( int iAdapterIndex,
											   int iDisplayIndex,
											   AUDIO_MAPPING_INFO_GET_POLICY policy,
											   int* lpNumAudioMappingInfos,
											   AudioEndPointAssociationInfo** lppAudioMappingInfos);


///
///\brief Function to get target timing associated with a display
/// 
/// This function retrieves target timing info associated with a display
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   displayID  The structure stores the display target information.
/// \param[out]  *lpDisplayTiming The pointer to an structure used to retrieve display timing
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results											   
int EXPOSED ADL_Display_TargetTiming_Get (int iAdapterIndex, ADLDisplayID displayID, ADLDisplayTargetTiming* lpDisplayTiming);
                                         											   

///
///\brief Function to get audio mapping info associated with a given screen coordiante
/// 
/// This function retrieves audio mapping info associated with a given screen coordiante
/// \platform
/// \ALL
/// \param[in]   iLeft The x screen coordinate with respect to global system screen space (left top corner of primary desktop is 0,0).
/// \param[in]   iTop The y screen coordinate with respect to global system screen space (left top corner of primary desktop is 0,0).
/// \param[in]   policy Indicate how the result AudioMappingInfo list is built. \ref define_audiomappinginfo_get_policy
/// \param[out]  lpNumAudioMappingInfos The pointer to the number of AduioMappingInfos returned
/// \param[out]  *lppAudioMappingInfos The pointer to an empty memory buffer(NULL).  This function will use the callback to allocate the appropriate buffer size.  This buffer will contain a list of AudioMappingInfos. If no AudioMappingInfos were found, this memory buffer will remain empty, or NULL.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_ScreenPoint_AudioMappingInfo_Get ( int iLeft,
												   int iTop,
												   AUDIO_MAPPING_INFO_GET_POLICY policy,
												   int* lpNumAudioMappingInfos,
												   AudioEndPointAssociationInfo** lppAudioMappingInfos);


///
///\brief  AMD internall call only .Function to set scaling configuration
/// 
/// This function sets an enhenced scaling configuration
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iControllerIndex 
/// \param[in]   *pScaling The pointer to an structure which describes the requested scaling configuration
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results											   
int EXPOSED ADL_DisplayScaling_Set ( int iAdapterIndex, int iControllerIndex, const ADLMMDisplayScaling* pScaling);

#endif /* AMD_DISPLAY_H_ */
