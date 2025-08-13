#include "points_processor.h"

namespace processor {

PointsFileProcessor::PointsFileProcessor(const std::string& points_file_path,
                            const std::string& planes_file_path)
    : points_file_path_(points_file_path),
      plane1_(planes_file_path, 0),
      plane2_(planes_file_path, 3)
{
    
}

void PointsFileProcessor::ProcessData() {
    OpenFiles();
    ProcessPoints();
}

PointsFileProcessor::~PointsFileProcessor() {
    try {
        input_stream_.close();
        good_stream_.close();
        wrong_stream_.close();
    } catch (const std::exception& e) {
        std::cerr << "Can't close file/s" << e.what() << std::endl;
    }
}

geometry::Plane3D PointsFileProcessor::CreatePlaneFromDots(const std::vector<geometry::Point3D>& dots) const {
    return geometry::Plane3D(dots[0], dots[1], dots[2]);
}

[[nodiscard]] bool PointsFileProcessor::IsPointInForbiddenZone(const geometry::Point3D& point) const {
    return plane1_.CalculateRelativePosition(point) > plane1_.GetEpsilonValue()
        && plane2_.CalculateRelativePosition(point) > plane2_.GetEpsilonValue();
}

void PointsFileProcessor::OpenFiles() {
    input_stream_.open(points_file_path_);
    if (!input_stream_) {
        throw std::runtime_error("Failed to open input file: " + points_file_path_);
    }

    const std::string base_name = points_file_path_.substr(0, points_file_path_.find_last_of('.'));
    good_stream_.open(base_name + "_good.txt");
    wrong_stream_.open(base_name + "_wrong.txt");

    if (!good_stream_ || !wrong_stream_) {
        throw std::runtime_error("Failed to create output files");
    }
}

void PointsFileProcessor::ProcessPoints() {
    std::string line;

    while (std::getline(input_stream_, line)) {
        try {
            const auto point = utils::ParseLine(line);

            if (IsPointInForbiddenZone(point)) {
                wrong_stream_ << line << '\n';
            } else {
                good_stream_ << line << '\n';
            }
        } catch (const std::exception& e) {
            std::cerr << "Warning: invalid point occured - " << e.what() << std::endl;
        }
    }
}

} // end of namespace processor