#pragma once

#include "manager.h"
#include <memory>

void I_weapon::get_pos_angle(){
	x = manager::get().player_.x;
	y = manager::get().player_.y;
	angle = manager::get().player_.gunangle;
}


void I_weapon::r_reload(){
	if (Input::keydown(KEY_INPUT_R) && bullet != 0){
		manager::get().statusbar_.mrate = 0.0; //ステータスバーの表示メインウェポン弾数を0に(見た目の問題)
		bullet = 0;
		reloadcool = reloadneed;
		Sound::playback("reloadstart");
		manager::get().str_log_.add("*カチッ* " + name + "をリロード開始した。");
	}
}


//武器が弾を撃てるかどうかを返す
//引数はInput::keynow(250)などのキーの情報
bool I_weapon::shot(bool keyon){
	//リロード処理
	if (bullet <= 0 && Func::coolcount(reloadcool)){
		bullet = bulletmax;
		firecool = 0;
		Sound::playback("reloadend");
		manager::get().str_log_.add("*ガチャリッ* " + name + "をリロード完了。");
	}

	//弾発射処理
	if (bullet > 0 && Func::coolcount(firecool)){
		if (keyon){
			firecool = firerate - 1;
			bullet--;
			if (bullet <= 0){
				reloadcool = reloadneed;
				Sound::playback("reloadstart");
				manager::get().str_log_.add("*カチッ* " + name + "をリロード開始した。");
			}
			return true;
		}
	}
	return false;
}

void w_machinegun::init(){
	name = "サブマシンガン";
	firecool = 0, firerate = 6;
	reloadcool = 0;
	reloadneed = 60;
	bullet = 100;
	bulletmax = 100;
	atk = 1.0;
	knockbackdist = 3.0;
	range = 300;
	movespeedplus = 0.0;
}
void w_machinegun::update(){
	get_pos_angle();//位置更新・忘れないこと！！

	r_reload();//rでリロード

	if (shot(Input::keynow(250))){
		Sound::playback("machinegun");
		double sx, sy;
		Func::polartoxy(sx, sy, 25, angle);
		manager::get().effect_.add<fireflash>(x + sx, y + sy);
		for (int i = 0; i < 3; i++){
			manager::get().effect_.add<firesmoke>(x + sx, y + sy);
		}
		manager::get().damagearea_.addptr(std::make_shared<dm_lineone>(x + sx, y + sy, range, angle + Random::FRand(-0.1, 0.1), atk, knockbackdist));
	}
}
void w_machinegun::draw(){
	Draw::exrot3(x, y, -5, 8, 1, 1, angle, Graph::handle("gun"), 255);
}



void w_rifle::init(){
	name = "ライフル";
	firecool = 0, firerate = 3;
	reloadcool = 0;
	reloadneed = 30;
	bullet = 12;
	bulletmax = 12;
	atk = 5.0;
	knockbackdist = 64.0;
	range = 1200;
	movespeedplus = 0.0;
}
void w_rifle::update(){
	get_pos_angle();//位置更新・忘れないこと！！

	r_reload();//rでリロード

	if (shot(Input::keydown(250))){
		Sound::playback("rifle");
		double sx, sy;
		Func::polartoxy(sx, sy, 25, angle);
		manager::get().effect_.add<fireflash>(x + sx, y + sy);
		for (int i = 0; i < 3; i++){
			manager::get().effect_.add<firesmoke>(x + sx, y + sy);
		}
		manager::get().damagearea_.addptr(std::make_shared<dm_lineone>(x + sx, y + sy, range, angle, atk, knockbackdist));
	}
}
void w_rifle::draw(){
	Draw::exrot3(x, y, -5, 8, 1, 1, angle, Graph::handle("gun"), 255);
}




