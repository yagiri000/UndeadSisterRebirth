#include "manager.h"

void Istage::init(){
	resetframe_wave();
}

void Istage::draw(){

	/*
	//TODO デバッグ情報を描画
	auto& e = manager::get().enemy_;
	int y = 300;
	int alpha = 180;
	Draw_::text(20, y += 20, 0xFFFFFF, Font::handle("SegoeUI20"),
		"Debug info", alpha);
	Draw_::text(20, y += 20, 0xFFFFFF, Font::handle("SegoeUI20"),
		"wave:" + std::to_string(wave), alpha);
	Draw_::text(20, y += 20, 0xFFFFFF, Font::handle("SegoeUI20"),
		"eframe:" + std::to_string(eframe), alpha);
	Draw_::text(20, y += 20, 0xFFFFFF, Font::handle("SegoeUI20"),
		"wframe:" + std::to_string(waveframe) +
		"/" + std::to_string(waveendframe[wave]), alpha);
	Draw_::text(20, y += 20, 0xFFFFFF, Font::handle("SegoeUI20"),
		"Score:" + std::to_string((int)manager::get().scoremgr_.score), alpha);
	Draw_::text(20, y += 20, 0xFFFFFF, Font::handle("SegoeUI20"),
		"Rate" + std::to_string((int)(manager::get().scoremgr_.comborate * 100.0)), alpha);
	Draw_::text(20, y += 20, 0xFFFFFF, Font::handle("SegoeUI20"),
		"ENEMY:" + std::to_string((int)e.v.size()), alpha);
	Draw_::text(20, y += 20, 0xFFFFFF, Font::handle("SegoeUI20"),
		"EFFECT:" + std::to_string((int)manager::get().effect_.v.size()), alpha);
	if (waveendframe[wave] < waveframe){
		Draw_::text(20, y += 20, 0xFFFFFF, Font::handle("SegoeUI20"), "now : waveend", alpha);
	}
	*/

}

bool Istage::Isenemyzero(){
	return (int)manager::get().enemy_.v.size() == 0;
}

void Istage::stageend(){

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

	//スコアランキング更新
	manager::get().result_.addrank();

	Sound::playbgm("result");

	manager::get().gamestate_ = manager::result;
}

void Istage::stageending(){
	if (waveframe == 1){
		manager::get().scoremgr_.eframe = eframe;
		Sound::playbgm_once("stageend");
		manager::get().str_log_.addbigstr("STAGE END", "zombies were destroyed");
	}
	if (waveframe > 300){
		stageend();
	}
}

void Istage::advancewave(){
	if (wave == 0){
		Sound::playbgm("stagebgm");
	}
	wave++;
	waveframe = 0;
	//TODO デバッグ用
	//manager::get().str_log_.add("wave advanced");
}


stage0::stage0(){
	waveendframe.emplace_back(300);
	waveendframe.emplace_back(900);
	waveendframe.emplace_back(300);
	waveendframe.emplace_back(99999);
	waveendframe.emplace_back(99999);
	init();
}

void stage0::init(){
	resetframe_wave();
}

void stage0::update(){
	auto& e = manager::get().enemy_;

	countframe();

	if (eframe == 1){
		manager::get().str_log_.addbigstr("Stage 0", "template ! template ! template !");
	}

	if (waveendframe[wave] < waveframe){
		if (Isenemyzero()){
			advancewave();
		}
	}
	else{
		if (wave == 0){

		}
		else if (wave == 1){
			if (modbool(waveframe, 60)){
				e.addmarge<emy_weak>(3.0 * sin(waveframe * 0.1), 100);
			}
			if (modbool(waveframe, 30)){
				e.addmarge<emy_normal>(3.0 * sin(waveframe * 0.1), 100);
			}
		}
		else if (wave == 2){
			stageending();
		}
	}
}


stage1::stage1(){
	waveendframe.emplace_back(300);
	waveendframe.emplace_back(1300);
	waveendframe.emplace_back(700);
	waveendframe.emplace_back(700);
	waveendframe.emplace_back(99999);
	init();
}

void stage1::init(){
	resetframe_wave();
}

