#include "menufounction.h"
#include "lepton.h"
#include "lepton_i2c.h"
#include "flir_lcd.h"
#include "flir_compass.h"
#include "flir_menu.h"
#include "flir_focusing.h"
#include "electricity.h"
#include "key.h"
#include "stmflash.h"

extern TIM_HandleTypeDef htim3;
extern IWDG_HandleTypeDef hiwdg;
extern uint8_t SleepTime_Setting;


extern void Flir_Display(void);
bool set_reticle_mark=false;
/**
* name Brightnesschosen
* founction when chosen the brightness seting,display the set menu.
*
**/
void Brightnesschosen(void)
{
	BrightnessCont_sta BGL_value = flir_conf.flir_sys_Bright;
	
	KeyStatus Key_Value = Key_None;
	uint8_t timer = 0;

	display_Brightnessmenu(BGL_value);
#ifdef enable_iwdg
  HAL_IWDG_Refresh(&hiwdg);
#endif
	while(1)
	{
		HAL_Delay(50);
		Key_Value = Key_Scan();   
		if(Key_Value)
		{
			Time_Sleep = 0;                  // Sleep Time counter����
#ifdef enable_iwdg
			HAL_IWDG_Refresh(&hiwdg);
#endif
			timer = 0;
			if(Key_Value == Key_Short)        // �̰��л��˵���
			{
				if(++BGL_value == BGL_empty) BGL_value = Level1;
				display_Brightnessmenu(BGL_value);
#ifdef enable_iwdg
				HAL_IWDG_Refresh(&hiwdg);
#endif
			}
			if(Key_Value == Key_Long)
			{
				switch((int)BGL_value)         // �˵�����������
				{
					case (int)Level1:
						SET_BGLight(Level1);
						flir_conf.flir_sys_Bright = Level1;					
						display_Check(OP1_2_TH);
						break;
					case (int)Level2:
						SET_BGLight(Level2);
						flir_conf.flir_sys_Bright = Level2;
						display_Check(OP2_2_TH);
						break;
					case (int)Level3:
						SET_BGLight(Level3);
						flir_conf.flir_sys_Bright = Level3;
						display_Check(OP3_2_TH);
						break;
					case (int)Level4:
						SET_BGLight(Level4);
						flir_conf.flir_sys_Bright = Level4;
						display_Check(OP4_2_TH);
						break;

					case (int)BGL_Exit:
						timer = 200;                          // timer=200ʱ���˳��˵�����
						break;
				}
			}									
		}
#ifdef enable_iwdg
		HAL_IWDG_Refresh(&hiwdg);
#endif		
		if(timer++ == 200)                            // ����10s�ް�����Ӧ�����˳��˵�����
		{
			timer = 0;
			break;                      
		}
	}
}

