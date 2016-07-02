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
#include "Screen.h"


class titlemgr{
public:

	class startbutton{
	public:
		bool IsActive;
		int x, y, width, height;

		startbutton(){
			IsActive = false;
			x = ScreenWidth / 2;
			y = 450;
			width = 800;
			height = 50;
		}

		void update(){
			bool preIsActive = IsActive;
			if (Func::DotAndRect(Input::mousex_(), Input::mousey_(), x - width / 2, y - height / 2, x + width / 2, y + height / 2)){
				IsActive = true;
				//マウス右クリックされたら次のシーケンスに進む
				if (Input::keydown(250)){
					stateshift();
				}
			}
			else{
				IsActive = false;
			}

			if (preIsActive == false && IsActive == true){
				Sound::playback("menumove");
			}
		}

		void stateshift();

		void draw(){
			Draw_::centerbox(x, y, width, height, Func::HSVtoRGB(Input::eframe()*1.5, 255, 255), 32);

			if (IsActive){
				Draw_::centerbox(x, y, width, height, Func::HSVtoRGB(Input::eframe()*1.5, 255, 255), 128);
			}

			Draw_::exrot(x, y, 1.0, 0.0, Graph::handle("title_str_start"), 255);
			if (Input::keydown(250)){
				SetDrawScreen(Screen::get().trail);
				for (int i = 0; i < 50; i++){
					double dx, dy;
					Random::RandInCircle(96, dx, dy);
					Draw::circle(Input::mousex() + dx, Input::mousey() + dy, Random::FRand(4, 24), GetColor(Random::Rand(120, 130), 0, 0), 255);
				}
				SetDrawScreen(DX_SCREEN_BACK);
			}
			if (Input::keynow(251)){
				SetDrawScreen(Screen::get().trail);
				for (int i = 0; i < 3; i++){
					double dx, dy;
					Random::RandInCircle(32, dx, dy);
					Draw::circle(Input::mousex() + dx, Input::mousey() + dy, Random::FRand(4, 12), GetColor(Random::Rand(120, 130), 0, 0), 255);
				}
				SetDrawScreen(DX_SCREEN_BACK);
			}
		}
	};

	class exitbutton{
	public:
		bool IsActive;
		int x, y, width, height;

		exitbutton(){
			IsActive = false;
			x = ScreenWidth / 2;
			y = 520;
			width = 800;
			height = 50;
		}

		void update(){
			bool preIsActive = IsActive;
			if (Func::DotAndRect(Input::mousex_(), Input::mousey_(), x - width / 2, y - height / 2, x + width / 2, y + height / 2) ){
				IsActive = true;
				if (Input::keydown(250)){
					stateshift();
				}
			}
			else{
				IsActive = false;
			}
			if (preIsActive == false && IsActive == true){
				Sound::playback("menumove");
			}

		}

		void stateshift();

		void draw(){
			Draw_::centerbox(x, y, width, height, Func::HSVtoRGB(Input::eframe()*1.5 + 60, 255, 255), 32);

			if (IsActive){
				Draw_::centerbox(x, y, width, height, Func::HSVtoRGB(Input::eframe()*1.5 + 60, 255, 255), 128);
			}

			Draw_::exrot(x, y, 1.0, 0.0, Graph::handle("title_str_exit"), 255);
		}
	};

	startbutton s_button;
	exitbutton e_button;

	titlemgr(){
		init();
	}

	void init(){
	}

	void update(){
		s_button.update();
		e_button.update();
	}

	void draw(){
		Draw_::normal(0, 0, Graph::handle("titlebg"), 255);
		s_button.draw();
		e_button.draw();
	}
};



class stageselectmgr{
public:
	class stageselectparts{
	public:

		int x, y, num, width, height;
		double alpha, taralpha;

		stageselectparts(){
			init();
		}

		void init(){
			width = 64;
			height = 64;
			alpha = 0;
			taralpha = 100;
		}

		void setxy(int xx, int yy){
			x = xx;
			y = yy;
		}

