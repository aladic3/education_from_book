//
// Created by Dmytrenko Kyrylo on 11.10.2025.
//
#include <iostream>

class Bad_area {
};

void error(std::string msg) {
    throw std::runtime_error(msg);
}

int area(int length, int width) {

    if ( !(length > 0 && width > 0))
        error("Length or width is negative\n");

    int result = length * width;
    if (result <= 0) {
        std::string msg = "Result under zero! Result is " + std::to_string(result);
        error(msg);
    }




    return result;
}

double hexagon_area(int a) {
    double result = ( (3 * std::sqrt(3))  / 2) * (a * a);

    if (result < 0)
        throw Bad_area{};

    return result;


}

int framed_area(int x, int y) {
    constexpr int frame_width = 2;

    return area(x-frame_width, y-frame_width);
}

void test (int x, int y, int z) {
    int area1 = area(x, y);
    int area2 = framed_area(12, z);
    int area3 = framed_area(y,z);
    int area4 = area(500000,50000);
    double ratio = double(area1)/area3;

    std::cout << "area1 " << area1 << " area2 " << area2 << " area3 " << area3  << " ratio " << ratio;
}

double estimate_reach_time(int speed, int distance) {
    if (!(speed > 0 && distance > 0)) {
        error("Estimate driving time is fall. Distance or speed is under 0!");
    }

    return static_cast<double>(distance) / speed;
}

void estimate_driving_flying_time_all_cities()
// estimate driving and flying time (in hours)
// between cities
{
    // speed in kilometers
    constexpr int avg_driving_speed = 110;
    constexpr int avg_flying_speed = 805;


    constexpr int distance_London_Nice_drive = 1390;
    constexpr int distance_London_Nice_fly = 1028;

    constexpr int distance_Denver_New_York_drive = 2861;
    constexpr int distance_Denver_New_York_fly = 2619;

    std::cout << "Estimate flying and driving between London and Nice...\n"
            << estimate_reach_time(avg_flying_speed, distance_London_Nice_fly) << "h, "
            << estimate_reach_time(avg_driving_speed, distance_London_Nice_drive) << "h\n";

    std::cout << "Estimate flying and driving between New York City and Denver...\n"
            << estimate_reach_time(avg_flying_speed, distance_Denver_New_York_fly) << "h, "
            << estimate_reach_time(avg_driving_speed, distance_Denver_New_York_drive) << "h\n";

}



