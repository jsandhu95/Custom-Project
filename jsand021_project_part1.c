/*    Author: jsand021 - Jeevan Sandhu
 *  Partner(s) Name:
 *    Lab Section: 23
 *    Assignment: Custom Project
 *    Exercise Description: [optional - include for your own benefit]
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <avr/interrupt.h>
#include "lcd.h"
#include "adc.h"

enum States {state_init, state_start, state_stationary, state_north, state_northeast, state_east, state_southeast, state_south, state_southwest, state_west, state_northwest, state_reset} state;

enum Movement {center, clear, move_north, move_northeast, move_east, move_southeast, move_south, move_southwest, move_west, move_northwest} move;

unsigned char x;
unsigned char y;
static unsigned char display[84][48] = {0};

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerSet(unsigned long M){
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

void TimerOn(){
    // avr timer/counter controller register TCCR1
    TCCR1B = 0x0B;

    // avr output compare register OCR1A
    OCR1A = 125;

    // avr timer interrupt mask register
    TIMSK1 = 0x02;

    // initialize avr counter
    TCNT1 = 0;

    _avr_timer_cntcurr = _avr_timer_M;

    // enable global interrupts
    SREG |= 0x80;
}

void TimerOff(){
    TCCR1B = 0x00;
}

void TimerISR(){
    TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
    _avr_timer_cntcurr--;
    if(_avr_timer_cntcurr == 0){
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

/*
void display(Movement move){
  switch(move){
    case center:
      DisplayLCD(xxx);
      break;
    case move_north:
      DisplayLCD(xxx);
      break;
    case move_northeast:
      DisplayLCD(xxx);
      break;
    case move_east:
      DisplayLCD(xxx);
      break;
    case move_southeast;
      DisplayLCD(xxx);
      break;
    case move_south:
      DisplayLCD(xxx);
      break;
    case move_southwest:
      DisplayLCD(xxx);
      break;
    case move_west:
      DisplayLCD(xxx);
      break;
    case move_northwest:
      DisplayLCD(xxx);
      break;
    case clear:
      ClearDisplay();
      break;
    default:
      break;
  }
}

*/

