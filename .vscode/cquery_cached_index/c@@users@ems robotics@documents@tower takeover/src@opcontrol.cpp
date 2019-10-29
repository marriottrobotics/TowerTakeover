#include "main.h"
#include <string>
#include <stdio.h>

string fileName;
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

	pros::ADIAnalogIn sensor (1);

	Controller master(CONTROLLER_MASTER);
	Motor left_front(1, mtr_s_n);
	Motor right_front(10, mtr_s_p);
	Motor left_back(11, mtr_s_p);
	Motor right_back(20, mtr_s_n);
	Motor dr4b_left(12, torque_p);
	Motor dr4b_right(15, torque_n);
	Motor claw_right(17,torque_p);
  Motor claw_left(14, torque_n);

	claw_right.set_brake_mode(MOTOR_BRAKE_HOLD);
	claw_left.set_brake_mode(MOTOR_BRAKE_HOLD);
	dr4b_left.set_brake_mode(MOTOR_BRAKE_HOLD);
	dr4b_right.set_brake_mode(MOTOR_BRAKE_HOLD);

	int tower = 0;
	int mtr1 = 0;
	int mtr2 = 0;
	int mtr3 = 0;
	int mtr4 = 0;
  int sideways;

	int perSecondExe = 0;
	int secondsInGame = 0;
	double f_initBatteryLvl = battery::get_capacity();
	double f_controllerBattery = master.get_battery_capacity();

	std::uint32_t now = pros::millis();

FILE *fp;
fp = fopen("/usd/run.csv", "a");
initFile(fp, f_initBatteryLvl, f_controllerBattery);

	bool clawpos = false;
	bool clawrot = true;
	bool R1slime = false;
	bool R2slime = false;
	bool Upslime = false;

	float speed = 1;
	float slowfactor = 320;

	float left_velocity = 0;
	float right_velocity = 0;
	float f_joy = 0;
	float right_joy = 0;
	int gate_fact = 20;
	float turn_fact;

	float joyfact = 5;
	float lerp = 30;