		bool IsOnMouse(){
			if (Func::DotAndRect(Input::mousex_(), Input::mousey_(), x - width / 2, y - height / 2, x + width / 2, y + height / 2)){
				alpha = 200;
				if (Input::keydown(250)){
					alpha = 255;
					return true;
				}
			}
			return false;
		}


		void draw(){
			Func::moverate(alpha, taralpha, 0.03);
			Draw_::exrot(x, y, 2.0, 0.0, Graph::handle("rect32"), alpha);
			SetDrawBright(255, 128, 0);
			Draw_::center(x, y, GraphDiv::handle("icon64", num), 180);
			SetDrawBright(255, 255, 255);
		}
	};


	class startbutton{
	public:
		bool IsActive;
		int x, y, width, height;

		startbutton(){
			IsActive = false;
			x = ScreenWidth / 2;
			y = 500;
			width = 800;
			height = 50;
		}

		void update(){
			bool preIsActive = IsActive;
			if (Func::DotAndRect(Input::mousex_(), Input::mousey_(), x - width / 2, y - height / 2, x + width / 2, y + height / 2)){
				IsActive = true;
				//マウスクリックされたら次のシーケンスに進む
				if (Input::keydown(250)){
					stateshift();
				}
			}
			else{
				IsActive = false;
			}

			if (preIsActive == false && IsActive == true){
				Sound::playback("menumove");
			}
		}

		void stateshift();

		void draw(){
			Draw_::centerbox(x, y, width, height, 0xFFFFFF, 100 + 50 * sin(Input::eframe() * 0.06));

			if (IsActive){
				Draw_::centerbox(x, y, width, height, 0xFFFFFF, 150);
			}

			Draw_::exrot(x, y, 1.0, 0.0, Graph::handle("s_select_start"), 255);
		}
	};


	class select_cursor{
	public:
		stageselectparts* tgt;
		double x, y;

		select_cursor(){
			init();
		}

		void init(){
			x = ScreenWidth / 2;
			y = ScreenHeight / 2;
		}

		void update(){
			Func::moverate(x, y, tgt->x, tgt->y, 0.2, 0.3);

		}

		void draw(){
			auto sinframe = [](double base, double a, double omega){
				return base + a * sin(omega * Input::eframe());
			};
			Draw_::exrot(x, y, 1.0, 0.0, Graph::handle("icon_frame"), sinframe(150, 50, 0.1));
		}
	};



	double basex, basey, iconspace;
	int stagenum;
	int eframe;
	int nowselect;

	backloop1024 back;
	startbutton s_button;
	select_cursor cursor;
	std::vector<stageselectparts> v;

	stageselectmgr(){
		basex = ScreenWidth / 2;
		basey = ScreenHeight / 2 + 20;
		stagenum = 10;
		nowselect = 0;
		back.setgh(Graph::handle("s_select_bk_ef"));
		init();
	}


	void init(){
		iconspace = 1024;
		eframe = 0;
		back.init();
		v.clear();
		for (int i = 0; i < stagenum; i++){
			v.emplace_back(stageselectparts());
		}
		for (int i = 0; i < stagenum; i++){
			v[i].num = i;
		}
		iconmove();
		cursor.tgt = &(v[nowselect]);
	}

	void update(){
		eframe++;
		back.update(0.0f, 0.001f);
		s_button.update();
		iconmove();
		int preselect = nowselect;
		for (int i = 0; i < (int)v.size(); i++){
			if (v[i].IsOnMouse()){
				nowselect = i;
			}
		}
		movewasd();
		cursor.tgt = &(v[nowselect]);
		if (preselect != nowselect){
			v[nowselect].alpha = 255;
			PlaySoundMem(Sound::handle("menumove"), DX_PLAYTYPE_BACK);
		}

		cursor.update();

		//開始の位置（画面外側）から所定の位置に移動
		Func::moverate(iconspace, 130.0, 0.1, 0.3);
	}

