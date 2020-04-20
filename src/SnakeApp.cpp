#include "Snake.hpp"
#define SQUARE_SIZE 15

class SnakeApp : public App {
public:
	params::InterfaceGlRef text; // информационное табло
	bool gameover = false, flag, match; bool music = false, start_game;
	Apple apple;
	Snake snake;
	Square square1[SQUARE_SIZE]; // препятствие 
	Square square2[SQUARE_SIZE]; // препятствие
	bool mIsPaused; // игровая пауза
	int level = 0; // игровой уровень
	int scale = 0; // размер клетки (одна из сторон)
	int total_score = 0; // количество набранных очков
	int N = 4; // размер поля по горизонтали
	int M = 4; // по вертикали
	int x_apple, y_apple; // вспомогательные
	int x_snake, y_snake; // переменные
	VoiceRef SnakeDie; // звук при поражении
	VoiceRef BackGroundMusic; // фоновая музыка
	void setup() override;
	void keyDown(KeyEvent event) override;
	void update() override;
	void draw() override;
	void new_apple_coords(void);
	void updateinfo(void);
};

void SnakeApp::setup()
{
	mIsPaused = true;
	double height = getWindowSize().y, width = getWindowSize().x;
	if (width / height == 16.0 / 9) {
		N *= 16;
		M *= 9;
	}
	else if (width / height == 4.0 / 3) {
		N *= 4 * 4;
		M *= 3 * 4;
	}
	else {
		N *= 10;
		M *= 10;
	}
	scale = getWindowSize().x / N;
	int x = N / 4, y = M / 5, count = 1; // значения для препятствия
	for (auto& now : square1) {
		now.setRGB(0.5, 0.5, 0.5);
		now.setscale(scale);
		if (count % 10 != 0) {
			now.setx(x);
			now.sety(y++);
			count++;
		}
		else {
			now.setx(x++);
			now.sety(y);
		}
	}
	x = N / 1.3, y = M / 3, count = 1; // значения для препятствия
	for (auto& now : square2) {
		now.setRGB(0.5, 0.5, 0.5);
		now.setscale(scale);
		if (count % 10 != 0) {
			now.setx(x++);
			now.sety(y);
			count++;
		}
		else {
			now.setx(x);
			now.sety(y++);
		}
	}
	apple.setscale(scale);
	snake.setscale(scale);
	snake.setx(N * 0.5f);
	snake.sety(M * 0.5f);
	apple.setRGB(1.f, 0.1f, 0.f);
	new_apple_coords();
	snake.setSound("EatAppleSound.wav", "MovementSound.wav");
#ifdef WITH_ASSETS
	audio::SourceFileRef sound = audio::load(loadAsset("DeadSound.wav"));
	SnakeDie = audio::Voice::create(sound);
	SnakeDie->setVolume(0.3f);
	sound = audio::load(app::loadAsset("MainTheme.wav"));
	BackGroundMusic = audio::Voice::create(sound);
	BackGroundMusic->setVolume(0.008f);
#else
	audio::SourceFileRef sound = audio::load(app::loadResource(DEAD_SOUND));
	SnakeDie = audio::Voice::create(sound);
	SnakeDie->setVolume(0.3f);
	sound = audio::load(app::loadResource(MAINTHEME_SOUND));
	BackGroundMusic = audio::Voice::create(sound);
	BackGroundMusic->setVolume(0.008f);
#endif // WITH_ASSETS
	text = params::InterfaceGl::create("Snake game v0.6", ivec2(0, 0));
	updateinfo();
	text->maximize();
}

