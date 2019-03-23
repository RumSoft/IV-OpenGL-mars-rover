#pragma once
#include "Geom.h"

class Background : public Geom
{
public:
	Background()
	{
	}

	void Update() override
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5, 0.5, 0.5, 1);



		float ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float position[] = { 1.0f, 1.0f, 0.3f, 0.0f };

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		float model_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		int model_two_side = 1;                                //0=2sided, 1=1sided
		int viewpoint = 0;

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, viewpoint);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);

		glShadeModel(GL_SMOOTH);
		glEnable(GL_COLOR_MATERIAL);
	}
};
