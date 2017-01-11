/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
 
// TODO: Include your class to test here.
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "videoOutputPortType.hpp"
#include "manager.hpp"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


#include "libIBus.h"
#include "mfrMgr.h"




int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s : <true|false>\n", argv[0]);
        return 0;
    }

    IARM_Bus_Init("enableHDCPclient");
    IARM_Bus_Connect();

    device::Manager::Initialize();


    char *enabled = argv[1];
    int protectContent = false;

    if (strcmp(enabled, "true") == 0) {
	    protectContent = true;
    }

    int keySize = 0;
    char *hdcpKey = 0;
	int IsMfrDataRead = false;
    IARM_Bus_MFRLib_GetSerializedData_Param_t param_, *param = &param_;
   

		if (protectContent) {
		do
		{	
			 IsMfrDataRead = false;
			 /*Initialize the struct */
			 memset(param, 0, sizeof(*param));
			/* Get Key */
			param->type = mfrSERIALIZED_TYPE_HDMIHDCP;
			param->bufLen = MAX_SERIALIZED_BUF;
			
			int ret = IARM_Bus_Call(IARM_BUS_MFRLIB_NAME,IARM_BUS_MFRLIB_API_GetSerializedData,
				(void *)param, sizeof(IARM_Bus_MFRLib_GetSerializedData_Param_t));

			if(ret != IARM_RESULT_SUCCESS)
			{
				printf("Call failed for %s: error code:%d\n","IARM_BUS_MFR_SERIALIZED_TYPE_HDMIHDCP",ret);
				/**Sleep for 2 sec - wait for MFR data to be ready*/
				sleep(2);
			}
			else
			{
				 keySize = param->bufLen;
				 hdcpKey = param->buffer;

				 if(0 == keySize){
					break;
				 }
				
				if ((hdcpKey[0] == 0) &&
					(hdcpKey[1] == 0) &&
					(hdcpKey[2] == 0) &&
					(hdcpKey[3] == 0) &&
					(hdcpKey[4] == 0) &&
					(hdcpKey[5] == 0) 
					)
				{
					printf("Invalid MFR Data !! Wait for MFR data to be ready..Retry after 10 sec\n");
					/**Sleep for 10 sec - wait for MFR data to be ready*/
					sleep(10);
				}
				else
				{
					printf("Call succeed for %s: [%d]\n","IARM_BUS_MFR_SERIALIZED_TYPE_HDMIHDCP\n", param->bufLen);
					IsMfrDataRead = true;
			  	}
							
				#if 0
					for (int i = 0; i < keySize; i++) {
					printf(" %02X", (unsigned char)hdcpKey[i]);
					}
					printf("\r\n");
				#endif
			}
		}while(false == IsMfrDataRead);	
    }

    try {
	    printf("Setting HDCP [%s]\n", enabled);
		if(0 == keySize){
			printf("Ignoring request, invalid parameters \n");
		}else{
			device::VideoOutputPortType::getInstance(device::VideoOutputPortType::kHDMI).enabledHDCP(protectContent, hdcpKey, keySize);
			printf("Setting  HDCP done\n");
		}
    }
    catch (...) {
	    printf("Exception Caught during [%s]\r\n", argv[0]);
    }

    device::Manager::DeInitialize();

    IARM_Bus_Disconnect();
    IARM_Bus_Term();
    return 0;
}
