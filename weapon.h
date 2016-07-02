#pragma once

#include "myglobal.h"

#include <DxLib.h>
#include "Func.h"

#include "Source.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <algorithm>





class I_weapon{
public:
	std::string name;
	int firecool, firerate;//次の弾発射までのクール時間(>0で弾打てない), 所要時間
	int reloadcool, reloadneed;//リロードクール時間(>0で弾打てない) , リロード所要時間
	int bullet, bulletmax;//現在弾数, 最大弾数
	double x, y, angle;
	double atk;
	double knockbackdist;
	double range;
	double movespeedplus;//自機移動速度比率に加算する値

	I_weapon(){

	}
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	bool shot(bool keyon);

	void r_reload();

	void get_pos_angle();
};


//サブマシンガン
class w_machinegun : public I_weapon{
public:
	w_machinegun() : I_weapon()
	{
		init();
	}
	void init();
	void update();
	void draw();
};


//ライフル
class w_rifle : public I_weapon{
public:
	w_rifle() : I_weapon()
	{
		init();
	}
	void init();
	void update();
	void draw();
};


//ショットガン
class w_shotgun : public I_weapon{
public:
	w_shotgun() : I_weapon()
	{
		init();
	}
	void init();
	void update();
	void draw();
};


//火炎放射器
class w_firegun : public I_weapon{
public:
	int soundcool, soundrate;
	w_firegun() : I_weapon()
	{
		init();
	}
	void init();
	void update();
	void draw();
};

//チェーンソー
class w_chainsaw : public I_weapon{
public:
	int soundcool, soundrate;
	w_chainsaw() : I_weapon()
	{
		init();
	}
	void init();
	void update();
	void draw();
};

//レールガン
class w_railgun : public I_weapon{
public:
	w_railgun() : I_weapon()
	{
		init();
	}
	void init();
	void update();
	void draw();
};

//グレネード
class w_grenade : public I_weapon{
public:
	class grenadeparts{
	public:
		double sx, sy, ex, ey, nowx, nowy;
		int etime;
		int falltime;

		grenadeparts(double sx_, double sy_, double ex_, double ey_){
			sx = sx_;
			sy = sy_;
			ex = ex_;
			ey = ey_;
			etime = 0;
			falltime = 40 + 0.07 * Func::dist(sx, sy, ex, ey);
		}
		void update();
		void draw();
	};

	std::vector<grenadeparts> vec;

	w_grenade() : I_weapon()
	{
		init();
		vec.clear();
	}
	void init();
	void update();
	void draw();
};


//地雷
class w_mine : public I_weapon{
public:
	class mineparts{
	public:
		double x, y;
		int etime;
		bool deleteflag;
		mineparts(double x_, double y_){
			x = x_;
			y = y_;
			deleteflag = false;
		}
		void update();
		void draw();
	};

	std::vector<mineparts> vec;

	w_mine() : I_weapon()
	{
		init();
		vec.clear();
	}
	void init();
	void update();
	void draw();
};


//火炎瓶
class w_molotov : public I_weapon{
public:
	class parts{
	public:
		double sx, sy, ex, ey, nowx, nowy;
		int etime;
		int falltime;
		int state;//0で投げ中・1で炎上中

		parts(double sx_, double sy_, double ex_, double ey_){
			sx = sx_;
			sy = sy_;
			ex = ex_;
			ey = ey_;
			state = 0;
			etime = 0;
			falltime = 60;
		}
		void update();
		void draw();
	};

	std::vector<parts> vec;

	w_molotov() : I_weapon()
	{
		init();
		vec.clear();
	}
	void init();
	void update();
	void draw();
};



//氷結弾
class w_freeze : public I_weapon{
public:
	class parts{
	public:
		double sx, sy, ex, ey, nowx, nowy;
		int etime;
		int falltime;
		int state;//0で投げ中・1で炎上中

		parts(double sx_, double sy_, double ex_, double ey_){
			sx = sx_;
			sy = sy_;
			ex = ex_;
			ey = ey_;
			state = 0;
			etime = 0;
			falltime = 60;
		}
		void update();
		void draw();
	};

	std::vector<parts> vec;

	w_freeze() : I_weapon()
	{
		init();
		vec.clear();
	}
	void init();
	void update();
	void draw();
};

//ナイフ
class w_knife : public I_weapon{
public:
	w_knife() : I_weapon()
	{
		init();
	}
	void init();
	void update();
	void draw();
};


//ブロック
class w_block : public I_weapon{
public:
	class blockparts{
	public:
		double x;
		double y;
		double r;
		int remaintime;

		blockparts(double x_, double y_){
			x = x_;
			y = y_;
			r = 53;
			remaintime = 1800;
		}
		void update();
		void draw();
	};

	std::vector<blockparts> vec;

	w_block() : I_weapon()
	{
		init();
	}
	void init();
	void update();
	void draw();
};




class weaponmgr{
public:

	std::vector<std::shared_ptr<I_weapon>> mainvec;
	std::vector<std::shared_ptr<I_weapon>> subvec;
	std::shared_ptr<I_weapon> main;
	std::shared_ptr<I_weapon> sub;


	weaponmgr(){
		mainvec.emplace_back(std::make_shared<w_machinegun>());
		mainvec.emplace_back(std::make_shared<w_rifle>());
		mainvec.emplace_back(std::make_shared<w_shotgun>());
		mainvec.emplace_back(std::make_shared<w_firegun>());
		mainvec.emplace_back(std::make_shared<w_chainsaw>());
		mainvec.emplace_back(std::make_shared<w_railgun>());

		subvec.emplace_back(std::make_shared<w_grenade>());
		subvec.emplace_back(std::make_shared<w_mine>());
		subvec.emplace_back(std::make_shared<w_molotov>());
		subvec.emplace_back(std::make_shared<w_freeze>());
		subvec.emplace_back(std::make_shared<w_knife>());
		subvec.emplace_back(std::make_shared<w_block>());

		main = mainvec[0];
		sub = subvec[0];

		init();
	}

	void init(){
		for (auto& i : mainvec){
			i->init();
		}
		for (auto& i : subvec){
			i->init();
		}
	}

	void update(){

		main->update();
		sub->update();
	}

	//武器の残弾数をstringで返す関数
	std::string bulletnum_main(){
		if (main->bullet >= 999){
			return std::string("∞");
		}else if (main->bullet > 0){
			return std::to_string(main->bullet);
		}
		else{
			int rate = 100.0 - (double)main->reloadcool / main->reloadneed * 100.0;
			return	std::to_string(rate) + "%";
		}
	}

	//サブ武器の残弾数をstringで返す関数
	std::string bulletnum_sub(){
		if (sub->bullet >= 999){
			return std::string("∞");
		}
		else if (sub->bullet > 0){
			return std::to_string(sub->bullet);
		}
		else{
			int rate = 100.0 - (double)sub->reloadcool / sub->reloadneed * 100.0;
			return std::to_string(rate) + "%";
		}
	}

	void setweapon(int mainnum, int subnum){
		main = mainvec[mainnum];
		sub = subvec[subnum];
	}

	void draw(){
		main->draw();
	}
	void draw2(){
		sub->draw();
	}

};
