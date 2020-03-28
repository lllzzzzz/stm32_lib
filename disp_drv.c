#include "disp_drv.h"
#include "lz_debug.h"
#include "ltdc.h"
#include "dma2d.h"

const struct screen_info sreen_akt = 
{
  .ID = 0X4342,
  .width = 480,
  .height = 272,
};

/**
  * @brief  Initial sdram
  * @note   ltdc_fill
  * @param  hsdram : SDRAM handle 
  * @retval void
  */
void LTDC_Fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color)
{
  uint16_t c_x0, c_y0, c_x1, c_y1; //以LCD面板为基准的坐标系,不随横竖屏变化而变化

  //坐标系转换
  c_x0 = y0;
  c_y0 = sreen_akt.height - x1 - 1;
  c_x1 = y1;
  c_y1 = sreen_akt.height - x0 - 1;
 
  __HAL_RCC_DMA2D_CLK_ENABLE();   //使能DM2D时钟
  // DMA2D->CR &= ~(DMA2D_CR_START); //先停止DMA2D
  // DMA2D->CR = DMA2D_R2M;          //寄存器到存储器模式
  // DMA2D->OPFCCR = 0X02;           //设置颜色格式
  // DMA2D->OOR = offline;           //设置行偏移

  // DMA2D->OMAR = (0xc0000000 + 2 * (sreen_akt.width * c_y0 + c_x0));                                     //输出存储器地址
  // DMA2D->NLR = (c_y1 - c_y0 + 1) | ((c_x1 - c_x0 + 1) << 16); //设定行数寄存器
  // DMA2D->OCOLR = color;                                   //设定输出颜色寄存器
  // DMA2D->CR |= DMA2D_CR_START;                            //启动DMA2D
  //   uint32_t time_out = 0;
  // while ((DMA2D->ISR & (DMA2D_FLAG_TC)) == 0)             //等待传输完成
  // {
  //   time_out++;
  //   if (time_out > 0X1FFFFF)
  //     break; //超时退出
  // }
  // DMA2D->IFCR |= DMA2D_FLAG_TC; //清除传输完成标志
  /* DMA config */
  
  uint32_t dst_address = (uint32_t)(0xc0000000 + 2 * (sreen_akt.width * c_y0 + c_x0));

  HAL_DMA2D_ConfigLayer(&hdma2d, 1);
  HAL_DMA2D_Start(&hdma2d, color, dst_address, c_x1 - c_x0 + 1, c_y1 - c_y0 + 1);
  HAL_DMA2D_PollForTransfer(&hdma2d, 100);


}
