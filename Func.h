#pragma once

#include <DxLib.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "myglobal.h"
#include "Source.h"

/*
//�V���O���g��Draw�N���X
//Vector2�N���X
//�V���O���g��Random�N���X
------------------�ȉ��A�����蔻��---------------------
------------------�ȉ��A�ɍ��W����XY���W------------------
------------------�ȉ��A��]---------------------
------------------�ȉ��A�x�N�g��---------------------
------------------�ȉ��A�C�[�W���O�Ȑ�---------------
------------------�ȉ��A�֗��֐�------------------
*/


//�V���O���g��Draw�N���X
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

	//�B�ꑶ�݂���C���X�^���X��Ԃ�
	static Draw& get()
	{
		static Draw inst;
		return inst;
	}

	static void setdxdy(int x, int y){
		get().dx = x;
		get().dy = y;
	}


	//�ʏ�̕`��E���W�͍�����w��
	static void normal(int x, int y, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawGraph(x + get().dx, y + get().dy, GrHandle, 1);
	}

	//�摜�̒����̍��W���w�肵�ĕ`��
	static void center(int x, int y, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRotaGraph(x + get().dx, y + get().dy, 1.0, 0.0, GrHandle, 1, TurnFlag);
	}

	//�g��E��]�`��
	static void exrot(int x, int y, double ExtRate, double Angle, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRotaGraph(x + get().dx, y + get().dy, ExtRate, Angle, GrHandle, 1, TurnFlag);
	}

	//�g��E��]�E�����w��`��
	static void exrot3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRotaGraph3(x + get().dx, y + get().dy, cx, cy, ExtRateX, ExtRateY, Angle, GrHandle, 1, TurnFlag);
	}

	//���R�ό`�`��
	static void modi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawModiGraph(
			x1 + get().dx, y1 + get().dy, x2 + get().dx, y2 + get().dy,
			x3 + get().dx, y3 + get().dy, x4 + get().dx, y4 + get().dy,
			GrHandle, 1);
	}

	//����E�E�����w�肵�ĕ`��
	static void modi2(int x1, int y1, int x2, int y2, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawExtendGraph(x1 + get().dx, y1 + get().dy, x2 + get().dx, y2 + get().dy, GrHandle, 1);
	}

	//�ȉ~��ɃO���t��`��@r�ŉ~�̔��a�Erate:�c��r��rate�̔�̕��Ђ��Ⴐ������Eangle:��]�p
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

	//�摜�̎w�肵�������̂ݕ`��@�`����W�E������W�E�`��摜�T�C�Y
	static void trim(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRectGraph(DestX + get().dx, DestY + get().dy, SrcX, SrcY, Width, Height, GrHandle, 1, TurnFlag);
	}

	//�T�[�N���Q�[�W�`��@(dx, dy)���V�t�g
	static void circlegauge(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawCircleGauge(x + get().dx, y + get().dy, 100, GrHandle, 100 - percent);
	}

	//�T�[�N���Q�[�W�`��i�t�����j�@(dx, dy)���V�t�g
	static void circlegauge_rev(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawCircleGauge(x + get().dx, y + get().dy, percent, GrHandle);
	}

	//�}�`�`��֐�

	//����`��
	static void line(int sx, int sy, int ex, int ey, int color, int Alpha, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawLine(sx + get().dx, sy + get().dy, ex + get().dx, ey + get().dy, color, Thickness);
	}

	//�Ǝ�
	//�n�_�ƏI�_�ւ̋����A�p�x���w�肵�Đ���`��
	static void lineangle(int sx, int sy, int r, double angle, int color, int Alpha, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawLine(sx + get().dx, sy + get().dy, sx + r * cos(angle) + get().dx, sy + r * sin(angle) + get().dy, color, Thickness);
	}

	//����`��
	static void box(int x1, int y1, int x2, int y2, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawBox(x1 + get().dx, y1 + get().dy, x2 + get().dx, y2 + get().dy, color, 1);
	}

	//�Ǝ�
	//���S���w�肵�Ĕ���`��
	static void centerbox(int centerx, int centery, int width, int height, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawBox(
			centerx - width / 2 + get().dx, centery - height / 2 + get().dy,
			centerx + width / 2 + get().dx, centery + height / 2 + get().dy,
			color, 1);
	}

	//�~��`��
	static void circle(int x, int y, int r, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawCircle(x + get().dx, y + get().dy, r, color, 1);
	}

	//�O�p�`��`��
	static void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawTriangle(x1 + get().dx, y1 + get().dy, x2 + get().dx, y2 + get().dy, x3 + get().dx, y3 + get().dy, color, 1);
	}


	//�����`��֐�

	//������`��
	static void text(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawFormatStringToHandle(x + get().dx, y + get().dy, color, fonthandle, "%s", str.c_str());
	}

	//�w�肵�����W�𒆐S�ɕ�����`��
	static void centertext(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		int wd = GetDrawFormatStringWidthToHandle(fonthandle, "%s", str.c_str());
		DrawFormatStringToHandle(x + get().dx - wd / 2, y + get().dy, color, fonthandle, "%s", str.c_str());
	}

	//�����̉E��̍��W���w�肵�ĕ�����`��
	static void righttext(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		int wd = GetDrawFormatStringWidthToHandle(fonthandle, "%s", str.c_str());
		DrawFormatStringToHandle(x + get().dx - wd, y + get().dy, color, fonthandle, "%s", str.c_str());
	}
};


