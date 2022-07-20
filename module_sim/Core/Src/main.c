/* information code


*/

#include "main.h"
#include "AT.h"
#include "uart.h"
#include "system.h"
#include "gpio.h"

AT_TimeTypeDef AT_Time;

int handleCheckModule(int value);
void setupModule(char keyCheck[]);

void getTime();
void sendTimeToServer(int number_second);

void UART1_Transmit(char data[]);
void UART3_Transmit(char *data);
int compare_Data(char source[], char compare[], char final[]);

void waitTimeout(int milisecond);

uint8_t UART1_Rx;
char UART1_RxData[SIZE_DATA];
char UART1_RxDatabuffer[SIZE_DATA];

uint8_t UART3_Rx;
char UART3_RxData[SIZE_DATA];
const int LIST_CONFIG = 12;

char UART3_DataReceived[SIZE_DATA];

int completeTest = 0;
const int GET_TIME_ON = 1, GET_TIME_OFF = 0 ;
int ONE_SECOND = 1;

uint16_t couterMessage = 0;
char messageTime[SIZE_DATA];
char couterChar[SIZE_DATA];
uint32_t oldGetTickSendTimeToServer = 0, oldGetTickTimeout = 0;

int UART1_CouterDataInterruption = 0;


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

  setStatusModuleSim(TURN_ON, WAIT_ON_MODULE);
  HAL_Delay(5000);
	while (1)	
	{
    setupModule(UART1_RxData);
    sendTimeToServer(60 * ONE_SECOND);
  }
}

void sendTimeToServer(int number_Second)
{
  getTime(completeTest);
  if( ( HAL_GetTick() - oldGetTickSendTimeToServer >= number_Second * 1000 ) && ( completeTest == GET_TIME_ON ) )
  {
    couterMessage ++;
    uint8_t donvi = couterMessage % 10 + 48;
    uint8_t chuc = couterMessage % 100 / 10 + 48; 
    uint8_t tram = couterMessage / 100 + 48; 

    if(couterMessage < 10)
    {
      chuc = NULL_CHARACTER;
      couterChar[0] = donvi;
    }
    if( ( couterMessage >= 10 ) && ( couterMessage < 100 ) )
    {
      tram = NULL_CHARACTER; 
      couterChar[1] = donvi; 
      couterChar[0] = chuc;
    }
    if(couterMessage >= 100)
    {
      couterChar[2] = donvi; 
      couterChar[1] = chuc; 
      couterChar[0] = tram;
    }

    memset(messageTime, NULL_CHARACTER, SIZE_DATA);
    char message[] = "Message";
    char dash[] = " - ";
    char punctuation[] = ":";
    char final_char[] = "\r\n";
    memcpy(messageTime + strlen(messageTime), AT_CheckList[AT_SendData].send, strlen(AT_CheckList[AT_SendData].send));
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
    HAL_UART_Transmit(&huart3, (uint8_t *) &messageTime, strlen(messageTime), UART_TIMEOUT);
    oldGetTickSendTimeToServer = HAL_GetTick();
  }
}

void getTime(int getAllow)
{
  if(getAllow == GET_TIME_ON)
  {
    if(handleCheckModule( AT_GetTime ) == 1)
    {
      cutString(AT_Time.hours, UART3_DataReceived, strlen(UART3_DataReceived)-18, strlen(UART3_DataReceived)-16);
      cutString(AT_Time.minuste, UART3_DataReceived, strlen(UART3_DataReceived)-15, strlen(UART3_DataReceived)-13);
      cutString(AT_Time.second, UART3_DataReceived, strlen(UART3_DataReceived)-12, strlen(UART3_DataReceived)-10);
    }
  }
}

void setupModule(char keyCheck[]){
  
  if(strcmp(keyCheck, "KT\r\n") == 0){
    completeTest = GET_TIME_OFF;
    memset(UART1_RxData, NULL_CHARACTER, SIZE_DATA);
    for(int i= 0; i < LIST_CONFIG; i++){
      if(handleCheckModule(i) != 1)
      {
        i = i-2;
      }
    }
    completeTest = GET_TIME_ON;
  }
}

void waitTimeout(int milisecond)
{
  HAL_Delay(milisecond);
}

int compare_Data(char source[], char compare[], char final[]){
  int ret = 0;
  if(strlen(strstr(source, compare)) != 0 && strlen(strstr(strstr(source, compare), final)) != 0)
  {
    memset(UART3_DataReceived, NULL_CHARACTER, SIZE_DATA);
    getStringToString(UART3_DataReceived, source, compare, final);
    ret = 1;
  }
  else
  {
    ret = 0;
  }
  return ret;
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
int handleCheckModule(int value)
{
  
  int ret = 0;
  UART3_Transmit(AT_CheckList[value].send);

  waitTimeout(AT_CheckList[value].timeout);

  if(compare_Data(UART3_RxData, AT_CheckList[value].compare, AT_CheckList[value].final) == 1)
  {
    ret = 1;
  }
  else{
    ret = 0;
  }
  return ret;
}

void UART3_Transmit(char *data)
{
  memset(UART3_RxData, NULL_CHARACTER, SIZE_DATA);
  HAL_UART_Transmit(&huart3, (uint8_t *) data, strlen(data), UART_TIMEOUT);
}

void UART1_Transmit(char data[])
{
  memset(UART1_RxData, NULL_CHARACTER, SIZE_DATA);
  HAL_UART_Transmit(&huart1, (uint8_t *) &data, strlen(data), UART_TIMEOUT);
}

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
    if( (UART1_Rx[strlen(UART1_Rx) - 2] == CARRIAGE_RETURN) && (UART1_Rx[strlen(UART1_Rx) - 1] == LINE_FEED) )
    {
		  ++UART1_CouterDataInterruption;
      if(UART1_CouterDataInterruption >= Number_Allow)
      {
        memset(UART1_RxData, NULL_CHARACTER, SIZE_DATA);
        memcpy(UART1_RxData, UART1_Rx, strlen(UART1_Rx));
		    memset(UART1_RxDatabuffer, NULL_CHARACTER, SIZE_DATA);
        UART1_CouterDataInterruption = 0;
      }
	  }
  }
}

/**
  * @brief Interrupt Receive data from UARTx
  * @param 
  * @retval Variable saved: UART1_RxData, UART3_RxData  
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
	if(huart->Instance == huart1.Instance)
  {
		HAL_UART_Receive_IT(&huart1, &UART1_Rx, 1);
		UART1_RxDatabuffer[strlen(UART1_RxDatabuffer)] = UART1_Rx;
	}
  UART1_GetData(UART1_RxDatabuffer, 1);
	if(huart->Instance == huart3.Instance)
  {
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
