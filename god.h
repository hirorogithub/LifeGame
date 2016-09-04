#ifndef GOD_H
#define GOD_H

#include "creature.h"
#include <vector>
/*
I am the god of my world

Code is my body&Algorithm is my blood

I have created over a thousand programes

Unknown to Death,Nor known to Life

Have with stood pain to create many applications

Yet,those hands will never hold anything

So as I pray,Unlimited Code Works

															----hiro
*/
class God
{


public:
	creature c_map[MAP_X][MAP_Y];
	bool lockForRun;//haven`t use
	int life_num;			//count how many creature have burn,which use for id
	int alive;				//count how many alive creature now
	int year;					
	std::vector<pointForPaint> log;	//for GUI output,
	std::vector<int>map[MAP_X];		//a map for free position

	int cntlv[6];

	God();
	void initWorld();	
	void createLv1(int num);		
	void capture_f_t(int x1, int y1, int x2, int y2);	//capture a position ,from (x1,y1) to(x2,y2)
	int getNewId();
	bool isFull();							//judge if the world is full of creatures
	void saveLog(int x, int y,int lv /*QColor color*/);		

	//tools for access data in vector
	int getIndex(int x,int val);		
	void erasexy(int x, int y);
};

#endif // GOD_H
