#ifndef WATER_EFFECT_H
#define WATER_EFFECT_H

#include "Component.h"

class WaterEffect : public Component
{
public:
	WaterEffect(Component* parent);
	void Update();
};

#endif // !WATER_EFFECT_H
