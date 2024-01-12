#include <avr/pgmspace.h>

#include "Bitmaps.h"
#include "timer.h"
#include "BadDisplay.h"


#define SYSCLK CLK32M
#define PLL 1


void setup()
{
  PORTE.DIRSET = 0b11111110;
  PORTE.PIN2CTRL = PORT_OPC_WIREDAND_gc;
  TCE0.CCCL = 0;
  TCE0.CTRLA = TC_CLKSEL_DIV8_gc;
  TCE0.CTRLB = TC0_CCCEN_bm | TC_WGMODE_SINGLESLOPE_gc;
  TCE0.CTRLE = TC_BYTEM_BYTEMODE_gc; // Splitmode
  TCE0.PERL = 128;

  LEDROT_OFF;
  LEDGRUEN_OFF;
  LEDRGB_BLAU_OFF;
  LEDRGB_GRUEN_OFF;
  LEDRGB_ROT_OFF;
  BEEPER_OFF;

  PORTA.DIRSET = 0xff;
   //PIN4_bm | PIN7_bm;
  PORTB.DIRSET = 0xff;
  PORTC.DIRSET = 0b10111010;
  PORTD.DIRSET = 0b10111011;



  LEDROTSETUP; LEDGRUENSETUP; LEDRGB_BLAUSETUP; LEDRGB_ROTSETUP; LEDRGB_GRUENSETUP; BEEPERSETUP; DIMMERSETUP;
  init_clock(SYSCLK, PLL,true,CLOCK_CALIBRATION);

	PMIC_CTRL = PMIC_LOLVLEX_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm;
  //SPI_MasterInit(&spiDisplay,&SPI_DEV,&SPI_PORT,false,SPI_MODE_1_gc,SPI_INTLVL_LO_gc,false,SPI_PRESCALER_DIV128_gc);
  lcd_init();
  sei();
  init_mytimer();
  cmulti.open(Serial::BAUD_57600,F_CPU);
  //cmulti.sendInfo("Badezimmer sagt hallo","BR");
  lcd_set_font(FONT_PROP_8  , NORMAL);
  updateDisplayMain(true);

}

int main()
{
uint8_t taste = 0;

  setup();
  for(uint8_t i=0;i<4;i++)
  {
    BEEPER_TOGGLE;
    _delay_ms(50);
  }
  BEEPER_OFF;

  AR1021 touch(&(MyTimers[TIMER_TOUCH]),SPI_INTLVL_LO_gc,false,SPI_PRESCALER_DIV128_gc);
  pTouch = &touch;
  pTouch->setDebug(&cmulti);

  pTouch->init(4,2,true);
  //pTouch->registerDump();


  MyTimers[TIMER_DISPLAY_OFF].state = TM_START;

  //AR1021::touchCoordinate_t coord;

  DIMMER_OFF;
  while(1)
  {
		cmultiRec.comStateMachine();
		cmultiRec.doJob();

    if(u8StatusLuefterSoll == FAN_STATUS_AUTO)
      LEDRGB_BLAU_ON;
    else
      LEDRGB_BLAU_OFF;
    if(u8StatusHeizungIst == HEAT_ON)
    {
      LEDRGB_ROT_ON;
      LEDRGB_GRUEN_OFF;
    }
    else
    {
      LEDRGB_ROT_OFF;
      LEDRGB_GRUEN_ON;
    }

    pTouch->readTouchIrq();
    taste = displayTouched();

    if(taste>0)
    {
      DIMMER_ON;
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
            case 1:
              switch(u8StatusHeizungSoll)
              {
                case HEAT_OFF:
                  cmulti.sendStandard("ein","V1",'V','0','S','T');
                break;
                case HEAT_ON:
                  cmulti.sendStandard("Auto","V1",'V','0','S','T');
                break;
                case HEAT_AUTO:
                  cmulti.sendStandard("aus","V1",'V','0','S','T');
                break;
              }
            break;
          }

        break;
        case DISPLAY_CHOICE:
          strcpy(glbTarget,"LB");
          glbFunction = 'L';
          glbAddress  = '1';
          switch(taste)
          {
            case 1: // radiator Night
              displayStatus = DISPLAY_SETVALUE;
              strcpy(glbTarget,"V1");
              glbJob = 'N';
              glbFunction = 'V';
              glbAddress  = '0';
              initDisplaySetValue("Na.:",10.0,40,0.2,&fThreshTempNight);
            break;
            case 2: // radiator Day
              displayStatus = DISPLAY_SETVALUE;
              strcpy(glbTarget,"V1");
              glbJob = 'D';
              glbFunction = 'V';
              glbAddress  = '0';
              initDisplaySetValue("Tag:",10.0,40,0.2,&fThreshTempDay);
            break;
            case 6: // radiator Hysterese
              displayStatus = DISPLAY_SETVALUE;
              strcpy(glbTarget,"V1");
              glbJob = 'H';
              glbFunction = 'V';
              glbAddress  = '0';
              initDisplaySetValue("Hy.:",0.1,10,0.1,&fThreshHyst);
            break;
            case 5: // abgebrochen
              displayStatus = DISPLAY_MAIN;
              updateDisplayMain(true);
            break;
            case 3:
              displayStatus = DISPLAY_SETVALUE;
              glbJob = 'G';
              initDisplaySetValue("L2:",10.0,95.0,0.5,&fThreshLuefter2);
            break;
            case 4:
              displayStatus = DISPLAY_SETVALUE;
              glbJob = 'L';
              initDisplaySetValue("L1:",10.0,95.0,0.5,&fThreshLuefter1);
            break;
            case 7:
              displayStatus = DISPLAY_SETVALUE;
              glbJob = 'I';
              initDisplaySetValue("H2:",1.0,15.0,0.5,&fHystLuefter2);
            break;
            case 8:
              displayStatus = DISPLAY_SETVALUE;
              glbJob = 'H';
              initDisplaySetValue("H1:",1.0,15.0,0.5,&fHystLuefter1);
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
        if(taste>0)
        {
          MyTimers[TIMER_DISPLAY_OFF].state = TM_START;
          displayStatus = DISPLAY_MAIN;
          updateDisplayMain(true);
        }
      break;
      case DISPLAY_MAIN:
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



