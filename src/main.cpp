#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

#include "utils.h"
#include "points_processor.h"

int main(int argc, char* argv[]) {

    if (argc != 3) {
        throw std::invalid_argument("""Wrong argument quantity, please specify """ \
            """input path for points and planes to .txt files.""");
    }

    std::string input_file_points = argv[1];
    std::string input_file_planes = argv[2];

    processor::PointsFileProcessor processor(input_file_points, input_file_planes);

    processor.ProcessData();

    return 0;
}