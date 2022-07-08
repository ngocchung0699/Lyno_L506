/* information code

  hoàn thành
- lấy dữ liệu từ UART1 và UART3
- truyền lệnh kiểm tra module

  tiếp theo
- hoàn thiện thư viện AT_command (gửi, nhận và xử lý tín hiệu) sau đó xuất ra UART1
- hoàn thiện hàm "Send_Data_Check_Module" (truyền, nhận, báo thành công, báo l)











*/

#include "main.h"
#include "AT_command.h"

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

//AT_HandleTypeDef AT;
check_List current_Number_Of_Check_Module_List = Command_0;

AT_Command_HandleTypeDef AT_Check_Module;
AT_Command_HandleTypeDef AT_Check_Sim;
AT_Command_HandleTypeDef AT_Check_Signal;
AT_Command_HandleTypeDef AT_Check_Subscribe;

AT_Command_HandleTypeDef AT_Check_GPRS;
AT_Command_HandleTypeDef AT_Set_Timeout;
AT_Command_HandleTypeDef AT_Set_Transmit_Mode;
AT_Command_HandleTypeDef AT_Check_Net_Open;

AT_Command_HandleTypeDef AT_Check_IP;
AT_Command_HandleTypeDef AT_Set_Receive_Mode;
AT_Command_HandleTypeDef AT_Get_Current_Time;
AT_Command_HandleTypeDef AT_Transmit_Data_To_TCP;

AT_Command_HandleTypeDef AT_Connect_TCP_Server;
AT_Command_HandleTypeDef AT_Check_Connect_TCP;
AT_Command_HandleTypeDef AT_Close_Connect_TCP_Server;
AT_Command_HandleTypeDef AT_Set_Net_Close;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_UART4_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM2_Init(void);


// function declaration

void get_RTC(void);           
void enable_Sim(int x); 
void UART1_GetData(char uart1_rx[], int number_allow_get_data);
void UART3_GetData(char uart3_rx[], int number_allow_get_data);
void handle_Data_Module(char check_character[]);
int handle_Check_Data_Module(AT_Command_HandleTypeDef);

void get_And_Send_Current_Time(int time_template);
// variable declare 

uint8_t UART1_Rx;
char UART1_Rx_Data_buffer[100];
char UART1_Rx_Data[100];
int UART1_Rx_Couter_Data =0;
int UART1_Couter_Data_Interruption=0;
int UART1_Number_Data_Interruption=1;

uint8_t UART3_Rx;
char UART3_Rx_Data_buffer[100];
char UART3_Rx_Data[100];
int UART3_Rx_Couter_Data =0;
int UART3_Couter_Data_Interruption=0;
int UART3_Number_Data_Interruption=5;

int variable_Check_Is_Done =0;
char IP_Address[] = "117.6.163.177";
char IP_Port[] = "7577";

char check_Mode[] = "KT\r\n";

char uart1_rx[100];

char send_Data_buffer[100];
char working_buffer[100];
char error_buffer[100];
char ready_buffer[100];
int number_buffer=0;

int main(void)
{
	HAL_Init();
	SystemClock_Config();

	MX_GPIO_Init();
  
	MX_UART4_Init();
	MX_USART1_UART_Init();
	MX_USART3_UART_Init();
	MX_RTC_Init();
	MX_TIM2_Init();

	HAL_TIM_Base_Start_IT(&htim2);
	HAL_UART_Receive_IT(&huart3,&UART3_Rx,1);
	HAL_UART_Receive_IT(&huart1,&UART1_Rx,1);

	AT_Init(IP_Address, IP_Port);
  enable_Sim(15);

	while (1)	
	{
    //handle_Data_Module(UART1_Rx_Data);
    get_And_Send_Current_Time(1);
	}
}

int time_template = 0;
unsigned int old_time_get_data = 0;
unsigned int old_time_send_data = 0;
char Message[] = "Message: ";
char data_time_to_send[100];
char data_time_of_sim[100];
char send_time[100];
int get_data_time=8;
char end_String[] = "\r\n";
int couter =0;
uint8_t don_vi;
uint8_t chuc;
uint8_t tram;

