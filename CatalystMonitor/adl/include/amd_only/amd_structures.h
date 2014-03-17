///
///  Copyright (c) 2008 - 2009 Advanced Micro Devices, Inc.
 
///  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
///  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

/// \file amd_structures.h
/// \brief This file contains the structure declarations used by the internal AMD Driver Library interfaces for \ALL platforms.
///
/// All data structures used in ADL internal interfaces should be defined in this header file.
///

#ifndef AMD_STRUCTURES_H_
#define AMD_STRUCTURES_H_

#ifndef ADL_DEFINES_H_
#include "adl_defines.h"
#endif

/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Structure containing information about GPU.
///
/// This structure is used to store information about GPU.
/// This structure is used by internal ADL implementation.
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADLGPUInfo
{
/// The persistent GPU Index.
	int iGPUIndex;
/// The bus number associated with this GPU.
	int iBusNumber;
/// The number of logical adapters on this GPU.
	int iNumAdapters;
/// The logical adapters of this GPU.
	int* lpAdapterTable;
} ADLGPUInfo, *LPADLGPUInfo;


/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Structure containing information about the ASIC.
///
/// This structure is used to store various information about the ASIC.  This 
/// information can be returned to the user.
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADLASICInfo
{
    long long iMemorySize;        	///< Memory size in bytes.
    int iCoreClock;          		///< Core clock in 10 KHz.
    int iMemoryClock;        		///< Memory clock in 10 KHz.
    char strMemoryType[ADL_MAX_PATH];  	///< Memory type in string.
} ADLASICInfo, *LPADLASICInfo;

/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Structure containing information about the Chipset.
///
/// This structure is used to store various information about the Chipset.  This 
/// information can be returned to the user.
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADLChipSetInfo
{
    int iBusType; 		///< Bus type.
    int iMaxPCIELaneWidth; 	///< Number of PCIE lanes.
	int iCurrentPCIELaneWidth;  ///< Current PCIE Lane Width
    int iSupportedAGPSpeeds;    ///< Bit mask or AGP transfer speed.
	int iCurrentAGPSpeed;       ///< Current AGP speed
} ADLChipSetInfo, *LPADLChipSetInfo;

/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Structure containing information about lcd refresh rate capability.
///
/// This structure is used to store the information about LCD refresh rate capability for the adapter.
/// This structure is used by the ADL_Display_LCDRefreshRateCapability_Get() function.
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADLLcdRefreshRateCap
{
    int iSize;
    int iDefaultRefreshRate;
    int iNumLowRefreshRates;
    int iLowRefreshRate1;
    int iLowRefreshRate2;
    int iLowRefreshRate3;
    int iLowRefreshRate4;
    int iCapsFlag;
} ADLLcdRefreshRateCap;

/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Structure containing information about LCD refresh rate options.
///
/// This structure is used to store the information about LCD refresh rate options for the adapter.
/// This structure is used by the ADL_Display_LCDRefreshRateOptions_Get() and ADL_Display_LCDRefreshRateOptions_Set() functions.
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADLLcdRefreshRateOptions
{
    int iSize;
    int iOptions;
    int iReserved1;
    int iReserved2;
} ADLLcdRefreshRateOptions;



/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Structure containing information about Target Display timing information.
/// This structure is used by the ADL_Display_TargetTiming_Get() functions
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADLDisplayTargetTiming
{
    int iSize;
	unsigned int horizontalTotal;
	unsigned int verticalTotal;
	unsigned int horizontalActive;
	unsigned int verticalActive;
	unsigned int refreshRateNumerator;
	unsigned int refreshRateDenominator;
	unsigned int pixelClockInKHz;
} ADLDisplayTargetTiming;


