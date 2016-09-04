#ifndef CREATURE_H
#define CREATURE_H

class God;
#include "tools.h"


class creature
{
public:

	creature();

	~creature();

	void create(int level);

	int Getlifelevel() { return lifelevel; }

	void Setlifelevel(int val) { lifelevel = val; }
	
	int Getid() { return id; }
	
	void Setid(int val) { id = val; }
	
	int Getenergy() { return energy; }
	
	void Setenergy(int val) { energy = val; }
	
	int Getmax_energy() { return max_energy; }
	
	void Setmax_energy(int val) { max_energy = val; }
	
	int Getmove() { return move; }
	
	void Setmove(int val) { move = val; }
	
	int Getstep() { return step; }
	
	void Setstep(int val) { step = val; }
	
	int Getdeath() { return death; }

	void Setdeath(int val) { death = val; }
	
	int Getvision() { return vision; }
	
	void Setvision(int val) { vision = val; }
	
	int Getx() { return x; }
	
	void Setx(int val) { x = val; }
	
	int Gety() { return y; }
	
	void Sety(int val) { y = val; }

	int Getage(){ return age;  }

	void Setage(int val){ age = val; }
	
	double Getmutation() { return mutation; }
	
	void Setmutation(double val) { mutation = val; }

	int Getm_size(){ return m_size; }

	void Setm_size(int val){ m_size = val; }

	int Getmax_cnt(){
		int max = 0, maxi = 0;
		for (int i = 0; i<NUM_ACTIVITIES; i++){
			if (max <= m_activities_cnt[i]){
				max = m_activities_cnt[i];
				maxi = i;
			}
		}
		return maxi;
	}

	void Addcnt(int activity_id){
		m_activities_cnt[activity_id]++;
	}

	void Setcnt(int activity_id, int cnt){
		m_activities_cnt[activity_id] = cnt;
	}
	/* Base activities*/
	void activity_mov();
	void activity_eat();
	void activity_sleep();
	void activity_burn();
	void kill();

	/*sudden change the creature`s status,which may lead to be better or worse*/
	void sudden_change(int type);
	void sudden_change();

	void schdule();

	/*some tools for other methors*/
	void setCreature(int x, int y, God* hiro);
	void setLife(int level);
	int findEmpty(int x, int y, int range);
	int findEatable(int x, int y, int level, int vision);

private:
	int lifelevel; //for 0-5,0 mean die
	int id;			//unique

	int energy;		//something just like HP
	int max_energy;	
	int age;

	int move;			//creature can go to each place in Rect[x-move,y-move,x+move,y+move] 
	int step;			//times that creature can act in an year
	int death;			//in every year,energy-=death;
	int vision;			//vision that effect eat() and burn()
	int x;					//position
	int y; 
	double mutation;		//sudden change rate
	int m_size;				//memory size ,but haven`t use yet
	double m_logic;		// a 0-1 rate to judge whether this year`s action will be effect by the memory or not 
	int m_activities_cnt[NUM_ACTIVITIES];	//count the activities times ,which means memory;
	God *hiro;			//for a creature to access the world`s status like the map,id,etc..

};


#endif // CREATURE_H
