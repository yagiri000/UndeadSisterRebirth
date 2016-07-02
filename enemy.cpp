#pragma once

#include "manager.h"

Ienemy::Ienemy(){
	angle = 0.0;
	eframe = 0;
	wait = 0;
	deleteflag = false;
}


void Ienemy::attack(){
	auto& p = manager::get().player_;
	auto& s = manager::get().saintstone_;
	if (wait == 0 && Func::Circles(x, y, r, p.x, p.y, p.r - 3)){
		p.hp -= atk;
		wait = 60;
		Sound::playback("zusa");
		manager::get().scoremgr_.damage();
		for (int i = 0; i < 10; i++){
			manager::get().effect_.add<bloodsplash>((p.x + x) / 2, (p.y + y) / 2);
		}
	}
	if (wait == 0 && Func::Circles(x, y, r, s.x, s.y, s.r - 3)){
		s.hp -= atk;
		wait = 60;
		Sound::playback("zusa");
		manager::get().scoremgr_.damage();
		for (int i = 0; i < 10; i++){
			manager::get().effect_.add<saint_bloodsplash>((s.x + x) / 2, (s.y + y) / 2);
		}
	}
}

void Ienemy::move(){
	if (Func::coolcount(wait)){
		movetoplayer();
	}
	else{
		double vx, vy;
		Random::RandOnCircle(3.0, vx, vy);
		x += vx;
		y += vy;
	}
}

void Ienemy::movetoplayer(){
	auto& ply = manager::get().player_;
	double vx, vy;
	Func::normalizedVector(vx, vy, x, y, ply.x, ply.y);
	angle = atan2(vy, vx) - PI / 2;
	Func::rotateonzero(vx, vy, vrotangle);
	x += vx * speed;
	y += vy * speed;
}

void Ienemy::movetostone(){
	auto& s = manager::get().saintstone_;
	double vx, vy;
	Func::normalizedVector(vx, vy, x, y, s.x, s.y);
	angle = atan2(vy, vx) - PI / 2;
	Func::rotateonzero(vx, vy, vrotangle);
	x += vx * speed;
	y += vy * speed;
}

void Ienemy::Isdead(){
	if (hp < 0.1){
		for (int i = 0; i < 10; i++){
			manager::get().effect_.add<enemy_bloodsplash>(x, y);
		}
		SetDrawScreen(Screen::get().blood);
		for (int i = 0; i < 5; i++){
			double dx, dy;
			Random::RandInCircle(32, dx, dy);
			Draw_::exrot(x + dx, y + dy, Random::FRand(0.5, 1.5), Random::FRadRand(), Graph::handle("blood01"), 255);
		}
		SetDrawScreen(DX_SCREEN_BACK);

		Sound::playback("enemydead");
		deadlog();
		addscore();
		deleteflag = true;
	}
	if (x < -300){
		deleteflag = true;
	}
}

void Ienemy::deadlog(){
	manager::get().str_log_.add(
		gion() + name + "を倒した。"
		);
}

void Ienemy::addscore(){
	manager::get().scoremgr_.addscore(100);
};


void Ienemy::drawScreenOut(){
	double cx = dx + ScreenWidth / 2;
	double cy = dy + ScreenHeight / 2;
	if (abs(cx - x) > ScreenWidth / 2 + 64 || abs(cy - y) > ScreenHeight / 2 + 64){
		double drawx = ScreenWidth / 2;
		double drawy = ScreenHeight / 2;
		double angle = Func::calAngle(cx, cy, x, y);
		Func::addVector(cx, cy, x, y, 300, drawx, drawy);
		Draw_::exrot(drawx, drawy, 0.5, angle, Graph::handle("enemycursor"), 64);
	}
}


std::string Ienemy::gion(){
	std::string deadsound;
	int rnd = Random::Rand(9);
		 if (rnd == 0){ deadsound = "*バキッ* "; }
	else if (rnd == 1){ deadsound = "*グチャッ* "; }
	else if (rnd == 2){ deadsound = "*メリッ* "; }
	else if (rnd == 3){ deadsound = "*デロッ* "; }
	else if (rnd == 4){ deadsound = "*パァンッ* "; }
	else if (rnd == 5){ deadsound = "*グシュ* "; }
	else if (rnd == 6){ deadsound = "*ザシュ* "; }
	else if (rnd == 7){ deadsound = "*バタッ* "; }
	else if (rnd == 8){ deadsound = "*ゴリッ* "; }
	else if (rnd == 9){ deadsound = "*グニョキッ* "; }
	return deadsound;
}


