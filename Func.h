#pragma once

#include <DxLib.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "myglobal.h"
#include "Source.h"

/*
//シングルトンDrawクラス
//Vector2クラス
//シングルトンRandomクラス
------------------以下、当たり判定---------------------
------------------以下、極座標←→XY座標------------------
------------------以下、回転---------------------
------------------以下、ベクトル---------------------
------------------以下、イージング曲線---------------
------------------以下、便利関数------------------
*/


//シングルトンDrawクラス
class Draw
{
	Draw(){
		dx = 0; dy = 0;
	}
	Draw(const Draw& r) = delete;
	Draw& operator=(const Draw& r) = delete;
public:
	double dx;
	double dy;

	//唯一存在するインスタンスを返す
	static Draw& get()
	{
		static Draw inst;
		return inst;
	}

	static void setdxdy(int x, int y){
		get().dx = x;
		get().dy = y;
	}


	//通常の描画・座標は左上を指定
	static void normal(int x, int y, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawGraph(x + get().dx, y + get().dy, GrHandle, 1);
	}

	//画像の中央の座標を指定して描画
	static void center(int x, int y, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRotaGraph(x + get().dx, y + get().dy, 1.0, 0.0, GrHandle, 1, TurnFlag);
	}

	//拡大・回転描画
	static void exrot(int x, int y, double ExtRate, double Angle, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRotaGraph(x + get().dx, y + get().dy, ExtRate, Angle, GrHandle, 1, TurnFlag);
	}

	//拡大・回転・中央指定描画
	static void exrot3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRotaGraph3(x + get().dx, y + get().dy, cx, cy, ExtRateX, ExtRateY, Angle, GrHandle, 1, TurnFlag);
	}

	//自由変形描画
	static void modi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawModiGraph(
			x1 + get().dx, y1 + get().dy, x2 + get().dx, y2 + get().dy,
			x3 + get().dx, y3 + get().dy, x4 + get().dx, y4 + get().dy,
			GrHandle, 1);
	}

	//左上・右下を指定して描画
	static void modi2(int x1, int y1, int x2, int y2, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawExtendGraph(x1 + get().dx, y1 + get().dy, x2 + get().dx, y2 + get().dy, GrHandle, 1);
	}

	//楕円上にグラフを描画　rで円の半径・rate:縦にrをrateの比の分ひしゃげさせる・angle:回転角
	static void modiOval(double x, double y, double r, double rate, double angle, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		float gx[4];
		float gy[4];
		float dr = PI * -0.75;
		for (int i = 0; i < 4; i++){
			float dangle = PI * 0.5;
			gx[i] = x + r * cos(angle + i * dangle - dr);
			gy[i] = y + rate * r * sin(angle + i * dangle - dr);
		}

		SetDrawBlendMode(BlendMode, Alpha);
		DrawModiGraphF(
			gx[0] + get().dx, gy[0] + get().dy,
			gx[1] + get().dx, gy[1] + get().dy,
			gx[2] + get().dx, gy[2] + get().dy,
			gx[3] + get().dx, gy[3] + get().dy, GrHandle, 1);
	}

	//画像の指定した部分のみ描画　描画座標・左上座標・描画画像サイズ
	static void trim(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRectGraph(DestX + get().dx, DestY + get().dy, SrcX, SrcY, Width, Height, GrHandle, 1, TurnFlag);
	}

	//サークルゲージ描画　(dx, dy)分シフト
	static void circlegauge(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawCircleGauge(x + get().dx, y + get().dy, 100, GrHandle, 100 - percent);
	}

	//サークルゲージ描画（逆方向）　(dx, dy)分シフト
	static void circlegauge_rev(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawCircleGauge(x + get().dx, y + get().dy, percent, GrHandle);
	}

	//図形描画関数

	//線を描画
	static void line(int sx, int sy, int ex, int ey, int color, int Alpha, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawLine(sx + get().dx, sy + get().dy, ex + get().dx, ey + get().dy, color, Thickness);
	}

	//独自
	//始点と終点への距離、角度を指定して線を描画
	static void lineangle(int sx, int sy, int r, double angle, int color, int Alpha, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawLine(sx + get().dx, sy + get().dy, sx + r * cos(angle) + get().dx, sy + r * sin(angle) + get().dy, color, Thickness);
	}

	//箱を描画
	static void box(int x1, int y1, int x2, int y2, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawBox(x1 + get().dx, y1 + get().dy, x2 + get().dx, y2 + get().dy, color, 1);
	}

	//独自
	//中心を指定して箱を描画
	static void centerbox(int centerx, int centery, int width, int height, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawBox(
			centerx - width / 2 + get().dx, centery - height / 2 + get().dy,
			centerx + width / 2 + get().dx, centery + height / 2 + get().dy,
			color, 1);
	}

	//円を描画
	static void circle(int x, int y, int r, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawCircle(x + get().dx, y + get().dy, r, color, 1);
	}

	//三角形を描画
	static void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawTriangle(x1 + get().dx, y1 + get().dy, x2 + get().dx, y2 + get().dy, x3 + get().dx, y3 + get().dy, color, 1);
	}


	//文字描画関数

	//文字を描画
	static void text(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawFormatStringToHandle(x + get().dx, y + get().dy, color, fonthandle, "%s", str.c_str());
	}

	//指定した座標を中心に文字を描画
	static void centertext(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		int wd = GetDrawFormatStringWidthToHandle(fonthandle, "%s", str.c_str());
		DrawFormatStringToHandle(x + get().dx - wd / 2, y + get().dy, color, fonthandle, "%s", str.c_str());
	}

	//文字の右上の座標を指定して文字を描画
	static void righttext(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		int wd = GetDrawFormatStringWidthToHandle(fonthandle, "%s", str.c_str());
		DrawFormatStringToHandle(x + get().dx - wd, y + get().dy, color, fonthandle, "%s", str.c_str());
	}
};


