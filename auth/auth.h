/*
 * auth.h
 *
 *  Created on: 9/9/2023
 *      Author: Habiba Oraby
 */

#ifndef APP_AUTH_AUTH_H_
#define APP_AUTH_AUTH_H_

#define MAXIMUM_USERNAME_SIZE		10
#define MAXIMUM_PASSWORD_SIZE		8
#define MAXIMUM_USERS				5
#define MAXIMUM_TRIES				5
#define	USER_NAME_LOCATION			0
#define USER_COUNT_LOCATION         1023
typedef enum {
	LOGGED_IN,
	INVALID_USER_NAME,
	INVALID_USER_PASSWORD
}LOGIN_STATUS;
typedef enum{
	SIGNED,
	NO_ROOM
}SIGNUP_STATUS;
typedef enum{
	NUMBERS,
	CHARACTERS
}KEYPAD_RETRIVE_VALUES;

LOGIN_STATUS detectLoginData(u8*name , u8*password);
SIGNUP_STATUS signUpOrAddUser(u8*name, u8*password);
void loginExecute(u8*name , u8*password);
boolean	signUpExecute(u8*name, u8*password);
void logOut(void);
void getData(KEYPAD_RETRIVE_VALUES type, u8*dataPtr, u8 xPosition, u8 yPosition);
void displayMessage(u8*message,u8 xPosition);
#endif /* APP_AUTH_AUTH_H_ */
