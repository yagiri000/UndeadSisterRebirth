#include "manager.h"

void statusbar::init(){
	auto& p = manager::get().player_;
	auto& s = manager::get().saintstone_;
	d_hp = p.hpmax;
	d_stone = s.hpmax;
	mrate = srate = 100.0;
}

void statusbar::update(){

}

void statusbar::draw(){
	auto& p = manager::get().player_;
	auto& s = manager::get().saintstone_;
	auto& w = manager::get().weapon_;

	//案I
	//画面左上にHP,STONEバー　オレンジ・スカイブルーデザイン　グラデーション有り
	int basex = 180;
	int basey = 12;
	int posy2 = basey + 12;
	int height = 6;
	int barx = 55;
	double length = 230;
	Draw_::normal(basex, basey, Graph::handle("bar_back"), 255);
	Draw_::box(basex + barx, posy2, basex + barx + length, posy2 + height, 0x552f1f, 220);
	if (p.hp > 0){
		Func::moverate(d_hp, p.hp, 0.1, 0.5);
		Draw_::modi2(basex + barx, posy2, basex + barx + length * d_hp / p.hpmax, posy2 + height, Graph::handle("bar_hp"), 220);
	}

	posy2 += 15;
	Draw_::box(basex + barx, posy2, basex + barx + length, posy2 + height, 0x233d53, 220);
	if (s.hp > 0){
		Func::moverate(d_stone, s.hp, 0.1, 0.5);
		Draw_::modi2(basex + barx, posy2, basex + barx + length * d_stone / s.hpmax, posy2 + height, Graph::handle("bar_stone"), 220);
	}

	int basex2 = basex + 305;
	int basey2 = basey;
	int dy_cir = 23;
	int dx_str = 1;
	int dy_str = 14;
	if (w.main->bullet > 0){
		Func::moverate(mrate, (double)w.main->bullet / w.main->bulletmax * 100.0, 0.2, 0.5);
	}
	else{
		Func::moverate(mrate, 100.0 - (double)w.main->reloadcool / w.main->reloadneed * 100.0, 0.2, 0.5);
	}
	if (w.sub->bullet > 0){
		Func::moverate(srate, (double)w.sub->bullet / w.sub->bulletmax * 100.0, 0.2, 0.5);
	}
	else{
		Func::moverate(srate, 100.0 - (double)w.sub->reloadcool / w.sub->reloadneed * 100.0, 0.2, 0.5);
	}
	Draw_::normal(basex2, basey2, Graph::handle("bar_wback"), 255);
	Draw_::circlegauge(basex2 + 28, basey2 + dy_cir, mrate, Graph::handle("bar_wmain"), 220);
	Draw_::circlegauge(basex2 + 112, basey2 + dy_cir, srate, Graph::handle("bar_wsub"), 220);
	Draw_::centertext(basex2 + dx_str + 28, basey2 + dy_str, 0xdb8b67, Font::handle("SegoeUI16"), w.bulletnum_main(), 240);
	Draw_::centertext(basex2 + dx_str + 112, basey2 + dy_str, 0xacd0e5, Font::handle("SegoeUI16"), w.bulletnum_sub(), 240);




	auto time_str = [](int frame){
		int sec = frame / 60;
		if ((sec % 60) < 10){
			return std::to_string((int)(sec / 60)) + ":0" + std::to_string((int)(sec % 60));
		}
		else{
			return std::to_string((int)(sec / 60)) + ":" + std::to_string((int)(sec % 60));
		}
	};

	int col_st = 0xFFFFFF;
	int x_st = 30;
	int y_st = 580;
	Draw_::center(x_st, y_st, Graph::handle("bar_sima64_40"), 255);
	Draw_::centertext(x_st, y_st - 20, col_st, Font::handle("SegoeUI16"), "Score", 240);
	Draw_::centertext(x_st, y_st, col_st, Font::handle("SegoeUI16"), std::to_string((int)manager::get().scoremgr_.score), 240);

	Draw_::center(800 - x_st, y_st, Graph::handle("bar_sima64_40"), 255);
	Draw_::centertext(800 - x_st, y_st - 20, col_st, Font::handle("SegoeUI16"), "Time", 240);
	Draw_::centertext(800 - x_st, y_st, col_st, Font::handle("SegoeUI16"), time_str(manager::get().stage_.now->eframe), 240);


}




void pausemgr::init(){

}

void pausemgr::update(){
	if (manager::get().gamestate_ == manager::gamemain){
		if (Input::keydown(KEY_INPUT_SPACE)){
			Sound::playback("menuenter");
			manager::get().gamestate_ = manager::pause;
			Input::setAllzeroframe(10);
		}
	}
	else if (manager::get().gamestate_ == manager::pause){
		if (Input::keydown(KEY_INPUT_SPACE)){
			Sound::playback("menucancel");
			manager::get().gamestate_ = manager::gamemain;
			Input::setAllzeroframe(10);
		}
		titlebutton.update();
	}
}

void pausemgr::draw(){
	if (manager::get().gamestate_ == manager::pause){
		Draw_::box(0, 0, 800, 600, 0x000000, 128);
		Draw_::centerbox(400, 300, 800, 80, 0xFFFFFF, 200);
		Draw_::centertext(400, 270, 0xFF3333, Font::handle("SegoeUI40"), "Pause", 255);
		Draw_::centertext(400, 310, 0xFF3333, Font::handle("SegoeUI16"), "スペースキーでゲームに戻る", 255);
		titlebutton.draw();
	}
}


void pausemgr::to_title::stateshift(){
	manager::get().init();

	SetDrawScreen(Screen::get().trail);
	ClearDrawScreen();
	SetDrawScreen(DX_SCREEN_BACK);

	manager::get().gamestate_ = manager::pretitle;
}

//TODO:この関数をステージ開始時に呼ばなければいけない
void dyingmgr::init(){
	eframe = 0;
}

void dyingmgr::update(){
	if (manager::get().gamestate_ == manager::gamemain){
		if (manager::get().player_.hp < 0.1 || manager::get().saintstone_.hp < 0.1){
			Sound::playbgm_once("dying");
			manager::get().result_.addrank();//スコア追加
			manager::get().str_log_.addbigstr("YOU DIE", "you may live as a zombie eternaly");
			manager::get().gamestate_ = manager::dying;
		}
	}
	else if (manager::get().gamestate_ == manager::dying){
		eframe++;
		if (eframe >= 300){

			SetDrawScreen(Screen::get().trail);
			manager::get().background_.draw();
			SetDrawScreen(Screen::get().trail);
			manager::get().player_.draw();
			SetDrawScreen(Screen::get().trail);
			manager::get().saintstone_.draw();
			SetDrawScreen(Screen::get().trail);
			manager::get().enemy_.draw();
			SetDrawScreen(Screen::get().trail);
			manager::get().effect_.draw();
			SetDrawScreen(Screen::get().trail);
			manager::get().str_log_.draw();
			SetDrawScreen(Screen::get().trail);
			manager::get().statusbar_.draw();
			SetDrawScreen(Screen::get().trail);
			manager::get().scoremgr_.draw();
			SetDrawScreen(Screen::get().trail);
			manager::get().stage_.draw();
			SetDrawScreen(DX_SCREEN_BACK);

			Screen::get().clear_blood();
			dx = dy = 0;
			Draw::setdxdy(dx, dy);

			Sound::playbgm("result");
			manager::get().gamestate_ = manager::result;
		}
	}
}

void dyingmgr::draw(){
	if (manager::get().gamestate_ == manager::dying){

	}
}