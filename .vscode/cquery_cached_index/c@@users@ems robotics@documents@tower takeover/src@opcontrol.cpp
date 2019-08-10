#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_front(1);
	pros::Motor right_front(2);
	pros::Motor left_back(3);
	pros::Motor right_back(4);
	pros::Motor dr4b_left(5);
	pros::Motor dr4b_right(6);
	pros::Motor claw_pivot(7);
	pros::Motor claw(8);
	int tower = 0;
	int mtr1 = 0;

	while (true) {
		mtr1 = master.get_analog(ANALOG_LEFT_Y);
		int mtr2 = master.get_analog(ANALOG_RIGHT_Y);
		int mtr3 = master.get_analog(ANALOG_LEFT_Y);
		int mtr4 = master.get_analog(ANALOG_RIGHT_Y);

		if(master.get_digital(DIGITAL_R1) == 1){
			dr4b_left = 127;
			dr4b_right = -217;
		} else if(master.get_digital(DIGITAL_R2) == 1){
			dr4b_left = -127;
			dr4b_right = 127;
		} else {
			dr4b_left = 0;
			dr4b_right = 0;
		}

		int sideways = master.get_analog(ANALOG_RIGHT_X)+master.get_analog(ANALOG_RIGHT_X);
		sideways = sideways/2;

		mtr1 -= sideways;
		mtr3 += sideways;
		mtr2 = mtr2 + sideways;
		mtr4 = mtr4 - sideways;
		mtr1 = mtr1/-1;
		mtr4 = mtr4/-1;


		left_front.move(mtr1); // = mtr1;
		right_front = mtr2;
		left_back = mtr3;
		right_back = mtr4;

		pros::delay(20);
	}
}
