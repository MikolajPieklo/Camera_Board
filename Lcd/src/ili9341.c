/*
 * ILI9341.c
 *
 *  Created on: Aug 30, 2022
 *      Author: mkpk
 */

#include <ili9341.h>

#include <stdlib.h>

#include <stm32f4xx_fsmc.h>
#include <timestamp.h>
#include <FONT.h>

uint16_t POINT_COLOR=0x0000;
uint16_t BACK_COLOR=0xFFFF;
_lcd_dev lcddev;

void lcd_show_num(uint16_t y, uint16_t x, uint32_t num)
{
    uint8_t len = 0, size = 16;
    uint8_t t, temp;
    uint8_t enshow = 0;
    uint32_t n = num;

    //lcd_scan_dir(3);
    // �����ֳ���
    while(n)
    {
        n/=10;
        len++;
    }
    if(len == 0)
    {
        LCD_ShowChar(x, y, '0', size, 0);
    }

    // �ο������ļ� LCD_ShowxNum
    for(t = 0; t < len; t++)
    {
        temp = (num/LCD_Pow(10,len-t-1))%10;
        if( (enshow == 0)&&(t<(len-1)) )
        {
            if(temp == 0)
            {
                LCD_ShowChar(x+(size/2)*t, y, ' ', size, 0);
                continue;
            }
            else
            {
                enshow = 1;
            }
        }
        LCD_ShowChar(x+(size/2)*t, y, temp+'0', size, 0);
    }
    //lcd_scan_dir(5);
}

void LCD_WR_REG(uint16_t regval)
{
   regval = regval;
   LCD->LCD_REG = regval;
}

void LCD_WR_DATA(uint16_t data)
{
   data = data;
   LCD->LCD_RAM = data;
}

uint16_t LCD_RD_DATA(void)
{
   uint16_t ram;
   ram = LCD->LCD_RAM;
   return ram;
}

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
   LCD->LCD_REG = LCD_Reg;
   LCD->LCD_RAM = LCD_RegValue;
}

uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
   LCD_WR_REG(LCD_Reg);
   TS_Delay_ms(1);
   return LCD_RD_DATA();
}

void lcd_write_ram_prepare(void)
{
   LCD->LCD_REG = 0x2C;
}

void LCD_WriteRAM(uint16_t RGB_Code)
{
   LCD->LCD_RAM = RGB_Code;
}

void opt_delay(uint8_t i)
{
   while(i--);
}

uint16_t LCD_ReadPoint(uint16_t x, uint16_t y)
{
   uint16_t r=0,g=0,b=0;

   if(x >= 240 || y >= 320)
   {
      return 0;
   }

   lcd_set_cursor(x,y);
   LCD_WR_REG(0x2E);
   LCD_RD_DATA();//dummy Read
   opt_delay(2);
   r = LCD_RD_DATA();
   opt_delay(2);
   b = LCD_RD_DATA();
   g = r & 0xFF;
   g <<= 8;
   return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));
}

void lcd_set_cursor(uint16_t Xpos, uint16_t Ypos)
{
   LCD_WR_REG(0x2A);
   LCD_WR_DATA(Xpos >> 8);
   LCD_WR_DATA(Xpos & 0xFF);
   LCD_WR_REG(0x2B);
   LCD_WR_DATA(Ypos >> 8);
   LCD_WR_DATA(Ypos & 0XFF);
}

void LCD_DisplayOn(void)
{
   LCD_WR_REG(0x29);
}

void LCD_DisplayOff(void)
{
   LCD_WR_REG(0x28);
}

void LCD_DrawPoint(uint16_t x, uint16_t y)
{
   lcd_set_cursor(x, y);
   lcd_write_ram_prepare();
   LCD->LCD_RAM = POINT_COLOR;
}

void LCD_Fast_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
   LCD_WR_REG(0x2A);
   LCD_WR_DATA(x >> 8);
   LCD_WR_DATA(x & 0xFF);
   LCD_WR_REG(0x2B);
   LCD_WR_DATA(y >> 8);
   LCD_WR_DATA(y & 0XFF);
   LCD->LCD_REG = 0x2C;
   LCD->LCD_RAM = color;
}

