/**
* @file Camera.c
* @brief Source file of the camera.
*
* @author Mikolaj Pieklo
* @date 17.04.2022
*/

#include <stdbool.h>
#include <stdio.h>

#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_rcc.h>

#include <camera.h>
#include <camera_datatypes.h>
#include <camera_registers.h>

#include <dcmi_hal.h>
#include <dma_hal.h>
#include <iic_hal.h>
#include <mco_hal.h>
#include <timestamp.h>

#define CAMERA_RESET_PIN          LL_GPIO_PIN_7
#define CAMERA_RESET_GPIO_Port    GPIOA

#define CAMERA_PWDn_PIN           LL_GPIO_PIN_1
#define CAMERA_PWDn_GPIO_Port     GPIOE

#define OV7670_WRITE_ADDR         0x42

__attribute__((section(".EXTRAM")))uint16_t image[CAMERA_BUFFER];

static void camera_gpio_init(void);
static ErrorStatus ov7725_init(void);

static void camera_gpio_init(void)
{
   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);

   LL_GPIO_SetPinSpeed       (CAMERA_RESET_GPIO_Port, CAMERA_RESET_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (CAMERA_RESET_GPIO_Port, CAMERA_RESET_PIN, LL_GPIO_MODE_OUTPUT);
   LL_GPIO_SetPinOutputType  (CAMERA_RESET_GPIO_Port, CAMERA_RESET_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetPinPull        (CAMERA_RESET_GPIO_Port, CAMERA_RESET_PIN, LL_GPIO_PULL_NO);
   LL_GPIO_SetOutputPin      (CAMERA_RESET_GPIO_Port, CAMERA_RESET_PIN);

   LL_GPIO_SetPinSpeed       (CAMERA_PWDn_GPIO_Port, CAMERA_PWDn_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (CAMERA_PWDn_GPIO_Port, CAMERA_PWDn_PIN, LL_GPIO_MODE_OUTPUT);
   LL_GPIO_SetPinOutputType  (CAMERA_PWDn_GPIO_Port, CAMERA_PWDn_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetPinPull        (CAMERA_PWDn_GPIO_Port, CAMERA_PWDn_PIN, LL_GPIO_PULL_NO);
   LL_GPIO_ResetOutputPin    (CAMERA_PWDn_GPIO_Port, CAMERA_PWDn_PIN);
}

static ErrorStatus ov7725_init(void)
{
   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_COM7 , 0x80);//Reset Registers
   TS_Delay_ms(10);

   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_CLKRC, 0x01); // 10fps 16Mhz/(7+1)/2
   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_EXHCH, 0x00);
   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_EXHCL, 0x00);
   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_DM_LNL,0x00);
   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_DM_LNH,0x00);
   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_ADVFL, 0x00);
   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_ADVFH, 0x00);
   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_COM2,  0x00);// Output drive capability 1x
   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_COM3,  0b10000000);
   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_COM4,  0x40); // PLL 4x
   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_COM7 , 0b01000110);// QVGA, BT.656, RGB565, RGB
   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_COM9 , 0b00010110); //test
   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_COM10, 0b00000000); // HREF changes to HSYNC

//   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_HREF,  0b00001000); //
//   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_REG16, 0b10000000); //

//   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_SCAL0, 0x00001111);
//   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_SCAL1, 0xFF);
//   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_SCAL1, 0xFF);
//   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_DSPAuto, 0x00);
//
//   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_DSP_Ctrl1, 0b00011111);
//   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_DSP_Ctrl2, 0x00);
//   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_DSP_Ctrl3, 0b10001110);
//   I2C_Master_Transmit_Byte(OV7670_WRITE_ADDR, OV7725_R_DSP_Ctrl4, 0b00000001);

   return SUCCESS;
}

void Camera_Init(void)
{
   uint8_t rxdata[2];
   camera_gpio_init();
   MCO1_Init();
   I2C_Init();
   DCMI_Initialize();

   DMA_Init();
   DCMI_Enable();

   TS_Delay_ms(1);
   Camera_Reset();

   ov7725_init();

   I2C_Master_Recesive(OV7670_WRITE_ADDR, OV7725_R_PID, false, rxdata, 2);
   printf("PID: 0x%x%x\r\n", rxdata[0], rxdata[1]);

   I2C_Master_Recesive(OV7670_WRITE_ADDR, OV7725_R_MIDH, false, rxdata, 2);
   printf("MID: 0x%x%x\r\n", rxdata[0], rxdata[1]);

   I2C_Master_Recesive(OV7670_WRITE_ADDR, OV7725_R_COM7, false, rxdata, 1);
   printf("COM7: 0x%x\r\n", rxdata[0]);

   I2C_Master_Recesive(OV7670_WRITE_ADDR, OV7725_R_HSTART, false, rxdata, 1);
   printf("HSTART: 0x%x\r\n", rxdata[0]);
};

void Camera_Reset(void)
{
   uint8_t txdata = 0x80;
   LL_GPIO_SetOutputPin(CAMERA_PWDn_GPIO_Port, CAMERA_PWDn_PIN);
   LL_GPIO_ResetOutputPin(CAMERA_RESET_GPIO_Port, CAMERA_RESET_PIN);
   TS_Delay_ms(10);

   LL_GPIO_SetOutputPin(CAMERA_RESET_GPIO_Port, CAMERA_RESET_PIN);
   LL_GPIO_ResetOutputPin(CAMERA_PWDn_GPIO_Port, CAMERA_PWDn_PIN);
   TS_Delay_ms(100);

   I2C_Master_Transmit(OV7670_WRITE_ADDR, OV7725_R_COM7, false, &txdata, 1);
   TS_Delay_ms(10);
}

void Camera_Start(void)
{
   DMA_EnableStream();
   DCMI_Start();
}

void Camera_Stop(void)
{
   DCMI_Stop();
   DMA_DisableStream();
}
