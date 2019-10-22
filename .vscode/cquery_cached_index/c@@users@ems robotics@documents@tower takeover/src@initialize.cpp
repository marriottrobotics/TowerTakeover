#include "main.h"
using namespace pros;
void on_center_button() {

}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  ADIAnalogIn auto_select(2);
  Controller master(CONTROLLER_MASTER);
  Motor left_front(1, mtr_s_n);
  Motor right_front(10, mtr_s_p);
  Motor left_back(11, mtr_s_p);
  Motor right_back(20, mtr_s_n);
  Motor dr4b_left(15, torque_p);
  Motor dr4b_right(12, torque_n);
  Motor claw_pivot(17,torque_p);
  Motor claw(14, torque_p);
  left_front.set_brake_mode(MOTOR_BRAKE_COAST);
  right_front.set_brake_mode(MOTOR_BRAKE_COAST);
  left_back.set_brake_mode(MOTOR_BRAKE_COAST);
  right_back.set_brake_mode(MOTOR_BRAKE_COAST);
  dr4b_left.set_brake_mode(MOTOR_BRAKE_HOLD);
  dr4b_right.set_brake_mode(MOTOR_BRAKE_HOLD);
  claw.set_brake_mode(MOTOR_BRAKE_BRAKE);
  claw_pivot.set_brake_mode(MOTOR_BRAKE_HOLD);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  while(true){
  ADIAnalogIn auto_select(2);
  Controller master(CONTROLLER_MASTER);
  if(auto_select.get_value() < 2000){
    if(auto_select.get_value() < 1000){
      //0 - 675
      if(s_side == true && s_pos == true){
        //do nothing
      } else{
      master.set_text(0, 0, "RED TOP    ");
      s_side = true;
      s_pos = true;
      bool override = false;
    }
    }else {
      //675 - 1350
      if(s_side == true && s_pos == false){
        //do nothing
      } else{
      master.set_text(0, 0, "RED BOTTOM ");
      s_side = true;
      s_pos = false;
      bool override = false;
    }
    }
  } else if(auto_select.get_value() > 2000){
    if(auto_select.get_value() < 3000){
      //1350 - 2025
      if(s_side == false && s_pos == true){
        //do nothing
      } else{
      master.set_text(0, 0, "BLUE TOP   ");
      s_side = false;
      s_pos = true;
      bool override = false;
    }
  }else if(auto_select.get_value() < 4000){
     //2025 - 2700
     if(s_side == false && s_pos == false){
       //do nothing
     } else{
     master.set_text(0, 0, "BLUE BOTTOM");
     s_side = false;
     s_pos = false;
     bool override = false;
    }
  } else {
      if(s_side == true && s_pos == true){

      } else {
        master.set_text(0, 0, "bool override   ");
        s_side = true;
        s_pos = true;
        bool override = true;
      }
    }
  }
  delay(60);
}
}