void stage1::update(){
	auto& e = manager::get().enemy_;

	countframe();

	if (eframe == 1){
		manager::get().str_log_.addbigstr("Stage 1", "game start of tutorial");
	}

	if (waveendframe[wave] < waveframe){
		if (Isenemyzero()){
			advancewave();
		}
	}
	else{
		if (wave == 0){

		}
		else if (wave == 1){
			if (waveframe == 1){
				manager::get().str_log_.addupstr("WASDキーで移動");
			}
			if (waveframe == 600){
				manager::get().str_log_.addupstr("左クリックでメインウェポン使用");
			}
			if (waveframe == 1200){
				manager::get().str_log_.addupstr("武器によっては、押しっぱなしでオート連射。Rでリロード");
			}
			if (modbool(waveframe, 60)){
				e.addmarge<emy_weak>(3.0 * sin(waveframe * 0.1), 100);
			}
		}
		else if (wave == 2){
			if (waveframe == 1){
				manager::get().str_log_.addupstr("右クリックでサブウェポン使用。スペースキーでポーズ");
			}
			if (waveframe == 600){
				manager::get().str_log_.addupstr("青い石、または自分のHPが0になったらゲームオーバー");
			}
			if (modbool(waveframe, 40)){
				e.addmarge<emy_normal>(3.0 * sin(waveframe * 0.1), 100);
			}
		}
		else if (wave == 3){
			if (waveframe == 1){
				manager::get().str_log_.addupstr("短時間に多くの敵を倒し、ダメージを受けないほど高スコア");
			}
			if (waveframe == 600){
				manager::get().str_log_.addupstr("以上でチュートリアルは終わりです。敵をすべて倒すとステージクリアになります");
			}
			if (modbool(waveframe, 30)){
				e.addmarge<emy_weak>(3.0 * sin(waveframe * 0.1), 100);
			}
			if (modbool(waveframe, 60)){
				e.addmarge<emy_normal>(3.0 * sin(waveframe * 0.1), 100);
			}
		}
		else if (wave == 4){
			stageending();
		}
	}
}



stage2::stage2(){
	waveendframe.emplace_back(300);
	waveendframe.emplace_back(600);
	waveendframe.emplace_back(600);
	waveendframe.emplace_back(900);
	waveendframe.emplace_back(99999);
	init();
}

void stage2::init(){
	resetframe_wave();
}

void stage2::update(){

	auto& e = manager::get().enemy_;

	countframe();

	if (eframe == 1){
		manager::get().str_log_.addbigstr("Stage 2", "basement of ground of...");
	}

	if (waveendframe[wave] < waveframe){
		if (Isenemyzero()){
			advancewave();
		}
	}
	else{
		if (wave == 0){

		}
		else if (wave == 1){
			//600f
			if (modbool(waveframe, 90)){
				e.addmarge<emy_normal>(2.5 * sin(waveframe * 4.5), 64);
			}
			if (modbool(waveframe, 45)){
				e.addmarge<emy_weak>(2.5 * sin(waveframe * 4.5), 64);
			}
			if (waveframe == 600 - 1){
				for (int i = -20; i <= 20; i += 2){
					e.addmarge<emy_light>(i * 0.1, 64);
				}
			}
		}
		else if (wave == 2){
			//600f
			if (modbool(waveframe, 90)){
				e.addmarge<emy_normal>(1.5 * sin(waveframe * 4.5), 64);
			}
			if (modbool(waveframe, 30)){
				e.addmarge<emy_light>(2.0 + 1.0 * sin(waveframe * 4.9), 64);
				e.addmarge<emy_light>(-2.0 + 1.0 * sin(waveframe * 4.7), 64);
			}
		}
		else if (wave == 3){
			//900f
			if (modbool(waveframe, 20)){
				e.addmarge<emy_normal>(2.0 * sin(waveframe * 4.5), 64);
			}
			if (modbool(waveframe, 90)){
				e.addmarge<emy_light>(2.0 + 1.0 * sin(waveframe * 4.9), 64);
				e.addmarge<emy_light>(-2.0 + 1.0 * sin(waveframe * 4.7), 64);
			}
		}
		else if (wave == 4){
			stageending();
		}
	}
}



