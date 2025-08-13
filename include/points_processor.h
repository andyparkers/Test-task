#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "geometry.h"
#include "utils.h"

namespace processor {

class PointsFileProcessor {
public:
    PointsFileProcessor() = delete;

    explicit PointsFileProcessor(const std::string& points_file_path,
                                const std::string& planes_file_path);

    void ProcessData();

    ~PointsFileProcessor();

private:
    geometry::Plane3D CreatePlaneFromDots(const std::vector<geometry::Point3D>& dots) const;

    [[nodiscard]] bool IsPointInForbiddenZone(const geometry::Point3D& point) const;

    void OpenFiles();

    void ProcessPoints();

    const std::string points_file_path_;
    const std::string planes_file_path_;
    geometry::Plane3D plane1_;
    geometry::Plane3D plane2_;

    std::ifstream input_stream_;
    std::ofstream good_stream_;
    std::ofstream wrong_stream_;
};

} // end of namespace processor