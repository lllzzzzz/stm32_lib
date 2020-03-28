#include "sdram_drv.h"
#include "lz_debug.h"

/**
  * @brief  Initial sdram
  * @note   Once the SDRAM controller is initialized, the SDRAM needs to be initialized 
  *         in the following order.
  * @param  hsdram : SDRAM handle 
  * @retval void
  */
void sdram_init_seq(SDRAM_HandleTypeDef *hsdram)
{
  FMC_SDRAM_CommandTypeDef cmd_struct;

  /* Enable clock */
  cmd_struct.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
  cmd_struct.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  cmd_struct.AutoRefreshNumber = 1;
  cmd_struct.ModeRegisterDefinition = 0;

  if (HAL_SDRAM_SendCommand(&hsdram1, &cmd_struct, 1000) != HAL_OK) //
  {
    PRINT_ERR("");
    Error_Handler();
  }

  HAL_Delay(1);

  /* Set to charge the storage area */
  cmd_struct.CommandMode = FMC_SDRAM_CMD_PALL;

  if (HAL_SDRAM_SendCommand(&hsdram1, &cmd_struct, 1000) != HAL_OK)
  {
    PRINT_ERR("");
    Error_Handler();
  }

  /* Set the number of self-refreshes */
  cmd_struct.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  cmd_struct.AutoRefreshNumber = 8;

  if (HAL_SDRAM_SendCommand(&hsdram1, &cmd_struct, 1000) != HAL_OK) //
  {
    PRINT_ERR("");
    Error_Handler();
  }

  /* Configuration register */
  cmd_struct.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  cmd_struct.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  cmd_struct.AutoRefreshNumber = 1;
  cmd_struct.ModeRegisterDefinition = SDRAM_MODEREG_BURST_LENGTH_1 |
                                      SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
                                      SDRAM_MODEREG_CAS_LATENCY_3 |
                                      SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                                      SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  if (HAL_SDRAM_SendCommand(&hsdram1, &cmd_struct, 1000) != HAL_OK) //
  {
    PRINT_ERR("");
    Error_Handler();
  }
}

/**
  * @brief  Write data to SDRAM
  * @note   
  * @param
  * @retval 
  */
void sdram_write(uint32_t addr, uint8_t *buf, uint32_t buf_len)
{
  for (; buf_len != 0; buf_len--)
  {
    *(uint8_t *)(Bank5_SDRAM_ADDR + addr) = *buf;
    addr++;
    buf++;
  }
}

/**
  * @brief  Read data from SDRAM
  * @note   
  * @param  
  * @retval 
  */
void sdram_read(uint32_t addr, uint8_t *buf, uint32_t buf_len)
{
  for (; buf_len != 0; buf_len--)
  {
    *buf++ = *(uint8_t *)(Bank5_SDRAM_ADDR + addr);
    addr++;
  }
}

/**
  * @brief  test
  * @note   
  * @param  
  * @retval 
  */
//uint16_t testsram[250000] __attribute__((at(0XC0000000))); //测试用数组

void fsmc_sdram_test(void)
{
  uint32_t temp = 0;
  uint32_t sval = 0; //在地址0读到的数据
  //每隔16K字节,写入一个数据,总共写入2048个数据,刚好是32M字节
  uint32_t i;
  for (i = 0; i < 32 * 1024 * 1024; i += 16 * 1024)
  {
    *(uint32_t *)(Bank5_SDRAM_ADDR + i) = temp;
    temp++;
  }
  //依次读出之前写入的数据,进行校验
  for (i = 0; i < 32 * 1024 * 1024; i += 16 * 1024)
  {
    temp = *(uint32_t *)(Bank5_SDRAM_ADDR + i);
    if (i == 0)
      sval = temp;
    else if (temp <= sval)
      break;                                                                 //后面读出的数据一定要比第一次读到的数据大.
    PRINT_INFO("SDRAM Capacity:%dKB\r\n", (uint16_t)(temp - sval + 1) * 16); //打印SDRAM容量
  }
}
