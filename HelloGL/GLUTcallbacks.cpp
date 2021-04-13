#include "GLUTcallbacks.h"
#include "HelloGL.h"

namespace GLUTcallbacks
{
	namespace
	{
		//initialise to a null ptr
		HelloGL* helloGL = nullptr;

	}

	void Init(HelloGL* gl)
	{

		helloGL = gl;

	}

	void Display()
	{

		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		helloGL->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(preferredRefresh - updateTime, GLUTcallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		helloGL->Keyboard(key, x, y);
	}

	void MenuChoices(int selection)
	{
		helloGL->MenuChoices(selection);
	}

}