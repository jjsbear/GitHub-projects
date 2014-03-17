///
///  Copyright (c) 2008 - 2012 Advanced Micro Devices, Inc.
 
///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file adl.h
/// \brief Contains the main functions exposed by ADL for \ALL platforms.
///
/// This file contains the main functions exposed by ADL for \ALL platforms.
/// All functions in this file can be used as a reference when creating
/// specific function pointers to be used by the appropriate runtime
/// dynamic library loaders.
/// \mainpage
// @{
/// This document describes the APIs (application programming interfaces) that can be used to access
/// AMD-specific display driver functionality, such as those related to specific display devices. \n\n
/// Included in this document are definitions as well as the data structures used by each API. \n
/// Public functions are prefixed with "ADL_". 
/// The majority of the APIs are supported on 32-bit and 64-bit versions of Windows (XP and Vista) and Linux platforms. \n\n
/// Working code samples and snippets of the API source code files are also provided for reference purposes.\n\n
///\note Although a number of header files are referenced in this document, only three are required and provoided with this SDK:\n
///\li \b adl_sdk.h : The ony header file to be included in a C/C++ project \n
///\li \b adl_structures.h : Definitions of all structures for public use. Included in \b adl_sdk.h \n
///\li \b adl_defines.h : Definitions of all Constants and Enumerations.  Included in \b adl_structures.h \n
///
/// The three files should be placed in the same folder.
// @}

#ifndef ADL_H_
#define ADL_H_

// Define the API groups here so they can appear in this partiqular order.
// Use Doxygen command "ingroup" to add APIs to these groups from other files.

/// \example Sample-Managed/program.cs
/// A C# Sample Application for \WIN \n
/// Visual Studio 2005 solution file <b> "Sample-Managed.sln" </b> is included in ADL SDK

/// \example Sample-Managed/ADL.cs
/// A C# class encapsulating some of the ADL APIs. Used by the C# Sample Application

/// \example Sample/main.c
/// A C/C++ Sample Application for \ALL \n
/// Visual Studio 2005 solution file <b> "ADL Sample.sln" </b> is included in ADL SDK

// Adding the Supported Hardware and OS page (Add another slash to the lines below to enable...)
/// \page LOGOS Compatibility
/// \htmlinclude Public-Documents/logo.htm

// Adding the tutorial as a separate page...
/// \page WHATISADL What is ADL and how to use it?
/// \htmlinclude Public-Documents/WhatIsADL.html

/// \page OD5_APIS OverDrive5 API Notes
/// \htmlinclude Public-Documents/OD5_APIs.html

// Enable the top "API Groups" this by adding one more slash line at the begginning of line below...
//\defgroup ADL_API API Groups



///\ingroup ADL_API
///\defgroup MAINAPI Main Group of APIs
/// This group describes the APIs for initializing, refreshing and destroying ADL

///\ingroup ADL_API
///\defgroup ADAPTERAPI Adapter Related APIs
/// This group outlines all adapter related APIs.

///\ingroup ADAPTERAPI
///\defgroup ADAPTER General Adapter APIs
/// This group describes general Adapter  APIs.

///\ingroup ADAPTERAPI
///\defgroup CROSSDISPLAY CrossDisplay APIs
/// This group describes the CrossDisplay APIs.

///\ingroup ADAPTERAPI
///\defgroup CROSSFIRE CrossFire APIs
/// This group describes the CrossFire APIs.

///\ingroup ADAPTERAPI
///\defgroup STEREO3D Stereo3D APIs
/// This group describes the Stereo3D APIs.

///\ingroup ADL_API
///\defgroup DISPLAYAPI Display Related APIs
/// This group outlines all display related APIs.

///\ingroup DISPLAYAPI
///\defgroup DISPLAY Miscellaneous Display APIs
/// This group outlines the Miscellaneous Display related APIs.

///\ingroup DISPLAYAPI
///\defgroup DISPLAYMNGR Eyefinity APIs
/// This group outlines the Displays Manager related APIs.

