/*
 * TIMER.c
 *
Configurar el timer 0 y timer 1 en modo de 32bits para hacer la siguiente rutina

una función que active  el convertidor analógico digital y muestre dos señal de cierta frecuencia y amplitud definida.
y las guarde en dos arreglos  de tamaño 1024 y la envié por el protocolo de comunicación asíncrono para ser procesadas
 y regresadas al microcontrolador en valores binarios las cuales modificaran el ancho de pulso 
 y reconstruirán la señal enviada a un transistor o opam.
 */
#include "lib/include.h"
void (*PeriodicTask)(void);
extern void Configurar_Timer0A(void(*task)(void), unsigned long int periodo)
{
    SYSCTL->RCGCTIMER |= (1<<0) | (1<<1) ; //Encender el Periferico Timer 0 y timer 1  pag 404. Listo para acceso
    
    PeriodicTask = task; // asignar la direccion de memoria de la tarea a temporizar
   
    TIMER0->CTL = (0<<0);  // desabilitar el temporizador a usar antes de hacer cambios
    TIMER1->CTL = (0<<0);

    TIMER0->CFG = 0x00000000; // modo de operacion 16 o 32 bits 
    TIMER1->CFG = 0x00000000; // modo de operacion 16 o 32 bits 
    // seleciona 32 bits con 0x0
    
    TIMER0->TAMR = (0x2<<0); // modo periodico en el bit 0:1 poner 0x2 pag 732
    TIMER1->TAMR = (0x2<<0);

    TIMER0->TAILR = periodo - 1; //Para establecer la carga
    TIMER1->TAILR = periodo - 1; //Para establecer la carga

    TIMER0->ICR = 1<<0; //limpia 3l bit correspondiente
    TIMER1->ICR = 1<<0; //limpia 3l bit correspondiente

    TIMER0->IMR = 1<<0; //Mascara de interrupcion de tiempo de espera, con 1 se habilita la int
    TIMER1->IMR = 1<<0; //Mascara de interrupcion de tiempo de espera, con 1 se habilita la int
    
    NVIC->IP[4] = (NVIC->IP[4]&0x00FFFFFF) | 0x20000000; //Duda
    NVIC->ISER[0] = (1UL << 19); //pag 147
    // numero de interrupcion TIMER0A = 19 
    // n=19 ----> [4n+3] [4n+2] [4n+1] [4n] ---> [4n+3]
    
    TIMER0->CTL = (1<<0);//HABILITAR TEMP
    TIMER1->CTL = (1<<0); //HABILITAR EL TEMPORALIZADOR

}

extern void Timer0A_Handler(void)
{
  TIMER0->ICR = 1<<0;// acknowledge TIMER0A timeout
  TIMER1->ICR = 1<<0;
  (*PeriodicTask)();           
}


