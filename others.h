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

class hoge{
public:
	hoge(){
		init();
	}

	void init(){

	}

	void update(){

	}

	void draw(){

	}
};

class drawmouse{
public:
	static drawmouse& get(){
		static drawmouse inst;
		return inst;
	}

	double exrate;

	void draw(){
		if (Input::keydown(250) || Input::keydown(251)){
			exrate = 200;
		}
		Draw::exrot(Input::mousex(), Input::mousey(), 1.0, Input::eframe() * 0.1, Graph::handle("mousecursor"), 255);
		Draw::exrot(Input::mousex(), Input::mousey(), exrate * 0.01, 0.0, Graph::handle("mousecursor2"), 255);
		Func::moverate(exrate, 100.0, 0.1);
	}
private:
	drawmouse(const drawmouse& r);			//コピーコンストラクタも delete 指定
	drawmouse& operator=(const drawmouse& r);	//代入演算子も delete 指定

	drawmouse(){
		exrate = 100;
	}
};

class background{
public:
	background(){
		init();
	}

	void init(){

	}

	void update(){

	}

	void draw(){
		Draw::modi2(0, 0, 1024, 1024, Graph::handle("suna"), 255);
		Draw::modi2(0, 0, 1024, 1024, Graph::handle("floor01"), 50);
	}

};

class backloop1024{
public:

	VERTEX2D Vert[6];
	int ghandle;

	backloop1024(){
		init();
	}

	void init(){
		for (int i = 0; i < 6; i++){
			Vert[i].pos = VGet((i % 2 == 0) ? 0 : 1024.0, (i == 2 || i > 3) ? 1024.0 : 0, 0.0f);
			Vert[i].rhw = 1.0f;
			Vert[i].dif = GetColorU8(255, 255, 255, 255);
			Vert[i].u = (i % 2 == 0) ? 0.0f : 1.0f;
			Vert[i].v = (i == 2 || i>3) ? 1.0f : 0.0f;
		}
	}

	void setgh(int gh){
		ghandle = gh;
	}

	//shiftu, shiftv分移動
	void update(float shiftu, float shiftv){
		for (int i = 0; i < 6; i++){
			Vert[i].u += shiftu;
			Vert[i].v -= shiftv;
		}
	}

	void draw(int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetTextureAddressMode(DX_TEXADDRESS_WRAP);
		SetDrawBlendMode(BlendMode, Alpha);
		DrawPolygon2D(Vert, 2, ghandle, true);
		SetTextureAddressMode(DX_TEXADDRESS_CLAMP);
	}
};



class str_log{
public:
	int x0, y0;//基準座標
	double alpharate;
	double yshift, ydif;
	std::string str[9];//ログ文字列

	int bigstrtime;
	std::string bigstr;//画面中央に表示する文字
	std::string bigstr_under;//画面中央の下に小さく表示する文字列

	int upstrtime;
	std::string upstr;//チュートリアル用

	//コンストラクタ
	str_log(){
		init();
	}

	//ログに文字列を追加する
	void add(const std::string &addstr){
		alpharate = 1;
		yshift = ydif;
		for (int i = 7; i >= 0; i--){
			str[i + 1] = str[i];
		}
		str[0] = addstr;
	}

	//画面中央に大きな文字を文字列を指定して描画開始
	void addbigstr(const std::string & str, const std::string & ministr){
		bigstrtime = 300;
		bigstr = str;
		bigstr_under = ministr;
	}

	//画面中央に大きな文字を文字列を指定して描画開始
	void addupstr(const std::string & str){
		upstrtime = 600;
		upstr = str;
	}


	void init(){
		yshift = 0;
		ydif = 17;
		alpharate = 0;
		bigstrtime = 0;
		upstrtime = 0;
		x0 = 20;
		y0 = (int)(600 - ydif - 5);
		for (int i = 0; i < 9; i++){
			str[i] = std::string("");
		}
	}

	void update(){
		if (alpharate>0){ alpharate -= 0.002; }
		if (yshift > 0){ yshift -= 2.5; }
		if (yshift <0){ yshift = 0; }
	}

