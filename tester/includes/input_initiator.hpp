#ifndef __INPUT_INITIATOR_HPP__
#define __INPUT_INITIATOR_HPP__

#include <ctime>
#include <vector>
#include <iostream>
#include <limits.h>
#include <float.h>

#define SHORT_INPUTS_SIZE 10
#define MID_INPUTS_SIZE 256
#define LONG_INPUTS_SIZE 5028

#define TEST_STRING_ELEMENT_LENGTH 10
#define TEST_INT_ELEMENT_LIMIT 10000
#define TEST_FLOAT_ELEMENT_LIMIT 10000
#define TEST_DOUBLE_ELEMENT_LIMIT 10000

struct test_dataType_all {};
struct test_dataType_char {};
struct test_dataType_int {};
struct test_dataType_float {};
struct test_dataType_double {};
struct test_dataType_string {};


struct char_bucket {
    std::vector<char> short_inputs;
    std::vector<char> mid_inputs;
    std::vector<char> long_inputs;
};

struct int_bucket {
    std::vector<int> short_inputs;
    std::vector<int> mid_inputs;
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
    struct int_bucket int_bucket;
    struct char_bucket char_bucket;
    struct double_bucket double_bucket;
    struct string_bucket string_bucket;
    struct float_bucket float_bucket;
};

std::string generate_rand_string(void) {
    std::string ret = "";
    // TEST_STRING_ELEMENT_LENGTH is defined in top of this header file;
    for (size_t i  = 0; i < TEST_STRING_ELEMENT_LENGTH; i++) {
        ret += (33 + (std::rand() % 107)); // filled by 33 (!) to 126 (~)
    }
    return ret;
};

int generate_rand_int(void) {
    return std::rand() % TEST_INT_ELEMENT_LIMIT;
}

char generate_rand_char(void) {
    return 33 + (std::rand() % 107); // filled by 33 (!) to 126 (~)
}

float generate_rand_float(void) {
    float FLOAT_MIN = std::numeric_limits<float>::min();
    float FLOAT_MAX = std::numeric_limits<float>::max();
    float low = FLOAT_MIN > (TEST_FLOAT_ELEMENT_LIMIT * -1) ? FLOAT_MIN : TEST_FLOAT_ELEMENT_LIMIT * -1;
    float high = FLOAT_MAX < TEST_FLOAT_ELEMENT_LIMIT ? FLOAT_MAX : TEST_FLOAT_ELEMENT_LIMIT;
    
    return low + static_cast<float>(std::rand()) * static_cast<float>(high - low) / RAND_MAX;
}

double generate_rand_double(void) {
    double DOUBLE_MIN = std::numeric_limits<double>::min();
    double DOUBLE_MAX = std::numeric_limits<double>::max();
    double low = DOUBLE_MIN > (TEST_DOUBLE_ELEMENT_LIMIT * -1) ? DOUBLE_MIN : TEST_DOUBLE_ELEMENT_LIMIT * -1;
    double high = DOUBLE_MAX < TEST_DOUBLE_ELEMENT_LIMIT ? DOUBLE_MAX : TEST_DOUBLE_ELEMENT_LIMIT;
    
    return low + static_cast<double>(std::rand()) * static_cast<double>(high - low) / RAND_MAX;
}

template <class T>
std::vector<T> build_vector(std::size_t size, T (*fptr_generate_elem)(void)) {
    std::vector<T> ret;
    for (std::size_t i = 0; i < size; i++) {
        ret.push_back(fptr_generate_elem());
    }
    return ret;
}


class Input_initiator {
    private :
        Input_initiator(const Input_initiator& other) {
            (void) other;
        };
        Input_initiator& operator= (const Input_initiator& rhs) {
            (void) rhs;
            return *this;
        };
    
    public :
        Input_initiator() {
            std::srand(std::time(nullptr));
        };
        ~Input_initiator() {
            ;
        }

