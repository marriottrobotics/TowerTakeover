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
  Motor dr4b_left(15, torque_p);
  Motor dr4b_right(12, torque_n);
  Motor claw_pivot(17,torque_p);
  Motor claw(14, torque_p);
  claw_pivot.set_brake_mode(MOTOR_BRAKE_BRAKE);
  claw.set_brake_mode(MOTOR_BRAKE_BRAKE);

  if(1 == 2){
    while(true){
      //start of Override

      cout << "left: " << light_l.get_value() << "\n";

      //end of Override
    }
  }

  if(s_pos == true){
    //Top Auton
    claw_rot(1);
    dr4b_left.move_absolute(130, 200);
    dr4b_right.move_absolute(130, 200);
    m_delay(400);
    claw_rot(0);
    m_delay(300);
    m_move_degrees(240, 50);
    dr4b_left.move_absolute(0, 50);
    dr4b_right.move_absolute(0, 50);
    m_delay(400);
    claw.move_absolute(70, 200);
    m_delay(400);
    dr4b_left.move_absolute(130, 200);
    dr4b_right.move_absolute(130, 200);
    m_delay(500);
    m_move_sin(180, 80, 60);
    m_turn_up(580, 100);
    dr4b_left.move_absolute(0, 30);
    dr4b_right.move_absolute(0, 30);
    m_delay(700);
    claw.move_absolute(-10, 200);
    m_delay(300);
    dr4b_left.move_absolute(90, 100);
    dr4b_right.move_absolute(90, 100);
    m_delay(300);
    m_move_sin(395, 100, 200);
    m_delay(300);
    dr4b_left.move_absolute(0, 100);
    dr4b_right.move_absolute(0, 100);
    m_delay(600);
    claw.move_absolute(70, 200);
    m_delay(400);
    dr4b_left.move_absolute(100, 100);
    dr4b_right.move_absolute(100, 100);
    m_delay(400);
    claw_rot(1);
    m_move_sin(180, 100, 70);
    m_turn_up(300, 100);
    m_move_sin(400, 150, 100);
    m_delay(400);
    dr4b_left.move_absolute(0, 30);
    dr4b_right.move_absolute(0, 30);
    m_delay(700);
    claw.move_absolute(-10, 100);
    m_delay(700);
    m_move_sin(-100, 60, 70);
    //Skills

/*    m_turn_up(-840, 100);
    m_slide_up(-400, 100);
    m_delay(200);
    claw_rot(1);
    dr4b_left.move_absolute(60, 100);
    dr4b_right.move_absolute(60, 100);
    m_move_sin(400, 100, 250);
    dr4b_left.move_absolute(0, 30);
    dr4b_right.move_absolute(0, 30);
    claw.move_absolute(70, 100);
    m_delay(100);
    dr4b_left.move_absolute(140, 100);
    dr4b_right.move_absolute(140, 100);
    m_move_sin(-100, 75, 75);
    m_delay(300);
    m_move_sin(200, 75, 100);
    claw.move_absolute(-10, 100);

    m_slide_up(600, 100);
    m_move_sin(-100, 75, 75);
    dr4b_left.move_absolute(0, 30);
    dr4b_right.move_absolute(0, 30);
    m_delay(500);
    claw.move_absolute(70, 100);
    m_delay(200);
    dr4b_left.move_absolute(140, 100);
    dr4b_right.move_absolute(140, 100);
    m_delay(400);
    m_move_sin(100, 75, 75);
    claw.move_absolute(-10, 100);

    m_slide_up(-600, 100);
    m_move_sin(-100, 75, 75);
    dr4b_left.move_absolute(0, 30);
    dr4b_right.move_absolute(0, 30);
    m_delay(500);
    claw.move_absolute(70, 100);
    m_delay(200);
    dr4b_left.move_absolute(140, 100);
    dr4b_right.move_absolute(140, 100);
    m_delay(400);
    m_move_sin(100, 75, 75);
    claw.move_absolute(-10, 100);
*/

  } else {
    //Bottom Auton
    claw_rot(1);
    m_delay(500);
    m_move_sin(200, 100, 50);
    dr4b_left.move_absolute(90, 200);
    dr4b_right.move_absolute(90, 200);
    m_delay(500);
    m_move_sin(310, 125, 80);
    claw_rot(0);
    m_delay(500);
    dr4b_left.move_absolute(0, 200);
    dr4b_right.move_absolute(0, 200);
    m_delay(500);
    claw.move_absolute(70, 200);
    m_delay(100);
    dr4b_left.move_absolute(90, 200);
    dr4b_right.move_absolute(90, 200);
    claw_rot(1);
    m_delay(800);
    if(s_pos == true){
    m_turn_up(-840, 100);
  } else {
    m_turn_up(-880, 100);
  }
    m_delay(100);
    m_move_sin(630, 100, 200);
    m_delay(200);
    left_front.move_velocity(60);
    right_front.move_velocity(60);
    m_delay(700);
    left_front.move_velocity(0);
    right_front.move_velocity(0);
    m_delay(100);
    dr4b_left.move_absolute(0, 200);
    dr4b_right.move_absolute(0, 200);
    m_delay(1000);
    claw.move_absolute(-10, 200);
    m_move_sin(-200, 100, 20);
    m_delay(3000);
  }
}
