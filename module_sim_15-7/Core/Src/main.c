/* information code


*/

#include "main.h"
#include "AT.h"
#include "uart.h"
#include "system.h"
#include "gpio.h"

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

void MX_UART4_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);


int handle_Check_Data_Module(uint8_t send[], int length_send, uint8_t compare[], int length_compare, uint8_t final[], int length_final, int numberAllow);
void setupModule(char check_Character[]);

int TEN_SECOND =10;
int runValue=0;
char test[100];

uint8_t UART1_Rx;
char UART1_RxDatabuffer[100];
char UART1_RxData[100];
int UART1_RxCouterData =0;
int UART1_CouterDataInterruption=0;
int UART1_NumberDataInterruption=1;

uint8_t UART3_Rx;
char UART3_RxDatabuffer[100];
char UART3_RxData[100];
char Rx3_Data[100];
int UART3_RxCouterData =0;
int UART3_CouterDataInterruption=0;
int UART3_NumberDataInterruption=5;

char sendBuffer[100];
char compareBuffer[100];
char finalBuffer[100];


void char_m(uint8_t data[], int length);
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

  wait_Enable_Sim(TEN_SECOND);
  HAL_Delay(2000);
	while (1)	
	{
    setupModule(UART1_RxData);
	}
}

void char_m(uint8_t data[], int length){
  memcpy(test, data, length);
}

char KT[]= "KT\r\n";

void setupModule(char check_Character[]){
  if(strcmp(check_Character, KT) ==0){
    memset(UART1_RxData,0x00,100);
    runValue =1;
  }
  if(runValue == 1){
    for(int i = 0; i < 12; i++){
      if ( handle_Check_Data_Module(
        AT_CheckList[i].send.data,    AT_CheckList[i].send.length_Data,
        AT_CheckList[i].compare.data, AT_CheckList[i].compare.length_Data,
        AT_CheckList[i].final.data,   AT_CheckList[i].final.length_Data,
        AT_CheckList[i].number_char) != 1)
      {
        i=i-1;
      }
    }
    runValue=0;
  }

  // switch (runValue)
  // {
  // case 1:
  //   if (handle_Check_Data_Module(
  //     AT_CheckList[AT_CheckModule].send.data,    AT_CheckList[AT_CheckModule].send.length_Data,
  //     AT_CheckList[AT_CheckModule].compare.data, AT_CheckList[AT_CheckModule].compare.length_Data,
  //     AT_CheckList[AT_CheckModule].final.data,   AT_CheckList[AT_CheckModule].final.length_Data,
  //     AT_CheckList[AT_CheckModule].number_char) ==1)      { runValue = 2;}
  //   else{ runValue = 1;}
  //   break;
  // case 2:
  //   if (handle_Check_Data_Module(
  //     AT_CheckList[AT_CheckSignal].send.data,    AT_CheckList[AT_CheckSignal].send.length_Data,
  //     AT_CheckList[AT_CheckSignal].compare.data, AT_CheckList[AT_CheckSignal].compare.length_Data,
  //     AT_CheckList[AT_CheckSignal].final.data,   AT_CheckList[AT_CheckSignal].final.length_Data,
  //     AT_CheckList[AT_CheckSignal].number_char) ==1)      { runValue = 3;}
  //   else{ runValue = 2;}
  //   break;
  // case 2:
  //   if (handle_Check_Data_Module(AT_CheckList[AT_CheckSim].send.data,AT_CheckList[AT_CheckSim].compare.data, 
  //   AT_CheckList[AT_CheckSim].final.data, AT_CheckList[AT_CheckSim].number_char) ==1){ runValue = 3;}
  //   else{ runValue = 2;}
  //   break;
  // case 3:
  //   if (handle_Check_Data_Module(AT_CheckList[AT_CheckSignal].send.data,AT_CheckList[AT_CheckSignal].compare.data, 
  //   AT_CheckList[AT_CheckSignal].final.data, AT_CheckList[AT_CheckSignal].number_char) ==1){ runValue = 4;}
  //   else{ runValue = 3;}
  //   break;
  // case 4:
  //   if (handle_Check_Data_Module(AT_CheckList[AT_CheckSubscribe].send.data,AT_CheckList[AT_CheckSubscribe].compare.data, 
  //   AT_CheckList[AT_CheckSubscribe].final.data, AT_CheckList[AT_CheckSubscribe].number_char) ==1){ runValue = 5;}
  //   else{ runValue = 4;}
  //   break;
  // case 5:
  //   if (handle_Check_Data_Module(AT_CheckList[AT_CheckGPRS].send.data,AT_CheckList[AT_CheckGPRS].compare.data, 
  //   AT_CheckList[AT_CheckGPRS].final.data, AT_CheckList[AT_CheckGPRS].number_char) ==1){ runValue = 6;}
  //   else{ runValue = 5;}
  //   break;
  // case 6:
  //   if (handle_Check_Data_Module(AT_CheckList[AT_SetTimeout].send.data,AT_CheckList[AT_SetTimeout].compare.data, 
  //   AT_CheckList[AT_SetTimeout].final.data, AT_CheckList[AT_SetTimeout].number_char) ==1){ runValue = 7;}
  //   else{ runValue = 6;}
  //   break;
  // case 7:
  //   if (handle_Check_Data_Module(AT_CheckList[AT_SetTransmit].send.data,AT_CheckList[AT_SetTransmit].compare.data, 
  //   AT_CheckList[AT_SetTransmit].final.data, AT_CheckList[AT_SetTransmit].number_char) ==1){ runValue = 8;}
  //   else{ runValue = 7;}
  //   break;
  // case 8:
  //   if (handle_Check_Data_Module(AT_CheckList[AT_SetNetOpen].send.data,AT_CheckList[AT_SetNetOpen].compare.data, 
  //   AT_CheckList[AT_SetNetOpen].final.data, AT_CheckList[AT_SetNetOpen].number_char) ==1){ runValue = 9;}
  //   else{ runValue = 8;}
  //   break;
  // case 9:
  //   if (handle_Check_Data_Module(AT_CheckList[AT_CheckIP].send.data,AT_CheckList[AT_CheckIP].compare.data, 
  //   AT_CheckList[AT_CheckIP].final.data, AT_CheckList[AT_CheckIP].number_char) ==1){ runValue = 10;}
  //   else{ runValue = 9;}
  //   break;
  // case 10:
  //   if (handle_Check_Data_Module(AT_CheckList[AT_SetReceive].send.data,AT_CheckList[AT_SetReceive].compare.data, 
  //   AT_CheckList[AT_SetReceive].final.data, AT_CheckList[AT_SetReceive].number_char) ==1){ runValue = 11;}
  //   else{ runValue = 10;}
  //   break;
  // case 11:
  //   if (handle_Check_Data_Module(AT_CheckList[AT_SetConnectTCP].send.data,AT_CheckList[AT_SetConnectTCP].compare.data, 
  //   AT_CheckList[AT_SetConnectTCP].final.data, AT_CheckList[AT_SetConnectTCP].number_char) ==1){ runValue = 12;}
  //   else{ runValue = 11;}
  //   break;
  // case 12:
  //   if (handle_Check_Data_Module(AT_CheckList[AT_CheckConnectTCP].send.data,AT_CheckList[AT_CheckConnectTCP].compare.data, 
  //   AT_CheckList[AT_CheckConnectTCP].final.data, AT_CheckList[AT_CheckConnectTCP].number_char) ==1){ runValue = 13;}
  //   else{ runValue = 12;}
  //   break;
  // default:
  //   break;
  // }
}