void LCD_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
   uint8_t hsareg, heareg, vsareg, veareg;
   uint16_t hsaval, heaval, vsaval, veaval;
   width = sx + width - 1;
   height = sy + height - 1;

   LCD_WR_REG(0x2A);
   LCD_WR_DATA(sx>>8);
   LCD_WR_DATA(sx&0XFF);
   LCD_WR_DATA(width>>8);
   LCD_WR_DATA(width&0XFF);

   LCD_WR_REG(0x2B);
   LCD_WR_DATA(sy>>8);
   LCD_WR_DATA(sy&0XFF);
   LCD_WR_DATA(height>>8);
   LCD_WR_DATA(height&0XFF);
}

void fsmc_lcd_init(void)
{
//  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
//  FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;
//  FSMC_NORSRAMTimingInitTypeDef  writeTiming;
//  readWriteTiming.FSMC_AddressSetupTime = 0XF;   //��ַ����ʱ�䣨ADDSET��Ϊ16��HCLK 1/168M=6ns*16=96ns
//  readWriteTiming.FSMC_AddressHoldTime = 0x00;   //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�
//  readWriteTiming.FSMC_DataSetupTime = 24;         //���ݱ���ʱ��Ϊ25��HCLK   =6*25=150ns
//  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
//  readWriteTiming.FSMC_CLKDivision = 0x00;
//  readWriteTiming.FSMC_DataLatency = 0x00;
//  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;    //ģʽA
//
//
//  writeTiming.FSMC_AddressSetupTime =8;        //��ַ����ʱ�䣨ADDSET��Ϊ8��HCLK =48ns
//  writeTiming.FSMC_AddressHoldTime = 0x00;    //��ַ����ʱ�䣨A
//  writeTiming.FSMC_DataSetupTime = 8;      //���ݱ���ʱ��Ϊ6ns*9��HCLK=54ns
//  writeTiming.FSMC_BusTurnAroundDuration = 0x00;
//  writeTiming.FSMC_CLKDivision = 0x00;
//  writeTiming.FSMC_DataLatency = 0x00;
//  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;  //ģʽA
//
//
//  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  ��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
//  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ���������ݵ�ַ
//  FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM
//  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ��Ϊ16bit
//  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable;
//  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
//  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
//  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
//  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
//  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable; //  �洢��дʹ��
//  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
//  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ��дʹ�ò�ͬ��ʱ��
//  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
//  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //��дʱ��
//  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //дʱ��
//
//  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����
//
//  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // ʹ��BANK1

   //TS_Delay_ms(50);
   //LCD_WriteReg(0x0000,0x0001);
   //TS_Delay_ms(50); // delay 50 ms

   LCD_WR_REG(0xDA);                    //Read ID1
   lcddev.id1 = LCD_RD_DATA();          //dummy read
   lcddev.id1 = LCD_RD_DATA();          //0x--

   LCD_WR_REG(0xDB);                    //Read ID2
   lcddev.id2 = LCD_RD_DATA();          //dummy read
   lcddev.id2 = LCD_RD_DATA();          //0x--

   LCD_WR_REG(0xDC);                    //Read ID3
   lcddev.id3 = LCD_RD_DATA();          //dummy read
   lcddev.id3 = LCD_RD_DATA();          //0x--

   LCD_WR_REG(0xD3);                    //Read ID4
   lcddev.id4 = LCD_RD_DATA();          //dummy read
   lcddev.id4 = LCD_RD_DATA();          //0x00
   lcddev.id4 = (LCD_RD_DATA() << 8);   //0x93
   lcddev.id4 |= LCD_RD_DATA();         //0x41

   //��������дʱ����ƼĴ�����ʱ��
   FSMC_Bank1E->BWTR[6] &=~(0xF<<0);//��ַ����ʱ�䣨ADDSET������
   FSMC_Bank1E->BWTR[6] &=~(0xF<<8);//���ݱ���ʱ������
   FSMC_Bank1E->BWTR[6] |= 3<<0;      //��ַ����ʱ�䣨ADDSET��Ϊ3��HCLK =18ns
   FSMC_Bank1E->BWTR[6] |= 2<<8;   //���ݱ���ʱ��Ϊ6ns*3��HCLK=18ns

   //printf(" LCD ID:%x\r\n",lcddev.id); //��ӡLCD ID
   LCD_WR_REG(0x26);       //Gamma curve selected
   LCD_WR_DATA(0x01);

   LCD_WR_REG(0x2A);       //Column Address Set       0-239
   LCD_WR_DATA(0x00);
   LCD_WR_DATA(0x00);
   LCD_WR_DATA(0x00);
   LCD_WR_DATA(0xef);

   LCD_WR_REG(0x2B);       //Page Address Set         0-319
   LCD_WR_DATA(0x00);
   LCD_WR_DATA(0x00);
   LCD_WR_DATA(0x01);
   LCD_WR_DATA(0x3f);

   LCD_WR_REG(0x36);       //Memory Access Control    ?
   LCD_WR_DATA(0x48);

   LCD_WR_REG(0x3A);       //Pixel Format Set         16 bit
   LCD_WR_DATA(0x55);

   LCD_WR_REG(0xB1);       //Frame Control
   LCD_WR_DATA(0x00);
   LCD_WR_DATA(0x1A);

   LCD_WR_REG(0xB6);       //Display Function Control
   LCD_WR_DATA(0x0A);
   LCD_WR_DATA(0xA2);
//   LCD_WR_DATA(0x00);
//   LCD_WR_DATA(0x00);

   LCD_WR_REG(0xC0);       //Power control 1          3.40V
   LCD_WR_DATA(0x1B);

   LCD_WR_REG(0xC1);       //Power control 2
   LCD_WR_DATA(0x01);

   LCD_WR_REG(0xC5);       //VCOM control 1
   LCD_WR_DATA(0x30);      //3F
   LCD_WR_DATA(0x30);      //3C

   LCD_WR_REG(0xC7);       //VCOM control 2
   LCD_WR_DATA(0XB7);

   LCD_WR_REG(0xCB);       //Power control A
   LCD_WR_DATA(0x39);
   LCD_WR_DATA(0x2C);
   LCD_WR_DATA(0x00);
   LCD_WR_DATA(0x34);
   LCD_WR_DATA(0x02);

   LCD_WR_REG(0xCF);       //Power control B
   LCD_WR_DATA(0x00);
   LCD_WR_DATA(0xC1);
   LCD_WR_DATA(0X30);

   LCD_WR_REG(0xE0);       //Positive Gamma Correction
   LCD_WR_DATA(0x0F);
   LCD_WR_DATA(0x2A);
   LCD_WR_DATA(0x28);
   LCD_WR_DATA(0x08);
   LCD_WR_DATA(0x0E);
   LCD_WR_DATA(0x08);
   LCD_WR_DATA(0x54);
   LCD_WR_DATA(0XA9);
   LCD_WR_DATA(0x43);
   LCD_WR_DATA(0x0A);
   LCD_WR_DATA(0x0F);
   LCD_WR_DATA(0x00);
   LCD_WR_DATA(0x00);
   LCD_WR_DATA(0x00);
   LCD_WR_DATA(0x00);

   LCD_WR_REG(0XE1);       //Negative Gamma Correction
   LCD_WR_DATA(0x00);
   LCD_WR_DATA(0x15);
   LCD_WR_DATA(0x17);
   LCD_WR_DATA(0x07);
   LCD_WR_DATA(0x11);
   LCD_WR_DATA(0x06);
   LCD_WR_DATA(0x2B);
   LCD_WR_DATA(0x56);
   LCD_WR_DATA(0x3C);
   LCD_WR_DATA(0x05);
   LCD_WR_DATA(0x10);
   LCD_WR_DATA(0x0F);
   LCD_WR_DATA(0x3F);
   LCD_WR_DATA(0x3F);
   LCD_WR_DATA(0x0F);

   LCD_WR_REG(0xE8);       //Driver timing control A
   LCD_WR_DATA(0x85);
   LCD_WR_DATA(0x10);
   LCD_WR_DATA(0x7A);

   LCD_WR_REG(0xEA);       //Driver timing control B
   LCD_WR_DATA(0x00);
   LCD_WR_DATA(0x00);

   LCD_WR_REG(0xED);       //Power on sequence control
   LCD_WR_DATA(0x64);
   LCD_WR_DATA(0x03);
   LCD_WR_DATA(0X12);
   LCD_WR_DATA(0X81);

   LCD_WR_REG(0xF2);       //Enable 3G
   LCD_WR_DATA(0x00);

   LCD_WR_REG(0xF7);       //Pump ratio control
   LCD_WR_DATA(0x20);

   LCD_WR_REG(0x11);       //Exit Sleep
   TS_Delay_ms(120);

   LCD_WR_REG(0x29);       //display on

   LCD_WriteReg(0x36, 0xC8);

   LCD_WR_REG(0x2A); //Column Address Set
   LCD_WR_DATA(0);
   LCD_WR_DATA(0);
   LCD_WR_DATA(0);
   LCD_WR_DATA(0xEF);

   LCD_WR_REG(0x2B);//Page Address Set
   LCD_WR_DATA(0);
   LCD_WR_DATA(0);
   LCD_WR_DATA(0x01);
   LCD_WR_DATA(0x3F);

   lcd_clear(RED);

   LCD_DrawLine(0, 0, 50, 50);
}