stage3::stage3(){
	waveendframe.emplace_back(300);
	waveendframe.emplace_back(300);
	waveendframe.emplace_back(600);
	waveendframe.emplace_back(1200);
	waveendframe.emplace_back(99999);
	init();
}

void stage3::init(){
	resetframe_wave();
}

void stage3::update(){

	auto& e = manager::get().enemy_;

	countframe();

	if (eframe == 1){
		manager::get().str_log_.addbigstr("Stage 3", "madness bommer of red dead read");

	}

	if (waveendframe[wave] < waveframe){
		if (Isenemyzero()){
			advancewave();
		}
	}
	else{
		if (wave == 0){

		}
		else if (wave == 1){
			if (waveframe == 1){
				e.addmarge<emy_bomb>(3.0 * sin(waveframe * 0.1), 100);
			}
			if (modbool(waveframe, 30)){
				e.addmarge<emy_fast>(3.0 * sin(waveframe * 0.1), 100);
			}
		}
		else if (wave == 2){
			if (modbool(waveframe, 15, 0)){
				e.addmarge<emy_normal>(1.0 * sin(waveframe * 0.1), 200);
			}
			if (modbool(waveframe, 60)){
				e.addmarge<emy_bomb>(2.0 + 1.0 * sin(waveframe * 0.1), 50);
				e.addmarge<emy_bomb>(-2.0 + 1.0 * sin(waveframe * 0.1), 50);
			}
		}
		else if (wave == 3){
			if (modbool(waveframe, 10, 0)){
				e.addmarge<emy_normal>(2.0 * sin(waveframe * 0.1), 200);
			}
			if (modbool(waveframe, 90)){
				e.addmarge<emy_bomb>(2.0 + 1.0 * sin(waveframe * 0.1), 50);
				e.addmarge<emy_bomb>(-2.0 + 1.0 * sin(waveframe * 0.1), 50);
			}
		}
		else if (wave == 4){
			stageending();
		}
	}
}



stage4::stage4(){
	waveendframe.emplace_back(300);
	waveendframe.emplace_back(500);
	waveendframe.emplace_back(600);
	waveendframe.emplace_back(900);
	waveendframe.emplace_back(1200);
	waveendframe.emplace_back(99999);
	init();
}

void stage4::init(){
	resetframe_wave();
}

void stage4::update(){
	auto& e = manager::get().enemy_;

	countframe();

	if (eframe == 1){
		manager::get().str_log_.addbigstr("Stage 4", "devided splash split");
	}

	if (waveendframe[wave] < waveframe){
		if (Isenemyzero()){
			advancewave();
		}
	}
	else{
		if (wave == 0){

		}
		else if (wave == 1){
			//
			if (modbool(waveframe, 80)){
				e.addmarge<emy_sin>(3.0 * sin(waveframe * 5.0), 32);
				e.addmarge<emy_sin>(2.0 + 1.0 * sin(waveframe * 5.0), 32);
				e.addmarge<emy_sin>(-2.0 + 1.0 * sin(waveframe * 5.0), 32);
			}
			if (modbool(waveframe, 100)){
				e.addmarge<emy_normal>(3.0 * sin(waveframe * 0.1), 100);
			}
		}
		else if (wave == 2){
			//600
			if (modbool(waveframe, 100)){
				e.addmarge<emy_devide>(3.0 * sin(waveframe * 0.1), 100);
			}
			if (modbool(waveframe, 90)){
				e.addmarge<emy_light>(2.0 + 1.0 * sin(waveframe * 0.1), 100);
				e.addmarge<emy_light>(-2.0 + 1.0 * sin(waveframe * 0.1), 100);
			}
		}
		else if (wave == 3){
			//900
			if (modbool(waveframe, 240)){
				e.addmarge<emy_devide>(3.0 * sin(waveframe * 0.1), 100);
			}
			if (modbool(waveframe, 30)){
				e.addmarge<emy_normal>(3.0 * sin(waveframe * 0.1), 100);
			}
		}
		else if (wave == 4){
			//爆発＆分裂 1200
			if (modbool(waveframe, 105)){
				e.addmarge<emy_sin>(2.0 + 1.0 * sin(waveframe * 0.1), 100);
			}
			if (modbool(waveframe, 105)){
				e.addmarge<emy_bomb>(1.0 * sin(waveframe * 5.0), 100);
				e.addmarge<emy_devide>(1.0 * sin(waveframe * 5.0), 100);
			}
		}
		else{
			stageending();
		}
	}
}




