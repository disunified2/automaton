#include "Automaton.h"

#include <utility>


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
    // le symbole n'est pas dans l'automate
    if (symbols.find(symbol) == symbols.end()) {
      return false;
    }
    // parcours des transitions pour supprimer les transitions concernées
    for (const auto& state : states) { // Parcours des états
      for (const auto& transition : state.second.transitions) {
        for (auto state2 : transition.second) {
          removeTransition(state.first, symbol, state.first);
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

    return states.insert(std::pair<int, State>(state, st)).second;
  }

  bool Automaton::removeState(int state) {
    return true;
  }

  bool Automaton::hasState(int state) const {
    return states.find(state) != states.end();
  }

  std::size_t Automaton::countStates() const {
    return states.size();
  }

  void Automaton::setStateInitial(int state) {

  }

  bool Automaton::isStateInitial(int state) const {
    return true;
  }

  void Automaton::setStateFinal(int state) {

  }

  bool Automaton::isStateFinal(int state) const {
    return true;
  }

  bool Automaton::addTransition(int from, char alpha, int to) {
    return true;
  }

  bool Automaton::removeTransition(int from, char alpha, int to) {
    return true;
  }

  bool Automaton::hasTransition(int from, char alpha, int to) const {
    return true;
  }

  std::size_t Automaton::countTransitions() const {
    return 0;
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

