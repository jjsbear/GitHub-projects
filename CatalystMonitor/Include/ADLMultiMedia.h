#pragma once


#include "adl_sdk.h"
#include ".\amd_only\amd_adl.h"
#include ".\customer\oem_structures.h"
#include "stdio.h"

typedef int ( *ADL_MAIN_CONTROL_CREATE )(ADL_MAIN_MALLOC_CALLBACK, int );
typedef int ( *ADL_MAIN_CONTROL_REFRESH )();
typedef int ( *ADL_MAIN_CONTROL_DESTROY )();
typedef int ( *ADL_FLUSH_DRIVER_DATA ) ();
typedef int ( *ADL_ADAPTER_NUMBEROFADAPTERS_GET ) ( int* );
typedef int ( *ADL_ADAPTER_ADAPTERINFO_GET ) ( LPAdapterInfo, int );
typedef int ( *ADL_ADAPTER_ACTIVE_GET ) ( int, int* );
typedef int ( *ADL_DISPLAY_COLORCAPS_GET ) ( int, int, int *, int * );
typedef int ( *ADL_DISPLAY_COLOR_GET ) ( int, int, int, int *, int *, int *, int *, int * );
typedef int ( *ADL_DISPLAY_COLOR_SET ) ( int, int, int, int );
typedef int ( *ADL_DISPLAY_DISPLAYINFO_GET ) ( int, int *, ADLDisplayInfo **, int );
typedef int ( *ADL_DISPLAY_DISPLAYMAPCONFIG_GET ) (int, int*, ADLDisplayMap** lppDisplayMap, int* lpNumDisplayTarget, ADLDisplayTarget**, int);
typedef int ( *ADL_DISPLAY_MODES_GET ) ( int, int, int *, ADLMode **);
typedef int ( *ADL_DISPLAY_MODES_SET ) ( int, int, int, ADLMode *);

typedef int ( * ADL_ADAPTER_NUMBEROFACTIVATABLESOURCES_GET ) ( int, int *, ADLActivatableSource **);
typedef int ( * ADL_DISPLAY_POSSIBLEMODE_GET ) (int, int*, ADLMode** lppModes);
typedef int ( * ADL_DISPLAY_PIXELCLOCKCAPS_GET) (int iAdapterIndex, int iDisplayIndex, ADLPixelClockCaps * lpPixelClockCaps);
typedef int ( * ADL_DISPLAY_CURRENTPIXELCLOCK_GET )(int iAdapterIndex, int iDisplayIndex, ADLCurrentPixelClock * lpCurrentPixelClock);
typedef int ( * ADL_DISPLAY_PIXELCLOCKALLOWABLERANGE_SET )(int iAdapterIndex, int iDisplayIndex, ADLPixelClockRange * lpPixelClockRange);
typedef int ( * ADL_DISPLAY_EDIDDATA_GET )(int iAdapterIndex, int iDisplayIndex, ADLDisplayEDIDData * lpEDIDData);
typedef int ( * ADL_GRAPHICS_VERSIONS_GET ) ( ADLVersionsInfo * lpVersionsInfo);
typedef int ( * ADL_MMD_FEATURELIST_GET)  ( int , ADLFeatureName ** , int *);
typedef int ( * ADL_MMD_FEATURES_CAPS)  ( int ,  ADLFeatureCaps ** , int *);
typedef int ( * ADL_MMD_FEATUREVALUES_GET)  ( int ,  ADLFeatureValues ** , int *);
typedef int ( * ADL_MMD_FEATUREVALUES_SET)  ( int ,  ADLFeatureValues * , int, int );


class ADLMultiMedia
{
public:
    ADLMultiMedia();
    virtual ~ADLMultiMedia();