/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Structure containing information about the Chipset.
///
/// This structure is used to store various information about the Chipset.  This 
/// information can be returned to the user.
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADLSWInfo
{
	char strDrvVer[ADL_MAX_PATH]; 	 	///< Driver release version (e.g., 8.47.2).
	char strOGLVendor[ADL_MAX_PATH]; 	///< Vendor name (e.g.,. Advanced Micro Devices).
	char strOGLRenderer[ADL_MAX_PATH]; 	///< OGL renderer (e.g., AMD FirePro V7200).
	char strOGLVersion[ADL_MAX_PATH]; 	///< OGL version (e.g., 2.1.7410 FireGL Release).
} ADLSWInfo, *LPADLSWInfo;


/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Structure containing the display mode definition used per controller.
///
/// This structure is used to store the display mode definition used per controller.
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADL_DL_DISPLAY_MODE
{
   int  iPelsHeight;                      // Vertical resolution (in pixels).
   int  iPelsWidth;                       // Horizontal resolution (in pixels).
   int  iBitsPerPel;                      // Color depth.
   int  iDisplayFrequency;                // Refresh rate.
} ADL_DL_DISPLAY_MODE;

/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Structure containing detailed timing parameters.
///
/// This structure is used to store the detailed timing parameters.
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADL_DL_DETAILEDTIMING
{
     int   iSize;							/// Size of the structure.
     short sTimingFlags;				/// Timing flags. ADL_DL_TIMINGFLAG_xx.
     short sHTotal;						/// Total width (columns).
     short sHDisplay;					/// Displayed width.
     short sHSyncStart;				/// Horizontal sync signal offset.
     short sHSyncWidth;				/// Horizontal sync signal width.
     short sVTotal;						/// Total height (rows).
     short sVDisplay;					/// Displayed height.
     short sVSyncStart;				/// Vertical sync signal offset.
     short sVSyncWidth;				/// Vertical sync signal width.
     short sPixelClock;				/// Pixel clock value.
     short sHOverscanRight;		/// Overscan right.
     short sHOverscanLeft;			/// Overscan left.
     short sVOverscanBottom;	/// Overscan bottom.
     short sVOverscanTop;			/// Overscan top.
     short sOverscan8B;
     short sOverscanGR;
} ADL_DL_DETAILEDTIMING;

/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Structure containing display mode information.
///
/// This structure is used to store the display mode information.
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADL_DL_DISPLAYMODEINFO
{
  int  iTimingStandard;				/// Timing standard of the current mode.
  int  iPossibleStandard;			/// Applicable timing standards for the current mode.
  int  iRefreshRate;					/// Refresh rate factor.
  int  iPelsWidth;						/// Num of pixels in row.
  int  iPelsHeight;						/// Num of pixels in column.
  ADL_DL_DETAILEDTIMING  sDetailedTiming; // Detailed timing parameters.
} ADL_DL_DISPLAYMODEINFO;


/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about latest driver supported Resize and Rotate release
///
/// This structure is used to store the latest driver supported Resize and Rotate release numbers
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADLXInfoData
{
    int iRandRmajor;            ///< Latest Resize and Rotate version that driver supports, Major portion
    int iRandRminor;            ///< Latest Resize and Rotate version that driver supports, Minor portion
} ADLXInfoData, *LPADLXInfoData; 



/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing additional information about the ASIC memory
///
/// This structure is used to store additional information about the ASIC memory.  This
/// information can be returned to the user.
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADLMemoryInfo2
{
	/// Memory size in bytes.
	long long iMemorySize;
	/// Memory type in string.
	char strMemoryType[ADL_MAX_PATH];
	/// Highest default performance level Memory bandwidth in Mbytes/s
	long long iMemoryBandwidth;
	/// HyperMemory size in bytes.
	long long iHyperMemorySize;

	/// Invisible Memory size in bytes.
	long long iInvisibleMemorySize;
	/// Visible Memory size in bytes.
	long long iVisibleMemorySize;
} ADLMemoryInfo2, *LPADLMemoryInfo2;


/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about association between display and audio endpoint
///
/// This structure is used to store display and audio endpoint association information
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct AudioEndPointAssociationInfo
{
	/// Display Index
	unsigned long DisplayIndex;
	/// PCI Bus number
	unsigned Bus          : 8;
	/// Device number
	unsigned Device       : 5;
	/// Function number
	unsigned Function     : 3;
	/// Reserved bits for possible future use. App can ignore this field for now
	unsigned Reserved     : 16;
} AudioEndPointAssociationInfo, *LPAudioEndPointAssociationInfo;

