#include "stdafx.h"
#include "ADLMultiMedia.h"

void* __stdcall ADLMultiMedia::ADL_Main_Memory_Alloc ( int iSize )
{
    void* lpBuffer = malloc ( iSize );
    return lpBuffer;
}

void __stdcall ADLMultiMedia::ADL_Main_Memory_Free ( void** lpBuffer )
{
    if ( NULL != *lpBuffer )
    {
        free ( *lpBuffer );
        *lpBuffer = NULL;
    }
}

ADLMultiMedia::ADLMultiMedia()
{
    char sztemp[20];
    sprintf_s(sztemp, "atiadlxx.dll");
    m_hDLL = LoadLibraryA(sztemp);
    if (m_hDLL == NULL)
    {
        // A 32 bit calling application on 64 bit OS will fail to LoadLIbrary.
        // Try to load the 32 bit library (atiadlxy.dll) instead
        sprintf_s(sztemp, "atiadlxy.dll");
        m_hDLL = LoadLibraryA(sztemp);
    }

    if (m_hDLL == NULL)
        return;

    ADL_Main_Control_Create = (ADL_MAIN_CONTROL_CREATE)GetProcAddress(m_hDLL,"ADL_Main_Control_Create");
    ADL_Main_Control_Refresh = (ADL_MAIN_CONTROL_REFRESH)GetProcAddress(m_hDLL,"ADL_Main_Control_Refresh");
    ADL_Flush_Driver_Data = (ADL_FLUSH_DRIVER_DATA)GetProcAddress(m_hDLL,"ADL_Flush_Driver_Data");
    ADL_Adapter_NumberOfAdapters_Get = (ADL_ADAPTER_NUMBEROFADAPTERS_GET)GetProcAddress(m_hDLL,"ADL_Adapter_NumberOfAdapters_Get");
    ADL_Adapter_AdapterInfo_Get = (ADL_ADAPTER_ADAPTERINFO_GET)GetProcAddress(m_hDLL,"ADL_Adapter_AdapterInfo_Get");
    ADL_Display_DisplayInfo_Get = (ADL_DISPLAY_DISPLAYINFO_GET)GetProcAddress(m_hDLL,"ADL_Display_DisplayInfo_Get");

    ADL_Adapter_Active_Get = (ADL_ADAPTER_ACTIVE_GET)GetProcAddress(m_hDLL,"ADL_Adapter_Active_Get");
    ADL_Display_DisplayMapConfig_Get = (ADL_DISPLAY_DISPLAYMAPCONFIG_GET)GetProcAddress(m_hDLL,"ADL_Display_DisplayMapConfig_Get");
    ADL_Display_Modes_Get = (ADL_DISPLAY_MODES_GET)GetProcAddress(m_hDLL,"ADL_Display_Modes_Get");
    ADL_Display_Modes_Set = (ADL_DISPLAY_MODES_SET)GetProcAddress(m_hDLL,"ADL_Display_Modes_Set");

    ADL_Adapter_NumberOfActivatableSources_Get = (ADL_ADAPTER_NUMBEROFACTIVATABLESOURCES_GET)GetProcAddress(m_hDLL,"ADL_Adapter_NumberOfActivatableSources_Get");
    ADL_Display_PossibleMode_Get = (ADL_DISPLAY_POSSIBLEMODE_GET)GetProcAddress(m_hDLL,"ADL_Display_PossibleMode_Get");
    ADL_Display_PixelClockCaps_Get = (ADL_DISPLAY_PIXELCLOCKCAPS_GET)GetProcAddress(m_hDLL,"ADL_Display_PixelClockCaps_Get");
    ADL_Display_ColorCaps_Get = (ADL_DISPLAY_COLORCAPS_GET)GetProcAddress(m_hDLL,"ADL_Display_ColorCaps_Get");
    ADL_Display_Color_Get = (ADL_DISPLAY_COLOR_GET)GetProcAddress(m_hDLL,"ADL_Display_Color_Get");
    ADL_Display_Color_Set = (ADL_DISPLAY_COLOR_SET)GetProcAddress(m_hDLL,"ADL_Display_Color_Set");
    ADL_DISPLAY_EDIDData_Get = (ADL_DISPLAY_EDIDDATA_GET)GetProcAddress(m_hDLL,"ADL_Display_EdidData_Get");

    ADL_Main_Control_Destroy = (ADL_MAIN_CONTROL_DESTROY)GetProcAddress(m_hDLL,"ADL_Main_Control_Destroy");
    ADL_Graphics_Versions_Get = (ADL_GRAPHICS_VERSIONS_GET) GetProcAddress(m_hDLL,"ADL_Graphics_Versions_Get");
    
    ADL_MMD_FeatureList_Get = (ADL_MMD_FEATURELIST_GET) GetProcAddress(m_hDLL,"ADL_MMD_FeatureList_Get");
    ADL_MMD_Features_Caps = (ADL_MMD_FEATURES_CAPS) GetProcAddress(m_hDLL,"ADL_MMD_Features_Caps");
    ADL_MMD_FeatureValues_Get = (ADL_MMD_FEATUREVALUES_GET) GetProcAddress(m_hDLL,"ADL_MMD_FeatureValues_Get");
    ADL_MMD_FeatureValues_Set = (ADL_MMD_FEATUREVALUES_SET) GetProcAddress(m_hDLL,"ADL_MMD_FeatureValues_Set");


    if ( NULL == ADL_Main_Control_Create ||
		NULL == ADL_Main_Control_Refresh ||
		NULL == ADL_Adapter_NumberOfAdapters_Get ||
		NULL == ADL_Adapter_AdapterInfo_Get ||
		NULL == ADL_Display_DisplayInfo_Get ||
		NULL == ADL_Adapter_Active_Get || 
		NULL == ADL_Display_DisplayMapConfig_Get || 
		NULL == ADL_Display_Modes_Get || 
		NULL == ADL_Adapter_NumberOfActivatableSources_Get ||
		NULL == ADL_Display_PossibleMode_Get || 
		NULL == ADL_Display_PixelClockCaps_Get || 
		NULL == ADL_Display_ColorCaps_Get || 
		NULL == ADL_Display_Color_Get || 
		NULL == ADL_Display_Color_Set || 
		NULL == ADL_Main_Control_Destroy || 
		NULL == ADL_Graphics_Versions_Get )
	   return;

    // The second parameter is 1, which means:
    // retrieve adapter information only for adapters that are physically present and enabled in the system
    int ADL_Err = ADL_Main_Control_Create(ADL_Main_Memory_Alloc, 1);
    if (ADL_OK != ADL_Err )
        return;

    int nAdapterCount = ADLActiveAdapterGet(&m_nAdapterIndex);
    return;
}

