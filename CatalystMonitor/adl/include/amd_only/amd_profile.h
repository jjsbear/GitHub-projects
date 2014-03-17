/*********************************************************************************************************************\
*  Module Name    amd_profile.h
*  Project        ADL
*  Device         
*
*  Description    A collection of Apply profile functions used
*
*  Copyright (c) 2008 - 2009 Advanced Micro Devices, Inc. (unpublished)
*
*  All rights reserved.  This notice is intended as a precaution against inadvertent publication and does not imply 
*  publication or any waiver of confidentiality.  The year included in the foregoing notice is the year of creation 
*  of the work.
*
\*********************************************************************************************************************/
#ifndef AMD_PROFILE_H
#define AMD_PROFILE_H

#if defined (_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include "ProfileStructure.h"

/// Defines for (un)setting expansion options.
#define UNSET_EXPANSION_OPTION 0
#define SET_EXPANSION_OPTION   1

/// Size of the string that contains the device name.
#define DEVICE_NAME_SIZE 32

/// 
/// \brief  Function to retrieve the expansion options for a specified display.
/// 
/// \param[in] iAdapterIndex The The ADL index handle of the desired adapter.
/// \param[in] iDisplayIndex The desired display index.
/// \param[out] piExpansion The retrieved expansion options.
void HIDDEN Display_ExpansionOptions_Get(int iAdapterIndex, int iDisplayIndex, int *piExpansion);

///
/// \brief Function to set the expansion options for a specified display, if they are different then currently set.
///
/// \param[in] iAdapterIndex  The ADL index handle of the desired adapter.
/// \param[in] iDisplayIndex  The desired display index.
/// \param[in] iValue The desired flags.
/// \param[out] piChanged Indicates whether the expansion options have changed. If options have been changed, it is set to TRUE. Otherwise it is set to FALSE.
void HIDDEN Display_ExpansionOptions_Set(int iAdapterIndex, int iDisplayIndex, int iValue, int *piChanged);

///
/// \brief Function to copy a driver profile to the adapter driver configuration.
/// 
/// \param[in] pastDrvProfile  The desired driver profile (source).
/// \param[out] pstAdapterDrvCfg  The desired adapter driver configuration (target).
void HIDDEN DrvProfileToAdapterDrvCfg_Copy(DrvProfile *pastDrvProfile, DI_ADAPTERDRIVERCONFIG *pstAdapterDrvCfg);

/// 
/// \brief Function to copy profile information retrieved from the OS to a specified driver profile.
///
/// \param[in] iAdapterIndex The ADL index handle of the adapter from which to copy (source).
/// \param[out] pastDrvProfile The desired driver profile (target).
///
/// \return If the function succeeds, the return value is is 1. Otherwise, the return value is 0.
int HIDDEN OSDataToProfile_Copy(int iAdapterIndex, DrvProfile *pastDrvProfile);

///
/// \brief Function to apply expansion if any change is required.
///  
/// \param[in] iAdapterIndex  The ADL index handle of the desired adapter.
/// \param[in] pastProfileToApply The the profile to be applied.
/// \param[out] pabExpansionApplied The set per driver (controller) if expansion is applied.
void HIDDEN Display_Expansion_Apply(int iAdapterIndex, DrvProfile *pastProfileToApply, int *pabExpansionApplied);

///
/// \brief Function to remove an extended desktop if it is not used in the profile that is to be applied.
///
/// \param[in] iAdapterIndex  The ADL index handle of the desired adapter.
/// \param[in] pastProfileToApply The profile to be applied.
/// \param[out] pastCurrentProfile The (current) profile to be replaced.
///  
/// \return If the function succeeds, ADL_OK is returned. Otherwise ADL_ERR_NULL_POINTER is returned.
int HIDDEN Display_IfRequired_RemoveDesktop(int iAdapterIndex, DrvProfile *pastProfileToApply, 
                                            DrvProfile *pastCurrentProfile);

