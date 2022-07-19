/* information code


*/

#include "main.h"
#include "AT.h"
#include "uart.h"
#include "system.h"
#include "gpio.h"

AT_CommandTypeDef AT_CheckList1;
AT_TimeTypeDef AT_Time;

int handleCheckModule(char send[], int length_send, char compare[], int length_compare, char final[], int length_final, int timeout);
void setupModule(char keyCheck[]);

void getTime();
void sendTimeToServer(int number_second);

const int FIFTEEN_SECOND = 15;
uint8_t UART1_Rx;
char UART1_RxData[100];
char UART1_RxDatabuffer[100];

uint8_t UART3_Rx;
char UART3_RxData[100];
int couterCheck = 0;
const int LIST_CONFIG = 12;

char UART3_DataReceived[100];

int check_ok = 0;
const int GET_TIME_ON = 1, GET_TIME_OFF = 0 ;
int SECOND = 1;

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_UART4_Init();
	MX_USART1_UART_Init();
	MX_USART3_UART_Init();

  HAL_UART_Receive_IT(&huart1, &UART1_Rx, 1);
  HAL_UART_Receive_IT(&huart3, &UART3_Rx, 1);

  wait_Enable_Sim(FIFTEEN_SECOND);
  HAL_Delay(5000);
	while (1)	
	{
    setupModule(UART1_RxData);
    sendTimeToServer(60*SECOND);
  }
}

uint16_t couterMessage = 0;
char messageTime[100];
char couterChar[10];
uint32_t oldGetTick = 0;

void sendTimeToServer(int number_second)
{
  getTime(check_ok);
  if(HAL_GetTick() - oldGetTick >= number_second * 1000 && check_ok == GET_TIME_ON){
    couterMessage ++;
    uint8_t donvi = couterMessage % 10 + 48;
    uint8_t chuc = couterMessage % 100 / 10 + 48; 
    uint8_t tram = couterMessage / 100 + 48; 

    if(couterMessage < 10)
    {
      chuc = 0x00; 
      couterChar[0] = donvi;
    }
    if(couterMessage >= 10 && couterMessage < 100)
    {
      tram = 0x00; 
      couterChar[1] = donvi; 
      couterChar[0] = chuc;
    }
    if(couterMessage >= 100)
    {
      couterChar[2] = donvi; 
      couterChar[1] = chuc; 
      couterChar[0] = tram;
    }

    memset(messageTime, 0x00, 100);
    char message[] = "Message";
    char dash[] = " - ";
    char punctuation[] = ":";
    char final_char[] = "\r\n";
    memcpy(messageTime + strlen(messageTime), AT_CheckList[AT_SendData].send.data, AT_CheckList[AT_SendData].send.length_Data);
    memcpy(messageTime + strlen(messageTime), message, strlen(message));
    memcpy(messageTime + strlen(messageTime), punctuation, strlen(punctuation));
    memcpy(messageTime + strlen(messageTime), couterChar, strlen(couterChar));
    memcpy(messageTime + strlen(messageTime), dash, strlen(dash));
    memcpy(messageTime + strlen(messageTime), AT_Time.hours, 2);
    memcpy(messageTime + strlen(messageTime), punctuation, strlen(punctuation));
    memcpy(messageTime + strlen(messageTime), AT_Time.minuste, 2);
    memcpy(messageTime + strlen(messageTime), punctuation, strlen(punctuation));
    memcpy(messageTime + strlen(messageTime), AT_Time.second, 2);
    memcpy(messageTime + strlen(messageTime), final_char, strlen(final_char));
    HAL_UART_Transmit(&huart3, (uint8_t *) &messageTime, strlen(messageTime), 200);
    oldGetTick = HAL_GetTick();
  }
  
}

void getTime(int getAllow)
{
  if(getAllow == GET_TIME_ON)
  {
    
    if(handleCheckModule(
      AT_CheckList[AT_GetTime].send.data,    AT_CheckList[AT_GetTime].send.length_Data,
      AT_CheckList[AT_GetTime].compare.data, AT_CheckList[AT_GetTime].compare.length_Data,
      AT_CheckList[AT_GetTime].final.data,   AT_CheckList[AT_GetTime].final.length_Data, 
      AT_CheckList[AT_GetTime].timeout) == 1)
    {
      cutString(AT_Time.hours, UART3_DataReceived, strlen(UART3_DataReceived)-18, strlen(UART3_DataReceived)-16);
      cutString(AT_Time.minuste, UART3_DataReceived, strlen(UART3_DataReceived)-15, strlen(UART3_DataReceived)-13);
      cutString(AT_Time.second, UART3_DataReceived, strlen(UART3_DataReceived)-12, strlen(UART3_DataReceived)-10);
    }
  }
}

