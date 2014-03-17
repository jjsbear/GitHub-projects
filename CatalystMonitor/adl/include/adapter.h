///
///  Copyright (c) 2008 - 2009 Advanced Micro Devices, Inc.
 
///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file adapter.h
/// \brief Contains all adapter-related functions exposed by ADL for \ALL platforms.
///
/// This file contains all adapter-related functions exposed by ADL for \ALL platforms.
/// All functions in this file can be used as a reference to ensure
/// the appropriate function pointers can be used by the appropriate runtime
/// dynamic library loaders.

#ifndef ADAPTER_H_
#define ADAPTER_H_

#include "adl_structures.h"

#ifndef EXPOSED
#define EXPOSED
#endif /* EXPOSED */

///\addtogroup ADAPTER
// @{
///
/// \brief Function to determine if the adapter is active or not.
/// 
/// The function is used to check if the adapter associated with iAdapterIndex is active. Logic is different for Windows and Linux!
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpStatus The pointer to the retrieved status. \ref ADL_TRUE : Active; \ref ADL_FALSE : Disabled.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_Active_Get ( int iAdapterIndex, int* lpStatus);

///
/// \brief Function to retrieve the number of OS-known adapters.
/// 
/// This function retrieves the number of graphics adapters recognized by the OS (OS-known adapters). OS-known adapters can include adapters that are physically present in the system (logical adapters)    
/// as well as ones that no longer present in the system but are still recognized by the OS.
/// \platform
/// \ALL
/// \param[out] lpNumAdapters The pointer to the number of OS-known adapters.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results 
int EXPOSED ADL_Adapter_NumberOfAdapters_Get (  int* lpNumAdapters );

///
/// \brief Function to save driver data
/// 
/// This function saves all required data from driver to persist updated settings
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The adapter index to be flushed.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results 
int EXPOSED ADL_Flush_Driver_Data(int iAdapterIndex);

///
/// \brief Retrieves all OS-known adapter information.
/// 
/// This function retrieves the adapter information of all OS-known adapters in the system. OS-known adapters can include adapters that are physically present in the system (logical adapters)    
/// as well as ones that are no longer present in the system but are still recognized by the OS.
/// \platform
/// \ALL
/// \param[in]  iInputSize The size of the lpInfo buffer.
/// \param[out] lpInfo The pointer to the buffer containing the retrieved adapter information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results  
///
/// \remarks This API take a fixed-size output array. For dynamic-size output, use \ref ADL_Adapter_AdapterInfoX2_Get function.
int EXPOSED ADL_Adapter_AdapterInfo_Get (LPAdapterInfo lpInfo, int iInputSize);

///
/// \brief Retrieves all OS-known adapter information.
/// 
/// This function retrieves the adapter information of all OS-known adapters in the system. OS-known adapters can include adapters that are physically present in the system (logical adapters)    
/// as well as ones that are no longer present in the system but are still recognized by the OS.
/// \platform
/// \ALL
/// \param[out] lppAdapterInfo is pointer to the pointer of AdapterInfo array. Initialize to NULL before calling this API. ADL will allocate the necessary memory, using the user provided callback function.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// 
/// \remarks This API uses the memory allocation callback function provided by the user.
int EXPOSED ADL_Adapter_AdapterInfoX2_Get (AdapterInfo **lppAdapterInfo);

///
///\brief Function to get the ASICFamilyType from the adapter. 
/// 
/// This function retrieves the display Color Caps information for a specified adapter and display.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpAsicTypes The pointer to the Color Caps information retrieved from the driver. \ref define_Asic_type
/// \param[out] lpValids The pointer to the bit vector indicating which bit is valid on the lpAsicTypes returned.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Adapter_ASICFamilyType_Get (int iAdapterIndex, int* lpAsicTypes, int* lpValids);

///
/// \brief Function to get the current Force3DClock setting from the adapter. 
///
/// This function retrieves the adapter speed information for a specified adapter.  Return valud can be \ref ADL_ADAPTER_SPEEDCAPS_SUPPORTED or “0”
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpCaps The caps of adapter speed settings
/// \param[out] lpValid The valid bits of adapter speed settings
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Adapter_Speed_Caps (int iAdapterIndex, int* lpCaps, int* lpValid);

