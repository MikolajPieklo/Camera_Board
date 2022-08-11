#include <stdint.h>

#define ST7789_CASET 0x2A
#define ST7789_RASET 0x2B
#define ST7789_RAMWR 0x2C

#define LCD_RES_GPIO_PIN      LL_GPIO_PIN_0
#define LCD_RES_GPIO_PORT     GPIOC
#define LCD_DC_GPIO_PIN       LL_GPIO_PIN_1
#define LCD_DC_GPIO_PORT      GPIOC
#define LCD_BLK_GPIO_PIN      LL_GPIO_PIN_2
#define LCD_BLK_GPIO_PORT     GPIOC

#define DisplayWidth 240
#define DisplayHeight 240

void ST7789_GPIO_Init(void);
void ST7789_Init(void);
void ST7789_Reset(void);

void ST7789_SendCommand(uint8_t data);
void ST7789_SendData(uint8_t data);
void ST7789_SetWindow(uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end);

void ST7789_SetPixel(uint16_t color);
void ST7789_SendChar(const uint8_t c);
void ST7789_SendText(const uint8_t* text, uint16_t h);
