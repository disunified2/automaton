#include "Automaton.h"


namespace fa {

  Automaton::Automaton() {
    this->symbols = {};
    this->states = {};
  }

  bool Automaton::isValid() const {
    return true;
  }


}

