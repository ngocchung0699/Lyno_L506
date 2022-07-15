#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int xy[10] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A};

void getString( void *data, const char source[], const char startPosition[], const char finalPosition[]){
   char *pdata = (char *)data;
   int maxLength = 200;
   char *subStart, *subFinal, getStart[maxLength], getFinal[maxLength];

   subStart = strstr(source, startPosition);
   memcpy(getStart, subStart ,maxLength);
   subFinal = strstr(getStart, finalPosition);
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
char abc[100];
int main()
{

   char chuoi[] = "\r\n+CCLK: \"22/07/13,10:26:04+28\"\r\n\r\nOK123\r\n";
   //printf("chuoi: %s\n", chuoi);
   char str1[] = "CCLK";
   char str2[] = "13";
   
   //printf("\nChuoi con la: %d", strcmp(str, "CCLK"));
   getString(abc, chuoi, str1, str2 );
   printf("\nChuoi get: %s", abc);
   return 0;
}
