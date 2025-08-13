#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include <optional>

namespace geometry {

struct Point3D {
    Point3D() noexcept = default;

    Point3D(double x_val, double y_val, double z_val) noexcept
        : x(x_val), y(y_val), z(z_val)
    {

    }

    double x;
    double y;
    double z; 
};

class Plane3D {
public:
    Plane3D() noexcept;

    Plane3D(const std::string& path_to_base_points, size_t start_pos);

    Plane3D(const Point3D& first_point, const Point3D& second_point, const Point3D& third_point);

    void CalculateCoeffs(const Point3D& first_point,
                        const Point3D& second_point,
                        const Point3D& third_point);

    std::vector<double> GetPlaneCoeffs() const noexcept;

    [[nodiscard]] inline double CalculateRelativePosition(const Point3D& point) const noexcept {
        return a_coeff_ * point.x + b_coeff_ * point.y + c_coeff_ * point.z + d_coeff_;
    }

    double GetEpsilonValue() const noexcept {
        return COEFF_EPSILON_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Plane3D& plane);

private:
    [[nodiscard]] bool IsCollinear() const noexcept;

    std::optional<std::vector<Point3D>> ParseBasePoints(const std::string& path, size_t start_pos) const;

    const size_t POINTS_SIZE_ = 3;
    const double COEFF_EPSILON_;
    double a_coeff_;
    double b_coeff_;
    double c_coeff_;
    double d_coeff_;
};

}  // end of namespace geometry