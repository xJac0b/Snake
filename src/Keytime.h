#pragma once
#include "State.h"
class Keytime
{
public:
	Keytime(float start, float max);
	~Keytime();

	void update(const float& dt);
	const bool& get();
private:
	float value;
	float max;
};

