#include "utils.h"

namespace utils {

[[nodiscard]] geometry::Point3D ParseLine(const std::string& line) {
    std::istringstream iss(line);
    geometry::Point3D point;
    
    if (!(iss >> point.x >> point.y >> point.z)) {
        throw std::invalid_argument("Invalid point format: " + line);
    }

    std::string extra;
    if (iss >> extra) {
        throw std::invalid_argument("Extra data in point line: " + line);
    }

    return point;
}

} // end of namespace utils