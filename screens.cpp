#include "screens.h"
#include "Bitmaps.h"

#include "myConstants.h"
#include "time.h"

//double *toChangeValue;
double glbStep,glbMax,glbMin;
double tempValue;

void updateDisplayMain(bool forceUpdate)
{
char text[20];
static uint8_t altStatusLuefterSoll,altStatusHeizungSoll,altStatusLuefterIst;
static float   altFeuchteIst,altTemperaturIst,altThreshTempDay;
static uint32_t altSecondsCounter;

  if(forceUpdate)
  {
    lcd_clear_area_xy(LCD_RAM_PAGES,LCD_WIDTH,NORMAL,0,0);
    altStatusLuefterSoll=255;
    altStatusHeizungSoll=255;
    altStatusLuefterIst=255;
    altFeuchteIst=-1;
    altTemperaturIst=-1;
    altThreshTempDay=-1;
    altSecondsCounter=0;
  }

  if(u8StatusLuefterSoll!=altStatusLuefterSoll)
  {
    lcd_moveto_xy(0,0);
    lcd_draw_compact_image_P(data_fanOff_cbmp, 4, 32, u8StatusLuefterSoll==FAN_STATUS_OFF ? 4:0);
    lcd_moveto_xy(0,32);
    lcd_draw_compact_image_P(data_fanAuto_cbmp, 4, 32, u8StatusLuefterSoll==FAN_STATUS_AUTO ? 4:0);
    lcd_moveto_xy(0,64);
    switch(u8StatusLuefterSoll)
    {
      case FAN_STATUS_1:
        lcd_draw_compact_image_P(data_fanSpeed_1_cbmp, 4, 32, 4);
      break;
      case FAN_STATUS_2:
        lcd_draw_compact_image_P(data_fanSpeed_2_cbmp, 4, 32, 4);
      break;
      default:
        lcd_draw_compact_image_P(data_fanSpeed_1_cbmp, 4, 32, 0);
    }
    altStatusLuefterSoll = u8StatusLuefterSoll;
  }
  if(u8StatusHeizungSoll!=altStatusHeizungSoll)
  {
    lcd_moveto_xy(0,95);
    switch(u8StatusHeizungSoll)
    {
      case HEAT_OFF:
        lcd_draw_compact_image_P(data_radiatorOff_cbmp, 4, 32, 0);
      break;
      case HEAT_ON:
        lcd_draw_compact_image_P(data_radiator_cbmp, 4, 32, 0);
      break;
      case HEAT_AUTO:
        lcd_draw_compact_image_P(data_radiatorAuto_cbmp, 4, 32, 0);
      break;
      default:
        lcd_draw_compact_image_P(data_HeizungAn_cbmp, 4, 32, 4);
    }
    altStatusHeizungSoll = u8StatusHeizungSoll;
  }

  if( (u8StatusLuefterIst!=altStatusLuefterIst) || (fFeuchteIst!=altFeuchteIst) )
  {
    lcd_moveto_xy(5,1);
    sprintf(text,"L%d: %.1f %% rH",u8StatusLuefterIst,fFeuchteIst);
    lcd_put_string(FONT_PROP_8, 0,text);
    altStatusLuefterIst = u8StatusLuefterIst;
    altFeuchteIst = fFeuchteIst;
  }

  if( (fTemperaturIst!=altTemperaturIst) || (fThreshTempDay!=altThreshTempDay) )
  {
    lcd_moveto_xy(7,1);
    sprintf(text,"H%d: %.1f %cC",u8StatusHeizungIst,fTemperaturIst,char(176));
    lcd_put_string(FONT_PROP_8, 0, text);
    altTemperaturIst = fTemperaturIst;
    altThreshTempDay = fThreshTempDay;
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
    lcd_put_string(FONT_PROP_16, INVERT*u8StatusNight, text);
  }
}

void initDisplayClock(bool forceUpdate)
{
char text[20];
static uint32_t altSecondsCounter;

  if( (u32SecondsCounter-altSecondsCounter>60) || forceUpdate )
  {
    lcd_clear_area_xy(LCD_RAM_PAGES,LCD_WIDTH,NORMAL,0,0);
    time_t lokalTime;
    cli();
    lokalTime = (time_t)u32SecondsCounter;
    altSecondsCounter = u32SecondsCounter;
    sei();
    struct tm info;
    localtime_r( &lokalTime,&info );
    strftime(text,20,"%H:%M", &info);
    lcd_moveto_xy(2,4);
    lcd_put_string(FONT_DIGITS_32, 0, text);
  }
}