///
/// \brief Function to get the current Speed setting from the adapter.
///
/// This function retrieves the adapter speed information for a specified adapter.  Return value is either \ref ADL_CONTEXT_SPEED_UNFORCED or \ref ADL_CONTEXT_SPEED_FORCEHIGH
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpCurrent The current speed setting
/// \param[out] lpDefault The default speed setting
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Adapter_Speed_Get (int iAdapterIndex, int *lpCurrent, int *lpDefault);

///
/// \brief Function to set the current Speed setting from the adapter.
///
/// This function set the adapter speed information for a specified adapter.  Input value is either \ref ADL_CONTEXT_SPEED_UNFORCED or \ref ADL_CONTEXT_SPEED_FORCEHIGH
/// \platform
/// \ALL
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in] iSpeed The speed to set on specified adapter
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Adapter_Speed_Set (int iAdapterIndex, int iSpeed);

///
/// \brief Function to check if the GPU is accessible or not at the time of this call.
/// 
/// Some GPUs enter into various power savings mode when not in use, and during this time, direct access to the GPU can result in failures.
/// Access through proper channels (such as via ADL) always works because the software accounts for the GPU's accessibility.
/// However, direct access outside of authorised mechanisms may fail.
/// Use this API to find out if the GPU is currently accessible or not.
///  If API returns GPU accessible, this status will be maintained for 2 seconds.
///
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpAccessibility The pointer to an int  value which indicates if the adapter is accessible or not (\ref ADL_TRUE : Accessible, \ref ADL_FALSE : Not accessible)
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_Accessibility_Get (int iAdapterIndex, int  *lpAccessibility); 

///
/// \brief ADL local interface. Function to retrieve BIOS information.
/// 
/// This function retrieves the BIOS information for a specified adapter.
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lpBiosInfo The pointer to the structure storing the retrieved BIOs information.
/// \platform 
/// \LNX
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_VideoBiosInfo_Get( int iAdapterIndex, ADLBiosInfo* lpBiosInfo );

///
///\brief Function to get the unique identifier of an adapter.
/// 
/// This function retrieves the unique identifier of a specified adapter.\n
/// The adapter ID is a unique value and will be used to determine what other controllers share the same adapter.\n
/// The desktop will use this to find which HDCs are associated with an adapter.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lpAdapterID The pointer to the adapter identifier. Zero means: The adapter is not AMD.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API is a duplicate to ADL_Display_AdapterID_Get()
 int EXPOSED ADL_Adapter_ID_Get(int iAdapterIndex, int* lpAdapterID);

// @}

///\addtogroup CROSSFIRE
// @{
///
/// \brief Function to retrieve CrossfireX capabilities of the system.
///
/// This function is used to determine if the system is capable of doing CrossfireX, regardless if the system is setup properly.
/// \platform
/// \ALL
/// \param[in]	iAdapterIndex The ADL index handle of the desired adapter to query CrossfireX capabilities
/// \param[out]	lpPreferred The index of the preferred CrossfireX chain. The index is a zero based index reference in the ADLCrossfireComb list.
/// \param[out]	lpNumComb The integer value indicating the number of ADLCrossfireComb structures in the lpCrossfireComb buffer
/// \param[out]	ADLCrossfireComb **ppCrossfireComb The Pointer to an empty memory buffer(NULL).  This function will use the callback to allocate the appropriate buffer size.  This buffer will contain a list of supported CrossfireX combinations if the adapter supports CrossfireX.  If the adapter does not support CrossfireX, this memory buffer will remain empty, or NULL.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results
///
/// \remarks This API uses the memory allocation callback function provided by the user.
int EXPOSED ADL_Adapter_Crossfire_Caps (int iAdapterIndex, int* lpPreferred, int* lpNumComb, ADLCrossfireComb **ppCrossfireComb);

///
/// \brief Function to get current CrossfireX combination settings.
///
/// This function is used to retrieve the current information about a particular CrossfireX combination.  A CrossfireX combination includes
/// the CrossfireX capable adapter and its CrossfireX chain (a list of other adapters that will work with the CrossfireX capable adapter).  The possible
/// CrossfireX chain combinations for an adapter is retrieved from the ADL_Adapter_Crossfire_Caps function.
/// \platform
/// \ALL
/// \param[in]	iAdapterIndex The ADL index of the CrossfireX capable adapter to query the CrossfireX state and current information
/// \param[in]	lpCrossfireComb The CrossfireX chain to get information about.
/// \param[out]	lpCrossfireInfo State and error information about the CrossfireX combination.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results
int EXPOSED ADL_Adapter_Crossfire_Get (int iAdapterIndex, ADLCrossfireComb *lpCrossfireComb, ADLCrossfireInfo *lpCrossfireInfo);

