///  Copyright (c) 2008 - 2011 Advanced Micro Devices, Inc.

///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file amd_adapter.h
/// \brief Contains all AMD internal adapter-related functions exposed by ADL for \ALL platforms.
///
/// This file contains all AMD internal adapter-related functions exposed by ADL for \ALL platforms.
/// All functions in this file can be used as a reference to ensure
/// the specified function pointers can be used by the appropriate runtime
/// dynamic library loaders. This header file is for AMD internal use only.

#ifndef AMD_ADAPTER_H_
#define AMD_ADAPTER_H_

#ifndef EXPOSED
#define EXPOSED
#endif /* EXPOSED */

///\addtogroup ADAPTER
// @{

/// \brief ADL local interface. Function to retrieve the supported aspects list.
/// 
/// This function retrieves the list of supported aspects for a specified adapter.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lpAspects The pointer to the buffer storing the list of aspects supported for the specified adapter.
/// \param[in] iSize The size of the lpAspects buffer.
/// \platform 
/// \ALL
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
int EXPOSED ADL_Adapter_Aspects_Get( int iAdapterIndex, char* lpAspects, int iSize );

///
/// \brief ADL local interface. Function to query a registry value by driver.
/// 
/// This function query a registry value by driver for a specified adapter.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  szDriverSettings The name of registry value to be got.
/// \param[in]  iDriverPathOption The option of the driver path. See \ref Definitions for driver path options for values.
/// \param[in]  iType The type of registry value to be got. See \ref Definitions for registry value types for values
/// \param[in]  iSize The size of registry value to be got.
/// \param[out] lpSetting The pointer to registry value to be got.
/// \platform 
/// \WIN
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
int EXPOSED ADL_Adapter_DriverSettings_Get( int iAdapterIndex, char *szDriverSettings, int iDriverPathOption, int iType, int iSize, char *lpSetting);

///
/// \brief ADL local interface. Function to set a registry value by driver.
/// 
/// This function set a registry value by driver for a specified adapter.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  szDriverSettings The name of registry value to be set.
/// \param[in]  iDriverPathOption The option of the driver path. See \ref Definitions for driver path options for values.
/// \param[in]  iType The type of registry value to be got. See \ref Definitions for registry value types for values
/// \param[in]  iSize The size of registry value to be set.
/// \param[out] lpSetting The pointer to registry value to be set.
/// \platform 
/// \WIN
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
int EXPOSED ADL_Adapter_DriverSettings_Set( int iAdapterIndex, char *szDriverSettings, int iDriverPathOption, int iType, int iSize, char *lpSetting);

///
/// \brief ADL local interface. Function to query a integer registry value set by driver.
/// 
/// This function queries a driver registry integer value for a specified adapter by specifying the subkey path and key name.
/// \param[in]  iAdapterIndex		The ADL index handle of the desired adapter.
/// \param[in]  iDriverPathOption	The option of the driver path. 0: Current; 1: function1; 2: function2; 0xFFFF for all device.
/// \param[in]  szSubKey			The path of registry subkey to be accessed. This is a null terminated string and the parameter can be NULL.
/// \param[in]  szKeyName			The name of registry value to be got. This is a null terminated string.
/// \param[out] lpKeyValue			The pointer to registry value to be got.
/// \platform 
/// \WIN
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
int EXPOSED ADL_Adapter_RegValueInt_Get( int iAdapterIndex, int iDriverPathOption, char* szSubKey, char *szKeyName, int *lpKeyValue);

///
/// \brief ADL local interface. Function to set a driver registry integer value.
/// 
/// This function sets a driver registry integer value for a specified adapter by specifying the subkey path and key name.
/// \param[in]  iAdapterIndex		The ADL index handle of the desired adapter.
/// \param[in]  iDriverPathOption	The option of the driver path. 0: Current; 1: function1; 2: function2; 0xFFFF for all device.
/// \param[in]  szSubKey			The path of registry subkey to be accessed. This is a null terminated string and the parameter can be NULL.
/// \param[in]  szKeyName			The name of registry value to be set. This is a null terminated string.
/// \param[in]  iKeyValue			The integer registry value to be set.
/// \platform 
/// \WIN
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
int EXPOSED ADL_Adapter_RegValueInt_Set( int iAdapterIndex, int iDriverPathOption, char *szSubKey, char *szKeyName, int iKeyValue);

