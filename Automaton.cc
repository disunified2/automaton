#include "Automaton.h"

#include <cassert>
#include <iostream>
#include <list>
#include <ostream>

namespace fa {

  Automaton::Automaton() {
    this->symbols = {};
    this->states = {};
  }

  bool Automaton::isValid() const {
    return (countStates() != 0 && countSymbols() != 0);
  }



  bool Automaton::addSymbol(char symbol) {
    if (!isgraph(symbol)) {
      return false;
    }
    return symbols.insert(symbol).second;
  }

  bool Automaton::removeSymbol(char symbol) {
    if (symbols.find(symbol) == symbols.end()) {
      return false;
    }
    // Suppression de toute transition qui contient symbol
    for (auto it : states) {
      for (auto it2 : it.second.transitions) {
        for (auto it3 : it2.second) {
          removeTransition(it.first, symbol, it3.first);
        }
      }
    }
    return symbols.erase(symbol);
  }

  bool Automaton::hasSymbol(char symbol) const {
    return symbols.find(symbol) != symbols.end();
  }

  std::size_t Automaton::countSymbols() const {
    return symbols.size();
  }



  bool Automaton::addState(int state) {
    if (state < 0) {
      return false;
    }

    State st;
    st.state = state;
    st.isFinal = false;
    st.isInitial = false;
    st.transitions = {};

    if(!states.insert(std::pair<int, State>(state, st)).second) {
      return false;
    };
    return true;
  }

  bool Automaton::removeState(int state) {
    if (states.find(state) == states.end()) {
      return false;
    }
    for (auto it : states) {
      for (auto it2 : it.second.transitions) {
        for (auto it3 : it2.second) {
          removeTransition(it.first, it2.first, state);
        }
      }
    }
    return states.erase(state);
  }

  bool Automaton::hasState(int state) const {
    return states.find(state) != states.end();
  }

  std::size_t Automaton::countStates() const {
    return states.size();
  }

  void Automaton::setStateInitial(int state) {
    states.find(state)->second.isInitial = true;
  }

  bool Automaton::isStateInitial(int state) const {
    if (states.find(state) == states.end()) {
      return false;
    }
    return states.at(state).isInitial;
  }

  void Automaton::setStateFinal(int state) {
    states.find(state)->second.isFinal = true;
  }

  bool Automaton::isStateFinal(int state) const {
    if (states.find(state) == states.end()) {
      return false;
    }
    return states.at(state).isFinal;
  }



  bool Automaton::addTransition(int from, char alpha, int to) {
    if (!hasState(from) || !hasState(to) || (!hasSymbol(alpha) && alpha != fa::Epsilon)) {
      return false;
    }
    if (!states[from].transitions[alpha].insert(std::pair<int, State>(to, states[to])).second) {
      return false;
    }
    return true;
  }

  bool Automaton::removeTransition(int from, char alpha, int to) {
    if (!hasState(from) || !hasState(to) || (!hasSymbol(alpha) && alpha != fa::Epsilon)) {
      return false;
    }
    if (!hasTransition(from, alpha, to)) {
      return false;
    }
    states[from].transitions[alpha].erase(to);
    if (states[from].transitions[alpha].empty()) {
      states[from].transitions.erase(alpha);
    }
    return true;
  }

  bool Automaton::hasTransition(int from, char alpha, int to) const {
    if (!hasState(from) || !hasState(to) || (!hasSymbol(alpha) && alpha != fa::Epsilon)) {
      return false;
    }
    if (states.find(from)->second.transitions.find(alpha)->first != alpha) {
      return false;
    }
    if (states.find(from)->second.transitions.find(alpha)->second.find(to) == states.find(from)->second.transitions.find(alpha)->second.end()) {
      return false;
    }
    return true;
  }

  std::size_t Automaton::countTransitions() const {
    std::size_t nbTransitions = 0;
    for (auto it = states.begin(); it != states.end(); ++it) {
      for (auto it2 = it->second.transitions.begin(); it2 != it->second.transitions.end(); ++it2) {
        nbTransitions += it2->second.size();
      }
    }
    return nbTransitions;
  }

  void Automaton::prettyPrint(std::ostream &os) const {

  }

  bool Automaton::hasEpsilonTransition() const {
    return true;
  }

  bool Automaton::isDeterministic() const {
    return true;
  }

  bool Automaton::isComplete() const {
    return true;
  }

  std::set<int> Automaton::makeTransition(const std::set<int>& origin, char alpha) const {
    std::set<int> result;
    return result;
  }

  std::set<int> Automaton::readString(const std::string& word) const {
    std::set<int> result;
    return result;
  }

  bool Automaton::match(const std::string& word) const {
    return true;
  }

  void Automaton::removeNonAccessibleStates() {

  }

  void Automaton::removeNonCoAccessibleStates() {

  }

  bool Automaton::isLanguageEmpty() const {
    return true;
  }

  bool Automaton::hasEmptyIntersectionWith(const Automaton& other) const {
    return true;
  }

  bool Automaton::isIncludedIn(const Automaton& other) const {
    return true;
  }

  Automaton Automaton::createMirror(const Automaton& automaton) {
    return automaton;
  }

  Automaton Automaton::createComplete(const Automaton& automaton) {
    return automaton;
  }

  Automaton Automaton::createComplement(const Automaton& automaton) {
    return automaton;
  }

  Automaton Automaton::createIntersection(const Automaton& lhs, const Automaton& rhs) {
    return lhs;
  }

  Automaton Automaton::createDeterministic(const Automaton& other) {
    return other;
  }

  Automaton Automaton::createMinimalMoore(const Automaton& other) {
    return other;
  }

  Automaton Automaton::createMinimalBrzozowski(const Automaton& other) {
    return other;
  }
}