///
/// \brief Function to set CrossfireX combination settings.
///
/// This function is used to enable or disable CrossfireX on a particular adapter (pointed to by iAdapterIndex), along with the indicated CrossfireX chain.
/// The CrossfireX chain combination for the adapter must be one returned by ADL_Adapter_Crossfire_Caps().
/// \platform
/// \ALL
/// \param[in]	iAdapterIndex The adapter in which to enable or disable CrossfireX
/// \param[in]	lpCrossfireComb[in] the CrossfireX chain combination to enable or disable for the master adapter.  If this parameter is not NULL, it will
/// enable CrossfireX with the indicated combination.  If this parameter is NULL, it will disable CrossfireX on that particular adapter.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results
int EXPOSED ADL_Adapter_Crossfire_Set (int iAdapterIndex, ADLCrossfireComb *lpCrossfireComb);

// @}


/// \addtogroup LINUX
// @{

///
/// \brief Function to retrieve memory information from the adapter.
/// 
/// This function retrieves the memory information for a specified graphics adapter.
/// \platform
/// \LNX
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpMemoryInfo The pointer to the structure storing the retrieved memory information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Adapter_MemoryInfo_Get(int iAdapterIndex, ADLMemoryInfo *lpMemoryInfo);

///
///\brief Function to get the memory configuration of an adapter
///
/// This function retrieves the memory configuration of a specified adapter.\n
/// \platform
/// \LNX
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]   iScreenWidth	The pixel width of the X screen associated with the adapter.
/// \param[in]   iScreenHeight	The pixel height of the X screen associated with the adapter.
/// \param[in]   displayFeatureMask	The valid \ref define_adl_visiblememoryfeatures features
/// \param[in]   numDisplays	 Number of displays associated with the XScreen.
/// \param[in]   displayFeatureList	List of display features associated with each display found in the XScreen. Number of entries is numDisplays.
/// \param[in]   iNumMemTypes	Size of  lppMemRequired List
/// \param[out]  lppMemRequired List of visible memory size required in bytes of specified type
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \remarks This API uses the memory allocation callback function provided by the user. If this API is called in Windows the return value is always \ref ADL_ERR_NOT_SUPPORTED
int EXPOSED ADL_Adapter_ConfigMemory_Get(int iADLAdapter, int iScreenWidth, int iScreenHeight, int displayFeatureMask, int numDisplays, ADLMemoryDisplayFeatures * displayFeatureList, int *iNumMemTypes, ADLMemoryRequired **lppMemRequired);

///
///\brief Function to get the core and memory clock info of an adapter.  This is the clock displayed on CCC information center.
///         Specific logic is used to select appropriate clock for display in current configuration.
///
/// This function retrieves the core and memory clock of an adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpCoreClock The pointer to the core clock retrieved from the driver in Mhz.
/// \param[out] lpMemoryClock The pointer to the memory clock retrieved from the driver in Mhz.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results
int EXPOSED ADL_Adapter_ObservedClockInfo_Get (int iAdapterIndex, int* lpCoreClock, int* lpMemoryClock);

// @}

// Deprecated APIs

///
/// \brief Function to retrieve clock information for an adapter.
/// 
/// This function retrieves the clock information for a specified graphics adapter.
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpClockInfo The pointer to the structure storing the retrieved core and memory clock information.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results \n
/// \deprecated This API has been deprecated because it does not provide accurate clocks when the ASIC is over-clocked. Use the OD5 set of APIs, when OverDrive5 is supported.
int EXPOSED ADL_Adapter_ClockInfo_Get(int iAdapterIndex, ADLClockInfo* lpClockInfo);

///
///\brief Function to get the unique identifier of an adapter. Will be removed! Use ADL_Adapter_ID_Get()
/// 
/// This function retrieves the unique identifier of a specified adapter.\n
/// The adapter ID is a unique value and will be used to determine what other controllers share the same adapter.\n
/// The desktop will use this to find which HDCs are associated with an adapter.
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lpAdapterID The pointer to the adapter identifier. Zero means: The adapter is not AMD.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
/// \deprecated This API will be removed. Use the duplicate API ADL_Adapter_ID_Get() 
 int EXPOSED ADL_Display_AdapterID_Get(int iAdapterIndex, int* lpAdapterID);


#endif /* ADAPTER_H_ */

