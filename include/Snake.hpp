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
	      float setGREEN = 1.0f, float setBLUE = 0.0f); // class constructor
	~Point(); // class destructor
	void setx(float newX);	// set new x coordinate
	void sety(float newY);	// set new y coordinate
	auto getx(void) -> int;	// get x coordinate of point
	auto gety(void) -> int;	// get y coordinate of point
	void setRGB(float newRED, float newGREEN, float newBLUE); // set color
	void moveto(float NewX, float NewY) override; // move point
	void draw(void) override; // show figure point
};

class Square : public Point
{
protected:
	int scale; // square scale (number of pixels per side)
public:
	explicit Square(float InitX = 0.f, float InitY = 0.f, float setRED = 1.0f,
	                float setGREEN = 1.0f, float setBLUE = 0.0f, int Scale = 25); // class constructor
	~Square(); // class destructor
	void setscale(int newScale); // set a different scale
	void draw(void) override; // show figure SQUARE
};

class Apple : public Square
{
private:
	std::default_random_engine generator; // random number processor
public:
	Apple(float InitX = 0.f, float InitY = 0.f, float setRED = 1.0f,
	      float setGREEN = 0.f, float setBLUE = 0.0f, int Scale = 25); // class constructor
	~Apple(); // class destructor
	int new_x(int N); // set new random x coordinate
	int new_y(int M); // set new random y coordinate
};

class Snake : public Square
{
private:
	int size; // snake size
	int dir; // the direction of movement of the snake
	Point eye[2]; // eyes for the SNAKE
	VoiceRef EatAppleVoice; // the sound of eating an apple
	VoiceRef MovementVoice; // sound when turning the head
public:
	vector<pair<float, float>> snakemas; // an array of coordinates of body parts
	explicit Snake(float InitX = 10, float InitY = 10, float setRED = 0.f, float setGREEN = 1.f,
	               float setBLUE = 0.f, int Scale = 25, int InitSize = 3, int initDir = 2); // class constructor
	~Snake(); // class destructor
	void draw(void) override; // show the figure SNAKE
	void moveto(float x, float y) override; // move the snake
	void setDir(int NewDirection); // set direction
	void updatesize(void); // increase the size of the SNAKE by 1
	int getsize(void); // get snake size
	bool bingo_with_head(float x, float y); // coordinate matching check
	bool bingo_without_head(float x, float y);
	int new_x(void); // new X coordinate for the head
	int new_y(void); // new Y coordinate for the head
	void setSound(const char* assetnameEat, const char* assetnameMove); // set sounds for the SNAKE
	void playsoundEat(void); // play the sound of eating an apple
	void playsoundMove(void); // play the sound of turning the head of a snake
	void set_eyes_color(float RED, float GREEN, float BLUE); // set the color of the eyes of the snake
	void restart(void); // sets initial conditions for the SNAKE
};