void get_And_Send_Current_Time(int time_template){
  UART3_Number_Data_Interruption=4;
  if(UART3_Rx_Data[3] == 67 && UART3_Rx_Data[4] ==67 && UART3_Rx_Data[5] == 76 && UART3_Rx_Data[6] ==75 )
  {
		memcpy(data_time_of_sim,UART3_Rx_Data , 100);
	}

  if(HAL_GetTick() - old_time_get_data >= time_template*1000/1.5 && variable_Check_Is_Done == 0)
  {
    memcpy(send_Data_buffer, AT_Get_Current_Time.Send,100);
		HAL_UART_Transmit(&huart3, (uint8_t *)&send_Data_buffer, strlen(send_Data_buffer), 500);
		old_time_get_data = HAL_GetTick();
	}

  if(HAL_GetTick() - old_time_send_data >= time_template*1000 && variable_Check_Is_Done == 0)
  {
		couter++;
    if(couter%10 < 1 && couter%100/10 < 1){ don_vi = 0x00; }
    else{ don_vi = couter %10 + 48; }
    if(couter%100/10 < 1 && couter/100 < 1){ chuc = 0x00; }
    else{ chuc = couter %100/10 + 48; }
    if(couter%1000/100 < 1){ tram = 0x00; }
    else{ tram = couter/100 + 48;}

    memcpy(data_time_to_send, Message,strlen(Message));

		data_time_to_send[strlen(data_time_to_send)] = tram;
    data_time_to_send[strlen(data_time_to_send)] = chuc;
    data_time_to_send[strlen(data_time_to_send)] = don_vi;
    data_time_to_send[strlen(data_time_to_send)] = 45;
 
		for(int i=0;i< get_data_time ;i++)
    {
		  data_time_to_send[strlen(data_time_to_send)] = data_time_of_sim[19+i];
		}

    memcpy(data_time_to_send + strlen(data_time_to_send), end_String, strlen(end_String));
    memcpy(send_time, data_time_to_send, 100);

    
    memset(data_time_to_send, 0x00, 100);
		old_time_send_data = HAL_GetTick();
	}	
  
}

void handle_Data_Module(char check_Character[])
{    
  if(strcmp(check_Character, check_Mode) == 0) 
  {
    memset(UART1_Rx_Data,0x00,100);
    memset(UART3_Rx_Data,0x00,100);
    current_Number_Of_Check_Module_List = Command_1;
    variable_Check_Is_Done = 0;
  }
  
  switch (current_Number_Of_Check_Module_List)
  {
    case Command_1:
    if (handle_Check_Data_Module(AT_Check_Module) ==1) { current_Number_Of_Check_Module_List = Command_2; }
    else { current_Number_Of_Check_Module_List = Command_1; }
      break;

    case Command_2:
    if (handle_Check_Data_Module(AT_Check_Sim) ==1) { current_Number_Of_Check_Module_List = Command_3; }
    else { current_Number_Of_Check_Module_List = Command_2; }
      break;

    case Command_3:
    if (handle_Check_Data_Module(AT_Check_Signal) ==1) { current_Number_Of_Check_Module_List = Command_4; }
    else { current_Number_Of_Check_Module_List = Command_3; }
      break;
    
    case Command_4:
    if (handle_Check_Data_Module(AT_Check_Subscribe) ==1) { current_Number_Of_Check_Module_List = Command_5; }
    else { current_Number_Of_Check_Module_List = Command_4; }
      break;

    case Command_5:
    if (handle_Check_Data_Module(AT_Check_GPRS) ==1) { current_Number_Of_Check_Module_List = Command_6; }
    else { current_Number_Of_Check_Module_List = Command_5; }
      break;

    case Command_6:
    if (handle_Check_Data_Module(AT_Set_Timeout) ==1) { current_Number_Of_Check_Module_List = Command_7; }
    else { current_Number_Of_Check_Module_List = Command_6; }
      break;
    
    case Command_7:
    if (handle_Check_Data_Module(AT_Set_Transmit_Mode) ==1) { current_Number_Of_Check_Module_List = Command_8; }
    else { current_Number_Of_Check_Module_List = Command_7; }
      break;
    
    case Command_8:
    if (handle_Check_Data_Module(AT_Check_Net_Open) ==1) { current_Number_Of_Check_Module_List = Command_9; }
    else { current_Number_Of_Check_Module_List = Command_8; }
      break;
    
    case Command_9:
    if (handle_Check_Data_Module(AT_Check_IP) ==1) { current_Number_Of_Check_Module_List = Command_10; }
    else { current_Number_Of_Check_Module_List = Command_9; }
      break;
    
    case Command_10:
    if (handle_Check_Data_Module(AT_Set_Receive_Mode) ==1) { current_Number_Of_Check_Module_List = Command_11; }
    else { current_Number_Of_Check_Module_List = Command_10; }
      break;
    
    case Command_11:
    if (handle_Check_Data_Module(AT_Close_Connect_TCP_Server) ==1) { current_Number_Of_Check_Module_List = Command_12; }
    else { current_Number_Of_Check_Module_List = Command_11; }
      break;

    case Command_12:
    if (handle_Check_Data_Module(AT_Check_Connect_TCP) ==1) { current_Number_Of_Check_Module_List = Command_0 ;}
    else { current_Number_Of_Check_Module_List = Command_12; }
    variable_Check_Is_Done = 1;
      break;

    default:
      break;
  }
}




