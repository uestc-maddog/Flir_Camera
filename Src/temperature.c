/*-----------------------------------------------------------------
 * Name:    temprature.h  
 * Purpose: stm32f411 internal_temprature driver include  
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
#include "temprature.h"

#include "stdint.h"
#include "flir_lcd.h"
#include "flir_menu.h"
#include "key.h"
#include "electricity.h"
#include "stmflash.h"

/********************************************************************************************************
 *                                                 MACROS
 ********************************************************************************************************/
const float Vref = 3.0425;                // �°�
//const float Vref = 3.3395;              // �ɰ�
/********************************************************************************************************
 *                                               CONSTANTS
 ********************************************************************************************************/
 
const uint8_t temp_number[10][10] = 
{
	{ 254, 198, 146, 146, 146, 146, 146, 146, 198, 254},       // 0
	{ 254, 230, 198, 134, 166, 230, 230, 230, 230, 254},       // 1
	{ 254, 198, 146, 242, 242, 230, 206, 158, 130, 254},       // 2
	{ 254, 198, 146, 242, 230, 242, 242, 146, 198, 254},       // 3
	{ 254, 242, 226, 210, 210, 178, 128, 242, 242, 254},       // 4
	{ 254, 194, 206, 158, 134, 178, 242, 146, 198, 254},       // 5
	{ 254, 198, 146, 158, 134, 146, 146, 146, 198, 254},       // 6
	{ 254, 130, 242, 230, 230, 206, 206, 206, 206, 254},       // 7
	{ 254, 198, 146, 146, 198, 146, 146, 146, 198, 254},       // 8
	{ 254, 198, 146, 146, 146, 194, 242, 146, 198, 254}        // 9
};
 
/********************************************************************************************************
 *                                               GLOBAL VARIABLES
 ********************************************************************************************************/

/********************************************************************************************************
 *                                               EXTERNAL VARIABLES
 ************************************ ********************************************************************/
extern ADC_HandleTypeDef hadc1;
extern SPI_HandleTypeDef hspi1;
extern DMA_HandleTypeDef LCD_DMA_PORT;

extern uint16_t rowBuf[FLIR_LCD_RAW][FLIR_LCD_COLUMNUM];
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
 * @fn        Get_Adc()
 *
 * @brief     ���ĳ��ͨ��ADC��ֵ  
 *
 * @param     ch��ADC_Channel 
 *
 * @return    ADC�Ĵ���ֵ
 */
uint16_t  Get_Adc(uint32_t ch)
{
	uint16_t ADC_Temp = 0;
	ADC_ChannelConfTypeDef ADC1_ChanConf;
		
	ADC1_ChanConf.Channel=ch;                                   // ͨ��
	ADC1_ChanConf.Rank=1;                                       // 1������
	ADC1_ChanConf.SamplingTime=ADC_SAMPLETIME_3CYCLES;          // ����ʱ��
	ADC1_ChanConf.Offset=0;                 
	HAL_ADC_ConfigChannel(&hadc1,&ADC1_ChanConf);               // ͨ������

	HAL_ADC_Start(&hadc1);                                      // ����ADC
 	if(HAL_ADC_PollForConversion(&hadc1,2) == HAL_OK)
	{
		 ADC_Temp = HAL_ADC_GetValue(&hadc1);
	}
	HAL_ADC_Stop(&hadc1);
	return ADC_Temp;	            //�������һ��ADC1�������ת�����
}

/*********************************************************************
 * @fn        Get_Adc_Average()
 *
 * @brief     �õ�ĳ��ͨ����������������ƽ��ֵ
 *
 * @param     ch��ADC_Channel     times:��������
 *
 * @return    ��������������ƽ��ֵ
 */
uint16_t Get_Adc_Average(uint32_t ch,uint8_t times)
{
	uint32_t temp_val=0;
	uint8_t t;
	
	for(t=0;t<times;t++)
	{
		temp_val += Get_Adc(ch);
	}
	return temp_val / times;
}

/*********************************************************************
 * @fn        Get_Temprate()
 *
 * @brief     ��ȡSTM32F411�ڲ��¶ȴ��������¶�ֵ
 *
 * @param     None  
 *
 * @return    STM32F411�ڲ��¶ȴ��������¶�ֵ
 */
