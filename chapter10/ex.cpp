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
        Point()= default;
        int x = 0;
        int y = 0;

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

    void print_vec_points(const std::vector<Point>& poly_points, std::ostream&
        output) {
        for (int k = 0; k < poly_points.size(); ++k) {
            output << k << '\t' << poly_points[k].x << '\t' << poly_points[k].y;
            if (k != 0 && poly_points[k] == poly_points[k-1])
                output << '\t' << "equal previous" << '\n';
            else
                output << std::endl;
        }
    }

    std::vector<Point> get_superellipse_points(std::pair<int,int> ab, std::pair<double,double> mn) {
        int a = ab.first;
        int b = ab.second;
        double m = mn.first;
        double n = mn.second;

        std::vector<Point> super_ellipse_points;
        int N_max = 1000;
        double dt = 2. * pi / static_cast<double>(N_max);

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

        return super_ellipse_points;
    }

    double distance_between_points(const std::pair<Point,Point>& points) {
        auto first = points.first;
        auto second = points.second;

        auto a = abs(first.x - second.x);
        auto b = abs(first.y - second.y);
        auto c = pow(a*a + b*b, 0.5);

        return c;
    }

    std::vector<double> get_sum_distances(const std::vector<Point>& poly_points) {
        std::vector<double> result;
        std::pair<Point,Point> two_points;
        two_points.second = poly_points.front();

        for (int i = 1; i < poly_points.size(); ++i) {
            two_points.first = two_points.second;
            two_points.second = poly_points[i];
            auto distance = distance_between_points(two_points);

            if (result.empty())
                result.push_back(distance);
            else
                result.push_back(result.back()+distance);
        }

        return result;
    }

    std::vector<double> get_segment_distances(double step, int N) {
        std::vector<double> result;

        for (int i = 0; i<N; ++i) { // first point of segment equal zero and this point will be first point poly_points
            result.push_back(i*step);
        }

        return result;
    }

    double get_segment_length(const std::vector<double>& poly_distances, int i) {
       return  i==0 ? poly_distances[i] : poly_distances[i] - poly_distances[i-1];
    }

    Point get_interpolary_point(const std::vector<Point>& poly_points, int i, double local_t) {
        Point A = poly_points[i];
        Point B = poly_points[i+1];

        double xf = A.x + local_t * (B.x - A.x);
        double yf = A.y + local_t * (B.y - A.y);

        Point p;
        p.x = static_cast<int>(lround(xf));
        p.y = static_cast<int>(lround(yf));

        return p;
    }

    std::vector<Point> get_segment_coordinates(const std::vector<Point>& poly_points,
        const std::vector<double>& target_distances, const std::vector<double>& poly_distances) {
        std::vector<Point> result_coordinates{poly_points[0]}; // first point

        for (int i = 1; i < target_distances.size(); ++i) // first is zero point
        {
            double target = target_distances[i];
            for (int j = 0; j < poly_distances.size(); ++j) {
                if (poly_distances[j] < target)
                    continue;

                double segment_length = get_segment_length(poly_distances,j);
                double local_t = (poly_distances[j] - target) / segment_length;
                Point p = get_interpolary_point(poly_points,j,local_t);

                result_coordinates.push_back(p);
                break;
            }

        }

        return result_coordinates;
    }

    std::vector<Point> get_coordinates_equal_segments(const std::vector<Point>& poly_points, int N) {
        std::vector<double> poly_distances = get_sum_distances(poly_points); // last element is approximate distance entire polygon

        double step = poly_distances.back()/N;
        std::vector<double> target_distances = get_segment_distances(step,N);

        return get_segment_coordinates(poly_points,target_distances,poly_distances);
    }

    void ex12(int a, int b, double n, double m, int N) {
        auto output = ch9::open_output_stream("ch10_ex12.txt");
        std::vector<Point> super_ellipse_points = get_superellipse_points({a,b},{m,n});
        std::vector<Point> equal_segments_coordinates = get_coordinates_equal_segments(super_ellipse_points,N);

        output << std::format("a = {}\tb = {}\tn = {}\tm = {}\tcount points = {}\n",
            a,b,n,m,super_ellipse_points.size());
        print_vec_points(super_ellipse_points,output);
        output << std::format("\nEqual segments coordinates for N = {} elements:\n",N);
        print_vec_points(equal_segments_coordinates,output);
    }
}