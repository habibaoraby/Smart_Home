/*
 * room.h
 *
 *  Created on: 9/9/2023
 *      Author:  Habiba Oraby
 */

#ifndef APP_ROOM_ROOM_H_
#define APP_ROOM_ROOM_H_

#define ROOMS_PORT			PORT_D
#define ROOM1_PIN			3
#define ROOM2_PIN			4
#define ROOM3_PIN			5
#define ROOM4_PIN			6
#define ROOM1_CHANNEL 		ADC_CHANNEL_3
#define ROOM2_CHANNEL		ADC_CHANNEL_4
#define ROOM3_CHANNEL		ADC_CHANNEL_5
#define ROOM4_CHANNEL		ADC_CHANNEL_6
typedef enum{
	OFF,
	ON,
	AUTO
}LIGHT_MODE;
void switchOffRooms();
void ROOM_vidInit();
void ROOM_switchOn(u8 roomNumber);
void ROOM_switchOff(u8 roomNumber);
void ROOM_AutoLight(u8 roomNumber);
void setRoomMode(u8 roomNumber ,LIGHT_MODE state);
void autoListener();
#endif /* APP_ROOM_ROOM_H_ */
