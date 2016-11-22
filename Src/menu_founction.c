#include "menufounction.h"
#include "lepton.h"
#include "lepton_i2c.h"
#include "flir_lcd.h"
#include "flir_compass.h"
#include "flir_menu.h"
#include "flir_focusing.h"
#include "electricity.h"
#include "key.h"
#include "temprature.h"
#include "stmflash.h"

extern TIM_HandleTypeDef htim3;
extern IWDG_HandleTypeDef hiwdg;
extern uint8_t SleepTime_Setting;
extern float Sys_temprature;                   

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
	uint8_t timer = 0;                           // 粗略计时

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
			timer = 0;
			Time_Sleep = 0;                  // Sleep Time counter归零
			
#ifdef enable_iwdg
			HAL_IWDG_Refresh(&hiwdg);
#endif
			
			if(Key_Value == Key_Short)        // 短按切换菜单栏
			{
				if(++BGL_value == BGL_empty) BGL_value = Level1;
				display_Brightnessmenu(BGL_value);
				
#ifdef enable_iwdg
				HAL_IWDG_Refresh(&hiwdg);
#endif
			}
			if(Key_Value == Key_Long)
			{
				switch((int)BGL_value)         // 菜单栏二级功能
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
						timer = 200;                          // timer=200时，退出菜单界面
						break;
				}
			}									
		}
		
#ifdef enable_iwdg
		HAL_IWDG_Refresh(&hiwdg);
#endif		
		
		if(timer++ == 200) break;                           // 超过10s无按键响应，则退出菜单界面
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
			timer = 0;
			Time_Sleep = 0;                  // Sleep Time counter归零
			
#ifdef enable_iwdg
			HAL_IWDG_Refresh(&hiwdg);
#endif
			
			if(Key_Value == Key_Short)        // 短按切换菜单栏
			{
				if(++SLP_value == SLP_empty) SLP_value = Minutes_3;
				display_Sleepmenu(SLP_value);
				
#ifdef enable_iwdg
				HAL_IWDG_Refresh(&hiwdg);
#endif
			}
			if(Key_Value == Key_Long)
			{
				switch((int)SLP_value)         // 菜单栏二级功能
				{
					case (int)Minutes_3:
						Time_Sleep = 0;
						HAL_TIM_Base_Start_IT(&htim3);       // 开启定时器TIM3中断
						flir_conf.flir_sys_Sleep = Minutes_3;
						display_Check(OP1_2_TH);
						break;
					case (int)Minutes_5:
						Time_Sleep = 0;
						HAL_TIM_Base_Start_IT(&htim3);       // 开启定时器TIM3中断
						flir_conf.flir_sys_Sleep = Minutes_5;
						display_Check(OP2_2_TH);
						break;
					case (int)Minutes_10:
						Time_Sleep = 0;
						HAL_TIM_Base_Start_IT(&htim3);       // 开启定时器TIM3中断
						flir_conf.flir_sys_Sleep = Minutes_10;
						display_Check(OP3_2_TH);
						break;
					case (int)Minutes_15:
						Time_Sleep = 0;
						HAL_TIM_Base_Start_IT(&htim3);       // 开启定时器TIM3中断
						flir_conf.flir_sys_Sleep = Minutes_15;
						display_Check(OP4_2_TH);
						break;
					case (int)Minutes_NA:
						HAL_TIM_Base_Stop_IT(&htim3);         // 关闭定时器TIM3中断  Time_Sleep一直为0
						Time_Sleep = 0;
						flir_conf.flir_sys_Sleep = Minutes_NA;
						display_Check(OP5_2_TH);
						break;
					case (int)SLP_Exit:
						timer = 200;                         // timer=200时，退出菜单界面
						break;
				}
			}									
		}
		
#ifdef enable_iwdg
		HAL_IWDG_Refresh(&hiwdg);
#endif
		
		if(timer++ == 200) break;                           // 超过10s无按键响应，则退出菜单界面
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
		
		if(timer++ == 8) break;                            // 超过4s无按键响应，则退出菜单界面
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
	reticle_sta = reticle_able;
	uint16_t timer = 0;
	KeyStatus Key_Value = Key_None;
	Hor = (flir_conf.flir_sys_Reticle[0] + 36)/4;
	Ver = (flir_conf.flir_sys_Reticle[1] + 54)/6;
	while(1)
	{
		set_reticle_mark=true;    // 二级菜单标志量设为true
		Flir_Display();	          // Flir界面
		
		Key_Value = Key_Scan();                
		if(Key_Value)
		{
			HAL_Delay(100);
			timer = 0;
			Time_Sleep = 0;                  // Sleep Time counter归零
			
#ifdef enable_iwdg
			HAL_IWDG_Refresh(&hiwdg);
#endif
			
			if(Key_Value == Key_Short)           // 长按改动选项
			{
				switch((int)reticle_sta)
				{
					case reticle_able:
						if(flir_conf.flir_sys_Focus == focus_enable) flir_conf.flir_sys_Focus = focus_disable;                     // focus开关状态反转
						else                                         flir_conf.flir_sys_Focus = focus_enable;	                     // focus开关状态反转                        						
						break;
					case reticle_Hor:
						if(++Hor > 18) Hor = 0;
						flir_conf.flir_sys_Reticle[0] = Hor*4-36;
						break;
					case reticle_Ver:
						if(++Ver > 18) Ver = 0;
						flir_conf.flir_sys_Reticle[1] = Ver*6-54;
					break;
					case reticle_back:
						timer = 4000;
					break;
					default :
						timer = 4000;
					break;
				}
			}
			if(Key_Value == Key_Long)            // 短按切换选项
			{
				if(flir_conf.flir_sys_Focus == focus_enable) 
				{
					if(++reticle_sta == reticle_empty) reticle_sta = reticle_able;
				}
				else                                         
				{
					if(reticle_sta == reticle_able)      reticle_sta = reticle_back;
					else if(reticle_sta == reticle_back) reticle_sta = reticle_able;
					else                                 reticle_sta = reticle_able;
				}				
			}
		}
#ifdef enable_iwdg
		HAL_IWDG_Refresh(&hiwdg);
#endif
		if(timer % 300 == 0) Sys_temprature = Get_Temprate();             // 刷新温度值
		
		if(timer++ >= 4000)                            // 超过10s无按键响应，则退出菜单界面
		{
			timer = 0;
			break;                      
		}
	}
	set_reticle_mark=false;
}

