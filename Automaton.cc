#include "Automaton.h"


namespace fa {

  Automaton::Automaton() {
    this->symbols = {};
    this->states = {};
  }

  bool Automaton::isValid() const {
    return true;
  }

  bool Automaton::addSymbol(char symbol) {
    return true;
  }

  bool Automaton::removeSymbol(char symbol) {
    return true;
  }

  bool Automaton::hasSymbol(char symbol) const {
    return true;
  }

  std::size_t Automaton::countSymbols() const {
    return 0;
  }

  bool Automaton::addState(int state) {
    return true;
  }

  bool Automaton::removeState(int state) {
    return true;
  }

  bool Automaton::hasState(int state) const {
    return true;
  }

  std::size_t Automaton::countStates() const {
    return 0;
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