//�V���O���g��Draw_�i�h���[�A���_�[�o�[�j�N���X
//dx,dy���C�����Ȃ�
class Draw_
{
	Draw_(){
	}
	Draw_(const Draw_& r) = delete;
	Draw_& operator=(const Draw_& r) = delete;
public:

	//�B�ꑶ�݂���C���X�^���X��Ԃ�
	static Draw_& get()
	{
		static Draw_ inst;
		return inst;
	}


	//�ʏ�̕`��E���W�͍�����w��
	static void normal(int x, int y, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawGraph(x, y, GrHandle, 1);
	}

	//�摜�̒����̍��W���w�肵�ĕ`��
	static void center(int x, int y, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRotaGraph(x, y, 1.0, 0.0, GrHandle, 1, TurnFlag);
	}

	//�g��E��]�`��
	static void exrot(int x, int y, double ExtRate, double Angle, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRotaGraph(x, y, ExtRate, Angle, GrHandle, 1, TurnFlag);
	}

	//�g��E��]�E�����w��`��
	static void exrot3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRotaGraph3(x, y, cx, cy, ExtRateX, ExtRateY, Angle, GrHandle, 1, TurnFlag);
	}

	//���R�ό`�`��
	static void modi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawModiGraph(
			x1, y1, x2, y2,
			x3, y3, x4, y4,
			GrHandle, 1);
	}

	//����E�E�����w�肵�ĕ`��
	static void modi2(int x1, int y1, int x2, int y2, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawExtendGraph(x1, y1, x2, y2, GrHandle, 1);
	}

	//�摜�̎w�肵�������̂ݕ`��@�`����W�E������W�E�`��摜�T�C�Y
	static void trim(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GrHandle, int Alpha, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawRectGraph(DestX, DestY, SrcX, SrcY, Width, Height, GrHandle, 1, TurnFlag);
	}

	//�T�[�N���Q�[�W�`��@(dx, dy)���V�t�g
	static void circlegauge(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawCircleGauge(x, y, 100, GrHandle, 100 - percent);
	}

	//�T�[�N���Q�[�W�`��i�t�����j�@(dx, dy)���V�t�g
	static void circlegauge_rev(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawCircleGauge(x, y, percent, GrHandle);
	}

	//�}�`�`��֐�

	//����`��
	static void line(int sx, int sy, int ex, int ey, int color, int Alpha, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawLine(sx, sy, ex, ey, color, Thickness);
	}

	//�Ǝ�
	//�n�_�ƏI�_�ւ̋����A�p�x���w�肵�Đ���`��
	static void lineangle(int sx, int sy, int r, double angle, int color, int Alpha, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawLine(sx, sy, sx + r * cos(angle), sy + r * sin(angle), color, Thickness);
	}

	//����`��
	static void box(int x1, int y1, int x2, int y2, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawBox(x1, y1, x2, y2, color, 1);
	}

	//�Ǝ�
	//���S���w�肵�Ĕ���`��
	static void centerbox(int centerx, int centery, int width, int height, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawBox(
			centerx - width / 2, centery - height / 2,
			centerx + width / 2, centery + height / 2,
			color, 1);
	}

	//�~��`��
	static void circle(int x, int y, int r, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawCircle(x, y, r, color, 1);
	}

	//�O�p�`��`��
	static void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawTriangle(x1, y1, x2, y2, x3, y3, color, 1);
	}


	//�����`��֐�

	//������`��
	static void text(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		DrawFormatStringToHandle(x, y, color, fonthandle, "%s", str.c_str());
	}

	//�w�肵�����W�𒆐S�ɕ�����`��
	static void centertext(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		int wd = GetDrawFormatStringWidthToHandle(fonthandle, "%s", str.c_str());
		DrawFormatStringToHandle(x - wd / 2, y, color, fonthandle, "%s", str.c_str());
	}

	//�����̉E��̍��W���w�肵�ĕ�����`��
	static void righttext(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode = DX_BLENDMODE_ALPHA){
		SetDrawBlendMode(BlendMode, Alpha);
		int wd = GetDrawFormatStringWidthToHandle(fonthandle, "%s", str.c_str());
		DrawFormatStringToHandle(x - wd, y, color, fonthandle, "%s", str.c_str());
	}
};



