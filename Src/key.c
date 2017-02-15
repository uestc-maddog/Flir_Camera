/*-----------------------------------------------------------------
 * Name:    key.c   
 * Purpose: key driver  
 *-----------------------------------------------------------------
 * 
 * Copyright (c) *reserve
 
||                       _      _               ||
||    /\  /\  __  _  __ | | __ | | ____  ___ _  ||
||   /  \/  \/ _ ` |/ _ ` |/ _ ` |/ _  \/ _ ` | ||
||  / /\  /\  (_|    (_|    (_|    (_)   (_)  | ||
|| /_/  \/  \_.__, |\__, _|\__, _|\____/\___. | ||
|| =====================================|____/  ||
||                                              ||

 -----------------------------------------------------------------*/
 
/********************************************************************************************************
 *                                               INCLUDES
 ********************************************************************************************************/
#include "stm32f4xx_hal.h"
#include "key.h"
#include "electricity.h"
#include "menufounction.h"
#include "flir_lcd.h"
/********************************************************************************************************
 *                                                 MACROS
 ********************************************************************************************************/


/********************************************************************************************************
 *                                               CONSTANTS
 ********************************************************************************************************/

 
/********************************************************************************************************
 *                                               GLOBAL VARIABLES
 ********************************************************************************************************/
uint8_t  Key_Up = 0;
uint8_t  Key_Down = 0;
uint32_t Time_1ms = 0;                 // ����ʱ�䲶��
bool return_mark = false;              // true: Mode������
volatile int Time_Sleep = 0;           // Sleep Time counter
extern int index_x,index_y; //????
extern uint8_t Hor,Ver;   //��׼��ˮƽ����  0-19  ��Ӧ-9��9
/********************************************************************************************************
 *                                               EXTERNAL VARIABLES
 ********************************************************************************************************/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern IWDG_HandleTypeDef hiwdg;
extern PA_sta PAValue;                    // ͼ��Ŵ�ϵ��
/********************************************************************************************************
 *                                               EXTERNAL FUNCTIONS
 ********************************************************************************************************/


/********************************************************************************************************
 *                                               LOCAL VARIABLES
 ********************************************************************************************************/

 
/********************************************************************************************************
 *                                               LOCAL FUNCTIONS
 ********************************************************************************************************/

 
/********************************************************************************************************
 *                                               PUBLIC FUNCTIONS
 ********************************************************************************************************/
 
/*********************************************************************
 * @fn        Key_Scan()
 *
 * @brief     ����ɨ������ 
 *
 * @param     None
 *
 * @return    Key_None��������Ч   Key_Short�������̰�   Key_Long����������
 */
