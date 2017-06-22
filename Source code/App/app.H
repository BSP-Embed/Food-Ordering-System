#ifndef _APP_H
#define _APP_H

/********* EEPROM CONFIGURATION ******************/
#define EEPROM_DISPLAY				0
/********* EEPROM CONFIGURATION ENDS*************/


/************ LCD CONFIGURATION ********************/
#define LCD_DDR           	   		DDRB 
#define LCD_DATA_PORT          		PORTB
#define LCD_ENABLE_PIN        		PB3 
#define LCD_REGISTER_SELECT_PIN     PB2
#define DISPLAY_INIT				1
#define LCD_NSCRL					1
#define FLOAT_T0_STRING				1
#define DECIMAL_PRECISION			10

/******** LCD CONFIGURATION ENDS ****************/

/* BUZZER: CONFIGURATION */
#define	BUZ_DDR						DDRC
#define	BUZ_PORT					PORTC
#define	BUZ_PIN						PC1
#define OFF_TIME					100
/******** BUZZER CONFIGURATION ENDS ****************/

/* LED: CONFIGURATION */

#define	LED_DDR			DDRC
#define	LED_PORT		PORTC
#define	LED_PIN			PC0

#define OFF_TIME		100
/******** LED CONFIGURATION ENDS ****************/

/* GSM: CONFIGURATION */

#define MSG_START					""
#define MSG_END						""
/******** GSM CONFIGURATION ENDS ****************/


/******** ADC CONFIGURATION ****************/
//#define REF_VOL_256
/******** ADC CONFIGURATION ENDS ****************/




/******** RFID  CONFIGURATION ****************/
//#define DISPLAY_TAGNUMBER	1

/******** MOTOR CONFIGURATION   ****************/
#define MOT_PORT			PORTC
#define MOT_DDR				DDRC
#define MOT1_AN				PC4
#define MOT1_CA				PC5
/******** MOTOR CONFIGURATION ENDS  ****************/

/******* SERVO CONFIGURATION ********************/
#define SERVO_DDR			DDRD
#define SERVO_PORT			PORTD
#define SERVO1				PD5
/******** SERVO CONFIGURATION ENDS **************/

/******* ULTRASONIC SENSOR CONFIGURATION ********/
#define	ULTSEN_DDR			DDRB
#define	ULTSEN_PORT			PORTB
#define	ULTSEN_PIN			PINB
#define ECHO_PIN			PB0
#define TRIG_PIN			PB1
/****** ULTRASONIC CONFIGURATION ENDS **********/

/****** HX711 24-BIT ADC CONFIGURATIONS *******/
#define HX711_DDR			DDRD
#define HX711_PORT			PORTD
#define HX711_INPIN			PIND
#define HX711_CLK_PIN		PD3
#define HX711_DIN_PIN		PD2
/****** HX711 24-BIT ADC CONFIGURATIONS ENDS*******/


/************ RFID CONFIGURATION ***********/
//#define DISPLAY_TAGNUMBER
/************ RFID CONFIGURATION ***********/


/*********** RF CONFIGURATION ************/
#define RFDDR				DDRA
#define RFPORT				PORTA
#define RFEN_PIN			PC3
/*********** RF CONFIGURATION ENDS *******/

/******** GRAPHICS LCD CONFIGURATION    *****/
#define KS0108_DATA_PORT	PORTB
#define KS0108_DATA_DIR		DDRB
#define KS0108_DATA_PIN		PINB

#define KS0108_CTRL_PORT	PORTD
#define KS0108_CTRL_DIR		DDRD

#define KS0108_RS			(1 << 2)
#define KS0108_RW			(1 << 3)
#define KS0108_EN			(1 << 4)

#define KS0108_CS1			(1 << 6)
#define KS0108_CS2			(1 << 5)
#define KS0108_CS3			(1 << 6)
/******** GRAPHICS LCD CONFIGURATION ENDS  *****/

/******** TOUCH SCREEN CONFIGURATION   ******/
#define TSCREEN_DDR		DDRC
#define TSCREEN_PORT	PORTC
#define TSCREEN_4		PC7
#define TSCREEN_3		PC6
#define TSCREEN_2		PC5
#define TSCREEN_1		PC4
/******** TOUCH SCREEN CONFIGURATION ENDS******/

#endif
