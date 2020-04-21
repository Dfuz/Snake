#include <cinder/app/AppBase.h>
#include "Snake.hpp"
#include "Resources.h"
#include <Windows.h>

/*-----------------------------------------------------------------------*/
/*           I M P L E M E N T A T I O N   OF   M E T H O D S			 */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/*                     CLASS METHODS Point                               */
/*-----------------------------------------------------------------------*/

Point::Point(int InitX, int InitY, float setRED, float setGREEN, float setBLUE)
{
	x = InitX;
	y = InitY;
	RED = setRED;
	GREEN = setGREEN;
	BLUE = setBLUE;
}

Point::~Point()
{
}

// set x coordinate
void Point::setx(float newX)
{
	x = newX;
}

// set y coordinate
void Point::sety(float newY)
{
	y = newY;
}

// get x coordinate
int Point::getx(void)
{
	return x;
}

// get y coordinate
int Point::gety(void)
{
	return y;
}

// задать цвет
void Point::setRGB(float newRED, float newGREEN, float newBLUE)
{
	RED = newRED;
	GREEN = newGREEN;
	BLUE = newBLUE;
}

// draw POINT
void Point::draw()
{
	color(Color(RED, GREEN, BLUE));
	drawSolidRect(Rectf(vec2(x - 2, y - 2), vec2(x + 2, y + 2)));
}

// move FIGURE
void Point::moveto(float NewX, float NewY)
{
	x = NewX; // change point coordinates
	y = NewY;
}

/*-----------------------------------------------------------------------*/
/*                        CLASS METHODS Square                           */
/*-----------------------------------------------------------------------*/
Square::Square(float InitX, float InitY, float setRED, float setGREEN, float setBLUE, int Scale)
	: Point(InitX, InitY, setRED, setGREEN, setBLUE)
{
	scale = Scale;
}

Square::~Square()
{
} 

// set the scale
void Square::setscale(int newScale)
{
	scale = newScale;
}

// draw SQUARE
void Square::draw()
{
	color(Color(RED, GREEN, BLUE));
	drawSolidRect(Rectf(vec2(x * scale, y * scale), vec2((x + 1) * scale, (y + 1) * scale)));
}

/*-----------------------------------------------------------------------*/
/*                     CLASS METHODS Apple                               */
/*-----------------------------------------------------------------------*/
Apple::Apple(float InitX, float InitY, float setRED, float setGREEN,
             float setBLUE, int Scale) : Square(InitX, InitY, setRED, setGREEN,
                                                setBLUE, Scale)
{
	generator.seed(time(nullptr));
}

Apple::~Apple()
{
}

int Apple::new_x(int N)
{
	std::uniform_int_distribution<int> distribution(0, N - 1);
	return distribution(generator);
}

int Apple::new_y(int M)
{
	std::uniform_int_distribution<int> distribution(0, M - 1);
	return distribution(generator);
}

/*-----------------------------------------------------------------------*/
/*                     CLASS METHODS Snake                               */
/*-----------------------------------------------------------------------*/
Snake::Snake(float InitX, float InitY, float setRED, float setGREEN, float setBLUE,
             int Scale, int InitSize, int initDir) : Square(InitX, InitY, setRED, setGREEN,
                                                            setBLUE, Scale)
{
	size = InitSize;
	dir = initDir;
	pair<int, int> buf;
	buf.first = -100.f;
	buf.second = -100.f;
	for (auto i = 0; i < InitSize; i++)
	{
		snakemas.push_back(buf);
		buf.first = -300.f; // put it off the screen so that 
							// the loss condition does not work
	}
	eye[0].setRGB(0.f, 0.f, 1.f);
	eye[1].setRGB(0.f, 0.f, 1.f);
}

Snake::~Snake()
{
}

// draw a SNAKE
void Snake::draw()
{
	color(Color(RED, GREEN, BLUE));
	for (auto now : snakemas)
		drawSolidRect(Rectf(vec2((now.first + 0.1) * scale, (now.second + 0.1) * scale),
		                    vec2((now.first + 0.9) * scale, (now.second + 0.9) * scale)));

	if (dir == 0)
	{
		// if the SNAKE moves DOWN
		eye[0].setx((x + 0.3) * scale); // change the coordinates of the eyes
		eye[0].sety((y + 0.6) * scale); // depending on the direction
		eye[1].setx((x + 0.7) * scale);
		eye[1].sety((y + 0.6) * scale);

		color(Color(1.f, 0.1f, 0.f)); // tongue rendering
		drawSolidRect(Rectf(vec2((x + 0.4) * scale, (y + 0.9) * scale),
		                    vec2((x + 0.6) * scale, (y + 1.1) * scale)));
	}
	else if (dir == 1)
	{
		// if the SNAKE moves LEFT
		color(Color(RED, GREEN, BLUE));
		eye[0].setx((x + 0.4) * scale);
		eye[0].sety((y + 0.3) * scale);
		eye[1].setx((x + 0.4) * scale);
		eye[1].sety((y + 0.7) * scale);

		color(Color(1.f, 0.f, 0.f)); // tongue rendering
		drawSolidRect(Rectf(vec2((x - 0.1) * scale, (y + 0.4) * scale),
		                    vec2((x + 0.1) * scale, (y + 0.6) * scale)));
	}
	else if (dir == 2)
	{
		// if the SNAKE moves to the RIGHT
		color(Color(RED, GREEN, BLUE));
		eye[0].setx((x + 0.6) * scale);
		eye[0].sety((y + 0.3) * scale);
		eye[1].setx((x + 0.6) * scale);
		eye[1].sety((y + 0.7) * scale);

		color(Color(1.f, 0.f, 0.f)); // tongue rendering
		drawSolidRect(Rectf(vec2((x + 0.9) * scale, (y + 0.4) * scale),
		                    vec2((x + 1.1) * scale, (y + 0.6) * scale)));
	}
	else if (dir == 3)
	{
		// if the SNAKE moves UP
		color(Color(RED, GREEN, BLUE));
		eye[0].setx((x + 0.7) * scale);
		eye[0].sety((y + 0.4) * scale);
		eye[1].setx((x + 0.3) * scale);
		eye[1].sety((y + 0.4) * scale);

		color(Color(1.f, 0.1f, 0.f)); // tongue rendering
		drawSolidRect(Rectf(vec2((x + 0.4) * scale, (y - 0.1) * scale),
		                    vec2((x + 0.6) * scale, (y + 0.1) * scale)));
	}
	eye[0].draw(); // eyes
	eye[1].draw(); // rendering
}

