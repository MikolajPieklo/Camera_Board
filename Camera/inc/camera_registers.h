/**
* @file Camera_Registers.h
* @brief Header of Camera_Registers file of the camera.
*
* @author Mikolaj Pieklo
* @date 24.04.2022
*/

#ifndef INC_CAMERA_REGISTERS_H_
#define INC_CAMERA_REGISTERS_H_

#define OV7725_R_COM2      0x09   /* Common Control 2 */
#define OV7725_R_PID       0x0A   /* Product ID Number MSB (Read only = 0x77) */
#define OV7725_R_VER       0x0B   /* Product ID Number LSB (Read only = 0x21) */
#define OV7725_R_COM3      0x0C   /* Common Control 3 */
#define OV7725_R_COM4      0x0D   /* Common Control 4 */
#define OV7725_R_COM5      0x0E   /* Common Control 5 */
#define OV7725_R_COM6      0x0F   /* Common Control 6 */

#define OV7725_R_CLKRC     0x11   /* Internal Clock */
#define OV7725_R_COM7      0x12   /* Common Control 7 */
#define OV7725_R_COM8      0x13   /* Common Control 8 */
#define OV7725_R_COM9      0x14   /* Common Control 9 */
#define OV7725_R_COM10     0x15   /* Common Control 10 */
#define OV7725_R_REG16     0x16   /* Register 16 */
#define OV7725_R_HSTART    0x17   /* Horizontal Frame (HREF column) */

#define OV7725_R_MIDH      0x1C   /* Manufacturer ID Byte – High (Read only = 0x7F) */
#define OV7725_R_MIDL      0x1D   /* Manufacturer ID Byte – Low (Read only = 0xA2) */
#define OV7725_R_COM11     0x20   /* Common Control 11 */
#define OV7725_R_BDBase    0x22   /* Banding Filter Minimum AEC Value */
#define OV7725_R_BDMStep   0x23   /* Banding Filter Maximum Step */
#define OV7725_R_AEW       0x24   /* AGC/AEC - Stable Operating Region (Upper Limit) */
#define OV7725_R_AEB       0x25   /* AGC/AEC - Stable Operating Region (Lower Limit) */
#define OV7725_R_VPT       0x26   /* AGC/AEC Fast Mode Operating Region */
#define OV7725_R_HOutSize  0x29   /* Horizontal Data Output Size MSBs (2 LSBs at register EXHCH[1:0]) */
#define OV7725_R_EXHCH     0x2A   /* Dummy Pixel Insert MSB */
#define OV7725_R_EXHCL     0x2B   /* Dummy Pixel Insert LSB */
#define OV7725_R_VOutSize  0x2C   /* Vertical Data Output Size MSBs (LSB at register EXHCH[2]) */
#define OV7725_R_ADVFL     0x2D   /* LSB of Insert Dummy Rows in Vertical Sync (1 bit equals 1 row) */
#define OV7725_R_ADVFH     0x2E   /* MSB of Insert Dummy Rows in Vertical Sync */
#define OV7725_R_HREF      0x32   /* Image Start and Size Control */
#define OV7725_R_DM_LNL    0x33   /* Dummy Row Low 8 Bits */
#define OV7725_R_DM_LNH    0x34   /* Dummy Row High 8 Bits */

#define OV7725_R_COM12     0x3D   /* Common Control 12 */
#define OV7725_R_COM13     0x3E   /* Common Control 13 */
#define OV7725_R_COM14     0x3F   /* Common Control 14 */
#define OV7725_R_COM15     0x40   /* Common Control 15 */
#define OV7725_R_COM16     0x41   /* Common Control 16 */
#define OV7725_R_TGT_B     0x42   /* BLC Blue Channel Target Value */
#define OV7725_R_TGT_R     0x43   /* BLC Red Channel Target Value */
#define OV7725_R_TGT_Gb    0x44   /* BLC Gb Channel Target Value */
#define OV7725_R_TGT_Gr    0x45   /* BLC Gr Channel Target Value */
#define OV7725_R_LC_CTR    0x46   /* Lens Correction Control */
#define OV7725_R_LC_XC     0x47   /* X Coordinate of Lens Correction Center Relative to Array Center */
#define OV7725_R_LC_COEF   0x49   /* Lens Correction Coefficient */
#define OV7725_R_LC_RADI   0x4A   /* Lens Correction Radius – radius of the circular section where no compensation applies */
#define OV7725_R_LC_COEFB  0x4B   /* Lens Correction B Channel Compensation Coefficient (effective only when LC_CTR[2] is high) */
#define OV7725_R_LC_COEFR  0x4C   /* Lens Correction R Channel Compensation Coefficient (effective only when LC_CTR[2] is high) */
#define OV7725_R_FixGain   0x4D   /* Analog Fix Gain Amplifier */
#define OV7725_R_AWB_Ctrl0 0x63   /* AWB Control Byte 0 */

