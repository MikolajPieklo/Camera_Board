#include <stdint.h>

#define COLOR_RGB_565_BLACK    0x0000
#define COLOR_RGB_565_BLUE     0x001F
#define COLOR_RGB_565_GREEN    0x07E0
#define COLOR_RGB_565_RED      0xF800
#define COLOR_RGB_565_CYAN     0x07FF
#define COLOR_RGB_565_MAGENTA  0xF81F
#define COLOR_RGB_565_YELLOW   0xFFE0
#define COLOR_RGB_565_PURPLE   0xC219
#define COLOR_RGB_565_WHITE    0xFFFF

typedef struct Image_Tag
{
   const uint16_t *data;
   uint16_t width;
   uint16_t height;
   uint8_t dataSize;
} Image_t;

void Lcd_Start(void);

void LCD_Draw_Rectangle (uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1, uint16_t color);
void LCD_Draw_Line      (uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1, uint16_t color, int16_t thickness);
void LCD_Draw_Circle    (uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color, int16_t Fill);
void LCD_Draw_Bitmap_565(Image_t Bitmap);
