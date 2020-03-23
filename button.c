#include "button.h"

/**
  * @brief  button initial
  * @note   
  * @param
  * @retval 
  */
void button_init(button_t *p_button, button_cfg_t *p_button_cfg, void (*p_func_cb)(button_t *))
{
  p_button->cfg.deb_val = p_button_cfg->deb_val;
  p_button->cfg.deb_long_val = p_button_cfg->deb_long_val;
  p_button->func_cb = p_func_cb;
}

/**
  * @brief  button update
  * @note   
  * @param
  * @retval 
  */
void button_update(button_t *p_button, uint8_t button_in)
{
  if (button_in == p_button->buf)
  {
    if ((HAL_GetTick() - p_button->deb >= p_button->cfg.deb_val) && p_button->flg.change)
    {
      p_button->flg.change = 0;

      if (p_button->buf == 0)
      {
        /* down */
        p_button->flg.down = 1;

        p_button->state = DOWN;
        p_button->func_cb(p_button);

        p_button->combo++;
        if (p_button->combo >= p_button->cfg.combo_val)
        {
          p_button->state = COMBO;
          p_button->func_cb(p_button);
        }
      }
      else
      {
        /* up */
        p_button->flg.down = 0;

        p_button->state = UP;
        p_button->func_cb(p_button);
      }
    }
  }
  else
  {
    p_button->flg.change = 1;
    p_button->buf = button_in;
    p_button->deb = HAL_GetTick();
  }

  /* Long press processing */
  if ((HAL_GetTick() - p_button->deb >= p_button->cfg.deb_long_val) && p_button->flg.down)
  {
    p_button->flg.down = 0;
    p_button->state = LONG;
    p_button->func_cb(p_button);
  }
}