	void draw(){
		if (bigstrtime > 0){
			bigstrtime -= 1;
			int alpha = Func::graph4(0, 255, 255, 0, 64, 300 - 64, bigstrtime, 300);
			Draw_::centerbox(400, 300, 800, 100, 0x000000, alpha * 0.3);
			Draw_::centertext(400, 270, 0xFFFFFF, Font::handle("SegoeUI40"), bigstr.c_str(), alpha);
			Draw_::centertext(400, 320, 0xFFFFFF, Font::handle("SegoeUI16"), bigstr_under.c_str(), alpha);
		}

		if (upstrtime > 0){
			upstrtime--;
			int alpha = Func::graph4(0, 255, 255, 0, 128, 600 - 128, upstrtime, 600);
			Draw_::centerbox(400, 200, 800, 100, 0x000000, alpha * 0.3);
			Draw_::centertext(400, 190, 0xFFFFFF, Font::handle("SegoeUI20"), upstr.c_str(), alpha);
		}

		Draw_::modi2(0, 495, 800, 600, Graph::handle("str_log_gra"), alpharate * 128, 1);
		for (int i = 0; i < 3; i++){
			Draw_::centertext(400, y0 - i * ydif + yshift, 0xFFFFFF, Font::handle("SegoeUI16"), str[i].c_str(), (200 - (i*ydif - yshift) * 2)*alpharate);
		}
	}
};


class saintstone{
public:
	double x, y, r;
	double hp, hpmax;
	int etime;

	saintstone(){
		init();
	}

	void init(){
		x = 150;
		y = 512;
		r = 32;
		hp = hpmax = 150;
		etime = 0;
	}

	void update(){
		etime++;
	}

	void draw(){
		Draw::modiOval(x, y, 128, 0.7, etime * -0.003, Graph::handle("saint_foot"), 128);
		SetDrawBright(0, 128, 255);
		drawstone();
		SetDrawBright(255, 255, 255);
	}

	void drawstone(){
		int max = 100;
		double high = (5 * sin(etime * 0.01) + 50.0) / max;
		for (int i = 10; i < max - 5; i += 2){
			double ax[4];
			double ay[4];
			double
				dd = etime * 0.01,
				rr = 40,
				h1 = -high * i + y,
				h2 = -high * (i + 1) + y,
				k1 = sin((double)i / max * 3.14),
				k2 = sin((double)(i + 1) / max * 3.14),
				kat = 0.4,
				angle = i * 0.41 + dd,
				angle2 = (i + 1) * 0.41 + dd;
			ax[0] = k1 * rr * cos(angle) + x;
			ay[0] = kat * rr * sin(angle) + h1;
			ax[1] = k2 * rr * cos(angle2) + x;
			ay[1] = kat * rr * sin(angle2) + h2;
			ax[2] = ax[1];
			ay[2] = ay[1] - 20;
			ax[3] = ax[0];
			ay[3] = ay[0] - 20;
			Draw::modi(ax[0], ay[0], ax[1], ay[1], ax[2], ay[2], ax[3], ay[3], Graph::handle("rect32"), 200);
		}
	}
};

class statusbar{
public:
	double d_hp;
	double d_stone;
	double mrate, srate;
	statusbar(){
		init();
	}
	void init();
	void update();
	void draw();
};

class scoremgr{
public:

	double score;
	double comborate;
	int killnum;//倒した敵の数
	int damagenum;//ダメージを受けた回数
	int eframe;//ステージクリアにかかったフレーム

	scoremgr(){
		init();
	}

	void init(){
		score = 0;
		comborate = 1.0;
		killnum = 0;
		damagenum = 0;
		eframe = 0;
	}

	void addscore(double s){
		score += s * comborate;
		comborate += 0.1;
		killnum++;
	}

	//自機、石がダメージを受けたらコンボレートを減らす
	// & 被弾回数に+1
	void damage(){
		damagenum++;
		comborate -= 0.3;
		if (comborate < 1.0){
			comborate = 1.0;
		}
	}

	void update(){
		if (comborate > 1.0){
			comborate -= 0.001;
		}
		if (comborate < 1.0){
			comborate = 1.0;
		}
	}

	void draw(){

	}
};



class resultefparts{
public:
	double x, y, exrate, angle, angle_v;
	resultefparts(){}
	void init(){
		x = 400.0;
		y = 300.0;
		exrate = Random::FRand(2.5);
		angle = Random::FRadRand();
		angle_v = Random::FRand(0.01, 0.03) * Random::RandPM1();
	}

	void update(){
		angle += angle_v;

	}
	void draw(){
		if (1){
			Draw_::exrot(x, y, exrate, angle, Graph::handle("slash01"), 180, 0, DX_BLENDMODE_ALPHA);
		}
		else{
			Draw_::exrot(x, y, exrate, angle, Graph::handle("slash01"), 30, 0, DX_BLENDMODE_SUB);
		}
	}
};

