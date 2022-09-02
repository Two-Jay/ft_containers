#ifndef __CONTAINER_TEST_RUNNER__
#define __CONTAINER_TEST_RUNNER__

struct testType_shortCase {};
struct testType_midCase {};
struct testType_longCase {};

class Container_test_runner {
    private :
        
    public :
        Container_tester() {}; 
        ~Container_tester() {};
        Container_tester& operator= (const Container_tester& rhs) {
            ;
        };
        Container_tester(const Container_tester& other) {
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