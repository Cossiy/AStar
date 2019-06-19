
/*Õ¾µã*/
#ifndef _STATION_
#define _STATION_

#include "Point.h"

class Station{
public: 
	Station* parent;
	Point point;
	short int f;
	short int g;
	short int h;
};

#endif // _STATION_