void lcd_clear(uint16_t color)
{
   uint32_t index = 0;
   uint32_t totalpoint = 240;
   totalpoint *= 320;
   lcd_set_cursor(0x00, 0x0000);
   lcd_write_ram_prepare();
   for(index = 0; index < totalpoint; index++)
   {
      LCD->LCD_RAM = color;
   }
}

void LCD_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
   uint16_t i, j;
   uint16_t xlen = 0;
   uint16_t temp;

   xlen = ex - sx + 1;
   for(i = sy; i <= ey; i++)
   {
      lcd_set_cursor(sx, i);
      lcd_write_ram_prepare();
      for(j=0; j < xlen; j++)
      {
         LCD->LCD_RAM = color;
      }
   }
}

void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{
   uint16_t height,width;
   uint16_t i,j;
   width=ex-sx+1;          //�õ����Ŀ��
   height=ey-sy+1;         //�߶�
   for(i=0;i<height;i++)
   {
      lcd_set_cursor(sx,sy+i);      //���ù��λ��
      lcd_write_ram_prepare();     //��ʼд��GRAM
      for(j=0;j<width;j++)LCD->LCD_RAM=color[i*width+j];//д������
   }
}

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
   uint16_t t;
   int xerr=0,yerr=0,delta_x,delta_y,distance;
   int incx,incy,uRow,uCol;
   delta_x=x2-x1; //������������
   delta_y=y2-y1;
   uRow=x1;
   uCol=y1;
   if(delta_x>0)incx=1; //���õ�������
   else if(delta_x==0)incx=0;//��ֱ��
   else {incx=-1;delta_x=-delta_x;}
   if(delta_y>0)incy=1;
   else if(delta_y==0)incy=0;//ˮƽ��
   else{incy=-1;delta_y=-delta_y;}
   if( delta_x>delta_y)distance=delta_x; //ѡȡ��������������
   else distance=delta_y;
   for(t=0;t<=distance+1;t++ )//�������
   {
      LCD_DrawPoint(uRow,uCol);//����
      xerr+=delta_x ;
      yerr+=delta_y ;
      if(xerr>distance)
      {
         xerr-=distance;
         uRow+=incx;
      }
      if(yerr > distance)
      {
         yerr-= distance;
         uCol+= incy;
      }
   }
}

