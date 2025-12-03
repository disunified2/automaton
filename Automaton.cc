#include "Automaton.h"

#include <cassert>
#include <iostream>
#include <list>
#include <ostream>
#include <stack>
#include <vector>
#include <queue>

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
          removeTransition(it.first, symbol, states.find(it3)->first);
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
        removeTransition(it.first, it2.first, state);
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
    if (!states[from].transitions[alpha].insert(to).second) {
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
    auto& temp = states[from].transitions[alpha];
    temp.erase(to);
    if (temp.empty()) {
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
    os << "Initial states :" << std::endl;
    for (const auto& state : states) {
      if (state.second.isInitial) {
        os << "\t" << state.first << " " << std::endl;
      }
    }
    os << "Final states :" << std::endl;
    for (const auto& state : states) {
      if (state.second.isFinal) {
        os << "\t" << state.first << " " << std::endl;
      }
    }

    os << "Transitions :" << std::endl;
    for (const auto& state : states) {
      os << "\tFor state " << state.first << " :" << std::endl;
      for (const auto symbol : symbols) {
        os << "\t\tFor letter " << symbol << " : ";
        for (const auto& state2 : states) {
          if (hasTransition(state.first, symbol, state2.first)) {
            os << state2.first << " ";
          }
        }
        os << std::endl;
      }
    }
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
        std::set<int> arrival_states = states.find(it)->second.transitions.find(alpha)->second;
        for (const int it2 : arrival_states) {
          result.insert(it2);
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
            if (return_ && states.at(it2).isFinal) {
              return true;
            }
            stack.push(it2);
          }
        }
      }
    }
    return false;
  }

  void Automaton::removeNonAccessibleStates() {
    std::unordered_set<int> visited;
    // add all accessible states to the visited set
    for (const auto& state : states) {
      if (state.second.isInitial) {
        depthFirstSearch(state.first, visited, false);
      }
    }

    if (visited.size() == states.size()) {
      return; // all states are accessible
    }

    // removing all states that aren't accessible
    std::vector<int> states_to_remove;
    for (const auto& state : states) {
      if (visited.find(state.first) == visited.end()) {
        states_to_remove.push_back(state.first);
      }
    }
    for (auto state : states_to_remove) {
      removeState(state);
    }

    if (states.empty()) {
      addState(0);
      setStateInitial(0);
    }
  }

  void Automaton::removeNonCoAccessibleStates() {
    std::vector<int> states_to_remove;
    for (const auto& state : states) {
      std::unordered_set<int> visited;
      if(!depthFirstSearch(state.first, visited, true)) {
        if (!state.second.isFinal) {
          states_to_remove.push_back(state.first);
        }
      }
    }

    for (auto state : states_to_remove) {
      removeState(state);
    }

    if (states.empty()) {
      addState(0);
    }
  }

  bool Automaton::isLanguageEmpty() const {
    std::unordered_set<int> visited;
    for (const auto& state : states) {
      if (state.second.isInitial) {
        if (depthFirstSearch(state.first, visited, true)) {
          return false;
        }
      }
    }
    return true;
  }

  bool Automaton::hasEmptyIntersectionWith(const Automaton& other) const {
    Automaton intersection = createIntersection(*this, other);
    return intersection.isLanguageEmpty();
  }

  bool Automaton::isIncludedIn(const Automaton& other) const {
    if (isLanguageEmpty()) {
      return true;
    }
    for (const auto& symbol : symbols) {
      if (other.symbols.find(symbol) == other.symbols.end()) {
        return false;
      }
    }
    Automaton complement = other;
    // complement = createDeterministic(complement);
    complement = createComplement(complement);
    return hasEmptyIntersectionWith(complement);
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
          mirror.addTransition(state2, symbol.first, state.first);
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

    int sinkState = -1;

    // Attempt to find a sink state in the automaton
    for (const auto& state : automaton.states) {
      // sink state has been found in condition that it has no exiting transitions
      if (!state.second.isFinal) {
        if (state.second.transitions.empty()) {
        sinkState = state.first;
        break;
        }
        for (const auto& symbol : state.second.transitions) {
          for (int arrivalState : symbol.second) {
            if (arrivalState == sinkState) {
              sinkState = state.first;
            } else {
              sinkState = -1;
            }
          }
        }
      }

    }

    if (sinkState == -1) {
      // creation of the sink state
      sinkState = static_cast<int>(automaton.countStates()) + 1;
      while(complete.hasState(sinkState)) {
        ++sinkState;
      }
    }
    // Adding missing transitions to self to make automaton complete
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

  Automaton Automaton::createComplement(const Automaton& automaton) {
    Automaton complement = automaton;
    complement = createDeterministic(complement);
    complement = createComplete(complement);

    for (const auto& state : complement.states) {
      complement.states.at(state.first).isFinal = !complement.states.at(state.first).isFinal;
    }

    return complement;
  }



  Automaton Automaton::createIntersection(const Automaton& lhs, const Automaton& rhs) {
    // the goal is to go through both automats at the same time synchronously
    // the challenge is to find a way of saving the visited states into a pair -> map of pairs
    Automaton intersection;

    // Symbols
    std::unordered_set<char> shared_symbols;
    for (const char symbol : lhs.symbols) {
      if (rhs.hasSymbol(symbol)) {
        shared_symbols.insert(symbol);
      }
    }
    // for (const char symbol : rhs.symbols) {
    //   shared_symbols.insert(symbol);
    // }
    if (shared_symbols.empty()) {
      intersection.addState(0);
      intersection.addSymbol('a');
      return intersection;
    }

    intersection.symbols.insert(shared_symbols.begin(), shared_symbols.end());

    // States

    std::map<std::pair<int, int>, int> pairs;
    std::queue<std::pair<int, int>> queue;
    int stateID = 0;

    // going through both automats to find the initial pairs
    for (const auto& l_state : lhs.states) {
      if (l_state.second.isInitial) {
        for (const auto& r_state : rhs.states) {
          if (r_state.second.isInitial) {

            // Creating the pair that will become one single state in result automat
            auto newPair = std::make_pair(l_state.first, r_state.first);

            // Checking to see if its not already in our pairs map
            if (pairs.find(newPair) == pairs.end()) {
              // Add to the list of pairs
              pairs[newPair] = stateID++;

              // inserting new pair into result
              intersection.addState(pairs[newPair]);
              intersection.setStateInitial(pairs[newPair]);

              if (l_state.second.isFinal && r_state.second.isFinal) {
                intersection.setStateFinal(pairs[newPair]);
              }

              // Add the pair to the queue for makeTransition after
              queue.push(newPair);
            }
          }
        }
      }
    }

    // Case where there is no initial pairs
    if (pairs.empty()) {
      intersection.addState(0);
      return intersection;
    }

    // Go through the queue to add all transitions between the initial states and the others
    while (!queue.empty()) {
      auto statePair = queue.front();
      queue.pop();
      int currentStateID = pairs[statePair];

      // Go through the common symbols
      for (char symbol : intersection.symbols) {
        std::set<int> l_states = lhs.makeTransition({statePair.first}, symbol);
        std::set<int> r_states = rhs.makeTransition({statePair.second}, symbol);

        // Like above, create the pairs with what is obtained
        for (int l_state : l_states) {
          for (int r_state : r_states) {
            auto newPair = std::make_pair(l_state, r_state);
            if (pairs.find(newPair) == pairs.end()) {
              pairs[newPair] = stateID++;

              intersection.addState(pairs[newPair]);

              if (lhs.isStateFinal(l_state) && rhs.isStateFinal(r_state)) {
                intersection.setStateFinal(pairs[newPair]);
              }

              queue.push(newPair);
            }

            // Add the transition between the current pair and the new found pair
            intersection.addTransition(currentStateID, symbol, pairs[newPair]);
          }
        }
      }
    }

    return intersection;
  }

  Automaton Automaton::createDeterministic(const Automaton& other) {
    Automaton deterministic;

    for (const char symbol : other.symbols) {
      deterministic.addSymbol(symbol);
    }

    if (other.isLanguageEmpty()) {
      deterministic.addState(0);
      deterministic.setStateInitial(0);
      return deterministic;
    }

    std::map<std::set<int>, int> det_states;
    int state_ID = 0;
    std::queue<std::set<int>> queue;

    std::set<int> initials;
    // Add the initial states into the states to add
    for (const auto& state : other.states) {
      if (state.second.isInitial) {
        initials.insert(state.first);
      }
    }
    queue.push(initials);
    det_states[initials] = state_ID++;
    deterministic.addState(det_states[initials]);
    deterministic.setStateInitial(det_states[initials]);

    while (!queue.empty()) {
      auto current_set = queue.front();
      queue.pop();

      for (char symbol : other.symbols) {
        // Find the next states from the current ones
        std::set<int> next_set = other.makeTransition(current_set, symbol);
        // There are no transitions with this symbol
        if (next_set.empty()) {
          continue;
        }

        // If the new set is not in the deterministic states, then add it
        if (det_states.find(next_set) == det_states.end()) {
          det_states[next_set] = state_ID++;
          queue.push(next_set);
          deterministic.addState(det_states[next_set]);
        }

        // Add the transition in the deterministic automat
        deterministic.addTransition(det_states[current_set], symbol, det_states[next_set]);
      }
    }

    // Find the final states
    for (auto& set : det_states) {
      for (int state : set.first) {
        if (other.isStateFinal(state)) {
         deterministic.setStateFinal(det_states[set.first]);
          break;
        }
      }
    }

    return deterministic;
  }



  Automaton Automaton::createMinimalMoore(const Automaton& other) {
    Automaton CD = other;
    CD.removeNonAccessibleStates();
    CD = createDeterministic(CD);
    CD = createComplete(CD);

    // Create initial partition (final : class 1, other : class 0)
    std::map<int, int> classes;
    for (auto& state : CD.states) {
      classes[state.first] = CD.isStateFinal(state.first) ? 1 : 0;
    }

    bool changed = true;

    while (changed) {
      changed = false;
      std::map<int, std::vector<int>> signatures;
      std::map<std::vector<int>, int> classIDs;
      int nextClassID = 0;

      for (auto& state : CD.states) {
        std::vector<int> signature;

        for (auto& symbol : state.second.transitions) { // possible because minimal is complete and deterministic
          int dest = *symbol.second.begin();
          signature.push_back(classes[dest]);
        }

        signature.push_back(CD.isStateFinal(state.first) ? 1 : 0);
        signatures[state.first] = signature;
      }

      std::map<int, int> newClasses;
      for (auto& signature : signatures) {
        if (!classIDs.count(signature.second)) {
          classIDs[signature.second] = nextClassID++;
        }
        newClasses[signature.first] = classIDs[signature.second];
      }

      // Check to see if new iteration is different from previous
      if (newClasses != classes) {
        classes = newClasses;
        changed = true;
      }
    }

    Automaton minimal;

    // Add the symbols to new automat
    for (char symbol : other.symbols) {
      minimal.addSymbol(symbol);
    }

    // Clean up the classes
    std::map<int, int> newStates;
    for (auto& state : classes) {
      if (!newStates.count(state.second)) {
        newStates[state.second] = state.first;
      }
    }

    // Create the new states
    for (auto& state : newStates) {
      minimal.addState(state.first);
      // Check if the old state was initial
      if (CD.isStateInitial(state.second)) {
        minimal.setStateInitial(state.first);
      }
      // Check if the old state was final
      if (CD.isStateFinal(state.second)) {
        minimal.setStateFinal(state.first);
      }
    }

    // Create the transitions
    for (auto& state_pairs : newStates) {
      State &s = minimal.states[state_pairs.first];
      const State &oldState = CD.states.at(state_pairs.second);

      for (char symbol : minimal.symbols) {
        int oldDest = *oldState.transitions.at(symbol).begin();
        int newDest = classes[oldDest];
        minimal.addTransition(s.state, symbol, newDest);
      }
    }

    return minimal;
  }

  Automaton Automaton::createMinimalBrzozowski(const Automaton& other) {
    Automaton minimal = other;
    minimal.removeNonAccessibleStates();

    minimal = createMirror(minimal);
    minimal = createDeterministic(minimal);

    minimal = createMirror(minimal);
    minimal = createDeterministic(minimal);

    minimal = createComplete(minimal);

    return minimal;
  }
}

