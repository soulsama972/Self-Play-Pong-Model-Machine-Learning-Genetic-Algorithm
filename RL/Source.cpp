#include <Window.hpp>
#include<Texture2D.hpp>
#include"pong.hpp"
#include<iostream>
#include <chrono>
#include <algorithm>
#pragma comment(lib,"Engine.lib")

using namespace std::chrono_literals;



#pragma warning (push)
#pragma warning (disable : 28251)


#define CONSOLE_SIZE (100 * 100)
#define WIDTH 80
#define HEIGHT 80
#define BOARDSIZE (WIDTH * HEIGHT)
#define NUM_OF_BALL_COLOR 2
#define NUM_OF_ACTION 3
#define QTABLE_SIZE ((BOARDSIZE * WIDTH) * NUM_OF_BALL_COLOR)
using u32 = unsigned int;

float MinMax(float x, float min, float max)
{
	return (x - min) / (max - min) * 2 - 1;
}

void PutText(char* screen,u32 index, const char* format, ...)
{
	std::va_list va;
	va_start(va,format);
	std::vsprintf(screen+index, format,va);
	va_end(va);
}

int argMax(double* arr, int len)
{
	int index = 0;
	for (int i = 0; i < len; i++)
	{
		if (arr[index] < arr[i])
			index = i;
	}
	return index;
}

HANDLE InitConsole()
{
	AllocConsole();
	SMALL_RECT rect = { 0,0,100,100 };
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 2000, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);

	if (!SetConsoleWindowInfo(hConsole, 1, &rect))
		assert("error 2");
	return hConsole;
}

struct MyQTable
{
	double action[3];
};


void saveToFile(const std::vector<MyQTable>qtable,std::string fileName,unsigned int len)
{

	std::fstream out(fileName, std::ios::out);
	if (out.is_open())
	{
		for (size_t i = 0; i < len; i++)
		{
			out << qtable[i].action[0]  << " " << qtable[i].action[1] << " " << qtable[i].action[2] << std::endl;
		}
		out.close();
	}
}

void loadFromFile(std::vector<MyQTable>&qtable,std::string fileName, unsigned int len)
{
	std::ifstream in(fileName, std::ios::in);
	MyQTable qt;
	if (in.is_open())
	{
		for (size_t i = 0; i < len; i++)
		{
			in >> qt.action[0] >> qt.action[1] >> qt.action[2];
			qtable.push_back(qt);
		}
		in.close();
	}
}

inline __int64 getQTableIndex(const State state)
{
	return static_cast<__int64>(state.ballState * static_cast<__int64>(pow(WIDTH, 3)) + state.pX * BOARDSIZE + state.bY * WIDTH + state.bX);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	std::vector<MyQTable>qTable;
	qTable.reserve(QTABLE_SIZE);
	Window  window;
	const fVec2 screen = fVec2(800, 800);
	window.Init(L"window", screen);
	//Init(&window);
	Texture2D::Bind(&window);
	Camera::Bind(&window);
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(-5.0, 0.0);
	std::uniform_real_distribution<double> random(0.0, 1.0);
	bool render;
	pong * p = new pong(screen);
	DWORD l;
	char *cScreen = new char[CONSOLE_SIZE];
	memset(cScreen, 0, CONSOLE_SIZE);
	HANDLE  hConsole = InitConsole();
	int bestScore = 0;
	std::string qtFile = "";
	
	if (qtFile.empty())
	{
		MyQTable qt;
		for (size_t i = 0; i < QTABLE_SIZE; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				double number = distribution(generator);
				
				qt.action[j] = number;
			}
			qTable.push_back(qt);
		}
	}
	else
	{
		loadFromFile(qTable, qtFile, QTABLE_SIZE);
	}
	for(int j = 0;j<1000;j++)
	{
		for (int i = 0; i < p->HW_ITER; i++)
		{
			if (i == p->HW_ITER - 1)
				render = true;
			else
				render = false;
			
			render = 1;
			int episode_reward = 0;
			PutText(cScreen, 0, "best score %d", bestScore);
			WriteConsoleOutputCharacterA(hConsole, cScreen, BOARDSIZE, { 0,0 }, &l);
			
			while (true)
			{
				if (render)
				{
					window.LoopEvent();
					if (window.IsWindowDestory())
						break;
					window.ClearTargetView(fVec4(0.1f, 0.1f, 0.1f, 1.0f));
				}
				State state = p->getState();
				__int64 QIndex = getQTableIndex(state);
				int action = (random(generator) > p->epsilon) ? argMax(qTable[QIndex].action, NUM_OF_ACTION) : rand() % NUM_OF_ACTION;

				p->update(action);
				State newState = p->getState();

				__int64 newQIndex = getQTableIndex(newState);
				double max_q = *std::max_element(qTable[newQIndex].action,qTable[newQIndex].action + NUM_OF_ACTION);
				double current_q = qTable[QIndex].action[action];

				if (newState.reward == p->HIT_REWARD || newState.reward == p->DIE_PENALTY)
					qTable[QIndex].action[action] = newState.reward;
				else
				{
					double newQ = (1 - p->lr) * current_q + p->lr * (newState.reward + p->discount * max_q);
					qTable[QIndex].action[action] = newQ;
				}
				episode_reward += newState.reward;
				
				if (newState.done)
					break;
				
				if (render)
				{
					p->draw();
					window.Render(true);
				}
			}
			if (bestScore < p->score)
				bestScore = p->score;
			p->epsilon *= p->iter_decay;
			p->rest();
		}
	}
	
	saveToFile(qTable, "test.q3" , QTABLE_SIZE);
	CloseHandle(hConsole);
	delete[] cScreen;
	return 0;
}

#pragma warning(pop)
