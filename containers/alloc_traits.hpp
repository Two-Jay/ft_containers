#ifndef __ALLOC_TRAITS_HPP__
#define __ALLOC_TRAITS_HPP__

#include <limits>

namespace ft {
    template <class _Alloc>
    struct allocator_traits {
        public :
            typedef _Alloc                                                      allocator_type;
            typedef typename _Alloc::value_type                                 value_type;
            typedef typename _Alloc::pointer                                    pointer; // value_type*
            typedef typename _Alloc::const_pointer                              const_pointer; // std::pointer_traits<pointer>::rebind<const value_type>
            typedef typename _Alloc::void_pointer                               void_pointer; // std::pointer_traits<pointer>::rebind<void>
            typedef typename _Alloc::const_void_pointer                         const_void_pointer; //  std::pointer_traits<pointer>::rebind<const void>
            typedef typename _Alloc::difference_type                            difference_type; //  std::pointer_traits<pointer>::difference_type
            typedef typename _Alloc::size_type                                  size_type; // std::make_unsigned<difference_type>::type
            typedef typename _Alloc::propagate_on_container_copy_assignment     propagate_on_container_copy_assignment; // std::false_type
            typedef typename _Alloc::propagate_on_container_move_assignment     propagate_on_container_move_assignment; // std::false_type
            typedef typename _Alloc::propagate_on_container_swap                propagate_on_container_swap; // std::false_type
            typedef typename _Alloc::is_always_equal                            is_always_equal; // std::is_empty<_Alloc>::type

            static pointer allocate(allocator_type& __a, size_type __n) {
                return __a.allocate(__n * sizeof(__a.value_type));
            };

            static pointer allocate(allocator_type& __a, size_type __n, const_void_pointer hint) {
                return __a.allocate(__n * sizeof(__a.value_type), hint);
            };

            static void deallocate(allocator_type& __a, pointer __p, size_type __n) {
                __a.deallocate(__p, __n);
            };

            static size_type max_size(const allocator_type& __a) throw() {
                return (__a.max_size) ? __a.max_size() : std::numeric_limits<size_type>::max() / sizeof(value_type);
            }

            static allocator_type select_on_container_copy_construction(const allocator_type& __a) {
                allocator_type tmp = __a;
                return tmp;
            }

            template<class _T>
            static void construct(allocator_type& __a, pointer __p) {
                __a.construct(__p);
            }

            template<class _T>
            static void destroy(allocator_type& __a, pointer __p) {
                __a.destroy(__p);
            }
    };
}

#endif // __ALLOC_TRAITS_HPP__
