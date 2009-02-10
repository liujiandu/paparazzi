#ifndef ACTUATORS_ASCTEC_TWI_BLMC_H
#define ACTUATORS_ASCTEC_TWI_BLMC_H

#include "std.h"
#include "led.h"

#include "airframe.h"

extern void asctec_twi_controller_send(void);

extern uint8_t twi_blmc_nb_err;
extern int8_t asctec_twi_blmc_motor_power[];

#define MB_TWI_CONTROLLER_COMMAND_NONE     0
#define MB_TWI_CONTROLLER_COMMAND_TEST     1
#define MB_TWI_CONTROLLER_COMMAND_REVERSE  2
#define MB_TWI_CONTROLLER_COMMAND_SET_ADDR 3


extern uint8_t actuators_asctec_twi_blmc_command;
extern uint8_t actuators_asctec_twi_blmc_addr;
extern uint8_t actuators_asctec_twi_blmc_new_addr;

#define actuators_asctec_twi_blmc_hw_SetCommand(value) { \
    actuators_asctec_twi_blmc_command = value;		 \
  }

#define actuators_asctec_twi_blmc_hw_SetAddr(value) {			\
    actuators_asctec_twi_blmc_command = MB_TWI_CONTROLLER_COMMAND_SET_ADDR; \
    actuators_asctec_twi_blmc_new_addr = value;				\
  }

#ifndef SetActuatorsFromCommands
#ifdef KILL_MOTORS
#define SetActuatorsFromCommands(_motors_on) {		      \
    Actuator(SERVO_PITCH)  = 0;				      \
    Actuator(SERVO_ROLL)   = 0;				      \
    Actuator(SERVO_YAW)    = 0;				      \
    Actuator(SERVO_THRUST) = 0;				      \
    ActuatorsCommit();					      \
  }
#else
#define SetActuatorsFromCommands(_motors_on) {				\
    Bound(booz2_commands[COMMAND_PITCH],-100, 100);			\
    Bound(booz2_commands[COMMAND_ROLL], -100, 100);			\
    Bound(booz2_commands[COMMAND_YAW],  -100, 100);			\
    if (_motors_on) {							\
      Bound(booz2_commands[COMMAND_THRUST],  1, 200);			\
    }									\
    Actuator(SERVO_PITCH)  = -(uint8_t)booz2_commands[COMMAND_PITCH];	\
    Actuator(SERVO_ROLL)   =  (uint8_t)booz2_commands[COMMAND_ROLL];	\
    Actuator(SERVO_YAW)    = -(uint8_t)booz2_commands[COMMAND_YAW];	\
    Actuator(SERVO_THRUST) =  (uint8_t)booz2_commands[COMMAND_THRUST];	\
    ActuatorsCommit();							\
  }
#endif /* KILL_MOTORS              */
#endif /* SetActuatorsFromCommands */

#define Actuator(i) asctec_twi_blmc_motor_power[i]
#define ActuatorsCommit() {			                \
    asctec_twi_controller_send();				\
  }

#endif /* ACTUATORS_ASCTEC_TWI_BLMC_H */
