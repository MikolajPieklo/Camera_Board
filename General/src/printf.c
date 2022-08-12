#include "printf.h"

#include <stdio.h>
#include <string.h>

#include <stm32f4xx_ll_usart.h>

#include <project_info.h>
#include <project_info_cfg.h>

void Project_Info_Print(void)
{
   printf("%s\n",               Get_Separator());
   printf("Project Name: %s\n", Get_Project_Name());
   printf("Build Date:   %s\n", Get_Build_Date());
   printf("Build Time:   %s\n", Get_Build_Time());
   printf("Build ID:     %s\n", Get_Version_Name());
   printf("User Name:    %s\n", Get_User_Name());
   printf("%s\n",               Get_Separator());
}

void USART_Printf(USART_TypeDef *USARTx,const uint8_t* text, bool newline)
{
   size_t len = strlen((char*)text);
   size_t idx = 0;
   while (idx < len)
   {
      LL_USART_TransmitData8(USARTx, *(text+idx));
      while(!LL_USART_IsActiveFlag_TC(USARTx));
      idx++;
   }
   if (true == newline)
   {
      LL_USART_TransmitData8(USARTx, '\n');
      while(!LL_USART_IsActiveFlag_TC(USARTx));
   }
}
