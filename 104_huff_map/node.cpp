#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  //WRITE ME!
  if(sym != NO_SYM){
    assert(left == NULL);
    assert(right == NULL);
    theMap.insert(std::pair<unsigned, BitString>(sym, b));
  }
  else{
    assert(left!=NULL);
    assert(right!=NULL);
    BitString b_left = b.plusZero();
    left->buildMap(b_left, theMap);
    BitString b_right = b.plusOne();
    right->buildMap(b_right, theMap);
  }
}

