#include "uart.h"

/**
  * @brief trim string based on start and end string
  * @param data - data received after cutting
  * @param source - pass to the original string
  * @param startString - string starts to get data
  * @param finalString - terminating string receiving data
  * @retval None  
  */
void cutString( void *data, const char source[], const char startString[], const char finalString[]){
   char *pdata = (char *)data;
   int maxLength = 100;
   char *subStart, *subFinal, getStart[maxLength], getFinal[maxLength];

   subStart = strstr(source, startString);
   memcpy(getStart, subStart ,maxLength);
   subFinal = strstr(getStart, finalString);
   memcpy(getFinal, subFinal ,maxLength);

   if(strlen(getStart)!=0 && strlen(getFinal) !=0){
      for(int i=0; i< strlen(getStart); i++){
         if(strcmp(&getStart[i-2], &getFinal[0]) ==0 && strcmp(&getStart[i-1], &getFinal[1]) ==0 ){
            break;
         }
         else{
            pdata[strlen(pdata)] = getStart[i];
         }
      }
   }
}