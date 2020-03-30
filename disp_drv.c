#include "disp_drv.h"
#include "lz_debug.h"
#include "ltdc.h"
#include "dma2d.h"

const struct screen_info sreen_atk =
    {
        .ID = 0X4342,
        .width = 480,
        .height = 272,
        .pixsize = 2,
};

/**
  * @brief  fill_rect
  * @note   fill_rect
  * @param  hsdram : SDRAM handle 
  * @retval void
  */
void fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color)
{
  uint16_t c_x0, c_y0, c_x1, c_y1;

  /* Coordinate transformation */
  c_x0 = y0;
  c_y0 = sreen_atk.height - x1 - 1;
  c_x1 = y1;
  c_y1 = sreen_atk.height - x0 - 1;

  /* DMA configure */
  uint16_t offset = sreen_atk.width - (c_x1 - c_x0 + 1);
  uint32_t dst_address = (uint32_t)(0xc0000000 + sreen_atk.pixsize * (sreen_atk.width * c_y0 + c_x0));

  hdma2d.Init.OutputOffset = offset;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
    ;
  {
    Error_Handler();
  }
  if (HAL_DMA2D_Start(&hdma2d, color, dst_address, c_x1 - c_x0 + 1, c_y1 - c_y0 + 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* DMA transfer */
  if (HAL_DMA2D_PollForTransfer(&hdma2d, 100) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  write_point
  * @note   fill_rect
  * @param  hsdram : SDRAM handle 
  * @retval void
  */
void write_point(uint16_t x, uint16_t y, uint32_t color)
{
  *(uint16_t *)((uint32_t)0xc0000000 + sreen_atk.pixsize * (sreen_atk.width * (sreen_atk.height - x - 1) + y)) = color;
}

/**
  * @brief  drow_point
  * @note   fill_rect
  * @param  hsdram : SDRAM handle 
  * @retval void
  */
uint32_t read_point(uint16_t x, uint16_t y)
{
  return *(uint16_t *)((uint32_t)0xc0000000 + sreen_atk.pixsize * (sreen_atk.width * (sreen_atk.height - x - 1) + y));
}