ADLMultiMedia::~ADLMultiMedia ()
{
    ADL_Main_Control_Destroy();
    FreeLibrary(m_hDLL);
}

int ADLMultiMedia::ADLActiveAdapterGet(int* pIndex)
{
    *pIndex = -1;
    int nCount = 0;
    if ( NULL != ADL_Adapter_NumberOfAdapters_Get )
    {
        int  iNumberAdapters = 0;
        ADL_Adapter_NumberOfAdapters_Get ( &iNumberAdapters );

        if ( 0 < iNumberAdapters )
        {
            LPAdapterInfo     lpAdapterInfo = NULL;
            lpAdapterInfo = (LPAdapterInfo)malloc ( sizeof (AdapterInfo) * iNumberAdapters );
            memset ( lpAdapterInfo,'\0', sizeof (AdapterInfo) * iNumberAdapters );

            // Get the AdapterInfo structure for all adapters in the system
            if ( NULL != ADL_Adapter_AdapterInfo_Get )
            {
                ADL_Adapter_AdapterInfo_Get (lpAdapterInfo, sizeof (AdapterInfo) * iNumberAdapters);

                for ( int i = 0; i < iNumberAdapters; i++ )
                {
                    int  iActive = 0;
                    int ADL_Err = ADL_Adapter_Active_Get (lpAdapterInfo[ i ].iAdapterIndex, &iActive );
		            if ( 1 == iActive && ADL_OK == ADL_Err)
                    {
                        nCount++;
                        if (*pIndex <= 0)
                            *pIndex = lpAdapterInfo[ i ].iAdapterIndex;
                    }
                }
            }
            ADL_Main_Memory_Free ( (void**)&lpAdapterInfo );
        }
    }
    return nCount;
}

int ADLMultiMedia::GetAdapterNum()
{
    if (ADL_Adapter_NumberOfAdapters_Get == NULL)
        return 0;

    int  iNumberAdapters = 0;
    ADL_Adapter_NumberOfAdapters_Get ( &iNumberAdapters );
    return iNumberAdapters;
}