//シングルトンDraw_（ドローアンダーバー）クラス
//dx,dy分修正しない
class Draw_
{
	Draw_(){
	}
	Draw_(const Draw_& r) = delete;
	Draw_& operator=(const Draw_& r) = delete;
public:

	//唯一存在するインスタンスを返す
	static Draw_& get()
	{
		static Draw_ inst;
		return inst;
	}


	//通常の描画・座標は左上を指定
	static void normal(int x, int y, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawGraph(x, y, GrHandle, 1);
	}

	//画像の中央の座標を指定して描画
	static void center(int x, int y, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRotaGraph(x, y, 1.0, 0.0, GrHandle, 1, TurnFlag);
	}

	//拡大・回転描画
	static void exrot(int x, int y, double ExtRate, double Angle, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRotaGraph(x, y, ExtRate, Angle, GrHandle, 1, TurnFlag);
	}

	//拡大・回転・中央指定描画
	static void exrot3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRotaGraph3(x, y, cx, cy, ExtRateX, ExtRateY, Angle, GrHandle, 1, TurnFlag);
	}

	//自由変形描画
	static void modi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawModiGraph(
			x1, y1, x2, y2,
			x3, y3, x4, y4,
			GrHandle, 1);
	}

	//左上・右下を指定して描画
	static void modi2(int x1, int y1, int x2, int y2, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawExtendGraph(x1, y1, x2, y2, GrHandle, 1);
	}

	//画像の指定した部分のみ描画　描画座標・左上座標・描画画像サイズ
	static void trim(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRectGraph(DestX, DestY, SrcX, SrcY, Width, Height, GrHandle, 1, TurnFlag);
	}

	//サークルゲージ描画　(dx, dy)分シフト
	static void circlegauge(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawCircleGauge(x, y, 100, GrHandle, 100 - percent);
	}

	//サークルゲージ描画（逆方向）　(dx, dy)分シフト
	static void circlegauge_rev(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawCircleGauge(x, y, percent, GrHandle);
	}

	//図形描画関数

	//線を描画
	static void line(int sx, int sy, int ex, int ey, int color, int Alpha, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawLine(sx, sy, ex, ey, color, Thickness);
	}

	//独自
	//始点と終点への距離、角度を指定して線を描画
	static void lineangle(int sx, int sy, int r, double angle, int color, int Alpha, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawLine(sx, sy, sx + r * cos(angle), sy + r * sin(angle), color, Thickness);
	}

	//箱を描画
	static void box(int x1, int y1, int x2, int y2, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawBox(x1, y1, x2, y2, color, 1);
	}

	//独自
	//中心を指定して箱を描画
	static void centerbox(int centerx, int centery, int width, int height, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawBox(
			centerx - width / 2, centery - height / 2,
			centerx + width / 2, centery + height / 2,
			color, 1);
	}

	//円を描画
	static void circle(int x, int y, int r, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawCircle(x, y, r, color, 1);
	}

	//三角形を描画
	static void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawTriangle(x1, y1, x2, y2, x3, y3, color, 1);
	}


	//文字描画関数

	//文字を描画
	static void text(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawFormatStringToHandle(x, y, color, fonthandle, "%s", str.c_str());
	}

	//指定した座標を中心に文字を描画
	static void centertext(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		int wd = GetDrawFormatStringWidthToHandle(fonthandle, "%s", str.c_str());
		DrawFormatStringToHandle(x - wd / 2, y, color, fonthandle, "%s", str.c_str());
	}

	//文字の右上の座標を指定して文字を描画
	static void righttext(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		int wd = GetDrawFormatStringWidthToHandle(fonthandle, "%s", str.c_str());
		DrawFormatStringToHandle(x - wd, y, color, fonthandle, "%s", str.c_str());
	}
};



//マウス座標・キー状態・起動からのフレーム数

//!!!!!!!!!!!!! 注意 !!!!!!!!!!!!!
//getする前にstaticメンバにアクセスするのは不可能

class Input{
public:

	Input()
	{
		m_mousex = 0;
		m_mousey = 0;
		m_eframe = 0;
		Allzeroframe = 0;
		IsAllzero = false;
	}

	Input& operator=(const Input& a) = delete;
	Input(const Input& a) = delete;


	static Input& get(){
		static Input inp;
		return inp;
	}

	static void update(){
		get().do_update();
	}

	//キーが押されているかをboolで返す
	static bool keynow(int i){
		return get().keystate[i] > 0;
	}

	//キーが押されたフレームだけtrueを返す
	static bool keydown(int i){
		return (get().keystate[i] == 1 && get().keystate_pre[i] != -1);
	}

	//キーが離されたフレームだけtrueを返す
	static bool keyup(int i){
		return (get().keystate[i] == 0) && (get().keystate_pre[i] > 0);
	}

