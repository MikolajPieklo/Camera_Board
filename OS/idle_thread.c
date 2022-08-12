#include <FreeRTOS.h>

#include <main.h>
#include <cmsis_os.h>

const osThreadAttr_t idleTask_attributes =
{
   .name = "idleTask",
   .stack_size = 128 * 4,
   .priority = (osPriority_t) osPriorityNormal,
};

void StartIdleTask(void *argument)
{
   for(;;)
   {
      LL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
      osDelayUntil(200);
   }
   osDelay(1);
}