/// \ingroup DISPLAYAPI
/// \defgroup COLOR Color related APIs
/// This group describes the Color related APIs

///\ingroup DISPLAYAPI
/// \defgroup T_OVERRIDE Timing Override APIs
/// This group describes the Timing Overide related APIs

/// \ingroup DISPLAYAPI
/// \defgroup CUSTOMIZED Customized Modes APIs
/// This group describes the APIs related to Customized modes

/// \ingroup DISPLAYAPI
/// \defgroup OVERSCAN Overscan/Underscan APIs
/// This group outlines Overscan and Underscan related APIs.

/// \ingroup DISPLAYAPI
///\defgroup OVERLAY Overlay APIs
/// This group outlines all Overlay related APIs.

/// \ingroup DISPLAYAPI
///\defgroup POWERX PowerXpress APIs
/// This group outlines PowerXpress Related APIs.

/// \ingroup DISPLAYAPI
///\defgroup VIEWPORT ViewPort APIs
/// This group outlines ViewPort Related APIs.

/// \ingroup ADL_API
///\defgroup SPECIALDISP DFP, TV, Component Video APIs
/// This group outlines DFP, TV and Component Video related APIs.

/// \ingroup SPECIALDISP
///\defgroup DFP Digital Flat Panel APIs
/// This group outlines all digital flat panel related APIs.

/// \ingroup SPECIALDISP
///\defgroup TV TV APIs
/// This group outlines all television related APIs.

/// \ingroup SPECIALDISP
///\defgroup CV Component Video APIs
/// This group outlines all component video related APIs.

/// \ingroup ADL_API
///\defgroup OVERDRIVE5 Overdrive5 APIs
/// This group outlines all Overdrive5 related APIs

/// \ingroup ADL_API
///\defgroup I2CDDCEDID I2C, DDC and EDID APIs
/// This group outlines I2C, DDC and EDID related APIs.

/// \ingroup ADL_API
///\defgroup WORKSTATION Workstation APIs
/// This group outlines all workstation related APIs.

/// \ingroup ADL_API
///\defgroup APPPROFILES Application Profiles APIs
/// This group outlines all Application Profiles APIs.

/// \ingroup ADL_API
///\defgroup LINUX Linux Specific APIs
/// This group outlines Linux specific APIs.


#include "adl_sdk.h"
#include "amd_only/amd_structures.h"

#include "adapter.h"
#include "display.h"
#include "workstation.h"
#include "displaysmanager.h"


#ifndef EXPOSED
#define EXPOSED
#endif /* EXPOSED */


///\addtogroup MAINAPI
// @{

///
/// \brief Function to initialize the ADL interface. This function should be called first.
/// 
/// This function initializes the ADL library. It also initializes global pointers and, at the same time, calls the ADL_Main_Control_Refresh function.
/// \platform 
/// \ALL
/// \param[in] callback: The memory allocation function for memory buffer allocation. This must be provided by the user.
/// \param[in] iEnumConnectedAdapters: Specify a value of 0 to retrieve adapter information for all adapters that have ever been present in the system. Specify a value of 1 to retrieve adapter information only for adapters that are physically present and enabled in the system.
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Main_Control_Create ( ADL_MAIN_MALLOC_CALLBACK callback, int iEnumConnectedAdapters );

///
/// \brief Function to refresh adapter information. This function generates an adapter index value for all logical adapters that have ever been present in the system.
/// 
/// This function updates the adapter information based on the logical adapters currently in the system. The adapter index and UDID mappings remain unchanged for each refresh call. 
/// \platform 
/// \ALL
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Main_Control_Refresh ();

///
/// \brief Function to destroy ADL global pointers. This function should be called last.
/// 
/// All ADL global buffers and resources are released after this function is called.
/// \platform 
/// \ALL
/// \return If the function succeeds, the return value is \ref ADL_OK. Otherwise the return value is an ADL error code. \ref define_adl_results
int EXPOSED ADL_Main_Control_Destroy ();

// @}

#endif /* ADL_H_ */
