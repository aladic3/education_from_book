//
// Created by Dmytrenko Kyrylo on 07.05.2026.

module;
#include <algorithm>
#include <iostream>
#include <map>
#include <numbers>
#include <random>
#include <set>
#include <span>
#include <sstream>

#include "../error.h"

module chapter16;

namespace ch16::exercises::Hunt_the_wumpus {

    void print_numbers_of_vector_rooms(std::vector<const Room*>& rooms) {
        for (auto& el : rooms) {
            std::cout << el->number_this << ' ';
        }
        std::cout << std::endl;
    }

    std::default_random_engine& get_rand()
    {
        static std::default_random_engine ran;
        return ran;
    };

    void seed(int s) { get_rand().seed(s); }
    void seed() { get_rand().seed(); }
    inline int random_int(int min, int max) { return std::uniform_int_distribution<>{min, max}(get_rand()); }

    inline int random_int(int max) { return random_int(0, max); }

    std::set<int> get_set_range(const std::pair<int,int>& min_max = {1,20}) {
        std::set<int> result;
        for (int i = min_max.first-1; i < min_max.second; ++i) {
            result.insert(i+1);
        }

        return result;
    }

    int get_random_value_in_set(const std::set<int>& sibel_values, const std::pair<int,int>& min_max = {1,20}) {
        int result_random = random_int(min_max.first,min_max.second);
        int val_left = result_random-1;
        int val_right = result_random+1;
        while (!sibel_values.contains(result_random)) {
            if (sibel_values.contains(val_left)) {
                result_random = val_left;
                break;
            }

            if (sibel_values.contains(val_right)) {
                result_random = val_right;
                break;
            }

            --val_left;
            ++val_right;
        }

        return result_random;
    }

    void init_numbers_of_map(std::vector<Room>& map) {
        auto set = get_set_range();
        for (auto& el: map) {
            int result_random = get_random_value_in_set(set);

            el.number_this = set.extract(result_random).value();

        }
    }



    void init_map(std::vector<Room>& map) {
        map[0].next_1 = &map[1];    map[0].next_2 = &map[4];    map[0].next_3 = &map[7]; // 1
        map[1].next_1 = &map[0];    map[1].next_2 = &map[2];    map[1].next_3 = &map[9]; // 2
        map[2].next_1 = &map[1];    map[2].next_2 = &map[3];    map[2].next_3 = &map[11]; // 3
        map[3].next_1 = &map[13];    map[3].next_2 = &map[4];    map[3].next_3 = &map[2]; // 4
        map[4].next_1 = &map[0];    map[4].next_2 = &map[3];    map[4].next_3 = &map[5]; // 5
        map[5].next_1 = &map[14];    map[5].next_2 = &map[4];    map[5].next_3 = &map[6]; // 6
        map[6].next_1 = &map[16];    map[6].next_2 = &map[5];    map[6].next_3 = &map[7]; // 7
        map[7].next_1 = &map[6];    map[7].next_2 = &map[0];    map[7].next_3 = &map[8]; // 8
        map[8].next_1 = &map[17];    map[8].next_2 = &map[9];    map[8].next_3 = &map[7]; // 9
        map[9].next_1 = &map[10];    map[9].next_2 = &map[8];    map[9].next_3 = &map[1]; // 10
        map[10].next_1 = &map[18];    map[10].next_2 = &map[11];    map[10].next_3 = &map[9]; // 11
        map[11].next_1 = &map[12];    map[11].next_2 = &map[10];    map[11].next_3 = &map[2]; // 12
        map[12].next_1 = &map[11];    map[12].next_2 = &map[19];    map[12].next_3 = &map[13]; // 13
        map[13].next_1 = &map[14];    map[13].next_2 = &map[12];    map[13].next_3 = &map[3]; // 14
        map[14].next_1 = &map[13];    map[14].next_2 = &map[15];    map[14].next_3 = &map[5]; // 15
        map[15].next_1 = &map[14];    map[15].next_2 = &map[16];    map[15].next_3 = &map[19]; // 16
        map[16].next_1 = &map[15];    map[16].next_2 = &map[6];    map[16].next_3 = &map[17]; // 17
        map[17].next_1 = &map[16];    map[17].next_2 = &map[8];    map[17].next_3 = &map[18]; // 18
        map[18].next_1 = &map[10];    map[18].next_2 = &map[17];    map[18].next_3 = &map[19]; // 19
        map[19].next_1 = &map[12];    map[19].next_2 = &map[18];    map[19].next_3 = &map[15]; // 20

        init_numbers_of_map(map);

        return;
    }

