#include "main.h"
#include "Movements.h"

using namespace Movement;


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  pros::ADIAnalogIn sensor (1);
  ADIAnalogIn auto_select(2);
  ADIAnalogIn light_l(3);
  ADIAnalogIn light_r(4);
  Controller master(CONTROLLER_MASTER);
  Motor left_front(4, mtr_s_p);
	Motor right_front(3, mtr_s_n);
	Motor left_back(2, mtr_s_p);
	Motor right_back(1, mtr_s_n);
  Motor loader_left(7, mtr_s_n);
  Motor loader_right(8, mtr_s_p);
  Motor score(5, torque_n);
  Motor rot_loader(6, torque_n);

  rot_loader.set_brake_mode(MOTOR_BRAKE_HOLD);
	score.set_brake_mode(MOTOR_BRAKE_HOLD);
	loader_left.set_brake_mode(MOTOR_BRAKE_BRAKE);
	loader_right.set_brake_mode(MOTOR_BRAKE_BRAKE);

  if(1 == 2){
    while(true){
      //start of Override

      cout << "left: " << light_l.get_value() << "\n";

      //end of Override
    }
  }

  if(s_pos == true){
    //Top Auton


  } else { //================================================================================================================


  }
}
