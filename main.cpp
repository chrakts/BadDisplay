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
  init_clock(SYSCLK,PLL,false,0);
  SPI_MasterInit(&spiDisplay,&SPI_DEV,&SPI_PORT,false,SPI_MODE_0_gc,SPI_INTLVL_LO_gc,false,SPI_PRESCALER_DIV128_gc);

	PMIC_CTRL = PMIC_LOLVLEX_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm;
  sei();
  init_mytimer();

  cmulti.open(Serial::BAUD_57600,F_CPU);
  cmulti.sendInfo("Badezimmer sagt hallo","BR");
  lcd_init(&spiDisplay);
  lcd_set_font(FONT_PROP_8  , NORMAL);
  updateDisplayMain(true);
  touch.setDebug(&cmulti);
  touch.init(800,600);
}

int main()
{
char text[20];
  setup();
  MyTimers[TIMER_LEDBLINK1].state = TM_START;
  for(uint8_t i=0;i<18;i++)
  {
    sprintf(text,"AR1021:%x",touch.readRegister8(i));
    cmulti.sendInfo(text,"BR");
  }

  while(1)
  {
    updateDisplayMain(false);
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