    const Room& get_room_from_map_by_number(const int number, const std::vector<Room>& map) {
        for (const Room& room : map) {
            if (room.number_this == number)
                return room;
        }

        error("bad room number");
        return map.front();
    }

    void Game::init_bats(std::set<int> &sibel_values, const int count) {
        for (int i = 0; i < count; ++i) {
            int random_room_number = sibel_values.extract(
                get_random_value_in_set(sibel_values)).value();
            const Room& room_for_bat = get_room_from_map_by_number(random_room_number,this->map);
            this->bats.emplace_back(room_for_bat);
        }

    }



    void Game::init_pits(std::set<int> &sibel_values, const int count) {
        for (int i = 0; i < count; ++i) {
            int random_room_number = sibel_values.extract(
                get_random_value_in_set(sibel_values)).value();
            const Room& room_for_pit = get_room_from_map_by_number(random_room_number,this->map);
            this->pits.emplace_back(room_for_pit);
        }
    }

    void Game::init_wumpus(std::set<int> &sibel_values) {
        int random_room_number = sibel_values.extract(
                get_random_value_in_set(sibel_values)).value();
        const Room& room_for_wumpus = get_room_from_map_by_number(random_room_number,this->map);
        this->wumpus = new Wumpus{room_for_wumpus};
    }

    void Game::init_antagonist(std::set<int> &sibel_values) {
        int random_room_number = sibel_values.extract(
         get_random_value_in_set(sibel_values)).value();
        const Room& room_for_antagonist = get_room_from_map_by_number(random_room_number,this->map);
        this->antagonist = new Antagonist{room_for_antagonist};
    }

    std::vector<Mortal*> Game::get_alive_mobs() {
        std::vector<Mortal*> result;
        result.reserve(bats.size()+2);
        for (Mortal& bat : bats) {
            result.push_back(&bat);
        }

        result.push_back(antagonist);
        result.push_back(wumpus);

        // TODO must tested
        for (auto it = result.begin(); it != result.end();) // clean dead mobs
            if ((*it)->get_location() == &hell_room)
                result.erase(it);
            else
                ++it;


        return result;
    }


    void Pit::contact_with_antagonist(Antagonist *antagonist, const Room *wumpus_room, const Game *engine) const {
        antagonist->die();
    }

    void Bat::die() {
        location = &hell_room;
    }

    const Room* get_random_next_location(const Room* location) {
        const Room* result = nullptr;

        int choise = random_int(1,3);
        switch (choise) {
            case 1:
                result = location->next_1;
                break;

            case 2:
                result = location->next_2;
                break;

            case 3:
                result = location->next_3;
                break;

                default:
                error("bad random engine");

        }

        return result;
    }

    void Bat::contact_with_antagonist(Antagonist * antagonist, const Room *wumpus_room, const Game *engine) const {
        antagonist->bat_move(wumpus_room, engine);
    }

    void Wumpus::move() {
        location = get_random_next_location(location);
    }



    void Wumpus::die() {
        location = &hell_room;
    }


    const Room* get_next_room_from_number(int room_number, const Room* current_room) {
        std::vector<const Room*> available_rooms {
            current_room->next_1,
            current_room->next_2,
            current_room->next_3};

        for (const Room* true_room : available_rooms ) {
            if (true_room->number_this == room_number)
                return true_room;
        }

        return nullptr;
    }

    void kill_mobs_in_room(const std::vector<Mortal*>& mobs,const Room* room) {
        for (const auto mob : mobs) {
            if (room == mob->get_location())
                mob->die();
        }
    }

    void Antagonist::shoot(std::span<int> trajectory, const std::vector<Mortal*>& mobs){
        const Room* current_room = this->location;
        bool is_random = false;

        for (int room_number : trajectory) {
            const Room* prev = current_room;

            if (!is_random) current_room = get_next_room_from_number(room_number,current_room);

            if (current_room == nullptr || is_random) {
                is_random = true;
                current_room = get_random_next_location(prev);
            }

            kill_mobs_in_room(mobs,current_room);
        }

        --arrows_capacity;
    }

