#include "gpio.h"

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init()
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


/**
  * @brief Allow sim to work (wait x seconds)
  * @param Time (x second)
  * @retval None
  */
void wait_Enable_Sim(int x)
{

  HAL_GPIO_WritePin(OF_SIM_GPIO_Port ,OF_SIM_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RESET_SIM_GPIO_Port, RESET_SIM_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWRKEY_GPIO_Port, PWRKEY_Pin, GPIO_PIN_SET);

  HAL_GPIO_WritePin(LED_DO_GPIO_Port, LED_DO_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_XANH_GPIO_Port, LED_XANH_Pin, GPIO_PIN_RESET);

  for(int i=0; i < x; i++)
  {
    HAL_GPIO_TogglePin(LED_DO_GPIO_Port, LED_DO_Pin);
    HAL_GPIO_TogglePin(LED_XANH_GPIO_Port, LED_XANH_Pin);
    HAL_Delay(1000);
  }

  HAL_GPIO_WritePin(LED_DO_GPIO_Port, LED_DO_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_XANH_GPIO_Port, LED_XANH_Pin, GPIO_PIN_SET);
}
