#ifndef __BUTTON_H
#define __BUTTON_H
/* Includes ------------------------------------------------------------------*/
#include "lz_debug.h"
#include "stdint.h"
#include "main.h"

typedef enum button_state
{
  DOWN = 0,
  UP,
  LONG,
  COMBO,
} state_t;

typedef struct button_cfg
{
  uint32_t deb_val;
  uint32_t deb_long_val;
  uint8_t combo_val;
} button_cfg_t;

typedef struct button button_t;

typedef struct button
{
  struct
  {
    uint8_t change : 1;
    uint8_t down : 1;
  } flg;

  button_cfg_t cfg;

  uint8_t buf;
  uint32_t deb;
  uint32_t deb_long;
  uint8_t combo;

  state_t state;

  void (*func_cb)(button_t *);

} button_t;

void button_init(button_t *, button_cfg_t *, void (*)(button_t *));
void button_update(button_t *, uint8_t );

#endif