bool ADLMultiMedia::GetAdapterInfo(LPAdapterInfo lpAdapterInfo, int nSize)
{
    if (ADL_Adapter_AdapterInfo_Get == NULL)
        return false;

    int nAdapterNumber = GetAdapterNum();
    ASSERT(nSize == nAdapterNumber*sizeof(AdapterInfo));

    ADL_Adapter_AdapterInfo_Get(lpAdapterInfo, nSize);
    return true;
}

int ADLMultiMedia::GetAdapterActive(int nAdapterIndex)
{
    if (ADL_Adapter_Active_Get == NULL)
        return -1;
    
    int nActive=0;
    ADL_Adapter_Active_Get(nAdapterIndex, &nActive);
    return nActive;
}

int ADLMultiMedia::GetDisplayInfo(int nAdapterIndex, int* pDisplayNumber, LPADLDisplayInfo* lppAdlDisplayInfo)
{
    if (ADL_Display_DisplayInfo_Get == NULL)
        return -1;

    return ADL_Display_DisplayInfo_Get(nAdapterIndex, pDisplayNumber, lppAdlDisplayInfo, 0);
}

int ADLMultiMedia::GetEDIDData(int nAdapterIndex, int nDisplayIndex, ADLDisplayEDIDData* lpEDIDData)
{
    if (ADL_DISPLAY_EDIDData_Get == NULL)
        return -1;

    return ADL_DISPLAY_EDIDData_Get(nAdapterIndex, nDisplayIndex, lpEDIDData);
}

int ADLMultiMedia::GetDisplayMode(int nAdapterIndex, int nDisplayIndex, int* pNumber, ADLMode** ppMode)
{
	if (ADL_Display_Modes_Get == 0)
		return -1;

	return ADL_Display_Modes_Get(nAdapterIndex, nDisplayIndex, pNumber, ppMode);
}

int ADLMultiMedia::SetDisplayMode(int nAdapterIndex, int nDisplayIndex, int number, ADLMode* pMode)
{
	if (ADL_Display_Modes_Set == 0)
		return -1;

	return ADL_Display_Modes_Set(nAdapterIndex, nDisplayIndex, number, pMode);
}

int ADLMultiMedia::GetDisplayColor(int nAdapterIndex, int nDisplayIndex, int nColorType, int* pCurrent, int* pDefault, int* pMin, int* pMax, int* pStep)
{
    if (ADL_Display_ColorCaps_Get==0 || ADL_Display_Color_Get==0)
        return -1;

    int nColorCaps=0, nValidBits=0;
    if (ADL_OK != ADL_Display_ColorCaps_Get( nAdapterIndex, nDisplayIndex, &nColorCaps, &nValidBits))
        return -1;

    nColorCaps &= nValidBits;
    if (nColorCaps & nColorType)
        return ADL_Display_Color_Get(nAdapterIndex, nDisplayIndex, nColorType, pCurrent, pDefault, pMin, pMax, pStep);
    return -1;
}

int ADLMultiMedia::SetDisplayColor(int nAdapterIndex, int nDisplayIndex, int nColorType, int nCurrent)
{
    if (ADL_Display_ColorCaps_Get==0 || ADL_Display_Color_Set==0)
        return -1;

    int nColorCaps=0, nValidBits=0;
    if (ADL_OK != ADL_Display_ColorCaps_Get( nAdapterIndex, nDisplayIndex, &nColorCaps, &nValidBits))
        return -1;

    nColorCaps &= nValidBits;
    if (nColorCaps & nColorType)
    {
        if ( ADL_OK != ADL_Display_Color_Set(nAdapterIndex, nDisplayIndex, nColorType, nCurrent))
            return -1;

        if (ADL_Flush_Driver_Data)
            return ADL_Flush_Driver_Data();
        else
            return ADL_OK;
    }
    return -1;
}

bool ADLMultiMedia::ADLFeatureCaps(LPADLFeatureCaps& lpAdlFeatureCaps, int* pFeatureCount)
{
    if (ADL_MMD_Features_Caps == NULL)
        return false;

    *pFeatureCount = 0;
    ADL_Main_Memory_Free ( (void**)&lpAdlFeatureCaps );
    ADL_MMD_Features_Caps(m_nAdapterIndex, &lpAdlFeatureCaps, pFeatureCount);
    return true;
}

