#ifndef __DISP_DRV_H
#define __DISP_DRV_H

#include "stdint.h"

struct screen_info
{
  uint16_t ID;
  uint16_t width;
  uint16_t height;
  uint8_t pixsize;
};

void fill_rect(uint16_t , uint16_t , uint16_t , uint16_t , uint32_t );
void write_point(uint16_t x, uint16_t y, uint32_t color);
uint32_t read_point(uint16_t x, uint16_t y);

#endif
