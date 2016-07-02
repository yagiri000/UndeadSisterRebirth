#include "manager.h"

void titlemgr::startbutton::stateshift(){
	manager::get().weaponselect_.init();

	Sound::playback("menuenter");
	Sound::playbgm("select");

	SetDrawScreen(Screen::get().trail);
	manager::get().title_.draw();
	SetDrawScreen(DX_SCREEN_BACK);
	manager::get().gamestate_ = manager::weaponselect;
}


void titlemgr::exitbutton::stateshift(){
	manager::get().gamestate_ = manager::exit;
}


//武器選択画面の決定ボタンが押された時の処理
void weaponselectmgr::startbutton::stateshift(){
	manager::get().stageselect_.init();
	Sound::playback("menuenter");

	manager::get().weapon_.init();
	auto &p = manager::get().weaponselect_;
	manager::get().weapon_.setweapon(p.mainw_nowselect, p.subw_nowselect);

	SetDrawScreen(Screen::get().trail);
	manager::get().weaponselect_.draw();
	SetDrawScreen(DX_SCREEN_BACK);
	manager::get().gamestate_ = manager::stageselect;
}

void weaponselectmgr::draw(){
	Draw_::normal(0, 0, Graph::handle("w_selectback"), 255);
	back.draw(16, DX_BLENDMODE_ADD);

	Draw_::centerbox(main_basex, main_basey - str_yshift + 10, 500, 32, 0x000000, 100);
	Draw_::centerbox(main_basex, sub_basey - str_yshift + 10, 500, 32, 0x000000, 100);
	Draw_::centertext(main_basex, main_basey - str_yshift, 0xFFFFFF, Font::handle("SegoeUI20"), 
		std::string("MAIN WEAPON : ") + manager::get().weapon_.mainvec[mainw_nowselect]->name, 255);
	Draw_::centertext(sub_basex, sub_basey - str_yshift, 0xFFFFFF, Font::handle("SegoeUI20"), 
		std::string("SUB WEAPON : ") + manager::get().weapon_.subvec[subw_nowselect]->name, 255);
	Draw_::centerbox(main_basex, main_basey, 700, 96, 0x000000, 100);
	Draw_::centerbox(sub_basex, sub_basey, 700, 96, 0x000000, 100);
	for (auto &i : mainw_icon) { i.draw(); }
	for (auto &i : subw_icon) { i.draw(); }
	mainw_cursor.draw();
	subw_cursor.draw();
	s_button.draw();
	//Draw_::centertext(400, 0, 0xFFFFFF, Font::handle("SegoeUI20"), std::string("MAIN : ") + std::to_string(mainw_nowselect) + std::string("  SUB : ") + std::to_string(subw_nowselect), 255, 1);
}


//ステージ選択画面の決定ボタンが押された時の処理
void stageselectmgr::startbutton::stateshift(){
	manager::get().weaponselect_.init();
	Sound::playback("menuenter");
	Sound::playbgm_once("stagestart");

	Screen::get().clear_blood();
	Screen::get().clear_fire();

	SetDrawScreen(Screen::get().trail);
	manager::get().stageselect_.draw();
	SetDrawScreen(DX_SCREEN_BACK);

	manager::get().init();
	manager::get().stage_.init();
	manager::get().str_log_.init();

	manager::get().stage_.setstage(manager::get().stageselect_.nowselect);

	Input::setAllzeroframe(10);
	manager::get().gamestate_ = manager::gamemain;
}

//ステージ終了or死亡時に呼ばれる関数
void resultmgr::addrank(){
	std::string weaponlog;
	weaponlog += manager::get().weapon_.main->name;
	weaponlog += "/";
	weaponlog += manager::get().weapon_.sub->name;
	newrank = Datamgr::get().add(manager::get().stage_.stagenum, manager::get().scoremgr_.score, weaponlog);
}

void resultmgr::init(){
	newrank = -1;
	ef.init();
}

void resultmgr::update(){
	ef.update();
	to_title_.update();
	to_w_select_.update();
}

void resultmgr::draw(){
	auto& s = manager::get().scoremgr_;

	Draw_::normal(0, 0, Graph::handle("resultback"), 255);


	if ( ((int)s.score) % 2 == 0){
		SetDrawScreen(Screen::get().blood);
		ef.draw();
		SetDrawScreen(DX_SCREEN_BACK);
	}
	else{
		ef.draw();
	}

	Screen::get().update_result();
	Screen::get().DrawtoBACK(Screen::get().blood, DX_BLENDMODE_SUB, 255);

	Draw_::centerbox(400, 70, 800, 60, 0x000000, 160);
	Draw_::center(400, 70, Graph::handle("result_str"), 255);

	int y = 150;
	int yp = 45;

	auto drawstr_box = [](int y, std::string s1, std::string s2)
	{
		int x1 = 200;
		int x2 = 600;
		int col = 0xFFFFFF;
		Draw_::centerbox(400, y + 12, 800, 32, 0x000000, 160);
		Draw_::text(x1, y, col, Font::handle("SegoeUI20"),	s1, 255);
		Draw_::righttext(x2, y, col, Font::handle("SegoeUI20"),	s2, 255);
	};

	auto time_str = [](int frame){
		int sec = frame / 60;
		if ((sec % 60) < 10){
			return std::to_string((int)(sec / 60)) +
				":0" +
				std::to_string((int)(sec % 60));
		}
		else{
			return std::to_string((int)(sec / 60)) +
				":" +
				std::to_string((int)(sec % 60));
		}
	};

	drawstr_box(y, "撃破数  :", std::to_string(s.killnum));
	y += yp;
	drawstr_box(y, "被ダメージ数  :", std::to_string(s.damagenum));
	y += yp;
	drawstr_box(y, "クリア時間  :", time_str(s.eframe));
	y += yp;
	drawstr_box(y, "総合スコア  :", std::to_string((int)(s.score)));

	int yshift = -10;
	Draw_::centerbox(400, 425 + yshift, 800, 130, 0x000000, 160);
	Draw_::centertext(400, 366 + yshift, 0xFF8800, Font::handle("SegoeUI20"),
		"Stage" + std::to_string(manager::get().stage_.stagenum + 1) + " : Ranking", 255);


	for (int i = 0; i < 3; i++){
		int y2 = 394 + i * 30 + yshift;
		Draw_::text(220, y2, 0xFFFFFF, Font::handle("SegoeUI20"),
			std::to_string(i + 1) + " : " + std::to_string(Datamgr::get().stage[manager::get().stage_.stagenum].score[i]) + " pt", 255);
		Draw_::text(360, y2, 0xFFFFFF, Font::handle("SegoeUI20"), Datamgr::get().stage[manager::get().stage_.stagenum].weaponlog[i], 255);
		if (newrank == i){
			Draw_::righttext(215, y2 + 2, 0xFF8800, Font::handle("SegoeUI16"), "ハイスコア更新！", 128 + 128 * sin(Input::eframe() * 0.1));
		}
	}

	to_title_.draw();
	to_w_select_.draw();
}

void resultmgr::to_title::stateshift(){
	manager::get().init();

	SetDrawScreen(Screen::get().trail);
	ClearDrawScreen();
	SetDrawScreen(DX_SCREEN_BACK);

	manager::get().gamestate_ = manager::pretitle;
}

void resultmgr::to_w_select::stateshift(){
	manager::get().init();

	SetDrawScreen(Screen::get().trail);
	manager::get().result_.draw();
	SetDrawScreen(DX_SCREEN_BACK);

	Sound::playbgm("select");

	manager::get().gamestate_ = manager::weaponselect;
}