stage5::stage5(){
	waveendframe.emplace_back(300);
	waveendframe.emplace_back(1200);
	waveendframe.emplace_back(800);
	waveendframe.emplace_back(700);
	waveendframe.emplace_back(9999);
	init();
}

void stage5::init(){
	resetframe_wave();
}

void stage5::update(){
	auto& e = manager::get().enemy_;

	countframe();

	if (eframe == 1){
		manager::get().str_log_.addbigstr("Stage 5", "assult crimson");

	}
	if (waveendframe[wave] < waveframe){
		if (Isenemyzero()){
			advancewave();
		}
	}
	else{
		if (wave == 0){

		}
		else if (wave == 1){
			//強襲 1200
			if (modbool(waveframe, 35)){
				e.addmarge<emy_rot_l>(0.5 * sin(waveframe * 5.0), 100);
			}
		}
		else if (wave == 2){
			if (modbool(waveframe, 60)){
				e.addmarge<emy_light>(3.0 * sin(waveframe * 5.0), 100);
				e.addmarge<emy_devide>(1.0 * sin(waveframe * 5.0), 100);
			}
		}
		else if (wave == 3){
			if (modbool(waveframe, 60)){
				e.addmarge<emy_light>(3.0 * sin(waveframe * 5.1), 100);
				e.addmarge<emy_rot_l>(3.0 * sin(waveframe * 5.2), 100);
				e.addmarge<emy_normal>(3.0 * sin(waveframe * 5.3), 100);
			}
		}
		else{
			stageending();
		}
	}
}


stage6::stage6(){
	waveendframe.emplace_back(300);
	waveendframe.emplace_back(600);
	waveendframe.emplace_back(1200);
	waveendframe.emplace_back(900);
	waveendframe.emplace_back(99999);
	init();
}

void stage6::init(){
	resetframe_wave();
}

void stage6::update(){
	auto& e = manager::get().enemy_;

	countframe();

	if (eframe == 1){
		manager::get().str_log_.addbigstr("Stage 6", "merrygoround planetarium");
	}

	if (waveendframe[wave] < waveframe){
		if (Isenemyzero()){
			advancewave();
		}
	}
	else{
		if (wave == 0){

		}
		else if (wave == 1){
			if (modbool(waveframe, 90)){
				e.addmarge<emy_rot_l>(3.0 * sin(waveframe * 0.1), 100);
				e.addmarge<emy_normal>(3.0 * sin(waveframe * 0.1), 100);
			}
			if (modbool(waveframe, 13)){
				e.addmarge<emy_goleft>(0.1 * sin(waveframe * 0.3), 100);
			}
		}
		else if (wave == 2){
			//1200f
			if (modbool(waveframe, 100)){
				e.addmarge<emy_rot_l>(1.8 * sin(waveframe * 5.0), 64);
			}
			if (modbool(waveframe, 30)){
				e.addmarge<emy_rot_l_tos>(2.5 * sin(waveframe * 5.0), 64);
			}
			if (modbool(waveframe, 100)){
				e.addmarge<emy_light>(-1.5 + 0.5 * sin(waveframe * 2.5), 64);
				e.addmarge<emy_light>(1.5 + 0.5 * sin(waveframe * 5.3), 64);
			}
		}
		else if (wave == 3){
			if (modbool(waveframe, 100)){
				e.addmarge<emy_rot_l_tos>(2.5 * sin(waveframe * 5.0), 64);
			}
			if (modbool(waveframe, 40)){
				e.addmarge<emy_sin>(1.0 * sin(waveframe * 0.1), 50);
				e.addmarge<emy_rot_l>(3.0 * sin(waveframe * 0.1), 100);
			}
		}
		else{
			stageending();
		}
	}
}