void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
   LCD_DrawLine(x1,y1,x2,y1);
   LCD_DrawLine(x1,y1,x1,y2);
   LCD_DrawLine(x1,y2,x2,y2);
   LCD_DrawLine(x2,y1,x2,y2);
}

void LCD_Draw_Circle_ili(uint16_t x0, uint16_t y0, uint8_t r)
{
   int a,b;
   int di;
   a=0;b=r;
   di=3-(r<<1);             //�ж��¸���λ�õı�־
   while(a<=b)
   {
      LCD_DrawPoint(x0+a,y0-b);             //5
      LCD_DrawPoint(x0+b,y0-a);             //0
      LCD_DrawPoint(x0+b,y0+a);             //4
      LCD_DrawPoint(x0+a,y0+b);             //6
      LCD_DrawPoint(x0-a,y0+b);             //1
      LCD_DrawPoint(x0-b,y0+a);
      LCD_DrawPoint(x0-a,y0-b);             //2
      LCD_DrawPoint(x0-b,y0-a);             //7
      a++;
      //ʹ��Bresenham�㷨��Բ
      if(di<0)di +=4*a+6;
      else
      {
         di+=10+4*(a-b);
         b--;
      }
   }
}

void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint8_t mode)
{
   uint8_t temp,t1,t;
   uint16_t y0=y;
   uint8_t csize=(size/8+((size%8)?1:0))*(size/2);      //�õ�����һ���ַ���Ӧ������ռ���ֽ���
   //���ô���
   num=num-' ';//�õ�ƫ�ƺ��ֵ
   for(t=0;t<csize;t++)
   {
      if (size == 12)
      {
         temp=asc2_1206[num][t];
      }
      else if (size==16)
      {
         temp=asc2_1608[num][t];
      }
      else if (size==24)
      {
         temp=asc2_2412[num][t];
      }
      else
         return;

      for(t1 = 0; t1 < 8; t1++)
      {
         if(temp&0x80)
            LCD_Fast_DrawPoint(x,y,POINT_COLOR);
         else if(mode==0)
            LCD_Fast_DrawPoint(x,y,BACK_COLOR);
         temp <<= 1;
         y++;
         if(y >= 320)
            return;
         if((y-y0)==size)
         {
            y=y0;
            x++;
            if(x >= 240)
               return;
            break;
         }
      }
   }
}

