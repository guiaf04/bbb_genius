/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/07/2023 22:00:00
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *        Authors:  Ryan Guilherme (ryanguilhermetbt@gmail.com)
 *                  Guilherme Araújo ()
 *                  Éliton Melo (elitonp.melo@gmail.com)
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "timer.h"
#include "gpio.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "interrupt.h"

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define CM_PER_GPMCBEn1_REGS                    0x44E10878

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/

bool flag_gpio;

bool flag_timer;


// TODO: make butConfig modular
void butConfig ( ){
    /* configure pin 28 mux for input GPIO */
    HWREG(CM_PER_GPMCBEn1_REGS) |= 0x2F;
    //gpioPinMuxSetup(GPIO1, 28);

    /* clear pin 28 for input, led USR0, TRM 25.3.4.3 */
    HWREG(SOC_GPIO_1_REGS + GPIO_OE) |= 1<<28;

    flag_gpio = false;

    /* Setting interrupt GPIO pin. */
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_SET_0) |= 1<<28;

    /* Enable interrupt generation on detection of a rising edge.*/
    HWREG(SOC_GPIO_1_REGS + GPIO_RISINGDETECT) |= 1<<28;

    /* Enable debounce for pin 28 GPIO1 */
    HWREG(SOC_GPIO_1_REGS + GPIO_DEBOUNCENABLE) |= 1<<28;
}/* -----  end of function butConfig  ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */
int main(void){

    disableWdt();

	return(0);
} /* ----------  end of function main  ---------- */

/* COMPILE AND RUN
 * setenv app "setenv autoload no; setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1; tftp 0x80000000 /tftpboot/appGenius.bin; go 0x80000000;"
 * run app
*/
