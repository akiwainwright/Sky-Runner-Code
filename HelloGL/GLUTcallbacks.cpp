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
		helloGL->Update();
		glutTimerFunc(preferredRefresh, GLUTcallbacks::Timer, preferredRefresh);
	}

}