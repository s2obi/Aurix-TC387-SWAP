#ifndef USERSW_INC_PWM_H_
#define USERSW_INC_PWM_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxGtm_Tom_Pwm.h"

/*********************************************************************************************************************/
/*-----------------------------------------------Function Prototypes-------------------------------------------------*/
/*********************************************************************************************************************/
void initGtmTomPwm(uint32 dutyCycle);
void startGtmTomPwm(void);
void stopGtmTomPwm(void);

#endif /* USERSW_INC_PWM_H_ */