void w_shotgun::init(){
	name = "ショットガン";
	firecool = 0, firerate = 15;
	reloadcool = 0;
	reloadneed = 60;
	bullet = 20;
	bulletmax = 20;
	atk = 0.8;
	knockbackdist = 5.0;
	range = 150;
	movespeedplus = 0.0;
}
void w_shotgun::update(){
	get_pos_angle();//位置更新・忘れないこと！！

	r_reload();//rでリロード

	if (shot(Input::keynow(250))){
		Sound::playback("shotgun");
		double sx, sy;
		Func::polartoxy(sx, sy, 25, angle);
		manager::get().effect_.add<fireflash>(x + sx, y + sy);
		for (int i = 0; i < 30; i++){
			manager::get().effect_.add<firesmoke>(x + sx, y + sy);
		}
		for (int i = 0; i < 15; i++){
			manager::get().damagearea_.addptr(std::make_shared<dm_lineone>(x + sx, y + sy, range + Random::FRand(-50, 50), angle + Random::FRand(-0.4, 0.4), atk, knockbackdist));
		}
	}
}
void w_shotgun::draw(){
	Draw::exrot3(x, y, -5, 8, 1, 1, angle, Graph::handle("gun"), 255);
}


void w_firegun::init(){
	name = "火炎放射器";
	firecool = 0;
	firerate = 2;
	soundcool = 0;
	soundrate = 4;
	reloadcool = 0;
	reloadneed = 45;
	bullet = 300;
	bulletmax = 300;
	atk = 0.7;//8/10 -> 0.8
	knockbackdist = 2.2;
	range = 260;
	movespeedplus = 0.0;
}
void w_firegun::update(){
	get_pos_angle();//位置更新・忘れないこと！！

	r_reload();//rでリロード

	if (shot(Input::keynow(250))){
		double sx = x;
		double sy = y;
		Func::addVector(40, angle, sx, sy);
		for (int i = 0; i < 6; i++){
			auto efp = manager::get().effect_.add<flamethrow>(sx, sy);
			double angleplus = Random::FRandND(0, 0.26);
			if (abs(angleplus) > 0.6){
				angleplus = 0.0;
			}
			Func::addVector(13.0, angle + angleplus, efp->vx, efp->vy);
			efp->wait(Random::Rand(2));
		}

		//4回に一回判定＋音
		if (Func::coolcount(soundcool)){
			Sound::playback("flamethrow");
			soundcool += soundrate;
			manager::get().damagearea_.addptr(std::make_shared<dm_tlitbox>(sx, sy, range, angle, 45.0, atk, knockbackdist));
		}
	}
}
void w_firegun::draw(){
	Draw::exrot3(x, y, -5, 8, 1, 1, angle, Graph::handle("gun"), 255);
}



void w_chainsaw::init(){
	name = "チェーンソー";
	firecool = 0, firerate = 5;
	reloadcool = 0;
	reloadneed = 60;
	soundcool = 0;
	soundrate = 1;
	bullet = 999;
	bulletmax = 999;
	atk = 1.5;
	knockbackdist = 0.0;
	range = 64;
	movespeedplus = 0.0;
}
void w_chainsaw::update(){
	get_pos_angle();//位置更新・忘れないこと！！
	if (shot(Input::keynow(250))){
		if (Func::coolcount(soundcool)){
			Sound::playback("chainsaw");
			soundcool += soundrate;
		}
		double sx = x;
		double sy = y;
		Func::addVector(20, angle, sx, sy);
		manager::get().damagearea_.addptr(std::make_shared<dm_chainsaw>(sx, sy, range, angle, 30.0, atk, knockbackdist));
		bullet++;
	}
}
void w_chainsaw::draw(){
	Draw::exrot3(x, y, -5, 16, 1, 1, angle, Graph::handle("chainsaw"), 255);
}



void w_railgun::init(){
	name = "レールガン";
	firecool = 0, firerate = 6;
	reloadcool = 0;
	reloadneed = 75;
	bullet = 6;
	bulletmax = 6;
	atk = 5.0;
	knockbackdist = 0.0;
	range = 1200;
	movespeedplus = 0.0;
}
void w_railgun::update(){
	get_pos_angle();//位置更新・忘れないこと！！

	r_reload();//rでリロード

	if (shot(Input::keydown(250))){
		Sound::playback("railgun");
		double sx, sy;
		Func::polartoxy(sx, sy, 25, angle);
		for (int i = 25; i < (int)range; i += 10){
			double dx = 0;
			double dy = 0;
			Func::addVector(i, angle, dx, dy);
			manager::get().effect_.add<splash_thin>(x + dx, y + dy);
		}
		manager::get().damagearea_.addptr(std::make_shared<dm_lineall>(x + sx, y + sy, range, angle, atk, knockbackdist));
	}
}
void w_railgun::draw(){
	Draw::exrot3(x, y, -5, 8, 1, 1, angle, Graph::handle("gun"), 255);
}




