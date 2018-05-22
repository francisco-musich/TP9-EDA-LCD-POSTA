#pragma once

//Creo byte
typedef unsigned char BYTE;
typedef unsigned long DWORD;

//Pedido por la catedra
#define MY_LCD_DESCRIPTION "EDA LCD 5 B"
#define CONNECTING_TIME 10 //in seconds

//Rs defs
#define DR true		//Data
#define IR false	//Instruction

//Asignacion de los puertos segun su posicion fisica
#define PORT_P0 0
#define PORT_P1 1
#define PORT_P2 2
#define PORT_P3 3
#define PORT_P4 4
#define PORT_P5 5
#define PORT_P6 6
#define PORT_P7 7


//Asignacion logica o funcional a cada pin
#define LCD_E (1<<PORT_P0)
#define LCD_RS (1<<PORT_P1)
#define LCD_D4 (1<<PORT_P4)
#define LCD_D5 (1<<PORT_P5)
#define LCD_D6 (1<<PORT_P6)
#define LCD_D7 (1<<PORT_P7)


//Mascaras
#define NOT_LCD_E ~(LCD_E)
#define NOT_LCD_RS ~(LCD_RS)
#define NOT_LCD_D4 ~(LCD_D4)
#define NOT_LCD_D5 ~(LCD_D5)
#define NOT_LCD_D6 ~(LCD_D6)
#define NOT_LCD_D7 ~(LCD_D7)


//Definicion a niveles logicos
#define LCD_E_ON (LCD_E)
#define LCD_D4_ON (LCD_D4)
#define LCD_D5_ON (LCD_D5)
#define LCD_D6_ON (LCD_D6)
#define LCD_D7_ON (LCD_D7)

#define LCD_E_OFF (LCD_E ^ LCD_E)
#define LCD_D4_OFF (LCD_D4 ^ LCD_D4)
#define LCD_D5_OFF (LCD_D5 ^ LCD_D5)
#define LCD_D6_OFF (LCD_D6 ^ LCD_D6)
#define LCD_D7_OFF (LCD_D7 ^ LCD_D7)

#define LCD_RS_DR (LCD_RS)
#define LCD_RS_IR (LCD_RS ^ LCD_RS)


//Definicion de funciones LCD HITACHI
#define LCD_CLEAR 0x01
#define LCD_DISPLAY  0x0F
#define LCD_FUNCTION8 0x34
#define LCD_FUNCTION4 0x28
#define LCD_DISPLAY_AOFF 0x0D
#define LCD_ENTRY 0x06

//Definiciones para impresion de pantalla
#define RS_WRITE 0
#define CLEAR_CHAR 0x20
#define COLUMNA 16
#define FILAS 2
#define OFFSET_ROW_DRAM 0x40
#define ADDRESS_COUNT_SET_MASK 0x80
#define ELEMENTOS_TOTALES (COLUMNA*FILAS)
#define ELEMENTOS_TOTALES_AJUSTADO ((COLUMNA*FILAS)-1)	//Le resto el 1 por que el 0 tambien es un elemento


