//
// Created by Dmytrenko Kyrylo on 24.12.2025.
//
module;

#include <string>
#include <utility>
#include <vector>
#include <iostream>

export module try_drill;

namespace ch9::ex3 {
    // using func for reading  ch9::ex1::read_file

    const std::vector<char> vowels {'a', 'e', 'i', 'o', 'u', 'y'};

    export [[nodiscard]] std::vector<std::string> read_file(const std::string& file_name);
    export void write_to_file(const std::string& file_name, const std::vector<std::string>& vec);
    export void remove_vowels_from_vector(std::vector<std::string>& vec);
    void remove_vowels_from_word(std::string& word);
    bool is_vowel_letter( char letter);

    export void test();

}

namespace ch9::ex1 {
    export [[nodiscard]] std::vector<std::string> read_file(const std::string& file_name);
    export [[nodiscard]] std::vector<std::string>read_line_file(const std::string& file_name);
    export void write_line_to_file(const std::string& file_name, const std::vector<std::string>& vec);
    export  std::vector<std::string>& convert_to_lower(std::vector<std::string>& input_lines);

    std::ifstream open_input_stream(const std::string& file_name);
    std::ofstream open_output_stream(const std::string& file_name);

    export void print_str_vec(const std::vector<std::string>& str_v, std::ostream& os);
    export void print_vec_with_line_num(const std::vector<std::string>& str_v, std::ostream& os);

    std::string& str_tolower(std::string& s);

    export void test();

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
    std::vector<UserInfo> test_create_vector_table();
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

    std::vector<Point> read_points_count_times(const int count_points, std::istream& is);
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