//�}�E�X���W�E�L�[��ԁE�N������̃t���[����

//!!!!!!!!!!!!! ���� !!!!!!!!!!!!!
//get����O��static�����o�ɃA�N�Z�X����͕̂s�\

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

	//�L�[��������Ă��邩��bool�ŕԂ�
	static bool keynow(int i){
		return get().keystate[i] > 0;
	}

	//�L�[�������ꂽ�t���[������true��Ԃ�
	static bool keydown(int i){
		return (get().keystate[i] == 1 && get().keystate_pre[i] != -1);
	}

	//�L�[�������ꂽ�t���[������true��Ԃ�
	static bool keyup(int i){
		return (get().keystate[i] == 0) && (get().keystate_pre[i] > 0);
	}

	//�L�[��������Ă���t���[����Ԃ�
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

	//Allzeroframe�̊�keystate�����ׂ�0��
	static void setAllzeroframe(int t){
		if (t > 0){
			get().Allzeroframe = t;
		}
	}

	//Allzerooff���Ă΂��܂�keystate�����ׂ�0��
	static void Allzeroon(){
		get().IsAllzero = true;
	}

	//keystate���ׂ�0 ������ Allzeroframe��0��
	static void Allzerooff(){
		get().IsAllzero = false;
		get().Allzeroframe = 0;
	}


private:
	int m_mousex;
	int m_mousey;//�}�E�X���W
	int m_eframe;//�o�߃t���[��

	char buf[256];
	int keystate[256];
	int keystate_pre[256];

	//setAllzeroframe�֐��Ń��b�N�����t���[���� waitframe>0�őS�z����e0�Ɂ@
	int Allzeroframe;

	//IsAll0 == true�őS�z����e0��
	bool IsAllzero;


	void do_update(){
		GetHitKeyStateAll(buf);
		buf[250] = GetMouseInput() & MOUSE_INPUT_LEFT;
		buf[251] = ((GetMouseInput() & MOUSE_INPUT_RIGHT) == 0) ? 0 : 1;
		for (int i = 0; i< 256; i++){
			//1�t���[���O�̏���ۑ�
			keystate_pre[i] = keystate[i];
			//keystate���X�V
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
		//�}�E�X���W�X�V
		GetMousePoint(&m_mousex, &m_mousey);
		//�o�߃t���[���v��
		m_eframe++;
	}

	void Allzero(){
		for (int i = 0; i < 256; i++){
			keystate[i] = -1;
			keystate_pre[i] = -1;
		}
	}
};


