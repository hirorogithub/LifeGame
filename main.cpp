#include <iostream>
#include "god.h"
#include <time.h>
int main()
{
	using namespace std;
	srand((int)time(0));
	God hiro;
	hiro.initWorld();
	hiro.createLv1(7500);
	for (hiro.year = 0; hiro.year<10000; hiro.year++){
		hiro.log.clear();

		/*some log*/
		hiro.cntlv[0] = 0;
		hiro.cntlv[1] = 0;
		hiro.cntlv[2] = 0;
		hiro.cntlv[3] = 0;
		hiro.cntlv[4] = 0;
		hiro.cntlv[5] = 0;


		

		hiro.createLv1(SUN);

		for (int i = 0; i<MAP_X; i++){
			for (int j = 0; j<MAP_Y; j++){
				
				if (hiro.c_map[i][j].Getlifelevel()){
					//hiro.cntlv[hiro.c_map[i][j].Getlifelevel()]++;
					for (int k = 0; k < hiro.c_map[i][j].Getstep();k++)
						hiro.c_map[i][j].schdule();
				}
			}
		}
		for (int i = 0; i < MAP_X; i++){
			for (int j = 0; j < MAP_Y; j++){
				hiro.cntlv[hiro.c_map[i][j].Getlifelevel()]++;
			}
		}


		cout << "Year\t" << hiro.year << endl;
		cout << "Alive\t" << hiro.alive << endl;
		cout << "Die\t" << hiro.cntlv[0] << endl;
		cout << "Lv1\t" << hiro.cntlv[1] << endl;
		cout << "Lv2\t" << hiro.cntlv[2] << endl;
		cout << "Lv3\t" << hiro.cntlv[3] << endl;
		cout << "Lv4\t" << hiro.cntlv[4] << endl;
		cout << "Lv5\t" << hiro.cntlv[5] << endl;

	}

	return 0;
}
