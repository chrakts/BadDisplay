#ifndef DOGDISPLAYHARDWARE_H_INCLUDED
#define DOGDISPLAYHARDWARE_H_INCLUDED

/*****************************************************************************
 * BEGIN CONFIG BLOCK
 *****************************************************************************/
//Select the display type: DOGS102: 102, DOGM128/DOGL128: 128, DOGM132: 132, DOGXL160: 160
#define DISPLAY_TYPE  128


#define ORIENTATION_UPSIDEDOWN 1
//Should chip select (CS) be used?
#define LCD_USE_CHIPSELECT  1
//Use Backlight?  (0: no backlight, 1: backlight (on when pin is high), 2: backlight (on when pin is low))
#define LCD_USE_BACKLIGHT   1

//A0 Port (CD on DOGS & DOGXL)
//#define LCD_A0_PORT PORTC
//#define LCD_A0_PIN  PIN3_bm
#define LCD_A0_PORT PORTE
#define LCD_A0_PIN  PIN0_bm


/*
#define PORT_A0  PORTC
#define DDR_A0   DDRC
#define PIN_A0   3*/

//Reset Port
//#define LCD_RST_PORT PORTA
//#define LCD_RST_PIN  PIN5_bm
#define LCD_RST_PORT PORTE
#define LCD_RST_PIN  PIN1_bm

//Backlight Port
#if LCD_USE_BACKLIGHT != 0
  #define LCD_BACKL_PORT PORTE
  #define LCD_BACKL_PIN  PIN2_bm

/*  #define PORT_LED PORTE
  #define DDR_LED  DDRE
  #define PIN_LED  2*/
#endif

//Chip select
#if LCD_USE_CHIPSELECT == 1
  #define LCD_CS_PORT PORTC
  #define LCD_CS_PIN  PIN4_bm
#endif

//Define this if LCD Output should continue in next line when reaching edge of display
//Used for all outputs. To enable this feature for text only, use the appropriate flag in font.h
#define LCD_WRAP_AROUND  1

//Include graphic functions, i.e. lcd_draw_image_P, lcd_draw_image_xy_P, lcd_clear_area ?
#define LCD_INCLUDE_GRAPHIC_FUNCTIONS  1


/*****************************************************************************
 * END CONFIG BLOCK
 *****************************************************************************/


#endif // DOGDISPLAYHARDWARE_H_INCLUDED
