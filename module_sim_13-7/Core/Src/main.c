/* information code


*/

#include "main.h"
#include "AT.h"
#include "uart.h"
#include "system.h"
#include "gpio.h"
      

const int TEN_SECOND = 10;

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_UART4_Init();
	MX_USART1_UART_Init();
	MX_USART3_UART_Init();

  wait_Enable_Sim(TEN_SECOND);

	while (1)	
	{

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