stage7::stage7(){
	waveendframe.emplace_back(300);
	waveendframe.emplace_back(600);
	waveendframe.emplace_back(1200);
	waveendframe.emplace_back(600);
	waveendframe.emplace_back(900);
	waveendframe.emplace_back(9999);
	init();
}
void stage7::init(){
	resetframe_wave();
}

void stage7::update(){
	auto& e = manager::get().enemy_;

	countframe();

	if (eframe == 1){

		manager::get().str_log_.addbigstr("Stage 7", "mother's theory");
	}
	if (waveendframe[wave] < waveframe){
		if (Isenemyzero()){
			advancewave();
		}
	}
	else{
		if (wave == 0){

		}
		else if (wave == 1){
			if (modbool(waveframe, 200)){
				e.addmarge<emy_mother>(1.0 * sin(waveframe * 0.1), 64);
			}
		}
		else if (wave == 2){
			//1200
			if (modbool(waveframe, 50)){
				e.addmarge<emy_rot_l>(2.0 * sin(waveframe * 5.0), 100);
			}
			if (modbool(waveframe, 200)){
				e.addmarge<emy_normal>(-2.0 + 1.0 * sin(waveframe * 5.0), 100);
				e.addmarge<emy_bomb>(1.0 * sin(waveframe * 5.0), 100);
			}
			if (modbool(waveframe, 300)){
				e.addmarge<emy_devide>(1.0 * sin(waveframe * 5.0), 100);
			}
		}
		else if (wave == 3){
			if (modbool(waveframe, 45)){
				e.addmarge<emy_sin>(2.0 + 1.0 * sin(waveframe * 3.4), 50);
				e.addmarge<emy_sin>(-2.0 + 1.0 * sin(waveframe * 3.3), 50);
			}
			if (modbool(waveframe, 90)){
				e.addmarge<emy_normal>(3.0 * sin(waveframe * 3.4), 100);
			}
		}
		else if (wave == 4){
			if (modbool(waveframe, 140)){
				e.addmarge<emy_sin>(2.0 + 1.0 * sin(waveframe * 3.4), 50);
				e.addmarge<emy_sin>(-2.0 + 1.0 * sin(waveframe * 3.3), 50);
			}
			if (modbool(waveframe, 310)){
				e.addmarge<emy_mother>(3.0 * sin(waveframe * 3.4), 100);
			}
		}
		else{
			stageending();
		}
	}
}




