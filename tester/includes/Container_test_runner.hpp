#ifndef __CONTAINER_TEST_RUNNER__
#define __CONTAINER_TEST_RUNNER__

#include "input_initiator.hpp"

struct testType_shortCase {};
struct testType_midCase {};
struct testType_longCase {};

class Container_test_runner {
    private :
        const Test_inputs& inputs;
        Container_test_runner() {};    
    public :
        Container_test_runner(Test_inputs& inputs) {
            this.inputs = inputs;
        }
        virtual ~Container_test_runner() {};
        Container_test_runner& operator= (const Container_test_runner& rhs) {
            ;
        };
        Container_test_runner(const Container_test_runner& other) {
            return *this;
        };

        virtual void run_allcase(void) {
            run_certain_length(testType_shortCase());
            run_certain_length(testType_midCase());
            run_certain_length(testType_longCase());
        };
        virtual void run_certain_length(testType_shortCase) {};
        virtual void run_certain_length(testType_midCase) {};
        virtual void run_certain_length(testType_longCase) {};
};

#endif // __CONTAINER_TEST_RUNNER__