/// 
/// \brief Function to set the mode per driver if a mode set is still required.
///  
/// \param[in] iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in] pastProfileToApply The profile to be applied.
/// \param[in] pastCurrentProfile The (current) profile to be replaced.
/// \param[in] pabModeSetRequired Specifies that a mode set is still required.
/// 
/// \return If the function succeeds, ADL_OK is returned. Otherwise ADL_ERR_NULL_POINTER is returned.
int HIDDEN Display_IfRequired_SetMode(int iAdapterIndex, DrvProfile *pastProfileToApply, 
                                      DrvProfile *pastCurrentProfile, int *pabModeSetRequired);

////////////////// Functions below need to be accessible from outside ADL /////////////////////////////////////////////////////

///
/// \brief Function to apply the passed in profile.
///  
/// \param[in] iAdapterIndex  The ADL index handle of the desired adapter.
/// \param[in] pastProfileToApply  The profile to be applied.
/// \param[in] ulConnectedDisplays Currently connected displays.
/// 
/// \return If the function succeeds, ADL_OK is returned. Otherwise ADL_ERR_NULL_POINTER is returned.
int EXPOSED ADL_ADC_Profile_Apply(int iAdapterIndex, DrvProfile *pastProfileToApply, ULONG ulConnectedDisplays);

///
/// \brief Function to retrieve the currently applied profile from the driver.
///
/// \param[in] iAdapterIndex  The ADL index handle of the desired adapter.
/// \param[in] pstConnectedProfile The connected profile is saved here.
/// \param[in] pstSelectedProfile  The selected profile is saved here.
/// \param[in] ulConnectedDisplays The currently connected displays.
///
/// \return If the function succeeds, ADL_OK is returned. Otherwise ADL_ERR_NULL_POINTER is returned.
int EXPOSED ADL_ADC_CurrentProfileFromDrv_Get(int iAdapterIndex, ConnectedProfile *pstConnectedProfile, 
                                              SelectedProfile *pstSelectedProfile, ULONG ulConnectedDisplays); 

///
/// \brief Function to copy the required profile information retrieved from the driver to a profile.  This function also
///           retrieves and saves the expansion settings from the driver.
///  
/// \param[in] iAdapterIndex  The ADL index handle of the desired adapter.
/// \param[in] pastDrvProfile The desire driver profile (target).
/// \param[in] pastDriverData The desire driver data(source).
/// 
/// \return If the function succeeds, ADL_OK is returned. Otherwise ADL_ERR_NULL_POINTER is returned.
 int EXPOSED ADL_ADC_DrvDataToProfile_Copy(int iAdapterIndex, DrvProfile *pastDrvProfile, DI_DRIVER_DATA *pastDriverData);

///
/// \brief Function to remap the controllers and displays based on the passed in DrvProfile.
///  
/// \param[in] iAdapterIndex  The ADL index handle of the desired adapter.
/// \param[in] pastProfileToApply The the profile to be applied.
/// \param[in] pabModeSetRequired If a mode change is occurring then set this to FALSE.
/// 
/// \return If the function succeeds, ADL_OK is returned. Otherwise ADL_ERR_NULL_POINTER is returned.
int EXPOSED ADL_Remap(int iAdapterIndex, DrvProfile *pastProfileToApply, int *pabModeSetRequired);

///
/// \brief Function to retrieve the closest mode to the one passed to the function.  Only a mode with the same BPP is returned.
///
/// \param[in] pcDisplayName The name of the display on which to perform the mode search.
/// \param[out] pstDevMode The pointer to the retrieved mode.  Will be used to return the mode to be set.
///
/// \return If the function succeeds, ADL_OK is returned. Otherwise ADL_ERR is returned.
int EXPOSED ADL_ADC_FindClosestMode_Get(char *pcDisplayName, DEVMODE *pstDevMode);

///
/// \brief This function checks whether a pair of modes is equivalent, including BPP, to each other.
///
/// \param[in] pstDevMode1 The mode being checked.
/// \param[in] pstDevMode2 The mode to be compared with pstDevMode1.
///
/// \return If the function succeeds, TRUE is returned. Otherwise FALSE is returned.
BOOL EXPOSED ADL_ADC_IsDevModeEqual_Get(DEVMODE *pstDevMode1, DEVMODE *pstDevMode2);


