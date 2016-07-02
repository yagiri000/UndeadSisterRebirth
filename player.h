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
	int firecool, firerate;//次の弾発射までのクール時間, 所要時間
	int reloadcool, reloadneed;//リロードクール時間(>0で弾打てない) , リロード所要時間
	int bullet, bulletmax;//現在弾数, 最大弾数
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