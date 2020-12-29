#pragma once
#include "Entity.h"
#include <array>

template <typename T>
struct Component {
	Entity entity;
	T data;
};

template <typename T>
bool operator<(Component<T>& lhs, Component<T>& rhs) {
	return lhs.entity < rhs.entity;
}

template <typename T>
bool operator==(Component<T>& lhs, Component<T>& rhs) {
	return lhs.entity == rhs.entity;
}