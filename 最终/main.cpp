#include"data.h"
#include"gameManager.h"
int main()
{
	initgraph(800, 600);
	gameManager manager;
	manager.loadSources();
	manager.controller();


	// �������¼���ı仯
	closegraph();
}

// ���°汾