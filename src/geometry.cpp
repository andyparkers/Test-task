#include "geometry.h"
#include "utils.h"

namespace geometry {

Plane3D::Plane3D() noexcept : COEFF_EPSILON_(1e-6)
{

}

Plane3D::Plane3D(const std::string& path_to_base_points, size_t start_pos)
    : COEFF_EPSILON_(1e-6)
{
    auto data = ParseBasePoints(path_to_base_points, start_pos);
    if (data && data.value().size() == POINTS_SIZE_) {
        CalculateCoeffs(data.value()[0],
                        data.value()[1],
                        data.value()[2]);
    }
    else {
        throw std::invalid_argument("Wrong points array size for plane.");
    }
}


Plane3D::Plane3D(const Point3D& first_point, const Point3D& second_point, const Point3D& third_point)
    : COEFF_EPSILON_(1e-6)
{
    CalculateCoeffs(first_point, second_point, third_point);
}

std::optional<std::vector<Point3D>> Plane3D::ParseBasePoints(const std::string& path, size_t start_pos) const {
    std::ifstream planes_dots(path);
    
    if (!planes_dots.is_open()) {
        std::cerr << "Error opening planes file: " << path << std::endl;
        return std::nullopt;
    }

    std::string line;
    std::vector<Point3D> data(POINTS_SIZE_);
    size_t pos = 0;

    while (std::getline(planes_dots, line)) {
        if (pos >= start_pos && pos < start_pos + POINTS_SIZE_) {
            data[pos - start_pos] = utils::ParseLine(line);
        }
        ++pos;
    }

    planes_dots.close();

    return data;
}

void Plane3D::CalculateCoeffs(const Point3D& first_point,
                        const Point3D& second_point,
                        const Point3D& third_point) {
    double v1x = second_point.x - first_point.x;
    double v1y = second_point.y - first_point.y;
    double v1z = second_point.z - first_point.z;
    
    double v2x = third_point.x - first_point.x;
    double v2y = third_point.y - first_point.y;
    double v2z = third_point.z - first_point.z;
    
    a_coeff_ = v1y * v2z - v1z * v2y;
    b_coeff_ = v1z * v2x - v1x * v2z;
    c_coeff_ = v1x * v2y - v1y * v2x;
    
    if (IsCollinear()) {
        throw std::invalid_argument("Points are collinear, a plane can't be formed.");
    }

    d_coeff_ = -(a_coeff_ * first_point.x
                + b_coeff_ * first_point.y
                + c_coeff_ * first_point.z);
}

std::vector<double> Plane3D::GetPlaneCoeffs() const noexcept {
    return {a_coeff_, b_coeff_, c_coeff_, d_coeff_};
}

[[nodiscard]] bool Plane3D::IsCollinear() const noexcept {
    return std::abs(a_coeff_) < COEFF_EPSILON_
        && std::abs(b_coeff_) < COEFF_EPSILON_
        && std::abs(c_coeff_) < COEFF_EPSILON_;
}

std::ostream& operator<<(std::ostream& out, const Plane3D& plane) {
    out << "{" << plane.a_coeff_ << "x + " << plane.b_coeff_
        << "y + " << plane.c_coeff_ << "z + " << plane.d_coeff_
        << "}";
    return out;
}

}  // end of namespace geometry