#define OV7725_R_DSP_Ctrl1 0x64   /* DSP Control Byte 1 */
#define OV7725_R_DSP_Ctrl2 0x65   /* DSP Control Byte 2 */
#define OV7725_R_DSP_Ctrl3 0x66   /* DSP Control Byte 3 */
#define OV7725_R_DSP_Ctrl4 0x67   /* DSP Control Byte 4 */

#define OV7725_R_AWBCtrl1  0x69   /* AWB Control 1 */
#define OV7725_R_AWBCtrl2  0x6A   /* AWB Control 2 */
#define OV7725_R_AWBCtrl3  0x6B   /* AWB Control 3 */
#define OV7725_R_GAM1      0x7E   /* Gamma Curve 1st Segment Input End Point 0x04 Output Value */
#define OV7725_R_GAM2      0x7F   /* Gamma Curve 2nd Segment Input End Point 0x08 Output Value */
#define OV7725_R_GAM3      0x80   /* Gamma Curve 3rd Segment Input End Point 0x10 Output Value */
#define OV7725_R_GAM4      0x81   /* Gamma Curve 4th Segment Input End Point 0x20 Output Value */
#define OV7725_R_GAM5      0x82   /* Gamma Curve 5th Segment Input End Point 0x28 Output Value */
#define OV7725_R_GAM6      0x83   /* Gamma Curve 6th Segment Input End Point 0x30 Output Value */
#define OV7725_R_GAM7      0x84   /* Gamma Curve 7th Segment Input End Point 0x38 Output Value */
#define OV7725_R_GAM8      0x85   /* Gamma Curve 8th Segment Input End Point 0x40 Output Value */
#define OV7725_R_GAM9      0x86   /* Gamma Curve 9th Segment Input End Point 0x48 Output Value */
#define OV7725_R_GAM10     0x87   /* Gamma Curve 10th Segment Input End Point 0x50 Output Value */
#define OV7725_R_GAM11     0x88   /* Gamma Curve 11th Segment Input End Point 0x60 Output Value */
#define OV7725_R_GAM12     0x89   /* Gamma Curve 12th Segment Input End Point 0x70 Output Value */
#define OV7725_R_GAM13     0x8A   /* Gamma Curve 13th Segment Input End Point 0x90 Output Value */
#define OV7725_R_GAM14     0x8B   /* Gamma Curve 14th Segment Input End Point 0xB0 Output Value */
#define OV7725_R_GAM15     0x8C   /* Gamma Curve 15th Segment Input End Point 0xD0 Output Value */
#define OV7725_R_SLOP      0x8D   /* Gamma Curve Highest Segment Slope - calculated as follows */
#define OV7725_R_DNSTh     0x8E   /* De-noise Threshold */
#define OV7725_R_EDGE0     0x8F   /* Sharpness (Edge Enhancement) Control 0 */
#define OV7725_R_EDGE1     0x90   /* Sharpness (Edge Enhancement) Control 1 */
#define OV7725_R_DNSOff    0x91   /* Auto De-noise Threshold Control */
#define OV7725_R_EDGE2     0x92   /* Sharpness (Edge Enhancement) Strength Upper Limit */
#define OV7725_R_EDGE3     0x93   /* Sharpness (Edge Enhancement) Strength Lower Limit */
#define OV7725_R_MTX1      0x94   /* Matrix Coefficient 1 */
#define OV7725_R_MTX2      0x95   /* Matrix Coefficient 2 */
#define OV7725_R_MTX3      0x96   /* Matrix Coefficient 3 */
#define OV7725_R_MTX4      0x97   /* Matrix Coefficient 4 */
#define OV7725_R_MTX5      0x98   /* Matrix Coefficient 5 */
#define OV7725_R_MTX6      0x99   /* Matrix Coefficient 6 */
#define OV7725_R_MTX_Ctrl  0x9A   /* Matrix Control */
#define OV7725_R_BRIGHT    0x9B   /* Brightness Control */
#define OV7725_R_CNST      0x9C   /* Contrast Gain */
#define OV7725_R_UVADJ0    0x9E   /* Auto UV Adjust Control 0 */
#define OV7725_R_SCAL0     0xA0   /* DCW Ratio Control */
#define OV7725_R_SCAL1     0xA1   /* Horizontal Zoom Out Control */
#define OV7725_R_SCAL2     0xA2   /* Vertical Zoom Out Control */
#define OV7725_R_SDE       0xA6   /* Special Digital Effect Control */
#define OV7725_R_USAT      0xA7   /* U Component Saturation Gain */
#define OV7725_R_VSAT      0xA8   /* V Component Saturation Gain */
#define OV7725_R_HUECOS    0xA9   /* Cosine value × 0x80 */
#define OV7725_R_HUESIN    0xAA   /* Sine value × 0x80 */
#define OV7725_R_DSPAuto   0xAC   /* DSP Auto Function ON/OFF Control */