void tick() {
//    unsigned char joystick = ~PINC;'
    unsigned char joystick = GetDirection();
    unsigned char ir = ~PINB & 0x01;
/*
    unsigned char north = joystick & 0x01;
    unsigned char northeast = joystick & 0x09;
    unsigned char east = joystick & 0x08;
    unsigned char southeast = joystick & 0x0A;
    unsigned char south = joystick & 0x02;
    unsigned char southwest = joystick & 0x06;
    unsigned char west = joystick & 0x04;
    unsigned char northwest = joystick & 0x05;
 */

    
/*    switch(state) {
        case state_init:
            state = state_start;
            break;
        case state_start:
            if(north)
                state = state_north;
            if(northeast)
                state = state_northeast;
            if(east)
                state = state_east;
            if(southeast)
                state = state_southeast;
            if(south)
                state = state_south;
            if(southwest)
                state = state_southwest;
            if(west)
                state = state_west;
            if(northwest)
                state = state_northwest;
            if(ir)
                state = state_reset;
            break;
        case state_stationary:
            if(north)
                state = state_north;
            if(northeast)
                state = state_northeast;
            if(east)
                state = state_east;
            if(southeast)
                state = state_southeast;
            if(south)
                state = state_south;
            if(southwest)
                state = state_southwest;
            if(west)
                state = state_west;
            if(northwest)
                state = state_northwest;
            if(ir)
                state = state_reset;
            break;
        case state_north:
            if(north)
                state = state_north;
            if(northeast)
                state = state_northeast;
            if(east)
                state = state_east;
            if(southeast)
                state = state_southeast;
            if(south)
                state = state_south;
            if(southwest)
                state = state_southwest;
            if(west)
                state = state_west;
            if(northwest)
                state = state_northwest;
            if(ir)
                state = state_reset;
            break;
        case state_northeast:
            if(north)
                state = state_north;
            if(northeast)
                state = state_northeast;
            if(east)
                state = state_east;
            if(southeast)
                state = state_southeast;
            if(south)
                state = state_south;
            if(southwest)
                state = state_southwest;
            if(west)
                state = state_west;
            if(northwest)
                state = state_northwest;
            if(ir)
                state = state_reset;
            break;
        case state_east:
            if(north)
                state = state_north;
            if(northeast)
                state = state_northeast;
            if(east)
                state = state_east;
            if(southeast)
                state = state_southeast;
            if(south)
                state = state_south;
            if(southwest)
                state = state_southwest;
            if(west)
                state = state_west;
            if(northwest)
                state = state_northwest;
            if(ir)
                state = state_reset;
            break;
        case state_southeast:
            if(north)
                state = state_north;
            if(northeast)
                state = state_northeast;
            if(east)
                state = state_east;
            if(southeast)
                state = state_southeast;
            if(south)
                state = state_south;
            if(southwest)
                state = state_southwest;
            if(west)
                state = state_west;
            if(northwest)
                state = state_northwest;
            if(ir)
                state = state_reset;
            break;
        case state_south:
            if(north)
                state = state_north;
            if(northeast)
                state = state_northeast;
            if(east)
                state = state_east;
            if(southeast)
                state = state_southeast;
            if(south)
                state = state_south;
            if(southwest)
                state = state_southwest;
            if(west)
                state = state_west;
            if(northwest)
                state = state_northwest;
            if(ir)
                state = state_reset;
            break;
        case state_southwest:
            if(north)
                state = state_north;
            if(northeast)
                state = state_northeast;
            if(east)
                state = state_east;
            if(southeast)
                state = state_southeast;
            if(south)
                state = state_south;
            if(southwest)
                state = state_southwest;
            if(west)
                state = state_west;
            if(northwest)
                state = state_northwest;
            if(ir)
                state = state_reset;
            break;
        case state_west:
            if(north)
                state = state_north;
            if(northeast)
                state = state_northeast;
            if(east)
                state = state_east;
            if(southeast)
                state = state_southeast;
            if(south)
                state = state_south;
            if(southwest)
                state = state_southwest;
            if(west)
                state = state_west;
            if(northwest)
                state = state_northwest;
            if(ir)
                state = state_reset;
            break;
        case west:
            if(north)
                state = state_north;
            if(northeast)
                state = state_northeast;
            if(east)
                state = state_east;
            if(southeast)
                state = state_southeast;
            if(south)
                state = state_south;
            if(southwest)
                state = state_southwest;
            if(west)
                state = state_west;
            if(northwest)
                state = state_northwest;
            if(ir)
                state = state_reset;
            break;
        case northwest:
            if(north)
                state = state_north;
            if(northeast)
                state = state_northeast;
            if(east)
                state = state_east;
            if(southeast)
                state = state_southeast;
            if(south)
                state = state_south;
            if(southwest)
                state = state_southwest;
            if(west)
                state = state_west;
            if(northwest)
                state = state_northwest;
            if(ir)
                state = state_reset;
            break;
        case state_reset:
            state = state_start;
            break;
        default:
            state = state_init;
    }
*/
    switch(state){
        case state_init:
            state = state_start;
            break;
        case state_start:
            if(joystick == UP){
                state = north;
            }
            if(joystick == DOWN){
                state = south;
            }
            if(joystick == LEFT){
                state = west;
            }
            if(joystick == RIGHT){
                state = east;
            }
            if(ir){
                state = state_reset;
            }
            break;
        case north:
            if(joystick == UP){
                state = north;
            }
            if(joystick == DOWN){
                state = south;
            }
            if(joystick == LEFT){
                state = west;
            }
            if(joystick == RIGHT){
                state = east;
            }
            if(ir){
                state = state_reset;
            }
            break;
        case south:
            if(joystick == UP){
                state = north;
            }
            if(joystick == DOWN){
                state = south;
            }
            if(joystick == LEFT){
                state = west;
            }
            if(joystick == RIGHT){
                state = east;
            }
            if(ir){
                state = state_reset;
            }
            break;
        case west:
            if(joystick == UP){
                state = north;
            }
            if(joystick == DOWN){
                state = south;
            }
            if(joystick == LEFT){
                state = west;
            }
            if(joystick == RIGHT){
                state = east;
            }
            if(ir){
                state = state_reset;
            }
            break;
        case east:
            if(joystick == UP){
                state = north;
            }
            if(joystick == DOWN){
                state = south;
            }
            if(joystick == LEFT){
                state = west;
            }
            if(joystick == RIGHT){
                state = east;
            }
            if(ir){
                state = state_reset;
            }
            break;
        case state_reset:
            state = state_start;
            break;
        default:
            state = state_start;
            break;
    }
        
            
    
    switch(state) {
        case state_init:
            x = 42;
            y = 24;
            break;
        case state_start:
            LCD_write_byte(display[x][y], 0);
            break;
        case state_stationary:
            break;
        case state_north:
            if(y <= 48){y++};
            LCD_write_byte(display[x][y], 0);
            break;
        case state_northeast:
            if(x <= 84){x++};
            if(y <= 48){y++};
            LCD_write_byte(display[x][y], 0);
            break;
        case state_east:
            if(x <= 84){x++};
            LCD_write_byte(display[x][y], 0);
            break;
        case state_southeast:
            if(x <= 84){x++};
            if(y >= 0){y--};
            LCD_write_byte(display[x][y], 0);
            break;
        case state_south:
            if(y >= 0){y--};
            LCD_write_byte(display[x][y], 0);
            break;
        case state_southwest:
           if(x >= 0){x--};
            if(y >= 0){y--};
            LCD_write_byte(display[x][y], 0);
            break;
        case state_west:
            if(x >= 0){x--};
            LCD_write_byte(display[x][y], 0);
            break;
        case state_northwest:
            if(x >= 0){x--};
            if(y <= 48){y++};
            LCD_write_byte(display[x][y], 0);
            break;
        case state_reset:
            LCD_clear();
            x = 42;
            y = 24;
            LCD_write_byte(display[x][y], 0);
            break;
    }
}


void main(void) {
    DDRC = 0x00; PORTC = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;
    
    LCD_init();
    ADC_init();
    
    state = state_init;
    PWM_on();
    TimerSet(100);
    TimerOn();
    while (1) {
        tick();
        while(!TimerFlag);
        TimerFlag = 0;
    }
    return 0;
}
