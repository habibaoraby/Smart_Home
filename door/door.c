/*
 * door.c
 *
 *  Created on: 9/9/2023
 *      Author: Habiba Oraby
 */
#include "../../LIB/math/datatypes.h"
#include "../../HAL/steppermotor/steppermotor.h"
#include "./door.h"
void enableDoor(){
	MOTOR_Init();
}
void openDoor(){
	MOTOR_CW();
}
void closeDoor(){
	MOTOR_CCW();
}
