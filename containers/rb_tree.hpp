#ifndef __FT_CONTAINERS__RB_TREE__
#define __FT_CONTAINERS__RB_TREE__

#include "./pair.hpp"
#include <memory>

#define ERROR_ALLOCATE_MEMORY 134

enum color_Node_RB_tree {
    RED,
    BLACK
};

namespace ft {
    template <class _T>
    class Node_RB_tree {
        public :
            typedef _T                                   value_type;
            typedef _T*                                  value_pointer;
            typedef _T&                                  value_reference;
            typedef Node_RB_tree<_T>                     node_value_type;
            typedef Node_RB_tree<_T>*                    node_pointer;
            typedef Node_RB_tree<_T>&                    node_reference;                                          
        
            value_type                              data;
            node_pointer                            grandpa_node;
            node_pointer                            left_child;
            node_pointer                            right_child;
            color_Node_RB_tree                      color;

        public :
            Node_RB_tree() : color(RED) {};
            
            explicit Node_RB_tree(value_reference data) : data(data), grandpa_node(NULL), left_child(NULL), right_child(NULL), color(RED) {};

            void
            set_data(value_reference data) {
                this->data = data;
            };

            void
            set_grandpa_node(node_pointer __nptr) {
                this->grandpa_node = __nptr;
            };

            void
            set_left_child(node_pointer __nptr) {
                this->left_child = __nptr;
            };
            
            void
            set_right_child(node_pointer __nptr) {
                this->right_child = __nptr;
            };

            value_reference
            get_data(void) {
                return this->data;
            }

            node_pointer
            get_grandpa(void) {
                return this->grandpa_node;
            };
            
            node_pointer
            get_left_child(void) {
                return this->left_child;
            };
            
            node_pointer
            get_right_child(void) {
                return this->right_child;
            };

            color_Node_RB_tree
            get_color(void) {
                return this->color;
            };

            void
            change_color(void) {
                this->color = this->color == RED ? BLACK : RED;
            };
    };

    template <class _T, class _Alloc>
    class NodeFactory_RB_tree {
        public :
            typedef _T                          value_type;
            typedef _T*                         value_pointer;
            typedef _T&                         value_reference;
            typedef size_t                      size_type;
            typedef Node_RB_tree<_T>            node_type;
            typedef node_type*                  node_pointer;
            typedef color_Node_RB_tree          color_type;
            typedef _Alloc                      allocator_type;

        private :
            allocator_type                      _allocator;

            explicit NodeFactory_RB_tree(const allocator_type& __a) : _allocator(__a) {};

            allocator_type
            inline get_allocator(void) {
                return this->_allocator;
            };

            size_type
            inline get_maxsize(void) {
                return this->_allocator.max_size();
            };

            template<class _U>
            node_pointer
            make_node(_U __data) {
                node_pointer __nptr = NULL;
                try {
                    __nptr = this->get_allocator.allocate(1);
                    this->get_allocator.construct(__nptr, __data);                    
                } catch (std::bad_alloc) {
                    exit(ERROR_ALLOCATE_MEMORY);
                }
                return __nptr;
            }
    };

    // template <class _T, class _Alloc = std::allocator<_T> >
    // class RB_tree {
    //     public :
    //         typedef _T                              value_type;
    //         typedef _T*                             value_pointer;
    //         typedef _T&                             value_reference;
    //         typedef _Alloc                          allocator_type;
    //         typedef size_t                          size_type;

    //     protected :
    //         typedef typename Node_RB_tree<_T>       node_type;
    //         typedef node_type*                      node_pointer;
    //         typedef node_type&                      node_reference;
    //         typedef typename color_Node_RB_tree     color_type;
    //         typedef typename NodeFactory_RB_tree    factory_type;

    //     private :
    //         size_type                               _size;
    //         factory_type                            _factory;
    

    // };
}

#endif // __FT_CONTAINERS__RB_TREE__