	//キーが押されているフレームを返す
	static int keyframe(int i){
		return get().keystate[i];
	}

	static int mousex(){
		return get().m_mousex + dx;
	}

	static int mousey(){
		return get().m_mousey + dy;
	}

	static int mousex_(){
		return get().m_mousex;
	}

	static int mousey_(){
		return get().m_mousey;
	}

	static int eframe(){
		return get().m_eframe;
	}

	//Allzeroframeの間keystateがすべて0に
	static void setAllzeroframe(int t){
		if (t > 0){
			get().Allzeroframe = t;
		}
	}

	//Allzerooffが呼ばれるまでkeystateをすべて0に
	static void Allzeroon(){
		get().IsAllzero = true;
	}

	//keystateすべて0 を解除 Allzeroframeを0に
	static void Allzerooff(){
		get().IsAllzero = false;
		get().Allzeroframe = 0;
	}


private:
	int m_mousex;
	int m_mousey;//マウス座標
	int m_eframe;//経過フレーム

	char buf[256];
	int keystate[256];
	int keystate_pre[256];

	//setAllzeroframe関数でロックされるフレーム数 waitframe>0で全配列内容0に　
	int Allzeroframe;

	//IsAll0 == trueで全配列内容0に
	bool IsAllzero;


	void do_update(){
		GetHitKeyStateAll(buf);
		buf[250] = GetMouseInput() & MOUSE_INPUT_LEFT;
		buf[251] = ((GetMouseInput() & MOUSE_INPUT_RIGHT) == 0) ? 0 : 1;
		for (int i = 0; i< 256; i++){
			//1フレーム前の情報を保存
			keystate_pre[i] = keystate[i];
			//keystateを更新
			if (buf[i] == 1){
				if (keystate[i] == -1) keystate[i] = 0;
				keystate[i]++;
			}
			else{
				keystate[i] = 0;
			}
		}
		if (IsAllzero == true || Allzeroframe > 0){
			Allzero();
		}
		if (Allzeroframe > 0){
			Allzeroframe--;
		}
		//マウス座標更新
		GetMousePoint(&m_mousex, &m_mousey);
		//経過フレーム計測
		m_eframe++;
	}

	void Allzero(){
		for (int i = 0; i < 256; i++){
			keystate[i] = -1;
			keystate_pre[i] = -1;
		}
	}
};


//2次元上の点を表すクラス
class Vector2
{
public:
	double x;
	double y;
	//コンストラクタ定義
	Vector2() :x(0), y(0){}
	Vector2(double x_, double y_) :x(x_), y(y_){}
	//オペレーターオーバーロード
	Vector2& operator +=(const Vector2& t)
	{
		x += t.x;
		y += t.y;
		return *this;
	}
	Vector2& operator -=(const Vector2& t)
	{
		x -= t.x;
		y -= t.y;
		return *this;
	}
	Vector2& operator *=(const Vector2& t)
	{
		x *= t.x;
		y *= t.y;
		return *this;
	}
	Vector2& operator /=(const Vector2& t)
	{
		x /= t.x;
		y /= t.y;
		return *this;
	}
	Vector2& operator +=(const double t)
	{
		x += t;
		y += t;
		return *this;
	}
	Vector2& operator -=(const double t)
	{
		x -= t;
		y -= t;
		return *this;
	}
	Vector2& operator *=(const double t)
	{
		x *= t;
		y *= t;
		return *this;
	}
	Vector2& operator /=(const double t)
	{
		x /= t;
		y /= t;
		return *this;
	}

