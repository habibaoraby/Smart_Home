/*
 * tv.h
 *
 *  Created on: 9/9/2023
 *      Author:  Habiba Oraby
 */

#ifndef APP_TV_TV_H_
#define APP_TV_TV_H_
#define TV_PIN 			2
#define AC_PIN			7
#define AC_CHANNEL		ADC_CHANNEL_7
#define AC_TV_PORT		PORT_D
#define AUTO_TEMP		27
void turnOnTV();
void turnOffTV();
void turnOnAC();
void turnOffAC();
void autoAC();
void ACautoListen();
void TVandACinit();
void switchOffTVAndAC();
typedef enum{
	ON_MODE,
	OFF_MODE,
	AUTO_MODE
}AC_MODE;

#endif /* APP_TV_TV_H_ */
