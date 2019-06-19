
/* A*��Ϸ�� */
#include "Game.h"

Game::Game(short mapWidth, short mapHeight){
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
}

Game::~Game(void){
	for(std::vector<Point*>::iterator iter = wall.begin(); iter != wall.end(); iter++){
		delete (*iter);
	}
	for(std::vector<Station*>::iterator iter = openArr.begin(); iter != openArr.end(); iter++){
		delete (*iter);
	}
	for(std::vector<Station*>::iterator iter = closeArr.begin(); iter != closeArr.end(); iter++){
		delete (*iter);
	}
}

// ���������յ�
void Game::setStartAndEndPoint(short start_x, short start_y, short end_x, short end_y){
	this->dst.x = end_x;
	this->dst.y = end_y;
	this->src.x = start_x;
	this->src.y = start_y;

	// Ĭ��װ����㵽����Ѱ�ڵ���
	this->openArr.clear();
	this->addOpenStation(start_x, start_y, NULL);
}

// ����ϰ���
void Game::addWallPoint(short x, short y){
	Point* newOne = new Point(x, y);
	this->wall.push_back(newOne);
}

// ��ͼ��
short Game::getMapWidth(void){
	return mapWidth;
}

// ��ͼ��
short Game::getMapHeight(void){
	return mapHeight;
}

// ��ӿ���Ѱվ��
void Game::addOpenStation(int x, int y, Station* parent){
	Station* newOne = new Station();
	newOne->parent = parent;
	newOne->point.x = x;
	newOne->point.y = y;
	newOne->g = pow(abs(x - this->src.x), 2.0) + pow(abs(y - this->src.y), 2.0);
	newOne->h = pow(abs(this->dst.x - x), 2.0) + pow(abs(this->dst.y - y), 2.0);
	newOne->f = newOne->g + newOne->h;
	openArr.push_back(newOne);
}

// �������Ѱվ��
void Game::addCloseStation(Station* sta){
	openArr.push_back(sta);
}

// ��ȡ��ͼ���ַ�����ʽ��
std::string Game::getStringMap(void){
	// ��ʼ������
	std::vector<std::vector<char>*> map;
	for(int i = 0; i < mapHeight; i++){
		std::vector<char>* temp = new std::vector<char>();
		for(int j = 0; j < mapWidth; j++)
			temp->push_back('-');
		map.push_back(temp);
	}
	// ����ϰ���
	for(std::vector<Point*>::iterator iter = wall.begin(); iter != wall.end(); iter++){
		map[(*iter)->y]->at((*iter)->x) = '#';
	}
	// ��ǿ���Ѱ�ڵ�
	for(std::vector<Station*>::iterator iter = openArr.begin(); iter != openArr.end(); iter++){
		map[(*iter)->point.y]->at((*iter)->point.x) = ':';
	}
	// �������Ѱ�ڵ�
	for(std::vector<Station*>::iterator iter = closeArr.begin(); iter != closeArr.end(); iter++){
		map[(*iter)->point.y]->at((*iter)->point.x) = 'x';
	}
	// �����Ѱ·��
	if(!isNoWay()){
		Station* dstStation = NULL;
		for(std::vector<Station*>::iterator iter = openArr.begin(); iter != openArr.end(); iter++){
			Point p = (*iter)->point;
			if(p.x == dst.x && p.y == dst.y){
				dstStation = (*iter);
			}
		}
		if(dstStation != NULL){
			for(Station* p = dstStation; p != NULL; p = p->parent){
				map[p->point.y]->at(p->point.x) = '=';
			}
		}
	}
	// ������
	map[src.y]->at(src.x) = 'O';
	// ����յ�
	map[dst.y]->at(dst.x) = 'Q';
	// ƴ��Ϊ�ַ���
	std::string rs;
	for(std::vector<std::vector<char>*>::iterator iter = map.begin(); iter != map.end(); iter++){
		for(std::vector<char>::iterator iter2 = (*iter)->begin(); iter2 != (*iter)->end(); iter2++){
			rs += (*iter2);
			rs += ' ';
		}
		rs += '\n';
	}
	// ������ʱ����Ŀռ�
	for(std::vector<std::vector<char>*>::iterator iter = map.begin(); iter != map.end(); iter++){
		delete (*iter);
	}
	return rs;
}