void emy_weak::init(){
	r = 18;
	name = "腐敗ゾンビ";
	speed = 0.5;
	vrotangle = Random::FRand(-0.1, 0.1);
	hp = 2.0;
	atk = 3.0;
}
void emy_weak::update(){
	auto& ply = manager::get().player_;
	move();
	attack();
	Isdead();
}
void emy_weak::draw(){
	Draw::exrot(x, y, 1.0, angle, GraphDiv::handle("zombie", 0), 255);
	drawScreenOut();
}




//石狙い
void emy_normal::init(){
	r = 18;
	name = "普遍的ゾンビ";
	speed = 1.0;
	vrotangle = Random::FRand(-0.1, 0.1);
	hp = 2.0;
	atk = 3.0;
}
void emy_normal::update(){
	auto& ply = manager::get().player_;
	move();
	attack();
	Isdead();
}
void emy_normal::draw(){
	Draw::exrot(x, y, 1.0, angle, GraphDiv::handle("zombie", 1), 255);
	drawScreenOut();
	
}
void emy_normal::move(){
	if (Func::coolcount(wait)){
		movetostone();
	}
	else{
		double vx, vy;
		Random::RandOnCircle(3.0, vx, vy);
		x += vx;
		y += vy;
	}
}



//回転しながら 
void emy_rot_l::init(){
	r = 18;
	name = "血染ゾンビ";
	speed = 1.5;
	vrotangle = 0.8 * Random::RandPM1();
	hp = 5.0;
	atk = 5.0;
}
void emy_rot_l::update(){
	auto& ply = manager::get().player_;
	move();
	attack();
	Isdead();
}
void emy_rot_l::draw(){
	Draw::exrot(x, y, 1.0, angle, GraphDiv::handle("zombie", 4), 255);
	drawScreenOut();
	
}


//回転しながら
void emy_rot_l_tos::init(){
	r = 18;
	name = "巡回ゾンビ";
	speed = 2.5;
	//vrotangle = 1.4 * Random::RandPM1();
	vrotangle = 1.4;
	hp = 2.0;
	atk = 3.0;
}
void emy_rot_l_tos::update(){
	auto& ply = manager::get().player_;
	move();
	attack();
	Isdead();
}
void emy_rot_l_tos::draw(){
	Draw::exrot(x, y, 1.0, angle, GraphDiv::handle("zombie", 14), 255);
	drawScreenOut();
}
void emy_rot_l_tos::move(){
	if (Func::coolcount(wait)){
		if (x < -40){
			if (vrotangle > 0 && y < manager::get().saintstone_.y){
				vrotangle *= -1;
			}
			if (vrotangle < 0 && y > manager::get().saintstone_.y){
				vrotangle *= -1;
			}
		}
		movetostone();
	}
	else{
		double vx, vy;
		Random::RandOnCircle(3.0, vx, vy);
		x += vx;
		y += vy;
	}
}


//sin軌道
void emy_sin::init(){
	r = 18;
	name = "波動ゾンビ";
	speed = 2.0;
	vrotangle = 0.0;
	hp = 3.0;
	atk = 3.0;
}
void emy_sin::update(){
	auto& ply = manager::get().player_;
	move();
	attack();
	Isdead();
}
void emy_sin::draw(){
	Draw::exrot(x, y, 1.0, angle, GraphDiv::handle("zombie", 9), 255);
	drawScreenOut();
	
}
void emy_sin::move(){
	if (Func::coolcount(wait)){
		eframe++;
		auto& ply = manager::get().player_;
		double vx, vy;
		Func::normalizedVector(vx, vy, x, y, ply.x, ply.y);
		angle = atan2(vy, vx) - PI / 2;
		double rangle = 0.5 * PI * sin(eframe * PI * 2 / 240);
		Func::rotateonzero(vx, vy, rangle);
		x += vx * speed;
		y += vy * speed;
	}
	else{
		double vx, vy;
		Random::RandOnCircle(3.0, vx, vy);
		x += vx;
		y += vy;
	}
}


