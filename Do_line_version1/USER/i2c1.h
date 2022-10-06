
/*
  ******************************************************************************
  * @file		abc.h                                                              *
  * @author	Nguyen Nhat Minh                                                *
  * @date		00/00/0000                                                         *
  ******************************************************************************
*/
	
#ifndef __ABC__
#define __ABC__

#ifdef __cplusplus
 extern "C" {
#endif

void i2c_init(void);
void i2c_send_byte(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_CLS(void);
void OLED_Fill(unsigned char fill_Data);
void OLED_OFF(void);
void OLED_ON(void);
void ssd1306_i2c_init(void);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
