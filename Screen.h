#pragma once

#include <iostream>
#include "DxLib.h"
#include "myglobal.h"

#include "Func.h"

/*
//�g�p��

//pso��ǂݍ��ގ�
Screen::get();


//���C���[�ɕ`�悷�鎞
SetDrawScreen(Screen::get().fire);
SetDrawScreen(DX_SCREEN_BACK);


//���C���[���X�V���鎞
Screen::get().update_fire();


//����ʂɍŏI�I�ɕ`�悷�鎞
SetDrawScreen(DX_SCREEN_BACK);
ClearDrawScreen();
Screen::get().draw(Screen::get().fire,DX_BLENDMODE_ADD, 255);

*/


//!!!!!!����!!!!!!!!!
//�O�Ռn�͌��摜�����ɋ߂��ƑS�����ɂȂ�\����



class Screen{
public:
	
	static const int ScrSize = 1024;

	//���_�̐ݒ�
	VERTEX2DSHADER vertex[4];

	static Screen& get(){
		static Screen inst;
		return inst;
	}

	//�X�N���[����`��
	void DrawtoBACK(int scrhandle, int blendmode, int pal = 255){
		SetDrawScreen(DX_SCREEN_BACK);
		SetDrawBlendMode(blendmode, pal);
		Draw::normal(0, 0, scrhandle, 255, blendmode);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	void Draw_toBACK(int scrhandle, int blendmode, int pal = 255){
		SetDrawScreen(DX_SCREEN_BACK);
		SetDrawBlendMode(blendmode, pal);
		Draw_::normal(0, 0, scrhandle, 255, blendmode);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	//�X�N���[���ɃV�F�[�_�[��K�p����tmp�ɏo��
	void DrawScrToTmpShader(int targetscr, int shaderh){
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawScreen(tmpscreen);
		ClearDrawScreen();
		SetUseTextureToShader(0, targetscr);
		SetUsePixelShader(shaderh);
		DrawPrimitive2DToShader(vertex, 4, DX_PRIMTYPE_TRIANGLESTRIP);
		SetDrawScreen(targetscr);
	}

	//�����ɋ߂Â�
	void update_toalpha8(){
		if (Input::eframe() % 2 == 0){
			DrawScrToTmpShader(trail, shader_toalpha25);

			//���ʂ��R�s�[
			GraphFilterBlt(tmpscreen, trail, DX_GRAPH_FILTER_GAUSS, 8, 1);
		}
	}
	//�����ɋ߂Â�
	void update_toalpha_result(){
		DrawScrToTmpShader(trail, shader_toalpha8);

		//���ʂ��R�s�[
		GraphFilterBlt(tmpscreen, trail, DX_GRAPH_FILTER_GAUSS, 8, 1);
	}


	//�����ɋ߂Â��E�K�E�X������
	//�l���̂悤�ȋO��
	void update_toalpha8_gauss(){
		DrawScrToTmpShader(trail, shader_toalpha8);
		//���ʂ��R�s�[
		GraphFilterBlt(tmpscreen, trail, DX_GRAPH_FILTER_GAUSS, 16, 100);
	}

	//�K�E�X�ڂ�������������
	void update_gauss(){
		GraphFilter(trail, DX_GRAPH_FILTER_GAUSS, 8, 50);
	}


	void update_title_trail(){
		if (Input::eframe() % 5 == 0){
			DrawScrToTmpShader(trail, shader_toalpha1);
			GraphFilterBlt(tmpscreen, trail, DX_GRAPH_FILTER_GAUSS, 8, 10);
		}

		SetDrawScreen(trail);
		int dd = 1;
		GraphFilterBlt(trail, tmpscreen, DX_GRAPH_FILTER_GAUSS, 8, 10);
		Draw_::normal(0, -dd, tmpscreen, 255);
		Draw_::normal(0, dd, tmpscreen, 255);
		Draw_::normal(-dd, 0, trail, 255);
		Draw_::normal(dd, 0, trail, 255);
		//Draw_::line(0, 0, 1024, 0, 0xAA0000, 10);
		SetDrawScreen(DX_SCREEN_BACK);
	}

	//���̃��C���[
	void update_blood(){
		if (Input::eframe() % 23 == 0){
			DrawScrToTmpShader(blood, shader_toalpha3);
			//���ʂ��R�s�[
			GraphFilterBlt(tmpscreen, blood, DX_GRAPH_FILTER_GAUSS, 8, 80);
		}
		if (Input::eframe() % 7 == 0){
			GraphFilter(blood, DX_GRAPH_FILTER_GAUSS, 8, 80);
		}
		if (Input::eframe() % 5 == 0){
			SetDrawScreen(blood);
			int dd = 1;
			Draw_::normal(dd, 0, blood, 255);
			Draw_::normal(0, dd, blood, 255);
			Draw_::normal(-dd, 0, blood, 255);
			Draw_::normal(0, -dd, blood, 255);
			SetDrawScreen(DX_SCREEN_BACK);
		}
	}

	//���U���g���
	void update_result(){
		if (Input::eframe() % 8 == 0){
			DrawScrToTmpShader(blood, shader_toalpha1);
			//���ʂ��R�s�[
			GraphFilterBlt(tmpscreen, blood, DX_GRAPH_FILTER_GAUSS, 8, 20);
		}
		if (Input::eframe() % 10 == 0){
			GraphFilter(blood, DX_GRAPH_FILTER_GAUSS, 8, 50);
		}
		if (Input::eframe() % 3 == 0){
			SetDrawScreen(blood);
			int dd = 1;
			Draw_::normal(dd, 0, blood, 255);
			Draw_::normal(0, dd, blood, 255);
			Draw_::normal(-dd, 0, blood, 255);
			Draw_::normal(0, -dd, blood, 255);
			SetDrawScreen(DX_SCREEN_BACK);
		}
	}

	//���p���C���[
	void update_fire(){
		if (Input::eframe() % 3 == 0){
			//�G�t�F�N�g�ɂ�200,80,50�̃O���f�~�Ȃǂ��g�p���邱��
			DrawScrToTmpShader(fire, shader_toblack8);
			//���ʂ��R�s�[
			GraphFilterBlt(tmpscreen, fire, DX_GRAPH_FILTER_GAUSS, 8, 500);
		}
		if (Input::eframe() % 3 == 0){
			GraphFilter(fire, DX_GRAPH_FILTER_LEVEL, 68, 255, 100, 0, 255);
		}

		//�����x128�̍���`��
		SetDrawScreen(fire);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 40);
		DrawBox(0, 0, 1024, 1024, 0x000000, 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	void clear_trail(){
		SetDrawScreen(trail);
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);
	}

	void clear_blood(){
		SetDrawScreen(blood);
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);
	}

	void clear_fire(){
		SetDrawScreen(fire);
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);
	}

