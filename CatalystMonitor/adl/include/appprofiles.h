///
///  Copyright (c) 2008 - 2009 Advanced Micro Devices, Inc.
 
///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file appprofiles.h
/// \brief Contains all appprofiles-related functions exposed by ADL for \ALL platforms.
///
/// This file contains all appprofiles-related functions exposed by ADL for \ALL platforms.
/// All functions in this file can be used as a reference to ensure
/// the specified function pointers can be used by the appropriate runtime
/// dynamic library loaders.

#ifndef APPPROFILES_H_
#define APPPROFILES_H_

#include "adl_structures.h"

#ifndef EXPOSED
#define EXPOSED
#endif /* EXPOSED */

/// \addtogroup APPPROFILES
// @{

///
/// \brief Function to Reload System appprofiles.
/// 
/// This function Reloads System appprofiles by reloading system profile and loading user profile.
/// \platform
/// \WIN
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.   \ref define_adl_results
int EXPOSED ADL_ApplicationProfiles_System_Reload();

///
/// \brief Function to Load User appprofiles.
/// 
/// This function Loads User appprofiles by loadding system profile and user profile.
/// \platform
/// \WIN
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.   \ref define_adl_results
int EXPOSED ADL_ApplicationProfiles_User_Load();

///
/// \brief Function to Unload User appprofiles.
/// 
/// This function Unloads User appprofiles by unloading user profile.
/// \platform
/// \WIN
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.   \ref define_adl_results
int EXPOSED ADL_ApplicationProfiles_User_Unload();



/* TODO++ NOT FINALIZED IN ADL

///
/// \brief Function to Get appprofiles status info.
/// 
/// This function Gets appprofiles status info such as system/user profile loaded, loaded profile valid or not.
/// \platform
/// \WIN
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code.   \ref define_adl_results
int EXPOSED ADL_ApplicationProfiles_StatusInfo_Get();


int EXPOSED ADL_ApplicationProfiles_Get();
int EXPOSED ADL_ApplicationProfiles_Select();

*/

///
/// \brief Function to retrieve the profile of an application defined in driver.
/// 
/// This function retrieves the profile information of an application. 
/// This API uses the Caller's Memory Allocation Callback Function to allocate memory pointed by lppProfile. 
/// Caller is responsible to de-allocate the memory.
/// \platform
/// \WIN
/// \param[in]	FileName	Specifies the application file name
/// \param[in]	Path		Specifies the application file path
/// \param[in]	Version		Specifies the application version
/// \param[in]	AppProfileArea		Specifies the area the profile works on (like 'PX', 'D3D', etc. )
/// \param[out] lppProfile	The pointer to the pointer to the retrieved application profile. Set it to NULL prior to call this API.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API will be replaced with a new API that supports unicode. This API uses the memory allocation callback function provided by the user.
int EXPOSED ADL_ApplicationProfiles_ProfileOfAnApplication_Search(const char* FileName, const char* Path, 
								const char* Version, const char* AppProfileArea, ADLApplicationProfile** lppProfile);


///
/// \brief Function to retrieve the recent application list from registry.
/// 
/// This function retrieves the recent application list from registry. 
/// This API uses the Caller's Memory Allocation Callback Function to allocate memory pointed by lppAppList. 
/// Caller is responsible to de-allocate the memory.
/// \platform
/// \WIN
/// \param[in]	iListType	Specifies the type of the list to retrieve, defined in \ref ApplicationListType 
/// \param[out] lpNumApps	The pointer to the number of applications in the list. 
/// \param[out] lppAppList	The pointer to the pointer to the retrieved application list from registry. Set it to NULL prior to call this API.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API uses the memory allocation callback function provided by the user.
int EXPOSED ADL_ApplicationProfiles_HitLists_Get( int iListType, int * lpNumApps, ADLApplicationData ** lppAppList);


// @}

#endif /* appprofiles_H_ */
