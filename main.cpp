#include <avr/pgmspace.h>

#include "Bitmap.h"
#include "timer.h"
#include "BadDisplay.h"


#define SYSCLK CLK32M
#define PLL 1

void setup()
{
  PORTA.DIRSET = 0xff;
   //PIN4_bm | PIN7_bm;
  PORTB.DIRSET = PIN2_bm | PIN5_bm | PIN7_bm;
  PORTC.DIRSET = PIN1_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN7_bm;
  PORTD.DIRSET = PIN3_bm | PIN4_bm | PIN5_bm | PIN7_bm;
  PORTE.DIRSET = PIN1_bm | PIN4_bm | PIN5_bm | PIN7_bm;

  init_clock(SYSCLK,PLL,false,0);
  SPI_MasterInit(&spiDisplay,&SPI_DEV,&SPI_PORT,false,SPI_MODE_0_gc,SPI_INTLVL_LO_gc,false,SPI_PRESCALER_DIV128_gc);

	PMIC_CTRL = PMIC_LOLVLEX_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm;
  sei();
  init_mytimer();

  cmulti.open(Serial::BAUD_57600,F_CPU);
  LEDROT_OFF;
  cmulti.sendInfo("Badezimmer sagt hallo","BR");
  lcd_init(&spiDisplay);
  lcd_set_font(FONT_PROP_8  , NORMAL);
  updateDisplayMain(true);
}

int main()
{

  setup();
  MyTimers[TIMER_LEDBLINK1].state = TM_START;

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



