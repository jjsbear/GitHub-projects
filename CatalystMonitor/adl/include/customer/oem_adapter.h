///
///  Copyright (c) 2008 - 2009 Advanced Micro Devices, Inc.
 
///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file oem_adapter.h
/// \brief Contains all customer display-related functions exposed by ADL for \ALL platforms.
///
/// This file contains all OEM or other customer adapter-related functions exposed by ADL for \ALL platforms.
/// All functions found in this file can be used as a reference to ensure
/// the specified function pointers can be used by the appropriate runtime
/// dynamic library loaders. This header file not for public release.

#ifndef OEM_ADAPTER_H_
#define OEM_ADAPTER_H_

#ifndef EXPOSED
#define EXPOSED
#endif /* EXPOSED */

/// \addtogroup ADAPTER
// @{
///\brief Function to get the VariBright capabilities
/// This function retrieves the VariBright capabilities for a specified display adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iSupported The pointer to an int variable which indicates if VariBright is supported ( \ref ADL_TRUE : supported, \ref ADL_FALSE : not supported)
/// \param[in]  iEnabled The pointer to an int variable which indicates if VariBright is enabled ( \ref ADL_TRUE : enabled, \ref ADL_FALSE : disabled)
/// \param[in]  iEnabled The pointer to an int variable receiving the VariBright version.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
///
/// \remarks Call this API first. Only if VariBright feature is supported and enabled call ADL_Adapter_VariBrightLevel_Get() or ADL_Adapter_VariBrightLevel_Set()
int EXPOSED ADL_Adapter_VariBright_Caps (int iAdapterIndex, int * iSupported, int * iEnabled, int * iVersion );

///\brief Function to enable or disable VariBright capabilities
/// This function enables or disables VariBright for a specified display adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iEnabled \ref ADL_TRUE : enables VariBright, \ref ADL_FALSE : disables VariBright.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
///
/// \remarks Call ADL_Adapter_VariBright_Caps() first to determine if VariBright feature is supported.
int EXPOSED ADL_Adapter_VariBrightEnable_Set (int iAdapterIndex, int iEnabled );

///\brief Function to get the current VariBright level 
/// This function retrieves the VariBright level for a specified display adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iDefaultLevel The pointer to an int variable with the default VariBright level.
/// \param[in]  iNumberOfLevels The pointer to an int variable receiving the number of VariBright levels (the Maximum value for VariBright level).
/// \param[in]  iStep The pointer to an int variable receiving the VariBright step. Determines the increments of the VariBright transition from one level to another.
/// \param[in]  iCurrentLevel The pointer to an int variable receiving the Current VariBright level.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
///
/// \remarks Call ADL_Adapter_VariBright_Caps() first to determine if VariBright feature is supported.
int EXPOSED ADL_Adapter_VariBrightLevel_Get (int iAdapterIndex, int * iDefaultLevel, int * iNumberOfLevels, int * iStep, int * iCurrentLevel );

///\brief Function to set the current VariBright level 
/// This function sets the VariBright level for a specified display adapter.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iCurrentLevel The VariBright level to be set. The range is from zero to iNumberOfLevels returned from ADL_Adapter_VariBrightLevel_Get()
/// \param[in]  iApplyImmediately If set to \ref ADL_TRUE the VariBright level is applied immediately. If \ref ADL_FALSE - the level is applied gradually.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results.
///
/// \remarks Call ADL_Adapter_VariBright_Caps() first to determine if VariBright feature is supported.
int EXPOSED ADL_Adapter_VariBrightLevel_Set (int iAdapterIndex, int iCurrentLevel, int iApplyImmediately );

// @}

///\addtogroup MAINAPI
// @{
///
/// \brief Function to retrieve version information.
/// 
/// This function retrieves software version information and a web link to an XML file with information about the latest web-posted Catalyst drivers
/// \param[out]  lpVersions The pointer to ADLVersionsInfo structure with the retrieved version information.
/// \platform 
/// \ALL
/// \return The function returns \ref ADL_OK or \ref ADL_OK_WARNING (if any of the version strings could not be retrieved from the system, for example "Catalyst Version"). If ADL is not initialized properly the function will return \ref ADL_ERR_DISABLED_ADAPTER
int EXPOSED ADL_Graphics_Versions_Get( ADLVersionsInfo * lpVersionsInfo );

// @}

/// \ingroup ADL_API
///\defgroup MMREARCHITECTURE Multi-Media APIs
/// This group outlines Multi-Media specific APIs.

/// \addtogroup MMREARCHITECTURE
// @{

/// \brief Function to obtain the list of Multi-Media features
/// 
/// The function is used to obtain the list of Multi-Media feature names for a specific display adapter.
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lppName is pointer to the pointer of ADLFeatureName array. Initialize to NULL before  calling this API. ADL will allocate the necessary memory, using the user provided callback function.
/// \param[out]  lpFeatureCount The number of all available features.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API uses the memory allocation callback function provided by the user.
int EXPOSED ADL_MMD_FeatureList_Get( int iAdapterIndex, ADLFeatureName ** lppName, int * lpFeatureCount );


/// \brief Function to obtain capabilities of Multi-Media features
/// 
/// The function is used to obtain the capabilities for a set of specific Multi-Media features for a specific display adapter.
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  lppFeatureCaps The pointer to the pointer to the retrieved Feature Caps array. Initialize to NULL before calling this API.
/// \param[out]  lpFeatureCount The pointer to the number of ADLFeatureCaps elements in the retrieved list.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API uses the memory allocation callback function provided by the user.
int EXPOSED ADL_MMD_Features_Caps( int iAdapterIndex, ADLFeatureCaps ** lppFeatureCaps, int * lpFeatureCount );


