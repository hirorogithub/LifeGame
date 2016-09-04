#include "god.h"
#include "tools.h"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
creature::creature()
{
}

/*set base message for creature in (x,y)*/
void creature::setCreature(int x, int y, God* hiro)
{
	
	lifelevel = 0;
	id = 0;
	age = 0;
	energy = 0;
	max_energy = 0;
	move = 0;
	step = 0;
	death = 0;
	vision = 0;
	this->x = x;
	this->y = y;
	mutation = 0;
	m_size = 0;
	m_logic = 0;
	m_activities_cnt[0] =
		m_activities_cnt[1] =
		m_activities_cnt[2] =
		m_activities_cnt[3] = 0;
	this->hiro = hiro;

}

creature::~creature()
{
	//dtor
}

/* randomly find an empty position from(x,y),*/
int creature::findEmpty(int x, int y, int range)
{

	vector <int> vec;
	for (int i = x - range; i <= x + range; i++){
		for (int j = y - range; j <= y + range; j++){
			if (hiro->getIndex((i+MAP_X)%MAP_X,(j+MAP_Y)%MAP_Y)!=-1){
				vec.push_back(((i+MAP_X)%MAP_X)*MAP_Y + (j+MAP_Y)%MAP_Y);
			}
		}
	}
	if (!vec.empty())
		return vec[ran_f_t(0, vec.size())];
	else
		return -1;
}

/* randomly find an eatable creature from(x,y),*/
int creature::findEatable(int x, int y, int level, int vision)
{
	vector <int> vec;
	for (int i = x - vision; i <= x + vision; i++){
		for (int j = y - vision; j <= y + vision; j++){
			if (hiro->c_map[(i+MAP_X)%MAP_X][(j+MAP_Y)%MAP_Y].Getlifelevel()<=level&&
					!hiro->c_map[(i+MAP_X)%MAP_X][(j+MAP_Y)%MAP_Y].Getlifelevel()){
				vec.push_back(((i+MAP_X)%MAP_X)*MAP_Y + (j+MAP_Y)%MAP_Y);
			}
		}
	}
	if (!vec.empty())
		return vec[ran_f_t(0, vec.size())];
	else
		return -1;
}

/*randomly move */
void creature::activity_mov()
{
	int temp = findEmpty(this->x, this->y, this->move);
	if (temp != -1){

		int temp_y = toY(temp);
		int temp_x = toX(temp);
		hiro->capture_f_t(this->x, this->y, temp_x, temp_y);

	}
	
}

/*randomly eat*/
void creature::activity_eat(){

	int temp = findEatable(this->x,this->y,this->lifelevel,this->vision);
	if (temp != -1){
		int temp_y = toY(temp);
		int temp_x = toX(temp);
		hiro->c_map[temp_x][temp_y].kill();
		energy += COST_RATE*hiro->c_map[temp_x][temp_y].Getenergy();
		hiro->capture_f_t(this->x, this->y, temp_x, temp_y);

	}
}

/*sleep that can get little energy*/
void creature::activity_sleep()
{
	energy += this->death>>1;
}

/*bear a new creature */
void creature::activity_burn()
{
	int temp = findEmpty(this->x, this->y, this->vision);
	if (temp != -1)
	{
		int temp_y = toY(temp);
		int temp_x = toX(temp);

		hiro->c_map[temp_x][temp_y].lifelevel = this->lifelevel;
		hiro->c_map[temp_x][temp_y].id = hiro->getNewId();
		hiro->c_map[temp_x][temp_y].age = this->lifelevel*AGE_K;
		hiro->c_map[temp_x][temp_y].energy = hiro->c_map[temp_x][temp_y].max_energy = this->max_energy;
		hiro->c_map[temp_x][temp_y].move = this->move;
		hiro->c_map[temp_x][temp_y].step = this->step;
		hiro->c_map[temp_x][temp_y].death = this->death;
		hiro->c_map[temp_x][temp_y].vision = this->vision;
		hiro->c_map[temp_x][temp_y].mutation = this->mutation;
		hiro->c_map[temp_x][temp_y].m_size = this->m_size;
		hiro->c_map[temp_x][temp_y].m_logic = this->m_logic;
		hiro->saveLog(temp_x, temp_y, this->lifelevel);

		for (int i = 0; i<NUM_ACTIVITIES; i++)
			hiro->c_map[temp_x][temp_y].Setcnt(i, this->m_activities_cnt[i]);
		hiro->c_map[temp_x][temp_y].sudden_change(ACTIVITY_BURN);
		hiro->erasexy(temp_x, temp_y);
		hiro->alive++;
	}
}

