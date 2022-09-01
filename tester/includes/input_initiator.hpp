#ifndef __INPUT_INITIATOR_HPP__
#define __INPUT_INITIATOR_HPP__

#include <ctime>
#include <vector>
#include <iostream>

#define SHORT_INPUTS_SIZE 10
#define MID_INPUTS_SIZE 256
#define LONG_INPUTS_SIZE 5028

#define TEST_STRING_ELEMENT_LENGTH 10
#define TEST_INT_ELEMENT_LIMIT 10000
#define TEST_FLOAT_ELEMENT_LIMIT 10000
#define TEST_DOUBLE_ELEMENT_LIMIT 10000

struct char_bucket {
    std::vector<char> short_inputs;
    std::vector<char> mid_inputs;
    std::vector<char> long_inputs;
};

struct int_bucket {
    std::vector<int> short_inputs;
    std::vector<int> mid_inputsid_inputs;
    std::vector<int> long_inputs;
};

struct float_bucket {
    std::vector<float> short_inputs;
    std::vector<float> mid_inputs;
    std::vector<float> long_inputs;
};

struct double_bucket {
    std::vector<double> short_inputs;
    std::vector<double> mid_inputs;
    std::vector<double> long_inputs;    
};

struct string_bucket {
    std::vector<std::string> short_inputs;
    std::vector<std::string> mid_inputs;
    std::vector<std::string> long_inputs;
};

struct Test_inputs{
    struct int_bucket& int_bucket;
    struct char_bucket& char_bucket;
    struct double_bucket& double_bucket;
    struct string_bucket& string_bucket;
    struct float_bucket& float_bucekt;
};

static std::string& generate_rand_string(void) {
    std::string ret = std::string("");
    // TEST_STRING_ELEMENT_LENGTH is defined in top of this header file;
    for (size_t i  = 0; i < TEST_STRING_ELEMENT_LENGTH; i++) {
        ret += (33 + (std::rand() % 107)); // filled by 33 (!) to 126 (~)
    }
    return ret;
};

template<class T>
std::vector<T> fill_rand<T>(size_t size) {
    (void) size;
    // this is origin definition for explicit specialization
    // define fill_rand by datatype you want as below
    return NULL;
};

// template<>
// std::vector<char> fill_rand<char>(size_t size) {
//     std::vector<char> ret;
//     for (size_t i = 0; i < size; i++) {
//         ret.append(33 + (std::rand() % 107)); // filled by 33 (!) to 126 (~)
//     }
//     return ret;
// };

// template<>
// std::vector<std::string> fill_rand<std::string>(size_t size) {
//     std::vector<std::string> ret;
//     for (size_t i = 0; i < size; i++) {
//         ret.append(generate_rand_string());
//     }
//     return ret;
// };

template<>
std::vector<int> fill_rand<int>(size_t size) {
    std::vector<int> ret;
    for (size_t i = 0; i < size; i++) {
        ret.append(std::rand() % TEST_INT_ELEMENT_LIMIT);
    }
    return ret;
};

// template<>
// std::vector<float> fill_rand<float>(size_t size) {
//     std::vector<float> ret;
//     int low = 0;
//     int high = TEST_FLOAT_ELEMENT_LIMIT;
//     for (size_t i = 0; i < size; i++) {
//         float rand = low + static_cast<float>(std::rand()) * static_cast<float>(high - low) / RAND_MAX;
//         ret.append(rand);
//     }
//     return ret;
// };

// template<>
// std::vector<double> fill_rand<double>(size_t size) {
//     std::vector<double> ret;
//     int low = 0;
//     int high = TEST_DOUBLE_ELEMENT_LIMIT;
//     for (size_t i = 0; i < size; i++) {
//         double rand = low + static_cast<double>(std::rand()) * static_cast<double>(high - low) / RAND_MAX;
//         ret.append(rand);
//     }
//     return ret;
// };

class Input_initiator {
    private :
        Input_initiator(const Input_initiator& other) {};
        Input_initiator& operator= (const Input_initiator& rhs) {};
    
    public :
        Input_initiator() {
            std::srand(std::time(nullptr));
        };

        template<T>
        Test_inputs& create_inputs_rand(void) {
            struct Test_inputs& ret = new input_list_bucket();
            ret.int_bucket = create_inputs_rand<int>();
            return ret;
        };

        template<>
        int_bucket& create_inputs_rand<int>(void) {
            struct int_bucket& ret = new int_bucket;
            ret.short_inputs = fill_rand<int>(SHORT_INPUTS_SIZE);
            ret.mid_inputs = fill_rand<int>(MID_INPUTS_SIZE);
            ret.long_inputs = fill_rand<int>(LONG_INPUTS_SIZE);
            return ret;
        }
        
        std::ostream& operator<< (std::ostream& os, Test_inputs& ti) {
            os << ti->int_bucket;
            return os;
        }
}

std::ostream& operator<< (std::ostream& os, int_bucket& ib) {
    os << "[short int_list] : [";
    for (size_t i = 0; i < SHORT_INPUTS_SIZE; i++) {
        os << ib.short_inputs[i] << " ";
    }
    os << "]\n";
    os << "[mid int_list] : [";
    for (size_t i = 0; i < MID_INPUTS_SIZE; i++) {
        os << ib.mid_inputs[i] << " ";
    }
    os << "]\n";
    os << "[long int_list] : [";
    for (size_t i = 0; i < LONG_INPUTS_SIZE; i++) {
        os << ib.long_inputs[i] << " ";
    }
    os << "]\n";
    return os;
}

#endif // __INPUT_INITIATOR_HPP__