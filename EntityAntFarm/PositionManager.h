#pragma once
#include <vector>
#include <list>
#include <cstdint>
#include <utility>
#include <unordered_map>
#include "Entity.h"
#include "Component.h"
#include "ComponentManager.h"

typedef Component<std::array<int32_t, 3>> Position;

class PositionManager : public ComponentManager<Position, std::vector> {
private:
	std::unordered_map<uint64_t, std::list<Entity>> _bucket_map;

	uint64_t _xy_to_key(int32_t x, int32_t y) const;
	uint64_t _position_to_key(Position pos) const;
	void _add_to_bucket(Position pos);
public:
	int32_t bucketWidth;
	PositionManager(int32_t width) {
		bucketWidth = width;
	}

	std::list<Entity>& list_at(Position position);
	std::list<Entity>& list_at(int32_t x, int32_t y);

	const std::list<Entity>& clist_at(Position position) const;
	const std::list<Entity>& clist_at(int32_t x, int32_t y) const ;
	bool has_bucket(int32_t x, int32_t y) const;
	bool has_bucket(Position pos) const;

	bool add_position_component(Position component);

	bool remove_position_component(const Entity e);
	
	void update_all_buckets();
	void update_bucket(Position pos);
	void update_position(Entity e, int32_t vx, int32_t vy);
};