int handle_Check_Data_Module(AT_Command_HandleTypeDef AT_Command){
  int ret=0;
  memcpy(send_Data_buffer,AT_Command.Send,100);
  memcpy(working_buffer,AT_Command.Checking,100);
  memcpy(error_buffer,AT_Command.Error,100);
  memcpy(ready_buffer,AT_Command.Ready,100);
  number_buffer = AT_Command.Number_Get_Data;
  
  UART3_Number_Data_Interruption = number_buffer;
  HAL_UART_Transmit(&huart3, (uint8_t *) &send_Data_buffer, strlen(send_Data_buffer),200);
  
  HAL_Delay(500);
	HAL_UART_Transmit(&huart1, (uint8_t *) &working_buffer, strlen(working_buffer),200);
  if(UART3_Rx_Data[strlen(UART3_Rx_Data)-4] == 79 && UART3_Rx_Data[strlen(UART3_Rx_Data)-3] == 75){
    HAL_UART_Transmit(&huart1, (uint8_t *) &ready_buffer, strlen(ready_buffer),200);
    memset(UART3_Rx_Data,0x00,100);
    ret = 1;
  }
  else{
    HAL_UART_Transmit(&huart1, (uint8_t *) &error_buffer, strlen(error_buffer),200);
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
		  ++UART1_Couter_Data_Interruption;
      if(UART1_Couter_Data_Interruption >= Number_Allow){
        memset(UART1_Rx_Data, 0x00,100);
        memcpy(UART1_Rx_Data, UART1_Rx, strlen(UART1_Rx));
		    memset(UART1_Rx_Data_buffer, 0x00,100);
		    UART1_Rx_Couter_Data=0;
        UART1_Couter_Data_Interruption=0;
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
		  ++UART3_Couter_Data_Interruption;
      if(UART3_Couter_Data_Interruption >= Number_String_Allow_Get_Data){
        memset(UART3_Rx_Data, 0x00,100);
        memcpy(UART3_Rx_Data, UART3_Rx, strlen(UART3_Rx));
		    memset(UART3_Rx_Data_buffer, 0x00,100);
		    UART3_Rx_Couter_Data=0;
        UART3_Couter_Data_Interruption=0;
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
		UART1_Rx_Data_buffer[UART1_Rx_Couter_Data] = UART1_Rx;
		++UART1_Rx_Couter_Data;
    UART1_GetData(UART1_Rx_Data_buffer, UART1_Number_Data_Interruption);
	}
  

	if(huart->Instance == huart3.Instance){
		HAL_UART_Receive_IT(&huart3, &UART3_Rx, 1);
    //HAL_UART_Transmit(&huart1, &UART3_Rx, 1,10);
		UART3_Rx_Data_buffer[UART3_Rx_Couter_Data] = UART3_Rx;
		++UART3_Rx_Couter_Data;
    UART3_GetData(UART3_Rx_Data_buffer, UART3_Number_Data_Interruption);
	}
  
}

/**
  * @brief Allow sim to work (wait x seconds)
  * @param Time (x second)
  * @retval None
  */
void enable_Sim(int x){
  // turn on sim
  HAL_GPIO_WritePin(OF_SIM_GPIO_Port ,OF_SIM_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(RESET_SIM_GPIO_Port, RESET_SIM_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWRKEY_GPIO_Port, PWRKEY_Pin,GPIO_PIN_SET);

  for(int i=0; i < 15; i++){
    HAL_GPIO_TogglePin(LED_DO_GPIO_Port,LED_DO_Pin);
    HAL_GPIO_TogglePin(LED_XANH_GPIO_Port,LED_XANH_Pin);
    HAL_Delay(1000);
  }
}

/**
  * @brief Get data time
  * @param None
  * @retval sTime, sDate
  */
void get_RTC(){
  HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);
}

// call to this function when an interrupt timer occurs  (set interrupt timer = 1s)
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == htim2.Instance){
		
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  RTC_AlarmTypeDef sAlarm = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 10;
  sTime.Minutes = 5;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
  sDate.Month = RTC_MONTH_JULY;
  sDate.Date = 6;
  sDate.Year = 22;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the Alarm A
  */
  sAlarm.AlarmTime.Hours = 0;
  sAlarm.AlarmTime.Minutes = 0;
  sAlarm.AlarmTime.Seconds = 20;
  sAlarm.AlarmTime.SubSeconds = 0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
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
static void MX_USART1_UART_Init(void)
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
static void MX_USART3_UART_Init(void)
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED_DO_Pin|LED_XANH_Pin|RESET_SIM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, PWRKEY_Pin|USIM_DET_Pin|SIM_DTR_Pin|SIM_RST_Pin
                          |OF_SIM_Pin|CE_BQ_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_DO_Pin LED_XANH_Pin RESET_SIM_Pin */
  GPIO_InitStruct.Pin = LED_DO_Pin|LED_XANH_Pin|RESET_SIM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PWRKEY_Pin USIM_DET_Pin SIM_DTR_Pin SIM_RST_Pin
                           OF_SIM_Pin CE_BQ_Pin */
  GPIO_InitStruct.Pin = PWRKEY_Pin|USIM_DET_Pin|SIM_DTR_Pin|SIM_RST_Pin
                          |OF_SIM_Pin|CE_BQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : CHG_Pin PGOOD_Pin Jack_PW_Pin */
  GPIO_InitStruct.Pin = CHG_Pin|PGOOD_Pin|Jack_PW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
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
