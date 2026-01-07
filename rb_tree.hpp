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
    if(!root->parent){ 
      y->parent = nullptr;
      y->left = root;
    }else{
      node p = root->parent;
      y->parent = p;
      y->left = root;
      if(p->left == root){
        p->left = y;
      }else{
        p->right = y;
      }
    }
    root->parent = y;
    return y;
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

  node successor(node )noexcept{
          
   }  
  void rb_insert(T value)noexcept{
    node current = new node(value);
    current.color = red;
    node p = nullptr;
    while(root != nullptr){
      p = root;
      if(current->value > root->value){
        root = root->left;
      }else{
        root = root->right;
      }
    }
    current->parent = p;
    if(p == nullptr)root = current;
    if(root->value < current->value)root->right = current;
    else{root->left = current;}

#if 0

Case 1) Uncle is red
  change the colors of parent, uncle,grandfather
  fix up from grandfather to root ---> line 123 - 126

#endif

    if(current->color == red && p->color == red){
      node->grand = p->parent;
      p->parent = gg;
      if(grand){
        node uncle = (grand->left == p)?grand->right:grand->left;
      }
      if(uncle && uncle->color == red){
        uncle->color = black;
        p->color = red;
        grad->color = red;
        while(gg && gg->color == red){
          gg->color = black;
          gg = gg->parent;
        }
      }

#if 0
Case 2) uncle is black
  4 Condition
  a)left-left  right_rotate, swap
  b)left-right left_rotate, right_rotate, swap
  c)right->right left_rotate, swap
  d)right->left right_rotate, left_rotate, swap
#endif

      if(uncle && uncle->color == black){
        if(p->left == current && gg->left == p){
          this->right_rotate(gg);
          std::swap(gg->color,p->color);
        }else if(gg->left == p && p->right == p){
          this->left_rotate(p);
          this->right_rotate(current);
          std::swap(current->color,gg->color);
        }else if(p->right == current && gg->right == current){
          this->left_rotate(gg);
          std::swap(p->color, gg->color);
        }else{
          this->right_rotate(p);
          this->left_rotate(gg);
          std::swap(gg->color,current->color);
        }
      }
    }
    
#if 0
tranlate(x, y) ------> take subtree starting from y and replace with x and delete x; 

Case 1) x is left child
Case 2) x is right child

#endif
    node* nb_translate(node x, node y)noexcept{      
      y->parent = x->parent;

      if(x->parent->left == x){
        x->parent->left = y;
        if(y->parent->left == y){
          y->parent->left = nullptr;
        }else{
          y->parent->right = nullptr;
        }
      }else{
        x->parent->right = y;
        if(y->parent->left == y){
          y->parent->left = nullptr;
        }else{
          y->parent->right = nullptr;
        }
      }
      delete x;
      return y;
    }

    node* rb_find(T value){
      node current = new node(value);
      if(current->value == root->value){return current;}
      while(current != nullptr){
        if(current->value < root->value){
          current = current->left;
          root = root->left;
        }else{
          current = current->right;
          root = root->right;
        }
      } 
      return nullptr;
    }

    void rb_delete(T del_node)noexc::ept{
      node current = find(del_node);
      if(!current)return;
      if(current->color == red){
        if(!current->left && !current->right){
          delete current ;
          current->parent = nullptr;
          return;
        }else if(current->left && !current->right){
          current->left->parent = current->parent;
          current->left = nullptr;
          delete current;
          return;
        }else if(!current->left && current->right){
          current->right->parent = current->parent;
          current->right = nullptr;
          delete current;
        }else{
          current = current->right;
          node succ = current;
          while(succ->left){
            current = current->left;
          }
i
          this->rb_translate()
          node temp = current;
        }
      }else{

      }

      }
    }
    
  }

};
