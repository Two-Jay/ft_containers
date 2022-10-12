#ifndef __FT_CONTAINERS_STACK__
#define __FT_CONTAINERS_STACK__

// #include <vector>
#include "vector.hpp"

namespace ft {
    template <class T, class Container = ft::vector<T> >
    class stack {
        public:
            typedef Container                                container_type;
            typedef typename container_type::value_type      value_type;
            typedef typename container_type::reference       reference;
            typedef typename container_type::const_reference const_reference;
            typedef typename container_type::size_type       size_type;

        protected:
            container_type c;

        public:
            explicit stack (const container_type& _ctnr = container_type()) {
                c = _ctnr;
            }

            bool
            empty() const {
                return c.empty();
            }

            size_type
            size() const {
                return c.size();
            }

            reference
            top() {
                return *c.rbegin();
            }

            const_reference 
            top() const {
                return *c.rbegin();
            }

            void
            push (const_reference _val) {
                c.push_back(_val);
            }
            
            void
            pop() {
                c.pop_back();
            }
    
            template <class _T, class _Container>
            friend bool operator==(const stack<T, Container>& __x, const stack<_T, _Container>& __y) {
                return __x.c == __y.c;
            }

            template <class _T, class _Container>
            friend bool operator!=(const stack<T, Container>& __x, const stack<_T, _Container>& __y) {
                return __x.c != __y.c;
            }

            template <class _T, class _Container>
            friend bool operator< (const stack<T, Container>& __x, const stack<_T, _Container>& __y) {
                return __x.c < __y.c;
            }

            template <class _T, class _Container>
            friend bool operator> (const stack<T, Container>& __x, const stack<_T, _Container>& __y) {
                return __x.c > __y.c;
            }

            template <class _T, class _Container>
            friend bool operator>=(const stack<T, Container>& __x, const stack<_T, _Container>& __y) {
                return __x.c >= __y.c;
            }

            template <class _T, class _Container>
            friend bool operator<=(const stack<T, Container>& __x, const stack<_T, _Container>& __y) {
                return __x.c <= __y.c;
            }

            template <class _T, class _Container>
            friend void swap(stack<_T, _Container>& __x, stack<_T, _Container>& __y) {
                __x.c.swap(__y.c);   
            }
    };
        
};

#endif // __FT_CONTAINERS_STACK__