/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about the overlap offset info for all the displays for each SLS mode.
///
/// This structure is used to store the no. of overlapped modes for each SLS Mode once user finishes the configuration from Overlap Widget
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADLSLSOverlappedMode
{
	/// the SLS mode for which the overlap is configured
	ADLMode SLSMode;
	/// the number of target displays in SLS.
	int iNumSLSTarget;
    /// the first target array index in the target array
	int iFirstTargetArrayIndex;
}ADLSLSTargetOverlap, *LPADLSLSTargetOverlap;

/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about the Linux X screen information.
///
/// This structure is used to store the current screen number, linked xscreen number and xorg.conf ID name assoicated with an adapter index.
///
/// If the current X screen number is set (not -1), then this indicates that the adapter has control over that XScreen. The adapter
/// is able to change display, desktop and OGL related settings associated with the XScreen.
///
/// If the linked X screen number is set (not -1), then this indicates that the adapter is being used in a supporting role for that XScreen.
/// In a supporting role, the current adapter only has partial control, as indicated by \ref ADL_Adapter_ConfigureState_Get
///
/// This structure is used for \ref ADL_Adapter_XScreenInfo_GetR2
///
/// Note: It is possible that an adapter can have a valid current and linked XScreen.
///
/// This structure is updated during ADL_Main_Control_Refresh or ADL_ScreenInfo_Update.
/// Note:  This structure should be used in place of iXScreenNum and strXScreenConfigName in AdapterInfo as they will be
/// deprecated.
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
#if defined (LINUX)
typedef struct XScreenInfoR2
{
/// Current X screen number that the adapter controls.
	int iXScreenNum;
/// Linked X screen number that the adapter is associated with.
	int iLinkedXScreenNum;
/// Internal x config file screen identifier name.
    char strXScreenConfigName[ADL_MAX_PATH];
} XScreenInfoR2, *LPXScreenInfoR2;
#endif /* (LINUX) */

///\brief Structure containing ECC statistics namely SEC counts and DED counts
/// // Single error count - count of errors that can be corrected 
/// This structure is used to store information about the SEC (count of errors that can be corrected)
/// & DED(count of errors that cannot be corrected) 
/// \nosubgrouping

////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _ADLECCData
{
	int iSec; // Single error count - count of errors that can be corrected 
	int iDed; // Double error detect - count of errors that cannot be corrected

} ADLECCData;

////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about SDIData 
///This structure is used to store information about the state of the SDI whether it is on
///or off and the current size of the segment or aperture size.
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADLSDIData
{
/// The SDI state, ADL_SDI_ON or ADL_SDI_OFF, for the current SDI mode
int iSDIState;
/// Size of the memory segment for SDI (in MB).
int iSizeofSDISegment;         
} ADLSDIData, *LPADLSDIData;

/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief ADL Structure for RGBTRPL16
///
/// ADLRGBTRPL16 structure
/// \nosubgrouping
/////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADLRGBTRPL16
{
  unsigned short rgbtRed;
  unsigned short rgbtGreen;
  unsigned short rgbtBlue;
  unsigned short reserved;
}ADLRGBTRPL16, *LPADLRGBTRPL16;

/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief ADL Structure for CONTROLLERGAMMA
///
/// CONTROLLERGAMMA structure
/////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADLCONTROLLERGAMMA16
{
  unsigned long ulSize;
  ADLRGBTRPL16 triGamma[256];
  unsigned long ulFlags;
}ADLCONTROLLERGAMMA16, *LPADLCONTROLLERGAMMA16;