///
/// \brief ADL local interface. Function to query a string registry value set by driver.
/// 
/// This function queries a driver registry string value for a specified adapter by specifying the subkey path and key name.
/// \param[in]  iAdapterIndex		The ADL index handle of the desired adapter.
/// \param[in]  iDriverPathOption	The option of the driver path. 0: Current; 1: function1; 2: function2; 0xFFFF for all device.
/// \param[in]  szSubKey			The path of registry sub key to be accessed. This is a null terminated string and the parameter can be NULL.
/// \param[in]  szKeyName			The name of registry value to be got. This is a null terminated string.
/// \param[in]  iSize				The size of registry value to be got.
/// \param[out] lpKeyValue			The pointer to registry value to be got.
/// \platform 
/// \WIN
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
int EXPOSED ADL_Adapter_RegValueString_Get( int iAdapterIndex, int iDriverPathOption, char* szSubKey, char *szKeyName, int iSize, char *lpKeyValue);

///
/// \brief ADL local interface. Function to set a driver registry string value.
/// 
/// This function sets a driver registry string value for a specified adapter by specifying the subkey path and key name.
/// \param[in]  iAdapterIndex		The ADL index handle of the desired adapter.
/// \param[in]  iDriverPathOption	The option of the driver path. 0: Current; 1: function1; 2: function2; 0xFFFF for all device.
/// \param[in]  szSubKey			The path of registry sub key to be accessed. This is a null terminated string and the parameter can be NULL.
/// \param[in]  szKeyName			The name of registry value to be set. This is a null terminated string.
/// \param[in]  iSize				The size of registry value to be set.
/// \param[in]	lpKeyValue			The pointer to registry value to be set.
/// \platform 
/// \WIN
/// \return If the function valid, the return value is 1. Otherwise it is 0. 
int EXPOSED ADL_Adapter_RegValueString_Set( int iAdapterIndex, int iDriverPathOption, char* szSubKey, char *szKeyName, int iSize, char *lpKeyValue);

/// \brief Function to get MM video theater mode info
///
/// The function is used to get multi-media video theater mode information.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[out] lpOverlayDisplayMode	The pointer to the overlay display mode.
/// \param[out]	lpSavedSettings			The pointer to the saved settings of the related mode.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_VideoTheaterModeInfo_Get( int iAdapterIndex, int* lpOverlayDisplayMode, int* lpSavedSettings);

/// \brief Function to set MM video theater mode info
///
/// The function is used to set multi-media video theater mode information.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[in]	iOverlayDisplayMode		The overlay display mode to be set.
/// \param[in]	iSavedSettings			The saved settings of the related mode to be set.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_VideoTheaterModeInfo_Set( int iAdapterIndex, int iOverlayDisplayMode, int iSavedSettings);

/// \brief Function to get Black and White level
///
/// The function is used to get Black and White level of display color.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[out] lpCONTROLLERGAMMA  	    The pointer to the retrieved CONTROLLERGAMMA data structure.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_Gamma_Get( int iAdapterIndex, ADLCONTROLLERGAMMA16* lpCONTROLLERGAMMA16 );

/// \brief Function to set Black and White level
///
/// The function is used to set Black and White level of display color.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[in]	lpCONTROLLERGAMMA		The pointer to the CONTROLLERGAMMA data structure to be set.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_Gamma_Set( int iAdapterIndex, ADLCONTROLLERGAMMA16* lpCONTROLLERGAMMA16 );

/// \brief Function to check if Black and White level functionality is supported
///
/// The function is used to check if Black and White level functionality is supported.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex			        The ADL index handle of the desired adapter.
/// \param[out] lpBlackAndWhiteLevelSupport  	The pointer to the BlackAndWhite support level. 1 for supported and 0 for unsupported
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_BlackAndWhiteLevelSupport_Get( int iAdapterIndex, int* lpBlackAndWhiteLevelSupport);

/// \brief Function to get Black and White level
///
/// The function is used to get Black and White level of display color.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[out] lpBlackAndWhiteLevel  	The pointer to the BlackAndWhite level. 1 for limited range and 0 for full range
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_BlackAndWhiteLevel_Get( int iAdapterIndex, int* lpBlackAndWhiteLevel);

/// \brief Function to set Black and White level
///
/// The function is used to set Black and White level of display color.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[in]	iBlackAndWhiteLevel		The BlackAndWhite level to be set.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_BlackAndWhiteLevel_Set( int iAdapterIndex, int iBlackAndWhiteLevel);

///
/// \brief ADL local interface. Function to retrieve ASIC information.
/// 
/// This function retrieves the ASIC information for a specified adapter.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpAsicInfo The pointer to the structure storing the retrieved ASIC information.
/// \platform 
/// \LNX
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_ASICInfo_Get( int iAdapterIndex, ADLASICInfo* lpAsicInfo );

///
/// \brief ADL local interface. Function to retrieve chipset information.
/// 
/// This function retrieves the chipset information for a specified adapter.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lpChipSetInfo The pointer to the structure storing the retrieved chipset information.
/// \platform 
/// \ALL
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_ChipSetInfo_Get( int iAdapterIndex, ADLChipSetInfo * lpChipSetInfo );