//2������̓_��\���N���X
class Vector2
{
public:
	double x;
	double y;
	//�R���X�g���N�^��`
	Vector2() :x(0), y(0){}
	Vector2(double x_, double y_) :x(x_), y(y_){}
	//�I�y���[�^�[�I�[�o�[���[�h
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

	//����֐�
	void Set(double x_, double y_)
	{
		x = x_; y = y_;
	}
	//���_�𒆐S�ɉ�]
	void Rotate(double rad)
	{
		double sint = sin(rad), cost = cos(rad);	//sin��cos�̒l
		double tx = x;	//�ꎞ�i�[
		x = cost*tx - sint*y;		// ( cos�� -sin��) ( x )
		y = sint*tx + cost*y;		// ( sin�� xos�� ) ( y )
	}
	//center�𒆐S�ɉ�]
	void RotateOnPoint(double rad, const Vector2 &center)
	{
		double sint = sin(rad), cost = cos(rad);	//sin��cos�̒l
		double tx = x - center.x;	//�ꎞ�i�[
		double ty = y - center.y;	//�ꎞ�i�[
		x = cost*tx - sint*ty + center.x;		// ( cos�� -sin��) ( x )
		y = sint*tx + cost*ty + center.y;		// ( sin�� xos�� ) ( y )
	}
	//dx,dy�������ړ�
	void Translate(double dx, double dy)
	{
		x += dx;
		y += dy;
	}
	//�x�N�g���̑傫����Ԃ�
	double magnitude(){
		return sqrt(x*x + y*y);
	}
	//�x�N�g���𐳋K������
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
	//Set�֐��B���と�E�と�������E��
	void Set(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
	{
		pos[0].Set(x1, y1);
		pos[1].Set(x2, y2);
		pos[2].Set(x3, y3);
		pos[3].Set(x4, y4);
	}
	//Set�֐��B����ƉE�����`
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
	//�����ƕ��������`
	void Set(Vector2& center, float Width, float Height)
	{
		pos[0].Set(center.x - Width / 2, center.y - Height / 2);
		pos[1].Set(center.x + Width / 2, center.y - Height / 2);
		pos[2].Set(center.x - Width / 2, center.y + Height / 2);
		pos[3].Set(center.x + Width / 2, center.y + Height / 2);
		width = (int)Width;
		height = (int)Height;
	}
	//��`���w��p�x������]
	void Rotate(float rad)
	{
		for (int i = 0; i<4; i++)
			pos[i].Rotate(rad);
	}
	//��`���w�蕪�������s�ړ�
	void Translate(float x, float y)
	{
		Vector2 Temp(x, y);
		for (int i = 0; i<4; i++)
			pos[i] += Temp;
	}
};
//�V���O���g��Random�N���X
class Random
{
	std::mt19937 mt;
	//�R���X�g���N�^�@SeedSetUseRD��MT�̏����l��ݒ�
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
	//MT�̏����l��Random_device���g�p���Đݒ�
	static void SeedSetUseRD(){
		std::random_device r;
		get().mt.seed(r());
	}
	//MT�̏����l�ݒ�
	static void Initialize(int seed)
	{
		get().mt.seed(seed);
	}
	//mt�G���W���{�̂��擾
	static std::mt19937& getMT(){ return get().mt; }
	//���S����
	static unsigned int RamdomDeviceValue()
	{
		std::random_device r;
		return r();
	}