/// \addtogroup APPPROFILES
// @{


///
/// \brief Function to retrieve data type for the specified property.
/// 
/// This function retrieves data type for the specified property. 
/// \platform
/// \WIN
/// \param[in]	DriverArea	 Specifies driver area where Property belong to
/// \param[in]	PropertyName Specifies name of property
/// \param[out] outType  	 The data type of property
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API retrieves data type for the specified property.
int EXPOSED ADL_ApplicationProfiles_PropertyType_Get(const wchar_t * DriverArea,  const wchar_t * PropertyName, DATATYPES * outType);


///
/// \brief Function to check if the specified profile exist or not in system blob.
/// 
/// This function checks if the specified profile exist or not in system blob. 
/// \platform
/// \WIN
/// \param[in]	DriverArea	Specifies driver area
/// \param[in]  ProfileName	Specifies the name of profile
/// \param[out] outExists	Indicates if the specified profile exists or not
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API checks if the specified profile exist or not in system blob.
int EXPOSED ADL_ApplicationProfiles_Profile_Exist ( const wchar_t * DriverArea, const wchar_t * ProfileName, BOOL * outExists);

///
/// \brief Function to retrieve privacy type for the specified area
/// 
/// This function retrieves privacy type for the specified area
/// \platform
/// \WIN
/// \param[in]	DriverArea	Specifies driver area
/// \param[out] outDriverAreaPrivacy	The pointer to privacy for the specified area/
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API retrieves privacy type for the specified area
int EXPOSED ADL_ApplicationProfiles_DriverAreaPrivacy_Get ( const wchar_t * DriverArea, PRIVACYTYPES * outDriverAreaPrivacy);

///
/// \brief Function to assign a profile in a new or existing applicaiton record.
/// 
/// This function assigns a profile in a new or existing applicaiton record.
/// \platform
/// \WIN
/// \param[in]	FileName	Specifies the name of file
/// \param[in] Path    	Specifies the path where file locates
/// \param[in] Version 	Specifies version
/// \param[in] DriverArea  Specifies driver area where Profile exists
/// \param[in] ProfileName Specifies Profile to use
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API assigns a profile in a new or existing applicaiton record. If area exists, then override use record, otherwise, create a new use record
int EXPOSED ADL_ApplicationProfiles_ProfileApplication_Assign ( const wchar_t * FileName, const wchar_t * Path,  const wchar_t * Version, const wchar_t * DriverArea, const wchar_t * ProfileName);

///
/// \brief Function to assign a profile in a new or existing applicaiton record.
/// 
/// This function assigns a profile in a new or existing applicaiton record.
/// \platform
/// \WIN
/// \param[in]	FileName	Specifies the name of file
/// \param[in] Path    	Specifies the path where file locates
/// \param[in] Version 	Specifies version
/// \param[in] Title 	Specifies title
/// \param[in] DriverArea  Specifies driver area where Profile exists
/// \param[in] ProfileName Specifies Profile to use
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API assigns a profile in a new or existing applicaiton record. If area exists, then override use record, otherwise, create a new use record
int EXPOSED ADL_ApplicationProfiles_ProfileApplicationX2_Assign ( const wchar_t * FileName, const wchar_t * Path,  const wchar_t * Version, const wchar_t * Title, const wchar_t * DriverArea, const wchar_t * ProfileName);

///
/// \brief Function to remove the specified application record 
/// 
/// This function removes the specified application record.
/// \platform
/// \WIN
/// \param[in]	FileName	Specifies the name of file
/// \param[in] Path    	Specifies the path where file locates
/// \param[in] Version 	Specifies version
/// \param[in] DriverArea  Specifies driver area where Profile exists
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API removes the specified application record.
int EXPOSED ADL_ApplicationProfiles_RemoveApplication (const wchar_t* FileName, const wchar_t* Path,  const wchar_t* Version,  const wchar_t* DriverArea);

