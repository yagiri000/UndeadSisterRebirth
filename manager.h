#pragma once
#include <iostream>
#include "player.h"
#include "effects.h"
#include "others.h"
#include "title_menu.h"
#include "weapon.h"
#include "damagearea.h"
#include "enemy.h"
#include "stage.h"

class manager{
public:
	static manager& get(){
		static manager inst;
		return inst;
	}

	enum gamestate{
		pretitle,
		title,
		explain,
		stageselect,
		weaponselect,
		gamemain,
		pause,
		dying,
		result,
		exit,
	};

	gamestate gamestate_;

	background background_;
	player player_;
	effectmgr effect_;
	saintstone saintstone_;
	weaponmgr weapon_;
	damageareamgr damagearea_;
	statusbar statusbar_;
	str_log str_log_;
	scoremgr scoremgr_;
	stagemgr stage_;
	resultmgr result_;
	pausemgr pause_;
	dyingmgr dying_;

	titlemgr title_;
	stageselectmgr stageselect_;
	weaponselectmgr weaponselect_;
	enemymgr enemy_;


	void update(){
		if (gamestate_ == pretitle){
			Screen::get().clear_trail();
			Sound::playbgm("title");
			gamestate_ = title;
		}
		else if (gamestate_ == title){
			title_.update();
		}
		else if (gamestate_ == explain){

		}
		else if (gamestate_ == stageselect){
			stageselect_.update();
		}
		else if (gamestate_ == weaponselect){
			weaponselect_.update();
		}
		else if (gamestate_ == gamemain){
			background_.update();
			player_.update();
			saintstone_.update();
			weapon_.update();
			damagearea_.update();
			enemy_.update();
			effect_.update();
			statusbar_.update();
			str_log_.update();
			scoremgr_.update();
			stage_.update();
			pause_.update();
			dying_.update();
		}
		else if (gamestate_ == pause){
			pause_.update();
		}
		else if (gamestate_ == dying){
			background_.update();
			//player_.update();
			saintstone_.update();
			//weapon_.update();
			damagearea_.update();
			enemy_.update();
			effect_.update();
			statusbar_.update();
			str_log_.update();
			scoremgr_.update();
			stage_.update();
			dying_.update();
		}
		else if (gamestate_ == result){
			result_.update();
		}

		
	}

	void draw(){
		SetDrawScreen(DX_SCREEN_BACK);
		if (gamestate_ == pretitle){
		}
		else if (gamestate_ == title){
			title_.draw();
			Screen::get().update_title_trail();
			Screen::get().DrawtoBACK(Screen::get().trail, DX_BLENDMODE_ALPHA, 255);
			Draw_::exrot(400, 350, 1.0, 0.0, Graph::handle("byyagiri"), 255);

		}
		else if (gamestate_ == explain){

		}
		else if (gamestate_ == stageselect){
			stageselect_.draw();
			Screen::get().update_toalpha8();
			Screen::get().DrawtoBACK(Screen::get().trail, DX_BLENDMODE_ALPHA, 255);
		}
		else if (gamestate_ == weaponselect){
			weaponselect_.draw();
			Screen::get().update_toalpha8();
			Screen::get().DrawtoBACK(Screen::get().trail, DX_BLENDMODE_ALPHA, 255);
		}
		else if (gamestate_ == gamemain){
			background_.draw();
			Screen::get().update_blood();
			Screen::get().DrawtoBACK(Screen::get().blood, DX_BLENDMODE_ALPHA, 255);
			player_.draw();
			saintstone_.draw();
			enemy_.draw();
			effect_.draw();
			str_log_.draw();
			statusbar_.draw();
			scoremgr_.draw();
			stage_.draw();
			Screen::get().update_toalpha8();
			Screen::get().Draw_toBACK(Screen::get().trail, DX_BLENDMODE_ALPHA, 255);
			Screen::get().update_fire();
			Screen::get().DrawtoBACK(Screen::get().fire, DX_BLENDMODE_ADD, 255);
			dying_.draw();
		}
		else if (gamestate_ == pause){
			background_.draw();
			//Screen::get().update_blood();
			Screen::get().DrawtoBACK(Screen::get().blood, DX_BLENDMODE_ALPHA, 255);
			player_.draw();
			saintstone_.draw();
			enemy_.draw();
			str_log_.draw();
			statusbar_.draw();
			scoremgr_.draw();
			stage_.draw();
			//Screen::get().update_toalpha8();
			Screen::get().Draw_toBACK(Screen::get().trail, DX_BLENDMODE_ALPHA, 255);
			//Screen::get().update_fire();
			Screen::get().DrawtoBACK(Screen::get().fire, DX_BLENDMODE_ADD, 255);
			pause_.draw();
		}
		else if (gamestate_ == dying){
			background_.draw();
			Screen::get().update_blood();
			Screen::get().DrawtoBACK(Screen::get().blood, DX_BLENDMODE_ALPHA, 255);
			player_.draw();
			saintstone_.draw();
			enemy_.draw();
			effect_.draw();
			str_log_.draw();
			statusbar_.draw();
			scoremgr_.draw();
			stage_.draw();
			Screen::get().update_toalpha8();
			Screen::get().Draw_toBACK(Screen::get().trail, DX_BLENDMODE_ALPHA, 255);
			Screen::get().update_fire();
			Screen::get().DrawtoBACK(Screen::get().fire, DX_BLENDMODE_ADD, 255);
			dying_.draw();
		}
		else if (gamestate_ == result){
			result_.draw();
			Screen::get().update_toalpha8();
			Screen::get().Draw_toBACK(Screen::get().trail, DX_BLENDMODE_ALPHA, 255);
		}
		drawmouse::get().draw();
		
	}

	void init(){
		background_.init();
		saintstone_.init();
		player_.init();
		weapon_.init();
		damagearea_.init();
		enemy_.init();
		effect_.init();
		statusbar_.init();
		str_log_.init();
		scoremgr_.init();
		stage_.init();
		result_.init();
		pause_.init();
		dying_.init();

		title_.init();
		stageselect_.init();
		weaponselect_.init();
		SetMouseDispFlag(0);
		dx = 0;	dy = 0;
		Draw::setdxdy(dx, dy);
	}


private:
	manager()
	{
		init();
		gamestate_ = pretitle;
	};
	manager(const manager& r) = delete;//ÉRÉsÅ[ã÷é~
	manager& operator=(const manager& r) = delete;//ë„ì¸ã÷é~
};