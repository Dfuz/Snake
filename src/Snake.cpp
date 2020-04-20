#include "Snake.hpp"

/*-----------------------------------------------------------------------*/
/*                Р Е А Л И З А Ц И Я    М Е Т О Д О В                   */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/*                     МЕТОДЫ КЛАССА Point                               */
/*-----------------------------------------------------------------------*/

Point::Point(int InitX, int InitY, float setRED, float setGREEN, float setBLUE) // конструктор
{
	x = InitX;
	y = InitY;
	RED = setRED;
	GREEN = setGREEN;
	BLUE = setBLUE;
}

Point::~Point(){}

// задать координату Y
void Point::setx(float newX)
{ 
	x = newX;
}

// задать координату X 
void Point::sety(float newY)
{ 
	y = newY;
}

// получить x координату 
int Point::getx(void) { 
	return x;
}

// получить x координату 
int Point::gety(void) { 
	return y;
}

// задать цвет
void Point::setRGB(float newRED, float newGREEN, float newBLUE)
{ 
	RED = newRED;
	GREEN = newGREEN;
	BLUE = newBLUE;
}

// отрисовать ТОЧКУ
void Point::draw() { 
	color(Color(RED, GREEN, BLUE));
	drawSolidRect(Rectf(vec2(x - 2, y - 2), vec2(x + 2, y + 2)));
}

// переместить ФИГУРУ
void Point::moveto(float NewX, float NewY) { 
	x = NewX; // поменять координаты ТОЧКИ
	y = NewY;
}

/*-----------------------------------------------------------------------*/
/*                        МЕТОДЫ КЛАССА Square                           */
/*-----------------------------------------------------------------------*/
Square::Square(float InitX, float InitY, float setRED, float setGREEN, float setBLUE, int Scale)
	: Point (InitX, InitY, setRED, setGREEN, setBLUE)
{
	scale = Scale;
}

Square::~Square() {} // формально пустое тело

// задать масштаб
void Square::setscale(int newScale)
{
	scale = newScale;
}

// отрисовать КВАДРАТ
void Square::draw() 
{
	color(Color(RED, GREEN, BLUE));
	drawSolidRect(Rectf(vec2(x * scale, y * scale), vec2((x + 1) * scale, (y + 1) * scale)));
}

/*-----------------------------------------------------------------------*/
/*                     МЕТОДЫ КЛАССА Apple                               */
/*-----------------------------------------------------------------------*/
Apple::Apple(float InitX, float InitY, float setRED, float setGREEN, 
	float setBLUE, int Scale) : Square (InitX, InitY, setRED, setGREEN, 
		setBLUE, Scale) {
	generator.seed(time(0));
}

Apple::~Apple() {}

int Apple::new_x(int N) {
	std::uniform_int_distribution<int> distribution(0, N - 1);
	return distribution(generator); 
}

int Apple::new_y(int M) {
	std::uniform_int_distribution<int> distribution(0, M - 1);
	return distribution(generator);
}

/*-----------------------------------------------------------------------*/
/*                     МЕТОДЫ КЛАССА Snake                               */
/*-----------------------------------------------------------------------*/
Snake::Snake (float InitX, float InitY, float setRED, float setGREEN, float setBLUE, 
	int Scale, int InitSize, int initDir) : Square (InitX, InitY, setRED, setGREEN, 
		setBLUE, Scale) 
{
	size = InitSize;
	dir = initDir;
	pair <int, int> buf;
	buf.first = -100.f;
	buf.second = -100.f;
	for (int i = 0; i < InitSize; i++) {
		snakemas.push_back(buf);
		buf.first = -300.f; // поставим за пределы экрана, чтобы
							// не сработало условие проигрыша
	}
	eye[0].setRGB(0.f, 0.f, 1.f);
	eye[1].setRGB(0.f, 0.f, 1.f);
}

Snake::~Snake() {}

 // отрисовать ЗМЕЙКУ
