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

//����̈�ԋ߂��G
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

//����̓G
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

//�~�̒��ɂ���G
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

//�X�����l�p�`��ɂ��邷�ׂĂ̓G
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


//�X�����l�p�`��ɂ��邷�ׂĂ̓G
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

	//�Ăяo������make_shared���g������ �X�}�[�g�|�C���^��Ԃ�
	std::shared_ptr<Idamagearea> addptr(std::shared_ptr<Idamagearea> p){
		v.emplace_back(p);
		return p;
	}

	//�e�X�V�E����
	void update(){
		for (auto i : v){
			i->update();
		}
		//deleteflag��true�Ȃ珜��
		auto rmv = std::remove_if(v.begin(), v.end(),
			[](std::shared_ptr<Idamagearea> p)->bool{
			return p->deleteflag;
		}
		);
		v.erase(rmv, v.end());
	}

};