short Get_Temprate(void)
{
 	uint32_t adcx;
 	double temperate = 0;
	
	adcx=Get_Adc(ADC_CHANNEL_TEMPSENSOR);    //��ȡ�ڲ��¶ȴ�����ͨ��
	temperate=(float)adcx*(Vref/4096);		   //��ѹֵ
	temperate=(temperate-0.76)/0.0025 + 25;  //ת��Ϊ�¶�ֵ 		
	
	return (float)temperate;
}

/*********************************************************************
 * @fn      display_Versionmenu
 *
 * @brief   display current temprature Message
 *
 * @param   none
 *
 * @return  
 */
void display_Temperature(float temp)
{
	uint16_t index;
	uint16_t i;
	uint8_t Temp_Value = 0;
	
	short temprature = (short)(temp * 1.80f + 32);    // �����¶�ת�����¶�
	
	// ��ʾ�¶�  
	Temp_Value = temprature / 100;      // �¶�ֵ    ��λ
	// block sending
	if(Temp_Value != 0)
	{
		for(index = 0; index < 10; index++)
		{
			for(i = 0; i < 7; i++)         // ���ֵķֱ��ʽ�Ϊ10 x 7
			{
				if(((temp_number[Temp_Value][(index * (16/2) + i) >> 3] >> (7 - (index * (16/2) + i)%8)) & 0x01) != 0x01)
					rowBuf[index+3][1+i] = 0xE007;
			}
		}
	}
	Temp_Value = temprature / 10 % 10;   // �¶�ֵ    ʮλ
	// block sending
	for(index = 0; index < 10; index++)
	{
		for(i = 0; i < 7; i++)          // ���ֵķֱ��ʽ�Ϊ10 x 7
		{
			if(((temp_number[Temp_Value][(index * (16/2) + i) >> 3] >> (7 - (index * (16/2) + i)%8)) & 0x01) != 0x01)
				rowBuf[index+3][8+i] = 0xE007;
		}
	}
	
	Temp_Value = temprature % 10;        // �¶�ֵ    ��λ
	// block sending
	for(index = 0; index < 10; index++)
	{
		for(i = 0; i < 7; i++)             // ���ֵķֱ��ʽ�Ϊ10 x 7
		{
			if(((temp_number[Temp_Value][(index * (16/2) + i) >> 3] >> (7 - (index * (16/2) + i)%8)) & 0x01) != 0x01)
				rowBuf[index+3][15+i]=0xE007;
		}
	}
}

/*********************************************************************
 * @fn      display_Versionmenu
 *
 * @brief   display current Countdown Message
 *
 * @param   none
 *
 * @return  
 */
