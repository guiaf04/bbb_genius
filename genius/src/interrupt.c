//
// Created by ryan on 28/06/23.
//

#include "interrupt.h"

#include "hw_types.h"
#include "uart.h"

void timerIrqHandler(void) {
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQSTATUS) = 0x2;

    flag_timer = true;

    DMTimerDisable(SOC_DMTIMER_7_REGS);
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioIsrHandler
 *  Description: Interrupt Service Routine for GPIO
 * =====================================================================================
 */
void gpioIsrHandler(gpioMod GPIO, intMode INT, pinNum PIN){

    uartPutString(UART0, "BUTTON PRESSED\n\r", 17);
    /* Clear the status of the interrupt flags */
    switch (GPIO) {
        case GPIO0:
            if (INT == A) {
                HWREG(SOC_GPIO_0_REGS + GPIO_IRQSTATUS_0) = (1<<PIN);
                GPIOINT0A ^= 1;
            }
            else {
                HWREG(SOC_GPIO_0_REGS + GPIO_IRQSTATUS_1) = (1 << PIN);
                GPIOINT0B ^= 1;
            }
            break;
        case GPIO1:
            if (INT == A) {
                HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0) = (1 << PIN);
                GPIOINT1A ^= 1;
            }
            else {
                HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_1) = (1<<PIN);
                GPIOINT1B ^= 1;
            }
            break;
        case GPIO2:
            if (INT == A) {
                HWREG(SOC_GPIO_2_REGS + GPIO_IRQSTATUS_0) = (1<<PIN);
                GPIOINT2A ^= 1;
            }
            else {
                HWREG(SOC_GPIO_2_REGS + GPIO_IRQSTATUS_1) = (1<<PIN);
                GPIOINT2B ^= 1;
            }
            break;
        case GPIO3:
            if (INT == A) {
                HWREG(SOC_GPIO_3_REGS + GPIO_IRQSTATUS_0) = (1<<PIN);
                GPIOINT3A ^= 1;
            }
            else {
                HWREG(SOC_GPIO_3_REGS + GPIO_IRQSTATUS_1) = (1<<PIN);
                GPIOINT3B ^= 1;
            }
            break;
        default:
            break;

    }
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ISR_Handler
 *  Description: Interrupt Service Routine
 * =====================================================================================
 */

void ISR_Handler(void){
	/* Verify active IRQ number */
	unsigned int irq_number = HWREG(INTCPS + INTC_SIR_IRQ) & 0x7f;
	switch(irq_number){
		case 95:
			timerIrqHandler();
			uartPutString(UART0,"TIMER INTERRUPT!\n\r",19);
			break;
		case 98:

			gpioIsrHandler(GPIO1, A, PIN28);
			uartPutString(UART0,"BUTTON INTERRUPT!\n\r",20);
			break;
	}
    /* acknowledge IRQ */
	HWREG(INTCPS + INTC_CONTROL) = 0x1;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  mirClear
 *  Description: Enable interrupt for a specific source
 * =====================================================================================
 */

void mirClear(int number) {
    int MIR_CLEAR = number / 32;
    int SOURCE = number % 32;
    switch (MIR_CLEAR) {
        case 0:
            HWREG(INTCPS + INTC_MIR_CLEAR0) |= (1<<SOURCE);
            break;
        case 1:
            HWREG(INTCPS + INTC_MIR_CLEAR1) |= (1<<SOURCE);
            break;
        case 2:
            HWREG(INTCPS + INTC_MIR_CLEAR2) |= (1<<SOURCE);
            break;
        case 3:
            HWREG(INTCPS + INTC_MIR_CLEAR3) |= (1<<SOURCE);
            break;
        default:
            break;
    }
}