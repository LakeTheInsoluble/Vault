#include "relativecoordinate.hh"

bool RelativeCoordinate::operator==(const RelativeCoordinate &other) const
{
    return this->absolute() == other.absolute();
}
