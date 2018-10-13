#ifndef BTREENODE_HPP
#define BTREENODE_HPP

#include <vector>
#include "BTree.hpp"

//Representa os Nos da arvore B
//Classe totalmente privada, acessivel apenas atraves
//dos metodos da classe friend BTree
template<class T>
class BTreeNode
{
   template<class U>
   friend class BTree;

   private:
      int numChaves;
      int ordem;
      std::vector<T> chaves;
      std::vector<BTreeNode*> filhos;
   
      BTreeNode (unsigned int);
      BTreeNode (unsigned int, T);
      bool insert (unsigned int, T);
      BTreeNode* split (BTreeNode*&, T*);
      void showInOrder () const;
      void showByLevel () const;
      void showLevel (int) const;
      int height () const;
      bool overflow () const;
      bool isLeaf () const;
      ~BTreeNode ();
};


#endif //!BTREENODE_HPP