void setupModule(char keyCheck[]){
  
  if(strcmp(keyCheck, "KT\r\n") == 0){
    check_ok = GET_TIME_OFF;
    memset(UART1_RxData, 0x00, 100);
    for(int i= 0; i < LIST_CONFIG; i++){
      if(handleCheckModule(
        AT_CheckList[i].send.data,    AT_CheckList[i].send.length_Data,
        AT_CheckList[i].compare.data, AT_CheckList[i].compare.length_Data,
        AT_CheckList[i].final.data,   AT_CheckList[i].final.length_Data, 
        AT_CheckList[i].timeout) != 1)
      {
        i = i-2;
      }
    }
    HAL_UART_Transmit(&huart1, (uint8_t *) "Da kiem tra xong \r\n", 19, 200);
    check_ok = GET_TIME_ON;
  }
}

/**
  * @brief check the received string is true or false
  * @param  Argument 1,2 : data send, length of data send
  * @param  Argument 3,4 : data compare, length of data compare
  * @param  Argument 5,6 : data final, length of data final
  * @param  Argument 7 : timout
  * @retval True or false
  * @retval UART3_DataReceived - data received after cutting
  */
int handleCheckModule(char send[], int length_send, char compare[], int length_compare, char final[], int length_final, int timeout)
{
  int ret = 0;

  memset(UART3_RxData, 0x00, 100);
  HAL_UART_Transmit(&huart3, (uint8_t *)send, strlen(send), 200);

  HAL_Delay(timeout);

  if(strlen(strstr(UART3_RxData, compare)) != 0 && strlen(strstr(strstr(UART3_RxData, compare), final)) != 0)
  {
    memset(UART3_DataReceived, 0x00, 100);
    getStringToString(UART3_DataReceived, UART3_RxData, compare, final);
    HAL_UART_Transmit(&huart1, (uint8_t *) &UART3_DataReceived, strlen(UART3_DataReceived), 200);
    HAL_UART_Transmit(&huart1, (uint8_t *) "\r\n", 2, 200);
    ret = 1;
  }
  else{ret = 0;}
  return ret;
}

int UART1_CouterDataInterruption=0;
/**
  * @brief Get string data from UART1
  * @param  List Argument
  * @param  Argument 1: Data receive from function interrupt  (UART1_RxData)
  * @param  Argument 2: Allow to get data after "number_allow" characters \r\n  
  * @retval Data after "number_allow" characters \r\n
  * @retval Variable saved: UART1_RxData  
  */
void UART1_GetData(char UART1_Rx[], int Number_Allow){
  if(Number_Allow != 0){
    if(UART1_Rx[strlen(UART1_Rx) - 2] == 0x0D && UART1_Rx[strlen(UART1_Rx) - 1] == 0x0A){
		  ++UART1_CouterDataInterruption;
      if(UART1_CouterDataInterruption >= Number_Allow){
        memset(UART1_RxData, 0x00,100);
        memcpy(UART1_RxData, UART1_Rx, strlen(UART1_Rx));
		    memset(UART1_RxDatabuffer, 0x00,100);
        UART1_CouterDataInterruption=0;
      }
	  }
  }
}

/**
  * @brief Interrupt Receive data from UARTx
  * @param 
  * @retval Variable saved: UART1_RxData, UART3_RxData  
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	
	if(huart->Instance == huart1.Instance){
		HAL_UART_Receive_IT(&huart1, &UART1_Rx, 1);
		UART1_RxDatabuffer[strlen(UART1_RxDatabuffer)] = UART1_Rx;
	}
  UART1_GetData(UART1_RxDatabuffer, 1);
	if(huart->Instance == huart3.Instance){
		HAL_UART_Receive_IT(&huart3, &UART3_Rx, 1);
		UART3_RxData[strlen(UART3_RxData)] = UART3_Rx;
	}
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler()
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
