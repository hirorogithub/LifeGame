#include "god.h"
#include "tools.h"
God::God()
{

}

/*init the world*/
void God::initWorld()
{
	for (int i = 0; i < MAP_X; i++){
		for (int j = 0; j < MAP_Y; j++){			
			c_map[i][j].setCreature(i,j,this);
			saveLog(i, j, c_map[i][j].Getlifelevel());
			map[i].push_back( j);
		}
	}

	lockForRun = false;
	life_num = 0;
	alive = 0;
	year = 0;


}

/*creat num  Lv1 creature*/
void God::createLv1(int num)
{
	int tx,ty ;

	for (int i = 0; i < num; i++){
	
		tx = ran_f_t(0, MAP_X);
		if (!isFull()){

			tx = ran_f_t(0, MAP_X);
			while (map[tx].empty())
				tx=((tx+1)%MAP_X);
			ty = ran_f_t(0, map[tx].size());
			c_map[tx][map[tx].at(ty)].setLife(1);
			map[tx].erase(map[tx].begin() + ty);
			alive++;

		}
		else
			return;

	}

}


//capture a position ,from (x1,y1) to(x2,y2)
void God::capture_f_t(int x1, int y1, int x2, int y2)
{
	erasexy(x2, y2);
	map[x1].push_back(y1);


	creature temp_c = c_map[x2][y2];
	c_map[x2][y2] = c_map[x1][y1];
	c_map[x1][y1] = temp_c;

	c_map[x1][y1].Setx(x1);
	c_map[x1][y1].Sety(y1);

	c_map[x2][y2].Setx(x2);
	c_map[x2][y2].Sety(y2);

	saveLog(x1, y1, c_map[x1][y1].Getlifelevel());
	saveLog(x2, y2, c_map[x2][y2].Getlifelevel());
}

int God::getNewId()
{
	return life_num++;
}

/*save the change log for gui to change*/
void God::saveLog(int x, int y,int lv/*, QColor color*/)
{
	pointForPaint temp = { x, y,lv/*, color */};
	log.push_back(temp);
}

//judge if the world is full of creatures
bool God::isFull(){

	if (MAP_SIZE - alive)
		return false;
	else
		return true;
}

/*get the index of val in vector::map[x],val must be valid!*/
int  God::getIndex(int x,int val){

	for (int i = 0; i < map[x].size(); i++){
		if (map[x][i] == val)
			return i;
	}
		
	return -1;
}

/*use vector::erase() and getIndex() to erase the (x,y) in free map*/
void God::erasexy(int x, int y){
	map[x].erase(map[x].begin() + getIndex(x, y));
}