void w_grenade::init(){
	name = "グレネード";
	firecool = 0, firerate = 6;
	reloadcool = 0;
	reloadneed = 1200;
	bullet = 3;
	bulletmax = 3;
	atk = 10.0;
	knockbackdist = 0.0;
	range = 100;
	movespeedplus = 0.0;
	vec.clear();
}
void w_grenade::update(){
	get_pos_angle();//位置更新・忘れないこと！！
	if (shot(Input::keydown(251))){
		Sound::playback("swing02");
		vec.emplace_back(grenadeparts(x, y, Input::mousex(), Input::mousey()));
	}

	for (auto i = vec.begin(); i < vec.end(); i++){
		i->etime++;
		i->update();
		if (i->etime == i->falltime){
			Sound::playback("bomb01");
			for (int j = 0; j < 18; j++){
				auto p = manager::get().effect_.add<grenadefire>(i->nowx, i->nowy);
				Func::polartoxy(p->vx, p->vy, Random::FRand(1.0, 12.0), (j * 20 + Random::FRand(50)) * DegToRad );
				manager::get().effect_.add<dotsplash>(i->nowx, i->nowy);
			}
			manager::get().damagearea_.addptr(std::make_shared<dm_circle>(i->nowx, i->nowy, range, atk, knockbackdist));
		}
	}
	
	auto rmv_iter = std::remove_if(vec.begin(), vec.end(),
		[](grenadeparts& i){
		return i.etime >= i.falltime;
	}
	);

	vec.erase(rmv_iter, vec.end());
}
void w_grenade::draw(){
	for (auto i = vec.begin(); i < vec.end(); i++){
		i->draw();
	}
	//Draw::text(100, 100, 0xFFFFFF, Font::handle("SegoeUI20"), std::to_string(vec.size()), 255);
}
void w_grenade::grenadeparts::update(){
	Vector2 ret;
	ret = Func::GetBezier2(Vector2(sx, sy), Vector2((sx + ex) / 2, (sy + ey) / 2 - 150), Vector2(ex, ey), (float)etime / falltime);
	nowx = ret.x;
	nowy = ret.y;
}
void w_grenade::grenadeparts::draw(){
	Draw::exrot(nowx, nowy, 1.0, Input::eframe() * 0.1, Graph::handle("ryudan"), 255);
}




void w_mine::init(){
	name = "地雷";
	firecool = 0, firerate = 6;
	reloadcool = 0;
	reloadneed = 960;
	bullet = 4;
	bulletmax = 4;
	atk = 20.0;
	knockbackdist = 0.0;
	range = 125;
	movespeedplus = 0.0;
	vec.clear();
}
void w_mine::update(){
	get_pos_angle();//位置更新・忘れないこと！！
	if (shot(Input::keydown(251))){
		Sound::playback("put01");
		vec.emplace_back(mineparts(x, y));
	}

	for (auto i = vec.begin(); i < vec.end(); i++){
		i->etime++;
		i->update();
		if (i->deleteflag == true){
			for (int j = 0; j < 50; j++){
				manager::get().effect_.add<grenadefire>(i->x, i->y);
				manager::get().effect_.add<dotsplash>(i->x, i->y);
			}
			Sound::playback("bomb01");
			manager::get().damagearea_.addptr(std::make_shared<dm_circle>(i->x, i->y, range, atk, knockbackdist));
		}
	}

	auto rmv_iter = std::remove_if(vec.begin(), vec.end(),
		[](mineparts& i){
		return i.deleteflag;
	}
	);

	vec.erase(rmv_iter, vec.end());
}
void w_mine::draw(){

	for (auto i = vec.begin(); i < vec.end(); i++){
		i->draw();
	}
}
void w_mine::mineparts::update(){
	auto &vec = manager::get().enemy_.v;

	for (auto &i = vec.begin(); i < vec.end(); i++){
		auto& obj = **i;
		if (Func::Circles(obj.x, obj.y, obj.r, x, y, 16)){
			deleteflag = true;
		}
	}
	
}
void w_mine::mineparts::draw(){
	Draw::exrot(x, y, 1.0, 0.0, Graph::handle("w_mine"), 235);
}



