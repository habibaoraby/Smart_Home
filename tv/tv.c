/*
 * tv.c
 *
 *  Created on: 9/9/2023
 *      Author:  Habiba Oraby
 */
#include "../../LIB/math/datatypes.h"
#include "../../MCAL/dio/dio.h"
#include "../../MCAL/adc/adc.h"
#include "./tv.h"
AC_MODE mode;
void TVandACinit(){
	MADC_vidInit(AVCC,PRE_SCALER_1);
	DIO_VIDSetPinDirection(AC_TV_PORT,TV_PIN,OUTPUT);
	DIO_VIDSetPinDirection(AC_TV_PORT,AC_PIN,OUTPUT);
}
void switchOffTVAndAC(){
	DIO_VIDSetPinValue(AC_TV_PORT,TV_PIN,LOW);
	DIO_VIDSetPinValue(AC_TV_PORT,AC_PIN,LOW);
}
void turnOnTV(){

	DIO_VIDSetPinValue(AC_TV_PORT,TV_PIN,HIGH);
}
void turnOffTV(){
	DIO_VIDSetPinValue(AC_TV_PORT,TV_PIN,LOW);
}
void turnOnAC(){

	DIO_VIDSetPinValue(AC_TV_PORT,AC_PIN,HIGH);
	mode=ON_MODE;
}
void turnOffAC(){
	DIO_VIDSetPinValue(AC_TV_PORT,AC_PIN,LOW);
	mode= OFF_MODE;
}
void autoAC(){
	u8 temprature = MADC_u8getTemprature(AC_CHANNEL);
	if(temprature>AUTO_TEMP){
		DIO_VIDSetPinValue(AC_TV_PORT,AC_PIN,HIGH);
	}else{
		DIO_VIDSetPinValue(AC_TV_PORT,AC_PIN,LOW);
	}
	mode= AUTO_MODE;
}
void ACautoListen(){
	if(mode == AUTO_MODE){
		autoAC();
	}
}