void initDisplaySetup()
{
  lcd_clear_area_xy(LCD_RAM_PAGES,LCD_WIDTH,NORMAL,0,0);
  lcd_moveto_xy(0,0);
	lcd_draw_compact_image_P(data_SetL1_cbmp, 4, 32, 0);
  lcd_moveto_xy(0,32);
	lcd_draw_compact_image_P(data_SetL2_cbmp, 4, 32, 0);
  lcd_moveto_xy(0,64);
	lcd_draw_compact_image_P(data_radiatorDay_cbmp, 4, 32, 0);
  lcd_moveto_xy(0,95);
	lcd_draw_compact_image_P(data_radiatorNight_cbmp, 4, 32, 0);
  lcd_moveto_xy(4,0);
	lcd_draw_compact_image_P(data_SetL1H_cbmp, 4, 32, 0);
  lcd_moveto_xy(4,32);
	lcd_draw_compact_image_P(data_SetL2H_cbmp, 4, 32, 0);
  lcd_moveto_xy(4,64);
	lcd_draw_compact_image_P(data_radiatorHysterese_cbmp, 4, 32, 0);
  lcd_moveto_xy(4,95);
	lcd_draw_compact_image_P(data_closeOutline_cbmp, 4, 32, 0);
}

void initDisplaySetValue(const char *text,double min,double max, double step,volatile double *oldValue)
{
  char temp[10];
  glbStep = step;
  glbMin  = min;
  glbMax  = max;
  //toChangeValue = oldValue;
  tempValue = *oldValue;
  lcd_clear_area_xy(LCD_RAM_PAGES,LCD_WIDTH,NORMAL,0,0);
  lcd_moveto_xy(0,0);
  lcd_bar_graph_xy(2,82,0,0,32,(uint8_t)(100*(tempValue)/(max-min))); // 2. Parameter war 94
  lcd_moveto_xy(4,0);
	lcd_draw_compact_image_P(data_minusOutline_cbmp, 4, 32, 0);
  lcd_moveto_xy(4,32);
	lcd_draw_compact_image_P(data_plusOutline_cbmp, 4, 32, 0);
  lcd_moveto_xy(4,64);
	lcd_draw_compact_image_P(data_checkOutline_cbmp, 4, 32, 0);
  lcd_moveto_xy(4,95);
	lcd_draw_compact_image_P(data_closeOutline_cbmp, 4, 32, 0);

  lcd_moveto_xy(0,0);
  lcd_put_string(FONT_PROP_16, 0, text);
  lcd_moveto_xy(2,20);
  sprintf(temp,"%.1f",tempValue);
  lcd_put_string(FONT_PROP_16, 0, temp);
  lcd_moveto_xy(2,50);
  lcd_put_string(FONT_SYMBOL_16, 0, "0");
  lcd_moveto_xy(2,70);
  lcd_put_string(FONT_PROP_16, 0, temp);

}

void addSetValue()
{
  if(tempValue+glbStep<glbMax)
    tempValue+=glbStep;
  else
    tempValue = glbMax;
  updateDisplaySetValue();
}

void subSetValue()
{
  if(tempValue-glbStep>glbMin)
    tempValue-=glbStep;
  else
    tempValue = glbMin;
  updateDisplaySetValue();
}

void setSetValue()
{
// #13DLBMeSL1LT71<4232

  //*toChangeValue = tempValue;
  cmulti.sendStandardDouble(glbTarget,glbFunction,glbAddress,glbJob,tempValue);
}

void updateDisplaySetValue()
{
char temp[10];
  lcd_moveto_xy(0,0);
  lcd_bar_graph_xy(2,82,0,0,32,(uint8_t)(100*(tempValue)/(glbMax-glbMin)));
  lcd_moveto_xy(2,70);
  sprintf(temp,"%.1f",tempValue);
  lcd_put_string(FONT_PROP_16, 0, temp);

}

uint8_t displayTouched()
{
AR1021::touchCoordinate_t coord;
uint8_t taste=0;

  if(pTouch->read(coord))
  {
    if(coord.touched)
    {
      taste = coord.x + 4*coord.y + 1;
    }
  }
  return taste;

}
