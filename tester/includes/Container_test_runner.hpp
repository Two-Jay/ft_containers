#ifndef __CONTAINER_TEST_RUNNER__
#define __CONTAINER_TEST_RUNNER__

#include "input_initiator.hpp"

struct testType_shortCase {};
struct testType_midCase {};
struct testType_longCase {};

template <typename T>
const T& check_test_type(const std::string& type_param) {
    if (type_param == "int") {
        return test_dataType_int();
    } else if (type_param == "char") {
        return test_dataType_char();
    } else if (type_param == "string") {
        return test_dataType_string();
    } else if (type_param == "double") {
        return test_dataType_double();
    } else if (type_param == "float") {
        return test_dataType_float();
    } else {
        return test_dataType_all();
    }
}

class Container_test_runner {
    private :
        Test_inputs inputs;


    public :
        Container_test_runner() {
            Input_initiator input_initiator;
            inputs = input_initiator.create_inputs_rand(test_dataType_all());
        };

        Container_test_runner(const std::string& type_param) {
            Input_initiator input_initiator;
            inputs = input_initiator.create_inputs_rand(check_test_type<T>(type_param));
        };

        Container_test_runner(Test_inputs& inputs) {
            this->inputs = inputs;
        }
        virtual ~Container_test_runner() {};
        Container_test_runner(Container_test_runner& other) {
            this->inputs = other.inputs;
        };

        const Test_inputs& get_inputs(void) const {
            return this->inputs;
        }

        void set_inputs(const Test_inputs& inputs) {
            this->inputs = inputs;
        }

        virtual void run_allcase(void) {
            run_certain_length(testType_shortCase());
            run_certain_length(testType_midCase());
            run_certain_length(testType_longCase());
        };

        virtual void run_certain_length(testType_shortCase) = 0;
        virtual void run_certain_length(testType_midCase) = 0;
        virtual void run_certain_length(testType_longCase) = 0;

        Container_test_runner& operator= (const Container_test_runner& rhs) {\
            if (this != &rhs) {
                this->set_inputs(rhs.get_inputs());
            }
            return *this;
        };
};

struct Experimental_vectors {
    std::vector<int> int_vector;
    std::vector<char> char_vector;
    std::vector<std::string> string_vector;
    std::vector<double> double_vector;
    std::vector<float> float_vector;
};

struct Comparison_vectors {
    std::vector<int> int_vector;
    std::vector<char> char_vector;
    std::vector<std::string> string_vector;
    std::vector<double> double_vector;
    std::vector<float> float_vector;
};

class Test_runner_vector : public Container_test_runner {
    
    // 멤버편수로 컨테이너별 테스트 객체 생성
    // 멤버변수로 잡아둔 테스트 객체 내에서 In/output 관리하기
    private :
        Experimental_vectors experimental_vectors;
        Comparison_vectors comparison_vectors;

    public :
        Test_runner_vector() {};
        virtual ~Test_runner_vector() {};

        template<class T>
        std::vector<T>& get_experimental_vector(std::string type_name) {
            if (type_name == "int") {
                return experimental_vectors.int_vector;
            } else if (type_name == "char") {
                return experimental_vectors.char_vector;
            } else if (type_name == "string") {
                return experimental_vectors.string_vector;
            } else if (type_name == "double") {
                return experimental_vectors.double_vector;
            } else if (type_name == "float") {
                return experimental_vectors.float_vector;
            } else {
                return experimental_vectors.int_vector;
            }
        }

        template<class T>
        std::vector<T>& get_comparison_vector(std::string type_name) {
            if (type_name == "int") {
                return comparison_vectors.int_vector;
            } else if (type_name == "char") {
                return comparison_vectors.char_vector;
            } else if (type_name == "string") {
                return comparison_vectors.string_vector;
            } else if (type_name == "double") {
                return comparison_vectors.double_vector;
            } else if (type_name == "float") {
                return comparison_vectors.float_vector;
            } else {
                return comparison_vectors.int_vector;
            }
        } 

        virtual void run_allcase(void) {
            run_certain_length(testType_shortCase());
            run_certain_length(testType_midCase());
            run_certain_length(testType_longCase());
        };

        virtual void run_certain_length(testType_shortCase) {

        };
        virtual void run_certain_length(testType_midCase) {

        };
        virtual void run_certain_length(testType_longCase) {

        };
};

#endif // __CONTAINER_TEST_RUNNER__