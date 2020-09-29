#include "screens.h"
#include "Bitmap.h"
#include "External.h"
#include "myConstants.h"
#include "time.h"

void updateDisplayMain(bool forceUpdate)
{
char text[20];
static uint8_t altStatusLuefterSoll,altStatusHeizungSoll,altStatusLuefterIst;
static float   altFeuchteIst,altTemperaturIst,altThreshTemp;
uint32_t       altSecondsCounter;

  if(forceUpdate)
  {
    altStatusLuefterSoll=255;
    altStatusHeizungSoll=255;
    altStatusLuefterIst=255;
    altFeuchteIst=-1;
    altTemperaturIst=-1;
    altThreshTemp=-1;
    altSecondsCounter=0;
  }

  if(u8StatusLuefterSoll!=altStatusLuefterSoll)
  {
    lcd_moveto_xy(0,0);
    lcd_draw_image_P(data_LuefterAus_bmp, 4, 32, u8StatusLuefterSoll==FAN_OFF ? 4:0);
    lcd_moveto_xy(0,32);
    lcd_draw_image_P(data_LuefterAuto_bmp, 4, 32, u8StatusLuefterSoll==FAN_AUTO ? 4:0);
    lcd_moveto_xy(0,64);
    switch(u8StatusLuefterSoll)
    {
      case FAN_S1:
        lcd_draw_image_P(data_Luefter1_bmp, 4, 32, 4);
      break;
      case FAN_S2:
        lcd_draw_image_P(data_Luefter2_bmp, 4, 32, 4);
      break;
      default:
        lcd_draw_image_P(data_Luefter1_bmp, 4, 32, 0);
    }
    altStatusLuefterSoll = u8StatusLuefterSoll;
  }
  if(u8StatusHeizungSoll!=altStatusHeizungSoll)
  {
    lcd_moveto_xy(0,95);
    switch(u8StatusHeizungSoll)
    {
      case HEAT_OFF:
        lcd_draw_image_P(data_HeizungAus_bmp, 4, 32, 0);
      break;
      case HEAT_ON:
        lcd_draw_image_P(data_HeizungAn_bmp, 4, 32, 0);
      break;
      default:
        lcd_draw_image_P(data_HeizungAn_bmp, 4, 32, 4);
    }
    altStatusHeizungSoll = u8StatusHeizungSoll;
  }

  if( (u8StatusLuefterIst!=altStatusLuefterIst) || (fFeuchteIst!=altFeuchteIst) )
  {
    lcd_moveto_xy(5,1);
    sprintf(text,"L%d: %.1f %% rH",u8StatusLuefterIst,fFeuchteIst);
    lcd_put_string(FONT_PROP_8, 0,text);
    u8StatusLuefterIst=altStatusLuefterIst;
    fFeuchteIst=altFeuchteIst;
  }

  if( (fTemperaturIst!=altTemperaturIst) || (fThreshTemp!=altThreshTemp) )
  {
    lcd_moveto_xy(7,1);
    sprintf(text,"%.1f | %.1f°C",fTemperaturIst,fThreshTemp);
    lcd_put_string(FONT_PROP_8, 0, text);
    fTemperaturIst=altTemperaturIst;
    fThreshTemp=altThreshTemp;
  }

  if( u32SecondsCounter-altSecondsCounter>2)
  {
    time_t lokalTime;
    cli();
    lokalTime = (time_t)u32SecondsCounter;
    altSecondsCounter = u32SecondsCounter;
    sei();
    struct tm info;
    localtime_r( &lokalTime,&info );
    strftime(text,20,"%H:%M:%S", &info);
    lcd_moveto_xy(5,72);
    lcd_put_string(FONT_PROP_16, 0, text);
  }
}

void initDisplayClock()
{
  lcd_moveto_xy(2,4);
  lcd_put_string(FONT_DIGITS_32, 0, "13:45");
}

void initDisplaySetup()
{
  lcd_moveto_xy(0,0);
	lcd_draw_image_P(data_SetL1_bmp, 4, 32, 0);
  lcd_moveto_xy(0,32);
	lcd_draw_image_P(data_SetL2_bmp, 4, 32, 0);
  lcd_moveto_xy(0,64);
	lcd_draw_image_P(data_SetT1_bmp, 4, 32, 0);
  lcd_moveto_xy(4,0);
	lcd_draw_image_P(data_SetL1H_bmp, 4, 32, 0);
  lcd_moveto_xy(4,32);
	lcd_draw_image_P(data_SetL2H_bmp, 4, 32, 0);
  lcd_moveto_xy(4,64);
	lcd_draw_image_P(data_SetT1H_bmp, 4, 32, 0);
  lcd_moveto_xy(2,95);
	lcd_draw_image_P(data_Minus_bmp, 4, 32, 0);
}

void initDisplaySetValue()
{
  lcd_bar_graph_xy(2,94,0,0,32,50);
  lcd_moveto_xy(4,0);
	lcd_draw_image_P(data_Minus_bmp, 4, 32, 0);
  lcd_moveto_xy(4,32);
	lcd_draw_image_P(data_Plus_bmp, 4, 32, 0);
  lcd_moveto_xy(4,64);
	lcd_draw_image_P(data_Set_bmp, 4, 32, 0);
  lcd_moveto_xy(4,95);
	lcd_draw_image_P(data_Minus_bmp, 4, 32, 0);

  lcd_moveto_xy(0,0);
  lcd_put_string(FONT_PROP_16, 0, "L1:");
  lcd_moveto_xy(2,32);
  lcd_put_string(FONT_PROP_16, 0, "46.6 ");
  lcd_put_string(FONT_SYMBOL_16, 0, "0");
  lcd_put_string(FONT_PROP_16, 0, " 48.6");

}