/*schdule a creature `s action in every steps*/
void creature::schdule(){

	this->energy -= this->death;
	this->age--;
	if (this->energy <= 0||!this->age){
		this->kill();
		return;
	}						
	this->sudden_change();


	int s_case = this->Getmax_cnt();
	if (ran_tf(this->m_logic)){
	int temp[NUM_ACTIVITIES] = { 0, 0, 0, 0 };	
		for (int i = 0; i<NUM_ACTIVITIES; i++)
			temp[i] = ran_f_t(0, 9);
		temp[s_case] *= (m_logic + 1);
		int max = 0, maxi;
		for (int i = 0; i<NUM_ACTIVITIES; i++){
			if (max <= temp[i]){
				max = temp[i];
				maxi = i;
			}
		}
	
		s_case = maxi;
	}


	switch (s_case){

	case ACTIVITY_BURN:
		if (this->Getenergy() >= CAN_BURN*this->Getmax_energy()){
			this->energy -= this->Getmax_energy();
			this->activity_burn();
			this->Addcnt(ACTIVITY_BURN);
		}
		break;
	case ACTIVITY_SLEEP: 
		this->activity_sleep();
		this->Addcnt(ACTIVITY_SLEEP);
		break;
	case ACTIVITY_EAT:
		this->activity_eat();
		this->Addcnt(ACTIVITY_EAT);
		break;
	case ACTIVITY_MOVE:
		this->activity_mov();
		this->Addcnt(ACTIVITY_MOVE);
		break;
	default:
		break;

	}


}


/*change the creature by all kinds of rate*/
void creature::sudden_change(){
	sudden_change(~ACTIVITY_BURN);
}

void creature::sudden_change(int type){
	double rate = this->mutation;
	if (type == ACTIVITY_BURN){
		rate = this->mutation*2;
		if (rate > 0.8)rate = 0.8;
	}
	if (ran_tf(rate)){
		switch (ran_f_t(0, NUM_STATU)){
		case LIFE_LEVEL:
		{
			if (this->lifelevel<MAX_LEVEL){
				this->lifelevel++;
				this->max_energy = this->energy *= LEVEL_UP_K;
				this->age += AGE_K;
				this->step++;
				this->death += DIE_K;
				this->vision++;
				this->mutation += 0.1;
				this->m_size++;
				this->m_logic += 0.1;
				//std::cout << "No." << this->Getid() << " have level up!,from " << this->lifelevel - 1 << "to " << this->lifelevel << std::endl;
				hiro->saveLog(this->x, this->y, this->lifelevel);
			}
			break;
		}

		case MAX_ENERGY:{
			this->max_energy += ran_f_t(-(this->max_energy) / LEVEL_UP_K, this->max_energy/ LEVEL_UP_K);
			if (this->max_energy < 0)this->max_energy = 0;
			break;
		}
		case MOVE:{
			this->move += ran_f_t(-1, 1);
			if (this->move < 0)this->move = 0;
			break;
		}
		case STEP:{
			this->step += ran_f_t(-1, 1);
			if (this->step < 0)this->step = 0;
			break;
		}
		case DEATH:{
			this->death += ran_f_t(-(DIE_K / 2), DIE_K / 2);
			if (this->death < 0)this->death = 1;
			break;
		}
		case VISION:{
			this->vision += ran_f_t(-1, 1);
			if (this->vision < 0)this->vision = 0;
			break;
		}
		case MUTATION:{
			this->mutation += dran_f_t(-0.1, 0.1);
			if (this->vision)this->vision = 0;
			break;
		}
		case M_SIZE:{
			this->m_size += ran_f_t(-1, 1);
			if (this->m_size)this->m_size = 0;
			break;
		}
		case M_LOGIC:{
			this->m_logic += dran_f_t(-0.1, 0.1);
			if (this->m_logic < 0)this->m_logic = 0;
			break;
		}

		}
	}
}

/*DIE :(*/
void creature::kill()
{
	hiro->cntlv[0]++;
	//std::cout << "No." << this->Getid() <<" Lv. "<<this->Getlifelevel()<<" die" << std::endl;
	lifelevel = 0;
	hiro->alive--;
	hiro->saveLog(this->x, this->y, this->lifelevel);
	hiro->map[x].push_back(this->y);
}

/*creature a Lv=level creatures by some default data*/
void creature::setLife(int level)
{
	lifelevel = level;
	hiro->saveLog(this->x, this->y, this->lifelevel);
	id = hiro->getNewId();
	step = level;
	if (level == 1)
	{
		max_energy = energy = BASE_ENERGY;
		age = AGE_K;
		move = 0;
		death = DIE_K;
		vision = 1;
		mutation = CHANGE_RATE;
		m_size = 0;
		m_logic = 0;
		m_activities_cnt[0] = 0;
		m_activities_cnt[1] = 0;
		m_activities_cnt[2] = 0;
		m_activities_cnt[3] = 0;

	}
	else
	{
		max_energy = energy = BASE_ENERGY>>level;//pow(2,level)*base_energy
		age = AGE_K*lifelevel;
		move = level;
		death = DIE_K;
		vision = level / LEVEL_UP_K;
		mutation = CHANGE_RATE;
		m_size = level;
		m_logic = level / 10;
		m_activities_cnt[0] = 0;
		m_activities_cnt[1] = 0;
		m_activities_cnt[2] = 0;
		m_activities_cnt[3] = 0;
	}
}
