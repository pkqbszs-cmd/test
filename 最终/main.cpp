#include"data.h"
#include"gameManager.h"
int main()
{
	initgraph(800, 600);
	gameManager manager;
	manager.loadSources();
	manager.controller();


	// 这里是新加入的变化
	closegraph();
}

// 最新版本