	//wasdで移動
	void movewasd(){
		if (Input::keydown(KEY_INPUT_W)){
			if (nowselect > 4){
				nowselect -= 5;
			}
		}
		else if (Input::keydown(KEY_INPUT_S)){
			if (nowselect < 5){
				nowselect += 5;
			}
		}
		else if (Input::keydown(KEY_INPUT_A)){
			if (nowselect > 0 && nowselect != 5){
				nowselect--;
			}
		}
		else if (Input::keydown(KEY_INPUT_D)){
			if (nowselect < stagenum - 1 && nowselect != 4){
				nowselect++;
			}
		}
	}

	void iconmove(){
		int num = 0;
		for (int y = -1; y < 2; y += 2){
			for (int x = -2; x < 3; x++){
				v[num].setxy(basex + iconspace * x, basey + iconspace * y * 0.45);
				v[num].num = num;
				num++;
			}
		}
	}

	void draw(){
		Draw_::normal(0, 0, Graph::handle("s_selectback"), 255);
		back.draw(128);
		for (auto& i : v){ i.draw(); }
		cursor.draw();
		s_button.draw();
		Draw_::centertext(400, 140, 0x444444, Font::handle("SegoeUI20"),
			"現在選択 : Stage " + std::to_string(nowselect + 1), 255);
		Draw_::centertext(400, 175, 0x444444, Font::handle("SegoeUI16"),
			"マウスでステージを選択し、SELECTを押して決定して下さい。", 255);
		std::vector<std::string> stagetitle;
		stagetitle.emplace_back("tutorial");
		stagetitle.emplace_back("light wing");
		stagetitle.emplace_back("bomb assertion");
		stagetitle.emplace_back("devided split");
		stagetitle.emplace_back("assault crimson");

		stagetitle.emplace_back("merrygoround");
		stagetitle.emplace_back("mother's theory");
		stagetitle.emplace_back("attractor eye");
		stagetitle.emplace_back("initial ray");
		stagetitle.emplace_back("world rebirth");
		Draw_::centertext(cursor.x, cursor.y + 45, 0x444444, Font::handle("SegoeUI16"),
			"s" + std::to_string(nowselect + 1) + " : " + stagetitle[nowselect], 255);
	}
};



class weaponselectmgr{
public:

	//それぞれのアイコン用クラス
	class weaponparts{
	public:
		//typeはmainかsubか
		int num, type, width, height;
		double x, y, tarx, tary;
		double alpha, taralpha;

		weaponparts(int n, int t){
			num = n;
			type = t;
			init();
		}

		void init(){
			x = ScreenWidth / 2;
			y = ScreenHeight / 2;
			width = 64;
			height = 64;
			alpha = 128;
			taralpha = 128;
		}

		void setxy(int xx, int yy){
			tarx = xx;
			tary = yy;
		}

		void update(int& nowselect){
			if (Func::DotAndRect(Input::mousex_(), Input::mousey_(), x - width / 2, y - height / 2, x + width / 2, y + height / 2)){
				alpha = 200;
				//マウスが押されたら
				if (Input::keydown(250)){
					nowselect = num;
					alpha = 255;
				}
			}
			Func::moverate(x, y, tarx, tary, 0.2);
			Func::moverate(alpha, taralpha, 0.04);
		}

		void draw(){
			Draw_::exrot(x, y, 2.0, 0.0, Graph::handle("rect32"), alpha);
			SetDrawBright(0, 0, 0);
			Draw_::center(x, y, GraphDiv::handle("weapon64", num + type * 6), 255);
			SetDrawBright(255, 255, 255);
		}
	};

	//画面下・決定ボタン
	class startbutton{
	public:
		bool IsActive;
		int x, y, width, height;

		startbutton(){
			IsActive = false;
			x = ScreenWidth / 2;
			y = 500;
			width = 800;
			height = 50;
		}

