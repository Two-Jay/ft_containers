#ifndef __CONTAINER_TEST_RUNNER__
#define __CONTAINER_TEST_RUNNER__

#include "input_initiator.hpp"

struct testType_shortCase {};
struct testType_midCase {};
struct testType_longCase {};

class Container_test_runner {
    private :
        const Test_inputs& inputs;

    public :
        Container_test_runner() {};
        Container_test_runner(Test_inputs& inputs) {
            this->inputs = inputs;
        }
        virtual ~Container_test_runner() {};

        Container_test_runner& operator= (const Container_test_runner& rhs) {\
            if (this != &rhs) {
                this->inputs = rhs.get_inputs();
            }
            return *this;
        };
        Container_test_runner(const Container_test_runner& other) {
            this->inputs = other.get_inputs();
        };

        const Test_inputs& get_inputs(void) const {
            return this->inputs;
        }

        virtual void run_allcase(void) {
            run_certain_length(testType_shortCase());
            run_certain_length(testType_midCase());
            run_certain_length(testType_longCase());
        };
        virtual void run_certain_length(testType_shortCase) {};
        virtual void run_certain_length(testType_midCase) {};
        virtual void run_certain_length(testType_longCase) {};
};


class Test_runner_vector : public Container_test_runner {
    
    // 멤버편수로 컨테이너별 테스트 객체 생성
    // 멤버변수로 잡아둔 테스트 객체 내에서 In/output 관리하기
    private :

    public :
        Test_runner_vector() {};
        virtual ~Test_runner_vector() {};

};

#endif // __CONTAINER_TEST_RUNNER__