#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <time.h>
#include <math.h>
#include <stdlib.h>


#define LEVEL_UP_K      2

#define NUM_STATU       9
#define LIFE_LEVEL      0
#define MAX_ENERGY      1
#define MOVE            2
#define STEP            3
#define DEATH           4
#define VISION          5
#define MUTATION        6
#define M_SIZE          7
#define M_LOGIC         8



#define NUM_ACTIVITIES  4
#define ACTIVITY_MOVE   0
#define ACTIVITY_EAT    1
#define ACTIVITY_SLEEP  2
#define ACTIVITY_BURN   3
#define MAX_LEVEL       5

/*map message ,will be input by file in the future version*/
#define MAP_X			100
#define MAP_Y			100
#define MAP_SIZE	10000

/*base rate and constant for the world to run*/
#define CHANGE_RATE     0.05
#define DIE_K           5			//base  num for a creature to reduce energy every step
#define COST_RATE       0.5	//energy cost rate ,eat a creature can only get COST_RATE*be_eated.energy
#define BASE_ENERGY     20//base energy for the LV1
#define SUN             200		//used as the energy input for this world,
#define CAN_BURN			1.8//creture must have CAN_BURN*max_energy so that both mother and baby can alive after burn
#define AGE_K			2

#define toX(a)          (int)(a/MAP_Y)
#define toY(a)          (int)(a%MAP_Y)


typedef struct {
public:
	int x;
	int y;
	int lv;
	//QColor color;

}pointForPaint;



/*
void  out_log(string s1,creature obj){
cout<<"G:"<<year<<" ID:"<<obj.id<<"`s"<<s1<<"has changed!"<<endl;
cout<<"lifelevel:"<<obj.Getlifelevel()<<endl;
cout<<"MAX/energy:"<<obj.Getmax_energy<<" / "<<obj.Getenergy()<<endl;
cout<<"step:"<<obj.Getstep()<<endl;
cout<<"death:"<<obj.Getdeath()<<endl;
cout<<"visiob:"<<obj.Getvision()<<endl;
cout<<"mem:{"<<endl;
cout<<"m_size"<<obj.Getm_size()<<endl;
cout<<"m_logic"<<obj.Getm_logic()<<endl;
return 0;
}*/


bool ran_tf(double rate);
int ran_f_t(int from, int to);
double dran_f_t(double from, double to);






#endif // TOOLS_H_INCLUDED
