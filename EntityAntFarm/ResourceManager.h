#pragma once
#include "ComponentManager.h"

class ResourceManager
{
public:
	enum AI_State {seeking};

	ComponentManager<Component<AI_State>, std::vector> _AIManager;
	ComponentManager<Component<uint8_t>, std::vector> _TrailManager;

	ResourceManager() : _AIManager{}, _TrailManager{} {}
};