// move the snake
void Snake::moveto(float NewX, float NewY)
{
	x = NewX;
	y = NewY;
	for (unsigned int i = snakemas.size(); i > 1; --i)
	{
		snakemas.at(i - 1).first = snakemas.at(i - 2).first;
		snakemas.at(i - 1).second = snakemas.at(i - 2).second;
	}
	snakemas.at(0).first = x;
	snakemas.at(0).second = y;
}

// new x coordinate
int Snake::new_x()
{
	if (dir == 1) return x - 1;
	if (dir == 2) return x + 1;
	return x;
}

// new y coordinate
int Snake::new_y()
{
	if (dir == 3) return y - 1;
	if (dir == 0) return y + 1;
	return y;
}

/**
 * \brief Set sounds for the snake
 * \param assetnameEat eat sound
 * \param assetnameMove move sound
 */
void Snake::setSound(const char* assetnameEat, const char* assetnameMove)
{
#ifdef WITH_ASSETS
	audio::SourceFileRef sound = audio::load(app::loadAsset(assetnameEat));
	EatAppleVoice = audio::Voice::create(sound);
	EatAppleVoice->setVolume(0.03f);
	sound = audio::load(app::loadAsset(assetnameMove));
	MovementVoice = audio::Voice::create(sound);
	MovementVoice->setVolume(0.01f);
 
#else
	SourceFileRef sound = load(loadResource(EATAPPLE_SOUND));
	EatAppleVoice = Voice::create(sound);
	EatAppleVoice->setVolume(0.03f);
	sound = load(loadResource(MOVEMENT_SOUND));
	MovementVoice = Voice::create(sound);
	MovementVoice->setVolume(0.01f);
#endif // WITH_ASSETS
}

void Snake::playsoundEat(void)
{
	EatAppleVoice->start();
}

void Snake::playsoundMove(void)
{
	MovementVoice->start();
}

// set the color of the eyes of the snake
void Snake::set_eyes_color(float RED, float GREEN, float BLUE)
{
	eye[0].setRGB(RED, GREEN, BLUE);
	eye[1].setRGB(RED, GREEN, BLUE);
}

// restart game
void Snake::restart(void)
{
	snakemas.clear();
	size = 3;
	dir = 2;
	pair<int, int> buf;
	buf.first = -100.f;
	buf.second = -100.f;
	for (auto i = 0; i < 3; i++)
	{
		snakemas.push_back(buf);
		buf.first = -300.f; /* put it off the screen so that 
							   the loss condition does not work	*/
	}
}

/**
 * \brief Set the direction of movement
 * \param NewDirection: <br>
 * 0 - turn down <br>
 * 1 - turn left <br>
 * 2 - turn right <br>
 * 3 - turn up <br>
 * the other is to do nothing
 */
auto Snake::setDir(const int NewDirection) -> void
{
	switch (NewDirection)
	{
	case 0:
		if (dir != 3 && dir != 0)
		{
			if (size > 1)
			{
				if (snakemas.at(0).first != snakemas.at(1).first)
				{
					dir = 0;
					playsoundMove();
				}
			}
			else
			{
				dir = 0;
				playsoundMove();
			}
		}
		break;

	case 1:
		if (dir != 2 && dir != 1)
		{
			if (size > 1)
			{
				if (snakemas.at(0).second != snakemas.at(1).second)
				{
					dir = 1;
					playsoundMove();
				}
			}
			else
			{
				dir = 1;
				playsoundMove();
			}
		}
		break;

	case 2:
		if (dir != 1 && dir != 2)
		{
			if (size > 1)
			{
				if (snakemas.at(0).second != snakemas.at(1).second)
				{
					dir = 2;
					playsoundMove();
				}
			}
			else
			{
				dir = 2;
				playsoundMove();
			}
		}
		break;

	case 3:
		if (dir != 0 && dir != 3)
		{
			if (size > 1)
			{
				if (snakemas.at(0).first != snakemas.at(1).first)
				{
					dir = 3;
					playsoundMove();
				}
			}
			else
			{
				dir = 3;
				playsoundMove();
			}
		}
		break;
	default: return;
	} // switch
}

// increase the size of the SNAKE by 1 unit
void Snake::updatesize()
{
	size++;
	pair<float, float> buffer;
	buffer.first = -5;
	buffer.second = -5;
	snakemas.push_back(buffer);
}

// get SNAKE size
int Snake::getsize()
{
	return size;
}

// find out if the coordinates coincided with the coordinates of all parts of the SNAKE
bool Snake::bingo_with_head(float x, float y)
{
	for (auto now : snakemas)
	{
		if (x == now.first && y == now.second)
			return true;
	}
	return false;
}

bool Snake::bingo_without_head(float x, float y)
{
	for (ULONG i = 1; i < snakemas.size(); i++)
		if (x == snakemas.at(i).first && y == snakemas.at(i).second)
			return true;
	return false;
}
