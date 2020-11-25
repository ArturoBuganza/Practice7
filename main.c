/*
 * File:   main.c
 * Author: COREI5
 *
 * Created on November 24, 2020, 5:46 PM
 */

#include "device_config.h"
#include "stdio.h"
#include "string.h"

void port_init(void){
    ANSELB = 0x00;
    ANSELD = 0x00;
    TRISB = 0xF0;
    TRISD = 0x00;
}

unsigned char bcdDecoder(char input[]){
    switch(input[0]){
        case '0': return 0x00;
        case '1': return 0x01;
        case '2': return 0x02;
        case '3': return 0x03;
        case '4': return 0x04;
        case '5': return 0x05;
        case '6': return 0x06;
        case '7': return 0x07;
        case '8': return 0x08;
        case '9': return 0x09;
        case 'A': return 0x0A;
        case 'B': return 0x0B;
        case 'C': return 0x0C;
        case 'D': return 0x0D;
        case 'E': return 0x0E;
        case 'F': return 0x0F;
        default: return 0x00;
    }
}

void main(void) {
    port_init();
    unsigned short column = 0;
    char digit[10];
    char prevdigit[10];
    while(1){
        if(column <= 2){
            column++;
        }
        else{
            column=0;
        }
        switch(column){
            case 0: LATB = 0xE; break;
            case 1: LATB = 0xD; break;
            case 2: LATB = 0xB; break;
            case 3: LATB = 0x7; break;
            default: LATB = 0x00; break;
        }
        
        //PRIMERA FILA
        if(PORTB == 0XEE){
            strcpy(digit, "A");
        }
        if(PORTB == 0XDE){
            strcpy(digit, "3");
        }
        if(PORTB == 0XBE){
            strcpy(digit, "2");
        }
        if(PORTB == 0X7E){
            strcpy(digit, "1");
        }
        
        //SEGUNDA FILA
        if(PORTB == 0XED){
            strcpy(digit, "B");
        }
        if(PORTB == 0XDD){
            strcpy(digit, "6");
        }
        if(PORTB == 0XBD){
            strcpy(digit, "5");
        }
        if(PORTB == 0X7D){
            strcpy(digit, "4");
        }
        
        //TERCERA FILA
        if(PORTB == 0XEB){
            strcpy(digit, "C");
        }
        if(PORTB == 0XDB){
            strcpy(digit, "9");
        }
        if(PORTB == 0XBB){
            strcpy(digit, "8");
        }
        if(PORTB == 0X7B){
            strcpy(digit, "7");
        }
        
        //CUARTA FILA
        if(PORTB == 0XE7){
            strcpy(digit, "D");
        }
        if(PORTB == 0XD7){
            strcpy(digit, "F");
        }
        if(PORTB == 0XB7){
            strcpy(digit, "0");
        }
        if(PORTB == 0X77){
            strcpy(digit, "E");
        }
        if(strcmp(prevdigit,digit)){
            LATD << 4;
            LATD = LATD + bcdDecoder(digit);
            strcpy(prevdigit, digit);
        }
        
    }
    
    return;
}