/// \brief Function to obtain the values and state of a Multi-Media feature
/// 
/// The function is used to obtain the values and state of a single Multi-Media feature for a specific display adapter.
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out]  lppFeatureValues The pointer to the pointer to the retrieved ADLFeatureValues array. Initialize to NULL before calling this API.
/// \param[out]  lpFeatureCount The pointer to the number of ADLFeatureValues elements in the retrieved list.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API uses the memory allocation callback function provided by the user.
int EXPOSED ADL_MMD_FeatureValues_Get( int iAdapterIndex, ADLFeatureValues ** lppFeatureValues, int * lpFeatureCount );


/// \brief Function to set the current value of a Multi-Media feature
/// 
/// The function is used to set the current value of a single Multi-Media feature and optionally provide the handle of SetEvent object.
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in]  lpFeatureValues A pointer to the ADLFeatureValues array. Refer to ADLFeatureValues structure for more information.
/// \param[out]  iFeatureCount The number of ADLFeatureValues elements in the array.
/// \param[in]  ClientID The Client ID of the caller. It is recommended to provide a valid Client ID to avoid raising caller?s event object, immediately after the current value is set.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
int EXPOSED ADL_MMD_FeatureValues_Set( int iAdapterIndex, ADLFeatureValues * lpFeatureValues, int iFeatureCount, int ClientID );


/// \brief Function to get MM video adjust info
///
/// The function is used to get multi-media video adjustment information.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[out] lppMMVideoData			The pointer to the pointer to the retrieved MM Video data structure.
/// \param[out]	lpCount					The number of returned video data structure.
/// \param[out] lpLetApplicationDecide	If it is true, disable the all settings and let application make decision. Otherwise, using driver settings.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_MMD_VideoAdjustInfo_Get( int iAdapterIndex, ADLMMVideoData** lppMMVideoData, int* lpCount, int* lpLetApplicationDecide );

/// \brief Function to set MM video adjust info
///
/// The function is used to set multi-media video adjustment information.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[in]	lpMMVideoSetData		The pointer to the pointer to the MM Video data structure to be set.
/// \param[in]	iCount					The number of video data structure to be set.
/// \param[in]	iCommittedFlag			Committed flag, the value can be ADL_TURE or ADL_FALSE. ( \ref ADL_TRUE : committed, \ref ADL_FALSE : uncommitted)
/// \param[in]	iLetApplicationDecide	If it is \ref ADL_TRUE, disable all the settings and let application make decision. Otherwise(\ref ADL_FALSE), using driver settings.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_MMD_VideoAdjustInfo_Set( int iAdapterIndex, ADLMMVideoSetData* lpMMVideoSetData, int iCount, int iCommittedFlag, int iLetApplicationDecide );

/// \brief Function to get MM video capabilities
///
/// The function is used to get current multi-media video capabilities.
/// 
/// \platform
/// \VISTAWIN7
/// \param[in]  iAdapterIndex			The ADL index handle of the desired adapter.
/// \param[in]	iVAControllerIndex		Controller index.
/// \param[in]	iVADisplayIndex			Display index.
/// \param[out] lpStandardVideoCaps		Standard video caps
/// \param[out]	lpHDVideoCaps			High-Definition Video caps
/// \param[out] lpGenericCaps			Generic Video caps
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_MMD_Video_Caps( int iAdapterIndex, int iVAControllerIndex, int iVADisplayIndex,
							   LPADLMMVideoCaps lpStandardVideoCaps, LPADLMMVideoCaps lpHDVideoCaps, LPADLMMVideoGenericCaps lpGenericCaps );
// @}


/// \addtogroup OVERDRIVE5
// @{

///  \brief Function to check for Power Control (long run GPU power limit) capabilities
///
/// The output parameter of the function lets the caller know about whether or not Power Control (long run GPU power limit) feature is available.  Supported only on GPUs with PowerTune Technology.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpSupported is ADL_TRUE if feature is supported, otherwise it is ADL_FALSE.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 

int EXPOSED ADL_Overdrive5_PowerControlAbsValue_Caps(int iAdapterIndex,  int *lpSupported);

///  \brief Function to get absolute values of Power Control (GPU power limit)
///
/// The parameters of the function allow the caller to obtain absolute value of the long run GPU power limit.  Supported only on GPUs with PowerTune Technology.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle  of the desired adapter 
/// \param[out]  lpCurrentValue pointer to the current value of long run GPU power limit 
/// \param[out]  lpDefaultValue pointer to the Default value of long run GPU power limit 
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 

int EXPOSED ADL_Overdrive5_PowerControlAbsValue_Get(int iAdapterIndex, int *lpCurrentValue, int *lpDefaultValue);

///  \brief Function to set absolute value of Power Control (long run GPU power limit)
///
/// The parameters of the function allow the caller to set absolute value of the long run GPU power limit, extends existing ADL_Overdrive5_PowerControl_Set API.  Supported only on GPUs with PowerTune Technology.
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter 
/// \param[in]  iValue New value of long run GPU power limit  
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error  code. 

int EXPOSED ADL_Overdrive5_PowerControlAbsValue_Set(int iAdapterIndex, int iValue);

// @}

#endif /* OEM_DISPLAY_H_ */
