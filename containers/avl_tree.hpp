#ifndef __FT_CONTAINERS_AVL_TREE__
#define __FT_CONTAINERS_AVL_TREE__

#include <memory>

namespace {

    template <class _Tp, class _Alloc = std::allocator<_Tp> >
    class avl_tree {

        public:
            typedef _Tp                         value_type;
            typedef _Alloc                      allocator_type;
            typedef value_type*                 pointer;
            typedef const value_type*           const_pointer;
            typedef value_type&                 reference;
            typedef const value_type&           const_reference;
            typedef size_t                      size_type;
            typedef ptrdiff_t                   difference_type;

        protected:
            size_type           _size;
            allocator_type      _node_allocator;
            pointer             _headp;

        public:
            avl_tree() {}

            ~avl_tree() {}

            void insert(const_reference) {};

            void pop() {};

            bool empty() const { return this->size() == 0 ? false : true; }

            size_type size() const { return 0; }

        private:
            bool condition(_Tp __input, _Tp __x) { return __input < __x; }
    };
}

#endif // __FT_CONTAINERS_AVL_TREE__