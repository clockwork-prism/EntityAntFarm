#include "Managers.h"

void History::update_history(int32_t x, int32_t y)
{
	for (size_t i{ this->data.size() - 2 }; i > 1; i--)
		this->data.at(i) = this->data.at(i - 2);
	this->data.at(0) = x;
	this->data.at(1) = y;
}

void History::reverse()
{
	for (size_t i{}; i < this->data.size() / 2; i++) {
		size_t j{ this->data.size() - 3 - i + 2 * (i % 2) };
		if (i != j) {
			int32_t temp = this->data.at(i);
			this->data.at(i) = this->data.at(j);
			this->data.at(j) = temp;
		}
	};
}

int32_t History::data_at(size_t i) const
{
	return this->data.at(i);
}

size_t History::size() const
{
	return this->data.size();
}

int32_t History::back() const
{
	return this->data.back();
}

void History::set_back(int32_t val)
{
	this->data.back() = val;
}