void w_molotov::init(){
	name = "火炎瓶";
	firecool = 0, firerate = 6;
	reloadcool = 0;
	reloadneed = 720;
	bullet = 1;
	bulletmax = 1;
	atk = 1.0;
	knockbackdist = -10;
	range = 120;
	movespeedplus = 0.0;
	vec.clear();
}
void w_molotov::update(){

	get_pos_angle();//位置更新・忘れないこと！！

	if (shot(Input::keydown(251))){
		Sound::playback("swing02");
		vec.emplace_back(parts(x, y, Input::mousex(), Input::mousey()));
	}

	for (auto i = vec.begin(); i < vec.end(); i++){
		i->etime++;
		i->update();
		if (i->state == 0 && i->etime == i->falltime){
			Sound::playback("glasscrash");
			Sound::playback("flamethrow");
			i->state = 1;
			i->etime = 0;
		}
		if (i->state == 1){
			for (int j = 0; j < 1; j++){
				double dx, dy;
				Random::RandInCircle(range, dx, dy);
				manager::get().effect_.add<molotovfire>(i->nowx + dx, i->nowy + dy);
			}
			if (i->etime % 20 == 0){
				manager::get().damagearea_.addptr(std::make_shared<dm_circle>(i->nowx, i->nowy, range, atk, knockbackdist));
			}
		}
	}

	auto rmv_iter = std::remove_if(vec.begin(), vec.end(),
		[](parts& i){
		return i.state == 1 && i.etime > 600;
	}
	);

	vec.erase(rmv_iter, vec.end());
}
void w_molotov::draw(){
	for (auto i = vec.begin(); i < vec.end(); i++){
		i->draw();
	}
}
void w_molotov::parts::update(){
	if (state == 0){
		Vector2 ret;
		ret = Func::GetBezier2(Vector2(sx, sy), Vector2((sx + ex) / 2, (sy + ey) / 2 - 150), Vector2(ex, ey), (float)etime / falltime);
		nowx = ret.x;
		nowy = ret.y;
	}

}
void w_molotov::parts::draw(){
	if (state == 0){
		Draw::exrot(nowx, nowy, 1.0, Input::eframe() * 0.1, Graph::handle("ryudan"), 255);
	}
}





void w_freeze::init(){
	name = "氷結弾";
	firecool = 0, firerate = 6;
	reloadcool = 0;
	reloadneed = 900;
	bullet = 1;
	bulletmax = 1;
	atk = 0.0;
	knockbackdist = 0.0;
	range = 200;
	movespeedplus = 0.0;
	vec.clear();
}
void w_freeze::update(){
	get_pos_angle();//位置更新・忘れないこと！！

	if (shot(Input::keydown(251))){
		Sound::playback("swing02");
		vec.emplace_back(parts(x, y, Input::mousex(), Input::mousey()));
	}

	for (auto i = vec.begin(); i < vec.end(); i++){
		i->etime++;
		i->update();
		if (i->state == 0 && i->etime == i->falltime){
			Sound::playback("glasscrash");
			i->state = 1;
			i->etime = 0;
		}
		if (i->state == 1){
			manager::get().effect_.add<freezeef>(i->nowx, i->nowy);

			if (i->etime % 20 == 0){
				auto &vec = manager::get().enemy_.v;

				for (auto &j = vec.begin(); j < vec.end(); j++){
					auto& obj = **j;
					if (Func::Circles(obj.x, obj.y, obj.r, i->nowx, i->nowy, range)){
						obj.wait = 60;
						manager::get().effect_.add<freezeef>(obj.x, obj.y);
					}
				}
			}
		}
	}

	auto rmv_iter = std::remove_if(vec.begin(), vec.end(),
		[](parts& i){
		return i.state == 1 && i.etime > 480;
	}
	);

	vec.erase(rmv_iter, vec.end());
}
void w_freeze::draw(){
	for (auto i = vec.begin(); i < vec.end(); i++){
		i->draw();
	}
}
void w_freeze::parts::update(){
	if (state == 0){
		Vector2 ret;
		ret = Func::GetBezier2(Vector2(sx, sy), Vector2((sx + ex) / 2, (sy + ey) / 2 - 150), Vector2(ex, ey), (float)etime / falltime);
		nowx = ret.x;
		nowy = ret.y;
	}

}
void w_freeze::parts::draw(){
	if (state == 0){
		Draw::exrot(nowx, nowy, 1.0, Input::eframe() * 0.1, Graph::handle("ryudan"), 255);
	}
}