	//操作関数
	void Set(double x_, double y_)
	{
		x = x_; y = y_;
	}
	//原点を中心に回転
	void Rotate(double rad)
	{
		double sint = sin(rad), cost = cos(rad);	//sinとcosの値
		double tx = x;	//一時格納
		x = cost*tx - sint*y;		// ( cosθ -sinθ) ( x )
		y = sint*tx + cost*y;		// ( sinθ xosθ ) ( y )
	}
	//centerを中心に回転
	void RotateOnPoint(double rad, const Vector2 &center)
	{
		double sint = sin(rad), cost = cos(rad);	//sinとcosの値
		double tx = x - center.x;	//一時格納
		double ty = y - center.y;	//一時格納
		x = cost*tx - sint*ty + center.x;		// ( cosθ -sinθ) ( x )
		y = sint*tx + cost*ty + center.y;		// ( sinθ xosθ ) ( y )
	}
	//dx,dy分だけ移動
	void Translate(double dx, double dy)
	{
		x += dx;
		y += dy;
	}
	//ベクトルの大きさを返す
	double magnitude(){
		return sqrt(x*x + y*y);
	}
	//ベクトルを正規化する
	void normalize(){
		double r = sqrt(x*x + y*y);
		if (r < 0.01){
			r = 0.01;
		}
		x /= r;
		y /= r;
	}
};
class RectPF
{
public:
	enum PosName
	{
		LEFT_TOP,
		RIGHT_TOP,
		LEFT_BOTTOM,
		RIGHT_BOTTOM,
	};
	Vector2 pos[4];
	int width, height;
	float _X(int posnum) const{ return pos[posnum].x; }
	float _Y(int posnum) const{ return pos[posnum].y; }
	//Set関数。左上→右上→左下→右下
	void Set(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
	{
		pos[0].Set(x1, y1);
		pos[1].Set(x2, y2);
		pos[2].Set(x3, y3);
		pos[3].Set(x4, y4);
	}
	//Set関数。左上と右下を定義
	void Set(Vector2& lefttop, Vector2& rightbottom)
	{
		pos[0].Set(lefttop.x, lefttop.y);
		pos[1].Set(rightbottom.x, lefttop.y);
		pos[2].Set(lefttop.x, rightbottom.y);
		pos[3].Set(rightbottom.x, rightbottom.y);
		width = (int)abs(rightbottom.x - lefttop.x);
		height = (int)abs(rightbottom.y - lefttop.y);
	}
	void Set(float ltx, float lty, float rbx, float rby)
	{
		pos[0].Set(ltx, lty);
		pos[1].Set(rbx, lty);
		pos[2].Set(ltx, rby);
		pos[3].Set(rbx, rby);
		width = (int)abs(rbx - ltx);
		height = (int)abs(rby - lty);
	}
	//中央と幅高さを定義
	void Set(Vector2& center, float Width, float Height)
	{
		pos[0].Set(center.x - Width / 2, center.y - Height / 2);
		pos[1].Set(center.x + Width / 2, center.y - Height / 2);
		pos[2].Set(center.x - Width / 2, center.y + Height / 2);
		pos[3].Set(center.x + Width / 2, center.y + Height / 2);
		width = (int)Width;
		height = (int)Height;
	}
	//矩形を指定角度だけ回転
	void Rotate(float rad)
	{
		for (int i = 0; i<4; i++)
			pos[i].Rotate(rad);
	}
	//矩形を指定分だけ平行移動
	void Translate(float x, float y)
	{
		Vector2 Temp(x, y);
		for (int i = 0; i<4; i++)
			pos[i] += Temp;
	}
};
//シングルトンRandomクラス
class Random
{
	std::mt19937 mt;
	//コンストラクタ　SeedSetUseRDでMTの初期値を設定
	Random(){
		SeedSetUseRD();
	}
	Random(const Random& r) = delete;
	Random& operator=(const Random& r) = delete;
public:
	static Random& get()
	{
		static Random r;
		return r;
	}
	//MTの初期値をRandom_deviceを使用して設定
	static void SeedSetUseRD(){
		std::random_device r;
		get().mt.seed(r());
	}
	//MTの初期値設定
	static void Initialize(int seed)
	{
		get().mt.seed(seed);
	}
	//mtエンジン本体を取得
	static std::mt19937& getMT(){ return get().mt; }
	//完全乱数
	static unsigned int RamdomDeviceValue()
	{
		std::random_device r;
		return r();
	}

	//通常のrand取得
	static int Rand(){
		return get().mt();
	}
	//0~max指定取得(int)
	static int Rand(int max)
	{
		std::uniform_int_distribution<int> uid(0, max);
		return uid(get().mt);
	}
	//min~maxを返す(int)
	static int Rand(int min, int max)
	{
		std::uniform_int_distribution<int> uid(min, max);
		return uid(get().mt);
	}
	//1か-1を返す関数
	static int RandPM1(){
		std::uniform_int_distribution<int> uid(0, 1);
		return uid(get().mt) * 2 - 1;
	}
	//0~1を返す(double)
	static double Value()
	{
		std::uniform_real_distribution<double> urd(0, 1);
		return urd(get().mt);
	}
	//0~maxを返す(double)
	static double FRand(double max)
	{
		std::uniform_real_distribution<double> urd(0, max);
		return urd(get().mt);
	}
	//min~maxを返す(double)
	static double FRand(double min, double max)
	{
		std::uniform_real_distribution<double> urd(min, max);
		return urd(get().mt);
	}
	//正規分布
	static double FRandND(double mean, double sigma)
	{
		std::normal_distribution<double> nd(mean, sigma);
		return nd(get().mt);
	}
	static double FRandND(double mean, double sigma, double limit)
	{
		std::normal_distribution<double> nd(mean, sigma);
		double r = nd(get().mt);
		if (r < mean - limit)
			r = mean - limit;
		if (r > mean + limit)
			r = mean + limit;
		return r;
	}
	//ラジアンで取得
	static double FRadRand()
	{
		return FRand(-PI, PI);
	}
	static double FRadRand(double deg_min, double deg_max)
	{
		return FRand(deg_min * DegToRad, deg_max * DegToRad);
	}
	static double FRadRandND(double deg_mean, double deg_sigma = 0)
	{
		return FRandND(deg_mean * DegToRad, deg_sigma * DegToRad);
	}
	//半径rの円上の点を返す
	static void RandOnCircle(double r, double &x, double &y){
		double randang = FRadRand();
		x = r * cos(randang);
		y = r * sin(randang);
	}
	//半径rの円上の点を返す　原点からの角度も返す
	static void RandOnCircle(double r, double &x, double &y, double &ang){
		double randang = FRadRand();
		x = r * cos(randang);
		y = r * sin(randang);
		ang = randang;
	}
	//半径rの円内部の点を返す
	static void RandInCircle(double r, double &x, double &y){
		double randang = FRadRand();
		double rr = r * Value();
		x = rr * cos(randang);
		y = rr * sin(randang);
	}
	//半径rの円内部の点を返す　原点からの角度も返す
	static void RandInCircle(double r, double &x, double &y, double &ang){
		double randang = FRadRand();
		double rr = r * Value();
		x = rr * cos(randang);
		y = rr * sin(randang);
		ang = randang;
	}
};

class Func{
private:
	Func(){}
	Func& operator=(const Func& a);
	Func(const Func& a);

public:
	//------------------以下、当たり判定-------------------- -

