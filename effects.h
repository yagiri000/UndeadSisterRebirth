#pragma once

#include <DxLib.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

#include "Func.h"

#include "Source.h"
#include "Screen.h"
//個々のエフェクトの設定ファイル

//-------------------------------------------
//
//                 n.i.a.
//
//                         effect draw system
//-------------------------------------------


//effectsの個々のエフェクトの基底クラス

class effectbase{
public:
	double x, y;
	double centerx, centery;
	double exratex, exratey;
	double angle;

	double alpha;
	double vx, vy;
	double ax, ay;
	double exratexplus, exrateyplus;
	double sppedrate;

	double angleplus;
	double alphaplus;
	int turnflag;
	int blendmode;

	int ghandle;
	int *efGHandle;

	int elapsedtime;
	int deleteframe;

	bool deleteflag;

	double PI;

	effectbase(int *p_gh) :
		efGHandle(p_gh),
		PI(3.141592653589793),
		x(0), y(0),
		centerx(0), centery(0),
		exratex(1.0), exratey(1.0),
		angle(0.0),

		alpha(255.0),
		vx(0.0), vy(0.0),
		ax(0.0), ay(0.0),
		exratexplus(1.0), exrateyplus(1.0),
		sppedrate(1.0),

		angleplus(0.0),
		alphaplus(0.0),
		turnflag(0),
		blendmode(DX_BLENDMODE_NOBLEND),

		elapsedtime(0),
		deleteframe(999),
		deleteflag(false)
	{

	}


	virtual void set(double xx, double yy,
		double centerx, double centery,
		double exratex, double exratey,
		double angle,

		double alpha,
		double vx, double vy,
		double ax, double ay,
		double exratexplus, double exrateyplus,
		double sppedrate,

		double angleplus,
		double alphaplus,

		int turnflag,
		int blendmode,
		int ghandle,

		int deleteframe
		)
	{
		this->x = xx;
		this->y = yy;
		this->centerx = centerx;
		this->centery = centery;
		this->exratex = exratex;
		this->exratey = exratey;
		this->angle = angle;

		this->alpha = alpha;
		this->vx = vx;
		this->vy = vy;
		this->ax = ax;
		this->ay = ay;
		this->exratexplus = exratexplus;
		this->exrateyplus = exrateyplus;
		this->sppedrate = sppedrate;

		this->angleplus = angleplus;
		this->alphaplus = alphaplus;
		this->turnflag = turnflag;
		this->blendmode = blendmode;

		this->ghandle = ghandle;

		this->elapsedtime = 0;
		this->deleteframe = deleteframe;
		this->deleteflag = false;
	}

	virtual void move(){
		x += vx;
		y += vy;

		vx += ax;
		vy += ay;

		vx *= sppedrate;
		vy *= sppedrate;

		exratex += exratexplus;
		exratey += exrateyplus;

		angle += angleplus;
		alpha += alphaplus;
	}

	virtual void update(){
		if (elapsedtime > -1){
			move();
		}

		elapsedtime++;

		if (elapsedtime > deleteframe){
			deleteflag = true;
		}
	}

	virtual void draw(){
		if (elapsedtime > -1){
			Draw::exrot3(x, y, centerx, centery, exratex, exratey, angle, ghandle, alpha, turnflag, blendmode);
		}
	}

	void wait(int f){
		elapsedtime = -f;
	}
};


//グレネード
class grenadefire : public effectbase{
public:
	grenadefire(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 2.0, 2.0, 0.0,
			120, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1, 1.0,
			0.0, -4, 0, DX_BLENDMODE_ADD, Graph::handle("firebase"), 15);
		Random::RandInCircle(12.0, vx, vy);
	};
	void draw(){
		if (elapsedtime > -1){
			SetDrawScreen(Screen::get().fire);
			Draw_::exrot3(x, y, centerx, centery, exratex, exratey, angle, ghandle, alpha, 0, blendmode);
			SetDrawScreen(DX_SCREEN_BACK);
		}
	}
};

