#include<new>
#include<utility>
#include<cassert>
#include "rbtress.hpp"
#include "lib::optional.hpp"

template<typename T>
class rb_tree{
  using node = rb_node<T>* root;
  node* root = nullptr;
  node root;
  
#if 0
 LEFT ROTATION (rotate at x)

BEFORE                     AFTER
  root                          y
     \                         / \
      y            ==>     root   γ
     / \                           \
    β   γ                           β

What moved:
- y moves up (becomes parent)
- x moves down to the left
- β moves from y->left to root->right
#endif

  node rotate_left(node root)noexcept{
    node y = root->right;
    if(!y)return nullptr;
    node beta = y->left;
    root->right = beta;
    if(beta)beta->parent = root;
    if(root->parent){ 
      y->parent = nullptr;
      y->left = root;
      x->parent = y;
    }else{
      node p = root->parent;
      y->parent = root->parent;
      if(p->left == x){
        p->left = y;
      }else{
        p->right = y;
      }
      root->parent = y;
    }
  }

#if 0

RIGHT ROTATION (rotate at y)

BEFORE                     AFTER
      root                       x
       /                        / \
      x            ==>         α  root 
     / \                          /
    α   β                         β

What moved:
- x moves up (becomes parent)
- y moves down to the right
- β moves from x->right to y->left    

#endif 

  node rotate_right(node root)noexcept{
    node y = root->left;
    if(!y)return nullptr;
    node beta = y->right;
    if(beta)beta->parent = root;
    root->left = beta;
    if(root->parent == nullptr){
      y->parent = nullptr;
      y->right = root;
    }else{
      node p = root->parent;
      y->parent = p;
      y->right = root;
      p->left == root?p->left = y:p->right = y;
    }
    root->parent = y;
    return y;
  } 
}