	//2乗
	template<typename T> static T Sqr(T x)
	{
		return x*x;
	}
	//内積計算
	template<typename T> static T Dot2D(T Ax, T Ay, T Bx, T By)
	{
		return Ax*Bx + Ay*By;
	}
	//外積計算
	template<typename T> static T Cross2D(T Ax, T Ay, T Bx, T By)
	{
		return Ax*By - Bx*Ay;
	}

	
	//円形同士
	static bool Circles(double x1, double y1, double r1, double x2, double y2, double r2)
	{
		return Sqr(x2 - x1) + Sqr(y2 - y1) < Sqr(r2 + r1);
	}
	static bool Circles(const Vector2& c1, double r1, const Vector2& c2, double r2)
	{
		return Sqr(c2.x - c1.x) + Sqr(c2.y - c1.y) < Sqr(r2 + r1);
	}
	//矩形同士
	static bool Boxes(double a1x, double a1y, double a2x, double a2y, double b1x, double b1y, double b2x, double b2y)
	{
		return a1x < b2x && a1y < b2y && b1x < a2x && b1y < a2y;
	}
	static bool Boxes(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2)
	{
		return a1.x < b2.x && a1.y < b2.y && b1.x < a2.x && b1.y < a2.y;
	}
	static bool Boxes(const RectPF& a, const RectPF& b)
	{
		return	a.pos[RectPF::LEFT_TOP].x < b.pos[RectPF::RIGHT_BOTTOM].x &&
			a.pos[RectPF::LEFT_TOP].y < b.pos[RectPF::RIGHT_BOTTOM].y &&
			b.pos[RectPF::LEFT_TOP].x < a.pos[RectPF::RIGHT_BOTTOM].x &&
			b.pos[RectPF::LEFT_TOP].y < a.pos[RectPF::RIGHT_BOTTOM].y;
	}

	//点と幅のある線 (点の座標、幅のある線の始点・終点)
	static bool BroadLinePoint(double px, double py, double line_sx, double line_sy, double line_ex, double line_ey, double broad){
		double x, y, ang, width;
		x = px - line_sx;
		y = py - line_sy;
		ang = atan2(line_ey - line_sy, line_ex - line_sx);
		width = dist(line_sx, line_sy, line_ex, line_ey);

		rotateonzero(x, y, -ang);

		if (x > 0 && x < width && y > -broad && y < broad){
			return true;
		}
		else{
			return false;
		}
	}

	//点と幅のある線 (点の座標、幅のある線の始点・終点までの距離、角度)
	static bool BroadLinePointAng(double px, double py, double line_sx, double line_sy, double e_r, double e_ang, double broad){
		double x, y;
		x = px - line_sx;
		y = py - line_sy;

		rotateonzero(x, y, -e_ang);

		if (x > 0 && x < e_r && y > -broad && y < broad){
			return true;
		}
		else{
			return false;
		}
	}

	//点と矩形
	bool BoxPoint(int px, int py, int box_cx, int box_cy, int box_width, int box_height){
		return abs(px - box_cx) < box_width / 2 && abs(py - box_cy) < box_height / 2;
	}

