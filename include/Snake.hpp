#pragma once
/**************************************************************************
*                      �  �  �  �      �  �  �                            *
*-------------------------------------------------------------------------*
*                                                                         *
* Project Name  : \Snake\                                                 *
* Project Type  : OpenGL application                                      *
* File Name     : Snake.h                                                 *
* Language      : Visual C++ MS VS 2019                                   *
* Programmer(s) : ��������� �.�.                                          *
* Modified By   : ��������� �.�.                                          *
* Created       : 26 / 04 / 2019                                          *
* Last Revision : 24 / 05 / 2019                                          *
* Comment(s)    : ���� "������"    					                      *
*                                                                         *
**************************************************************************/

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/audio/audio.h"
#include "cinder/Rand.h"
#include "cinder/params/Params.h"
#include <Windows.h>
#define WITH_ASSETS
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace gl;
using namespace audio;
using std::vector;
using std::pair;

class Location { // ����������� ����� - ���������
protected:
	float x; // ���������� X
	float y; // ���������� Y
public:   
	virtual void draw(void) = 0; // �������� ������
	virtual void moveto(float, float) = 0; // ����������� ������
};

class Point : public Location {
protected:
	float RED, GREEN, BLUE; // RGB
public:
	Point(int InitX = 0.f, int InitY = 0.f, float setRED = 0.0f, 
		float setGREEN = 1.0f, float setBLUE = 0.0f); // ����������� ������
	~Point(); // ����������
	void setx(float newX); // ������ ����� ���������� X
	void sety(float newY); // ������ ����� ���������� Y
	int getx(void);	// �������� x ���������� �����
	int gety(void);	// �������� y ���������� �����
	void setRGB(float newRED, float newGREEN, float newBLUE); // ������ ����
	void moveto(float NewX, float NewY) override; // ����������� ������
	void draw(void) override; // �������� ������ �����
};

class Square : public Point {
protected:
	int scale; // ������� �������� (���������� �������� �� �������)
public:
	Square(float InitX = 0.f, float InitY = 0.f, float setRED = 1.0f, 
		float setGREEN = 1.0f, float setBLUE = 0.0f, int Scale = 25); // �����������
	~Square(); // ����������
	void setscale(int newScale); // ������ ������ �������
	void draw(void) override; // �������� ������ �������
};

class Apple : public Square {
private:
	std::default_random_engine generator; // ��������� ���������� �����
public:
	Apple(float InitX = 0.f, float InitY = 0.f, float setRED = 1.0f,
		float setGREEN = 0.f, float setBLUE = 0.0f, int Scale = 25); // �����������
	~Apple(); // ����������
	int new_x(int N); // ������ ����� ��������� ���������� X
	int new_y(int M); // ������ ����� ��������� ���������� Y
};

class Snake : public Square {
private:
	int size; // ������ ������
	int dir; // ����������� ��������
	Point eye[2]; // ����� ��� ������
	VoiceRef EatAppleVoice; // ���� ��� �������� ������
	VoiceRef MovementVoice; // ���� ��� �������� ������
public:
	vector <pair <float, float>> snakemas; // ������ ��������� ������ ���� ������
	Snake(float InitX = 10, float InitY = 10, float setRED = 0.f, float setGREEN = 1.f, 
		float setBLUE = 0.f, int Scale = 25, int InitSize = 3, int initDir = 2); // �����������
	~Snake(); // ����������
	void draw(void) override; // �������� ������ ������
	void moveto(float x, float y) override; // ����������� ������
	void setdir(int NewDirection); // ������ �����������
	void updatesize(void); // ��������� ������ ������ �� 1
	int getsize(void); // �������� ������ ������
	bool bingo_with_head(float x, float y); // �������� ���������� ���������
	bool bingo_without_head(float x, float y);
	int new_x(void); // ����� ���������� X ��� ������
	int new_y(void); // ����� ���������� Y ��� ������
	void setSound(const char* assetnameEat, const char* assetnameMove); // ������ ����� ��� ������
	void playsoundEat(void); // ��������� ���� �������� ������
	void playsoundMove(void); // ��������� ���� �������� ������
	void set_eyes_color(float RED, float GREEN, float BLUE); // ������ ���� ���� ������
	void restart(void); // ������ ��������� ������� ��� ������
};
