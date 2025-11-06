#include "map.hpp"

#include "debug.hpp"
#include "snippets.hpp"

#include <algorithm>
#include <string>
#include <vector>

namespace mapdev {

    Map::Map() {
        for (usize i = 0; i < (width * height); i++) { map_grid.push_back(Tile {true}); }
    }

    Tile Map::operator[](usize index) const {
        return map_grid.at(index);
    }

    uint16 Map::size() const {
        return map_grid.size();
    }

    string Map::printMap() const {
        string out;
        for (uint32 i = 0; i < map_grid.size(); i++) {
            if (map_grid.at(i).passable) {
                out += ',';
            } else {
                out += 'X';
            }
            // line break
            if (i % width == width - 1) {
                if (i == width - 1) {
                    out += "       Turn: #"_s + to_string(clock.turn_number);
                }
                out += '\n';
            }
        }
        for (Entity* e : entities) { out[pos2Index(e->pos)] = '?'; }
        return out;
    }

    usize Map::pos2Index(Pos t_pos) const {
        return (width + 1) * t_pos.y + t_pos.x;
    }

    TEST_CASE ("Check map size", "[Map]") {
        Map m;
    REQUIRE(m.size() == 16*16);
    }

    #ifdef CATCH2
        inline usize Map::entityAmount() const {
            return entities.size();
        }
    #endif
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Entity::Entity(Map& map) {
        own_map = &map;
        map.entities.push_back(this); 
    }

    Entity::~Entity() {
        own_map->entities.erase(find(own_map->entities.begin(), own_map->entities.end(), this));
    }

    void Entity::teleport(Pos t_pos) {
        pos = t_pos;

    }

    TEST_CASE("Auto cleanup after erasing entity", "[Entity]") {
        Map m;
        REQUIRE(m.entityAmount() == 0);
        {
            Entity e(m);
            REQUIRE(m.entityAmount() == 1);
        }
        REQUIRE(m.entityAmount() == 0);
    }

    

} // namespace mapdev
