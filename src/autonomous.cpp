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
  Motor left_front(1, mtr_s_n);
  Motor right_front(10, mtr_s_p);
  Motor left_back(11, mtr_s_p);
  Motor right_back(20, mtr_s_n);
  Motor dr4b_left(12, torque_p);
  Motor dr4b_right(15, torque_n);
  Motor claw_right(17,torque_p);
  Motor claw_left(14, torque_n);

  claw_left.set_brake_mode(MOTOR_BRAKE_HOLD);
  claw_right.set_brake_mode(MOTOR_BRAKE_HOLD);
  //claw_pivot.set_brake_mode(MOTOR_BRAKE_BRAKE);
  //claw.set_brake_mode(MOTOR_BRAKE_BRAKE);

  if(1 == 2){
    while(true){
      //start of Override

      cout << "left: " << light_l.get_value() << "\n";

      //end of Override
    }
  }

  if(s_pos == true){
    //Top Auton
    claw(100);
    m_async(50, 100);
    dr4b_move(100, 100);
    delay(500);
    claw(0);
    delay(200);

    move_cm(9, 100, 5);

    delay(200);

    dr4b_move(10, 75);
    claw(100);
    delay(1000);
    claw(0);
    dr4b_move(450, 100);
    move_cm(52, 75, 30);
    dr4b_claw(60);
    claw(100);
    delay(200);
    dr4b_move(80, 100);
    delay(200);
    m_turn_up(570, 75);
    claw(0);
    move_cm(65, 75, 30);
    m_slide_up(-410, 100);
    m_turn_up(335, 100);
    move_cm(30, 100, 10);
    delay(200);
    dr4b_move(0, 30);
    delay(500);
    dr4b_claw(450);
    delay(300);
    move_cm(-20, 75, 10);


  } else { //================================================================================================================
/*
    //bottom autonomous
    claw(100);
    dr4b_move(70, 100);
    claw(0);
*/
  }
}