	//�s�N�Z���V�F�[�_
	int shader_toalpha1;
	int shader_toalpha3;
	int shader_toalpha8;
	int shader_toalpha25;
	int shader_toblack8;

	//�X�N���[��
	int tmpscreen;
	int trail;
	int blood;
	int fire;

private:
	Screen(const Screen& r) = delete;			//�R�s�[�R���X�g���N�^�� delete �w��
	Screen& operator=(const Screen& r) = delete;	//������Z�q�� delete �w��

	Screen(){
		//�s�N�Z���V�F�[�_�ǂݍ���
		shader_toalpha1 = LoadPixelShader("Shader/toalpha1.pso");
		shader_toalpha3 = LoadPixelShader("Shader/toalpha3.pso");
		shader_toalpha8 = LoadPixelShader("Shader/toalpha8.pso");
		shader_toalpha25 = LoadPixelShader("Shader/toalpha25.pso");
		shader_toblack8 = LoadPixelShader("Shader/toblack8.pso");

		//�V���ɃX�N���[�����쐬
		tmpscreen = MakeScreen(ScrSize, ScrSize, 1);
		trail = MakeScreen(ScrSize, ScrSize, 1);
		blood = MakeScreen(ScrSize, ScrSize, 1);
		fire = MakeScreen(ScrSize, ScrSize, 1);
		

		//���_�̐ݒ�
		for (int i = 0; i < 4; i++)
		{
			vertex[i].pos = VGet((i % 2)*(float)ScrSize, (i / 2)*(float)ScrSize, 0);
			vertex[i].rhw = 1.0f;
			vertex[i].dif = GetColorU8(255, 255, 255, 255);
			vertex[i].spc = GetColorU8(0, 0, 0, 0);
			vertex[i].u = vertex[i].su = (float)(i % 2);
			vertex[i].v = vertex[i].sv = (float)(i / 2);
		}
	}

};