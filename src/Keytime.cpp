#include "pch.h"
#include "Keytime.h"

Keytime::Keytime(float start, float max) : value(start), max(max)
{
}

Keytime::~Keytime()
{
}

void Keytime::update(const float& dt)
{
	if (this->value < this->max)
		this->value += 100.f * dt;
}

const bool& Keytime::get()
{
	if (this->value >= this->max)
	{
		this->value = 0.f;
		return true;
	}

	return false;
}
