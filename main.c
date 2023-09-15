/*
 * main.c
 *
 *  Created on: 9/9/2023
 *      Author:  Habiba Oraby
 */
#include "../LIB/math/datatypes.h"
#include "../LIB/util/util.h"
#include "../MCAL/adc/adc.h"
#include "../MCAL/dio/dio.h"
#include "../MCAL/eeprom/eeprom.h"
#include "../HAL/lcd/lcd.h"
#include "../HAL/keypad/keypad.h"
#include "./auth/auth.h"
#include "./room/room.h"
#include "./door/door.h"
#include "./tv/tv.h"
#include "./component/authpage/auth.h"
#include "./component/tvandac/tvpage.h"
#include "./component/roompage/roompage.h"
#include<util/delay.h>
void disableAll(){
	switchOffTVAndAC();
	switchOffRooms();
	closeDoor();
}
int main(){
	HCLCD_vidInit();
	HKEYPAD_vidinit();
	u8 username[10]= {'\0'};
	u8 pass[8] = {'\0'};
	if(MC_EEPROM_u8Read(USER_COUNT_LOCATION)==0xff){
		displaySignUp(username,pass);
	}
	displayLogin(username,pass);
	while(1){
		ROOM_vidInit();
		TVandACinit();
		HCLCD_vidClear();
		HCLCD_vidSendString("1.logOut 3.reset");
		HCLCD_vidGoTo(0,1);
		HCLCD_vidSendString("2.addnew  #.more");
		u8 key='+';
		while(key!='1' && key!='2' && key!='3' && key!='#'){
			key = HKEYPAD_u8getPressedValue();
		}
		switch(key){
		case '1' :
			disableAll();
			logOut();
			while(HKEYPAD_u8getPressedValue()!='#');
			HCLCD_vidClear();
			loginExecute(username,pass);
			_delay_ms(600);
			HCLCD_vidClear();
			break;
		case '2' :
			autoListener();
			ACautoListen();
			username[0]= '\0';
			pass[0] = '\0';
			signUpExecute(username,pass);
			_delay_ms(600);
			HCLCD_vidClear();
			break;
		case '3' :
			MC_EEPROM_RESET();
			HCLCD_vidClear();
			username[0]= '\0';
			pass[0] = '\0';
			displaySignUp(username,pass);
			_delay_ms(200);
			HCLCD_vidClear();
			username[0]= '\0';
			pass[0] = '\0';
			displayLogin(username,pass);
			break;
		case '#':
			displayRoomPageOne();
			break;
		default:
			break;
		}
	}
	return 0;
}

