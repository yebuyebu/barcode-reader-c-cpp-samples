// HelloWorld.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

// Include headers of DynamsoftBarcodeReader SDK
#include "../../../include/DynamsoftBarcodeReader.h"
#include "../../../include/DynamsoftCommon.h"


// Link libraries of DynamsoftBarcodeReader SDK for Windows.
#if defined(_WIN64) || defined(_WIN32)
#ifdef _WIN64
#pragma comment(lib, "../../../lib/Windows/x64/DBRx64.lib")
#else
#pragma comment(lib, "../../../lib/Windows/x86/DBRx86.lib")
#endif
#endif

void main()
{
    void* dbr = NULL;
    int errorCode = 0;
    char szErrorMsg[256];
    TextResultArray* barcodeResults = NULL;
    int index;

    // 1. Initialize license
    /*
    // By setting organization ID as "200001", a 7-day trial license will be used for license verification.
    // Note that network connection is required for this license to work.
    //
    // When using your own license, locate the following line and specify your Organization ID.
    // organizationID = "200001";
    //
    // If you don't have a license yet, you can request a trial from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=c_cpp
    */
    DM_DLSConnectionParameters paramters;
    DBR_InitDLSConnectionParameters(&paramters);
    paramters.organizationID = "200001"; // replace it with your organization ID
    errorCode = DBR_InitLicenseFromDLS(&paramters, szErrorMsg, 256);
    if (errorCode != DBR_OK)
    {
        printf("%s\r\n", szErrorMsg);
    }

    // 2. Create an instance of Barcode Reader
    dbr = DBR_CreateInstance();

    // 3. Read barcode from an image file
    errorCode = DBR_DecodeFile(dbr, "../../../images/AllSupportedBarcodeTypes.png", "");
    if (errorCode != DBR_OK)
        printf("%s\r\n", DBR_GetErrorString(errorCode));

    // 4. Get all barcode results
    DBR_GetAllTextResults(dbr, &barcodeResults);


    if (barcodeResults != NULL && barcodeResults->resultsCount > 0)
    {
        // Process each result in a loop
        for (index = 0; index < barcodeResults->resultsCount; ++index)
        {
            printf("Result %d:\r\n", (index + 1));

            // 4.1. Get format of each barcode
            if (barcodeResults->results[index]->barcodeFormat != BF_NULL)
                printf("    Barcode Format: %s\r\n", barcodeResults->results[index]->barcodeFormatString);
            else
                printf("    Barcode Format: %s\r\n", barcodeResults->results[index]->barcodeFormatString_2);

            // 4.2. Get text result of each barcode
            printf("    Barcode Text: %s\r\n", barcodeResults->results[index]->barcodeText);
        }
    }
    else
    {
        printf("No barcode detected.");
    }

    // 5. Free the memory allocated for text results
    if (barcodeResults != NULL)
        DBR_FreeTextResults(&barcodeResults);
    DBR_DestroyInstance(dbr);

    printf("Press any key to quit...");
    getchar();
}