//爆発する敵のエフェクト
class enemybombef : public effectbase{
public:
	enemybombef(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 4.0, 4.0, 0.0,
			128, 0.0, 0.0, 0.0, 0.0, 0.3, 0.3, 1.0,
			0.0, -3, 0, DX_BLENDMODE_ADD, Graph::handle("firebase"), 10);
	};
	void draw(){
		if (elapsedtime > -1){
			SetDrawScreen(Screen::get().fire);
			Draw_::exrot3(x, y, centerx, centery, exratex, exratey, angle, ghandle, alpha, 0, blendmode);
			SetDrawScreen(DX_SCREEN_BACK);
		}
	}
};



//火炎瓶
class molotovfire : public effectbase{
public:
	molotovfire(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 2.0, 5.0, 0.0,
			128, 0.0, 0.0, 0.0, 0.0, -0.02, -0.1, 1.0,
			0.0, -3, 0, DX_BLENDMODE_ADD, Graph::handle("firebase"), 30);
		vy = Random::FRand(-6, -3);
	};
	void draw(){
		if (elapsedtime > -1){
			SetDrawScreen(Screen::get().fire);
			Draw_::exrot3(x, y, centerx, centery, exratex, exratey, angle, ghandle, alpha, 0, blendmode);
			SetDrawScreen(DX_SCREEN_BACK);
		}
	}
};

//氷結弾
class freezeef : public effectbase{
public:
	freezeef(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			90, 0.0, 0.0, 0.0, -0.03, 0.4, 0.0, 1.0,
			0.0, -2, 0, DX_BLENDMODE_ADD, Graph::handle("icebase"), 30);
		Random::RandInCircle(10.0, vx, vy, angle);
	};
	void draw(){
		if (elapsedtime > -1){
			SetDrawScreen(Screen::get().fire);
			Draw_::exrot3(x, y, centerx, centery, exratex, exratey, angle, ghandle, alpha, 0, blendmode);
			SetDrawScreen(DX_SCREEN_BACK);
		}
	}
};

//火炎放射器
class flamethrow : public effectbase{
public:
	flamethrow(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.4, 1.4, 0.0,
			90, 0.0, 0.0, 0.0, 0.013, 0.013, 0.0, 0.98,
			0.0, -3.0, 0, DX_BLENDMODE_ADD, Graph::handle("firebase"), 30);
	};
	void draw(){
		if (elapsedtime > -1){
			SetDrawScreen(Screen::get().fire);
			Draw_::exrot3(x, y, centerx, centery, exratex, exratey, angle, ghandle, alpha, 0, blendmode);
			SetDrawScreen(DX_SCREEN_BACK);
		}
	}
};


//敵に火炎放射器が当たった時のエフェクト
class enemyhitfire : public effectbase{
public:	
	enemyhitfire(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
	set(x, y, 32, 32, 1.0, 1.0, 0.0,
		200, 0.0, 0.0, 0.0, 0.0, 0, 0, 1.0,
		0.0, -20, 0, DX_BLENDMODE_ALPHA, Graph::handle("light01"), 10);
	angle = Random::FRadRand();
	exratex = exratey = Random::FRand(0.4, 0.8);
	exratexplus = exrateyplus = Random::FRand(0.1, 0.2);
};
		void draw(){
			if (elapsedtime > -1){
				SetDrawScreen(Screen::get().fire);
				Draw_::exrot3(x, y, centerx, centery, exratex, exratey, angle, ghandle, alpha, 0, blendmode);
				SetDrawScreen(DX_SCREEN_BACK);
			}
		}
};



//敵にダメージを受けた時のエフェクト
class bloodsplash : public effectbase{
public:
	bloodsplash(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, Random::FRadRand(),
			255.0, 0.0, 0.0, 0.0, 0.0, -0.05, -0.05, 0.93,
			Random::FRand(-1.0, 1.0), 0.0, 0, DX_BLENDMODE_ALPHA, Graph::handle("blood01"), 19);
		Random::RandInCircle(15.0, vx, vy);
		Random::RandInCircle(0.1, ax, ay);
	};
	void draw(){
		if (elapsedtime > -1){
			SetDrawScreen(Screen::get().blood);
			Draw_::exrot3(x, y, centerx, centery, exratex, exratey, angle, ghandle, alpha, 0, blendmode);
			SetDrawScreen(DX_SCREEN_BACK);
			Draw::exrot3(x, y, centerx, centery, exratex, exratey, angle, ghandle, alpha, 0, blendmode);
		}
	}
};

