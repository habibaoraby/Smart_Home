/*
 * auth.c
 *
 *  Created on: 9/9/2023
 *      Author: Habiba Oraby
 */
#include "../../LIB/math/datatypes.h"
#include "../../LIB/util/util.h"
#include "../../MCAL/eeprom/eeprom.h"
#include "../../HAL/keypad/keypad.h"
#include "../../HAL/lcd/lcd.h"
#include "util/delay.h"
#include "./auth.h"
LOGIN_STATUS detectLoginData(u8*name , u8*password){
	u8 usersCounter= 0;
	u8 passAddress ;
	u8 userName[10];
	u8 userPass[8];
	while(MC_EEPROM_u8Read(usersCounter) != 0xff && usersCounter < MAXIMUM_USERNAME_SIZE*MAXIMUM_USERS ){
		MC_EEPROM_vidRead(usersCounter,MAXIMUM_USERNAME_SIZE,userName);
		if( util_u8StringCompare(userName,name) ){
			break;
		}
		usersCounter+=MAXIMUM_USERNAME_SIZE;
	}
	if( !util_u8StringCompare(userName,name)  ){
		return INVALID_USER_NAME;
	}
	passAddress= (MAXIMUM_USERNAME_SIZE*MAXIMUM_USERS)+((usersCounter/MAXIMUM_USERNAME_SIZE)*MAXIMUM_PASSWORD_SIZE);
	MC_EEPROM_vidRead(passAddress,MAXIMUM_PASSWORD_SIZE,userPass);
	if( !util_u8StringCompare(userPass,password) ){
		return INVALID_USER_PASSWORD;
	}
	return LOGGED_IN;
}
void loginExecute(u8*name , u8*password){
	LOGIN_STATUS status;
	u8 counter = MAXIMUM_TRIES;
	while(1){
		if(counter==0){
			HCLCD_vidSendString("maximum of tries");
			HCLCD_vidGoTo(0,1);
			HCLCD_vidSendString("wait for");
			HCLCD_vidGoTo(12,1);
			HCLCD_vidSendString("sec");
			counter = 30;
			while(counter){
				if(counter<10){
					HCLCD_vidGoTo(9,1);
					HCLCD_vidSendData('0');
					HCLCD_vidGoTo(10,1);
					HCLCD_vidSendNumber(counter);
				}else{
					HCLCD_vidGoTo(9,1);
					HCLCD_vidSendNumber(counter);
				}
				_delay_ms(800);
				counter--;
			}
			counter = MAXIMUM_TRIES;
			HCLCD_vidClear();

		}
		counter--;
		HCLCD_vidSendString("insert name");
		getData(CHARACTERS,name,0,1);
		HCLCD_vidClear();
		HCLCD_vidSendString("insert password");
		getData(NUMBERS,password,0,1);
		status = detectLoginData(name,password);
		HCLCD_vidClear();
		if(status == LOGGED_IN){
			HCLCD_vidSendString("confirmed");
			break;
		}else if(status == INVALID_USER_NAME ){
			HCLCD_vidSendString("invalid name");

		}
		else if(status == INVALID_USER_PASSWORD  ){
			HCLCD_vidSendString("invalid pass");
		}
		_delay_ms(200);
		HCLCD_vidClear();
		if(counter==0){
			continue;
		}
		HCLCD_vidSendNumber(counter);
		HCLCD_vidSendString(" tries left");
		HCLCD_vidGoTo(0,1);
		HCLCD_vidSendString("# to proceed");
		while(HKEYPAD_u8getPressedValue()!='#');
		HCLCD_vidClear();

	}
}
SIGNUP_STATUS signUpOrAddUser(u8*name, u8*password){
	u8 count =  MC_EEPROM_u8Read(USER_COUNT_LOCATION);
	if(count == 0xff ){
		MC_EEPROM_vidWrite(USER_COUNT_LOCATION,0);
	}
	count =  MC_EEPROM_u8Read(USER_COUNT_LOCATION);
	if(count == MAXIMUM_USERS){
		return NO_ROOM;
	}
	MC_EEPROM_vidWriteString((count)*MAXIMUM_USERNAME_SIZE ,name);
	MC_EEPROM_vidWriteString( ((MAXIMUM_USERS*MAXIMUM_USERNAME_SIZE)+((count)*MAXIMUM_PASSWORD_SIZE)) ,password );
	count++;
	MC_EEPROM_vidWrite(USER_COUNT_LOCATION,count);
	return SIGNED;
}
boolean	signUpExecute(u8*name, u8*password){
	SIGNUP_STATUS status ;
	while(name[0] == '\0'){
		HCLCD_vidClear();
		HCLCD_vidSendString("insert name");
		getData(CHARACTERS,name,0,1);
		HCLCD_vidClear();
		HCLCD_vidSendString("name: ");
		HCLCD_vidSendString(name);
		HCLCD_vidGoTo(0,1);
		HCLCD_vidSendString("#continue");
		HCLCD_vidGoTo(11,1);
		HCLCD_vidSendString("*back");
		u8 key ='+';
		while(key!='#' && key !='*' ){
			key = HKEYPAD_u8getPressedValue();
		}
		if(key=='#'){
			break;
		}else if(key=='*'){
			name[0]='\0';
			password[0]='\0';
			continue;
		}

	}
	while(password[0]== '\0'){
		HCLCD_vidClear();
		HCLCD_vidSendString("insert password");
		getData(NUMBERS,password,0,1);
	}
	status = signUpOrAddUser(name,password);
	HCLCD_vidClear();
	if(status == SIGNED){
		HCLCD_vidSendString("confirmed ");
		HCLCD_vidSendString(name);
		return true;
	}
	else if(status == NO_ROOM){
		HCLCD_vidSendString("maximum users");
		return false;
	}
}
void getData(KEYPAD_RETRIVE_VALUES type , u8*dataPtr, u8 xPosition ,u8 yPosition ){
	u8(*ptrFunction)(void) = NULL;
	u8 key= 0;
	u8 i=0;
	u8 max;
	HCLCD_vidGoTo(xPosition,yPosition);
	switch(type){
		case NUMBERS :
			ptrFunction = HKEYPAD_u8getPressedValue;
			max = MAXIMUM_PASSWORD_SIZE;
			break;
		case CHARACTERS :
			ptrFunction = HKEYPAD_u8getCharecterValue;
			max = MAXIMUM_USERNAME_SIZE;
			break;
		default:
			break;
	}
	while (key != '#'){
		key = ptrFunction();
		if(key!='+'){
			if(key == '*'){
				if(i!=0){
					i--;
					HCLCD_vidGoTo((xPosition+i),yPosition);
					HCLCD_vidSendData('\b');
					HCLCD_vidGoTo((xPosition+i),yPosition);
				}
			}else if(key=='#'){
				break;
			}else{
				if(i == max){
					break;
				}
				dataPtr[i] = key;
				HCLCD_vidSendData(dataPtr[i]);
				if(type == NUMBERS){
					_delay_ms(30);
					HCLCD_vidGoTo((xPosition+i),yPosition);
					HCLCD_vidSendData('*');
				}
				i++;
			}
		}
	}
	dataPtr[i] = '\0';
}
void displayMessage(u8*message,u8 xPosition){
	HCLCD_vidGoTo(3,0);
	HCLCD_vidSendString("smart home");
	HCLCD_vidGoTo(xPosition,1);
	HCLCD_vidSendString(message);
}
void logOut(void){
	HCLCD_vidClear();
	displayMessage("# to login",3);
}