// �Ƿ񵽴��յ�,��openArr���Ƿ����dst
bool Game::isCatchEndPoint(void){
	for(std::vector<Station*>::iterator iter = openArr.begin(); iter != openArr.end(); iter++){
		Point p = (*iter)->point;
		if(p.x == dst.x && p.y == dst.y){
			return true;
		}
	}
	return false;
}

// �Ƿ��޷������յ�,��openArr�Ƿ�����Ѱ���
bool Game::isNoWay(void){
	return openArr.size() == 0;
}

// ��Ѱվ�㣬openArr��ѡ����СFֵ��վ�����OPEN���ѱ��ڵ�CLOSE
void Game::openStation(void){
	// ���
	if(this->isNoWay())
		return;

	// �������ſ���Ѱ�ڵ�
	std::vector<Station*>::iterator bestIter = openArr.begin();
	for(std::vector<Station*>::iterator iter = openArr.begin()+1; iter != openArr.end(); iter++){
		if((*iter)->f < (*bestIter)->f){
			bestIter = iter;
		}
	}

	// �رձ��ڵ�
	Station* bestSta = (*bestIter);
	openArr.erase(bestIter);
	closeArr.push_back(bestSta);

	// ��Ѱ�ڵ�
	Point p = bestSta->point;
	std::vector<Point> neighbor;
	neighbor.push_back(Point(p.x - 1, p.y));
	neighbor.push_back(Point(p.x, p.y - 1));
	neighbor.push_back(Point(p.x, p.y + 1));
	neighbor.push_back(Point(p.x + 1, p.y));
	// ��������Ƿ񲻺Ϸ���������Ѱ
	std::vector<Point> filter1;
	for(std::vector<Point>::iterator iter = neighbor.begin(); iter != neighbor.end(); iter++){
		if((*iter).x >= 0 && (*iter).y >= 0 && (*iter).x < mapWidth && (*iter).y < mapHeight){
			filter1.push_back(*iter);
		}
	}
	// ��������Ƿ�����Ѱ,������Ѱ
	std::vector<Point> filter2;
	for(std::vector<Point>::iterator iter = filter1.begin(); iter != filter1.end(); iter++){
		bool has = false;
		for(std::vector<Station*>::iterator iter2 = closeArr.begin(); iter2 != closeArr.end(); iter2++){
			if((*iter2)->point.x == (*iter).x && (*iter2)->point.y == (*iter).y){
				has = true;
				break;
			}
		}
		if(!has)
			filter2.push_back(*iter);
	}
	// ��������Ƿ����ڿ���Ѱ������,������Ѱ
	std::vector<Point> filter3;
	for(std::vector<Point>::iterator iter = filter2.begin(); iter != filter2.end(); iter++){
		bool has = false;
		for(std::vector<Station*>::iterator iter2 = openArr.begin(); iter2 != openArr.end(); iter2++){
			if((*iter2)->point.x == (*iter).x && (*iter2)->point.y == (*iter).y){
				has = true;
				break;
			}
		}
		if(!has)
			filter3.push_back(*iter);
	}
	// �ܿ��ϰ���
	std::vector<Point> filter4;
	for(std::vector<Point>::iterator iter = filter3.begin(); iter != filter3.end(); iter++){
		bool has = false;
		for(std::vector<Point*>::iterator iter2 = wall.begin(); iter2 != wall.end(); iter2++){
			if((*iter2)->x == (*iter).x && (*iter2)->y == (*iter).y){
				has = true;
				break;
			}
		}
		if(!has)
			filter4.push_back(*iter);
	}
	// ��ӵ�����Ѱ�ڵ�
	for(std::vector<Point>::iterator iter = filter4.begin(); iter != filter4.end(); iter++){
		this->addOpenStation((*iter).x, (*iter).y, bestSta);
	}
}