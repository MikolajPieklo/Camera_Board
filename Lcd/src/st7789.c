#include <stdlib.h>
#include <string.h>

#include <st7789.h>

#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_spi.h>

#include <font_36.h>
#include <timestamp.h>



typedef struct LCD_Tag
{
   uint16_t Background_color;
} LCD_t;

LCD_t l_lcd;

void ST7789_GPIO_Init(void)
{
   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

   LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);

   LL_GPIO_SetPinSpeed       (LCD_RES_GPIO_PORT, LCD_RES_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (LCD_RES_GPIO_PORT, LCD_RES_GPIO_PIN, LL_GPIO_MODE_OUTPUT);
   LL_GPIO_SetPinOutputType  (LCD_RES_GPIO_PORT, LCD_RES_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetPinPull        (LCD_RES_GPIO_PORT, LCD_RES_GPIO_PIN, LL_GPIO_PULL_NO);
   LL_GPIO_SetOutputPin      (LCD_RES_GPIO_PORT, LCD_RES_GPIO_PIN);

   LL_GPIO_SetPinSpeed       (LCD_DC_GPIO_PORT, LCD_DC_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (LCD_DC_GPIO_PORT, LCD_DC_GPIO_PIN, LL_GPIO_MODE_OUTPUT);
   LL_GPIO_SetPinOutputType  (LCD_DC_GPIO_PORT, LCD_DC_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetPinPull        (LCD_DC_GPIO_PORT, LCD_DC_GPIO_PIN, LL_GPIO_PULL_NO);
   LL_GPIO_SetOutputPin      (LCD_DC_GPIO_PORT, LCD_DC_GPIO_PIN);

   LL_GPIO_SetPinSpeed       (LCD_BLK_GPIO_PORT, LCD_BLK_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (LCD_BLK_GPIO_PORT, LCD_BLK_GPIO_PIN, LL_GPIO_MODE_OUTPUT);
   LL_GPIO_SetPinOutputType  (LCD_BLK_GPIO_PORT, LCD_BLK_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetPinPull        (LCD_BLK_GPIO_PORT, LCD_BLK_GPIO_PIN, LL_GPIO_PULL_NO);
   LL_GPIO_SetOutputPin      (LCD_BLK_GPIO_PORT, LCD_BLK_GPIO_PIN);

   //PC3  - SPI2_MOSI
   //PB10 - SPI2_CLK
   LL_GPIO_SetPinMode        (GPIOC, LL_GPIO_PIN_3, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinSpeed       (GPIOC, LL_GPIO_PIN_3, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinPull        (GPIOC, LL_GPIO_PIN_3, LL_GPIO_PULL_NO);
   LL_GPIO_SetAFPin_0_7      (GPIOC, LL_GPIO_PIN_3, LL_GPIO_AF_5);

   LL_GPIO_SetPinMode        (GPIOB, LL_GPIO_PIN_10, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinSpeed       (GPIOB, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinPull        (GPIOB, LL_GPIO_PIN_10, LL_GPIO_PULL_NO);
   LL_GPIO_SetAFPin_8_15     (GPIOB, LL_GPIO_PIN_10, LL_GPIO_AF_5);

   LL_SPI_InitTypeDef spi2;

   spi2.TransferDirection = LL_SPI_HALF_DUPLEX_TX;
   spi2.Mode = LL_SPI_MODE_MASTER;
   spi2.DataWidth = LL_SPI_DATAWIDTH_8BIT;
   spi2.ClockPolarity = LL_SPI_POLARITY_HIGH;
   spi2.ClockPhase = LL_SPI_PHASE_2EDGE;
   spi2.NSS = LL_SPI_NSS_SOFT;
   spi2.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2; /* 42MHz / 2 = 21MHz */
   spi2.BitOrder = LL_SPI_MSB_FIRST;
   spi2.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
   spi2.CRCPoly = 0x00;

   LL_SPI_Init(SPI2, &spi2);
   LL_SPI_Enable(SPI2);
}

void ST7789_Reset()
{
   LL_GPIO_ResetOutputPin(LCD_RES_GPIO_PORT, LCD_RES_GPIO_PIN);
   TS_Delay_ms(1);
   LL_GPIO_SetOutputPin(LCD_RES_GPIO_PORT, LCD_RES_GPIO_PIN);
   TS_Delay_ms(1);
}

void ST7789_Init()
{
   ST7789_SendCommand(0x11); //Sleep Out
   TS_Delay_ms(1);

   ST7789_SendCommand(0x36); //MADCTL: Memory Data Access Control
   ST7789_SendData(0x00);

   ST7789_SendCommand(0x3A); //COLMOD: Interface Pixel Format 16bit/pixel
   ST7789_SendData(0x05);

   ST7789_SendCommand(0xB2); //PORCTRL: Porch Setting
   ST7789_SendData(0x0C);
   ST7789_SendData(0x0C);

   ST7789_SendCommand(0xB7); //GCTRL: Gate Control
   ST7789_SendData(0x35);

   ST7789_SendCommand(0xBB); //VCOMS: VCOM Setting
   ST7789_SendData(0x1A);

   ST7789_SendCommand(0xC0); //LCMCTRL: LCM Control
   ST7789_SendData(0x2C);

   ST7789_SendCommand(0xC2); //VDVVRHEN: VDV and VRH Command Enable
   ST7789_SendData(0x01);

   ST7789_SendCommand(0xC3); //VRHS: VRH Set
   ST7789_SendData(0x0B);

   ST7789_SendCommand(0xC4); //VDVS (C4h): VDV Set
   ST7789_SendData(0x20);

   ST7789_SendCommand(0xC6); //FRCTRL2: Frame Rate Control in Normal Mode
   ST7789_SendData(0x0F);

   ST7789_SendCommand(0xD0); //PWCTRL1: Power Control 1
   ST7789_SendData(0xA4);
   ST7789_SendData(0xA1);

   ST7789_SendCommand(0x21); //INVON: Display Inversion On

   ST7789_SendCommand(0xE0); //PVGAMCTRL: Positive Voltage Gamma Control
   ST7789_SendData(0x00);
   ST7789_SendData(0x19);
   ST7789_SendData(0x1E);
   ST7789_SendData(0x0A);
   ST7789_SendData(0x09);
   ST7789_SendData(0x15);
   ST7789_SendData(0x3D);
   ST7789_SendData(0x44);
   ST7789_SendData(0x51);
   ST7789_SendData(0x12);
   ST7789_SendData(0x03);
   ST7789_SendData(0x00);
   ST7789_SendData(0x3F);
   ST7789_SendData(0x3F);

   ST7789_SendCommand(0xE1); //NVGAMCTRL: Negative Voltage Gamma Control
   ST7789_SendData(0x00);
   ST7789_SendData(0x18);
   ST7789_SendData(0x1E);
   ST7789_SendData(0x0A);
   ST7789_SendData(0x09);
   ST7789_SendData(0x25);
   ST7789_SendData(0x3F);
   ST7789_SendData(0x43);
   ST7789_SendData(0x52);
   ST7789_SendData(0x33);
   ST7789_SendData(0x03);
   ST7789_SendData(0x00);
   ST7789_SendData(0x3F);
   ST7789_SendData(0x3F);

   ST7789_SendCommand(0x29); //DISPON: Display On

   TS_Delay_ms(1);
}

void ST7789_SetPixel(uint16_t color)
{
   ST7789_SendData((uint8_t)(color >> 8));
   ST7789_SendData((uint8_t)(color & 0xFF));
}

void ST7789_SendChar(const uint8_t c)
{
   uint16_t i = 0;
   uint16_t j = 0;
   const uint8_t* p;

   for(i = 0; i < 126; i++)
   {
      p = &Font.chars[c-32].image->data[i];
      for(j = 0; j < 8; j++)
      {
         if((*p & (0x80>>j)) != 0)
         {
            ST7789_SendData(0x00);
            ST7789_SendData(0x00);
         }
         else
         {
            ST7789_SetPixel(l_lcd.Background_color);
         }
      }
   }
}

void ST7789_SendCommand(uint8_t data)
{
   LL_GPIO_ResetOutputPin(LCD_DC_GPIO_PORT, LCD_DC_GPIO_PIN);
   LL_SPI_TransmitData8(SPI2, data);
   while(!LL_SPI_IsActiveFlag_TXE(SPI2));
}

void ST7789_SendData(uint8_t data)
{
   LL_GPIO_SetOutputPin(LCD_DC_GPIO_PORT, LCD_DC_GPIO_PIN);
   LL_SPI_TransmitData8(SPI2, data);
   while(!LL_SPI_IsActiveFlag_TXE(SPI2));
}

void ST7789_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1,  uint16_t y1)
{
   ST7789_SendCommand(ST7789_CASET);//Column addr set
   ST7789_SendData(x0 >> 8);
   ST7789_SendData(x0);             // XSTART
   ST7789_SendData(x1 >> 8);
   ST7789_SendData(x1);             // XEND
   ST7789_SendCommand(ST7789_RASET);//Row addr set
   ST7789_SendData(y0 >> 8);
   ST7789_SendData(y0);             //YSTART
   ST7789_SendData(y1 >> 8);
   ST7789_SendData(y1);             // YEND
   ST7789_SendCommand(ST7789_RAMWR);//write to RAM
}

void ST7789_SendText(const uint8_t* text, uint16_t h)
{
   uint8_t i = 0;
   uint8_t len = strlen((const char*)text);

   for(i = 0; i < len; i++)
   {
      ST7789_SetWindow(50 + 23 * i, 73 + 23 * i, h, h + 41);
      ST7789_SendChar(*(text + i));
   }
}
