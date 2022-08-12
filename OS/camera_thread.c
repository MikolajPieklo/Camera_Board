#include <FreeRTOS.h>

#include <main.h>
#include <cmsis_os.h>

#include <camera.h>
#include <lcd.h>
#include <timestamp.h>
#include <st7789.h>

const osThreadAttr_t cameraTask_attributes =
{
   .name = "cameraTask",
   .stack_size = 128 * 4,
   .priority = (osPriority_t) osPriorityNormal,
};

extern uint16_t image[230*320*2];

void StartCameraTask(void *argument)
{
   static uint32_t i = 0;
   static uint32_t j = 0;
   static uint32_t offset = 0;

   ST7789_GPIO_Init();
   Lcd_Start();
   Camera_Init();
   Camera_Start();

   osDelayUntil(100);

   ST7789_SetWindow(0, 0, DisplayWidth - 1, DisplayHeight - 1);

   for(;;)
   {
      for(i = 0; i < 57600/2; i++)
      {
         uint32_t data = *((uint32_t*)image + i + offset);
         uint16_t data1 = (uint16_t)(data >> 16);
         uint16_t data2 = (uint16_t)data;
         ST7789_SetPixel((uint16_t)data1);
         ST7789_SetPixel((uint16_t)data2);
         j += 2;
         if (j == 240)
         {
            offset += 40;
            j = 0;
         }
      }
      j = 0;
      offset = 0;
   }
   osDelay(1);
}
