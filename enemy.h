#pragma once

#include <DxLib.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>



class Ienemy{
public:
	std::string name;
	double x, y, r, speed, angle, vrotangle;
	double hp;
	double atk;

	int wait;//wait>0なら停止・震え
	int eframe;
	bool deleteflag;

	Ienemy();
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void attack();
	virtual void move();
	virtual void movetoplayer();
	virtual void movetostone();
	virtual void Isdead();
	virtual void deadlog();
	virtual void addscore();
	virtual void drawScreenOut();
	std::string gion();
};


//腐敗ゾンビ・一番弱い（塊にして出すと面白そう）
class emy_weak : public Ienemy{
public:
	emy_weak(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
};

//普遍的ゾンビ
class emy_normal : public Ienemy{
public:
	emy_normal(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
	void move();
};


class emy_rot_l : public Ienemy{
public:
	emy_rot_l(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
};


class emy_rot_l_tos : public Ienemy{
public:
	emy_rot_l_tos(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
	void move();
};


class emy_sin : public Ienemy{
public:
	emy_sin(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
	void move();
};


//爆発ゾンビ・倒すと爆発（誘爆超楽しい）
class emy_bomb : public Ienemy{
public:
	emy_bomb(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
	void Isdead();
	void deadlog();
};


//ただ左に移動するだけのゾンビ（縦ラインにたくさん出して遊ぶ）
class emy_goleft : public Ienemy{
public:
	emy_goleft(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
	void move();
};

//大きいゾンビ
class emy_big : public Ienemy{
public:
	emy_big(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
};


//自機の周りを前後して回りながら強襲するゾンビ
class emy_moverot : public Ienemy{
public:
	emy_moverot(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
	void move();
};


//倒すと分裂するゾンビ
class emy_devide : public Ienemy{
public:
	emy_devide(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
	void Isdead();
	void deadlog();
};


//高速移動
class emy_fast : public Ienemy{
public:
	emy_fast(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
};


class emy_solid : public Ienemy{
public:
	emy_solid(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
	void move();
};

class emy_light : public Ienemy{
public:
	emy_light(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
};

class emy_mother : public Ienemy{
public:
	emy_mother(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
	void move();
};

class emy_boss : public Ienemy{
public:
	emy_boss(double x_, double y_){
		x = x_;	y = y_;
		init();
	}
	void init();
	void update();
	void draw();
	void move();
};

class enemymgr{
public:

	std::vector<std::shared_ptr<Ienemy>> v;
	std::vector<std::shared_ptr<Ienemy>> addv;

	enemymgr(){
	}


	void init(){
		v.clear();
		addv.clear();
	}

	//生成 スマートポインタを返す
	template <class T>
	std::shared_ptr<Ienemy> add(double x, double y){
		std::shared_ptr<Ienemy> p = std::make_shared<T>(x, y);
		v.emplace_back(p);
		return p;
	}

	//敵から敵を生成するとき呼ぶ関数
	template <class T>
	std::shared_ptr<Ienemy> addfromenemy(double x, double y){
		std::shared_ptr<Ienemy> p = std::make_shared<T>(x, y);
		addv.emplace_back(p);
		return p;
	}

	template <class T>
	std::shared_ptr<Ienemy> addmarge(double pos, double marge){
		double x, y;
		if (abs(pos) < 1.0){
			x = 1024.0 + marge;
			y = 512.0 + pos * 512.0;
		}
		else if (pos > 0){
			x = 1536.0 - 512.0 * pos;
			y = 1024.0 + marge;
		}
		else{
			x = 1536.0 + 512.0 * pos;
			y = -marge;
		}
		std::shared_ptr<Ienemy> p = std::make_shared<T>(x, y);
		v.emplace_back(p);
		return p;
	}

	//更新・消去
	void update(){
		for (auto i : v){
			i->update();
		}
		//deleteflagがtrueなら除去
		auto rmv = std::remove_if(v.begin(), v.end(),
			[](std::shared_ptr<Ienemy> p)->bool{
			return p->deleteflag;
		}
		);
		v.erase(rmv, v.end());

		for (auto i = addv.begin(); i < addv.end(); i++){
			v.emplace_back(*i);
		}
		addv.clear();
	}

	//描画
	void draw(){
		for (auto i : v){
			i->draw();
			//Draw::centertext(i->x, i->y - 40, 0xFFFFFF, Font::handle("SegoeUI20"), std::to_string((int)(i->hp * 10)), 64);
		}
		//デバッグ用・v.size()を表示
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		//DrawFormatString(20, 300, 0xFFFFFF, "NUM : %d", v.size()) ;
	}
};