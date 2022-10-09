#ifndef __FT_CONTAINERS_STACK__
#define __FT_CONTAINERS_STACK__

#include <vector>
// #include "vector.hpp"

namespace ft {
    template <class T, class _Container = std::vector<T> >
    class stack {
        private:
            typedef typename _Container::size_type	size_type;
            
            _Container _C;

        protected:
            size_type                   _size;

        public:
            
        
    };
}

#endif // __FT_CONTAINERS_STACK__
