#ifndef __FT_CONTAINERS__NULL_PTR__
#define __FT_CONTAINERS__NULL_PTR__

namespace ft {

    const class nullptr_t {
        public :
            template <typename _T>
            operator _T*() const { return 0; }

            template <typename _T, typename _U>
            operator _T _U::*() const { return 0; }

        private :
            void operator&() const;
    } nullptr_t = {};
}

#endif // __FT_CONTAINERS__NULL_PTR__