//爆発ゾンビ・倒すと爆発（誘爆超楽しい）
void emy_bomb::init(){
	r = 18;
	name = "起爆式ゾンビ";
	speed = 1.0;
	vrotangle = Random::FRand(-0.1, 0.1);
	hp = 2.0;
	atk = 3.0;
}
void emy_bomb::update(){
	auto& ply = manager::get().player_;
	move();
	attack();
	Isdead();
}
void emy_bomb::draw(){
	Draw::exrot(x, y, 1.0, angle, GraphDiv::handle("zombie", 3), 255);
	drawScreenOut();
}
void emy_bomb::Isdead(){
	if (hp < 0.1){

		Sound::playback("bomb01");
		for (int j = 0; j < 6; j++){
			manager::get().effect_.add<dotsplash>(x, y);
			auto efp = manager::get().effect_.add<enemybombef>(x, y);
			double dx, dy;
			Func::polartoxy(dx, dy, Random::FRand(7.0, 15.0), 2 * PI * j / 6 + Random::FRand(0.0, 0.5));
			efp->vx = dx;
			efp->vy = dy;
		}
		manager::get().damagearea_.addptr(std::make_shared<dm_circle>(x, y, 100, 10, 0.0));

		SetDrawScreen(Screen::get().blood);
		for (int i = 0; i < 5; i++){
			double dx, dy;
			Random::RandInCircle(32, dx, dy);
			Draw_::exrot(x + dx, y + dy, Random::FRand(0.5, 1.5), Random::FRadRand(), Graph::handle("blood01"), 255);
		}
		SetDrawScreen(DX_SCREEN_BACK);
		deadlog();
		addscore();
		deleteflag = true;
	}
}
void emy_bomb::deadlog(){
	manager::get().str_log_.add(
		gion() + name + "を倒した。"
		);
	manager::get().str_log_.add("*ドンッ* " + name + "は爆発した！");
}


void emy_goleft::init(){
	r = 18;
	name = "列伝ゾンビ";
	speed = 1.5;
	vrotangle = Random::FRand(-1.0, 1.0);
	hp = 1.0;
	atk = 3.0;
}
void emy_goleft::update(){
	move();
	attack();
	Isdead();
}
void emy_goleft::draw(){
	Draw::exrot(x, y, 1.0, angle, GraphDiv::handle("zombie", 2), 255);
	drawScreenOut();
	
}
void emy_goleft::move(){
	auto& ply = manager::get().player_;
	if (Func::coolcount(wait)){
		double vx = -speed;
		double vy = 0;
		angle = atan2(vy, vx) - PI / 2;
		x += vx * speed;
		y += vy * speed;
	}
	else{
		double vx, vy;
		Random::RandOnCircle(3.0, vx, vy);
		x += vx;
		y += vy;
	}
}


void emy_big::init(){
	r = 54;
	name = "大型ゾンビ";
	speed = 1.5;
	vrotangle = Random::FRand(-1.0, 1.0);
	hp = 1.0;
	atk = 3.0;
}
void emy_big::update(){
	move();
	attack();
	Isdead();
}
void emy_big::draw(){
	Draw::exrot(x, y, 3.0, angle, GraphDiv::handle("zombie", 2), 255);
	drawScreenOut();
	
}



void emy_moverot::init(){
	r = 18;
	name = "旋風ゾンビ";
	speed = 2.0;
	vrotangle = 1.0 * Random::RandPM1();
	hp = 3.0;
	atk = 3.0;
}
void emy_moverot::update(){
	auto& ply = manager::get().player_;
	eframe++;
	move();
	attack();
	Isdead();
}
void emy_moverot::draw(){
	Draw::exrot(x, y, 1.0, angle, GraphDiv::handle("zombie", 10), 255);
	drawScreenOut();
	
}
void emy_moverot::move(){
	if (Func::coolcount(wait)){
		auto& ply = manager::get().player_;
		double vx, vy;
		Func::normalizedVector(vx, vy, x, y, ply.x, ply.y);
		angle = atan2(vy, vx) - PI / 2;
		Func::rotateonzero(vx, vy, vrotangle + sin(eframe * 0.015));
		x += vx * speed;
		y += vy * speed;
	}
	else{
		double vx, vy;
		Random::RandOnCircle(3.0, vx, vy);
		x += vx;
		y += vy;
	}
}