KeyStatus Key_Scan(void)
{
	if(Key_Down == 1)
	{
		if(Time_1ms > Long_Thre && return_mark == false)       
		{
			return_mark = true;
			return Key_Long;         // ��������ʱ�����2s      ����
		}
	}
	if(Key_Up == 1)        // �а�������
	{
		Key_Up = 0;
		Key_Down = 0;

		if(Time_1ms > Short_Thre && return_mark == false) 
		{
			return Key_Short;        // ��������ʱ��С��2s      �̰� 
		}		
		else if(Time_1ms > Long_Thre && return_mark == false) 
		{
			return Key_Long;        // ��������ʱ��da��2s        ���� 
		}		
		else                           
		{
			return_mark = false;
			return Key_None;         // ������������
		}
	}
	return Key_None;
}
/*********************************************************************
 * @fn        HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)()
 *
 * @brief     TIM2 detection callbacks.
 *
 * @param     htim�����ö�ʱ���ṹ��   
 *
 * @return    None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the __HAL_TIM_PeriodElapsedCallback could be implemented in the user file
   */
	if(htim->Instance == TIM2) Time_1ms++; 
	if(htim->Instance == TIM3) Time_Sleep++;
}
/*********************************************************************
 * @fn        HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)()
 *
 * @brief     EXTI line detection callbacks.
 *
 * @param     GPIO_Pin: Specifies the pins connected EXTI line  
 *
 * @return    None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  static uint8_t CAPTURE_STA = 0;	   // ����״̬
	
	/* Prevent unused argument(s) compilation warning */
	UNUSED(GPIO_Pin);
		/* NOTE: This function Should not be modified, when the callback is needed,
						 the HAL_GPIO_EXTI_Callback could be implemented in the user file
		 */
	if(GPIO_Pin == GPIO_PIN_0)           // PBSTAT���£��жϣ�
	{
		if(!(GPIOB->IDR&0x0001))           // PB0�½���    
		{
			if(flir_conf.file_sys_LowPower == Not_LowPower) 
			{
				HAL_Delay(500);
#ifdef enable_iwdg
				HAL_IWDG_Refresh(&hiwdg);
#endif
				HAL_Delay(500);HAL_Delay(450);     
#ifdef enable_iwdg
				HAL_IWDG_Refresh(&hiwdg);
#endif
				if(!(GPIOB->IDR&0x0001))    // ����   �ػ�
				{
					flir_conf.file_sys_LowPower = Is_LowPower;        // ״̬�л�
					setSandby();                     // ����͹���ģʽ
				}
				else                        // �̰�   �л�����
				{
					Time_Sleep = 0;                  // Sleep Time counter����
					if((++PAValue) > PAValue3) PAValue = PAValue1;
					if(PAValue == PAValue1)  //�Ŵ�1X������Ŵ�ƫ����
					{
						flir_conf.flir_sys_Reticle[0] = flir_conf.flir_sys_Reticle[0]*2/3+(index_x*2-60);
						flir_conf.flir_sys_Reticle[1] = flir_conf.flir_sys_Reticle[1]*2/3+(index_y*2-80);
						if(flir_conf.flir_sys_Reticle[0] > 36) flir_conf.flir_sys_Reticle[0]=36;
						if(flir_conf.flir_sys_Reticle[0] < -36) flir_conf.flir_sys_Reticle[0]=-36;
						if(flir_conf.flir_sys_Reticle[1] > 54) flir_conf.flir_sys_Reticle[1]=54;
						if(flir_conf.flir_sys_Reticle[1] < -54) flir_conf.flir_sys_Reticle[1]=-54;
						Hor = (flir_conf.flir_sys_Reticle[0] + 36)/4;
						Ver = (flir_conf.flir_sys_Reticle[1] + 54)/6;
					}
					if(PAValue == PAValue2)  //�Ŵ�1.5X������Ŵ�ƫ����
					{
						index_x=(flir_conf.flir_sys_Reticle[0]+60)/2;
						index_y=(flir_conf.flir_sys_Reticle[1]+80)/2;
						flir_conf.flir_sys_Reticle[0] = 0;
						flir_conf.flir_sys_Reticle[1] = 0;
						if(index_x > 40) 
						{
							flir_conf.flir_sys_Reticle[0] = (index_x - 40)*3;
							index_x = 40;
						}
						if(index_x < 20) 
						{
							flir_conf.flir_sys_Reticle[0] = (index_x - 20)*3;
							index_x = 20;
						}
						if(index_y > 53) 
						{
							flir_conf.flir_sys_Reticle[1] = (index_y - 53)*3;
							index_y = 53;
						}
						if(index_y < 27) 
						{
							flir_conf.flir_sys_Reticle[1] = (index_y - 27)*3;
							index_y = 27;
						}
						Hor = (flir_conf.flir_sys_Reticle[0] + 36)/4;
						Ver = (flir_conf.flir_sys_Reticle[1] + 54)/6;
					}
					if(PAValue == PAValue3)  //�Ŵ�2X ����Ŵ�ƫ����
					{
						index_x=index_x + (flir_conf.flir_sys_Reticle[0]/3);
						index_y=index_y + (flir_conf.flir_sys_Reticle[1]/3);
						flir_conf.flir_sys_Reticle[0] = 0;
						flir_conf.flir_sys_Reticle[1] = 0;
						if(index_x > 45) 
						{
							flir_conf.flir_sys_Reticle[0] = (index_x - 45)*4;
							index_x = 45;
						}
						if(index_x < 15) 
						{
							flir_conf.flir_sys_Reticle[0] = (index_x - 15)*4;
							index_x = 15;
						}
						if(index_y > 60)
						{
							flir_conf.flir_sys_Reticle[1] = (index_y - 60)*4;
							index_y = 60;
						}
						if(index_y < 20) 
						{
							flir_conf.flir_sys_Reticle[1] = (index_y - 20)*4;
							index_y = 20;
						}
						Hor = (flir_conf.flir_sys_Reticle[0] + 36)/4;
						Ver = (flir_conf.flir_sys_Reticle[1] + 54)/6;
					}
					HAL_Delay(100);
				}
			}
			else
			{		
				SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
												 SysTick_CTRL_TICKINT_Msk   |
												 SysTick_CTRL_ENABLE_Msk;  			
				flir_conf.file_sys_LowPower = Not_LowPower;       // ״̬�л�
				flir_conf.file_sys_PBWakeup = PBWakeup_Down;      // ���PBSTA�������Ѽ�����
				Save_Parameter();                                 // ����9��ϵͳ������FLASH
				/*  SoftReset  */
				HAL_PWREx_DisableFlashPowerDown();
				__set_FAULTMASK(1);                               // �ر������ж�
				NVIC_SystemReset();                               // �����λ
			}
		}
	}
	if(GPIO_Pin == GPIO_PIN_12)          // �����ж�
	{
		GPIO_InitTypeDef GPIO_InitStruct;
		
		GPIO_InitStruct.Pin = GPIO_PIN_12;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		
		if(CAPTURE_STA == 1)               // �Ѿ����񵽰�������
		{
			GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			
			HAL_TIM_Base_Stop_IT(&htim2);    // �������£��رն�ʱ��TIM2
			Key_Up = 1;
			CAPTURE_STA = 0;
		}
		else                               // ��δ���񵽰�������
		{
			GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;   
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			
			Key_Down = 1;
			Time_1ms = 0;
			HAL_TIM_Base_Start_IT(&htim2);   // �������£�������ʱ��TIM2
			CAPTURE_STA = 1;
		}
	}
	else if(GPIO_Pin == GPIO_PIN_15)     // ����ж�
	{
		SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
										 SysTick_CTRL_TICKINT_Msk   |
										 SysTick_CTRL_ENABLE_Msk;  
		HAL_Delay(500);

		if(!(GPIOA->IDR&0x8000))           // �½��أ�������
		{
			if(flir_conf.file_sys_LowPower == Not_LowPower)  // ��Stopģʽ��������ģʽ
			{
				flir_conf.file_sys_chargingMode = charging;
			}
			else
			{
				flir_conf.file_sys_LowPower = Not_LowPower;       // ״̬�л�

				/*  SoftReset  */
				HAL_PWREx_DisableFlashPowerDown();
				__set_FAULTMASK(1);                               // �ر������ж�
				NVIC_SystemReset();                               // �����λ
			}
		}
		else                                // �Ͻ��أ��˳����
		{
			flir_conf.file_sys_chargingMode = normal; 
		}
	}
}
 /********************************************************************************************************
 *                                               LOCAL FUNCTIONS
 ********************************************************************************************************/

/*********************************************************************
 * @fn      
 *
 * @brief   
 *
 * @param   
 *
 * @return  
 */
 
 


/*********************************************************************
 */
