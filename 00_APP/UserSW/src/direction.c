#include "00_APP/UserSW/inc/direction.h"
#include "00_APP/UserSW/inc/IRsensor.h"
#include "00_APP/UserSW/inc/motordriver.h"
#include "00_APP/UserSW/inc/typedef.h"
#include "00_APP/UserSW/inc/ultrasonic.h"

UINT_8 ir_val;
UINT_8 state = 1;

void line_tracer (void) {


    while (1) {
        ir_val = IR_data();
        /*
         * black line = 1
         * white line = 0
         * sensor   DEC_value   Handle Direction
         * 0000     15          No_line
         * 0001     8           hard_right
         * 0011     12          hard_right
         * 0010     4           soft_right
         *
         * 0110     6           Forward
         *
         * 1000     1           hard_left
         * 1100     3           hard_left
         * 0100     2           soft_left
         *
         **/

        switch (ir_val) {
            // 모든 센서 값 라인이 없을 경우
            case 8:
                MT_hard_left();
                break;
            case 4:
                MT_soft_left();
                break;
            case 12:
                MT_hard_left();
                break;
            case 2:
                MT_soft_right();
                break;
            case 6: // 직진
                MT_forward();
                break;
            case 1:
                MT_hard_right();
                break;
            case 3:
                MT_hard_right();
                break;
            case 0:
                ir_val = IR_data();
                if (ir_val == 6) {
                    MT_forward();
                } else if (ir_val > 0 || ir_val < 4) {
                    MT_hard_left();
                } else if (ir_val == 12 || ir_val == 4 || ir_val == 8) {
                    MT_hard_right();
                } else {
                    MT_stop();
                }
                break;
        }
    }
}