	//�ʏ��rand�擾
	static int Rand(){
		return get().mt();
	}
	//0~max�w��擾(int)
	static int Rand(int max)
	{
		std::uniform_int_distribution<int> uid(0, max);
		return uid(get().mt);
	}
	//min~max��Ԃ�(int)
	static int Rand(int min, int max)
	{
		std::uniform_int_distribution<int> uid(min, max);
		return uid(get().mt);
	}
	//1��-1��Ԃ��֐�
	static int RandPM1(){
		std::uniform_int_distribution<int> uid(0, 1);
		return uid(get().mt) * 2 - 1;
	}
	//0~1��Ԃ�(double)
	static double Value()
	{
		std::uniform_real_distribution<double> urd(0, 1);
		return urd(get().mt);
	}
	//0~max��Ԃ�(double)
	static double FRand(double max)
	{
		std::uniform_real_distribution<double> urd(0, max);
		return urd(get().mt);
	}
	//min~max��Ԃ�(double)
	static double FRand(double min, double max)
	{
		std::uniform_real_distribution<double> urd(min, max);
		return urd(get().mt);
	}
	//���K���z
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
	//���W�A���Ŏ擾
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
	//���ar�̉~��̓_��Ԃ�
	static void RandOnCircle(double r, double &x, double &y){
		double randang = FRadRand();
		x = r * cos(randang);
		y = r * sin(randang);
	}
	//���ar�̉~��̓_��Ԃ��@���_����̊p�x���Ԃ�
	static void RandOnCircle(double r, double &x, double &y, double &ang){
		double randang = FRadRand();
		x = r * cos(randang);
		y = r * sin(randang);
		ang = randang;
	}
	//���ar�̉~�����̓_��Ԃ�
	static void RandInCircle(double r, double &x, double &y){
		double randang = FRadRand();
		double rr = r * Value();
		x = rr * cos(randang);
		y = rr * sin(randang);
	}
	//���ar�̉~�����̓_��Ԃ��@���_����̊p�x���Ԃ�
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
	//------------------�ȉ��A�����蔻��-------------------- -

	//2��
	template<typename T> static T Sqr(T x)
	{
		return x*x;
	}
	//���όv�Z
	template<typename T> static T Dot2D(T Ax, T Ay, T Bx, T By)
	{
		return Ax*Bx + Ay*By;
	}
	//�O�όv�Z
	template<typename T> static T Cross2D(T Ax, T Ay, T Bx, T By)
	{
		return Ax*By - Bx*Ay;
	}

	
	//�~�`���m
	static bool Circles(double x1, double y1, double r1, double x2, double y2, double r2)
	{
		return Sqr(x2 - x1) + Sqr(y2 - y1) < Sqr(r2 + r1);
	}
	static bool Circles(const Vector2& c1, double r1, const Vector2& c2, double r2)
	{
		return Sqr(c2.x - c1.x) + Sqr(c2.y - c1.y) < Sqr(r2 + r1);
	}
	//��`���m
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

	//�_�ƕ��̂���� (�_�̍��W�A���̂�����̎n�_�E�I�_)
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

	//�_�ƕ��̂���� (�_�̍��W�A���̂�����̎n�_�E�I�_�܂ł̋����A�p�x)
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

	//�_�Ƌ�`
	bool BoxPoint(int px, int py, int box_cx, int box_cy, int box_width, int box_height){
		return abs(px - box_cx) < box_width / 2 && abs(py - box_cy) < box_height / 2;
	}