/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Structure containing extended information about the graphics adapter
///
/// This structure is used to store extended information about the graphics adapter, not
/// already being returned by \ref AdapterInfo
/// NOTE: This structure may be extended in future release of ADL. As such,
/// to maintain backwards compatibility, the appropriate bit must be checked in the iFlag
/// member before accessing the actual member variable. If the bit is missing then ADL
/// may not have returned a version of this structure that contains that member variable
/// (i.e. ADL installed on the system is an older version than the one the calling application
/// was compiled against).
/// \nosubgrouping
/////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _AdapterExtInfo
{
/// The size of this structure, in bytes
long long iSize;
/// Which bits in the iFlags are valid
long long iValidBits;
/// Indicates which member in this structure has valid information
long long iFlag;
/// The maximum allowed surface width, in pixels, for this adapter
int iMaxSurfaceWidth;
/// The maximum allowed surface height, in pixels, for this adapter
int iMaxSurfaceHeight;
} AdapterExtInfo, *LPAdapterExtInfo;

/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about Overdrive 6 clock range
///
/// This structure is used to store information about Overdrive 6 clock range
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADLOD6ParameterRange
{
    /// The starting value of the clock range
    int 	iMin;
    /// The ending value of the clock range
    int 	iMax;	
    /// The minimum increment between clock values
    int 	iStep;	

} ADLOD6ParameterRange;

/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about Overdrive 6 performance level.
///
/// This structure is used to store information about Overdrive 6 performance level.
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADLOD6PerformanceLevel
{
    /// Engine clock.
    int iEngineClock;
    /// Memory clock.
    int iMemoryClock;

} ADLOD6PerformanceLevel;

/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about Overdrive 6 capabilities
///
/// This structure is used to store information about Overdrive 6 capabilities
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADLOD6Capabilities
{
    /// Contains a bitmap of the OD6 capability flags
    int 	iCapabilities;
    /// Contains a bitmap indicating the performance levels
    /// supported by OD6
    int 	iSupportedStates;
    /// Number of performance levels
    int     iNumberOfPerformanceLevels;
    /// Contains the hard limits of the sclk range.  Overdrive
    /// clocks cannot be set outside this range.
    ADLOD6ParameterRange 	sEngineClockRange;
    /// Contains the hard limits of the mclk range.  Overdrive
    /// clocks cannot be set outside this range.
    ADLOD6ParameterRange 	sMemoryClockRange;

    /// Value for future extension
    int     iExtValue;
    /// Mask for future extension
    int     iExtMask;

} ADLOD6Capabilities;

/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about Overdrive 6 performance level
///
/// This structure is used to store information about Overdrive 6 performance level
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADLOD6StateInfo
{
    /// Number of performance levels in this state
    int     iNumberOfPerformanceLevels;

    /// Value for future extension
    int     iExtValue;
    /// Mask for future extension
    int     iExtMask;

    /// Variable-sized array of performance levels. 
    /// The number of elements in the array is specified by iNumberofPerformanceLevels.
    ADLOD6PerformanceLevel aLevels [1];	

} ADLOD6StateInfo;

/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about Overdrive 6 current status
///
/// This structure is used to store information about Overdrive 6 current status
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADLOD6CurrentStatus
{
    /// Current engine clock
    int 	iEngineClock;
    /// Current memory clock
    int 	iMemoryClock;
    /// Current GPU activity in percent
    int 	iActivityPercent;
    /// Current DPM level
    int 	iCurrentPerformanceLevel;
    /// Current PCI-E bus speed
    int 	iCurrentBusSpeed;
    /// Current PCI-E bus # of lanes
    int 	iCurrentBusLanes;
    /// Maximum possible PCI-E bus # of lanes
    int 	iMaximumBusLanes;

    /// Value for future extension
    int     iExtValue;
    /// Mask for future extension
    int     iExtMask;

} ADLOD6CurrentStatus;

