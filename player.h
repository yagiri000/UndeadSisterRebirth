#pragma once

#include "myglobal.h"
#include <DxLib.h>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

#include "Func.h"

#include "Source.h"

class player{
public:

	double x, y;
	double r;
	double gunangle;
	double hp, hpmax;
	int houkou, aruku;
	int firecool, firerate;//���̒e���˂܂ł̃N�[������, ���v����
	int reloadcool, reloadneed;//�����[�h�N�[������(>0�Œe�łĂȂ�) , �����[�h���v����
	int bullet, bulletmax;//���ݒe��, �ő�e��
	int atk;
	double movespeed;

	player();
	void init();
	void update();
	void draw();

	void move();
	void movelimit(int width, int height);
	void sethoukou();
	void movecamera();
};