		void update(){
			bool preIsActive = IsActive;
			if (Func::DotAndRect(Input::mousex_(), Input::mousey_(), x - width / 2, y - height / 2, x + width / 2, y + height / 2)){
				IsActive = true;
				//マウスクリックされたら次のシーケンスに進む
				if (Input::keydown(250)){
					stateshift();
				}
			}
			else{
				IsActive = false;
			}

			if (preIsActive == false && IsActive == true){
				Sound::playback("menumove");
			}
		}

		void stateshift();

		void draw(){
			Draw_::centerbox(x, y, width, height, 0x000000, 100 + 50 * sin(Input::eframe() * 0.06));

			if (IsActive){
				Draw_::centerbox(x, y, width, height, 0x000000, 150);
			}

			Draw_::exrot(x, y, 1.0, 0.0, Graph::handle("w_select_start"), 255);
		}
	};

	class select_cursor{
	public:
		weaponparts* tgt;
		double x, y;

		select_cursor(){
			init();
		}

		void init(){
			x = ScreenWidth / 2;
			y = ScreenHeight / 2;
		}

		void update(weaponparts* t){
			tgt = t;
			Func::moverate(x, y, tgt->x, tgt->y, 0.4, 1.0);
		}

		void draw(){
			Draw_::exrot(x, y, 1.0, 0.0, Graph::handle("icon_frame"), 150 + 50 * sin(Input::eframe() * 0.1));
		}
	};

	double main_basex, main_basey;
	double sub_basex, sub_basey;
	double iconspacex;
	int mainw_nowselect;
	int subw_nowselect;
	int focus;//mainとsubどっちを選んでいるか
	const int str_yshift = 80;//文字とアイコンの基準座標の差
	int eframe;

	backloop1024 back;
	startbutton s_button;
	select_cursor mainw_cursor;
	select_cursor subw_cursor;
	std::vector<weaponparts> mainw_icon;
	std::vector<weaponparts> subw_icon;


	weaponselectmgr(){
		main_basex = ScreenWidth / 2;
		main_basey = 240;
		sub_basex = ScreenWidth / 2;
		sub_basey = 390;
		iconspacex = 100;
		back.setgh(Graph::handle("w_select_bk_ef"));
		focus = 0;
		mainw_nowselect = 0;
		subw_nowselect = 0;

		init();
	}

	void init(){
		eframe = 0;
		mainw_icon.clear();
		subw_icon.clear();

		for (int i = 0; i < MainWeaponNum; i++){
			mainw_icon.emplace_back(weaponparts(i, 0));
		}
		for (auto i = mainw_icon.begin(); i < mainw_icon.end(); i++){
			i->setxy((i->num - (MainWeaponNum - 1) / 2.0) * iconspacex + main_basex, main_basey);
		}
		for (int i = 0; i < SubWeaponNum; i++){
			subw_icon.emplace_back(weaponparts(i, 1));
		}
		for (auto i = subw_icon.begin(); i < subw_icon.end(); i++){
			i->setxy((i->num - (SubWeaponNum - 1) / 2.0) * iconspacex + sub_basex, sub_basey);
		}
	}

	void update(){
		eframe++;
		int mainw_preselect = mainw_nowselect;
		int subw_preselect = subw_nowselect;
		int prefocus = focus;
		back.update(0.0005f, 0.0f);
		movewasd();
		for (auto &i : mainw_icon) { i.update(mainw_nowselect); }
		for (auto &i : subw_icon) { i.update(subw_nowselect); }
		mainw_cursor.update(&mainw_icon[mainw_nowselect]);
		subw_cursor.update(&subw_icon[subw_nowselect]);
		//選択しているものが違えば音を鳴らす
		if (mainw_preselect != mainw_nowselect || subw_preselect != subw_nowselect || prefocus != focus){
			PlaySoundMem(Sound::handle("menumove"), DX_PLAYTYPE_BACK);
		}
		s_button.update();

	}