	//�_�Ɖ�]��`(��`���͖̂���]�œn������
	static bool DotAndRotRect(Vector2 dot, const Vector2& rectpos, const RectPF& rect, double rect_angle)
	{
		dot.Translate(-rectpos.x, -rectpos.y);
		dot.Rotate(-rect_angle);
		return	dot.x > rect._X(0) && dot.y > rect._Y(0) &&
			dot.x < rect._X(3) && dot.y < rect._Y(3);
	}
	//�~�Ɖ�]��`(��`���͖̂���]�œn������
	static bool CircleAndRotRect(Vector2 circle_pos, double circle_r, const Vector2& rectpos, const RectPF& rect, double rect_angle)
	{
		circle_pos.Translate(-rectpos.x, -rectpos.y);
		circle_pos.Rotate(-rect_angle);
		return circle_pos.x > rect._X(0) - circle_r && circle_pos.y > rect._Y(0) - circle_r
			&& circle_pos.x < rect._X(3) + circle_r && circle_pos.y < rect._Y(3) + circle_r;
	}
	//�ǉ�
	//�~(���acr,(cx,cy))�̋ߎ������`�Ɓ@�����`(����(rx1,ry1), �E��(rx2, ry2))�̓����蔻��
	static bool CircleAndRect(double cx, double cy, double cr, double rx1, double ry1, double rx2, double ry2){
		double rectx = (rx1 + rx2) / 2.0;
		double recty = (ry1 + ry2) / 2.0;
		return	cx > rx1 - cr && cy > ry1 - cr &&
			cx < rx2 + cr && cy < ry2 + cr;
	}
	//�������m(0�Ȃ炠�����ĂȂ��A0�ȏ�͂������Ă�
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
	//Lines�œ������Ă��ꍇ�͈ʒu���v�Z�ł���
	static Vector2 LinesCalcCrossPoint(double lines_result, double a_x, double a_y, double b_x, double b_y)
	{
		Vector2 AB(b_x - a_x, b_y - a_y);
		AB *= lines_result;
		AB.Translate(a_x, a_y);
		return AB;
	}
	//�~�Ɛ���
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
	//���ʂ̓_�Ƌ�`
	static bool DotAndRect(const Vector2& p, const RectPF& r)
	{
		return  r.pos[RectPF::LEFT_TOP].x <= p.x  && p.x <= r.pos[RectPF::RIGHT_BOTTOM].x
			&&  r.pos[RectPF::LEFT_TOP].y <= p.y  && p.y <= r.pos[RectPF::RIGHT_BOTTOM].y;
	}
	//�ǉ�
	//���ʂ̓_�Ƌ�`
	static bool DotAndRect(double px, double py, double b1x, double b1y, double b2x, double b2y)
	{
		return  b1x < px  && px < b2x
			&&  b1y < py  && py < b2y;
	}
	//����������p�`�̓����ɂ��邩�ǂ���
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

	

	//------------------�ȉ��A��]---------------------

	//���_�𒆐S��ang����]
	static void rotateonzero(double &x,  double &y, double ang){
		double sx = x - 0;
		double sy = y - 0;
		x = sx * cos(ang) - sy * sin(ang) + 0;
		y = sx * sin(ang) + sy * cos(ang) + 0;
	}
	
	//����_(centerx,centery)�𒆐S��ang����]
	static void rotateonpoint(double &x,  double &y,  double centerx, double centery, double ang){
		double sx = x - centerx;
		double sy = y - centery;
		x = sx * cos(ang) - sy * sin(ang) + centerx;
		y = sx * sin(ang) + sy * cos(ang) + centery;
	}
	

	//------------------�ȉ��A�x�N�g��---------------------

	//(���_����(sx,sy)�ւ̒P�ʃx�N�g�������߂�
	static void normalizedVector(double &vx, double &vy, double sx, double sy){
		double rd = atan2(sy, sx);
		vx = cos(rd);
		vy = sin(rd);
	}

	//(sx,sy)����(ex,ey)�ւ̒P�ʃx�N�g�������߂�
	static void normalizedVector(double &vx, double &vy, double sx, double sy, double ex, double ey){
		double rd = atan2(ey - sy, ex - sx);
		vx = cos(rd);
		vy = sin(rd);
	}


	//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɑ��
	static void calVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
		double rd = atan2(ey - sy, ex - sx);
		resultx = dist * cos(rd);
		resulty = dist * sin(rd);
	}