void display_Countdown(void)
{
	uint16_t index;
	uint16_t i = 0, j = 0, k = 0;
	uint8_t Temp_Value = 0;
	uint8_t minute = 0, second = 0;
	int countdown = 0;
		
	if(flir_conf.flir_sys_Sleep != Minutes_NA)
	{
		// ���㵹��ʱ  hour  minute
		switch((int)flir_conf.flir_sys_Sleep)
		{
			case (int)Minutes_3:
				countdown = Time_Minu3 - Time_Sleep;    
				break;
			case (int)Minutes_5:
				countdown = Time_Minu5 - Time_Sleep;
				break;
			case (int)Minutes_10:
				countdown = Time_Minu10 - Time_Sleep;
				break;
			case (int)Minutes_15:
				countdown = Time_Minu15 - Time_Sleep;
				break;
			default :
				break;
		}
		if(countdown < 21)              // 20~0����ʱ����ʾ����Ļ����
		{
			Temp_Value = countdown / 10;             // second    ʮλ
			// block sending
			for(index = 0; index < 10; index++)
			{
				for(i = 0; i < 7; i++)             // ���ֵķֱ��ʽ�Ϊ10 x 7
				{
					if(((temp_number[Temp_Value][(index * (16/2) + i) >> 3] >> (7 - (index * (16/2) + i)%8)) & 0x01) != 0x01)
					{
						for(j = 0; j < 4 ; j++)        // 10 x 7 ����4����ʾ
						{
							for(k = 0; k < 4 ; k++)
							{
								rowBuf[35+index*4+j][20+i*4+k] = 0xE007;  // ��ʾ���꣨40��70��;
								//rowBuf[35+index*4+j][20+i*4+k] = 0x0FFFF - rowBuf[35+index*4+j][20+i*4+k];  // ��ʾ���꣨40��70��
							}
						}
					}
				}
			}			
			
			Temp_Value = countdown % 10;             // second    ��λ
			// block sending
			for(index = 0; index < 10; index++)
			{
				for(i = 0; i < 7; i++)             // ���ֵķֱ��ʽ�Ϊ10 x 7
				{
					if(((temp_number[Temp_Value][(index * (16/2) + i) >> 3] >> (7 - (index * (16/2) + i)%8)) & 0x01) != 0x01)
					{
						for(j = 0; j < 4 ; j++)        // 10 x 7 ����4����ʾ
						{
							for(k = 0; k < 4 ; k++)
							{
								rowBuf[35+index*4+j][120+i*4+k] = 0xE007;
								//rowBuf[35+index*4+j][120+i*4+k] = 0x0FFFF - rowBuf[35+index*4+j][120+i*4+k]; // ��ʾ���꣨40��110��
							}
						}
					}
				}
			}			
		}
		else
		{
			minute = countdown / 60;
			second = countdown % 60;
			
			// ��ʾ����ʱ   minute
			Temp_Value = minute / 10;             // minute    ʮλ
			for(index = 0; index < 10; index++)
			{
				for(i = 0; i < 7; i++)          // ���ֵķֱ��ʽ�Ϊ10 x 7
				{
					if(((temp_number[Temp_Value][(index * (16/2) + i) >> 3] >> (7 - (index * (16/2) + i)%8)) & 0x01) != 0x01)
						rowBuf[index+3][62+i] = 0xE007;
				}
			}
			
			Temp_Value = minute % 10;             // minute    ��λ
			// block sending
			for(index = 0; index < 10; index++)
			{
				for(i = 0; i < 7; i++)             // ���ֵķֱ��ʽ�Ϊ10 x 7
				{
					if(((temp_number[Temp_Value][(index * (16/2) + i) >> 3] >> (7 - (index * (16/2) + i)%8)) & 0x01) != 0x01)
						rowBuf[index+3][69+i]=0xE007;
				}
			}
			
			// ��ʾ����ʱ ":"
			rowBuf[5][78] = 0xE007;
			rowBuf[5][79] = 0xE007;
			rowBuf[6][78] = 0xE007;
			rowBuf[6][79] = 0xE007;
			rowBuf[10][78] = 0xE007;
			rowBuf[10][79] = 0xE007;
			rowBuf[11][78] = 0xE007;
			rowBuf[11][79] = 0xE007;
			
			// ��ʾ����ʱ   second
			Temp_Value = second / 10;             // second    ʮλ
			for(index = 0; index < 10; index++)
			{
				for(i = 0; i < 7; i++)          // ���ֵķֱ��ʽ�Ϊ10 x 7
				{
					if(((temp_number[Temp_Value][(index * (16/2) + i) >> 3] >> (7 - (index * (16/2) + i)%8)) & 0x01) != 0x01)
						rowBuf[index+3][83+i] = 0xE007;
				}
			}
			
			Temp_Value = second % 10;             // second    ��λ
			// block sending
			for(index = 0; index < 10; index++)
			{
				for(i = 0; i < 7; i++)             // ���ֵķֱ��ʽ�Ϊ10 x 7
				{
					if(((temp_number[Temp_Value][(index * (16/2) + i) >> 3] >> (7 - (index * (16/2) + i)%8)) & 0x01) != 0x01)
						rowBuf[index+3][90+i]=0xE007;
				}
			}
		}
		// Sleep Time����ʱ��
		if(countdown <= 0)    
		{
			HAL_Delay(500);
			flir_conf.file_sys_LowPower = Is_LowPower;        // ״̬�л���Stop Mode
			setSandby();
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
