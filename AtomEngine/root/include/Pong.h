#pragma once

#include "GameObject.h"

enum class BallState { PLAYING, SCORE_LEFT, SCORE_RIGHT };

class Ball : public Renderable
{
public:
	Ball(Mesh* m, Shader* s) : Renderable(m, s) {}

	BallState Update(Entity& leftPaddle, Entity& rightPaddle)
	{
		transform.Move(velocityX, velocityY);
		glm::vec3 pos = transform.GetPosition();

		if (pos.y > 0.9)
		{
			velocityY = -velocityY;
			transform.SetPosition(pos.x, 0.9);
		}
		if (pos.y < -0.9)
		{
			velocityY = -velocityY;
			transform.SetPosition(pos.x, -0.9);
		}
		if (pos.x > 0.9)
		{
			return BallState::SCORE_LEFT;
		}
		if (pos.x < -0.9)
		{
			return BallState::SCORE_RIGHT;
		}

		if (CheckCollision(pos, leftPaddle.GetTransform().GetPosition()) ||
			CheckCollision(pos, rightPaddle.GetTransform().GetPosition()))
		{
			velocityX = -velocityX;
		}

		return BallState::PLAYING;
	}

	void ResetBall()
	{
		transform.SetPosition(0, 0);
		velocityX = (velocityX > 0) ? 0.002 : -0.002;
		velocityY = 0.002;
	}

	bool CheckCollision(glm::vec3 ballPos, glm::vec3 paddlePos)
	{
		float ballWidth = 0.04f;
		float ballHeight = 0.04f;

		float paddleWidth = 0.04f;
		float paddleHeight = 0.2f;

		bool xOverlap = (ballPos.x < paddlePos.x + paddleWidth / 2) &&
			(ballPos.x + ballWidth / 2 > paddlePos.x);

		bool yOverlap = (ballPos.y < paddlePos.y + paddleHeight / 2) &&
			(ballPos.y + ballHeight / 2 > paddlePos.y);

		return xOverlap && yOverlap;
	}

private:
	float velocityX = 0.002;
	float velocityY = 0.002;
};

class PongGame
{
public:
	PongGame(OpenGLWindow* window, Ball* b, Entity* lP, Entity* rP) : glWindow(window), ball(b), leftPaddle(lP), rightPaddle(rP), sideAPoints(0), sideBPoints(0)
	{
		b->ResetBall();
		lP->GetTransform().SetPosition(-0.9f, 0.0f);
		rP->GetTransform().SetPosition(0.9f, 0.0f);
	}		

	void Update() 
	{
		leftPaddle->Render();
		rightPaddle->Render();
		ball->Render();

		leftPaddle->HandleInput(*glWindow);
		rightPaddle->HandleInput(*glWindow, { GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN });

		BallState ballState = ball->Update(*leftPaddle, *rightPaddle);

		switch (ballState) {
		case BallState::SCORE_LEFT:
			sideAPoints += 1;
			printf("Left Side Scored +1! (%d)\n", sideAPoints);
			ResetRound();
			break;
		case BallState::SCORE_RIGHT:
			sideBPoints += 1;
			printf("Right Side Scored +1! (%d)\n", sideBPoints);
			ResetRound();
			break;
		case BallState::PLAYING:
			break;
		}

		if (sideAPoints == 5) {
			printf("Left player wins!\n");
			ResetGame();
		}
		else if (sideBPoints == 5) {
			printf("Right player wins!\n");
			ResetGame();
		}
	}

	void ResetGame()
	{
		sideAPoints = 0;
		sideBPoints = 0;

		ball->ResetBall();
		leftPaddle->GetTransform().SetPosition(-0.9f, 0.0f);
		rightPaddle->GetTransform().SetPosition(0.9f, 0.0f);
	}

	void ResetRound()
	{
		ball->ResetBall();
		leftPaddle->GetTransform().SetPosition(-0.9f, 0.0f);
		rightPaddle->GetTransform().SetPosition(0.9f, 0.0f);
	}

private:
	Ball* ball;
	Entity* leftPaddle;
	Entity* rightPaddle;
	OpenGLWindow* glWindow;

	int sideAPoints;
	int sideBPoints;
};