stage8::stage8(){
	waveendframe.emplace_back(300);
	waveendframe.emplace_back(800);
	waveendframe.emplace_back(800);
	waveendframe.emplace_back(800);
	waveendframe.emplace_back(600);
	waveendframe.emplace_back(9999);
	init();
}
void stage8::init(){
	resetframe_wave();
}
void stage8::update(){
	auto& e = manager::get().enemy_;

	countframe();

	if (eframe == 1){
		manager::get().str_log_.addbigstr("Stage 8", "extinction of attractor eye");
	}

	if (waveendframe[wave] < waveframe){
		if (Isenemyzero()){
			advancewave();
		}
	}
	else{
		if (wave == 0){

		}
		else if (wave == 1){
			//900f
			if (waveframe == 450){
				e.addmarge<emy_mother>(2.5 * sin(waveframe * 4.5), 64);
			}
			if (modbool(waveframe, 90)){
				e.addmarge<emy_normal>(2.5 * sin(waveframe * 4.5), 64);
			}
			if (400 < waveframe && waveframe < 430){
				double ex, ey;
				ex = ey = 512;
				Func::addVector(512 * 1.4, PI / 2 * sin(waveframe * 4.5), ex, ey);
				e.add<emy_light>(ex, ey);
			}
			if (800 < waveframe && waveframe < 830){
				double ex, ey;
				ex = ey = 512;
				Func::addVector(512 * 1.4, PI / 2 * sin(waveframe * 4.5), ex, ey);
				e.add<emy_light>(ex, ey);
			}
		}
		else if (wave == 2){
			if (modbool(waveframe, 80, 1)){
				e.addmarge<emy_rot_l>(2.5 * sin(waveframe * 3.5), 100);
			}
			if (modbool(waveframe, 80, 1)){
				//-1 < rate < 1
				auto f = [](double rate, double &x, double &y){
					x = 512 + 650 * cos(rate * PI / 2);
					y = 512 + 650 * sin(rate * PI / 2);
				};

				double ex, ey;
				f(sin(waveframe * 2.5), ex, ey);
				for (int i = 0; i < 6; i++){
					double px = ex, py = ey;
					Func::addVector(64, i * 60 * DegToRad, px, py);
					e.add<emy_normal>(px, py);
				}
			}
		}
		else if (wave == 3){
			if (modbool(waveframe, 35, 1)){
				e.addmarge<emy_moverot>(2.5 * sin(waveframe * 3.5), 100);
			}
			if (modbool(waveframe, 120, 1)){
				e.addmarge<emy_rot_l>(2.5 * sin(waveframe * 3.5), 100);
				e.addmarge<emy_bomb>(2.5 * sin(waveframe * 3.5), 100);
			}
			if (modbool(waveframe, 60, 1)){
				e.addmarge<emy_goleft>(0.2 * sin(waveframe * 3.5), 100);
			}
		}
		else if (wave == 4){
			if (waveframe == 500){
				e.addmarge<emy_mother>(0, 64);
			}
			if (modbool(waveframe, 120, 1)){
				e.addmarge<emy_rot_l>(2.5 * sin(waveframe * 3.5), 100);
				e.addmarge<emy_sin>(2.5 * sin(waveframe * 3.4), 100);
				e.addmarge<emy_moverot>(2.5 * sin(waveframe * 3.3), 100);
			}
			if (modbool(waveframe, 80, 1)){
				//-1 < rate < 1
				auto f = [](double rate, double &x, double &y){
					x = 512 + 650 * cos(rate * PI / 2);
					y = 512 + 650 * sin(rate * PI / 2);
				};

				double ex, ey;
				f(sin(waveframe * 2.5), ex, ey);
				for (int i = 0; i < 6; i++){
					double px = ex, py = ey;
					Func::addVector(128, i * 60 * DegToRad, px, py);
					e.add<emy_rot_l_tos>(px, py);
				}
			}
		}
		else{
			stageending();
		}
	}
}




stage9::stage9(){
	waveendframe.emplace_back(300);
	waveendframe.emplace_back(600);
	waveendframe.emplace_back(1200);
	waveendframe.emplace_back(1200);
	waveendframe.emplace_back(1200);
	waveendframe.emplace_back(99999);
	init();
}
void stage9::init(){
	resetframe_wave();
}
void stage9::update(){
	auto& e = manager::get().enemy_;

	countframe();

	if (eframe == 1){
		manager::get().str_log_.addbigstr("Stage 9", "initial ray became heavenly device");

	}

	if (waveendframe[wave] < waveframe){
		if (Isenemyzero()){
			advancewave();
		}
	}
	else{
		if (wave == 0){

		}
		else if (wave == 1){
			//600f
			if (modbool(waveframe, 200)){
				e.addmarge<emy_mother>(1.0 * sin(waveframe * 0.1), 64);
			}
		}
		else if (wave == 2){
			//1200f
			if (modbool(waveframe, 150)){
				e.addmarge<emy_solid>(1.0 * sin(waveframe * 5.0), 64);
			}
			if (modbool(waveframe, 50)){
				e.addmarge<emy_light>(3.3 * sin(waveframe * 5.0), 64);
			}
			if (modbool(waveframe, 300)){
				e.addmarge<emy_devide>(3.3 * sin(waveframe * 5.0), 64);
			}
		}

		else if (wave == 3){
			//1200f
			if (modbool(waveframe, 100)){
				e.addmarge<emy_rot_l>(2.5 * sin(waveframe * 5.0), 64);
			}
			if (modbool(waveframe, 30)){
				e.addmarge<emy_light>(-1.5 + 0.5 * sin(waveframe * 5.3), 64);
				e.addmarge<emy_light>(1.5 + 0.5 * sin(waveframe * 5.3), 64);
			}
		}
		else if (wave == 4){
			if (modbool(waveframe, 200)){
				e.addmarge<emy_solid>(1.0 * sin(waveframe * 5.0), 64);
				e.addmarge<emy_mother>(1.0 * sin(waveframe * 2.4), 64);
			}
		}
		else{
			stageending();
		}
	}
}