//Reg_Info sensor_config[] =
//{
//   {OV7725_R_HREF,    0x00},
//   {OV7725_R_EXHCH,   0x00},
//   {OV7725_R_CLKRC,   0x03}, //Set internal clock
//   {OV7725_R_COM7,    0x46}, //QVGA RGB565
//
//   {OV7725_R_TGT_B,     0x7f},
//   {OV7725_R_FixGain,   0x00},
//   {OV7725_R_AWB_Ctrl0, 0xf0},
//   {OV7725_R_DSP_Ctrl1, 0x1f},
//   {OV7725_R_DSP_Ctrl2, 0x20},
//   {OV7725_R_DSP_Ctrl3, 0x00},
//
//   {OV7725_R_DSP_Ctrl4, 0x00},
//
//   {OV7725_R_AWBCtrl1,  0x50},
//   {OV7725_R_COM8    ,  0xff},//<-
//   {OV7725_R_COM4    ,  0x41},//<-
//   {OV7725_R_COM6    ,  0x01},
//   {OV7725_R_COM9    ,  0x06},
//
//   {OV7725_R_AEW     ,  0x75},
//   {OV7725_R_AEB     ,  0x63},
//   {OV7725_R_VPT     ,  0xd1},
//   {OV7725_R_EXHCL   ,  0xff},
//   {OV7725_R_AWBCtrl3,  0xaa},
//
//   {OV7725_R_DNSTh   ,  0x10},
//   {OV7725_R_EDGE0   ,  0x00},
//   {OV7725_R_EDGE1   ,  0x00},
//   {OV7725_R_DNSOff  ,  0x00},
//   {OV7725_R_EDGE2   ,  0x00},
//   {OV7725_R_EDGE3   ,  0x00},
//
//   {OV7725_R_MTX1    ,  0x2c},
//   {OV7725_R_MTX2    ,  0x24},
//   {OV7725_R_MTX3    ,  0x08},
//   {OV7725_R_MTX4    ,  0x14},
//   {OV7725_R_MTX5    ,  0x24},
//   {OV7725_R_MTX6    ,  0x38},
//   {OV7725_R_MTX_Ctrl,  0x9e},
//   {OV7725_R_COM10   ,  0x00},
//   {OV7725_R_BRIGHT  ,  0x00},
//   {OV7725_R_CNST    ,  0x20},
//   {OV7725_R_USAT    ,  0x40},
//   {OV7725_R_VSAT    ,  0x40},
//   {OV7725_R_HUECOS  ,  0x80},
//   {OV7725_R_HUESIN  ,  0x80},
//
//   {OV7725_R_UVADJ0  ,  0x81},
//   {OV7725_R_SDE     ,  0x06},
//
//   {OV7725_R_GAM1    ,  0x0c},
//   {OV7725_R_GAM2    ,  0x16},
//   {OV7725_R_GAM3    ,  0x2a},
//   {OV7725_R_GAM4    ,  0x4e},
//   {OV7725_R_GAM5    ,  0x61},
//   {OV7725_R_GAM6    ,  0x6f},
//   {OV7725_R_GAM7    ,  0x7b},
//   {OV7725_R_GAM8    ,  0x86},
//   {OV7725_R_GAM9    ,  0x8e},
//   {OV7725_R_GAM10   ,  0x97},
//   {OV7725_R_GAM11   ,  0xa4},
//   {OV7725_R_GAM12   ,  0xaf},
//   {OV7725_R_GAM13   ,  0xc5},
//   {OV7725_R_GAM14   ,  0xd7},
//   {OV7725_R_GAM15   ,  0xe8},
//   {OV7725_R_SLOP    ,  0x20},
//
//   {OV7725_R_DM_LNL,0x40},
//   {OV7725_R_DM_LNH,0x00},
//   {OV7725_R_BDBase ,0xaf},
//   {OV7725_R_BDMStep,0x01},
//
//   {OV7725_R_LC_COEF,0x10},
//   {OV7725_R_LC_RADI,0x10},
//   {OV7725_R_LC_COEFB,0x14},
//   {OV7725_R_LC_COEFR,0x17},
//   {OV7725_R_LC_CTR,0x05},
//
//   {OV7725_R_LC_XC,0x08},
//   {OV7725_R_COM5,0x01},
//   {OV7725_R_COM3,0x60},
//   {OV7725_R_COM2,0x03},
//
//   {OV7725_R_HOutSize,0x50},
//   {OV7725_R_VOutSize,0x78},
//};

#endif /* INC_CAMERA_REGISTERS_H_ */
