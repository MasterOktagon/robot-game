#pragma once
#include "debug.hpp"
#include "snippets.hpp"

#include <string>
#include <vector>

namespace mapdev {
    struct Tile {
            bool passable;
    };

    struct Pos {
            uint8 x = 0;
            uint8 y = 0;
    };

    class Map;

    class Entity {
        public:
            Pos  pos;
            Map* own_map;

            Entity(Map& map);
            ~Entity();

            void teleport(Pos t_pos);
    };

    class Map {
            vector<Tile> map_grid;
            
            friend class Entity;

            uint8 width  = 16;
            uint8 height = 16;
        public:
            struct Clock {
                uint16 turn_number = 0;
            };

            Clock clock{0};

            Map();
            Tile operator[](usize index) const;

            uint16 size() const;

            string printMap() const;
            usize  pos2Index(Pos t_pos) const;

#ifdef CATCH2
            inline usize entityAmount() const;
#endif

        protected:
            vector<Entity*> entities;
    };

} // namespace mapdev