uint32_t LCD_Pow(uint8_t m, uint8_t n)
{
   uint32_t result = 1;
   while(n--)
   {
      result *= m;
   }
   return result;
}

void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size)
{
   uint8_t t,temp;
   uint8_t enshow=0;
   for(t=0;t<len;t++)
   {
      temp=(num/LCD_Pow(10,len-t-1))%10;
      if(enshow==0&&t<(len-1))
      {
         if(temp==0)
         {
            LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
            continue;
         }else enshow=1;

      }
      LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0);
   }
}

void LCD_ShowxNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode)
{
   uint8_t t, temp;
   uint8_t enshow = 0;
   for(t = 0; t < len; t++)
   {
      temp = (num /LCD_Pow(10, len-t-1)) % 10;
      if(enshow == 0 && t < (len-1))
      {
         if(temp == 0)
         {
            if(mode & 0X80)
               LCD_ShowChar(x+(size/2)*t, y, '0', size, (mode & 0X01));
            else
            {
               LCD_ShowChar(x+(size/2)*t, y, ' ', size, (mode & 0X01));
            }
            continue;
         }
         else
         {
            enshow = 1;
         }
      }
      LCD_ShowChar(x+(size/2)*t, y, temp+'0', size, (mode & 0X01));
   }
}

void LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint8_t *p)
{
   uint8_t x0 = x;
   width += x;
   height += y;
   while((*p <= '~') && (*p >= ' '))
   {
      if(x >= width)
      {
         x = x0;
         y += size;
      }
      if(y >= height)
      {
         break;
      }
      LCD_ShowChar(x, y, *p, size, 0);
      x += size/2;
      p++;
   }
}
