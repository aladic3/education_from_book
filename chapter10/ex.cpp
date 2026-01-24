//
// Created by Dmytrenko Kyrylo on 24.01.2026.
//
module;
#include <iostream>
#include <vector>
#include <cmath>
import try_drill;


module chapter10;


namespace ch10::ex12_13 {
    const double pi = std::acos(-1.0);;

    struct Point {
        int x;
        int y;

        bool operator==(const Point& another) const {
            return x==another.x && y==another.y;
        }
    };

    int get_sgn(double op){
        int res = 1;

        if (op<0)
            res = -1;
        else if (op == 0)
            res = 0;

        return res;
    }

    void print_super_ellipse(std::vector<Point>& super_ellipse_points, std::ostream&
        output) {
        for (int k = 0; k < super_ellipse_points.size(); ++k) {
            output << k << '\t' << super_ellipse_points[k].x << '\t' << super_ellipse_points[k].y;
            if (k != 0 && super_ellipse_points[k] == super_ellipse_points[k-1])
                output << '\t' << "equal previous" << '\n';
            else
                output << std::endl;
        }
    }


    void ex12(int a, int b, double n, double m) {
            int N_max = 1000;
            double dt = 2. * pi / static_cast<double>(N_max);
            auto output = ch9::open_output_stream("ch10_ex12.txt");

            std::vector<Point> super_ellipse_points;
            output << std::format("a = {}\tb = {}\tn = {}\tm = {}\n",a,b,n,m);

            for (int k = 0; k < N_max; ++k){
                double t = dt*k;


                double xf = a * get_sgn(cos(t)) * pow(abs(cos(t)),2/m);
                double yf = b * get_sgn(sin(t)) * pow(abs(sin(t)),2/n);

                Point p;
                p.x = static_cast<int>(lround(N_max*xf));
                p.y = static_cast<int>(lround(N_max*yf));

                if (super_ellipse_points.empty() || super_ellipse_points.back() != p)
                    super_ellipse_points.push_back(p);
            }

            print_super_ellipse(super_ellipse_points,output);

    }
}