	//点と回転矩形(矩形自体は無回転で渡すこと
	static bool DotAndRotRect(Vector2 dot, const Vector2& rectpos, const RectPF& rect, double rect_angle)
	{
		dot.Translate(-rectpos.x, -rectpos.y);
		dot.Rotate(-rect_angle);
		return	dot.x > rect._X(0) && dot.y > rect._Y(0) &&
			dot.x < rect._X(3) && dot.y < rect._Y(3);
	}
	//円と回転矩形(矩形自体は無回転で渡すこと
	static bool CircleAndRotRect(Vector2 circle_pos, double circle_r, const Vector2& rectpos, const RectPF& rect, double rect_angle)
	{
		circle_pos.Translate(-rectpos.x, -rectpos.y);
		circle_pos.Rotate(-rect_angle);
		return circle_pos.x > rect._X(0) - circle_r && circle_pos.y > rect._Y(0) - circle_r
			&& circle_pos.x < rect._X(3) + circle_r && circle_pos.y < rect._Y(3) + circle_r;
	}
	//追加
	//円(半径cr,(cx,cy))の近似正方形と　長方形(左上(rx1,ry1), 右下(rx2, ry2))の当たり判定
	static bool CircleAndRect(double cx, double cy, double cr, double rx1, double ry1, double rx2, double ry2){
		double rectx = (rx1 + rx2) / 2.0;
		double recty = (ry1 + ry2) / 2.0;
		return	cx > rx1 - cr && cy > ry1 - cr &&
			cx < rx2 + cr && cy < ry2 + cr;
	}
	//線分同士(0ならあたってない、0以上はあたってる
	static double Lines(double a_x, double a_y, double b_x, double b_y, double c_x, double c_y, double d_x, double d_y)
	{
		double c0;
		c0 = Cross2D(b_x - a_x, b_y - a_y, d_x - c_x, d_y - c_y);
		if (c0 == 0.0f)
			return 0.0f;
		double r0, r1;
		r0 = Cross2D(c_x - a_x, c_y - a_y, b_x - a_x, b_y - a_y) / c0;
		r1 = Cross2D(c_x - a_x, c_y - a_y, d_x - c_x, d_y - c_y) / c0;
		if (r0 >= 0.0f && r0 <= 1.0f && r1 >= 0.0f && r1 <= 1.0f)
			return r1;
		else
			return 0.0f;
	}
	//Linesで当たってた場合は位置を計算できる
	static Vector2 LinesCalcCrossPoint(double lines_result, double a_x, double a_y, double b_x, double b_y)
	{
		Vector2 AB(b_x - a_x, b_y - a_y);
		AB *= lines_result;
		AB.Translate(a_x, a_y);
		return AB;
	}
	//円と線分
	static bool CircleAndLine(double cx, double cy, double r, double sx, double sy, double ex, double ey)
	{
		if (distSqr(sx, sy, cx, cy) < r*r || distSqr(ex, ey, cx, cy) < r*r){
			return true;
		}
		else {
			double k = ey - sy;
			double l = ex - sx;
			if (!((k*cx - l*cy - k*sx + l*sy)*(k*cx - l*cy - k*sx + l*sy) < r * r * (k*k + l*l))){
				return false;
			}
			if (((sx - cx)*(ex - cx) + (sy - cy)*(ey - cy)) < 0){
				return true;
			}
		}
		return false;
	}
	//普通の点と矩形
	static bool DotAndRect(const Vector2& p, const RectPF& r)
	{
		return  r.pos[RectPF::LEFT_TOP].x <= p.x  && p.x <= r.pos[RectPF::RIGHT_BOTTOM].x
			&&  r.pos[RectPF::LEFT_TOP].y <= p.y  && p.y <= r.pos[RectPF::RIGHT_BOTTOM].y;
	}
	//追加
	//普通の点と矩形
	static bool DotAndRect(double px, double py, double b1x, double b1y, double b2x, double b2y)
	{
		return  b1x < px  && px < b2x
			&&  b1y < py  && py < b2y;
	}
	//ある閉じた多角形の内側にあるかどうか
	static bool In2DPolygon(const Vector2& p, std::vector<Vector2> vertexes)
	{
		int wn = 0;
		for (int i = 0; i < (int)vertexes.size() - 1; i++)
		{
			//Winding Number Algorithm
			if (vertexes[i].y <= p.y && p.y < vertexes[i + 1].y)
			{
				double t = (p.y - vertexes[i].y) / (vertexes[i + 1].y - vertexes[i].y);
				if (p.x < vertexes[i].x + t*(vertexes[i + 1].x - vertexes[i].x))
					wn++;
			}
			else if (vertexes[i].y > p.y && p.y >= vertexes[i + 1].y)
			{
				double t = (p.y - vertexes[i].y) / (vertexes[i + 1].y - vertexes[i].y);
				if (p.x < vertexes[i].x + t*(vertexes[i + 1].x - vertexes[i].x))
					wn--;
			}
		}
		return wn >= 1;
	}

	

	//------------------以下、回転---------------------

	//原点を中心にang分回転
	static void rotateonzero(double &x,  double &y, double ang){
		double sx = x - 0;
		double sy = y - 0;
		x = sx * cos(ang) - sy * sin(ang) + 0;
		y = sx * sin(ang) + sy * cos(ang) + 0;
	}
	
	//ある点(centerx,centery)を中心にang分回転
	static void rotateonpoint(double &x,  double &y,  double centerx, double centery, double ang){
		double sx = x - centerx;
		double sy = y - centery;
		x = sx * cos(ang) - sy * sin(ang) + centerx;
		y = sx * sin(ang) + sy * cos(ang) + centery;
	}
	

	//------------------以下、ベクトル---------------------

	//(原点から(sx,sy)への単位ベクトルを求める
	static void normalizedVector(double &vx, double &vy, double sx, double sy){
		double rd = atan2(sy, sx);
		vx = cos(rd);
		vy = sin(rd);
	}

