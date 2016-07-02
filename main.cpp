#include <DxLib.h>
#include <iostream>

#include "myglobal.h"

#include "Source.h"
#include "Func.h"
#include "Screen.h"

#include "manager.h"


int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
{
	SetWindowIconID(101);
	SetMainWindowText("UNDEAD SISTER REBIRTH");
	ChangeWindowMode( TRUE );
	SetGraphMode( ScreenWidth , ScreenHeight , 32 );
	SetOutApplicationLogValidFlag( FALSE ) ;//logを生成しないように設定
	if(DxLib_Init() == 1){return -1;}//初期化に失敗時にエラーを吐かせて終了
	SetDrawScreen( DX_SCREEN_BACK ) ;

	Screen::get();
	Input::get().update();
	Graph::get();
	Sound::get();
	GraphDiv::get();
	Font::get();
	Draw::get();
	Datamgr::get();
	manager::get();
	

	while( ProcessMessage() == 0)
	{
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();//裏画面消す
		Input::update();//キー更新・マウス座標更新・経過フレーム更新

		manager::get().update();
		manager::get().draw();

		if (Input::keydown(KEY_INPUT_ESCAPE)){
			Sound::stopall();
			manager::get().init();
			manager::get().gamestate_ = manager::pretitle;
		}

		//終了処理
		if (manager::get().gamestate_ == manager::exit){
			break;
		}

		/*
		//TODO デバッグ情報はstageにも有り

		//TODO デバッグ用
		//敵を生成
		if (Input::keydown(KEY_INPUT_X)){
			for (int i = -15; i < 15; i++){
				manager::get().enemy_.addmarge<emy_rot_l_tos>(i*0.2, -200);
			}
		}
		//敵を生成
		if (Input::keydown(KEY_INPUT_C)){
			for (int i = 0; i < 50; i++){
				manager::get().enemy_.add<emy_goleft>(512 + i * 20, 512);
			}
		}

		//TODO デバッグ用
		//武器を変更
		auto& w = manager::get().weapon_;
		for (int i = KEY_INPUT_1; i <= KEY_INPUT_6; i++){
			if (Input::keydown(i)){
				Sound::playback("menumove");
				if (Input::keynow(KEY_INPUT_LSHIFT)){
					w.sub = w.subvec[i - KEY_INPUT_1];
					for (auto& i : w.subvec){
						i->init();
					}
				}
				else{
					w.main = w.mainvec[i - KEY_INPUT_1];
					for (auto& i : w.mainvec){
						i->init();
					}
				}
			}
		}

		//TODO デバッグ用
		//Z押されている時にマウス座標描画
		if (Input::keynow(KEY_INPUT_Z)){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			int stry = 300;
			Draw_::righttext(800, 300, 0xFFFFFF, Font::handle("SegoeUI20"), "MX:" + std::to_string(Input::mousex_()) + " MY:" + std::to_string(Input::mousey_()), 200);
			Draw_::righttext(800, 320, 0xFFFFFF, Font::handle("SegoeUI20"), "MX:" + std::to_string(Input::mousex()) + " MY:" + std::to_string(Input::mousey()), 200);
		}
		*/


		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}