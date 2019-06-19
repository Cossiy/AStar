
/* A*”Œœ∑¿‡ */
#ifndef _GAME_
#define _GAME_

#include <vector>
#include <string>
#include "Station.h"

class Game{
public:
	Game(short, short);
	~Game();
	void setStartAndEndPoint(short, short, short, short);
	void addWallPoint(short, short);
	short getMapWidth();
	short getMapHeight();
	void addOpenStation(int, int, Station*);
	void addCloseStation(Station*);
	std::string getStringMap();
	bool isCatchEndPoint();
	bool isNoWay();
	void openStation();
private:
	short mapWidth;
	short mapHeight;
	std::vector<Point*> wall;
	Point src;
	Point dst;
	std::vector<Station*> openArr;
	std::vector<Station*> closeArr;
};

#endif // _GAME_