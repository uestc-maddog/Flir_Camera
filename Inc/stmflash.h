#ifndef __STMFLASH_H
#define __STMFLASH_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"                    // Device header
#include "stm32f4xx.h"                    // Device header

// FLASH 扇区的起始地址
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) 	//扇区0起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) 	//扇区1起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) 	//扇区2起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) 	//扇区3起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) 	//扇区4起始地址, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) 	//扇区5起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) 	//扇区6起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) 	//扇区7起始地址, 128 Kbytes 
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) 	//扇区8起始地址, 128 Kbytes 

// 系统参数存储
#define PARA_NUMS 10                              // 需要保存的参数个数 
#define PARA_SAVE_ADDR  ADDR_FLASH_SECTOR_7	      // 需要保存的参数的起始地址
//设置FLASH 保存地址(必须为4的倍数，且所在扇区,要大于本代码所占用到的扇区.
//否则,写操作的时候,可能会导致擦除整个扇区,从而引起部分程序丢失.引起死机.

// FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	// STM32 FLASH的起始地址
#define FLASH_WAITETIME  60000        // FLASH等待超时时间

uint8_t STMFLASH_GetFlashSector(uint32_t addr);     //获取某个地址所在的flash扇区
uint32_t STMFLASH_ReadWord(uint32_t faddr);		  	                             // 读出字  
void STMFLASH_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite);// 从指定地址开始写入指定长度的数据
void STMFLASH_Read(uint32_t ReadAddr,uint32_t *pBuffer,uint32_t NumToRead);   // 从指定地址开始读出指定长度的数据
//测试写入
void Test_Write(uint32_t WriteAddr,uint32_t WriteData);	
#endif