    bool Antagonist::move(int next_room) {
        bool result_operation = false;
        std::vector<const Room*> available_rooms {
            location->next_1,
            location->next_2,
            location->next_3};

        for (const Room* true_room : available_rooms ) {
            if (true_room->number_this == next_room) {
                location = true_room;
                result_operation = true;
                break;
            }
        }

        return result_operation;
    }



    std::set<const Room *> get_available_rooms_bat_moving(const Room *wumpus_room, const int depth) {
        std::set<const Room *> available_rooms    {wumpus_room,wumpus_room->next_1,
            wumpus_room->next_2,wumpus_room->next_3};
        std::set last_level {available_rooms};
        for (int i = 0; i < depth; ++i) {
            std::set<const Room *> next_level;
            for (const auto& room : last_level) {
                const auto & first = room->next_1;
                const auto & second = room->next_2;
                const auto & third = room->next_3;

                if (!available_rooms.contains(first)) next_level.emplace(first);
                if (!available_rooms.contains(second)) next_level.emplace(second);
                if (!available_rooms.contains(third)) next_level.emplace(third);
            }
            last_level = next_level;
            available_rooms.insert_range(last_level);
        }

        // available_rooms.extract(wumpus_room);

        return available_rooms;
    }

    const Room* get_random_room_from_set(const std::set<const Room *>& available_rooms ) {
        const int random_room = random_int(0,static_cast<int>(available_rooms.size()));
        int i = 0;

        for (const auto& room : available_rooms) {
            if (i == random_room) {
                return room;
            }
            ++i;
        }

        return nullptr;
    }

    void remove_rooms_with_enemies_from_set(const std::vector<const Enemy*>& enemies, std::set<const Room *>& rooms ) {
        std::vector<const Room*> rooms_for_extract;
        for (const Room* room : rooms)
            for (const Enemy* enemy : enemies)
                if (enemy->is_current_location(room))
                    rooms_for_extract.emplace_back(room);

         for (const Room* room : rooms_for_extract) // extract
            rooms.extract(room);
    }

    void Antagonist::bat_move(const Room *wumpus_room, const Game* engine, const int depth) {
        auto available_rooms = get_available_rooms_bat_moving(wumpus_room,depth);
        std::vector<const Enemy*> enemies = engine->get_list_of_alive_enemies();
        remove_rooms_with_enemies_from_set(enemies,available_rooms); // for legal moving

        location = get_random_room_from_set(available_rooms);
    }


    void Wumpus::contact_with_antagonist(Antagonist *antagonist, const Room *wumpus_room, const Game *engine) const {
        antagonist->die();
    }

    void Antagonist::die() {
        location = &hell_room;
    }

    Game::Game() {
        init_map(this->map);
        auto sibel_rooms_for_game_elements = get_set_range();

        init_pits(sibel_rooms_for_game_elements);
        init_bats(sibel_rooms_for_game_elements);
        init_antagonist(sibel_rooms_for_game_elements);
        init_wumpus(sibel_rooms_for_game_elements);
        
    }

    std::vector<const Enemy *> Game::get_list_of_alive_enemies() const {
        std::vector<const Enemy*> enemies;

        enemies.emplace_back(wumpus);
        for (const Enemy& bat : bats) {
            if (bat.is_alive())
                enemies.emplace_back(&bat);
        }
        for (const Enemy& pit : pits)
            enemies.emplace_back(&pit);

        return enemies;
    }

    std::set<std::string> Game::get_next_rooms_info_from_antagonist() {
        std::set<std::string> info;
        auto enemies = get_list_of_alive_enemies();

        std::vector next_rooms {antagonist->location->next_1,
            antagonist->location->next_2, antagonist->location->next_3};

        for (auto& room : next_rooms)
            for (const Enemy* enemy: enemies)
                if (enemy->is_current_location(room))
                    info.insert(enemy->get_message_preview());

        std::ostringstream info_about_locations ;
        info_about_locations << "Current location: " << antagonist->location->number_this << ", rooms around: ";

        for (auto& room : next_rooms)
            info_about_locations << room->number_this << " ";

        info.insert(info_about_locations.str());

        return info;
    }