bool ADLMultiMedia::ADLFeatureValuesGet(int adapter, LPADLFeatureValues& lpAdlFeatureValues, int* nFeatureCount)
{
    if (ADL_MMD_FeatureValues_Get == NULL)
        return false;

    *nFeatureCount = 0;
    ADL_Main_Memory_Free ( (void**)&lpAdlFeatureValues );
    ADL_MMD_FeatureValues_Get(adapter, &lpAdlFeatureValues, nFeatureCount);
    return true;
}

bool ADLMultiMedia::ADLFeatureValuesSet(LPADLFeatureValues& lpAdlFeatureValues, int nFeatureCount)
{
    if (ADL_MMD_FeatureValues_Set == NULL)
        return false;

     ADL_MMD_FeatureValues_Set(m_nAdapterIndex, lpAdlFeatureValues, nFeatureCount, 1);
     return true;
}


void ADLMultiMedia::DoTest()
{
#define TEST_CNT	5000 // loop number of times for testing an API

    LPAdapterInfo     lpAdapterInfo = NULL;
    LPADLDisplayInfo  lpAdlDisplayInfo = NULL;
    LPADLFeatureName    lpAdlFeatureName = NULL;
    LPADLFeatureCaps    lpAdlFeatureCaps = NULL;
    LPADLFeatureValues  lpAdlFeatureValues = NULL;

    int  i = 0, j = 0;
    int  ADL_Err = -1;
    int  iActive = 0;
    int  iNumberAdapters = 0;
    int  iAdapterIndex = 0;
    int  iDisplayIndex = 0;
    int  iNumDisplays = 0;
    int  iColorCaps = 0, iValidBits = 0;
    int  iCurrent= 0, iDefault= 0, iMin= 0, iMax= 0, iStep= 0;
    
	ADLPixelClockCaps		pcc;
	ADLCurrentPixelClock	cpc;
	ADLPixelClockRange		pcr;
	ADLVersionsInfo VersionsInfo;

    if (m_hDLL == NULL)
        return;

    if ( NULL == ADL_Main_Control_Refresh ||
		NULL == ADL_Adapter_NumberOfAdapters_Get ||
		NULL == ADL_Adapter_AdapterInfo_Get ||
		NULL == ADL_Display_DisplayInfo_Get ||
		NULL == ADL_Adapter_Active_Get || 
		NULL == ADL_Display_DisplayMapConfig_Get || 
		NULL == ADL_Display_Modes_Get || 
		NULL == ADL_Adapter_NumberOfActivatableSources_Get ||
		NULL == ADL_Display_PossibleMode_Get || 
		NULL == ADL_Display_PixelClockCaps_Get || 
		NULL == ADL_Display_ColorCaps_Get || 
		NULL == ADL_Display_Color_Get || 
		NULL == ADL_Display_Color_Set || 
		NULL == ADL_Main_Control_Destroy || 
		NULL == ADL_Graphics_Versions_Get )
	   return;

    // TODO Remove. This code is to test refresh. You can remove it if you want.
    /*for ( i = 0; i < 500; i++ )
    {
        if ( NULL != ADL_Main_Control_Refresh)
            ADL_Err = ADL_Main_Control_Refresh ();
    }*/
    // TODO Remove. This code is to test refresh. You can remove it if you want.

    // Obtain the number of adapters for the system
    if ( NULL != ADL_Adapter_NumberOfAdapters_Get )
    {
        ADL_Adapter_NumberOfAdapters_Get ( &iNumberAdapters );
    }

    if ( 0 < iNumberAdapters )
    {
        lpAdapterInfo = (LPAdapterInfo)malloc ( sizeof (AdapterInfo) * iNumberAdapters );
        memset ( lpAdapterInfo,'\0', sizeof (AdapterInfo) * iNumberAdapters );

        // Get the AdapterInfo structure for all adapters in the system
        if ( NULL != ADL_Adapter_AdapterInfo_Get )
        {
            ADL_Adapter_AdapterInfo_Get (lpAdapterInfo, sizeof (AdapterInfo) * iNumberAdapters);
        }
    }

	// Test the Versions API (Adobe)
	ADL_Err = ADL_Graphics_Versions_Get( &VersionsInfo );
    if ( ADL_OK == ADL_Err || ADL_OK_WARNING == ADL_Err )
    {
	//	printf(_T("Driver Release:  %s \nCatalyst Version:  %s \nWeb Link:  %s\n\n"),
	//		VersionsInfo.strDriverVer, VersionsInfo.strCatalystVersion, VersionsInfo.strCatalystWebLink );
	}

// Repeat for all available adapters in the system
    for ( i = 0; i < iNumberAdapters; i++ )
    {
        iAdapterIndex = lpAdapterInfo[ i ].iAdapterIndex;

		// Verify if the adapter is active
        ADL_Err = ADL_Adapter_Active_Get (iAdapterIndex, &iActive );

        // If the adapter is not active skip the steps below.
		if ( 0 == iActive || ADL_OK != ADL_Err)
        {
			continue;
        }

/*
        // TODO Remove. This code is to test refresh. You can remove it if you want.
	   // ADL_Adapter_NumberOfActivatableSources_Get
       for ( j = 0; j < TEST_CNT; j++ )
        {
            if ( NULL != ADL_Adapter_NumberOfActivatableSources_Get )
            {
                int iNum = 0;
                ADLActivatableSource* lpActSource = NULL;
				
                ADL_Err = ADL_Adapter_NumberOfActivatableSources_Get (iAdapterIndex, &iNum, &lpActSource);
				
				ADL_Main_Memory_Free ( &lpActSource); 
				lpActSource = NULL;
           }
        }
        break;

		// ADL_Display_Modes_Get
        for ( j = 0; j < TEST_CNT; j++ )
        {
            if ( NULL != ADL_Display_Modes_Get )
            {
				int iDisplayIndex = -1;
                int iNumModes = 0;
                ADLMode* lpModes = NULL;
				
                ADL_Err = ADL_Display_Modes_Get ( iAdapterIndex,
													iDisplayIndex,
                                                  &iNumModes,
                                                  &lpModes);
				
				ADL_Main_Memory_Free ( &lpModes); 
				lpModes = NULL;
           }
        }
        break;

	

		// ADL_Display_DisplayMapConfig_Get 
        for ( j = 0; j < TEST_CNT; j++ )
        {
            if ( NULL != ADL_Display_DisplayMapConfig_Get )
            {
                int iNumDisplayMap = 0;
                ADLDisplayMap* lpDisplayMap = NULL;
                int iNumDisplayTarget = 0;
                ADLDisplayTarget* lpDisplayTarget = NULL;
                ADL_Err = ADL_Display_DisplayMapConfig_Get ( iAdapterIndex, 
                                                             &iNumDisplayMap,
                                                             &lpDisplayMap,
                                                             &iNumDisplayTarget,
                                                             &lpDisplayTarget,
                                                             0 );
                ADL_Main_Memory_Free ( &lpDisplayMap );
                ADL_Main_Memory_Free ( &lpDisplayTarget );
            }
        }
    /*

        // ADL_Display_DisplayMapConfig_Get 
        for ( j = 0; j < TEST_CNT; j++ )
        {
            if ( NULL != ADL_Display_PossibleMode_Get )
            {
                int iNumMode = 0;
                ADLMode* lpMode = NULL;
                ADL_Err = ADL_Display_PossibleMode_Get ( iAdapterIndex, &iNumMode, &lpMode );
                ADL_Main_Memory_Free ( &lpMode );
            }
        }

        break;
*/

		// TODO Remove. This code is to test refresh. You can remove it if you want.

        ADL_Main_Memory_Free ( (void**)&lpAdlDisplayInfo );

       if ( NULL != ADL_Display_DisplayInfo_Get )
            ADL_Err = ADL_Display_DisplayInfo_Get (lpAdapterInfo[i].iAdapterIndex, &iNumDisplays, &lpAdlDisplayInfo, 0);

        if (ADL_OK != ADL_Err)
            continue;

        for ( j = 0; j < iNumDisplays; j++ )
        {
			// For each display, check its status. Use the display only if it's connected AND mapped (iDisplayInfoValue: bit 0 and 1 )
			if (  ( ADL_DISPLAY_DISPLAYINFO_DISPLAYCONNECTED | ADL_DISPLAY_DISPLAYINFO_DISPLAYMAPPED ) != 
				( ADL_DISPLAY_DISPLAYINFO_DISPLAYCONNECTED | ADL_DISPLAY_DISPLAYINFO_DISPLAYMAPPED	& lpAdlDisplayInfo[ j ].iDisplayInfoValue ) )
						continue;   // Skip the not connected or not mapped displays

            // Is the display mapped to this adapter?
            if ( iAdapterIndex != lpAdlDisplayInfo[ j ].displayID.iDisplayLogicalAdapterIndex )
                continue;

            iDisplayIndex = lpAdlDisplayInfo[ j ].displayID.iDisplayLogicalIndex;
			
			pcc.iSize = sizeof(ADLPixelClockCaps);
            ADL_Err = ADL_Display_PixelClockCaps_Get( iAdapterIndex, iDisplayIndex, &pcc);

            ADL_Err = ADL_Display_ColorCaps_Get( iAdapterIndex, iDisplayIndex, &iColorCaps, &iValidBits);

            // Use only the valid bits from iColorCaps
            iColorCaps &= iValidBits;

            // Check if the display supports this particular capability
            if ( ADL_DISPLAY_COLOR_BRIGHTNESS & iColorCaps )
            {
                // Get the Current display Brightness, Default value, Min, Max and Step
                ADL_Err = ADL_Display_Color_Get( iAdapterIndex, iDisplayIndex, ADL_DISPLAY_COLOR_BRIGHTNESS,
                                                 &iCurrent, &iDefault, &iMin, &iMax, &iStep);

                // Set half of the Min brightness for .5 sec
                ADL_Display_Color_Set( iAdapterIndex, iDisplayIndex, ADL_DISPLAY_COLOR_BRIGHTNESS, iMin / 2 );
                Sleep( 500 );
                ADL_Display_Color_Set( iAdapterIndex, iDisplayIndex, ADL_DISPLAY_COLOR_BRIGHTNESS, iCurrent );
                Sleep( 500 );
                // Set a quarter of the Max brightness for .5 sec
                ADL_Display_Color_Set( iAdapterIndex, iDisplayIndex, ADL_DISPLAY_COLOR_BRIGHTNESS, iMax / 4 );
                Sleep( 500 );
                // Restore the current brightness of the display
                ADL_Display_Color_Set( iAdapterIndex, iDisplayIndex, ADL_DISPLAY_COLOR_BRIGHTNESS, iCurrent );
                Sleep( 500 );
            }
        }

        // mm test
        if (ADL_MMD_FeatureList_Get && ADL_MMD_Features_Caps && ADL_MMD_FeatureValues_Get && ADL_MMD_FeatureValues_Set)
        {
            int nFeatureCount = 0;
            ADL_Main_Memory_Free ( (void**)&lpAdlFeatureName );
            ADL_MMD_FeatureList_Get( iAdapterIndex, &lpAdlFeatureName, &nFeatureCount);
            for (j=0; j<nFeatureCount; j++)
            {
                printf(("feature list: %s\n"), lpAdlFeatureName[j].FeatureName);
            }

            nFeatureCount = 0;
            ADL_Main_Memory_Free ( (void**)&lpAdlFeatureCaps );
            ADL_MMD_Features_Caps(iAdapterIndex, &lpAdlFeatureCaps, &nFeatureCount);

            nFeatureCount = 0;
            ADL_Main_Memory_Free ( (void**)&lpAdlFeatureValues );
            ADL_Err = ADL_MMD_FeatureValues_Get(iAdapterIndex, &lpAdlFeatureValues, &nFeatureCount);
            for (j=0; j<nFeatureCount; j++)
            {
                printf(("feature value: %s\n"), lpAdlFeatureValues[j].Name.FeatureName);
            }

            lpAdlFeatureValues[4].bCurrent = 0;
            lpAdlFeatureValues[8].fCurrent = -30;

            ADL_Err = ADL_MMD_FeatureValues_Set(iAdapterIndex, lpAdlFeatureValues, nFeatureCount, 1);
            if (ADL_OK != ADL_Err)
            {
                printf(("Reset value failed\n"));
            }
        }
    }

    ADL_Main_Memory_Free ( (void**)&lpAdapterInfo );
    ADL_Main_Memory_Free ( (void**)&lpAdlDisplayInfo );
    ADL_Main_Memory_Free ( (void**)&lpAdlFeatureName );
    ADL_Main_Memory_Free ( (void**)&lpAdlFeatureCaps );
    ADL_Main_Memory_Free ( (void**)&lpAdlFeatureValues );
}