///
/// \brief ADL local interface. Function to retrieve software information.
/// 
/// This function retrieves the software information for a specified adapter.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lpSWInfo The pointer to the structure storing the retrieved software information.
/// \platform 
/// \LNX
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_SWInfo_Get( int iAdapterIndex, ADLSWInfo * lpSWInfo );

// @}

/// \addtogroup OVERDRIVE5
// @{

///
/// \brief Function to retrieve current power management capabilities
/// 
/// This function retrieves current power management capabilities for a specified adapter.
/// \platform
/// \ALL
/// \param[in]  iSupported The pointer to an int variable which indicates if Overdrive feature is supported ( \ref ADL_TRUE : supported, \ref ADL_FALSE : not supported)
/// \param[in]  iEnabled The pointer to an int variable which indicates if Overdrive feature is enabled ( \ref ADL_TRUE : enabled, \ref ADL_FALSE : disabled)
/// \param[in]  iEnabled The pointer to an int variable receiving the Overdrive feature version.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results. If Overdrive feature is not supported the return code is \ref ADL_ERR_NOT_SUPPORTED 
///
/// \remarks Call this API prior to calling any other Overdrive APIs to determine if this feature is supported and enabled.
int EXPOSED ADL_Overdrive_Caps (int iAdapterIndex, int * iSupported, int * iEnabled, int * iVersion );

// @}


///
/// \brief Function to retrieve memory information from the adapter. Version 2
///
/// This function retrieves the memory information for a specified graphics adapter.
/// \platform
/// \LNX
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpMemoryInfo2 The pointer to the structure storing the retrieved memory information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_MemoryInfo2_Get(int iAdapterIndex, ADLMemoryInfo2 *lpMemoryInfo2);


///
/// \brief Function to re-enumerate adapter modes. 
///
/// This function re-enumerates adapter modes
/// \platform
/// \Win7
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks For Win7 only. This internal AMD API is used to test driver's SLS middle mode feature.
int EXPOSED ADL_Adapter_Modes_ReEnumerate();

///
/// \brief Retrieves additional adapter information
///
/// This function retreives extended adapter information for a particular adapter
/// \platform
/// \LNX
/// \param[in] iAdapterIndex The ADL index of the desired adapter to query the extended information
/// \param[out] lpExtInfo A pointer to an empty memory buffer(NULL). This function will allocate callback function to allocate the appropriate memory size. This buffer will contain the reteieved extended adapter information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADLerror code. \ref define_adl_results
int EXPOSED ADL_Adapter_ExtInfo_Get(int iAdapterIndex, LPAdapterExtInfo *lppExtInfo);

///
/// \brief Function to get current CrossfireX settings for both QUAD and Software crossfire.
///
/// On QUAD Crossfire systems this function is used to retrieve the current information about a particular CrossfireX combination.  A CrossfireX combination includes
/// the CrossfireX capable adapter and its CrossfireX chain (a list of other adapters that will work with the CrossfireX capable adapter).  The possible
/// CrossfireX chain combinations for an adapter is retrieved from the ADL_Adapter_Crossfire_Caps function.
/// On Software Crossfire systems this function is used to query support and status of Crossfire. 
/// \platform
/// \ALL
/// \param[in]	iAdapterIndex The ADL index of the CrossfireX capable adapter to query the CrossfireX state and current information
/// \param[in]	lpCrossfireComb The CrossfireX chain to get information about. Ignored when called for Software crossfire
/// \param[out]	lpCrossfireInfo State and error information about the CrossfireX combination.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results
int EXPOSED ADL_Adapter_CrossfireX2_Get (int iAdapterIndex, ADLCrossfireComb *lpCrossfireComb, ADLCrossfireInfo *lpCrossfireInfo);

///
/// \brief Function to retrieve adapter caps information.
/// 
/// This function implements a DI call to retrieve adapter capability information .
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] adapterCaps The pointer to the structure storing the retrieved adapter capability information.
/// \return If the function succeeds, the return value is \ref ADL_OK, or an ADL error code otherwise. \ref define_adl_results
int EXPOSED ADL_Adapter_Caps(int iAdapterIndex,  ADLAdapterCaps *adapterCaps);

///
/// \brief Function to retrieve adapter limitation information.
/// 
/// This function implements a DI call to retrieve adapter limitation information .
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpAdapterLimitationCaps The pointer to the structure storing the retrieved adapter limitation information.
/// \return If the function succeeds, the return value is \ref ADL_OK, or an ADL error code otherwise. \ref define_adl_results
int EXPOSED ADL_AdapterLimitation_Caps(int iAdapterIndex,  ADLAdapterLimitationCaps *lpAdapterLimitationCaps);

#endif /* AMD_ADAPTER_H_ */
