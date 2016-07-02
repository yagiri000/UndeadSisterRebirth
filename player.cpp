#pragma once

#include "manager.h"


player::player(){
	init();
}


void player::init(){
	x = 512;
	y = 512;
	r = 16;
	hp = hpmax = 80;
	gunangle = 0;
	houkou = 0, aruku = 0;
	firecool = 0, firerate = 9;//次の弾発射までのクール時間, 所要時間
	reloadcool = reloadneed = 120;//リロードクール時間(>0で弾打てない) , リロード所要時間
	bullet = 60, bulletmax = 60;//現在弾数, 最大弾数
	atk = 2;//銃威力
	movespeed = 1.8;//移動速度
}


void player::update(){
	move();
}


//主人公描画
void player::draw(){
	//自機と銃描画
	gunangle = atan2(Input::mousey() - y, Input::mousex() - x);
	int ar = (int)(aruku *0.1);
	ar = ar % 4;
	if (ar == 3){ ar = 1; }

	if (manager::get().gamestate_ == manager::dying){
		Draw::exrot3(x, y, 10, 20, 2, 2, PI / 2, GraphDiv::handle("playera", houkou + ar), 255);
	}
	else{
		manager::get().weapon_.draw2();
		if (gunangle < 0){
			manager::get().weapon_.draw();
			Draw::exrot3(x, y, 10, 20, 2, 2, 0, GraphDiv::handle("playera", houkou + ar), 255);
		}
		else{
			Draw::exrot3(x, y, 10, 20, 2, 2, 0, GraphDiv::handle("playera", houkou + ar), 255);
			manager::get().weapon_.draw();
		}
	}

	//地面にお絵かきする機能
	if (manager::get().gamestate_ == manager::gamemain &&  Input::keynow(KEY_INPUT_LSHIFT)){
		for (int i = 0; i < 36; i++){
			double dx, dy;
			Func::polartoxy(dx, dy, 128, 2 * PI / 36 * i);
			double ex = 8;
			if (Input::keyframe(KEY_INPUT_LSHIFT) > 10){
				ex = 8;
			}
			else{
				ex = 8.0 * Input::keyframe(KEY_INPUT_LSHIFT) / 10.0;
			}
			Draw::circle(x+dx, y+dy, ex, Func::HSVtoRGB(i * 10, 255, 255), 255);
		}
		Draw::centertext(x, y - 40, 0xFFFFFF, Font::handle("SegoeUI20"), "ペイント機能:ON", 128);

		SetDrawScreen(Screen::get().blood);
		double deg = atan2(Input::mousey() - y, Input::mousex() - x);
		deg += 2 * PI;
		deg = fmod(deg, 2 * PI);
		deg /= DegToRad;
		Draw_::circle(x, y, 16, Func::HSVtoRGB(deg, 255, 255), 255);
		SetDrawScreen(DX_SCREEN_BACK);
	}
}



void player::move(){
	double vv = movespeed;
	int angle = -1;

	if (Input::keynow(KEY_INPUT_RIGHT)){ angle = 0; }
	if (Input::keynow(KEY_INPUT_DOWN)){ angle = 90; }
	if (Input::keynow(KEY_INPUT_LEFT)){ angle = 180; }
	if (Input::keynow(KEY_INPUT_UP)){ angle = 270; }
	if (Input::keynow(KEY_INPUT_RIGHT) && Input::keynow(KEY_INPUT_DOWN)){ angle = 45; }
	if (Input::keynow(KEY_INPUT_DOWN) && Input::keynow(KEY_INPUT_LEFT)){ angle = 135; }
	if (Input::keynow(KEY_INPUT_LEFT) && Input::keynow(KEY_INPUT_UP)){ angle = 225; }
	if (Input::keynow(KEY_INPUT_UP) && Input::keynow(KEY_INPUT_RIGHT)){ angle = 315; }

	if (Input::keynow(32)){ angle = 0; }
	if (Input::keynow(31)){ angle = 90; }
	if (Input::keynow(30)){ angle = 180; }
	if (Input::keynow(17)){ angle = 270; }
	if (Input::keynow(32) && Input::keynow(31)){ angle = 45; }
	if (Input::keynow(31) && Input::keynow(30)){ angle = 135; }
	if (Input::keynow(30) && Input::keynow(17)){ angle = 225; }
	if (Input::keynow(17) && Input::keynow(32)){ angle = 315; }

	if (angle != -1){
		x += vv * cos(angle * DegToRad);
		y += vv * sin(angle * DegToRad);
		aruku++;
	}

	movelimit(800, 600);
	sethoukou();
	movecamera();
}


void player::movelimit(int width, int height){

	auto& p = manager::get().saintstone_;
	if (Func::dist(x, y, p.x, p.y) < 50){
		Func::addVector(p.x, p.y, x, y, 4.0, x, y);
	}
	if (x < 0){ x = 0; }
	if (x > StageWidth){ x = StageWidth; }
	if (y < 0){ y = 0; }
	if (y > StageHeight){ y = StageHeight; }
}


void player::sethoukou(){
	double angle = atan2(Input::mousey() - y, Input::mousex() - x);
	angle += 6.28 / 16;
	if (angle<0){ angle += 6.284; }
	int houkou8 = 0;
	int houkouset[9] = { 12, 9, 0, 3, 6, 15, 18, 21 };
	houkou8 = (int)(angle / DegToRad) / 45;
	houkou8 = houkou8 % 8;
	houkou = houkouset[houkou8];
}

void player::movecamera(){
	if (x < ScreenWidth / 2){
		dx = 0;
	}
	else if (x < StageWidth - (ScreenWidth / 2)){
		dx = x - ScreenWidth / 2;
	}
	else{
		dx = StageWidth - ScreenWidth;
	}

	if (y < ScreenHeight / 2){
		dy = 0;
	}
	else if (y < StageHeight - (ScreenHeight / 2)){
		dy = y - ScreenHeight / 2;
	}
	else{
		dy = StageHeight - ScreenHeight;
	}
	Draw::get().setdxdy(-dx, -dy);
}