/**
* name Sleepchosen
* founction when chosen the sleep time seting,display the set menu.
*
**/
void Sleepchosen(void)
{
	SleepCont_sta SLP_value = flir_conf.flir_sys_Sleep;
	KeyStatus Key_Value = Key_None;
	uint8_t timer = 0;

	display_Sleepmenu(SLP_value);
#ifdef enable_iwdg
  HAL_IWDG_Refresh(&hiwdg);
#endif
	while(1)
	{
		HAL_Delay(50);
		Key_Value = Key_Scan();   
		if(Key_Value)
		{
			Time_Sleep = 0;                  // Sleep Time counter����
#ifdef enable_iwdg
			HAL_IWDG_Refresh(&hiwdg);
#endif
			timer = 0;
			if(Key_Value == Key_Short)        // �̰��л��˵���
			{
				if(++SLP_value == SLP_empty) SLP_value = Minutes_3;
				display_Sleepmenu(SLP_value);
#ifdef enable_iwdg
				HAL_IWDG_Refresh(&hiwdg);
#endif
			}
			if(Key_Value == Key_Long)
			{
				switch((int)SLP_value)         // �˵�����������
				{
					case (int)Minutes_3:
						Time_Sleep = 0;
						HAL_TIM_Base_Start_IT(&htim3);       // ������ʱ��TIM3�ж�
						SleepTime_Setting = Time_Minu3;
						flir_conf.flir_sys_Sleep = Minutes_3;
						display_Check(OP1_2_TH);
						break;
					case (int)Minutes_5:
						Time_Sleep = 0;
						HAL_TIM_Base_Start_IT(&htim3);       // ������ʱ��TIM3�ж�
						SleepTime_Setting = Time_Minu5;
						flir_conf.flir_sys_Sleep = Minutes_5;
						display_Check(OP2_2_TH);
						break;
					case (int)Minutes_10:
						Time_Sleep = 0;
						HAL_TIM_Base_Start_IT(&htim3);       // ������ʱ��TIM3�ж�
						SleepTime_Setting = Time_Minu10;
						flir_conf.flir_sys_Sleep = Minutes_10;
						display_Check(OP3_2_TH);
						break;
					case (int)Minutes_15:
						Time_Sleep = 0;
						HAL_TIM_Base_Start_IT(&htim3);       // ������ʱ��TIM3�ж�
						SleepTime_Setting = Time_Minu15;
						flir_conf.flir_sys_Sleep = Minutes_15;
						display_Check(OP4_2_TH);
						break;
					case (int)Minutes_NA:
						HAL_TIM_Base_Stop_IT(&htim3);         // �رն�ʱ��TIM3�ж�  Time_SleepһֱΪ0
						Time_Sleep = 0;
						SleepTime_Setting = Time_Minu15;      // Time_Sleep != Time_Sleep,��ϵͳ�����ػ�
						flir_conf.flir_sys_Sleep = Minutes_NA;
						display_Check(OP5_2_TH);
						break;
					case (int)SLP_Exit:
						timer = 200;                         // timer=200ʱ���˳��˵�����
						break;
				}
			}									
		}
#ifdef enable_iwdg
		HAL_IWDG_Refresh(&hiwdg);
#endif
		if(timer++ == 200)                           // ����10s�ް�����Ӧ�����˳��˵�����
		{
			timer = 0;
			break;                      
		}
	}
}

/**
* name Versionchosen
* founction when chosen the vertion seting,display the Version message.
*
**/
void Versionchosen(void)
{
	uint8_t timer = 0;

	display_Versionmenu();
#ifdef enable_iwdg
  HAL_IWDG_Refresh(&hiwdg);
#endif
	while(1)
	{
		HAL_Delay(500);
#ifdef enable_iwdg
		HAL_IWDG_Refresh(&hiwdg);
#endif
		if(timer++ == 6)                            // ����3s�ް�����Ӧ�����˳��˵�����
		{
			timer = 0;
			break;                      
		}
	}
}

/**
* name set_reticle
* founction when chosen the reticle seting,to here.
*
**/
flir_reticle_sta reticle_sta=reticle_able;
void set_reticle(void)
{
	reticle_sta=reticle_able;
	uint16_t timer = 0;
	while(1)
	{
		set_reticle_mark=true;    // �����˵���־����Ϊtrue
		Flir_Display();	          // Flir����
		KeyStatus Key_Value = Key_None;
		Key_Value = Key_Scan();                
		if(Key_Value)
		{
			Time_Sleep = 0;                  // Sleep Time counter����
#ifdef enable_iwdg
			HAL_IWDG_Refresh(&hiwdg);
#endif
			timer = 0;
			if(Key_Value == Key_Short)           // �����Ķ�ѡ��
			{
				switch((int)reticle_sta)
				{
					case reticle_able:
						if(flir_conf.flir_sys_Focus == focus_enable) 
						{
							flir_conf.flir_sys_Focus = focus_disable;                     // focus����״̬��ת
						}
						else                                         
						{
							flir_conf.flir_sys_Focus = focus_enable;	                    // focus����״̬��ת
						}							
					break;
					case reticle_Hor:
						Hor++;
						if(Hor>18)
							Hor=0;
						flir_conf.flir_sys_Reticle[0]=Hor*4-36;
					break;
					case reticle_Ver:
						Ver++;
						if(Ver>18)
							Ver=0;
						flir_conf.flir_sys_Reticle[1]=Ver*6-54;
					break;
					case reticle_back:
						timer=4000;
					break;
					default :
						timer=4000;
					break;
				}
			}
			if(Key_Value == Key_Long)            // �̰��л�ѡ��
			{
				if(++reticle_sta == reticle_empty) reticle_sta = reticle_able;
			}
		}
#ifdef enable_iwdg
		HAL_IWDG_Refresh(&hiwdg);
#endif
		if(timer++ >= 4000)                            // ����10s�ް�����Ӧ�����˳��˵�����
		{
			timer = 0;
			break;                      
		}
		
	}
	set_reticle_mark=false;
}

