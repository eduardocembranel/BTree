#include <iostream>
#include "BTree.hpp"

int main ()
{
   BTree<int> *r = new BTree<int>(5); //ordem 5 
   
   r->insert(2);
   r->insert(1);
   r->insert(6);
   r->insert(8);
   r->insert(4);
   r->insert(5);
   r->insert(10);
   r->insert(20);
   r->insert(30);
   r->insert(3);
   r->insert(70);
   r->insert(90);
   r->insert(43);
   r->insert(7);
   r->insert(11);
   r->insert(12);
   r->insert(15);
   r->insert(18);
   r->insert(19);
   r->insert(14);

   r->showByLevel();

   delete r;
   return 0;
}