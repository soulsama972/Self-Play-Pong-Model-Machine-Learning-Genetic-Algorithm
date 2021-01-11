#pragma once
#include<Texture2D.hpp>
#include<random>
#include<ctime>
#include <fstream>
#include<iostream>

class Ball
{
public:
	Ball() { size = fVec2(20, 20); ballState = 0; }
	void setPos() 
	{
		this->pos.x = (rand() % 80)  * 10.0f;
		this->pos.y = 790;
		this->ballState = rand() % 2;
	}
	void update()
	{
		pos.y -= 10;
	}
	void draw(Texture2D * tex,const Camera &camera)
	{
		tex->AddInstance(pos, size, camera);
	}
	fVec2 pos;
	fVec2 size;
	__int64 ballState;
};

class Paddle
{
public:
	
	Paddle()
	{ 
		size = fVec2(100, 10);
	}
	void setPos()
	{
		this->pos.x = (rand() % 80) * 10.0f;
		this->pos.y = 20;
	}
	void update(int action)
	{
		if (action == 1 && this->pos.x > 0)
			this->pos.x -= 10;
		else if (action == 2 && this->pos.x + this->size.x < 800)
			this->pos.x += 10;
	}
	void draw(Texture2D* tex, const Camera& camera)
	{
		tex->AddInstance(pos, size, camera);
	}
	fVec2 pos;
	fVec2 size;
};

struct State
{
	int pX;
	int bX, bY;
	int reward;
	__int64 ballState;
	bool done;
};
class pong
{
public:
	pong(const fVec2 & screen)
	{
		tBall[0] = new Texture2D("ball1.png", "vs.hlsl", "ps.hlsl", 100);
		tBall[1] = new Texture2D("ball2.png", "vs.hlsl", "ps.hlsl", 100);
		tPaddle = new Texture2D("player.png", "vs.hlsl", "ps.hlsl", 100);
		camera.Init(screen, 0.1f, 1000.0f);
		camera.Update(fVec3(400, 400, 1));
		

		rest();
	}

	State getState()
	{
		State state;
		state.ballState = ball.ballState;
		state.pX = static_cast<int>(paddle.pos.x / 10);
		state.bX = static_cast<int>(ball.pos.x / 10);
		state.bY = static_cast<int>(ball.pos.y / 10);
		state.reward = reward;
		state.done = done;
		return state;
	}

	void rest()
	{
		ball.setPos();
		paddle.setPos();
		done = false;
		score = 0;
	}

	void update(int action)
	{
		ball.update();
		paddle.update(action);
		if (ball.pos.y == 10)
		{
			if (ball.ballState == 0)
			{
				if (ball.pos.x + ball.size.x > paddle.pos.x && ball.pos.x < paddle.pos.x + paddle.size.x)
				{
					reward = HIT_REWARD;
					score++;
				}
				else
				{
					reward = -DIE_PENALTY;
					done = true;
				}
			}
			else
			{
				if (ball.pos.x + ball.size.x > paddle.pos.x && ball.pos.x < paddle.pos.x + paddle.size.x)
				{
					reward = -DIE_PENALTY;
					done = true;
				}
				else
				{
					reward = HIT_REWARD;
					score++;
				}
			}
			ball.setPos();
		}
		else 
			reward = -MOVE_PENALTY;
	}
	void draw()
	{
		ball.draw(tBall[ball.ballState], camera);
		paddle.draw(tPaddle, camera);
		tPaddle->Draw(true);
		tBall[ball.ballState]->Draw(true);
	}
	
	Camera camera;
	Texture2D* tBall[2];
	Texture2D* tPaddle;
	Ball ball;
	Paddle paddle;
	int score;
	bool done;
	int reward;
	double epsilon = 0.9;
	double iter_decay = 0.9998;
	double lr = 0.1;
	double discount = 0.95;
	const int HW_ITER = 25000;

	const int MOVE_PENALTY = 1;
	const int DIE_PENALTY = 300;
	const int HIT_REWARD = 25;

};



