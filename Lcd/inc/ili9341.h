/*
 * ili9341.h
 *
 *  Created on: Aug 30, 2022
 *      Author: mkpk
 */

#ifndef LCD_INC_ILI9341_H_
#define LCD_INC_ILI9341_H_

#include <stdint.h>
#include <stdlib.h>

void lcd_show_image(uint16_t m[80][80]);
void lcd_show_num(uint16_t y, uint16_t x, uint32_t num);

/****************** ����Ϊ����ԭ��lcd.hԴ�� www.opendv.com *******************/
//LCD��Ҫ������
typedef struct
{
//   uint16_t width;        //LCD ���
//   uint16_t height;       //LCD �߶�
   uint8_t  id1;          //LCD ID1
   uint8_t  id2;          //LCD ID2
   uint8_t  id3;          //LCD ID3
   uint16_t id4;          //LCD ID4
   //uint8_t  dir;       //���������������ƣ�0��������1��������
   //uint16_t   wramcmd;    //��ʼдgramָ��
   //uint16_t  setxcmd;     //����x����ָ��
   //uint16_t  setycmd;     //����y����ָ��
}_lcd_dev;

//LCD����
extern _lcd_dev lcddev; //����LCD��Ҫ����
//LCD�Ļ�����ɫ�ͱ���ɫ
extern uint16_t  POINT_COLOR;//Ĭ�Ϻ�ɫ
extern uint16_t  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//////////////////////////////////////////////////////////////////////////////////
//-----------------LCD�˿ڶ���----------------
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //���
#define  LCD_LED PBout(15)       //LCD����          PB15
//LCD��ַ�ṹ��
typedef struct
{
   uint16_t LCD_REG;
   uint16_t LCD_RAM;
} LCD_TypeDef;
//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A6��Ϊ��������������
//ע������ʱSTM32�ڲ�������һλ����! 111 1110=0X7E
#define LCD_BASE        ((uint32_t)(0x6C000000 | 0x0000007E))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
//////////////////////////////////////////////////////////////////////////////////

//ɨ�跽����
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���

#define DFT_SCAN_DIR  L2R_U2D  //Ĭ�ϵ�ɨ�跽��

//������ɫ
#define WHITE            0xFFFF
#define BLACK            0x0000
#define BLUE             0x001F
#define BRED             0XF81F
#define GRED          0XFFE0
#define GBLUE         0X07FF
#define RED              0xF800
#define MAGENTA          0xF81F
#define GREEN            0x07E0
#define CYAN             0x7FFF
#define YELLOW           0xFFE0
#define BROWN         0XBC40 //��ɫ
#define BRRED         0XFC07 //�غ�ɫ
#define GRAY          0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE         0X01CF  //����ɫ
#define LIGHTBLUE        0X7D7C  //ǳ��ɫ
#define GRAYBLUE         0X5458 //����ɫ
//������ɫΪPANEL����ɫ

#define LIGHTGREEN       0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY         0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

void fsmc_lcd_init(void);                                            //��ʼ��
void LCD_DisplayOn(void);                                      //����ʾ
void LCD_DisplayOff(void);                                     //����ʾ
void lcd_clear(uint16_t color);                                     //����
void lcd_set_cursor(uint16_t Xpos, uint16_t Ypos);                             //���ù��
void LCD_DrawPoint(uint16_t x,uint16_t y);                               //����
void LCD_Fast_DrawPoint(uint16_t x,uint16_t y,uint16_t color);                      //���ٻ���
uint16_t  LCD_ReadPoint(uint16_t x,uint16_t y);                                  //����
void LCD_Draw_Circle_ili(uint16_t x0,uint16_t y0,uint8_t r);                         //��Բ
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);                   //����
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);                    //������
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);                   //��䵥ɫ
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color);            //���ָ����ɫ
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode);                  //��ʾһ���ַ�
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size);                   //��ʾһ������
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);          //��ʾ ����
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p);    //��ʾһ���ַ���,12/16����
uint32_t LCD_Pow(uint8_t m,uint8_t n);
void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);
uint16_t LCD_ReadReg(uint16_t LCD_Reg);
void lcd_write_ram_prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
void LCD_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height);//���ô���


#endif /* LCD_INC_ILI9341_H_ */
