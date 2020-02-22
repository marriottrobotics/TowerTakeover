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
  ADIAnalogIn auto_select (1);
  ADIAnalogIn line_r(3);
  ADIDigitalIn score_bttn(2);
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
  bool rot_pos = true;
  bool pivot_closed = false;

  if(1 == 2){
    while(true){
      //start of Override


      //end of Override
    }
  }
  if(s_pos == false){
    //Bottom
    bool auto_run = true;

    intake(-100);
    delay(500);
    intake(50);
    pivot(true);
    delay(1500);
    intake(0);
    tray_up(false);
    delay(100);
    //close jaws
    //rot_loader.move_relative(25, 100);
    //rot_pos = true;
    m_turn_up(20, 75);
    m_slide_up(-300, 75);
    m_turn_up(480, 110);
    intake(100);
    move_cm(15, 100, 10);
    intake(100);
    m_move_degrees(750, 40);
    delay(200);
    intake(0);
    move_cm(-52, 150, 40);

    m_turn_up(-710, 125);
    move_cm(40, 150, 30);
    intake(-30);
    tray_up(true);
    delay(2000);
    pivot(false);
    tray_up(false);
    delay(1000);
    intake(0);
    move_cm(-20, 17, 150);

  } else { //================================================================================================================
    bool auto_run = true;
    rot_loader.move_relative(25, 100);
    intake(-100);
    delay(500);
    intake(30);
    delay(1500);
    intake(0);
    tray_up(false);
    delay(3000);
    move_cm(-40, 100, 35);
    delay(100);
    move_cm(40, 100, 35);



  }
}
