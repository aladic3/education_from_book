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

    if (length < 0 && width < 0)
        error("Length or width is negative\n");

    int result = length * width;
    if (result <= 0)
        throw Bad_area{};



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
    double ratio = double(area1)/area3;

    std::cout << "area1 " << area1 << " area2 " << area2 << " area3 " << area3  << " ratio " << ratio;
}