int handle_Check_Data_Module(uint8_t send[], int length_send, uint8_t compare[], int length_compare, uint8_t final[], int length_final, int numberAllow){
  int ret=0;
  char *buffer;
  memset(sendBuffer,0x00,100);
  memset(compareBuffer,0x00,100);
  memset(finalBuffer,0x00,100);

  memcpy(sendBuffer, send, length_send);
  memcpy(compareBuffer, compare, length_compare);
  memcpy(finalBuffer, final, length_final);

  UART3_NumberDataInterruption = numberAllow;
  HAL_UART_Transmit(&huart3, (uint8_t *) &sendBuffer, strlen(sendBuffer),200);
  
  HAL_Delay(500);
  buffer = strstr(UART3_RxData, compareBuffer);
  if(strlen(buffer) !=0 ){
    memset(Rx3_Data,0x00,100);
    cutString(Rx3_Data, UART3_RxData, compareBuffer, finalBuffer);
    //memcpy(so, Rx3_Data, 2); memcpy(co, compareBuffer, 2);
    memcpy(Rx3_Data + strlen(Rx3_Data), "\r\n",2);
    HAL_UART_Transmit(&huart1, (uint8_t *) &Rx3_Data, strlen(Rx3_Data), 200);
    ret = 1;
  }
  
  else{
    HAL_UART_Transmit(&huart1, (uint8_t *) "ERROR\r\n", 7, 200);
    ret = 0;
  }
  return ret;
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
    if(UART1_Rx[strlen(UART1_Rx)-2]==13 && UART1_Rx[strlen(UART1_Rx)-1]==10){
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
  * @brief Get string data from UART3 and send received data to UART1
  * @param  List Argument
  * @param  Argument 1: Data receive from function interrupt  (UART1_RxData)
  * @param  Argument 2: Allow to get data after "number_allow" characters \r\n  
  * @retval Data after "number_allow" characters \r\n 
  * @retval Variable saved: UART3_RxData  
  */
void UART3_GetData(char UART3_Rx[], int Number_String_Allow_Get_Data){
  if(Number_String_Allow_Get_Data != 0){
    if(UART3_Rx[strlen(UART3_Rx)-2]==13 && UART3_Rx[strlen(UART3_Rx)-1]==10){
		  ++UART3_CouterDataInterruption;
      if(UART3_CouterDataInterruption >= Number_String_Allow_Get_Data){
        memset(UART3_RxData, 0x00,100);
        memcpy(UART3_RxData, UART3_Rx, strlen(UART3_Rx));
		    memset(UART3_RxDatabuffer, 0x00,100);
		    UART3_RxCouterData=0;
        UART3_CouterDataInterruption=0;
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
    UART1_GetData(UART1_RxDatabuffer, UART1_NumberDataInterruption);
	}
  

	if(huart->Instance == huart3.Instance){
		HAL_UART_Receive_IT(&huart3, &UART3_Rx, 1);
    //HAL_UART_Transmit(&huart1, &UART3_Rx, 1,10);
		UART3_RxDatabuffer[UART3_RxCouterData] = UART3_Rx;
		++UART3_RxCouterData;
    UART3_GetData(UART3_RxDatabuffer, UART3_NumberDataInterruption);
	}
  
}


/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */
    
  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */
    
  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

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
