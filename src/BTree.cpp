#include "BTree.hpp"

template <class T> 
BTree<T>::BTree(unsigned int ordem)
{
   this->ordem = ordem;
   this->root  = nullptr;
}

template <class T>
void BTree<T>::insert (T chave)
{
   if (this->root == nullptr)
   {
      this->root = new BTreeNode<T>(this->ordem, chave);
   }
   //overflow na raiz
   else if (root->insert(this->ordem, chave))
   {
      T mediano;
      BTreeNode<T> *novo     = this->root->split(this->root, &mediano);
      BTreeNode<T> *novaRaiz = new BTreeNode<T>(this->ordem, mediano);

      novaRaiz->filhos[0] = root;
      novaRaiz->filhos[1] = novo;
      this->root = novaRaiz;
   }
}

template <class T>
void BTree<T>::showInOrder () const
{
   if (root != nullptr)
      root->showInOrder();
}

template <class T>
void BTree<T>::showByLevel () const
{
   if (root != nullptr)
      root->showByLevel();
}

template <class T>
int BTree<T>::height () const
{
   if (root == nullptr)
      return 0;
   return root->height();
}

template <class T>
BTree<T>::~BTree ()
{
   delete root;
}

template class BTree<int>;