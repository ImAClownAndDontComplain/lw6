#ifndef APP_H
#define APP_H

#ifdef FREETYPE
#include "freetypeGL.h"
#endif


class App
{
protected:
	App();

	void CalcFPS();

	void RenderFPS();

	float GetRunningTime();

protected:
#ifdef FREETYPE
	FontRenderer m_fontRenderer;
#endif
private:
	float m_frameTime;
	float m_startTime;
	int m_frameCount;
        int m_fps;
};

#endif