//敵にダメージを受けた時のエフェクト
class saint_bloodsplash : public effectbase{
public:
	saint_bloodsplash(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, Random::FRadRand(),
			255.0, 0.0, 0.0, 0.0, 0.0, -0.05, -0.05, 0.93,
			Random::FRand(-1.0, 1.0), 0.0, 0, DX_BLENDMODE_ALPHA, Graph::handle("saint_blood"), 19);
		Random::RandInCircle(15.0, vx, vy);
		Random::RandInCircle(0.1, ax, ay);
	};
	void draw(){
		if (elapsedtime > -1){
			SetDrawScreen(Screen::get().blood);
			Draw_::exrot3(x, y, centerx, centery, exratex, exratey, angle, ghandle, alpha, 0, blendmode);
			SetDrawScreen(DX_SCREEN_BACK);
			Draw::exrot3(x, y, centerx, centery, exratex, exratey, angle, ghandle, alpha, 0, blendmode);
		}
	}
};

//弾発射時の弾の軌跡
class gunflash : public effectbase{
public:	gunflash(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
	set(x, y, 0, 16, 12.0, 0.1, 0.0,
		64, 0.0, 0.0, 0.0, 0.0, 0, 0, 1.0,
		0.0, 0, 0, DX_BLENDMODE_ALPHA, Graph::handle("gra32"), 2);
};
};

//弾発射時の閃光
class fireflash : public effectbase{
public:	fireflash(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
	set(x, y, 32, 32, 1.0, 1.0, 0.0,
		200, 0.0, 0.0, 0.0, 0.0, 0, 0, 1.0,
		0.0, -50, 0, DX_BLENDMODE_ALPHA, Graph::handle("light01"), 4);
	angle = Random::FRadRand();
	exratex = exratey = Random::FRand(0.8, 1.2);
};
};

//弾発射時の煙
class firesmoke : public effectbase{
public:	firesmoke(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
	set(x, y, 16, 16, 1.0, 1.0, 0.0,
		100, 0.0, 0.0, 0.0, 0.0, 0, 0, 1.0,
		0.0, -10, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32_black"), 10);
	exratex = exratey = Random::FRand(0.1, 0.3);
	double v_rate = Random::FRand(0.6, 1.2);
	Func::polartoxy(vx, vy, 4 * v_rate, Random::FRadRand());
	Func::polartoxy(ax, ay, 0.5 * v_rate, Random::FRadRand());
};
};

//レールガン
class splash_thin : public effectbase{
public:
	splash_thin(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 0.5, 0.0,
			220, 0.0, 0.0, 0.0, 0.0, 0, -0.05, 0.99,
			0.0, -10, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 10);
		Random::RandOnCircle(Random::FRand(2.0, 9.0), vx, vy, angle);
	};
};



//爆発時破片の表現
class dotsplash : public effectbase{
public:
	dotsplash(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.2, -0.05, -0.05, 0.93,
			0.0, 0.0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 19);
		Random::RandInCircle(15.0, vx, vy);
	};
};

//敵撃破時の血
class enemy_bloodsplash : public effectbase{
public:
	enemy_bloodsplash(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.2, -0.05, -0.05, 0.93,
			0.0, 0.0, 0, DX_BLENDMODE_ALPHA, Graph::handle("blood01"), 19);
		Random::RandInCircle(15.0, vx, vy);
	};
};
//チェーンソー・ナイフ 斬撃線
class slashef : public effectbase{
public:
	slashef(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 0.3, 0.6, 0.0,
			100, 0.0, 0.0, 0.0, 0.0, -0.03, 1.5, 1.0,
			0.0, -10, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 10);
		angle = Random::FRadRand();

	};
};