    int  ADLActiveAdapterGet(int* nIndex);
    int  GetAdapterNum();
    bool GetAdapterInfo(LPAdapterInfo lpAdapterInfo, int nSize);
    int  GetAdapterActive(int nAdapterIndex);
    int  GetDisplayInfo(int nAdapterIndex, int* pDisplayNumber, LPADLDisplayInfo* lppAdlDisplayInfo);
    int  GetEDIDData(int nAdapterIndex, int nDisplayIndex, ADLDisplayEDIDData* lpEDIDData);
	int  GetDisplayMode(int nAdapterIndex, int nDisplayIndex, int* pNumber, ADLMode** ppMode);
	int  SetDisplayMode(int nAdapterIndex, int nDisplayIndex, int number, ADLMode* pMode);
    int  GetDisplayColor(int nAdapterIndex, int nDisplayIndex, int nColorType, int* pCurrent, int* pDefault, int* pMin, int* pMax, int* pStep);
    int  SetDisplayColor(int nAdapterIndex, int nDisplayIndex, int nColorType, int nCurrent);

    bool ADLFeatureCaps(LPADLFeatureCaps& lpAdlFeatureCaps, int* pFeatureCount);
    bool ADLFeatureValuesGet(int adapter, LPADLFeatureValues& lpAdlFeatureValues, int* nFeatureCount);
    bool ADLFeatureValuesSet(LPADLFeatureValues& lpAdlFeatureValues, int nFeatureCount);
    void DoTest();

    static void* __stdcall ADL_Main_Memory_Alloc ( int iSize );
    static void  __stdcall ADL_Main_Memory_Free ( void** lpBuffer );

private:
    HINSTANCE m_hDLL;		// Handle to DLL
    int m_nAdapterIndex;

    ADL_MAIN_CONTROL_CREATE							ADL_Main_Control_Create;
    ADL_MAIN_CONTROL_REFRESH						ADL_Main_Control_Refresh;
    ADL_MAIN_CONTROL_DESTROY						ADL_Main_Control_Destroy;
    ADL_FLUSH_DRIVER_DATA                           ADL_Flush_Driver_Data;
    ADL_ADAPTER_NUMBEROFADAPTERS_GET				ADL_Adapter_NumberOfAdapters_Get;
    ADL_ADAPTER_ADAPTERINFO_GET						ADL_Adapter_AdapterInfo_Get;
    ADL_ADAPTER_ACTIVE_GET							ADL_Adapter_Active_Get;
    ADL_DISPLAY_COLORCAPS_GET						ADL_Display_ColorCaps_Get;
    ADL_DISPLAY_COLOR_GET							ADL_Display_Color_Get;
    ADL_DISPLAY_COLOR_SET							ADL_Display_Color_Set;
    ADL_DISPLAY_DISPLAYINFO_GET						ADL_Display_DisplayInfo_Get;
    ADL_DISPLAY_DISPLAYMAPCONFIG_GET				ADL_Display_DisplayMapConfig_Get;
	ADL_DISPLAY_MODES_GET							ADL_Display_Modes_Get;
	ADL_DISPLAY_MODES_SET							ADL_Display_Modes_Set;

	ADL_ADAPTER_NUMBEROFACTIVATABLESOURCES_GET      ADL_Adapter_NumberOfActivatableSources_Get;
    ADL_DISPLAY_POSSIBLEMODE_GET					ADL_Display_PossibleMode_Get;
	ADL_DISPLAY_PIXELCLOCKCAPS_GET					ADL_Display_PixelClockCaps_Get;
	ADL_DISPLAY_CURRENTPIXELCLOCK_GET				ADL_Display_CurrentPixelClock_Get;
	ADL_DISPLAY_PIXELCLOCKALLOWABLERANGE_SET	    ADL_Display_PixelClockAllowableRange_Set;
    ADL_DISPLAY_EDIDDATA_GET                        ADL_DISPLAY_EDIDData_Get;
	ADL_GRAPHICS_VERSIONS_GET						ADL_Graphics_Versions_Get;

    ADL_MMD_FEATURELIST_GET             ADL_MMD_FeatureList_Get;
    ADL_MMD_FEATURES_CAPS               ADL_MMD_Features_Caps;
    ADL_MMD_FEATUREVALUES_GET           ADL_MMD_FeatureValues_Get;
    ADL_MMD_FEATUREVALUES_SET           ADL_MMD_FeatureValues_Set;

};