    void print_info_about_next_rooms(const std::set<std::string>& info_about_enemies) {
        if (info_about_enemies.empty())
            std::cout << "No menaces around you.\n";

        for (auto& msg : info_about_enemies) {
            std::cout << msg << std::endl;
        }
    }

    void Game::play() {
        while (antagonist->is_alive() && wumpus->is_alive()) {
            std::cout << "Current capacity of your arrows: " << antagonist->arrows_capacity << std::endl;
            print_info_about_next_rooms(get_next_rooms_info_from_antagonist());

            std::cout << "What would you do? Enter 'm' if you want move, 's' if you want shoot: ";
            char answer = 0;
            std::cin >> answer;

            switch (answer) {
                case 'm':
                    move_antagonist();
                    after_move_antagonist(); // TODO see to Antagonist::bat_move
                    break;

                case 's':
                    shoot_antagonist();
                    break;

                default:
                    std::cout << "Bad answer!";
                    continue;
            }


        }


    }

    void Game::shoot_antagonist() {
        if (antagonist->arrows_capacity == 0) {
            std::cout << "You can't shooting, capacity arrows is 0! But you can move)";
            return;
        }

        std::cout << "Shooting..." << std::endl
            << "Enter how much rooms arrow must reached (less then 5): ";

        int count_rooms_reaching;
        std::cin >> count_rooms_reaching;
        std::vector<int> trace(count_rooms_reaching);

        std::cout << "Inputting trace...";
        for (int i = 0; i < count_rooms_reaching; ++i) {
            std::cout << "Enter trace[" <<  i<< "]: ";
            std::cin >> trace[i];
            std::cout << std::endl;
        }

        antagonist->shoot(trace,get_alive_mobs());
    }



    void Game::move_antagonist() const {
        using namespace std;
        vector<const Room*> available_rooms {antagonist->location->next_1,  antagonist->location->next_2,
                antagonist->location->next_3};
        cout << "Next available rooms for moving: ";
        print_numbers_of_vector_rooms(available_rooms);

        cout << "Enter number of room for move: ";

        int input_number;
        cin >> input_number;
        while (!antagonist->move(input_number)){
            cout << "Bad input number! Please, enter rooms from this list: ";
            print_numbers_of_vector_rooms(available_rooms);
            cout << "Enter number of room for move: ";
            cin >> input_number;
        }

    }

    void Game::after_move_antagonist() const {
        auto enemies = get_list_of_alive_enemies();

        for (const Enemy* enemy : enemies)
            if (enemy->is_current_location(antagonist->location)) {
                enemy->contact_with_antagonist(antagonist,wumpus->location, this);
                break;
            }
    }
}


namespace ch16::exercises {
    void to_lower(char* input_str) {
        for (char* p = input_str; *p != 0; ++p) {
            if (*p > 'A' && *p < 'Z')
                *p += 32;
        }
    }

    void print_str(const char* str) {
        for (const char* p = str; *p != 0; ++p)
            std::cout << *p;

        std::cout << std::endl;
    }

    int str_len(const char* str) {
        int result = 0;

        for (const char* p = str; *p != 0; ++p)
            ++result;

        return result;
    }

    char* str_dup(const char* str) {
        int len = str_len(str);
        char* res = new char [len];
        for (int i = 0; i < len; ++i) {
            res[i] = str[i];
        }

        return res;
    }

    const char *find_x(const char *str, const char *x) {
        const char* px = x;
        const char *result = nullptr;

        bool processing = false;
        for (const char* ps = str; *ps != 0 && *px != 0; ++ps) {
            if (processing && *ps != *px) {
                px = x;
                processing = false;
            }

            if (*ps == *px) {
                if (processing == false)
                    result = ps;
                ++px;
                processing = true;
            }
        }

        if (*px == 0)
            return result;

        return nullptr;
    }

    char * str_dup(const char * str, int size) {
        int len = size;
        char* res = new char [len];
        for (int i = 0; i < len; ++i) {
            res[i] = str[i];
        }

        return res;
    }

