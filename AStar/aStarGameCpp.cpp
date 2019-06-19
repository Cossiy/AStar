
#include <iostream>
#include <Windows.h>
#include "Game.h"

// �ӳ�500ms��������ӡ��ͼ
void flushPrintMap(Game* game){
	Sleep(800);
	system("cls");
	std::cout << game->getStringMap();
}

// ������
int main(int argc, char* argv[])
{
	Game* game = new Game(7, 7);

	// ��������յ�
	game->setStartAndEndPoint(1, 1, 5, 3);

	// ����������յ�һ��
	//game->setStartAndEndPoint(2, 2, 2, 2);

	// �����ϰ���
	game->addWallPoint(3, 1);
	game->addWallPoint(3, 2);
	game->addWallPoint(2, 3);
	game->addWallPoint(4, 1);
	game->addWallPoint(5, 1);
	game->addWallPoint(4, 4);
	
	// ������·
	//game->addWallPoint(6, 1);
	//game->addWallPoint(3, 4);
	//game->addWallPoint(5, 4);
	//game->addWallPoint(6, 4);

	do{
		// �Ƿ��ѵ���
		if(game->isCatchEndPoint())
			break;

		// �Ƿ���Ͷ��·
		if(game->isNoWay())
			break;
		
		// ��Ѱ�ڵ�
		game->openStation();
		
		// ˢ�´�ӡ��ͼ
		flushPrintMap(game);
	}while(true);

	// ���
	if(game->isNoWay()){
		std::cout << "Can not catch the QQ!" << std::endl;
	} else {
		std::cout << "Congratulation! We find it!" << std::endl;
	}
	std::cin.get();

	// ������Դ
	delete game;

	return 0;
}