void SnakeApp::keyDown(KeyEvent event) {
	switch (event.getCode()) {
		case KeyEvent::KEY_ESCAPE:
			quit();
			break;
		case KeyEvent::KEY_UP:
			if (!mIsPaused)
				snake.setdir(3);
			break;
		case KeyEvent::KEY_LEFT:
			if (!mIsPaused)
				snake.setdir(1);
			break;
		case KeyEvent::KEY_RIGHT:
			if (!mIsPaused)
				snake.setdir(2);
			break;
		case KeyEvent::KEY_DOWN:
			if (!mIsPaused)
				snake.setdir(0);
			break;
		case KeyEvent::KEY_SPACE:
			mIsPaused = !mIsPaused;
			BackGroundMusic->stop();
			start_game = true;
			break;
		case KeyEvent::KEY_1:
			if (!mIsPaused)
				setFrameRate(10.0f);
			break;
		case KeyEvent::KEY_2:
			if (!mIsPaused)
				setFrameRate(13.0f);
			break;
		case KeyEvent::KEY_3:
			if (!mIsPaused)
				setFrameRate(15.0f);
			break;
		case KeyEvent::KEY_f:
			setFullScreen(!isFullScreen());
			if (!isFullScreen()) {
				setWindowSize(1280, 720);
			}
			scale = getWindowSize().x / N;
			apple.setscale(scale);
			snake.setscale(scale);
			for (auto& now : square1)
				now.setscale(scale);
			for (auto& now : square2)
				now.setscale(scale);
			break;
		case KeyEvent::KEY_m:
			if (text->isMaximized())
				text->minimize();
			else text->maximize();
			break;
		case KeyEvent::KEY_r:
			if (gameover) {
				SnakeDie->stop();
				snake.setx(N * 0.5f);
				snake.sety(M * 0.5f);
				snake.restart();
				new_apple_coords();
				total_score = 0;
				text->clear();
				updateinfo();
				gameover = false;
				mIsPaused = false;
				music = false;
			}
			break;
	}
}

void SnakeApp::update()
{
	if (gameover) {
		BackGroundMusic->stop();
		if (!music) {
			SnakeDie->start();
			music = true;
			text->clear();
		}
		text->addText("Your total score is " + std::to_string(total_score));
		text->addText("Press R to restart");
		text->addText("Press ESC to exit");
		text->maximize();
	}
	else if (!mIsPaused) {
		snake.moveto(snake.new_x(), snake.new_y());
		
		if (!(BackGroundMusic->isPlaying())) BackGroundMusic->start();
		if (snake.getx() >= N) snake.moveto(0, snake.gety());
		if (snake.getx() < 0) snake.moveto(N - 1, snake.gety());
		if (snake.gety() >= M) snake.moveto(snake.getx(), 0);
		if (snake.gety() < 0) snake.moveto(snake.getx(), M - 1);
		flag = true; match = false;
		if (apple.getx() == snake.getx() && apple.gety() == snake.gety()) {
			new_apple_coords();
			snake.updatesize();
			total_score++;
			text->clear();
			updateinfo();
			apple.moveto(x_apple, y_apple);
			snake.playsoundEat();
		}

		if (snake.bingo_without_head(snake.getx(), snake.gety())) {
			gameover = true;
			mIsPaused = !mIsPaused;
		}
		for (auto now : square1) 
			if (snake.bingo_with_head(now.getx(), now.gety())) {
				gameover = true;
				mIsPaused = !mIsPaused;
			}
		for (auto now : square2)
			if (snake.bingo_with_head(now.getx(), now.gety())) {
				gameover = true;
				mIsPaused = !mIsPaused;
			}
	}
	return;
}

void SnakeApp::draw()
{
	clear(Color(0.3f, 0.4f, 0.f));
	for (auto now : square1)
		now.draw();
	for (auto now : square2)
		now.draw();
	if (start_game) {
		snake.draw();
		apple.draw();
	}
	text->draw();
}

void SnakeApp::new_apple_coords(void)
{
	flag = true; match = false;
	while (flag) {
		x_apple = apple.new_x(N);
		y_apple = apple.new_y(M);
		match = snake.bingo_with_head(x_apple, y_apple);
		if (!match) {
			for (int i = 0; i < SQUARE_SIZE; i++) {
				if (x_apple == square1[i].getx() && y_snake == square1[i].gety())
					match = true;
				if (x_apple == square2[i].getx() && y_snake == square2[i].gety()) {
					match = true;
				}
			}
			if (!match) flag = false;
		}
	}
	apple.moveto(x_apple, y_apple);
}

void SnakeApp::updateinfo(void)
{
	text->addText("1, 2, 3 - Change ->");
	text->addText(" -> game speed");
	text->addText("Space - Start/Pause");
	text->addText("M - Hide this panel");
	text->addText("F - Set fullscreen");
	text->addText("Esc - Exit");
	text->addText("Snake size is " + std::to_string(snake.getsize()));
	text->addText("Total score is " + std::to_string(total_score));
}

CINDER_APP(SnakeApp, RendererGl, [&](App::Settings* settings) 
{
	settings->setFrameRate(10.0f);
	settings->setBorderless(false);
	settings->setResizable(false);
	settings->setTitle("Snake");
	//settings->setWindowSize(1280, 720);
	settings->setFullScreen(true);
})
