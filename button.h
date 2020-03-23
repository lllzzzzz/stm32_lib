#ifndef __BUTTON_H
#define __BUTTON_H
/* Includes ------------------------------------------------------------------*/
#include "lz_debug.h"
#include "stdint.h"

typedef enum button_state
{
  DOWN = 0,
  UP,
  LONG,
} state_t;

typedef struct button_cfg
{
  uint8_t deb_val;
  uint8_t deb_long_val;
  uint8_t combo_val;
} button_cfg_t;

typedef struct button button_t;

typedef struct button
{
  struct
  {
    uint8_t change : 1;
  } flg;

  button_cfg_t cfg;

  uint8_t buf;
  uint8_t deb;
  uint8_t deb_long;
  uint8_t combo;

  state_t state;

  void (*func_cb)(button_t *);

} button_t;

#endif
