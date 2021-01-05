#include <avr/pgmspace.h>

#include "Bitmap.h"
#include "timer.h"
#include "BadDisplay.h"


#define SYSCLK CLK32M
#define PLL 1


void setup()
{
  LEDROT_OFF;
  LEDGRUEN_OFF;
  LEDRGB_BLAU_OFF;
  LEDRGB_GRUEN_OFF;
  LEDRGB_ROT_OFF;
  BEEPER_OFF;
  DIMMER_OFF;

  PORTA.DIRSET = 0xff;
   //PIN4_bm | PIN7_bm;
  PORTB.DIRSET = 0xff;
  PORTC.DIRSET = 0b10111010;
  PORTD.DIRSET = 0b10111011;
  PORTE.DIRSET = 0b11111110;

  LEDROTSETUP; LEDGRUENSETUP; LEDRGB_BLAUSETUP; LEDRGB_ROTSETUP; LEDRGB_GRUENSETUP; BEEPERSETUP; DIMMERSETUP;
  init_clock(SYSCLK, PLL,true,CLOCK_CALIBRATION);

	PMIC_CTRL = PMIC_LOLVLEX_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm;
  //SPI_MasterInit(&spiDisplay,&SPI_DEV,&SPI_PORT,false,SPI_MODE_1_gc,SPI_INTLVL_LO_gc,false,SPI_PRESCALER_DIV128_gc);
  lcd_init();
  sei();
  init_mytimer();

  cmulti.open(Serial::BAUD_57600,F_CPU);
  cmulti.sendInfo("Badezimmer sagt hallo","BR");
  lcd_set_font(FONT_PROP_8  , NORMAL);
  updateDisplayMain(true);

}

int main()
{
uint8_t taste = 0;

  setup();

  AR1021 touch(&(MyTimers[TIMER_TOUCH]),SPI_INTLVL_LO_gc,false,SPI_PRESCALER_DIV128_gc);
  pTouch = &touch;
  pTouch->setDebug(&cmulti);

  pTouch->init(4,2,true);
  pTouch->registerDump();

  LEDRGB_ROT_ON;

  MyTimers[TIMER_DISPLAY_OFF].state = TM_START;

  AR1021::touchCoordinate_t coord;

  for(uint8_t i=0;i<8;i++)
  {
    BEEPER_TOGGLE;
    _delay_ms(50);
  }
  BEEPER_OFF;

  while(1)
  {
		cmultiRec.comStateMachine();
		cmultiRec.doJob();
    //updateDisplayMain(false);
    pTouch->readTouchIrq();
    taste = displayTouched();
    if(taste>0)
    {
      MyTimers[TIMER_DISPLAY_OFF].state = TM_RESET;
      BEEPER_ON;
      MyTimers[TIMER_BEEP].state = TM_START;
      switch(displayStatus)
      {
        case DISPLAY_SLEEP:
          MyTimers[TIMER_DISPLAY_OFF].state = TM_START;
          displayStatus = DISPLAY_MAIN;
          updateDisplayMain(true);
        break;
        case DISPLAY_MAIN:
          switch(taste)
          {
            case 5:
              displayStatus = DISPLAY_CHOICE;
              initDisplaySetup();
            break;
            case 4:
              cmulti.sendStandard("aus","LB",'L','1','S','T');
            break;
            case 3:
              cmulti.sendStandard("Auto","LB",'L','1','S','T');
            break;
            case 2:

              if(u8StatusLuefterSoll==FAN_STATUS_1)
              cmulti.sendStandard("Stufe 2","LB",'L','1','S','T');
              else
              cmulti.sendStandard("Stufe 1","LB",'L','1','S','T');
            break;
          }

        break;
        case DISPLAY_CHOICE:
          switch(taste)
          {
            case 1:
            case 5:
              displayStatus = DISPLAY_MAIN;
              updateDisplayMain(true);
            break;
            case 3:
              displayStatus = DISPLAY_SETVALUE;
              initDisplaySetValue("L2:",10.0,95.0,1.0,&fThreshLuefter2,'G');
            break;
            case 4:
              displayStatus = DISPLAY_SETVALUE;
              initDisplaySetValue("L1:",10.0,95.0,1.0,&fThreshLuefter1,'L');
            break;
            case 7:
              displayStatus = DISPLAY_SETVALUE;
              initDisplaySetValue("H2:",1.0,15.0,0.5,&fHystLuefter2,'I');
            break;
            case 8:
              displayStatus = DISPLAY_SETVALUE;
              initDisplaySetValue("H1:",1.0,15.0,0.5,&fHystLuefter1,'H');
            break;
          }
        break;
        case DISPLAY_SETVALUE:
          switch(taste)
          {
            case 5:
              displayStatus = DISPLAY_MAIN;
              updateDisplayMain(true);
            break;
            case 6:
              displayStatus = DISPLAY_MAIN;
              setSetValue();
              updateDisplayMain(true);
            break;
            case 7:
              addSetValue();
            break;
            case 8:
              subSetValue();
            break;
          }
        break;
      }

    }
    switch(displayStatus)
    {
      case DISPLAY_SLEEP:
        initDisplayClock(false);
        LEDRGB_ROT_OFF;
        if(taste>0)
        {
          MyTimers[TIMER_DISPLAY_OFF].state = TM_START;
          displayStatus = DISPLAY_MAIN;
          updateDisplayMain(true);
        }
      break;
      case DISPLAY_MAIN:
        LEDRGB_ROT_ON;
        updateDisplayMain(false);
      break;
      case DISPLAY_CHOICE:
      break;
    }
/*    if(pTouch->read(coord))
    {
      sprintf(text," --> x: %d  y: %d  t:%d <-- ",coord.x,coord.y,coord.touched );
      cmulti.sendInfo(text,"BR");
    }*/

  }
}


/*! \brief SPI master interrupt service routine.
 *
 *  The interrupt service routines calls one common function,
 *  SPI_MasterInterruptHandler(SPI_Master_t *spi),
 *  passing information about what module to handle.
 *
 *  Similar ISRs must be added if other SPI modules are to be used.
 */
ISR(SPID_INT_vect)
{
	SPI_MasterInterruptHandler(&spiDisplay);
}

ISR(SPIC_INT_vect)
{
	SPI_MasterInterruptHandler(&spiDisplay);
}