void Snake::draw() {
	color(Color(RED, GREEN, BLUE));
	for (auto now : snakemas)
		drawSolidRect(Rectf(vec2((now.first + 0.1) * scale, (now.second + 0.1) * scale), 
			vec2((now.first + 0.9) * scale, (now.second + 0.9) * scale)));
	
	if (dir == 0) { // если ЗМЕЙКА движется ВНИЗ
		eye[0].setx((x + 0.3) * scale); // в зависимости от направления
		eye[0].sety((y + 0.6) * scale); // менять координаты глаз
		eye[1].setx((x + 0.7) * scale);
		eye[1].sety((y + 0.6) * scale);

		color(Color(1.f, 0.1f, 0.f)); // отрисовка языка
		drawSolidRect(Rectf(vec2((x + 0.4) * scale, (y + 0.9) * scale),
			vec2((x + 0.6) * scale, (y + 1.1) * scale)));
	}
	else if (dir == 1) { // если ЗМЕЙКА движется ВЛЕВО
		color(Color(RED, GREEN, BLUE));
		eye[0].setx((x + 0.4) * scale);
		eye[0].sety((y + 0.3) * scale);
		eye[1].setx((x + 0.4) * scale);
		eye[1].sety((y + 0.7) * scale);
		 
		color(Color(1.f, 0.f, 0.f)); // отрисовка языка
		drawSolidRect(Rectf(vec2((x - 0.1) * scale, (y + 0.4) * scale),
			vec2((x + 0.1) * scale, (y + 0.6) * scale)));
	}
	else if (dir == 2) { // если ЗМЕЙКА движется ВПРАВО
		color(Color(RED, GREEN, BLUE));
		eye[0].setx((x + 0.6) * scale);
		eye[0].sety((y + 0.3) * scale);
		eye[1].setx((x + 0.6) * scale);
		eye[1].sety((y + 0.7) * scale);

		color(Color(1.f, 0.f, 0.f)); // отрисовка языка
		drawSolidRect(Rectf(vec2((x + 0.9) * scale, (y + 0.4) * scale),
			vec2((x + 1.1) * scale, (y + 0.6) * scale)));
	}
	else if (dir == 3) { // если ЗМЕЙКА движется ВВЕРХ
		color(Color(RED, GREEN, BLUE));
		eye[0].setx((x + 0.7) * scale);
		eye[0].sety((y + 0.4) * scale);
		eye[1].setx((x + 0.3) * scale);
		eye[1].sety((y + 0.4) * scale);

		color(Color(1.f, 0.1f, 0.f)); // отрисовка языка
		drawSolidRect(Rectf(vec2((x + 0.4) * scale, (y - 0.1) * scale),
			vec2((x + 0.6) * scale, (y + 0.1) * scale)));
	}
	eye[0].draw(); // отрисовка
	eye[1].draw(); // глаз
	return;
}

// переместить ЗМЕЙКУ
void Snake::moveto(float NewX, float NewY) 
{ 
	x = NewX; 
	y = NewY;
	for (unsigned int i = snakemas.size(); i > 1; --i) {
		snakemas.at(i - 1).first = snakemas.at(i - 2).first;
		snakemas.at(i - 1).second = snakemas.at(i - 2).second;
	}
	snakemas.at(0).first = x;
	snakemas.at(0).second = y;
	return;
}

// новая координата по X
int Snake::new_x() 
{
	if (dir == 1) return x - 1;
	else if (dir == 2) return x + 1;
	else return x;
}

// новая координата по Y
int Snake::new_y() 
{
	if (dir == 3) return y - 1;
	else if (dir == 0) return y + 1;
	else return y;
}

// задать звуки для ЗМЕЙКИ
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
	audio::SourceFileRef sound = audio::load(app::loadResource(EATAPPLE_SOUND));
	EatAppleVoice = audio::Voice::create(sound);
	EatAppleVoice->setVolume(0.03f);
	sound = audio::load(app::loadResource(MOVEMENT_SOUND));
	MovementVoice = audio::Voice::create(sound);
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

// задать цвет глаз ЗМЕЙКИ
void Snake::set_eyes_color(float RED, float GREEN, float BLUE)
{
	eye[0].setRGB(RED, GREEN, BLUE);
	eye[1].setRGB(RED, GREEN, BLUE);
	return;
}

// для рестарта игры
void Snake::restart(void)
{
	snakemas.clear();
	size = 3;
	dir = 2;
	pair <int, int> buf;
	buf.first = -100.f;
	buf.second = -100.f;
	for (int i = 0; i < 3; i++) {
		snakemas.push_back(buf);
		buf.first = -300.f; // поставим за пределы экрана, чтобы
							// не сработало условие проигрыша
	}
}

// задать направление движения
void Snake::setdir(int InitDir) { 
	switch (InitDir) {
	case 0:	
		if (dir != 3 && dir != 0) 
		{
			if (size > 1) {
				if (snakemas.at(0).first != snakemas.at(1).first) { dir = 0; playsoundMove(); }
			}
			else { dir = 0; playsoundMove(); }
		}	
		break;

	case 1: 
		if (dir != 2 && dir != 1) {
		if (size > 1) {
			if (snakemas.at(0).second != snakemas.at(1).second) { dir = 1; playsoundMove(); }
		}
		else { dir = 1; playsoundMove(); }
		}
		break;

	case 2: 
		if (dir != 1 && dir != 2) {
		if (size > 1) {
			if (snakemas.at(0).second != snakemas.at(1).second) { dir = 2; playsoundMove(); }
		}
		else { dir = 2; playsoundMove(); }
		}
		break;

	case 3: 
		if (dir != 0 && dir != 3) {
			if (size > 1) {
				if (snakemas.at(0).first != snakemas.at(1).first) { dir = 3; playsoundMove(); }
			}
			else { dir = 3; playsoundMove(); }
		}
		break;
	} // switch
	return;
}

// увеличить размер ЗМЕЙКИ на 1
void Snake::updatesize() { 
	size++;
	pair <float, float> buffer;
	buffer.first = -5;
	buffer.second = -5;
	snakemas.push_back(buffer);
	return;
}

// получить размер ЗМЕЙКИ
int Snake::getsize() {
	return size;
}

// узнать совпали ли координаты с координатами всех частей ЗМЕЙКИ
bool Snake::bingo_with_head(float x, float y)
{
	for (auto now : snakemas) {
		if (x == now.first && y == now.second)
			return true;
	}
	return false;
}

bool Snake::bingo_without_head(float x, float y)
{
	for (int i = 1; i < snakemas.size(); i++) {
		if (x == snakemas.at(i).first && y == snakemas.at(i).second)
			return true;
	}
	return false;
}
