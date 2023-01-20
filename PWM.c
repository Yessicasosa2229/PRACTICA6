
#include "lib/include.h"



extern void Configura_Reg_PWM1(uint16_t freq)
{
//------------------------------------EXPERIMENTO 1-----------------------------------------------------------------------------------------
  /*

    SYSCTL->RCGCPWM |= (1<<0); //Enable reloj de modulo 0 PWM1 pag 354
    SYSCTL->RCGCGPIO |= (1<<1); //Enable reloj de GPIO Puerto b pag 340 pin 4
    SYSCTL->RCC |= (1<<20);
    SYSCTL->RCC &= ~(0x07<<17);

    //SYSCTL->RCC &= (0xFFF0FFFF);
    //AFSEL HABILITA LAS FUNCIONES ALTERNAS 
    GPIOB->AFSEL |= (1<<4); //Control de registros ya sea por GPIO o Otros Pag 672
    //GPIOB_AHB->AFSEL |= 0x0E; 
    //GPIOB->PCTL |= (GPIOB_AHB->PCTL & 0xFFFF0FFF) | 0x00040000; //Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689
    GPIOB->PCTL |=  0x00040000; 
    GPIOB->DEN |= (1<<4); // para decirle si es digital o no Pag 682
   // PWM0->CC &= ~(1<<8);  //Enable o DisabXle Divisor  Pag 1747
    PWM0->_1_CTL &= ~(1<<0); //GENERADOR QUE VOY A USAR, GENERADOR 1 1266 debo desahbilitar para poder configurar
    //PWM0->_1_CTL &= ~(1<<1);
    // va negado
   // PWM0->_1_CTL = (0<<0); //Bloqueo y desbloqueo
    //PWM0->_1_GENB = 0x0000080C; //Registro de las acciones del pwm Pag 1285
    //PWM0->_1_GENA = 0x0000008C;
    PWM0->_1_GENA = 0x008C; //Registro de las acciones del pwm usaremos generador a del generador 1
    //PWM0->_0_GENB = 0x0000008C;//PWM5
    //PWM0->_1_LOAD = (int)(20000000/freq); //cuentas=fclk/fpwm  para 1khz cuentas = (16,000,000/1000)
    //PWM0->_0_LOAD = (int)(25000000/freq); //25000000/10000=2500   **el25MHZ, es porque el valor inicial era 50MHz pero se dividio entre 2
    PWM0->_1_LOAD = 2500; //valor de carga 
    PWM0->_1_CMPB = 2000; 
    PWM0->_1_CMPA = 2000; //80%
  //  PWM0->_0_CMPA = 15000;
    PWM0->_1_CTL |= (1<<0);// Se activa el generador 1
  //  PWM0->_0_CTL = (1<<0);// Se activa el generador 2
    PWM0->ENABLE = (1<<2); //habilitar el bloque pa que pase, es el MnPWM2 en el pin2 Pag 1247

*/
//-------------------------------------Experimento 2---------------------------------------------------------------------------
    SYSCTL->RCGCPWM |= (1<<0); //Enable reloj de modulo 0 PWM1 pag 354
    SYSCTL->RCGCGPIO |= (1<<1);//Hab reloj GPIO PUERTO B
    SYSCTL->RCGCGPIO |= (1<<4); //Enable reloj de GPIO Puerto E pag 340 pin 4

    SYSCTL->RCC |= (1<<20); //Ponemos en alto bit USEPWMDIV para dividir la señal del reloj
    SYSCTL->RCC &= 0xFFF0FFFF; //para bit 17-19 que se divida entre 2 
    SYSCTL->RCC &= 0xFFF8FFFF; //config para bit 17-19

    SYSCTL->RCGC2 |= (1<<1);           //Activación del reloj para el PUERTO B
    SYSCTL->RCGC2 |= (1<<4);           //Activación del reloj para el  PUERTO E

    //SYSCTL->RCC &= (0xFFF0FFFF);
    //AFSEL HABILITA LAS FUNCIONES ALTERNAS 
    GPIOB->AFSEL |= (1<<4); //Control de registros ya sea por GPIO o Otros Pag 672 pines 4 y 6
    GPIOB->AFSEL |= (1<<6); // Pin b6
    GPIOE->AFSEL |= (1<<4); //pin e4
    //GPIOB_AHB->AFSEL |= 0x0E; 
    //GPIOB->PCTL |= (GPIOB_AHB->PCTL & 0xFFFF0FFF) | 0x00040000; //Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689
    GPIOB->PCTL |= 0x00040000;  //gen1 pin b4
    GPIOB->PCTL |= 0x04000000; //gen0 pin b6
    GPIOE->PCTL |= (0xFFF0FFFF) | 0x00040000; //gen2 pin E4
    //registro PCTL es pwm Pag 689 hab la func 4 del pin PE4 - en el port mux 4 
    //para el pin e4 del puerto E, se debe enmascarar porque no hay valores por default

    GPIOB->DEN |= (1<<4); // para decirle si es digital o no Pag 682
    GPIOB->DEN |= (1<<6); //pin b6
    GPIOE->DEN |= (1<<4); // Pin e4
   // PWM0->CC &= ~(1<<8);  Enable o DisabXle Divisor  Pag 1747
    PWM0->_0_CTL &= ~(1<<0); //GENERADOR QUE VOY A USAR, GENERADOR 1 1266 debo desahbilitar para poder configurar
    PWM0->_1_CTL &= ~(1<<0); //gen 1 del pwm0
    PWM0->_2_CTL &= ~(1<<0); //gen 2 
    // va negado
   // PWM0->_1_CTL = (0<<0); Bloqueo y desbloqueo
    //PWM0->_1_GENB = 0x0000080C; Registro de las acciones del pwm Pag 1285
    //PWM0->_1_GENA = 0x0000008C;
    PWM0->_0_GENA = 0x008C; //Registro de las acciones del pwm usaremos generador a del generador 1
    PWM0->_1_GENA = 0x008C; //gen 1
    PWM0->_2_GENA = 0x008C; //gen 2

    //PWM0->_0_GENB = 0x0000008C;//PWM5
    //PWM0->_1_LOAD = (int)(20000000/freq); cuentas=fclk/fpwm  para 1khz cuentas = (16,000,000/1000)
    //PWM0->_0_LOAD = (int)(25000000/freq); //25000000/10000=2500   **el25MHZ, es porque el valor inicial era 50MHz pero se dividio entre 2
    //(20000000/8 = 2500000/50=50000)
    PWM0->_0_LOAD = 50000; //valor de carga 
    PWM0->_0_CMPB = 40000; //80%
    PWM0->_0_CMPA = 40000; //80%

    PWM0->_1_LOAD = 50000; //valor de carga 
    PWM0->_1_CMPB = 40000; 
    PWM0->_1_CMPA = 40000; //80%

    PWM0->_2_LOAD = 50000; //valor de carga 
    PWM0->_2_CMPB = 40000; 
    PWM0->_2_CMPA = 40000; //80%
  //  PWM0->_0_CMPA = 15000;
    PWM0->_0_CTL |= (1<<0);// Se activa el generador 0
    PWM0->_1_CTL |= (1<<0);// Se activa el generador 1
    PWM0->_2_CTL |= (1<<0);// Se activa el generador 2
  //  PWM0->_0_CTL = (1<<0);// Se activa el generador 2
    PWM0->ENABLE = (1<<0) | (1<<2); //habilitar el bloque pa que pase, es el MnPWM2 en el pin2 y mnpwm0Pag 124 7
    PWM0->ENABLE = (1<<4); //m0pwm4
}