	void movewasd(){
		if (Input::keydown(KEY_INPUT_W) && focus == 1){
			focus = 0;
			mainw_icon[mainw_nowselect].alpha = 255;
		}
		else if (Input::keydown(KEY_INPUT_S) && focus == 0){
			focus = 1;
			subw_icon[subw_nowselect].alpha = 255;
		}

		if (focus == 0){
			int mainw_preselect = mainw_nowselect;
			if (Input::keydown(KEY_INPUT_A)){
				mainw_nowselect--;
			}
			else if (Input::keydown(KEY_INPUT_D)){
				mainw_nowselect++;
			}
			if (mainw_nowselect < 0){
				mainw_nowselect = 0;
			}
			if (mainw_nowselect >= MainWeaponNum){
				mainw_nowselect = MainWeaponNum - 1;
			}
			if (mainw_preselect != mainw_nowselect){
				mainw_icon[mainw_nowselect].alpha = 255;
			}
		}
		else{
			int subw_preselect = subw_nowselect;
			if (Input::keydown(KEY_INPUT_A)){
				subw_nowselect--;
			}
			else if (Input::keydown(KEY_INPUT_D)){
				subw_nowselect++;
			}
			if (subw_nowselect < 0){
				subw_nowselect = 0;
			}
			if (subw_nowselect >= SubWeaponNum){
				subw_nowselect = subw_nowselect - 1;
			}
			if (subw_preselect != subw_nowselect){
				subw_icon[subw_nowselect].alpha = 255;
			}
		}
	}

	void draw();

};




class resultmgr{
public:

	class to_title{
	public:
		bool IsActive;
		int x, y, width, height;

		void stateshift();

		to_title(){
			IsActive = false;
			x = ScreenWidth / 4 * 3 + 20;
			y = 535;
			width = 380;
			height = 60;
		}

		void update(){
			bool preIsActive = IsActive;
			if (Func::DotAndRect(Input::mousex_(), Input::mousey_(), x - width / 2, y - height / 2, x + width / 2, y + height / 2)){
				IsActive = true;
				if (Input::keydown(250)){
					stateshift();
				}
			}
			else{
				IsActive = false;
			}
			if (preIsActive == false && IsActive == true){
				Sound::playback("menumove");
			}
		}

		void draw(){
			Draw_::centerbox(x, y, width, height, 0x000000, 180);
			Draw_::centerbox(x, y, width, height, Func::HSVtoRGB(0, 0, 128 + 128 * sin(Input::eframe() * 0.05)), 64);
			if (IsActive){
				Draw_::centerbox(x, y, width, height, Func::HSVtoRGB(Input::eframe()*1.5, 255, 255), 128);
			}
			Draw_::centertext(x, y - 25, 0xFFFFFF, Font::handle("SegoeUI40"), "To Title", 255);

		}
	};

	class to_w_select{
	public:
		bool IsActive;
		int x, y, width, height;

		void stateshift();

		to_w_select(){
			IsActive = false;
			x = ScreenWidth / 4 - 20;
			y = 535;
			width = 380;
			height = 60;
		}

		void update(){
			bool preIsActive = IsActive;
			if (Func::DotAndRect(Input::mousex_(), Input::mousey_(), x - width / 2, y - height / 2, x + width / 2, y + height / 2)){
				IsActive = true;
				if (Input::keydown(250)){
					stateshift();
				}
			}
			else{
				IsActive = false;
			}
			if (preIsActive == false && IsActive == true){
				Sound::playback("menumove");
			}

		}

		void draw(){
			Draw_::centerbox(x, y, width, height, 0x000000, 180);
			Draw_::centerbox(x, y, width, height, Func::HSVtoRGB(0, 0, 128 + 128 * sin(Input::eframe() * 0.05)), 64);
			if (IsActive){
				Draw_::centerbox(x, y, width, height, Func::HSVtoRGB(Input::eframe()*1.5, 255, 255), 128);
			}
			Draw_::centertext(x, y - 25, 0xFFFFFF, Font::handle("SegoeUI40"), "To WeaponSelect", 255);
		}
	};


	resultef ef;
	to_title to_title_;
	to_w_select to_w_select_;
	int newrank;

	void addrank();

	resultmgr(){
		init();
	}

	void init();

	void update();

	void draw();
};


