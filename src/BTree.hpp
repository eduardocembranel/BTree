#ifndef BTREE_HPP
#define BTREE_HPP

#include "BTreeNode.hpp"

template <class T>
class BTreeNode;

template <class T>
class BTree
{
   private:
      BTreeNode<T> *root;
      int ordem;
   
   public:
      BTree (unsigned int);
      void insert (T);
      void showInOrder () const; //ordem crescente
      void showByLevel () const; //por nivel
      int  height () const;
      ~BTree ();
};

#endif //!BTREE_HPP