    const char * find_x(const char *str, const char *x, const std::pair<int, int> &size) {
        const char* px = x;
        const char *result = nullptr;
        int i1 = 0;
        int i2 = 0;

        bool processing = false;
        for (const char* ps = str; i1<size.first && i2<size.second; ++ps) {
            ++i1;
            if (processing && *ps != *px) {
                px = x;
                i2 = 0;
                processing = false;
            }

            if (*ps == *px) {
                if (processing == false) {
                    result = ps;
                }

                ++i2;
                ++px;
                processing = true;
            }
        }

        if (i2 == size.second) {
            return result;
        }


        return nullptr;
    }

    int str_cmp(const char *s1, const char *s2) {

        while (*s1 && *s2 && *s1 == *s2) {
            ++s1;
            ++s2;
        }

        return *s1 - *s2; // arbitrary banana 1-2 = -1
    }

    int str_cmp(const char *s1, const char *s2, const std::pair<int,int>& size) {
        int i1 = 0;
        int i2 = 0;
        while (i1<size.first && i2<size.second && *s1 == *s2) {
            ++s1;
            ++s2;
            ++i1;
            ++i2;
        }

        if (i1 == i2 && size.first < size.second) {
            return '\0' - *s2;

        }
        if (i1 == i2 && size.first > size.second) {
            return *s1 - '\0';
        }

        return *s1 - *s2; // arbitrary banana 1-2 = -1
    }

    char* cat_dot_c(const char *s1, const char *s2, const char* separator) {
        const std::pair len {str_len(s1),str_len(s2)};
        const int separator_size = str_len(separator);
        char* result = new char[len.first+len.second+separator_size]; //(s1,len.first+len.second+separator_size);

        for (int i = 0; *s1 != 0; ++i && ++s1) // add s1 to result
            result[i] = *s1;

        for (int i = len.first; *separator != 0; ++i && ++separator) // add separator to result
          result[i] = *separator;

        for (int i = len.first+separator_size; *s2 != 0; ++i && ++s2)
          result[i] = *s2;

        return result;
    }

    std::string cat_dot(const char *s1, const char *s2, const char* separator) {
        const std::pair len {str_len(s1),str_len(s2)};
        const int separator_size = str_len(separator);
        std::string result (s1,len.first+len.second+separator_size);

        result.replace(len.first,separator_size,separator);
        result.replace(len.first+separator_size,len.second,s2);



        return result;
    }

    std::string cat_dot(const std::string &s1, const std::string &s2, const std::string& separator ) {
        std::string result (s1,0,s1.length()+s2.length()+separator.length());
        result.insert(s1.length(),separator);
        result.insert(s1.length()+separator.length(),s2);

        return result;
    }

    bool isPalindrome(const std::string & input) {
        std::string reverse {"",input.size()};
        auto iterator = input.end();
        auto reverse_iterator = reverse.begin();

        do {
            --iterator;
            *reverse_iterator = *iterator;
            ++reverse_iterator;
        } while (iterator != input.begin());

        return reverse == input;
    }

    char* get_medium_char_from_str(char* str) { // if 2 elements, return first. if 3 elements, return second
        const int size = str_len(str);

        if (size%2 == 1)  return str+size/2;

        return str+size/2 - 1;
    }

    bool isPalindrome(const char * input) {
        int size = str_len(input);
        if (size == 0) return false;

        for (const char* ch = input; *ch == *(ch+size-1) && size > 0; ++ch && (size-=2)){}

        return size <= 0;

    }

    /*std::istream& operator>>(std::istream & is, char * buffer) {
        for (; is.width() > 0; ++buffer) {
            is.get(buffer,)
        }
        return is;
    }*/

    char* read_c_string_throwable(std::istream& is, char* buffer, int max){
        is.width(max);

        is.get(buffer,max);
        char last = 0;
        is.get(last);
        if (last != '\n' && last != 0)
            error("buffer is too short!");

        return buffer;
    }

    void copy_str_to_str(const char* from, char* to) {
        for (const char* ch = from; *ch != 0; ++ch) {
            *to = *ch;
            ++to;
        }
    }