//control loop
	while (true) {

		//speed mode
		if(master.get_digital(DIGITAL_A) == 1){
			speed = 1;
		}else
		if(master.get_digital(DIGITAL_B) == 1){
			speed = 2;
	  }

		//lift carriage ver 1
				//check lift button
		if(master.get_digital(DIGITAL_L1) == 1){
			if(dr4b_left.get_position() < 640){
				dr4b_left.move_velocity(100);
			}
			else{
				dr4b_left.move_velocity(0);
			}
			if(dr4b_right.get_position() < 640){
				dr4b_right.move_velocity(100);
			}
			else{dr4b_right.move_velocity(0);
			}
		}
		//lower carriage
		else if(master.get_digital(DIGITAL_L2) == 1){
			if(dr4b_left.get_position() > 0){
				dr4b_left.move_velocity(-75);
			}
			else{
				dr4b_left.move_velocity(0);
			}

			if(dr4b_right.get_position() > 0){
				dr4b_right.move_velocity(-75);
			}
			else{
				dr4b_right.move_velocity(0);
			}

		}
		else{
			//dr4b_left.move_velocity(0);
			//dr4b_right.move_velocity(0);
			if(abs(dr4b_left.get_position() - dr4b_right.get_position()) > 0.5){
			float newpos = (dr4b_left.get_position() + dr4b_right.get_position()) / 2;
			dr4b_left.move_absolute(newpos, 30);
			dr4b_right.move_absolute(newpos, 30);


			}
		}
		//pivot claw

/*
		if(master.get_digital(DIGITAL_R1) == 1){
			if(R2slime == false){
				R2slime = true;
				if(clawrot == false){
					clawrot = true;
				}
				else if(clawrot == true){
					clawrot = false;
				}
			}
		}
		else{
			R2slime = false;
		}

		claw_pivot.get_position();
		if(clawrot == true){
			if(abs(sensor.get_value() - 1900) > 10){
				if(sensor.get_value() > 1900){
					claw_pivot.move_velocity(abs(sensor.get_value() - 1900)/lerp);
				}
				else{
					claw_pivot.move_velocity(-abs(sensor.get_value() - 1900)/lerp);
				}
			}
			else{
				claw_pivot.move_velocity(0);
			}
		}
		else{
			if(abs(sensor.get_value() - 300) > 10){
				if(sensor.get_value() < 300){
					claw_pivot.move_velocity(-abs(sensor.get_value() - 300)/lerp);
				}
				else{
					claw_pivot.move_velocity(abs(sensor.get_value() - 300)/lerp);
				}
	 		}
			else{
				claw_pivot.move_velocity(0);
			}
		}

//		cout << "motor_position: " << dr4b_left.get_position() << "\n";
//		cout << "motor_position: " << dr4b_right.get_position() << "\n";
		//claw stuff
		if(master.get_digital(DIGITAL_R2) == 1){
			if(R1slime == false){
				R1slime = true;
				if(clawpos == false){
					clawpos = true;
					claw.move_absolute(60, 200);
				}
				else if(clawpos == true){
					clawpos = false;
					claw.move_absolute(-10, 200);
				}
			}
		}
		else{
			R1slime = false;
		}

		if(master.get_digital(DIGITAL_UP) == 1){
			if(Upslime == false){
				Upslime = true;
			}
		}
		if(Upslime == true){
			clawpos = false;
			claw.move_absolute(-10, 200);
		}*/



		#define ANALOG_SENSOR_PORT 1

		if(master.get_digital(DIGITAL_R1) == 1){
			claw_right.move_velocity(100);
			claw_left.move_velocity(100);
		} else if(master.get_digital(DIGITAL_R2) == 1){
			claw_right.move_velocity(-100);
			claw_left.move_velocity(-100);
		} else {
			claw_right.move_velocity(0);
			claw_left.move_velocity(0);
		}

		if(master.get_digital(DIGITAL_UP) == 1){
			dr4b_left.move_velocity(25);
			dr4b_right.move_velocity(25);

			claw_left.move_velocity(-100);
			claw_right.move_velocity(-100);
		} else if(master.get_digital(DIGITAL_DOWN) == 1){
			dr4b_left.move_velocity(-100);
			dr4b_right.move_velocity(-100);

			claw_left.move_velocity(60);
			claw_right.move_velocity(60);
		} else {

		}






		//drive stuff
		if(abs(master.get_analog(ANALOG_RIGHT_Y)) > gate_fact){
		if(master.get_analog(ANALOG_RIGHT_Y) > f_joy){
			f_joy += joyfact;
		} else if(master.get_analog(ANALOG_RIGHT_Y) < f_joy){
			f_joy -= joyfact;
		}
	} else{
		if(f_joy > 0){
			f_joy -= joyfact;
		} else if(f_joy < 0){
			f_joy += joyfact;
		} else{}
	}


		right_velocity = 1.5784 * f_joy;
		left_velocity = 1.5748 * f_joy;
		turn_fact = 1.1 * master.get_analog(ANALOG_LEFT_X);

		right_velocity -= turn_fact;
		left_velocity += turn_fact;

		if(right_velocity > 200){
			right_velocity = 200;
		} else if(right_velocity < -200){
			right_velocity = -200;
		}

		if(left_velocity > 200){
			left_velocity = 200;
		} else if(left_velocity < -200){
			left_velocity = -200;
		}


		right_velocity = ((abs(right_velocity)/right_velocity) * (100 * sin((1/63.6619) * right_velocity - 1.5707) + 100));
		left_velocity = ((abs(left_velocity)/left_velocity) * (100 * sin((1/63.6619) * left_velocity - 1.5707) + 100));


		int left = left_velocity  / (1 + (dr4b_left.get_position()) / slowfactor) / speed;
		int right = right_velocity  / (1 + (dr4b_left.get_position()) / slowfactor) / speed;
		cout << "left: " << left_velocity << "\n";
		cout << "right: " << right_velocity << "\n";

		mtr1 = left;
		mtr2 = right;
		mtr3 = left;
		mtr4 = right;

		if(abs(master.get_analog(ANALOG_RIGHT_X)) > gate_fact){
		  sideways = (master.get_analog(ANALOG_RIGHT_X));
			sideways *= -1.5748 / (1 + (dr4b_left.get_position()) / slowfactor) / speed;
		} else {
			sideways = 0;
		}

		mtr1 -= sideways;
		mtr3 += sideways;
		mtr2 += sideways;
		mtr4 -= sideways;



		left_front.move_velocity(mtr1);
		right_front.move_velocity(mtr2);
		left_back.move_velocity(mtr3);
		right_back.move_velocity(mtr4);

		perSecondExe += 1;
		if(perSecondExe == 10){
			perSecondExe = 0;
			secondsInGame += 1;
			//executes every second
			fp = fopen("/usd/run.csv", "a");

			//Motor 1 Start
			fprintf(fp, "%d", secondsInGame);
			fprintf(fp, "|LeftFront");
			fprintf(fp, "|%lf", left_front.get_power());
			fprintf(fp, "|%d", left_front.get_voltage());
			fprintf(fp, "|%d", left_front.get_current_draw());
			fprintf(fp, "|%lf", left_front.get_temperature());
			fprintf(fp, "|%lf", left_front.get_position());
			fprintf(fp, "|%lf", left_front.get_actual_velocity());
			//Motor 2 Start
			fprintf(fp, "|Right Front");
			fprintf(fp, "|%lf", right_front.get_power());
			fprintf(fp, "|%d", right_front.get_voltage());
			fprintf(fp, "|%d", right_front.get_current_draw());
			fprintf(fp, "|%lf", right_front.get_temperature());
			fprintf(fp, "|%lf", right_front.get_position());
			fprintf(fp, "|%lf", right_front.get_actual_velocity());
			//Motor 3 Start
			fprintf(fp, "|Left Back");
			fprintf(fp, "|%lf", left_back.get_power());
			fprintf(fp, "|%d", left_back.get_voltage());
			fprintf(fp, "|%d", left_back.get_current_draw());
			fprintf(fp, "|%lf", left_back.get_temperature());
			fprintf(fp, "|%lf", left_back.get_position());
			fprintf(fp, "|%lf", left_back.get_actual_velocity());
			//Motor 4 Start
			fprintf(fp, "|Right Back");
			fprintf(fp, "|%lf", right_back.get_power());
			fprintf(fp, "|%d", right_back.get_voltage());
			fprintf(fp, "|%d", right_back.get_current_draw());
			fprintf(fp, "|%lf", right_back.get_temperature());
			fprintf(fp, "|%lf", right_back.get_position());
			fprintf(fp, "|%lf", right_back.get_actual_velocity());

			fprintf(fp, "|DR4B Left");
			fprintf(fp, "|%lf", dr4b_left.get_power());
			fprintf(fp, "|%d", dr4b_left.get_voltage());
			fprintf(fp, "|%d", dr4b_left.get_current_draw());
			fprintf(fp, "|%lf", dr4b_left.get_temperature());
			fprintf(fp, "|%lf", dr4b_left.get_position());
			fprintf(fp, "|%lf", dr4b_left.get_actual_velocity());

			fprintf(fp, "|DR4B Right");
			fprintf(fp, "|%lf", dr4b_right.get_power());
			fprintf(fp, "|%d", dr4b_right.get_voltage());
			fprintf(fp, "|%d", dr4b_right.get_current_draw());
			fprintf(fp, "|%lf", dr4b_right.get_temperature());
			fprintf(fp, "|%lf", dr4b_right.get_position());
			fprintf(fp, "|%lf", dr4b_right.get_actual_velocity());
/*
			fprintf(fp, "|Claw Rotate");
			fprintf(fp, "|%lf", claw_pivot.get_power());
			fprintf(fp, "|%d", claw_pivot.get_voltage());
			fprintf(fp, "|%d", claw_pivot.get_current_draw());
			fprintf(fp, "|%lf", claw_pivot.get_temperature());
			fprintf(fp, "|%lf", claw_pivot.get_position());
			fprintf(fp, "|%lf", claw_pivot.get_actual_velocity());

			fprintf(fp, "|Claw");
			fprintf(fp, "|%lf", claw.get_power());
			fprintf(fp, "|%d", claw.get_voltage());
			fprintf(fp, "|%d", claw.get_current_draw());
			fprintf(fp, "|%lf", claw.get_temperature());
			fprintf(fp, "|%lf", claw.get_position());
			fprintf(fp, "|%lf", claw.get_actual_velocity());
*/
			fprintf(fp, "\r");
			fclose(fp);
		}
		pros::delay(20);




	}
}

