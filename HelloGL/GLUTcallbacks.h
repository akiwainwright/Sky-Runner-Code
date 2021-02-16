#pragma once
class HelloGL;

namespace GLUTcallbacks
{
	void Init(HelloGL* gl);

	void Display();

	void Timer(int preferredRefresh);
}
