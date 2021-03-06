#pragma once

#include "myglobal.h"
#include <DxLib.h>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

class Idamagearea{
public:
	double x, y, r, angle;
	int deletetime, etime;
	double damage;
	double knockbackdist;
	bool deleteflag;

	Idamagearea(){
		deletetime = 0;
		etime = 0;
	}
	virtual void update() = 0;
};

//線上の一番近い敵
class dm_lineone : public Idamagearea
{
public:
	dm_lineone(double x_, double y_, double r_, double angle_, double damage_, double knockbackdist_){
		x = x_;
		y = y_;
		r = r_;
		angle = angle_;
		damage = damage_;
		knockbackdist = knockbackdist_;
		deleteflag = true;
	}

	void update();
};

//線上の敵
class dm_lineall : public Idamagearea
{
public:
	dm_lineall(double x_, double y_, double r_, double angle_, double damage_, double knockbackdist_){
		x = x_;
		y = y_;
		r = r_;
		angle = angle_;
		damage = damage_;
		knockbackdist = knockbackdist_;
		deleteflag = true;
	}

	void update();
};

//円の中にいる敵
class dm_circle : public Idamagearea 
{
public:
	dm_circle(double x_, double y_, double r_, double damage_, double knockbackdist_){
		x = x_;
		y = y_;
		r = r_;
		damage = damage_;
		knockbackdist = knockbackdist_;
		deleteflag = true;
	}

	void update();
};

//傾いた四角形上にいるすべての敵
class dm_tlitbox : public Idamagearea
{
public:
	double broad;

	dm_tlitbox(double x_, double y_, double r_, double angle_, double broad_, double damage_, double knockbackdist_){
		x = x_;
		y = y_;
		r = r_;
		angle = angle_;
		broad = broad_;
		damage = damage_;
		knockbackdist = knockbackdist_;
		deleteflag = true;
	}

	void update();
};


//傾いた四角形上にいるすべての敵
class dm_chainsaw : public Idamagearea
{
public:
	double broad;

	dm_chainsaw(double x_, double y_, double r_, double angle_, double broad_, double damage_, double knockbackdist_){
		x = x_;
		y = y_;
		r = r_;
		angle = angle_;
		broad = broad_;
		damage = damage_;
		knockbackdist = knockbackdist_;
		deleteflag = true;
	}

	void update();
};

class damageareamgr{
public:

	std::vector<std::shared_ptr<Idamagearea>> v;

	damageareamgr(){

	}


	void init(){
		v.clear();
	}

	//呼び出す側でmake_sharedを使う生成 スマートポインタを返す
	std::shared_ptr<Idamagearea> addptr(std::shared_ptr<Idamagearea> p){
		v.emplace_back(p);
		return p;
	}

	//各更新・消去
	void update(){
		for (auto i : v){
			i->update();
		}
		//deleteflagがtrueなら除去
		auto rmv = std::remove_if(v.begin(), v.end(),
			[](std::shared_ptr<Idamagearea> p)->bool{
			return p->deleteflag;
		}
		);
		v.erase(rmv, v.end());
	}

};