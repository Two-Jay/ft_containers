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
    class _RBT_node {
        public :
            typedef _T                                   value_type;
            typedef _T*                                  value_pointer;
            typedef _T&                                  value_reference;
            typedef _RBT_node<_T>                     node_value_type;
            typedef _RBT_node<_T>*                    node_pointer;
            typedef _RBT_node<_T>&                    node_reference;                                          
        
        private :
            value_type                              _data;
            node_pointer                            _parent;
            node_pointer                            _left_child;
            node_pointer                            _right_child;
            color_Node_RB_tree                      _color;
            bool                                    _isLastNode;
            bool                                    _isNull;

        public :
            _RBT_node(value_type data = value_type(),
                        node_pointer parent = NULL,
                        node_pointer left_child = NULL,
                        node_pointer right_child = NULL,
                        color_Node_RB_tree color = RED,
                        bool isLastNode = false)
                    : _data(data), _parent(parent), _left_child(left_child), _right_child(right_child),
                    _color(color), _isLastNode(isLastNode), _isNull(data == NULL ? true : false) {};

            void
            set_data(value_reference data) {
                this->_data = data;
            };

            void
            set_parent(node_pointer __nptr) {
                this->_parent = __nptr;
            };

            void
            set_left_child(node_pointer __nptr) {
                this->_left_child = __nptr;
            };
            
            void
            set_right_child(node_pointer __nptr) {
                this->_right_child = __nptr;
            };

            value_reference
            get_data(void) {
                return this->_data;
            }

            node_pointer
            get_parent(void) {
                return this->_parent;
            };
            
            node_pointer
            get_left_child(void) {
                return this->_left_child;
            };
            
            node_pointer
            get_right_child(void) {
                return this->_right_child;
            };

            node_pointer
            get_grandparent(void) {
                node_pointer __nptr = this->get_parent();
                return __nptr != NULL ? __nptr->get_parent() : NULL;
            }

            node_pointer
            get_uncle(void) {
                node_pointer __nptr = this->get_grandparent();
                if (__nptr) {
                    return __nptr->get_left_child() == this->get_parent() ? __nptr->get_right_child() : __nptr->get_left_child();
                }
                return NULL;
            }

            color_Node_RB_tree
            get_color(void) {
                return this->_color;
            };

            void
            change_color(void) {
                this->_color = this->_color == RED ? BLACK : RED;
            };
    };

    template <class _T, class _Alloc = std::allocator<_T> >
    class NodeFactory_RB_tree {
        public :
            typedef _T                          value_type;
            typedef _T*                         value_pointer;
            typedef _T&                         value_reference;
            typedef size_t                      size_type;
            typedef _RBT_node<_T>               node_type;
            typedef node_type*                  node_pointer;
            typedef color_Node_RB_tree          color_type;
            typedef _Alloc                      allocator_type;

        public :
            NodeFactory_RB_tree() {};

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
                    __nptr = this->get_allocator().allocate(1);
                    this->get_allocator().construct(__nptr, __data);
                } catch (std::bad_alloc) {
                    exit(ERROR_ALLOCATE_MEMORY);
                }
                return __nptr;
            }

            template<class _U>
            node_pointer
            make_nill_node(void) {
                node_pointer __nptr = NULL;
                try {
                    __nptr = this->get_allocator().allocate(1);
                } catch (std::bad_alloc) {
                    exit(ERROR_ALLOCATE_MEMORY);
                }
                return __nptr;
            }

        private :
            allocator_type                      _allocator;
    };

    template <class _T, class _Alloc = std::allocator<_T> >
    class RB_tree {
        public :
            typedef _T                              value_type;
            typedef _T*                             value_pointer;
            typedef _T&                             value_reference;
            typedef _Alloc                          allocator_type;
            typedef size_t                          size_type;

        protected :
            typedef _RBT_node<_T>                           node_type;
            typedef node_type*                              node_pointer;
            typedef node_type&                              node_reference;
            typedef color_Node_RB_tree                      color_type;
            typedef NodeFactory_RB_tree<_T, _Alloc>         factory_type;

        private :
            size_type                               _size;
            factory_type                            _factory;
    
    };
}

#endif // __FT_CONTAINERS__RB_TREE__