void emy_devide::init(){
	r = 36;
	name = "拡散性ゾンビ";
	speed = 0.5;
	vrotangle = Random::FRand(-1.0, 1.0);
	hp = 5.0;
	atk = 3.0;
}
void emy_devide::update(){
	auto& ply = manager::get().player_;
	move();
	attack();
	Isdead();
}
void emy_devide::draw(){
	Draw::exrot(x, y, 2.0, angle, GraphDiv::handle("zombie", 5), 255);
	drawScreenOut();
	
}
void emy_devide::Isdead(){
	if (hp < 0.1){
		for (int i = 0; i < 30; i++){
			manager::get().effect_.add<floting_dot>(x, y);
		}

		for (int i = 0; i < 16; i++){
			double dx, dy;
			Func::polartoxy(dx, dy, 50, 2 * PI * i / 16);
			manager::get().enemy_.addfromenemy<emy_normal>(x + dx, y + dy);
		}
		deadlog();
		addscore();
		deleteflag = true;
	}
}
void emy_devide::deadlog(){
	manager::get().str_log_.add(
		gion() + name + "を倒した。"
		);
	manager::get().str_log_.add("*ミチャッ* " + name + "は分裂した！");
}



void emy_fast::init(){
	r = 18;
	name = "暗黒ゾンビ";
	speed = 3.5;
	vrotangle = Random::FRand(-0.1, 0.1);
	hp = 1.0;
	atk = 3.0;
}
void emy_fast::update(){
	auto& ply = manager::get().player_;
	move();
	attack();
	Isdead();
}
void emy_fast::draw(){
	Draw::exrot(x, y, 1.0, angle, GraphDiv::handle("zombie", 5), 255);
	drawScreenOut();
}


void emy_solid::init(){
	r = 18;
	name = "玉石ゾンビ";
	speed = 1.0;
	vrotangle = Random::FRand(-0.1, 0.1);
	hp = 10.0;
	atk = 3.0;
}
void emy_solid::update(){
	auto& ply = manager::get().player_;
	move();
	attack();
	Isdead();
}
void emy_solid::move(){
	if (Func::coolcount(wait)){
		movetostone();
	}
	else{
		double vx, vy;
		Random::RandOnCircle(3.0, vx, vy);
		x += vx;
		y += vy;
	}
}
void emy_solid::draw(){
	Draw::exrot(x, y, 1.0, angle, GraphDiv::handle("zombie", 7), 255);
	drawScreenOut();
}


void emy_light::init(){
	r = 18;
	name = "軽量化ゾンビ";
	speed = 1.5;
	vrotangle = Random::FRand(-0.03, 0.03);
	hp = 0.5;
	atk = 3.0;
}
void emy_light::update(){
	auto& ply = manager::get().player_;
	move();
	attack();
	Isdead();
}
void emy_light::draw(){
	Draw::exrot(x, y, 1.0, angle, GraphDiv::handle("zombie", 2), 255);
	drawScreenOut();
}


void emy_mother::init(){
	r = 36;
	name = "母体ゾンビ";
	speed = 0.5;
	vrotangle = Random::FRand(-0.1, 0.1);
	hp = 30.0;
	atk = 3.0;
}
void emy_mother::update(){
	auto& ply = manager::get().player_;
	eframe++;
	if (eframe % 120 == 60){
		for (int i = 0; i < 10; i++){
			manager::get().effect_.add<enemy_makeef>(x, y);
		}
	}
	if (eframe % 120 == 90){
		manager::get().str_log_.add("*グニョッ* " + name + "から新たにゾンビが生まれた！");
		manager::get().enemy_.addfromenemy<emy_rot_l>(x, y);
	}
	move();
	attack();
	Isdead();
}
void emy_mother::draw(){
	Draw::exrot(x, y, 2.0, angle, GraphDiv::handle("zombie", 8), 255);
	drawScreenOut();
}
void emy_mother::move(){
	if (Func::coolcount(wait)){
		movetostone();
	}
	else{
		double vx, vy;
		Random::RandOnCircle(3.0, vx, vy);
		x += vx;
		y += vy;
	}
}


void emy_boss::init(){
	r = 54;
	name = "肉塊ゾンビ";
	speed = 0.3;
	vrotangle = Random::FRand(-0.1, 0.1);
	hp = 100.0;
	atk = 10.0;
}
void emy_boss::update(){
	auto& ply = manager::get().player_;
	move();
	attack();
	Isdead();
}
void emy_boss::move(){
	if (Func::coolcount(wait)){
		movetostone();
	}
	else{
		double vx, vy;
		Random::RandOnCircle(3.0, vx, vy);
		x += vx;
		y += vy;
	}
}
void emy_boss::draw(){
	Draw::exrot(x, y, 3.0, angle, GraphDiv::handle("zombie", 11), 255);
	drawScreenOut();
}




