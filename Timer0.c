/*
 * File:   Timer.c
 * Author: Oscar Fernando Donis Martínez
 *
 * Created on 20 de enero de 2023, 12:11 PM
 */

#define _XTAL_FREQ 4000000
#include "Timer0.h"
#include <xc.h>

/**************************************************
 Funcion para configurar Timer
 ***************************************************/
void setupTimer0(void){
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 6;
    T0IE = 1;
    T0IF = 1;
    TMR0 = 6;
    GIE = 1;
}