class resultef{
public:
	static const int NUM = 50;
	resultefparts parts[NUM];

	resultef()
	{
		init();
	}

	void init(){
		for (int i = 0; i < NUM; i++){
			parts[i].init();
		}
	}
	void update(){
		for (int i = 0; i < NUM; i++){
			parts[i].update();
		}
	}
	void draw(){
		for (int i = 0; i < NUM; i++){
			parts[i].draw();
		}
	}
};



class stagescore{
public:
	static const int SCORELOGNUM = 3;
	int score[SCORELOGNUM];
	std::string weaponlog[SCORELOGNUM];
	stagescore(){
		for (int i = 0; i < SCORELOGNUM; i++){
			score[i] = 999;
			weaponlog[i] = "-------------------------";
		}
	}
};


class Datamgr{
public:
	static const int SCORELOGNUM = 3;
	static const int STAGENUM = 10;
	stagescore stage[STAGENUM];
	const char *filename;

	static Datamgr& get(){
		static Datamgr inst;
		return inst;
	}

	//初期化
	void init(){
		if (fexist(filename) == 0) {
			save();
		}
		load();
	}

	//ファイルがあるかどうかを返す関数
	int fexist(const char *filename)
	{
		FILE  *fp;

		if (fopen_s(&fp, filename, "r") != 0){
			return 0;
		}
		fclose(fp);
		return 1;
	}


	void save(){
		FILE* fp_out;
		errno_t error;

		if ((error = fopen_s(&fp_out, filename, "w")) != 0) {
			exit(1);
		}

		for (int i = 0; i < STAGENUM; i++){
			for (int j = 0; j < SCORELOGNUM; j++){
				fprintf(fp_out, "%d %s ", stage[i].score[j], stage[i].weaponlog[j].c_str());
			}
		}
		fclose(fp_out);
	}

	void load(){
		FILE* fp_in;
		errno_t error;

		if ((error = fopen_s(&fp_in, filename, "r")) != 0) {
			exit(1);
		}

		for (int i = 0; i < STAGENUM; i++){
			for (int j = 0; j < SCORELOGNUM; j++){
				char tmp[256];
				fscanf_s(fp_in, "%d %s ", &stage[i].score[j], tmp, sizeof(tmp));
				stage[i].weaponlog[j] = tmp;
			}
		}
		fclose(fp_in);
	}

	//リザルトより、得点を追加
	//ステージの配列番号(stage1だったら0), 得点を引数に取る
	//順位を返す。N位だったらN (N <= 3), それ以外は-1
	int add(int stagearynum, int score, std::string weaponlog){
		int rank = -1;
		for (int i = 0; i < SCORELOGNUM; i++){
			if (stage[stagearynum].score[i] < score){
				for (int j = SCORELOGNUM - 1; j > i; j--){
					stage[stagearynum].score[j] = stage[stagearynum].score[j - 1];
					stage[stagearynum].weaponlog[j] = stage[stagearynum].weaponlog[j - 1];
				}
				stage[stagearynum].score[i] = score;
				stage[stagearynum].weaponlog[i] = weaponlog;
				save();
				return i;
			}
		}
		return -1;
	}

private:
	Datamgr() :
		filename("data.bny")
	{
		init();
	}
	Datamgr(const Datamgr& r) = delete;			//コピーコンストラクタも delete 指定
	Datamgr& operator=(const Datamgr& r) = delete;
};


class pausemgr{
public:
	class to_title{
	public:
		bool IsActive;
		int x;
		int y;
		int width;
		int height;

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
			if (abs(Input::mousex_() - x) < width / 2 && abs(Input::mousey_() - y) < height / 2){
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
			//Draw_::centerbox(x, y, width, height, 0xFFFFFF, 200 + 32 * sin(Input::eframe() * 0.05));
			Draw_::centerbox(x, y, width, height, 0xFFFFFF, 200);
			if (IsActive){
				Draw_::centerbox(x, y, width, height, 0xFFFFFF, 255);
			}
			Draw_::centertext(x, y - 25, 0xFF3333, Font::handle("SegoeUI40"), "To Title", 255);
		}
	};
	to_title titlebutton;
	pausemgr(){
		init();
	}
	void init();
	void update();
	void draw();
};


class dyingmgr{
public:
	int eframe;

	dyingmgr(){
		init();
	}
	void init();
	void update();
	void draw();
};
