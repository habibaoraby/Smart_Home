/*
 * room.c
 *
 *  Created on: 9/9/2023
 *      Author: Habiba Oraby
 */
#include "../../LIB/math/datatypes.h"
#include "../../MCAL/dio/dio.h"
#include "../../MCAL/adc/adc.h"
#include "./room.h"
LIGHT_MODE room1;
LIGHT_MODE room2;
LIGHT_MODE room3;
LIGHT_MODE room4;
void switchOffRooms(){
	DIO_VIDSetPinValue(ROOMS_PORT,ROOM1_PIN,LOW);
	DIO_VIDSetPinValue(ROOMS_PORT,ROOM2_PIN,LOW);
	DIO_VIDSetPinValue(ROOMS_PORT,ROOM3_PIN,LOW);
	DIO_VIDSetPinValue(ROOMS_PORT,ROOM4_PIN,LOW);

}
void ROOM_vidInit(){
	DIO_VIDSetPinDirection(ROOMS_PORT,ROOM1_PIN,OUTPUT);
	DIO_VIDSetPinDirection(ROOMS_PORT,ROOM2_PIN,OUTPUT);
	DIO_VIDSetPinDirection(ROOMS_PORT,ROOM3_PIN,OUTPUT);
	DIO_VIDSetPinDirection(ROOMS_PORT,ROOM4_PIN,OUTPUT);
	MADC_vidInit(AVCC,PRE_SCALER_1);
}
void ROOM_switchOn(u8 roomNumber){
	DIO_VIDSetPinValue(ROOMS_PORT,roomNumber,HIGH);
	setRoomMode(roomNumber,ON);
}
void ROOM_switchOff(u8 roomNumber){
	DIO_VIDSetPinValue(ROOMS_PORT,roomNumber,LOW);
	setRoomMode(roomNumber,OFF);
}
void ROOM_AutoLight(u8 roomNumber){
	u16 x;
	switch (roomNumber){
		case ROOM1_PIN:
			x = MADC_u16Read(ROOM1_CHANNEL);
			break;
		case ROOM2_PIN:
			x = MADC_u16Read(ROOM2_CHANNEL);
			break;
		case ROOM3_PIN:
			x = MADC_u16Read(ROOM3_CHANNEL);
			break;
		case ROOM4_PIN:
			x = MADC_u16Read(ROOM1_CHANNEL);
			break;
		default:
			break;
	}

	if(x<465){
		DIO_VIDSetPinValue(ROOMS_PORT,roomNumber,HIGH);
	}else{
		DIO_VIDSetPinValue(ROOMS_PORT,roomNumber,LOW);
	}
	setRoomMode(roomNumber,AUTO);
}
void setRoomMode(u8 roomNumber ,LIGHT_MODE state){
	switch (roomNumber){
		case ROOM1_PIN:
			room1 = state;
			break;
		case ROOM2_PIN:
			room2 = state;
			break;
		case ROOM3_PIN:
			room3 = state;
			break;
		case ROOM4_PIN:
			room4 = state;
			break;
		default:
			break;
	}
}
void autoListener(){
		if(room1==AUTO){
			ROOM_AutoLight(ROOM1_PIN);
		}
		if(room2==AUTO){
			ROOM_AutoLight(ROOM2_PIN);
		}
		if(room3==AUTO){
			ROOM_AutoLight(ROOM3_PIN);
		}
		if(room4==AUTO){
			ROOM_AutoLight(ROOM4_PIN);
		}
;
}
