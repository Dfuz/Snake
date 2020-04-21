#pragma once
/**************************************************************************
* Project Name  : \Snake\                                                 *
* Project Type  : OpenGL application                                      *
* File Name     : Snake.hpp                                               *
* Language      : Visual C++ MS VS 2019                                   *
* Programmer(s) : Perfilyev Vadim                                         *
* Modified By   : Perfilyev Vadim                                         *
* Created       : 26 / 04 / 2019                                          *
* Last Revision : 21 / 04 / 2020                                          *
* Comment(s)    : GAME "SNAKE"    					                      *
**************************************************************************/

#include "cinder/gl/gl.h"
#include "cinder/audio/audio.h"
#include "cinder/Rand.h"
#include "cinder/params/Params.h"
#include <Windows.h>
//#define WITH_ASSETS

using namespace ci;
using namespace app;
using namespace gl;
using namespace audio;
using std::vector;
using std::pair;

/**
 * \brief Abstract class - interface
 */
class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void draw(void) = 0;			// draw a figure
	virtual void moveto(float, float) = 0;	// move figure
};

class Point : public GameObject
{
protected:
	float RED, GREEN, BLUE; // RGB
	float x; // X coordinate
	float y; // Y coordinate
public:
	Point(int InitX = 0.f, int InitY = 0.f, float setRED = 0.0f,
	      float setGREEN = 1.0f, float setBLUE = 0.0f); // конструктор класса
	~Point(); // деструктор
	void setx(float newX);	// задать новую координату X
	void sety(float newY);	// задать новую координату Y
	auto getx(void) -> int;	// получить x координату точки
	auto gety(void) -> int;	// получить y координату точки
	void setRGB(float newRED, float newGREEN, float newBLUE); // задать цвет
	void moveto(float NewX, float NewY) override; // переместить фигуру
	void draw(void) override; // показать фигуру ТОЧКА
};

class Square : public Point
{
protected:
	int scale; // масштаб квадрата (количество пикселей на сторону)
public:
	explicit Square(float InitX = 0.f, float InitY = 0.f, float setRED = 1.0f,
	                float setGREEN = 1.0f, float setBLUE = 0.0f, int Scale = 25); // конструктор
	~Square(); // деструктор
	void setscale(int newScale); // задать другой масштаб
	void draw(void) override; // показать фигуру КВАДРАТ
};

class Apple : public Square
{
private:
	std::default_random_engine generator; // random number processor
public:
	Apple(float InitX = 0.f, float InitY = 0.f, float setRED = 1.0f,
	      float setGREEN = 0.f, float setBLUE = 0.0f, int Scale = 25); 
	~Apple(); // деструктор
	int new_x(int N); // задать новую случайную координату X
	int new_y(int M); // задать новую случайную координату Y
};

class Snake : public Square
{
private:
	int size; // размер змейки
	int dir; // направление движения
	Point eye[2]; // глаза для ЗМЕЙКИ
	VoiceRef EatAppleVoice; // звук при поедании яблока
	VoiceRef MovementVoice; // звук при повороте головы
public:
	vector<pair<float, float>> snakemas; // массив координат частей тела ЗМЕЙКИ
	explicit Snake(float InitX = 10, float InitY = 10, float setRED = 0.f, float setGREEN = 1.f,
	               float setBLUE = 0.f, int Scale = 25, int InitSize = 3, int initDir = 2); // конструктор
	~Snake(); // деструктор
	void draw(void) override; // показать фигуру ЗМЕЙКА
	void moveto(float x, float y) override; // переместить ЗМЕЙКУ
	void setDir(int NewDirection); // задать направление
	void updatesize(void); // увеличить размер ЗМЕЙКИ на 1
	int getsize(void); // получить размер ЗМЕЙКИ
	bool bingo_with_head(float x, float y); // проверка совпадения координат
	bool bingo_without_head(float x, float y);
	int new_x(void); // новая координата X для головы
	int new_y(void); // новая координата Y для головы
	void setSound(const char* assetnameEat, const char* assetnameMove); // задать звуки для ЗМЕЙКИ
	void playsoundEat(void); // play the sound of eating an apple
	void playsoundMove(void); // play the sound of turning the head of a snake
	void set_eyes_color(float RED, float GREEN, float BLUE); // set the color of the eyes of the snake
	void restart(void); // sets initial conditions for the SNAKE
};