/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about Overdrive 6 thermal contoller capabilities
///
/// This structure is used to store information about Overdrive 6 thermal controller capabilities
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADLOD6ThermalControllerCaps
{
    /// Contains a bitmap of thermal controller capability flags
    int 	iCapabilities;
    /// Minimum fan speed expressed as a percentage
    int 	iFanMinPercent;
    /// Maximum fan speed expressed as a percentage
    int 	iFanMaxPercent;
    /// Minimum fan speed expressed in revolutions-per-minute
    int 	iFanMinRPM;
    /// Maximum fan speed expressed in revolutions-per-minute
    int 	iFanMaxRPM;

    /// Value for future extension
    int     iExtValue;
    /// Mask for future extension
    int     iExtMask;

} ADLOD6ThermalControllerCaps;

/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about Overdrive 6 fan speed information
///
/// This structure is used to store information about Overdrive 6 fan speed information
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADLOD6FanSpeedInfo
{
    /// Contains a bitmap of the valid fan speed type flags
    int 	iSpeedType;
    /// Contains current fan speed in percent (if valid flag exists in iSpeedType)
    int 	iFanSpeedPercent;
    /// Contains current fan speed in RPM (if valid flag exists in iSpeedType)
    int	    iFanSpeedRPM;

    /// Value for future extension
    int     iExtValue;
    /// Mask for future extension
    int     iExtMask;

} ADLOD6FanSpeedInfo;

/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about Overdrive 6 fan speed value
///
/// This structure is used to store information about Overdrive 6 fan speed value
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADLOD6FanSpeedValue
{
    /// Indicates the units of the fan speed
    int 	iSpeedType;
    /// Fan speed value (units as indicated above)
    int 	iFanSpeed;

    /// Value for future extension
    int     iExtValue;
    /// Mask for future extension
    int     iExtMask;

} ADLOD6FanSpeedValue;

/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about Overdrive 6 Power Control settings
///
/// This structure is used to store information about Overdrive 6 Power Control settings
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADLOD6PowerControlInfo 
{
    /// The minimum power control value
    int 	iMinValue;
    /// The maximum power control value
    int 	iMaxValue;
    /// The minimum difference between power control values
    int 	iStepValue;  

    /// Value for future extension
    int     iExtValue;
    /// Mask for future extension
    int     iExtMask;

} ADLOD6PowerControlInfo;



/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about enhenced scaling configuration
///
/// This structure is used to set v/h taps and v/h shapness. The caller should ensure that display clock is enough for the requested configuration
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADLMMDisplayScaling
{
    /// Display image width (destination)
    int 	iWidth;
    /// Display image height (destination)
    int 	iHeight;
    /// The requested number of hor taps
    int 	ihTaps;  
    /// The requested number of vert taps
    int 	ivTaps;  
    ///horizontal sharpness
    int 	ihorSharpness;  
    ///vertical sharpness
    int 	ivertSharpness;  

} ADLMMDisplayScaling;

/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about an controller mode
///
/// This structure is used to store information of an controller mode
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADLAdapterCaps
{
	/// AdapterID for this adapter
	int iAdapterID;
	/// Number of controllers for this adapter
	int iNumControllers;
	/// Number of displays for this adapter
	int iNumDisplays;
	/// Number of overlays for this adapter
	int iNumOverlays;
	/// Number of GLSyncConnectors
	int iNumOfGLSyncConnectors;
	/// The bit mask identifies the adapter caps
	int iCapsMask;
	/// The bit identifies the adapter caps \ref define_adapter_caps
	int iCapsValue;
}ADLAdapterCaps;
   

/////////////////////////////////////////////////////////////////////////////////////////////
///\brief Structure containing information about adapter limitation
///
/// This structure is used to store the adapter limitation. For example, the maxium number of dispalys in one clone
/// desktop
/// \nosubgrouping
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ADLAdapterLimitationCaps
{
	/// The number of activatable Sources.
	/// based on controllers and connected displays
	int iNumActivatableSources; 
	/// The number of activatable desktops in the GPU. 
	int iNumActivatableDesktops; 
	/// The number of activatable displays in one desktop.
	/// The max number of displays ine one clone.
	int iNumActivatableDisplaysInOneDesktops; 
	/// Revered 
	int iMask;
	/// Revered
	int iValue;

}ADLAdapterLimitationCaps;

#endif /* AMD_STRUCTURES_H_ */