        Test_inputs create_inputs_rand(test_dataType_all) {
            Test_inputs ret;

            ret.char_bucket.short_inputs = build_vector(SHORT_INPUTS_SIZE, generate_rand_char);
            ret.char_bucket.mid_inputs = build_vector(MID_INPUTS_SIZE, generate_rand_char);
            ret.char_bucket.long_inputs = build_vector(LONG_INPUTS_SIZE, generate_rand_char);
            
            ret.int_bucket.short_inputs = build_vector(SHORT_INPUTS_SIZE, generate_rand_int);
            ret.int_bucket.mid_inputs = build_vector(MID_INPUTS_SIZE, generate_rand_int);
            ret.int_bucket.long_inputs = build_vector(LONG_INPUTS_SIZE, generate_rand_int);

            ret.string_bucket.short_inputs = build_vector(SHORT_INPUTS_SIZE, generate_rand_string);
            ret.string_bucket.mid_inputs = build_vector(MID_INPUTS_SIZE, generate_rand_string);
            ret.string_bucket.long_inputs = build_vector(LONG_INPUTS_SIZE, generate_rand_string);
            
            ret.double_bucket.short_inputs = build_vector(SHORT_INPUTS_SIZE, generate_rand_double);
            ret.double_bucket.mid_inputs = build_vector(MID_INPUTS_SIZE, generate_rand_double);
            ret.double_bucket.long_inputs = build_vector(LONG_INPUTS_SIZE, generate_rand_double);
            
            ret.float_bucket.short_inputs = build_vector(SHORT_INPUTS_SIZE, generate_rand_float);
            ret.float_bucket.mid_inputs = build_vector(MID_INPUTS_SIZE, generate_rand_float);
            ret.float_bucket.long_inputs = build_vector(LONG_INPUTS_SIZE, generate_rand_float);
            return ret;
        };

        template<class T>
        Test_inputs create_inputs_rand(test_dataType_int) {
            Test_inputs ret;
            ret.int_bucket.short_inputs = build_vector(SHORT_INPUTS_SIZE, generate_rand_int);
            ret.int_bucket.mid_inputs = build_vector(MID_INPUTS_SIZE, generate_rand_int);
            ret.int_bucket.long_inputs = build_vector(LONG_INPUTS_SIZE, generate_rand_int);
            return ret;
        };

        template<class T>
        Test_inputs create_inputs_rand(test_dataType_char) {
            Test_inputs ret;
            ret.char_bucket.short_inputs = build_vector(SHORT_INPUTS_SIZE, generate_rand_char);
            ret.char_bucket.mid_inputs = build_vector(MID_INPUTS_SIZE, generate_rand_char);
            ret.char_bucket.long_inputs = build_vector(LONG_INPUTS_SIZE, generate_rand_char);
            return ret;
        };

        template<class T>
        Test_inputs create_inputs_rand(test_dataType_string) {
            Test_inputs ret;
            ret.string_bucket.short_inputs = build_vector(SHORT_INPUTS_SIZE, generate_rand_string);
            ret.string_bucket.mid_inputs = build_vector(MID_INPUTS_SIZE, generate_rand_string);
            ret.string_bucket.long_inputs = build_vector(LONG_INPUTS_SIZE, generate_rand_string);
            return ret;
        };

        template<class T>
        Test_inputs create_inputs_rand(test_dataType_float) {
            Test_inputs ret;
            ret.float_bucket.short_inputs = build_vector(SHORT_INPUTS_SIZE, generate_rand_float);
            ret.float_bucket.mid_inputs = build_vector(MID_INPUTS_SIZE, generate_rand_float);
            ret.float_bucket.long_inputs = build_vector(LONG_INPUTS_SIZE, generate_rand_float);
            return ret;
        };

        template<class T>
        Test_inputs create_inputs_rand(test_dataType_double) {
            Test_inputs ret;
            ret.double_bucket.short_inputs = build_vector(SHORT_INPUTS_SIZE, generate_rand_double);
            ret.double_bucket.mid_inputs = build_vector(MID_INPUTS_SIZE, generate_rand_double);
            ret.double_bucket.long_inputs = build_vector(LONG_INPUTS_SIZE, generate_rand_double);
            return ret;
        };
};

#endif // __INPUT_INITIATOR_HPP__