stage10::stage10(){
	waveendframe.emplace_back(300);
	waveendframe.emplace_back(800);
	waveendframe.emplace_back(1200);
	waveendframe.emplace_back(1200);
	waveendframe.emplace_back(1200);
	waveendframe.emplace_back(2200);
	waveendframe.emplace_back(99999);
	init();
}
void stage10::init(){
	resetframe_wave();
}

void stage10::update(){
	auto& e = manager::get().enemy_;

	countframe();

	if (eframe == 1){
		manager::get().str_log_.addbigstr("Stage 10", "R.E.B.I.R.T.H.");
	}

	if (waveendframe[wave] < waveframe){
		if (Isenemyzero()){
			advancewave();
		}
	}
	else{
		if (wave == 0){

		}
		else if (wave == 1){
			if (modbool(waveframe, 30)){
				e.addmarge<emy_sin>(2.5 * sin(waveframe * 4.3), 64);
			}
			if (modbool(waveframe, 45)){
				e.addmarge<emy_moverot>(2.5 * sin(waveframe * 4.5), 64);
			}
		}
		else if (wave == 2){
			if (modbool(waveframe, 120)){
				for (int i = 0; i < 1024; i += 128){
					e.add<emy_rot_l_tos>(i, 1024 + 64);
				}
			}
			if (modbool(waveframe, 20)){
				e.addmarge<emy_light>(2.5 * sin(waveframe * 4.5), 64);
			}
		}
		else if (wave == 3){
			if (waveframe == 1){
				e.addmarge<emy_boss>(0.0, 64);
			}
			if (modbool(waveframe, 45)){
				e.addmarge<emy_bomb>(2.5 * sin(waveframe * 4.5), 64);
			}
			if (modbool(waveframe, 45)){
				e.addmarge<emy_rot_l>(2.5 * sin(waveframe * 4.5), 64);
			}
		}
		else if (wave == 4){
			if (modbool(waveframe, 60)){
				e.addmarge<emy_normal>(2.5 * sin(waveframe * 4.5), 64);
			}
			if (modbool(waveframe, 120)){
				e.addmarge<emy_rot_l>(2.5 * sin(waveframe * 4.5), 64);
			}
			if (waveframe == 200 - 1 || waveframe == 600 - 1){
				for (int i = -20; i <= 20; i += 2){
					e.addmarge<emy_moverot>(i * 0.1, 64);
				}
			}
		}
		else if (wave == 5){
			if (modbool(waveframe, 350)){
				e.addmarge<emy_normal>(2.5 * sin(waveframe * 4.6), 64);
			}
			if (modbool(waveframe, 120)){
				e.addmarge<emy_light>(2.5 * sin(waveframe * 4.5), 64);
			}
			if (modbool(waveframe, 450)){
				e.addmarge<emy_rot_l>(2.5 * sin(waveframe * 4.7), 64);
			}
			if (modbool(waveframe, 250)){
				e.addmarge<emy_rot_l_tos>(2.5 * sin(waveframe * 4.8), 64);
			}
			if (modbool(waveframe, 460)){
				e.addmarge<emy_sin>(2.5 * sin(waveframe * 4.9), 64);
			}
			if (modbool(waveframe, 350)){
				e.addmarge<emy_moverot>(2.5 * sin(waveframe * 4.0), 64);
			}
			if (modbool(waveframe, 700)){
				e.addmarge<emy_mother>(2.5 * sin(waveframe * 4.2), 64);
			}
			if (modbool(waveframe, 500)){
				e.addmarge<emy_devide>(2.5 * sin(waveframe * 4.3), 64);
			}
		}
		else{
			stageending();
		}
	}
}


