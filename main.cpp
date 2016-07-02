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
	SetOutApplicationLogValidFlag( FALSE ) ;//log�𐶐����Ȃ��悤�ɐݒ�
	if(DxLib_Init() == 1){return -1;}//�������Ɏ��s���ɃG���[��f�����ďI��
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
		ClearDrawScreen();//����ʏ���
		Input::update();//�L�[�X�V�E�}�E�X���W�X�V�E�o�߃t���[���X�V

		manager::get().update();
		manager::get().draw();

		if (Input::keydown(KEY_INPUT_ESCAPE)){
			Sound::stopall();
			manager::get().init();
			manager::get().gamestate_ = manager::pretitle;
		}

		//�I������
		if (manager::get().gamestate_ == manager::exit){
			break;
		}

		/*
		//TODO �f�o�b�O����stage�ɂ��L��

		//TODO �f�o�b�O�p
		//�G�𐶐�
		if (Input::keydown(KEY_INPUT_X)){
			for (int i = -15; i < 15; i++){
				manager::get().enemy_.addmarge<emy_rot_l_tos>(i*0.2, -200);
			}
		}
		//�G�𐶐�
		if (Input::keydown(KEY_INPUT_C)){
			for (int i = 0; i < 50; i++){
				manager::get().enemy_.add<emy_goleft>(512 + i * 20, 512);
			}
		}

		//TODO �f�o�b�O�p
		//�����ύX
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

		//TODO �f�o�b�O�p
		//Z������Ă��鎞�Ƀ}�E�X���W�`��
		if (Input::keynow(KEY_INPUT_Z)){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			int stry = 300;
			Draw_::righttext(800, 300, 0xFFFFFF, Font::handle("SegoeUI20"), "MX:" + std::to_string(Input::mousex_()) + " MY:" + std::to_string(Input::mousey_()), 200);
			Draw_::righttext(800, 320, 0xFFFFFF, Font::handle("SegoeUI20"), "MX:" + std::to_string(Input::mousex()) + " MY:" + std::to_string(Input::mousey()), 200);
		}
		*/


		ScreenFlip();//����ʂ�\��ʂɃR�s�[
	}

	DxLib_End();
	return 0;
}