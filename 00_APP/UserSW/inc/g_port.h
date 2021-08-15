#ifndef APP_USERSW_INC_G_PORT_H_
#define APP_USERSW_INC_G_PORT_H_

#define IR_1        &MODULE_P33,12          /* IR Sensor 1 */
#define IR_2        &MODULE_P00,8           /* IR Sensor 2 */
#define IR_3        &MODULE_P00,7           /* IR Sensor 3 */
#define IR_4        &MODULE_P00,6           /* IR Sensor 4 */

#define MOTOR_1_E   &MODULE_P15,0           /* MOTOR_1_E */
#define MOTOR_2_E   &MODULE_P00,11          /* MOTOR_2_E */
#define MOTOR_3_E   &MODULE_P20,8           /* MOTOR_3_E */
#define MOTOR_4_E   &MODULE_P10,3           /* MOTOR_4_E */
#define MOTOR_1_F   &MODULE_P14,0           /* MOTOR_1_F */
#define MOTOR_2_F   &MODULE_P20,14          /* MOTOR_2_F */
#define MOTOR_3_F   &MODULE_P20,7           /* MOTOR_3_F */
#define MOTOR_4_F   &MODULE_P10,7           /* MOTOR_4_F */

#define TRIGPIN     &MODULE_P33,11          /* Ultrasonic Trigger Pin */
#define ECHOPIN     &MODULE_P33,7           /* Ultrasonic Echo Pin */

#define LED1        &MODULE_P33,4           /* LED D302: Port, Pin definition       */
#define LED2        &MODULE_P33,5           /* LED D303: Port, Pin definition       */
#define LED3        &MODULE_P33,6           /* LED D304: Port, Pin definition       */
#define LED5        &MODULE_P20,11          /* LED D306: Port, Pin definition       */
#define LED6        &MODULE_P20,12          /* LED D307: Port, Pin definition       */
#define LED7        &MODULE_P20,13          /* LED D308: Port, Pin definition       */
#define BUTTON      &MODULE_P33,11          /**/
#define WAIT_TIME   100                     /* Wait time constant in milliseconds   */

#endif /* USERSW_INC_G_PORT_H_ */
