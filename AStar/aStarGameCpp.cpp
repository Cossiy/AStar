
#include <iostream>
#include <Windows.h>
#include "Game.h"

// 延迟500ms清屏并打印地图
void flushPrintMap(Game* game){
	Sleep(800);
	system("cls");
	std::cout << game->getStringMap();
}

// 主函数
int main(int argc, char* argv[])
{
	Game* game = new Game(7, 7);

	// 设置起点终点
	game->setStartAndEndPoint(1, 1, 5, 3);

	// 测试起点与终点一致
	//game->setStartAndEndPoint(2, 2, 2, 2);

	// 设置障碍物
	game->addWallPoint(3, 1);
	game->addWallPoint(3, 2);
	game->addWallPoint(2, 3);
	game->addWallPoint(4, 1);
	game->addWallPoint(5, 1);
	game->addWallPoint(4, 4);
	
	// 测试无路
	//game->addWallPoint(6, 1);
	//game->addWallPoint(3, 4);
	//game->addWallPoint(5, 4);
	//game->addWallPoint(6, 4);

	do{
		// 是否已到达
		if(game->isCatchEndPoint())
			break;

		// 是否走投无路
		if(game->isNoWay())
			break;
		
		// 搜寻节点
		game->openStation();
		
		// 刷新打印地图
		flushPrintMap(game);
	}while(true);

	// 结果
	if(game->isNoWay()){
		std::cout << "Can not catch the QQ!" << std::endl;
	} else {
		std::cout << "Congratulation! We find it!" << std::endl;
	}
	std::cin.get();

	// 回收资源
	delete game;

	return 0;
}

