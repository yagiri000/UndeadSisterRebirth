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


class Istage{
public:

	int eframe;		//�X�e�[�W�J�n����̌o�߃t���[��
	int waveframe;	//�E�F�[�u�J�n����̌o�߃t���[��
	int wave;		//���݃E�F�[�u�͉��ڂ�
	int endwave;	//�ŏI�E�F�[�u�͉���
	std::vector<int> waveendframe;//�e�E�F�[�u�̏I���t���[��

	Istage(){
		init();
	}

	void resetframe_wave(){
		eframe = 0;
		waveframe = 0;
		wave = 0;
	}

	void countframe(){
		eframe++;
		waveframe++;
	}

	void advancewave();


	//a%b == c��Ԃ��֐�
	bool modbool(int a, int b, int c = 0){
		return (a % b) == c;
	}

	//�G�̐���0���ǂ����𒲂ׂ�bool��Ԃ��֐�
	bool Isenemyzero();

	void stageend();
	void stageending();

	virtual void init();
	virtual void update() = 0;
	virtual void draw();
};

//�e���v���p
class stage0 : public Istage{
public:
	stage0();
	void init();
	void update();
};

class stage1 : public Istage{
public:
	stage1();
	void init();
	void update();
	//void draw();
};

class stage2 : public Istage{
public:
	stage2();
	void init();
	void update();
};

class stage3 : public Istage{
public:
	stage3();
	void init();
	void update();
};

class stage4 : public Istage{
public:
	stage4();
	void init();
	void update();
};

class stage5 : public Istage{
public:
	stage5();
	void init();
	void update();
};

class stage6 : public Istage{
public:
	stage6();
	void init();
	void update();
};

class stage7 : public Istage{
public:
	stage7();
	void init();
	void update();
};

class stage8 : public Istage{
public:
	stage8();
	void init();
	void update();
};

class stage9 : public Istage{
public:
	stage9();
	void init();
	void update();
};

class stage10 : public Istage{
public:
	stage10();
	void init();
	void update();
};



class stagemgr{
public:
	std::vector<std::shared_ptr<Istage>> v;
	std::shared_ptr<Istage> now;
	int stagenum;
	
	stagemgr(){
		v.emplace_back(std::make_shared<stage1>());
		v.emplace_back(std::make_shared<stage2>());
		v.emplace_back(std::make_shared<stage3>());
		v.emplace_back(std::make_shared<stage4>());
		v.emplace_back(std::make_shared<stage5>());
		v.emplace_back(std::make_shared<stage6>());
		v.emplace_back(std::make_shared<stage7>());
		v.emplace_back(std::make_shared<stage8>());
		v.emplace_back(std::make_shared<stage9>());
		v.emplace_back(std::make_shared<stage10>());
		stagenum = 0;
		now = v[stagenum];
		init();
	}


	//�X�e�[�W�w�� stage1�Ȃ�1���w��
	void setstage(int num){
		stagenum = num;
		now = v[stagenum];
	}

	void init(){
		for (auto i : v){
			i->init();
		}
	}

	void update(){
		now->update();
	}

	void draw(){
		now->draw();
	}
};


