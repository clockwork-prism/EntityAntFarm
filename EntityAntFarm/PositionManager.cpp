#include "PositionManager.h"

const uint64_t MASK32{ (1LL << 31) - 1 };

uint64_t PositionManager::_xy_to_key(int32_t x, int32_t y) const
{
	int32_t xb, yb;
	if (x < 0)
		xb = (x / bucketWidth) - 1;
	else
		xb = (x / bucketWidth);
	if (y < 0)
		yb = (y / bucketWidth) - 1;
	else
		yb = (y / bucketWidth);
	uint64_t key{ static_cast<int64_t>(xb) & MASK32 };
	key = key << 32;
	key += static_cast<uint64_t>(static_cast<int64_t>(yb) & MASK32);
	return key;
}

uint64_t PositionManager::_position_to_key(Position pos) const
{
	return _xy_to_key(pos.data.at(0), pos.data.at(1));
}

void PositionManager::_add_to_bucket(Position pos)
{
	uint64_t key{ this->_position_to_key(pos) };
	if (this->_bucket_map.count(key)) {
		auto bucIt = std::find(this->_bucket_map.at(key).begin(), this->_bucket_map.at(key).end(), pos.entity);
		if (bucIt == this->_bucket_map.at(key).end())
			this->_bucket_map.at(key).push_back(pos.entity);
	}
	else
		this->_bucket_map.insert({ key, {pos.entity} });
}

std::list<Entity>& PositionManager::list_at(Position position)
{
	uint64_t key = _xy_to_key(position.data.at(0), position.data.at(1));
	return _bucket_map.at(key);
}

std::list<Entity>& PositionManager::list_at(int32_t x, int32_t y)
{
	uint64_t key = _xy_to_key(x, y);
	return _bucket_map.at(key);
}

const std::list<Entity>& PositionManager::clist_at(Position position) const
{
	uint64_t key = _xy_to_key(position.data.at(0), position.data.at(1));
	return _bucket_map.at(key);
}

const std::list<Entity>& PositionManager::clist_at(int32_t x, int32_t y) const
{
	uint64_t key = _xy_to_key(x, y);
	return _bucket_map.at(key);
}

bool PositionManager::has_bucket(int32_t x, int32_t y) const
{
	uint64_t key = _xy_to_key(x, y);
	return this->_bucket_map.count(key) > 0;
}

bool PositionManager::has_bucket(Position pos) const
{
	return this->has_bucket(pos.data.at(0), pos.data.at(1));
}

bool PositionManager::add_position_component(Position component)
{
	if (this->_map.count(component.entity.index())) {
		auto it = this->_get_component_iterator(component.entity);
		if (_position_to_key(component) != _position_to_key(*it)) {
			auto oldBucIt = std::find(list_at(*it).begin(), list_at(*it).end(), it->entity);
			list_at(*it).erase(oldBucIt);
			this->_add_to_bucket(component);
		}
		*it = component;
		return true;
	}
	else {
		size_t idx{ this->_components.size() };
		this->_components.push_back(component);
		this->_map[component.entity.index()] = idx;
		this->_add_to_bucket(component);
		return false;
	}
}

bool PositionManager::remove_position_component(const Entity e)
{
	if (!this->_map.count(e.index()))
		return false;
	size_t idx = this->_map[e.index()];
	size_t lastIdx = this->_components.size() - 1;
	auto it = this->_get_component_iterator(e);
	auto bucIt = std::find(this->list_at(*it).begin(), this->list_at(*it).end(), it->entity);
	this->list_at(*it).erase(bucIt);
	auto lastIt = this->_components.end();
	lastIt--;
	*it = *lastIt;
	this->_map[lastIt->entity.index()] = idx;
	this->_components.erase(lastIt);
	this->_map.erase(e.index());
	return true;
}

void PositionManager::update_all_buckets()
{
	this->_bucket_map.clear();
	for (auto pos : this->_components) {
		uint64_t key{ this->_position_to_key(pos) };
		if (this->_bucket_map.count(key))
			this->_bucket_map.at(key).push_back(pos.entity);
		else
			this->_bucket_map.insert({ key, {pos.entity} });
	}
}

void PositionManager::update_bucket(Position pos)
{
	auto pit = this->find(pos.entity);
	if (pit == this->end())
		return;

	uint64_t newKey = this->_position_to_key(pos);
	uint64_t oldKey = this->_position_to_key(*pit);
	if (newKey != oldKey) {
		auto oldBucIt = std::find(this->list_at(*pit).begin(), this->list_at(*pit).end(), pit->entity);
		this->_bucket_map.at(oldKey).erase(oldBucIt);
		this->_add_to_bucket(pos);
	}
	pit->data.at(0) = pos.data.at(0);
	pit->data.at(1) = pos.data.at(1);
}

void PositionManager::update_position(Entity e, int32_t vx, int32_t vy)
{
	
}