void w_knife::init(){
	name = "ナイフ";
	firecool = 0, firerate = 24;
	reloadcool = 0;
	reloadneed = 60;
	bullet = 999;
	bulletmax = 999;
	atk = 1.5;
	knockbackdist = 0.0;
	range = 60;
	movespeedplus = 0.0;
}
void w_knife::update(){
	get_pos_angle();//位置更新・忘れないこと！！
	if (shot(Input::keynow(251))){
		Sound::playback("swing02");
		double sx = x;
		double sy = y;
		Func::addVector(20, angle, sx, sy);
		auto ef = manager::get().effect_.add<knife_swing>(x, y);
		ef->angle = angle;
		manager::get().damagearea_.addptr(std::make_shared<dm_chainsaw>(sx, sy, range, angle, 40, atk, knockbackdist));
		bullet++;
	}
}
void w_knife::draw(){
	/*
	//攻撃範囲描画
	if (debug){
		double sx = x;
		double sy = y;
		Func::addVector(20, angle, sx, sy);
		Draw::lineangle(sx, sy, range, angle, 0xFFFFFFF, 255, 80);
	}
	*/
	//Draw::exrot3(x, y, -5, 8, 1, 1, angle, Graph::handle("gun"), 255);
}


void w_block::init(){
	name = "遮蔽壁";
	vec.clear();
	firecool = 0, firerate = 2;
	reloadcool = 0;
	reloadneed = 1800;
	bullet = 6;
	bulletmax = 6;
	atk = 0.0;
	knockbackdist = 0.0;
	movespeedplus = 0.0;
	vec.clear();
}
void w_block::update(){
	get_pos_angle();//位置更新・忘れないこと！！
	
	if (shot(Input::keyup(251))){
		vec.emplace_back(blockparts(Input::mousex(), Input::mousey()));
		Sound::playback("put01");
	}
	for (auto i = vec.begin(); i < vec.end(); i++){
		i->update();
	}
	auto rmv_iter = std::remove_if(vec.begin(), vec.end(),
		[](blockparts& i){
		return i.remaintime < 0;
	}
	);
	
	vec.erase(rmv_iter, vec.end());
}

void w_block::draw(){
	for (auto i = vec.begin(); i < vec.end(); i++){
		i->draw();
	}
	if (reloadcool == 0 && Input::keynow(251)){
		auto& s = manager::get().saintstone_;
		if (Func::dist(Input::mousex(), Input::mousey(), s.x, s.y) < 200){
			Func::SetDrawBrightInt(0xFF0000);
		}
		Draw::exrot(Input::mousex(), Input::mousey(), 1.0, 0.0, Graph::handle("block"), 150);
		Func::SetDrawBrightInt(0xFFFFFF);
	}
	//Draw::text(100, 100, 0xFFFFFF, Font::handle("SegoeUI20"), std::to_string(vec.size()), 255);
}

void w_block::blockparts::update(){
	remaintime--;
	auto& s = manager::get().saintstone_;
	if (Func::dist(x, y, s.x, s.y) < 200){
		Func::addVector(s.x, s.y, x, y, 4.0, x, y);
	}
	double& px = manager::get().player_.x;
	double& py = manager::get().player_.y;
	double& pr = manager::get().player_.r;
	if (Func::Circles(x, y, r, px, py, pr)){
		Func::addVector(x, y, px, py, 10, px, py);
	}
	auto &vec = manager::get().enemy_.v;
	for (auto &i = vec.begin(); i < vec.end(); i++){
		auto& obj = **i;
		if (Func::Circles(x, y, r, obj.x, obj.y, obj.r * 0.5)){
			Func::addVector(x, y, obj.x, obj.y, 3, obj.x, obj.y);
		}
	}
}

void w_block::blockparts::draw(){
	Draw::exrot(x, y, 1.0, 0.0, Graph::handle("block"), remaintime * 10);
}