//ナイフ 斬撃残像
class knife_swing : public effectbase{
public:
	knife_swing(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 256, 256, 0.2, 0.2, 0.0,
			150, 0.0, 0.0, 0.0, 0.0, 0.05, 0.05, 1.0,
			0.0, -10, 0, DX_BLENDMODE_ALPHA, Graph::handle("slash01"), 2);

	};
};




//母体ゾンビが敵を生成するときのエフェクト
class enemy_makeef : public effectbase{
public:
	enemy_makeef(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double sx, sy, ang;
		Random::RandOnCircle(100, sx, sy, ang);
		double vx = -10 * cos(ang);
		double vy = -10 * sin(ang);
		set(x + sx, y + sy, 16, 16, 1.0, 1.0, 0.0,
			120, vx, vy, 0.0, 0.0, 0.0, 0.0, 0.92,
			0.0, -4, 0, DX_BLENDMODE_ALPHA, Graph::handle("blood01"), 30);
	};
};



class scoreplus : public effectbase{
public:	scoreplus(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
	set(x, y, 16, 16, 0, 0, 0.0,
		255, 0.0, -4, 0.0, 0.0, 0, 0, 1.0,
		0.0, 0, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 90);
};
		void draw(){
			if (elapsedtime > -1){
				SetDrawBlendMode(blendmode, (int)alpha);
				//スコアを保存するのにghandleを使用
				DrawFormatStringToHandle((int)x + Draw::get().dx - 40, (int)y + Draw::get().dy, 0xFFFFFF, Font::handle("SegoeUI20"), "+%d ", ghandle);
			}
		}
};


class dotlight : public effectbase{
public:
	dotlight(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 0.0, 0.0, Random::FRadRand(),
			255.0, 0.0, 0.0, 0.0, 0.0, 0.04, 0.04, 1.0,
			0.01, -8, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 30);
	};
};

class bomb : public effectbase{
public:
	bomb(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, Random::FRadRand(),
			255.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1, 1.0,
			0.01, -25, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 5);
	};
};

class fire : public effectbase{
public:
	fire(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 4, 4, 0.0,
			200, 0.0, 0.0, 0.0, 0.0, -0.15, -0.15, 1.0,
			0.0, -8, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 25);
		vx = Random::FRand(-1, 1);
		vy = Random::FRand(-15, -5);
	};
};



class elipsplash : public effectbase{
public:
	elipsplash(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 2.0, 1.0, Random::FRadRand(),
			255.0, 0.0, 0.0, 0.0, 0.0, -0.05, -0.05, 0.93,
			0.0, 0.0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
		Random::RandInCircle(15.0, vx, vy);

	};
};

class elipsplash_rot : public effectbase{
public:
	elipsplash_rot(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 2.0, 1.0, Random::FRadRand(),
			255.0, 0.0, 0.0, 0.0, 0.0, -0.05, -0.05, 0.93,
			Random::FRand(-PI, PI), 0.0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
		Random::RandInCircle(15.0, vx, vy);

	};
};

class dotsplash_curve : public effectbase{
public:
	dotsplash_curve(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.0, -0.05, -0.05, 1.0,
			0.0, 0.0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 16);
		Random::RandOnCircle(12.0, vx, vy);
		ax = -0.10 * vx;
		ay = -0.10 * vy;
		Func::rotateonzero(ax, ay, Random::FRand(-0.5, 0.5));
	};
};


//速度変化率 1.1
class dotsplash_charge : public effectbase{
public:
	dotsplash_charge(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.0, -0.05, -0.05, 1.1,
			0.0, 0.0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
		Random::RandInCircle(3.0, vx, vy);
	};
};



//放物線
class dotsplash_fall : public effectbase{
public:
	dotsplash_fall(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.4, -0.05, -0.05, 0.93,
			0.0, 0.0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
		Random::RandInCircle(15.0, vx, vy);
	};
};

class dotsplash_rev : public effectbase{
public:
	dotsplash_rev(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.0, -0.05, -0.05, Input::mousex() / 100.0,
			0.01, -0.099, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
		Random::RandInCircle(100.0, vx, vy);
	};

};

