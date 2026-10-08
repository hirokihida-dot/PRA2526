#include <iostream>
#include "RoboticArm.h"

class RoboticArm(){
	private:
		double x;
		double y;
		double z;
		bool sujetando;
	public:
		RoboticArm();
		double readx();
		double read();
		double readz();
		void grab();
		void release();
		void move (double x, double y, double z);