void initFile(FILE *fp, double battery, double ctrbat){
	fprintf(fp, "\r\rDriver Control Started\r");
	fprintf(fp, "Robot Battery Level|");
	fprintf(fp, "%lf", battery);
	fprintf(fp, "||Controller Battery Level");
	fprintf(fp, "|%lf", ctrbat);
	fprintf(fp, "\r \r");
	fprintf(fp, "Seconds In Driver");
	fprintf(fp, "|Motor 1");
	fprintf(fp, "|Power");
	fprintf(fp, "|Voltage");
	fprintf(fp, "|Current");
	fprintf(fp, "|Temperature");
	fprintf(fp, "|Position");
	fprintf(fp, "|Actual Velocity");

	fprintf(fp, "|Motor 2");
	fprintf(fp, "|Power");
	fprintf(fp, "|Voltage");
	fprintf(fp, "|Current");
	fprintf(fp, "|Temperature");
	fprintf(fp, "|Position");
	fprintf(fp, "|Actual Velocity");

	fprintf(fp, "|Motor 3");
	fprintf(fp, "|Power");
	fprintf(fp, "|Voltage");
	fprintf(fp, "|Current");
	fprintf(fp, "|Temperature");
	fprintf(fp, "|Position");
	fprintf(fp, "|Actual Velocity");

	fprintf(fp, "|Motor 4");
	fprintf(fp, "|Power");
	fprintf(fp, "|Voltage");
	fprintf(fp, "|Current");
	fprintf(fp, "|Temperature");
	fprintf(fp, "|Position");
	fprintf(fp, "|Actual Velocity");

	fprintf(fp, "|DR4B left");
	fprintf(fp, "|Power");
	fprintf(fp, "|Voltage");
	fprintf(fp, "|Current");
	fprintf(fp, "|Temperature");
	fprintf(fp, "|Position");
	fprintf(fp, "|Actual Velocity");

	fprintf(fp, "|DR4b Right");
	fprintf(fp, "|Power");
	fprintf(fp, "|Voltage");
	fprintf(fp, "|Current");
	fprintf(fp, "|Temperature");
	fprintf(fp, "|Position");
	fprintf(fp, "|Actual Velocity");

	fprintf(fp, "|Claw Rotate");
	fprintf(fp, "|Power");
	fprintf(fp, "|Voltage");
	fprintf(fp, "|Current");
	fprintf(fp, "|Temperature");
	fprintf(fp, "|Position");
	fprintf(fp, "|Actual Velocity");

	fprintf(fp, "|Claw");
	fprintf(fp, "|Power");
	fprintf(fp, "|Voltage");
	fprintf(fp, "|Current");
	fprintf(fp, "|Temperature");
	fprintf(fp, "|Position");
	fprintf(fp, "|Actual Velocity");
	fprintf(fp, "\r");
	fclose(fp);
}
