#pragma once

#include <sstream>

#include "geometry.h"

namespace utils {

[[nodiscard]] geometry::Point3D ParseLine(const std::string& line);

} // end of namespace utils