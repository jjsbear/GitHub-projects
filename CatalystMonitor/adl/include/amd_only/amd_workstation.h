///
///  Copyright (c) 2008 - 2009 Advanced Micro Devices, Inc.
 
///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file amd_workstation.h
/// \brief This file contains the workstation method declarations used by the internal AMD Driver Library interfaces for \ALL platforms.
///

#ifndef __AMD_WORKSTATION_H__
#define __AMD_WORKSTATION_H__

///\brief Function to set ECC Mode, to turn on and off this feature. 
/// 
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  iDesiredMode - ECC Mode currently accepts ECC_MODE_OFF or ECC_MODE_ON
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// 
int EXPOSED ADL_Workstation_ECC_Set (int iAdapterIndex, int iDesiredMode);

///\brief Function to get the currentMode (driver mode) and the desired mode. 
/// 
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  lpDefault : Default ECC Mode (ECC_MODE_OFF, ECC_MODE_ON)
/// \param[in]  lpCurrentMode : ECC Mode that is currently stored in the permanent store for driver. (ECC_MODE_OFF, ECC_MODE_ON)
/// \param[in]  lpDesiredMode : Desired ECC mode from the user, once the user reboots the machine DesiredMode will be applied to CurrentMode (ECC_MODE_OFF, ECC_MODE_ON)
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise if all the parameters are null, returns ADL_ERR_NULL_POINTER. \ref define_adl_results 
/// \remarks Atleast one of these parameters (lpDefauls, lpCurrentMode and lpDesiredMode) should be not null, for this interface to extract the data 
int EXPOSED ADL_Workstation_ECC_Get (int iAdapterIndex, int *lpDefaultMode, int *lpCurrentMode, int *lpDesiredMode);

///\brief Function to get ECC caps
/// 
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  lpSupported - returns the capability, whether ECC is supported or not for the adapterIndex(ADL_TRUE or ADL_FALSE)
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
/// 

int EXPOSED ADL_Workstation_ECC_Caps (int iAdapterIndex, int *lpSupported);


///\brief Function to get ECC statistics ( SEC & DED counts). 
/// 
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex The index of the desired adapter.
/// \param[in]  lpAdlEccData is of type ADLECCData. to get the SEC & DED counts 
/// \return If the function succeeds, the return value is ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Workstation_ECCData_Get(int iAdapterIndex, ADLECCData *lpAdlEccData);


///
/// \brief Function to retreive the worstation 8-bit Grayscale mode.
/// 
/// This function retrieves the current and default workstation 8-bit Grayscale mode.
/// \platform
/// \XP
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[out] lpDefState The pointer to the default 8-bit Grayscale mode. \ref ADL_FALSE 
/// \param[out] lpCurState The pointer to the current 8-bit Grayscale mode. \ref ADL_TRUE/ADL_FALSE 
/// \return If the function is successful, \ref ADL_OK is returned. If lpDefState and/or lpCurState are NULL, \ref ADL_ERR_NULL_POINTER is returned.\n
/// If iAdapterIndex is an invalid adapter index, \ref ADL_ERR_INVALID_ADL_IDX is returned. If the function is not supported, \ref ADL_ERR_NOT_SUPPORTED is returned. For all other errors, \ref ADL_ERR is returned.
int EXPOSED ADL_Workstation_8BitGrayscale_Get ( int iAdapterIndex, int *lpDefState, int *lpCurState);

///
/// \brief Function to set the workstation 8-bit Grayscale mode.
/// 
/// This function sets the current workstation 8-bit Grayscale mode mode.
/// \platform
/// \XP
/// \param[in]  iAdapterIndex The ADL index handle of the desired adapter.
/// \param[in] iCurState The desired workstation 8-bit Grayscale mode. \ref ADL_TRUE/ADL_FALSE 
/// \return If the function is successful, \ref ADL_OK is returned. If iAdapterIndex is an invalid adapter index, \ref ADL_ERR_INVALID_ADL_IDX is returned.\n
/// If the function is not supported, \ref ADL_ERR_NOT_SUPPORTED is returned. For all other errors, \ref ADL_ERR is returned.
int EXPOSED ADL_Workstation_8BitGrayscale_Set( int iAdapterIndex, int iCurState);

/// \brief Function to check for Serial Digital Interface capabilities
///
/// \platform
/// \ALL
/// \param[in]  iAdapterIndex, ADL index handle of the desired adapter.
/// \param[out] lpSupported, The pointer to the caps of adapter settings. If the specified adapter supports SDI, it is set to ADL_TRUE, else set to ADL_FALSE
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Workstation_SDI_Caps(int iAdapterIndex, int *lpSupported);

/// \brief Function to get the default, driver and user requested Serial Digital Interface Data for the specified adapter.
/// 
/// \platform
/// \ALL
/// \param[in]   iAdapterIndex, ADL index handle of the desired adapter.
/// \param[out]  lpDefualt, pointer to the default SDI settings of the specified adapter.
/// \param[out]  lpCurrent, pointer to the driver SDI settings of the specified adapter.
/// \param[out]  lpDriver,  pointer to the user requested SDI seetings of the specified adapter.
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Workstation_SDI_Get( int iAdapterIndex, ADLSDIData *lpDefualt, ADLSDIData *lpDriver, ADLSDIData *lpCurrent );

/// \brief Function to set the  user requested Serial Digital Interface Data for the specified adapter.
/// 
/// \platform
/// \ALL
/// \param[in] iAdapterIndex, ADL index handle of the desired adapter.
/// \param[out] lpMemorySegmentCount, pointer to the supported memory segment count of the specified adapter
/// \param[out] lppMemorySegmentList, pointer to the supported memory segment list of the specified adapter
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Workstation_SDISegmentList_Get( int iAdapterIndex, int *lpMemorySegmentCount, int **lppMemorySegmentList );

///
/// \brief Function to set the  user requested Serial Digital Interface Data for the specified adapter.
/// 
/// \platform
/// \ALL
/// \param[in] iAdapterIndex, ADL index handle of the desired adapter.
/// \param[in] iSDIState, SDI state (possiable values ADL_SDI_ON or ADL_SDI_OFF
/// \param[in] iSizeofSDISegment, size of the apreture
/// \return If the function succeeds, the return value is \ref ADL_OK (zero). Otherwise the return value is an ADL error code (non-zero). \ref define_adl_results 
int EXPOSED ADL_Workstation_SDI_Set( int iAdapterIndex, int iSDIState, int iSizeofSDISegment );
// @}
#endif //__AMD_WORKSTATION_H__