class moveonCircle : public effectbase{
public:
	int origx;
	int origy;
	moveonCircle(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		origx = (int)x;
		origy = (int)y;
		double r = 15.0 * Random::Value();
		double angle = Random::FRadRand();
		double vx = r * cos(angle);
		double vy = r * sin(angle);
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			128.0, vx, vy, 0.0, 0.0, 0.0, 0.0, 1.0,
			0.01, -3, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 120);
	};


	void move(){
		x = origx + 100 * cos(elapsedtime * 0.1);
		y = origy + 50 * sin(elapsedtime* 0.1);
	}
};




class dot_ex_inout : public effectbase{
public:
	dot_ex_inout(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 0.0, 0.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.0, 0.04, 0.04, 1.0,
			0.0, -8, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 20);
	};

	void move(){

		x += vx;
		y += vy;
		vx += ax;
		vy += ay;

		exratey = exratex = 1.0 - abs(10 - elapsedtime) * 0.1;

		angle += angleplus;
		alpha += alphaplus;
	}
};




class dot_verybig : public effectbase{
public:
	dot_verybig(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 0.0, 0.0, 0.0,
			255.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.5, 1.0,
			0.3, -8, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 30);
	};
};




class chargerotate : public effectbase{
public:
	double tx, ty;

	chargerotate(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		tx = x; ty = y;
		double sx, sy;
		Random::RandOnCircle(100, sx, sy);
		set(x + sx, y + sy, 16, 16, 1.0, 1.0, 0.0,
			60, vx, vy, 0.0, 0.0, 0.0, 0.0, 0.92,
			0.0, -1, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 20);
	};

	void move(){

		Func::normalizedVector(vx, vy, x, y, tx, ty);
		Func::rotateonzero(vx, vy, 0.9);
		x += 8 * vx;
		y += 8 * vy;

		exratex += exratexplus;
		exratey += exrateyplus;

		angle += angleplus;
		alpha += alphaplus;
	}
};


class chargerotate_rev : public effectbase{
public:
	double tx, ty;
	chargerotate_rev(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		tx = x; ty = y;
		double sx, sy;
		Random::RandOnCircle(150, sx, sy);
		set(x + sx, y + sy, 16, 16, 0.5, 0.5, 0.0,
			255, vx, vy, 0.0, 0.0, 0.0, 0.0, 0.92,
			0.0, 0, 0, DX_BLENDMODE_ADD, Graph::handle("dot32"), 20);
		angleplus = 0.9 * Random::RandPM1();
	};

	void move(){
		Func::normalizedVector(vx, vy, x, y, tx, ty);
		Func::rotateonzero(vx, vy, angleplus);
		x += 12 * vx;
		y += 12 * vy;

		exratex += exratexplus;
		exratey += exrateyplus;

		angle += angleplus;
		alpha += alphaplus;
	}
};


class dot_charge : public effectbase{
public:
	dot_charge(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double sx, sy, ang;
		Random::RandOnCircle(100, sx, sy, ang);
		double vx = -7 * cos(ang);
		double vy = -7 * sin(ang);
		set(x + sx, y + sy, 16, 16, 1.0, 1.0, 0.0,
			60, vx, vy, 0.0, 0.0, 0.0, 0.0, 0.92,
			0.0, -1, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 60);
	};
};


class reaf_move : public effectbase{
public:
	reaf_move(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double ang_v = Random::FRand(0.05, 0.1);
		double vx, vy;
		Random::RandOnCircle(1.4, vx, vy);
		set(x, y, 16, 16, 1.0, 2, 0.0,
			120, vx, vy, 0.0, 0.0, 0.0, 0.0, 1.0,
			ang_v, -1, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 120);
	};
};


class firework : public effectbase{
public:
	firework(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double vx, vy, ang;
		Random::RandOnCircle(Random::FRand(5, 15), vx, vy, ang);
		set(x, y, 16, 16, 1.0, 0.2, ang,
			150, vx, vy, 0.0, 0.0, 0, 0, 0.97,
			0.0, -10, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 15);
	};
};

