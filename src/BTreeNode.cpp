#include <iostream>
#include "BTreeNode.hpp"

template <class T>
BTreeNode<T>::BTreeNode (unsigned int ordem)
{
   this->ordem = ordem;
   this->chaves.resize(this->ordem);
   this->filhos.resize(this->ordem + 1, nullptr);
   this->numChaves = 0;
}

template <class T>
BTreeNode<T>::BTreeNode (unsigned int ordem, T chave)
{
   this->ordem = ordem;
   this->chaves.resize(this->ordem);
   this->filhos.resize(this->ordem + 1, nullptr);
   this->chaves[0] = chave;
   this->numChaves = 1;
}

//pre-cond: nó contem no minimo 1 chave e no maximo ORDEM-1 chaves
template <class T>
bool BTreeNode<T>::insert (unsigned int ordem, T chave) 
{
   int i; //posicao do vetor-chave ou vetor-filhos que a chave deve pertencer
   for (i = 0; i < this->numChaves && chave > this->chaves[i]; ++i) 
      {}

   //insere a chave na posicao correta do vetor
   if (this->isLeaf()) 
   {
      for (int j = this->numChaves; j > i ; --j)
         this->chaves[j] = this->chaves[j - 1];
         
      this->chaves[i] = chave;
      ++this->numChaves;
   }

   //overflow no No filhos
   else if (this->filhos[i]->insert(ordem, chave))
   {
      T mediano;
      int posOverflow = i; //index do filho q sofreu overflow
      BTreeNode<T> *novo = split(this->filhos[i], &mediano);

      //inserir o mediano na posicao correta
      for (i = 0; i < this->numChaves && mediano > this->chaves[i]; ++i)
      {}
      for (int j = this->numChaves; j > i ; --j)
         this->chaves[j] = this->chaves[j - 1];
      
      this->chaves[i] = mediano;
      ++this->numChaves;

      //inserir o novo No filho na posicao correta
      int j;
      for (j = this->numChaves; j > posOverflow + 1; --j)
         this->filhos[j] = this->filhos[j - 1];
      this->filhos[j] = novo;
   }

   //CASO OVERFLOW
   return this->overflow();
}

template <class T>
BTreeNode<T>* BTreeNode<T>::split (BTreeNode *&node, T *med)
{
   BTreeNode<T> *novo = new BTreeNode<T>(node->ordem);
   int posMed = node->numChaves / 2;
   
   int i, j, fim = node->numChaves;
   for (i = posMed + 1, j = 0; i < fim; ++i, ++j)
   {
      novo->filhos[j] = node->filhos[i];
      novo->chaves[j] = node->chaves[i];
      node->filhos[i] = nullptr;

      ++novo->numChaves;
      --node->numChaves;
   }
   novo->filhos[j] = node->filhos[i];
   node->filhos[i] = nullptr;
   *med = node->chaves[posMed];
   --node->numChaves;

   return novo;
}

template <class T>
void BTreeNode<T>::showInOrder () const
{ 
   int i; 
   for (i = 0; i < this->numChaves; i++) 
   {  
      if (!this->isLeaf()) 
         this->filhos[i]->showInOrder(); 
      std::cout << " " << this->chaves[i]; 
   } 

   if (!this->isLeaf()) 
      this->filhos[i]->showInOrder(); 
} 

template <class T>
void BTreeNode<T>::showByLevel () const
{ 
   int h = this->height();

   for (int i = 1; i <= h; ++i)
   { 
      showLevel(i);
      std::cout << "\n";
   }
}

template <class T>
void BTreeNode<T>::showLevel (int level) const
{ 
   if (level == 1) 
   {
      for (int i = 0; i < this->numChaves; ++i)
         std::cout << "[" << this->chaves[i] << "]";
      std::cout << "  ";
   }
   else if (level > 1) 
   { 
      for (int i = 0; i <= this->numChaves; ++i)
         this->filhos[i]->showLevel(level - 1);
   } 
}

template <class T>
int BTreeNode<T>::height () const
{
   return this->isLeaf() ? 1 : 1 + this->filhos[0]->height();
}

template <class T>
bool BTreeNode<T>::overflow () const
{
   return (this->numChaves == this->ordem);
}

template <class T>
bool BTreeNode<T>::isLeaf () const
{
   return (this->filhos[0] == nullptr);
}

template <class T>
BTreeNode<T>::~BTreeNode ()
{
   for (int i = 0; i <= this->numChaves; ++i)
      delete this->filhos[i];
}

template class BTreeNode<int>;