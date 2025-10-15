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
    for (const auto& state : states) {
      for (const auto& symbol : state.second.transitions) {
        if (symbol.first == fa::Epsilon) {
          return true;
        }
      }
    }
    return false;
  }

  bool Automaton::isDeterministic() const {
    if (hasEpsilonTransition()) {
      return false;
    }

    size_t initial = 0;
    for (const auto& state : states) {
      if (state.second.isInitial) {
        ++initial;
      }
      for (const auto& symbol : state.second.transitions) {
        if (symbol.second.size() != 1) {
          return false;
        }
      }
    }
    if (initial != 1) {
      return false;
    }

    return true;
  }

  bool Automaton::isComplete() const {
    if (hasEpsilonTransition()) {
      return false;
    }
    for (const auto& state : states) {
      if (state.second.transitions.size() != countSymbols()) {
        return false;
      }
    }
    return true;
  }



  std::set<int> Automaton::makeTransition(const std::set<int>& origin, char alpha) const {
    // The returned set is the set of states that are present with hasTransition(origin[i], alpha, state)
    std::set<int> result;

    for (auto it : origin) {
      if (hasState(it) && states.find(it)->second.transitions.find(alpha) != states.find(it)->second.transitions.end()) {
        std::map<int, State> arrival_states = states.find(it)->second.transitions.find(alpha)->second;
        for (const auto& it2 : arrival_states) {
          result.insert(it2.first);
        }
      }
    }

    return result;
  }

  std::set<int> Automaton::readString(const std::string& word) const {
    // The returned set is the set of states gone through to read the word
    std::set<int> result;

    for (const auto& it : states) {
      if (isStateInitial(it.first)) {
        result.insert(it.first);
      }
    }
    for (char i : word) {
      result = makeTransition(result, i);
    }
    return result;
  }

  bool Automaton::match(const std::string& word) const {
    const std::set<int> result_states = readString(word);
    for (int it : result_states) {
      if (states.find(it)->second.isFinal) {
        return true;
      }
    }
    return false;
  }



  /*
   * initial : initial state from which to start the search
   * visited : unordered set of visited states
   * return_ : choose whether to return a boolean or not
   */
  bool Automaton::depthFirstSearch(const int& initial, std::unordered_set<int>& visited, bool return_) const {
    std::stack<int> stack;
    stack.push(initial);
    while (!stack.empty()) {
      int current = stack.top();
      stack.pop();
      if (visited.find(current) == visited.end()) {
        visited.insert(current);
        for (const auto& it : states.find(current)->second.transitions) {
          for (const auto& it2 : it.second) {
            if (return_ && it2.second.isFinal) {
              return true;
            }
            stack.push(it2.first);
          }
        }
      }
    }
    return false;
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
    fa::Automaton mirror;

    // Add the states to mirror and invert the states
    for (auto& state : automaton.states) {
      mirror.addState(state.first);
      if (state.second.isInitial) {
        mirror.setStateFinal(state.first);
      }
      if (state.second.isFinal) {
        mirror.setStateInitial(state.first);
      }
    }

    // Add the symbols to mirror
    for (auto& symbol : automaton.symbols) {
      mirror.addSymbol(symbol);
    }

    // Add the transitions to mirror
    for (auto& state : automaton.states) {
      for (auto& symbol : state.second.transitions) {
        for (auto& state2 : symbol.second) {
          mirror.addTransition(state2.first, symbol.first, state.first);
        }
      }
    }
    return mirror;
  }

  Automaton Automaton::createComplete(const Automaton& automaton) {
    if (automaton.isComplete()) {
      return automaton;
    }

    fa::Automaton complete = automaton;

    // creation of the sink state
    int sinkState = static_cast<int>(automaton.countStates()) + 1;
    while(complete.hasState(sinkState)) {
      ++sinkState;
    }
    complete.addState(sinkState);
    for (const char symbol : automaton.symbols) {
      complete.addTransition(sinkState, symbol, sinkState);
    }

    for (auto& state : complete.states) {
      if (state.second.transitions.size() != complete.symbols.size()) {
        for (auto& symbol : complete.symbols) {
          if (state.second.transitions.find(symbol) == state.second.transitions.end()) {
            complete.addTransition(state.first, symbol, sinkState);
          }
        }
      }
    }
    return complete;
  }

  // TODO : function is not complete and does not recognise complement language
  Automaton Automaton::createComplement(const Automaton& automaton) {
    fa::Automaton complement = automaton;
    complement = createDeterministic(automaton);
    complement = createComplete(complement);

    for (auto& state : complement.states) {
      state.second.isFinal = !state.second.isFinal;
    }

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