	//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɉ��Z
	static void addVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
		double rd = atan2(ey - sy, ex - sx);
		resultx += dist * cos(rd);
		resulty += dist * sin(rd);
	}

	//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɉ��Z
	static void addVector(double r, double angle, double &resultx, double &resulty){
		resultx += r * cos(angle);
		resulty += r * sin(angle);
	}

	//�ɍ��W�\������xy�\���ɒ���
	static void polartoxy(double &x, double &y, double r, double ang){
		x = r * cos(ang);
		y = r * sin(ang);
	}

	//�p�x���v�Z
	static double calAngle(double x, double y){
		return atan2(y, x);
	}
	
	//�p�x���v�Z
	static double calAngle(double sx, double sy, double ex, double ey){
		return atan2(ey - sy, ex - sx);
	}

	/*
	startx : �J�n�̒l(�J�n���̍��W��X�P�[���Ȃ�)
	enddif : �J�n�ƏI���̒l�̍���
	time_now : ���݂̎���
	time_end : Tween�̍��v����
	*/

	//�^�_�@�����������O���t
	static double linef(double startx, double dif, double time_now, double time_end){
		return startx + (dif - startx) * (1.0 - abs(time_end/2 - time_now) / (time_end/2) );
	}

	//�^�_�@����������2���Ȑ�
	static double quadraticf(double startx, double dif, double time_now, double time_end){
		double x = time_now / time_end;
		return startx + (dif - startx) * -4 * (x * x - x);
	}


	//3�_��ʂ钼���O���t
	static double graph3(double x0, double x1, double x2, double t1, double t_now, double t_end){
		if (t_now < t1){
			return (x1 - x0) * t_now / t1;
		}
		else{
			return (x2 - x1) * (t_now - t1) / (t_end - t1) + x1;
		}
	}

	//4�_��ʂ钼���O���t
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


	//---------------�ȉ��A�C�[�W���O�Ȑ�---------------

	/*
	t : ���݂̎���
	b : �J�n�̒l(�J�n���̍��W��X�P�[���Ȃ�)
	c : �J�n�ƏI���̒l�̍���
	d : Tween�̍��v����
	*/

	//�C�[�W���O�Ȑ� Cubic
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
	
	
	//�C�[�W���O�Ȑ� Sinusoidal
	static double ease_sin_in(double t, double b, double c, double d){
		return -c * cos(t/d * (PI/2.0)) + c + b;
	}

	static double ease_sin_out(double t, double b, double c, double d){
		return c * sin(t/d * (PI/2.0)) + b;
	}

	static double ease_sin_inout(double t, double b, double c, double d){
		return -c/2.0 * (cos(PI*t/d) - 1) + b;
	}
	
	//�C�[�W���O�Ȑ� Exponential
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

	//�C�[�W���O�Ȑ� Circular
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
	


	//�x�W�F�Ȑ�  p1->p2->p3  0<t<1
	static double bz_curve(double p1, double p2, double p3, double t){
		double tp = 1 - t;
		return t*t*p3 + 2*t*tp*p2 + tp*tp*p1;
	}

	//�x�W�F�Ȑ�  p1->p2->p3  nowtime, endtime
	static double bz_curve(double p1, double p2, double p3, double nowt, double endt){
		double t = nowt / endt;
		double tp = 1 - t;
		return t*t*p3 + 2*t*tp*p2 + tp*tp*p1;
	}

	//�A�j���[�V�����p�E�_�^�_�^�_�^�ƂȂ�O���t
	static int Repeat(int frame, int loop_num)
	{
		--loop_num;
		frame = frame % (loop_num * 2);
		if (frame > loop_num)
			return loop_num * 2 - frame;
		else
			return frame;
	}

	//2���x�W�G�Ȑ����v�Z����֐�
	static Vector2 GetBezier2(const Vector2& Start, const Vector2& Control
		, const Vector2& End, float t)
	{
		Vector2 Result;
		// P = t^2*P0 + 2t(1-t)P1 + (1-t)^2P2
		Result.x = (t*t)*End.x + 2 * t*(1 - t)*Control.x + (1 - t)*(1 - t)*Start.x;
		Result.y = (t*t)*End.y + 2 * t*(1 - t)*Control.y + (1 - t)*(1 - t)*Start.y;
		return Result;
	}

	//2���x�W�G�Ȑ��Ő���_���ʂ�悤�Ɉ��������ꍇ�̐���_��Ԃ��֐�
	static Vector2 GetBezierPassC2(const Vector2 &Start, const Vector2 &End, const Vector2 &PassPoint)
	{
		Vector2 C;
		C.x = (4 * PassPoint.x - Start.x - End.x) / 2.0f;
		C.y = (4 * PassPoint.y - Start.y - End.y) / 2.0f;
		return C;
	}

	//Control��ʂ�2���x�W�G�Ȑ����v�Z����֐�
	static Vector2 GetBezierCtrl2(const Vector2& Start, const Vector2& Control
		, const Vector2& End, float t)
	{
		Vector2 C;//Control��ʂ�2���x�W�G�Ȑ��̐���_
		Vector2 Result;
		C.x = (4 * Control.x - Start.x - End.x) / 2.0f;
		C.y = (4 * Control.y - Start.y - End.y) / 2.0f;
		Result.x = (t*t)*End.x + 2 * t*(1 - t)*C.x + (1 - t)*(1 - t)*Start.x;
		Result.y = (t*t)*End.y + 2 * t*(1 - t)*C.y + (1 - t)*(1 - t)*Start.y;
		return Result;
	}

	//3���x�W�G�Ȑ����v�Z����֐�
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
	//----------------�ȉ��A�֗��֐�------------------

	//HSV��RGB�Ɋ��Z
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
	
	//HSV��setdrawbright
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

	//0xXXXXXX��SetDrawBright����֐�
	static void SetDrawBrightInt(int col){
		SetDrawBright(col >> 16, (col >> 8) & (0x00FF), col & 0x0000FF);
	}

	//�����̊p�x,����̊p�x 2�p�̊֌W��Ԃ��@���v��葤�ɓ������ق����߂����1 �����łȂ����-1
	static int abs_angle(double angle1, double angle2){
		if(sin(angle2 - angle1)>0){
			return 1;
		}else{
			return -1;
		}
	}

	//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  tarx�Ƃ̍���erange�ȉ���tarx = x�ɂ���
	static void moverate(double &x, double tarx, double rate, double erange = 1.0)
	{
		x = x * (1 - rate) + tarx * rate;
		if (abs(x - tarx) < erange){
			x = tarx;
		}
	}
	//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  dist��0.5�ȉ���tarP = P�ɂ���
	static void moverate(double &x, double &y, double tarx, double tary, double rate, double erangedist = 0.5)
	{
		x = x * (1 - rate) + tarx * rate;
		y = y * (1 - rate) + tary * rate;
		if (dist(x, y, tarx, tary) < erangedist){
			x = tarx;
			y = tary;
		}
	}
	//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  dist��0.5�ȉ���tarP = P�ɂ���
	static void moverate(Vector2 &v2, const Vector2 &tarv2, double rate, double erangedist = 0.5)
	{
		v2.x = v2.x * (1 - rate) + tarv2.x * rate;
		v2.y = v2.y * (1 - rate) + tarv2.y * rate;
		if (dist(v2.x, v2.y, tarv2.x, tarv2.y) < erangedist){
			v2 = tarv2;
		}
	}

	
	//���_�Ƃ̋�����Ԃ�
	static double dist(double x, double y){
		return sqrt(x*x + y*y);
	}

	//2�_�̋�����Ԃ�
	static double dist(double x1, double y1, double x2, double y2){
		return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	}

	//2�_�̋�����2���Ԃ�
	static double distSqr(double x1, double y1, double x2, double y2){
		return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
	}


	//rate��cool�̃Z�b�g��cool���X�V�Ebool��Ԃ�
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