///
/// \brief Function to retrieve the pointer to Customization structure of the specified blob file
/// 
/// This function retrieves the pointer to Customization structure of the specified blob file.
/// \platform
/// \WIN
/// \param[in]	Databaseln	Specifies the type of blob file
/// \param[out] pCustomizationOut	The pointer to Customization structure of the specified blob file
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API retrieves the pointer to Customization structure of the specified blob file
int EXPOSED ADL_ApplicationProfiles_GetCustomization (SHARED_AP_DATABASE Databaseln, CUSTOMISATIONS * pCustomizationOut);

///
/// \brief Function to convert C style structures into Compact style for writing a blob file
/// 
/// This function converts C style structures into Compact style for writing a blob file
/// \platform
/// \WIN
/// \param[in]	pCustomisation	Specifies pointer to Customization of database 
/// \param[out] outCompact	The pointer to compact structure. 
/// \param[out] outSize	    The size of compact structure
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API onverts C style structures into Compact style for writing a blob file
int EXPOSED ADL_ApplicationProfiles_ConvertToCompact(CUSTOMISATIONS * pCustomisation, BINFILE * outCompact, int * outSize);

///
/// \brief Function to return release of installed system application profile blob file.
/// 
/// This function returns release of installed system application profile blob file.
/// \platform
/// \WIN
/// \param[in] driverArea  Specifies driver area where profile delcares 
/// \param[in] profileName Specifies the name of profile to be created
/// \param[in] numProperties Specifies the number of properties in the profile to be created
/// \param[in] propertyRecords  The pointer to property records in the profile to be created
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API returns release of installed system application profile blob file.
int EXPOSED ADL_ApplicationProfiles_Profile_Create ( const wchar_t * driverArea, const wchar_t * profileName,  int numProperties, const ADLPropertyRecordCreate * propertyRecords);

///
/// \brief Function to remove the specified profile from the User blb.
/// 
/// This function removes the specified profile from the User blb.
/// \platform
/// \WIN
/// \param[in] driverArea  Specifies driver area where profile delcares 
/// \param[in] profileName Specifies the name of profile to be removed
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API removes the specified profile from the User blb.
int EXPOSED ADL_ApplicationProfiles_Profile_Remove ( const wchar_t * driverArea, const wchar_t * profileName);

///
/// \brief Function to return list of applications declared in given driver area
/// 
/// This function builds and returns list of applications that exist in the given area of System, OEM and User blobs. User blob has precedence over OEM blob, OEM blob has precedence over System blob.
/// \platform
/// \WIN
/// \param[in] driverArea    	 Specifies driver area
/// \param[out] numApps 	     Returns number of application record in given driver area
/// \param[out] adlApplications  Returns the pointer to application records
/// \param[in] allowDuplication  If it's false and duplicated records of applicaiton exist (e.g. in System and Uer blob), then only one recored is returned, otherwise, return all same records from all blobs
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API builds and returns list of applications that exist in the given area of System, OEM and User blobs. User blob has precedence over OEM blob, OEM blob has precedence over System blob.
int EXPOSED ADL_ApplicationProfiles_Applications_Get ( const wchar_t * driverArea, int * numApps, ADLApplicationRecord ** adlApplications);

///
/// \brief Function to return release of installed system application profile blob file.
/// 
/// This function returns release of installed system application profile blob file.
/// \platform
/// \WIN
/// \param[out] strRelease  The pointer to the stRelease. 
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
///
/// \remarks This API returns release of installed system application profile blob file.
int EXPOSED ADL_ApplicationProfiles_Release_Get ( wchar_t** strRelease);

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
/// \remarks This API uses the memory allocation callback function provided by the user.
int EXPOSED ADL_ApplicationProfiles_ProfileOfAnApplicationX2_Search(const wchar_t* FileName, const wchar_t* Path, 
								const wchar_t* Version, const wchar_t* AppProfileArea, ADLApplicationProfile** lppProfile);

// @}

#endif /// AMD_PROFILE_H_