	//(sx,sy)から(ex,ey)への単位ベクトルを求める
	static void normalizedVector(double &vx, double &vy, double sx, double sy, double ex, double ey){
		double rd = atan2(ey - sy, ex - sx);
		vx = cos(rd);
		vy = sin(rd);
	}


	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに代入
	static void calVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
		double rd = atan2(ey - sy, ex - sx);
		resultx = dist * cos(rd);
		resulty = dist * sin(rd);
	}

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに加算
	static void addVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
		double rd = atan2(ey - sy, ex - sx);
		resultx += dist * cos(rd);
		resulty += dist * sin(rd);
	}

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに加算
	static void addVector(double r, double angle, double &resultx, double &resulty){
		resultx += r * cos(angle);
		resulty += r * sin(angle);
	}

	//極座標表現からxy表現に直す
	static void polartoxy(double &x, double &y, double r, double ang){
		x = r * cos(ang);
		y = r * sin(ang);
	}

	//角度を計算
	static double calAngle(double x, double y){
		return atan2(y, x);
	}
	
	//角度を計算
	static double calAngle(double sx, double sy, double ex, double ey){
		return atan2(ey - sy, ex - sx);
	}

	/*
	startx : 開始の値(開始時の座標やスケールなど)
	enddif : 開始と終了の値の差分
	time_now : 現在の時間
	time_end : Tweenの合計時間
	*/

	//／＼　←こういうグラフ
	static double linef(double startx, double dif, double time_now, double time_end){
		return startx + (dif - startx) * (1.0 - abs(time_end/2 - time_now) / (time_end/2) );
	}

	//／＼　←こういう2次曲線
	static double quadraticf(double startx, double dif, double time_now, double time_end){
		double x = time_now / time_end;
		return startx + (dif - startx) * -4 * (x * x - x);
	}


	//3点を通る直線グラフ
	static double graph3(double x0, double x1, double x2, double t1, double t_now, double t_end){
		if (t_now < t1){
			return (x1 - x0) * t_now / t1;
		}
		else{
			return (x2 - x1) * (t_now - t1) / (t_end - t1) + x1;
		}
	}

	//4点を通る直線グラフ
	static double graph4(double x0, double x1, double x2, double x3, double t1, double t2, double t_now, double t_end){
		if (t_now < t1){
			return (x1 - x0) * t_now / t1;
		}
		else if (t_now < t2){
			return (x2 - x1) * (t_now - t1) / (t2 - t1) + x1;
		}
		else{
			return (x3 - x2) * (t_now - t2) / (t_end - t2) + x2;
		}
	}


	//---------------以下、イージング曲線---------------

	/*
	t : 現在の時間
	b : 開始の値(開始時の座標やスケールなど)
	c : 開始と終了の値の差分
	d : Tweenの合計時間
	*/

	//イージング曲線 Cubic
	static double ease_cubic_in(double t, double b, double c, double d){
		t /= d;
		return c*t*t*t + b;
	}

	static double ease_cubic_out(double t, double b, double c, double d){
		t /= d;
		t = t - 1;
		return c*(t*t*t + 1) + b;
	}

	static double ease_cubic_inout(double t, double b, double c, double d){
		t /= d/2.0;
		if (t < 1){
			return c/2.0*t*t*t + b;
		}
		else{
			t = t - 2;
			return c/2.0 * (t*t*t + 2) + b;
		}
	}
	
	
	//イージング曲線 Sinusoidal
	static double ease_sin_in(double t, double b, double c, double d){
		return -c * cos(t/d * (PI/2.0)) + c + b;
	}

	static double ease_sin_out(double t, double b, double c, double d){
		return c * sin(t/d * (PI/2.0)) + b;
	}

	static double ease_sin_inout(double t, double b, double c, double d){
		return -c/2.0 * (cos(PI*t/d) - 1) + b;
	}
	
	//イージング曲線 Exponential
	static double ease_exp_in(double t, double b, double c, double d){
		return c * pow(2.0, (10*(t/d - 1))) + b;
	}

	static double ease_exp_out(double t, double b, double c, double d){
		return c * (-(pow(2.0,(-10.0 * t/d))) + 1) + b;
	}

	static double ease_exp_inout(double t, double b, double c, double d){
		t /= d/2.0;
		if(t < 1)
			return c/2.0 * pow(2.0,(10.0 * (t-1))) + b;
		t = t - 1;
		return c/2.0 * (-(pow(2.0,(-10*t))) + 2 ) + b;
	}

	//イージング曲線 Circular
	static double ease_sqrt_in(double t, double b, double c, double d){
		t /= d;
		return -c * (sqrt(1 - t*t) - 1) + b;
	}

	static double ease_sqrt_out(double t, double b, double c, double d){
		t /= d;
		t = t - 1;
		return c * sqrt(1 - t*t) + b;
	}

	static double ease_sqrt_inout(double t, double b, double c, double d){
		t /= d/2.0;
		if(t < 1)
			return -c/2.0 * (sqrt(1 - t*t) + 1);
		t = t - 2;
		return c/2.0 * (sqrt(1 - t*t) + 1) + b;
	}
	


	//ベジェ曲線  p1->p2->p3  0<t<1
	static double bz_curve(double p1, double p2, double p3, double t){
		double tp = 1 - t;
		return t*t*p3 + 2*t*tp*p2 + tp*tp*p1;
	}

	//ベジェ曲線  p1->p2->p3  nowtime, endtime
	static double bz_curve(double p1, double p2, double p3, double nowt, double endt){
		double t = nowt / endt;
		double tp = 1 - t;
		return t*t*p3 + 2*t*tp*p2 + tp*tp*p1;
	}

	//アニメーション用・＼／＼／＼／となるグラフ
	static int Repeat(int frame, int loop_num)
	{
		--loop_num;
		frame = frame % (loop_num * 2);
		if (frame > loop_num)
			return loop_num * 2 - frame;
		else
			return frame;
	}

	//2次ベジエ曲線を計算する関数
	static Vector2 GetBezier2(const Vector2& Start, const Vector2& Control
		, const Vector2& End, float t)
	{
		Vector2 Result;
		// P = t^2*P0 + 2t(1-t)P1 + (1-t)^2P2
		Result.x = (t*t)*End.x + 2 * t*(1 - t)*Control.x + (1 - t)*(1 - t)*Start.x;
		Result.y = (t*t)*End.y + 2 * t*(1 - t)*Control.y + (1 - t)*(1 - t)*Start.y;
		return Result;
	}

	//2次ベジエ曲線で制御点も通るように引きたい場合の制御点を返す関数
	static Vector2 GetBezierPassC2(const Vector2 &Start, const Vector2 &End, const Vector2 &PassPoint)
	{
		Vector2 C;
		C.x = (4 * PassPoint.x - Start.x - End.x) / 2.0f;
		C.y = (4 * PassPoint.y - Start.y - End.y) / 2.0f;
		return C;
	}

	//Controlを通る2次ベジエ曲線を計算する関数
	static Vector2 GetBezierCtrl2(const Vector2& Start, const Vector2& Control
		, const Vector2& End, float t)
	{
		Vector2 C;//Controlを通る2次ベジエ曲線の制御点
		Vector2 Result;
		C.x = (4 * Control.x - Start.x - End.x) / 2.0f;
		C.y = (4 * Control.y - Start.y - End.y) / 2.0f;
		Result.x = (t*t)*End.x + 2 * t*(1 - t)*C.x + (1 - t)*(1 - t)*Start.x;
		Result.y = (t*t)*End.y + 2 * t*(1 - t)*C.y + (1 - t)*(1 - t)*Start.y;
		return Result;
	}

	//3次ベジエ曲線を計算する関数
	static Vector2 GetBezier3(const Vector2& Start, const Vector2& ControlPoint1
		, const Vector2& ControlPoint2, const Vector2& End, float t)
	{
		Vector2 Result;
		Result.x = (t*t*t)*End.x + 3 * t*t*(1 - t)*ControlPoint2.x
			+ 3 * t*(1 - t)*(1 - t)*ControlPoint1.x + (1 - t)*(1 - t)*(1 - t)*Start.x;
		Result.y = (t*t*t)*End.y + 3 * t*t*(1 - t)*ControlPoint2.y
			+ 3 * t*(1 - t)*(1 - t)*ControlPoint1.y + (1 - t)*(1 - t)*(1 - t)*Start.y;
		return Result;
	}
	//----------------以下、便利関数------------------

	//HSVをRGBに換算
	static int HSVtoRGB(int h, int s, int v){
		float f;
		int i, p, q, t;
		int rgb[3];

		i = ((int)floor(h / 60.0f)) % 6;
		f = (float)(h / 60.0f) - (float)floor(h / 60.0f);
		p = (int)(v * (1.0f - (s / 255.0f)));
		q = (int)(v * (1.0f - (s / 255.0f) * f));
		t = (int)(v * (1.0f - (s / 255.0f) * (1.0f - f)));

		switch(i){
		case 0 : rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
		case 1 : rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
		case 2 : rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
		case 3 : rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
		case 4 : rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
		case 5 : rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
		}

		return GetColor(rgb[0], rgb[1], rgb[2]);
	}
	
	//HSVでsetdrawbright
	static void SetDrawBrightHSV(int h, int s, int v){
		float f;
		int i, p, q, t;
		int rgb[3];

		i = ((int)floor(h / 60.0f)) % 6;
		f = (float)(h / 60.0f) - (float)floor(h / 60.0f);
		p = (int)(v * (1.0f - (s / 255.0f)));
		q = (int)(v * (1.0f - (s / 255.0f) * f));
		t = (int)(v * (1.0f - (s / 255.0f) * (1.0f - f)));

		switch(i){
		case 0 : rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
		case 1 : rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
		case 2 : rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
		case 3 : rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
		case 4 : rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
		case 5 : rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
		}

		SetDrawBright(rgb[0], rgb[1], rgb[2]);
	}

	//0xXXXXXXでSetDrawBrightする関数
	static void SetDrawBrightInt(int col){
		SetDrawBright(col >> 16, (col >> 8) & (0x00FF), col & 0x0000FF);
	}

	//自分の角度,相手の角度 2角の関係を返す　時計回り側に動いたほうが近ければ1 そうでなければ-1
	static int abs_angle(double angle1, double angle2){
		if(sin(angle2 - angle1)>0){
			return 1;
		}else{
			return -1;
		}
	}

	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  tarxとの差がerange以下でtarx = xにする
	static void moverate(double &x, double tarx, double rate, double erange = 1.0)
	{
		x = x * (1 - rate) + tarx * rate;
		if (abs(x - tarx) < erange){
			x = tarx;
		}
	}
	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  distが0.5以下でtarP = Pにする
	static void moverate(double &x, double &y, double tarx, double tary, double rate, double erangedist = 0.5)
	{
		x = x * (1 - rate) + tarx * rate;
		y = y * (1 - rate) + tary * rate;
		if (dist(x, y, tarx, tary) < erangedist){
			x = tarx;
			y = tary;
		}
	}
	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  distが0.5以下でtarP = Pにする
	static void moverate(Vector2 &v2, const Vector2 &tarv2, double rate, double erangedist = 0.5)
	{
		v2.x = v2.x * (1 - rate) + tarv2.x * rate;
		v2.y = v2.y * (1 - rate) + tarv2.y * rate;
		if (dist(v2.x, v2.y, tarv2.x, tarv2.y) < erangedist){
			v2 = tarv2;
		}
	}

	
	//原点との距離を返す
	static double dist(double x, double y){
		return sqrt(x*x + y*y);
	}

	//2点の距離を返す
	static double dist(double x1, double y1, double x2, double y2){
		return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	}

	//2点の距離の2乗を返す
	static double distSqr(double x1, double y1, double x2, double y2){
		return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
	}


	//rateとcoolのセットのcoolを更新・boolを返す
	static bool coolcount(int &cool){
		if (cool > 0){
			cool--;
			return false;
		}
		else{
			cool = 0;
			return true;
		}
	}

	
};