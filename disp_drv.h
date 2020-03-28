#ifndef __DISP_DRV_H
#define __DISP_DRV_H

#include "stdint.h"

struct screen_info
{
  uint16_t ID;
  uint16_t width;
  uint16_t height;
};

void LTDC_Fill(uint16_t , uint16_t , uint16_t , uint16_t , uint32_t );

#endif