    char* read_c_string_extendable(std::istream& is, char* buffer, int* max){ //return buffer
        is.get(buffer,*max);

        char last = 0;
        is.get(last);

        int new_size = *max;
        for (; !is.eof() && last != '\n'; ) {
            new_size+=*max;
            is.putback(last);
            char* copy = str_dup(buffer);
            delete [] buffer;
            buffer = new char[new_size];
            copy_str_to_str(copy,buffer);
            delete [] copy;
            is.get(buffer+new_size-*max-1,*max+1);
            is.get(last);
        }

        *max = new_size;
        return buffer;
    }

    void j() {
        char x[20];
        std::istringstream stream("HelloWorld");
        stream.width(15);
        stream >> x;
        for (auto c = x;  *c != 0 ; ++c){
            std::cout << *c;
        }
        auto b = stream.get();
        if ( !stream.eof())
            std::cout << "Overflow";
        else
            std::cout << "Good";
       // stream.read(x, sizeof x);
        std::cout << "\nCharacters extracted: " << stream.gcount();

    }

    void ex13() {
        using namespace ch16::exercises::Hunt_the_wumpus;

        Game cave;

        cave.play();

    }

    void ex12() {
        int max = 5;
        char* buffer = new char[max];
        char buffer2 [max];


        std::cout << "Enter palindrome: ";
        std::cout << isPalindrome(read_c_string_throwable(std::cin,buffer2,max));


        while (std::cin) {
            std::cout << "Enter palindrome: ";
            std::string prompt =
                isPalindrome(read_c_string_extendable(std::cin,buffer,&max)) ? "It is Palindrome\n"
                : "It is not palindrome\n";
            std::cout << prompt;
        }



        delete [] buffer;
    }

    void ex11() {
        //j();
        int max = 3;
        char* buffer = new char[max];
        read_c_string_throwable(std::cin,buffer,max);
        std::istringstream str {"1234"};
        read_c_string_throwable(str,buffer,max);
        read_c_string_extendable(std::cin,buffer,&max);
        bool res = isPalindrome("BooB");
        res = isPalindrome("BokoB");
        res = isPalindrome("home");
        res = isPalindrome("tennet");

        delete [] buffer;
    }

    void ex8_9_10() {
        std::cout << cat_dot(std::string("cat"),std::string("dog"), "bababony") << std::endl;
        std::cout << cat_dot("cat","dog","-+-=") << std::endl;
        auto cat = cat_dot_c("cat","dog","-+-=");
        std::cout << cat;
        delete [] cat;
        cat = nullptr;
    }

    void ex7() {
        cat_dot("bam","boom");
    }


    void ex5() {
        char a [] = {'1','2','3','4'};
        char b [] = {'1','2','3','4', '5'};
        char aa[] = {"1234"};
        char bb[] = {"12345"};
        char s[] {"Hello, world! ellow bababa."};
        char x[] {"world!"};



        auto result = find_x(b,a,{5,4});
        result = find_x(s, "world!",{str_len(s),6});
        int asd = str_cmp(a,b,std::pair<int,int>{4,5});
        int asdd = str_cmp(aa,bb, {str_len(aa),str_len(bb)});
        asd =  std::strcmp(a,b);
        asdd = std::strcmp(aa,bb);
        auto r = str_dup(a, 4);
        delete [] r;

    }

    void ex4() {
       /* std::cout << str_cmp("Arbitrary","arbitrary") << std::endl;
        std::cout << str_cmp("ban","banana") << std::endl;
        std::cout << str_cmp("boom","beem") << std::endl;
        std::cout << str_cmp("boo","bo") << std::endl;
        std::cout << str_cmp("arbitrary","arbitrary") << std::endl;*/
    }


    void ex3() {
        char s[] {"Hello, world! ellow bababa."};
        char x[] {"world!"};

        const char* found = find_x(s, "world!");
        found = find_x(s,"ellow ba");
        if (found == nullptr) {
            std::cout << "Not found";
            return;
        }


        print_str(found);
    }

    void ex1() {
        char str [] = "Hello, World! NICE TO SEE YOU!!!\n";
        print_str(str);
        to_lower(str);
        print_str(str);
    }

    void ex2() {
        char buffer [256] {"Good game... It was nice idea...Last your idea..."};
        char* copy = str_dup(buffer);

        print_str(buffer);
        print_str(copy);

        delete [] copy;
    }




}