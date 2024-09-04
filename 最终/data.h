#pragma once
#include<iostream>
#include<vector>
#include<easyx.h>
#include<conio.h>
#include<fstream>
#include <string>// ���� std::to_string
#include<algorithm>//For_sort
#include <random>  // ���� std::mt19937 �� std::uniform_int_distribution
#include <cstdlib> // ���� std::random_device
#include <functional>
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

using namespace std;
// ����ö������
enum GameState {
	SIGNIN,
	LOGIN,
	FINDPASSWORD,
	FINDPASSWORD2,
	MENU,
	PASSCHOOSE,
	CHANGESTYLE,
	GUIDE,
	RANKLIST,
	SET,
	GAMEVIEW,
	LOSESHOW,
	WINSHOW,
	MEMBERINFO,
	BUFF,
	OVER
};
extern int map[15][20];
/*
	��ͼ��800*600��һ��ǽ40���أ���ǽΪ��λ������ά�����ͼ
	0��ʾ�յ�
	1��ʾľǽ
	2��ʾʯǽ
	3��ʾ��������
	4��ʾ�������
	5��ʾ���Ƶ���
	����������õ���3��ʾ�����ھ�����ʲô�����������İ�
	6��ʾ����
	7��ʾ��ҳ�����//����һ�µ�����Ԫ�ر�ǣ������Ƿ�������Ҫ��������һ��
	8��ʾ�ж�̹�˳�����//����һ�µ�����Ԫ�ر�ǣ������Ƿ�������Ҫ��������һ��
	100��ʾ�ҷ�̹��
	101��ʾ�з�̹��
*/
//�����ˣ�D-��ͼͬʱ��дpass�������Ӵ����ﶬ������Ԫ�غ�Ҫ�ڵ�ͼ��˵���������ӣ����磺7��ʾˮ��
//��һ�ص�ͼ
extern int pass1[15][20];
//�ڶ��ص�ͼ
extern int pass2[15][20];
//�����ص�ͼ
extern int pass3[15][20];
//���Ĺص�ͼ
extern int pass4[15][20];
//����ص�ͼ
extern int pass5[15][20];
/*
	�û���
		���ԣ�
			name:�˺�
			password:����
			email:����
			stars:��������
*/
struct user {
	string name;
	string password;
	string email;
	int stars;
	int time;
};
//�ҷ�̹��ͼƬ
extern IMAGE my_tank_img[3][4];
//�ӵ�ͼƬ
extern IMAGE bullet_img[2];
//�з�̹��ͼƬ
extern IMAGE enemy_tank_img[2][4];
//����ͼƬ
extern IMAGE base_img;
//ľǽͼƬ
extern IMAGE woodWall_img;
//ʯǽͼƬ
extern IMAGE stoneWall_img;
//����ͼƬ
extern IMAGE buff_img[3];
//Ƥ��ͼƬ
extern IMAGE skin[3];
//���˵�����ͼ
extern IMAGE bg;
extern IMAGE back_img[8];
extern vector<user> users; // ���ڴ洢�û���Ϣ������
extern IMAGE img_set;
extern IMAGE show_buff_img[3];
extern IMAGE pass_img[5];
extern int selectedBuff;
extern int selectedSkin;