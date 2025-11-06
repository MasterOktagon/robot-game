#include "debug.hpp"
#include "map.hpp"

int main() {
    mapdev::Map    m;
    mapdev::Entity test(m);

    DEBUG(0, "minia");
    DEBUG(0, "\n"_s + m.printMap());

    test.teleport(mapdev::Pos {6, 12});
    DEBUG(0, "\n"_s + m.printMap());

    return 0;
}
