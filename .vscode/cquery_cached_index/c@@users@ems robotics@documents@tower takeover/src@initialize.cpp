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
  ADIAnalogIn auto_select (2);
  ADIAnalogIn line_r(3);
  ADIDigitalIn score_bttn(1);
  Controller master(CONTROLLER_MASTER);
	Motor left_front(1, mtr_s_p);
	Motor right_front(2, mtr_s_n);
	Motor left_back(11, mtr_s_p);
	Motor right_back(12, mtr_s_n);
  Motor loader_left(3, mtr_s_n);
  Motor loader_right(14, mtr_s_p);
  Motor score(4, torque_p);
	Motor rot_loader(8, torque_p);
  rot_loader.set_brake_mode(MOTOR_BRAKE_HOLD);
	score.set_brake_mode(MOTOR_BRAKE_HOLD);
	loader_left.set_brake_mode(MOTOR_BRAKE_BRAKE);
	loader_right.set_brake_mode(MOTOR_BRAKE_BRAKE);
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
  bool auto_run = false;
  while(true){
  ADIAnalogIn auto_select(1);
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
