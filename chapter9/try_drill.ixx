//
// Created by Dmytrenko Kyrylo on 24.12.2025.
//
module;

#include <string>
#include <utility>
#include <vector>
#include <iostream>

export module try_drill;

namespace ch9::ex1 {
    std::vector<std::string> read_file(const std::string& file_name);
    void write_to_file(const std::string& file_name);
    std::vector<std::string>& convert_to_lower(std::vector<std::string>& input_lines);

    void test();

}

namespace ch9::drill {
    export void print_birthyear();
    export void try_reading_different_bases();

    struct UserInfo {
        std::string first_name;
        std::string last_name;
        std::string t_number;
        std::string email;
    };

    export class UserInfoTable {
    public:
        UserInfoTable()= default;
        explicit UserInfoTable(std::vector<UserInfo> table):_table(std::move(table)){};
        void add_row_to_table(const UserInfo& user_info){_table.push_back(user_info);}
        [[nodiscard]] const std::vector<UserInfo>& get_table() const{ return _table;}




    private:
        std::vector<UserInfo> _table;

    };

    std::ostream& print_table_vector(std::ostream& os, const std::vector<UserInfo>& table_vec);
    export std::ostream& operator<<(std::ostream& os, const UserInfoTable& table);
    export  std::ostream& operator<<(std::ostream& os, const UserInfo& row);
    export  void test_table();
}


namespace  ch9::drill11 {
    export struct Point {
        int x;
        int y;
    };


    export std::vector<Point> read_points_from_file(const std::string& file_name);
    export  void write_points_to_file(const std::string& file_name, const std::vector<Point>& points);
    export std::vector<Point> write_points_to_file_with_prompt(const std::string& file_name);
    std::vector<Point> read_from_prompt();
    std::ofstream& write_points_to_filestream(std::ofstream& ofs, const std::vector<Point>& points);
    void print_points(const std::vector<Point>& points_v);
    export  void test();

    export std::istream& operator>>(std::istream& is,  Point& p);
    export std::ostream& operator<<(std::ostream& os, const Point& p);


}

namespace ch9::try_s {
    export void print_birthyear();
    export void test_format();
}