class out_in_dot : public effectbase{
public:
	out_in_dot(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double ang = Random::FRadRand();
		double spd = Random::FRand(0.6, 1.3);
		double vx = 6 * spd * cos(ang);
		double vy = 6 * spd * sin(ang);
		double ax = 0.2 * spd * cos(ang - PI);
		double ay = 0.2 * spd * sin(ang - PI);
		set(x, y, 16, 16, 1.0, 1.0, ang,
			100, vx, vy, ax, ay, 0.0, 0.0, 1.0,
			0.0, -1.66, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 60);
	};
};


class floting_dot : public effectbase{
public:
	floting_dot(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double v_rate = Random::FRand(0.6, 1.3);
		double ang = Random::FRadRand();
		vx = 6 * v_rate * cos(ang);
		vy = 6 * v_rate * sin(ang);
		double ang_a = Random::FRadRand();
		ax = 0.2 * v_rate * cos(ang_a);
		ay = 0.2 * v_rate * sin(ang_a);
		set(x, y, 16, 16, 1.0, 1.0, ang,
			100, vx, vy, ax, ay, 0.0, 0.0, 0.9,
			0.0, -1.66, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 60);
	};
};

class fire_dot : public effectbase{
public:
	fire_dot(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double spd = Random::FRand(0.6, 1.3);
		double ang = Random::FRadRand(-100, -80);
		double vx = 8 * spd * cos(ang);
		double vy = 8 * spd * sin(ang);
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			80, vx, vy, 0.0, 0.0, -0.05, -0.05, 0.95,
			0.0, -4, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 20);
	};
	void move(){
		x += vx;
		y += vy;

		vx += ax;
		vy += ay;

		vx *= sppedrate;
		vy *= sppedrate;

		exratex += exratexplus;
		exratey += exrateyplus;

		angle += angleplus;
		alpha = Func::linef(0, 100, elapsedtime, 20);
	}
};

class splash_gravity : public effectbase{
public:
	splash_gravity(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		double spd = Random::FRand(0.6, 1.3);
		double ang = Random::FRadRand() * 0.2 - PI * 0.5;
		double vvx = 6 * spd * cos(ang);
		double vvy = 4 * spd * sin(ang);
		set(x, y, 16, 16, 1.0, 1.0, 0,
			100, vvx, vvy, 0.0, 0.5, 0.0, 0.0, 1.0,
			0.0, -1, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 60);
	};
};


class smoke : public effectbase{
public:
	smoke(double x, double y, int* p_ghandle) : effectbase(p_ghandle){
		set(x, y, 16, 16, 1.0, 1.0, 0.0,
			255.0, 0.0, -3, 0.0, 0.0, -0.05, -0.05, 0.99,
			0.0, -10, 0, DX_BLENDMODE_ALPHA, Graph::handle("dot32"), 20);
	};
};





class effectmgr{
public:

	std::vector<std::shared_ptr<effectbase>> v;
	int efGHandle[512];

	effectmgr(){
		loadimages();
	}

	void loadimages(){
	}

	void init(){
		v.clear();
	}

	//エフェクト生成 エフェクトへのスマートポインタを返す
	template <class T>
	std::shared_ptr<effectbase> add(double x, double y){
		std::shared_ptr<effectbase> p = std::make_shared<T>(x, y, efGHandle);
		v.emplace_back(p);
		return p;
	}


	//各エフェクトを更新・消去
	void update(){
		for (auto i : v){
			i->update();
		}
		//deleteflagがtrueなら除去
		auto rmv = std::remove_if(v.begin(), v.end(),
			[](std::shared_ptr<effectbase> p)->bool{
			return p->deleteflag;
		}
		);
		v.erase(rmv, v.end());
	}

	//描画
	void draw(){
		for (auto i : v){
			i->draw();
		}
		//デバッグ用・現在のエフェクト数を表示
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		//DrawFormatString(20, 60, 0xFFFFFF, "NUM : %d", v.size()) ;
	}
};