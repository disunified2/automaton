
#include "gtest/gtest.h"

#include "Automaton.h"
#include <climits>

// Example test
TEST(AutomatonExampleTest, Default) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isValid());
}

// isValid() tests
TEST(AutomatonIsValidTest, emptyStates) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_FALSE(fa.isValid());
}
TEST(AutomatonIsValidTest, emptySymbols) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.isValid());
}
TEST(AutomatonIsValidTest, valid) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addState(0);
  EXPECT_TRUE(fa.isValid());
}

// Tests for addSymbol()
TEST(AutomatonAddSymbolTest, epsilon) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol(fa::Epsilon));
  EXPECT_EQ(fa.countSymbols(), 0u);
}
TEST(AutomatonAddSymbolTest, invalidSymbol) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol('\t'));
  EXPECT_EQ(fa.countSymbols(), 0u);
}
TEST(AutomatonAddSymbolTest, validSymbol) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_EQ(fa.countSymbols(), 1u);
}
TEST(AutomatonAddSymbolTest, duplicateValidSymbol) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.addSymbol('a'));
  EXPECT_EQ(fa.countSymbols(), 1u);
}
TEST(AutomatonAddSymbolTest, multipleValidSymbols) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_EQ(fa.countSymbols(), 3u);
}
TEST(AutomatonAddSymbolTest, mixedSymbols) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.addSymbol(fa::Epsilon));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_EQ(fa.countSymbols(), 2u);
}

// Tests for removeSymbol()
TEST(AutomatonRemoveSymbolTest, epsilon) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol(fa::Epsilon));
}
TEST(AutomatonRemoveSymbolTest, noSymbols) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('a'));
}
TEST(AutomatonRemoveSymbolTest, nonExistentSymbol) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_FALSE(fa.removeSymbol('b'));
  EXPECT_EQ(fa.countSymbols(), 1u);
}
TEST(AutomatonRemoveSymbolTest, invalidSymbol) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('\t'));
}
TEST(AutomatonRemoveSymbolTest, symbolPresent) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_EQ(fa.countSymbols(), 0u);
}
TEST(AutomatonRemoveSymbolTest, duplicateSymbol) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.removeSymbol('a'));
}
TEST(AutomatonRemoveSymbolTest, multipleSymbols) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_TRUE(fa.removeSymbol('b'));
  EXPECT_TRUE(fa.removeSymbol('c'));
  EXPECT_EQ(fa.countSymbols(), 0u);
}
TEST(AutomatonRemoveSymbolTest, symbolInTransition) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addState(0);
  fa.addTransition(0, 'a', 0);
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.hasTransition(0, 'a', 0));
  EXPECT_EQ(fa.countSymbols(), 0u);
  EXPECT_EQ(fa.countTransitions(), 0u);
}

// Tests for hasSymbol()
TEST(AutomatonHasSymbolTest, noSymbols) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasSymbol('a'));
}
TEST(AutomatonHasSymbolTest, epsilon) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasSymbol(fa::Epsilon));
}
TEST(AutomatonHasSymbolTest, symbolPresent) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_TRUE(fa.hasSymbol('a'));
}

// Tests for countSymbols()
TEST(AutomatonCountSymbolsTest, noSymbols) {
  fa::Automaton fa;
  EXPECT_EQ(fa.countSymbols(), 0u);
}
TEST(AutomatonCountSymbolsTest, oneSymbol) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_EQ(fa.countSymbols(), 1u);
}
TEST(AutomatonCountSymbolsTest, multipleSymbols) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  EXPECT_EQ(fa.countSymbols(), 3u);
}

// Tests for addState()
TEST(AutomatonAddStateTest, stateNotPresent) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_EQ(fa.countStates(), 1u);
}
TEST(AutomatonAddStateTest, stateAlreadyPresent) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_FALSE(fa.addState(0));
  EXPECT_EQ(fa.countStates(), 1u);
}
TEST(AutomatonAddStateTest, negativeState) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addState(-1));
  EXPECT_EQ(fa.countStates(), 0u);
}
TEST(AutomatonAddStateTest, multipleStates) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_EQ(fa.countStates(), 3u);
}

// Tests for removeState()
TEST(AutomatonRemoveStateTest, stateNotPresent) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeState(0));
}
TEST(AutomatonRemoveStateTest, negativeState) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeState(-1));
}
TEST(AutomatonRemoveStateTest, statePresent) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_TRUE(fa.removeState(0));
  EXPECT_EQ(fa.countStates(), 0u);
}
TEST(AutomatonRemoveStateTest, multipleStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_TRUE(fa.removeState(0));
  EXPECT_EQ(fa.countStates(), 0u);
}
TEST(AutomatonRemoveStateTest, stateInTransitionFrom) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  EXPECT_TRUE(fa.removeState(0));
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_EQ(fa.countStates(), 1u);
  EXPECT_FALSE(fa.hasTransition(0, 'a', 1));
  EXPECT_EQ(fa.countTransitions(), 0u);
}
TEST(AutomatonRemoveStateTest, stateInTransitionTo) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_EQ(fa.countStates(), 1u);
  EXPECT_FALSE(fa.hasTransition(0, 'a', 1));
  EXPECT_EQ(fa.countTransitions(), 0u);
}

// Tests for hasState()
TEST(AutomatonHasStateTest, noStates) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasState(0));
}
TEST(AutomatonHasStateTest, stateNotPresent) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.hasState(1));
  EXPECT_EQ(fa.countStates(), 1u);
}
TEST(AutomatonHasStateTest, statePresent) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_EQ(fa.countStates(), 1u);
}

// Tests for countStates()
TEST(AutomatonCountStatesTest, noStates) {
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(), 0u);
}
TEST(AutomatonCountStatesTest, duplicate) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(0);
  EXPECT_EQ(fa.countStates(), 1u);
}
TEST(AutomatonCountStatesTest, multiple) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  EXPECT_EQ(fa.countStates(), 3u);
}
TEST(AutomatonCountStatesTest, single) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_EQ(fa.countStates(), 1u);
}
TEST(AutomatonCountStatesTest, lotsOfStates) {
  fa::Automaton fa;
  for (int i=0; i < 1000; ++i) {
    EXPECT_TRUE(fa.addState(i));
  }
  EXPECT_EQ(fa.countStates(), 1000u);
}

// Tests for setStateInitial()
TEST(AutomatonSetStateInitialTest, stateNotAlreadyInitial) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.isStateInitial(0));
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
}
TEST(AutomatonSetStateInitialTest, stateAlreadyInitial) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
}

// Tests for isStateInitial()
TEST(AutomatonIsStateInitialTest, emptyStates) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateInitial(0));
}
TEST(AutomatonIsStateInitialTest, stateNotPresent) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.isStateInitial(1));
}
TEST(AutomatonIsStateInitialTest, stateNotInitial) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.isStateInitial(0));
}
TEST(AutomatonIsStateInitialTest, stateIsInitial) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
}

// Tests for setStateFinal()
TEST(AutomatonSetStateFinalTest, stateNotAlreadyFinal) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.isStateFinal(0));
}
TEST(AutomatonSetStateFinalTest, stateAlreadyFinal) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));
}

// Tests for isStateFinal()
TEST(AutomatonIsStateFinalTest, noStates) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateFinal(0));
}
TEST(AutomatonIsStateFinalTest, stateNotPresent) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.isStateFinal(1));
}
TEST(AutomatonIsStateFinalTest, stateNotFinal) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.isStateFinal(0));
}
TEST(AutomatonIsStateFinalTest, stateIsFinal) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));
}

// Tests for addTransition()
TEST(AutomatonAddTransitionTest, invalidChar) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.addTransition(0, '\t', 0));
  EXPECT_EQ(fa.countTransitions(), 0u);
}
TEST(AutomatonAddTransitionTest, charNonExistant) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.addTransition(0, 'a', 0));
  EXPECT_EQ(fa.countTransitions(), 0u);
}
TEST(AutomatonAddTransitionTest, fromNonExistant) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.addTransition(1, 'a', 0));
  EXPECT_EQ(fa.countTransitions(), 0u);
}
TEST(AutomatonAddTransitionTest, toNonExistant) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.addTransition(0, 'a', 1));
  EXPECT_EQ(fa.countTransitions(), 0u);
}
TEST(AutomatonAddTransitionTest, transitionToSelf) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_EQ(fa.countTransitions(), 1u);
}
TEST(AutomatonAddTransitionTest, validTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_EQ(fa.countTransitions(), 1u);
}
TEST(AutomatonAddTransitionTest, sameStateDiffArrival) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'a', 2));
  EXPECT_EQ(fa.countTransitions(), 2u);
}
TEST(AutomatonAddTransitionTest, epsilonTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  EXPECT_TRUE(fa.addTransition(0, fa::Epsilon, 1));
  EXPECT_EQ(fa.countTransitions(), 1u);
}
TEST(AutomatonAddTransitionTest, epsilonTransitionToSelf) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_TRUE(fa.addTransition(0, fa::Epsilon, 0));
}

// Tests for removeTransition()
TEST(AutomatonRemoveTransitionTest, charNotInAutomaton) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.removeTransition(0, 'a', 0));
}
TEST(AutomatonRemoveTransitionTest, stateNotInAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_FALSE(fa.removeTransition(0, 'a', 0));
}
TEST(AutomatonRemoveTransitionTest, charNotInTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  EXPECT_FALSE(fa.removeTransition(0, 'b', 0));
  EXPECT_EQ(fa.countTransitions(), 1u);
}
TEST(AutomatonRemoveTransitionTest, toNonExistant) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  EXPECT_FALSE(fa.removeTransition(0, 'a', 1));
  EXPECT_EQ(fa.countTransitions(), 1u);
}
TEST(AutomatonRemoveTransitionTest, plausibleTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.removeTransition(0, 'a', 0));
  EXPECT_EQ(fa.countTransitions(), 0u);
}
TEST(AutomatonRemoveTransitionTest, lastTransitionRemaining) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  fa.addTransition(0, 'a', 1);
  EXPECT_EQ(fa.countTransitions(), 2u);
  EXPECT_TRUE(fa.removeTransition(0, 'a', 0));
  EXPECT_EQ(fa.countTransitions(), 1u);
  EXPECT_TRUE(fa.removeTransition(0, 'a', 1));
  EXPECT_EQ(fa.countTransitions(), 0u);
}
TEST(AutomatonRemoveTransitionTest, epsilonTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addTransition(0, fa::Epsilon, 0);
  EXPECT_TRUE(fa.removeTransition(0, fa::Epsilon, 0));
  EXPECT_EQ(fa.countTransitions(), 0u);
}
TEST(AutomatonRemoveTransitionTest, removeAllProf) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  for (const char c : { 'a', 'b', 'c'}) {
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        fa.addTransition(i, c, j);
      }
    }
  }

  EXPECT_EQ(fa.countTransitions(), 75u);

  for (const char c : { 'a', 'b', 'c'}) {
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        fa.removeTransition(i, c, j);
      }
    }
  }

  EXPECT_EQ(fa.countTransitions(), 0u);
}

// Tests for hasTransition()
TEST(AutomatonHasTransitionTest, invalidChar) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.hasTransition(0, '\t', 0));
}
TEST(AutomatonHasTransitionTest, charNonExistant) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_FALSE(fa.hasTransition(0, 'a', 0));
}
TEST(AutomatonHasTransitionTest, fromNonExistant) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.hasTransition(1, 'a', 0));
}
TEST(AutomatonHasTransitionTest, toDoesNotExist) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.hasTransition(0, 'a', 1));
}
TEST(AutomatonHasTransitionTest, transitionDoesNotExist) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 0);
  fa.addTransition(0, 'b', 1);
  EXPECT_FALSE(fa.hasTransition(0, 'a', 1));
}
TEST(AutomatonHasTransitionTest, epsilonTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addTransition(0, fa::Epsilon, 0);
  EXPECT_TRUE(fa.hasTransition(0, fa::Epsilon, 0));
}
TEST(AutomatonHasTransitionTest, validTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  EXPECT_TRUE(fa.hasTransition(0, 'a', 0));
}
TEST(AutomatonHasTransitionTest, deletedState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  EXPECT_TRUE(fa.hasTransition(0, 'a', 1));
  fa.removeState(1);
  EXPECT_FALSE(fa.hasTransition(0, 'a', 1));
  EXPECT_EQ(fa.countTransitions(), 0u);
}
TEST(AutomatonHasTransitionTest, backwardsTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  EXPECT_TRUE(fa.hasTransition(0, 'a', 1));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 0));
}

// Tests for countTransitions()
TEST(AutomatonCountTransitionsTest, emptyAutomaton) {
  fa::Automaton fa;
  EXPECT_EQ(fa.countTransitions(), 0u);
}
TEST(AutomatonCountTransitionsTest, noTransitions) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  EXPECT_EQ(fa.countTransitions(), 0u);
}
TEST(AutomatonCountTransitionsTest, validTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  EXPECT_TRUE(fa.hasTransition(0, 'a', 1));
  EXPECT_EQ(fa.countTransitions(), 1u);
}
TEST(AutomatonCountTransitionsTest, validTransitionToSelf) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  EXPECT_TRUE(fa.hasTransition(0, 'a', 0));
  EXPECT_EQ(fa.countTransitions(), 1u);
}
TEST(AutomatonCountTransitionsTest, multipleTransitionsSameSymbol) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  fa.addTransition(0, 'a', 1);
  EXPECT_EQ(fa.countTransitions(), 2u);
}

// TESTS DU TP2

// Tests for hasEpsilonTransition()
TEST(AutomatonHasEpsilonTransition, notPresent) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.hasEpsilonTransition());
}
TEST(AutomatonHasEpsilonTransition, present) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, fa::Epsilon, 0);
  EXPECT_TRUE(fa.hasEpsilonTransition());
}
TEST(AutomatonHasEspilonTransition, epsilonToSelf) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addTransition(0, fa::Epsilon, 0);
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

// Tests for isDeterministic()
TEST(AutomatonIsDeterministicTest, automatonIsDeterministic) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 0);
  EXPECT_TRUE(fa.isDeterministic());
}
TEST(AutomatonIsDeterministicTest, automatonNoFinalState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  EXPECT_TRUE(fa.isDeterministic());
}
TEST(AutomatonIsDeterministicTest, multipleInitialStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateInitial(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  EXPECT_FALSE(fa.isDeterministic());
}
TEST(AutomatonIsDeterministicTest, noInitialState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  EXPECT_FALSE(fa.isDeterministic());
}
TEST(AutomatonIsDeterministicTest, notDeterministic) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  fa.addTransition(0, 'a', 1);
  EXPECT_FALSE(fa.isDeterministic());
}

// Tests for isComplete()
TEST(AutomatonIsCompleteTest, automatonIsComplete) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  EXPECT_TRUE(fa.isComplete());
}
TEST(AutomatonIsCompleteTest, automatonIsNotComplete) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  EXPECT_FALSE(fa.isComplete());
}
TEST(AutomatonIsCompleteTest, initialAndFinalStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 0);
  EXPECT_TRUE(fa.isComplete());
}
TEST(AutomatonIsCompleteTest, multipleTransitionsSameSymbol) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'b', 1);
  fa.addTransition(1, 'b', 0);
  fa.addTransition(0, 'a', 0);
  fa.addTransition(0, 'b', 0);
  fa.addTransition(1, 'a', 1);
  EXPECT_TRUE(fa.isComplete());
}

// Tests for makeTransition()
TEST(AutomatonMakeTransitionTest, emptyOrigin) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  std::set<int> origin;
  const std::set<int> result = fa.makeTransition(origin, 'a');
  EXPECT_TRUE(result.empty());
}
TEST(AutomatonMakeTransitionTest, symbolNotPresent) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  std::set<int> origin;
  origin.insert(0);
  const std::set<int> result = fa.makeTransition(origin, 'b');
  EXPECT_TRUE(result.empty());
}
TEST(AutomatonMakeTransitionTest, symbolPresentNoTransitions) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 0);
  std::set<int> origin;
  origin.insert(0);
  const std::set<int> result = fa.makeTransition(origin, 'b');
  EXPECT_TRUE(result.empty());
}
TEST(AutomatonMakeTransitionTest, stateMultipleTimes) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(1, 'a', 1);
  fa.addTransition(0, 'a', 1);
  std::set<int> origin;
  origin.insert(0);
  origin.insert(1);
  const std::set<int> result = fa.makeTransition(origin, 'a');
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.size(), 1u);
  EXPECT_TRUE(result.find(1) != result.end());
}
TEST(AutomatonMakeTransitionTest, multipleTransitions) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1, 'a', 1);
  fa.addTransition(0, 'a', 1);
  fa.addTransition(0, 'b', 0);
  std::set<int> origin;
  origin.insert(0);
  origin.insert(1);
  const std::set<int> result = fa.makeTransition(origin, 'b');
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.size(), 1u);
  EXPECT_TRUE(result.find(0) != result.end());
}
TEST(AutomatonMakeTransitionTest, originNotMax) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 0);
  std::set<int> origin;
  origin.insert(1);
  const std::set<int> result = fa.makeTransition(origin, 'a');
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.size(), 1u);
  EXPECT_TRUE(result.find(0) != result.end());
  EXPECT_FALSE(result.find(1) != result.end());
}
TEST(AutomatonMakeTransitionTest, stateNotPresent) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  std::set<int> origin;
  origin.insert(1);
  const std::set<int> result = fa.makeTransition(origin, 'a');
  EXPECT_TRUE(result.empty());
}

// Tests for readString()
TEST(AutomatonReadStringTest, noTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  std::set<int> result = fa.readString("ab");
  EXPECT_TRUE(result.empty());
}
TEST(AutomatonReadStringTest, noInitialStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  std::set<int> result = fa.readString("a");
  EXPECT_TRUE(result.empty());
}
TEST(AutomatonReadStringTest, oneStateRead) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 0);
  fa.addTransition(0, 'b', 0);
  std::set<int> result = fa.readString("ab");
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.size(), 1u);
  EXPECT_TRUE(result.find(0) != result.end());
}
TEST(AutomatonReadStringTest, multipleStatesRead) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'b', 2);
  std::set<int> result = fa.readString("ab");
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.size(), 1u);
  EXPECT_TRUE(result.find(2) != result.end());
}
TEST(AutomatonReadStringTest, multiplePaths) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'b', 2);
  fa.addTransition(1, 'b', 3);
  std::set<int> result = fa.readString("ab");
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.size(), 2u);
  EXPECT_TRUE(result.find(2) != result.end() && result.find(3) != result.end());
}

// Tests for match()
TEST(AutomatonMatchTest, stateNotFinalEmptyWord) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.match(""));
}
TEST(AutomatonMatchTest, stateFinalemptyWord) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.match(""));
}
TEST(AutomatonMatchTest, statesNotFinal) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'b', 2);
  EXPECT_FALSE(fa.match("ab"));
}
TEST(AutomatonMatchTest, correctStateFinal) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'b', 2);
  EXPECT_TRUE(fa.match("ab"));
}
TEST(AutomatonMatchTest, wrongStateFinal) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'b', 2);
  EXPECT_FALSE(fa.match("ab"));
}

// Tests for isLanguageEmpty()
TEST(AutomatonIsLanguageEmptyTest, noInitialState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  EXPECT_TRUE(fa.isLanguageEmpty());
}
TEST(AutomatonIsLanguageEmptyTest, noFinalState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  EXPECT_TRUE(fa.isLanguageEmpty());
}
TEST(AutomatonIsLanguageEmptyTest, languageNotEmpty) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  EXPECT_FALSE(fa.isLanguageEmpty());
}
TEST(AutomatonIsLanguageEmptyTest, twoFinal) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(0, 'a', 2);
  EXPECT_FALSE(fa.isLanguageEmpty());
}
TEST(AutomatonIsLanguageEmptyTest, twoInitial) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 2);
  fa.addTransition(1, 'a', 2);
  EXPECT_FALSE(fa.isLanguageEmpty());
}

// Tests for removeNonAccessibleStates()
TEST(AutomatonRemoveNonAccessibleStatesTest, noInitialState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 2);
  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 1u);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.isLanguageEmpty());
}
TEST(AutomatonRemoveNonAccessibleStatesTest, noPathToState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 2u);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.isLanguageEmpty());
}
TEST(AutomatonRemoveNonAccessibleStatesTest, noNonAccesible) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(0, 'a', 2);
  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
}
TEST(AutomatonRemoveNonAccessibleStatesTest, noNonAccessiblePathfind) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 2);
  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
}
TEST(AutomatonRemoveNonAccessibleStatesTest, wrongDirection) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(2, 'a', 0);
  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 2u);
}
TEST(AutomatonRemoveNonAccessibleStatesTest, sameLanguage) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(2, 'a', 2);
  EXPECT_TRUE(fa.match("a"));
  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 2u);
  EXPECT_TRUE(fa.match("a"));
}

// Tests for removeNonCoAccessibleStates()
TEST(AutomatonRemoveNonCoAccessibleStatesTest, noInitialStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 2);
  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countSymbols(), 1u);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.isLanguageEmpty());
}
TEST(AutomatonRemoveNonCoAccessibleStatesTest, noFinalStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 2);
  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(), 1u);
}
TEST(AutomatonRemoveNonCoAccessibleStatesTest, notCoAccessible) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 2);
  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(), 2u);
  EXPECT_TRUE(fa.match("a"));
}
TEST(AutomatonRemoveNonCoAccessibleStatesTest, noDeletion) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 2);
  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_TRUE(fa.match("aa"));
}
TEST(AutomatonRemoveNonCoAccessibleStatesTest, multiplePaths) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.setStateFinal(4);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 3);
  fa.addTransition(0, 'b', 2);
  fa.addTransition(2, 'b', 4);
  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(), 5u);
  EXPECT_TRUE(fa.match("aa") && fa.match("bb"));
}
TEST(AutomatonRemoveNonCoAccessibleStatesTest, singleFinalInitial) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  fa.removeNonCoAccessibleStates();
  EXPECT_TRUE(fa.countStates() == 1u);
  EXPECT_TRUE(fa.match("aaaa"));
}
TEST(AutomatonRemoveNonCoAccessibleStatesTest, finalNotConnected) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
}

// Tests for createMirror()
TEST(AutomatonCreateMirrorTest, simpleAutomaton) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  const fa::Automaton mirror = fa::Automaton::createMirror(fa);
  EXPECT_TRUE(mirror.isStateInitial(1));
  EXPECT_TRUE(mirror.isStateFinal(0));
  EXPECT_TRUE(mirror.hasTransition(1, 'a', 0));
}
TEST(AutomatonCreateMirrorTest, initialAndFinal) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  const fa::Automaton mirror = fa::Automaton::createMirror(fa);
  EXPECT_TRUE(mirror.isStateInitial(0));
  EXPECT_TRUE(mirror.isStateFinal(0));
  EXPECT_TRUE(mirror.hasTransition(0, 'a', 0));
}
TEST(AutomatonCreateMirrorTest, noInitialFinal) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  const fa::Automaton mirror = fa::Automaton::createMirror(fa);
  EXPECT_FALSE(mirror.isStateInitial(0));
  EXPECT_FALSE(mirror.isStateFinal(0));
  EXPECT_TRUE(mirror.hasTransition(0, 'a', 0));
}
TEST(AutomatonCreateMirrorTest, mirrorTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 0);
  const fa::Automaton mirror = fa::Automaton::createMirror(fa);
  EXPECT_TRUE(mirror.hasTransition(0, 'a', 1));
  EXPECT_TRUE(mirror.hasTransition(1, 'a', 0));
}

// Tests for createComplete()
TEST(AutomatonCreateCompleteTest, alreadyComplete) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  const fa::Automaton complete = fa::Automaton::createComplete(fa);
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(complete.isComplete());
  EXPECT_TRUE(fa.isIncludedIn(complete) && complete.isIncludedIn(fa));
}
TEST(AutomatonCreateCompleteTest, notComplete) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  const fa::Automaton complete = fa::Automaton::createComplete(fa);
  EXPECT_FALSE(fa.isComplete());
  EXPECT_TRUE(complete.isComplete());
}
TEST(AutomatonCreateCompleteTest, noTransitions) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  const fa::Automaton complete = fa::Automaton::createComplete(fa);
  EXPECT_FALSE(fa.isComplete());
  EXPECT_TRUE(complete.isComplete());
}
TEST(AutomatonCreateCompleteTest, maxInt) {
  fa::Automaton fa;
  fa.addState(INT_MAX);
  fa.addSymbol('a');
  const fa::Automaton complete = fa::Automaton::createComplete(fa);
  EXPECT_FALSE(fa.isComplete());
  EXPECT_TRUE(complete.isComplete());
}

// Tests for createComplement()
TEST(AutomatonCreateComplementTest, deterministicComplete) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'b', 1);
  fa.addTransition(1, 'a', 0);
  fa.addTransition(0, 'a', 0);
  // Adding a sink state to keep the language the same while making the automaton complete
  fa.addState(2);
  fa.addTransition(2, 'a', 2);
  fa.addTransition(2, 'b', 2);
  fa.addTransition(1, 'b', 2);
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.match("ababaaaa"));
  const fa::Automaton complement = fa::Automaton::createComplement(fa);
  EXPECT_TRUE(complement.match("abbaaaa"));
}
TEST(AutomatonCreateComplementTest, notDeterministic) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'b', 1);
  fa.addTransition(1, 'b', 0);
  fa.addTransition(0, 'a', 0);
  fa.addTransition(1, 'a', 1);
  EXPECT_TRUE(fa.isComplete());
  EXPECT_FALSE(fa.isDeterministic());
  const fa::Automaton complement = fa::Automaton::createComplement(fa);
  EXPECT_TRUE(complement.isDeterministic());
  EXPECT_TRUE(complement.isComplete());
}
TEST(AutomatonCreateComplementTest, notComplete) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'b', 1);
  EXPECT_FALSE(fa.isComplete());
  EXPECT_TRUE(fa.isDeterministic());
  const fa::Automaton complement = fa::Automaton::createComplement(fa);
  EXPECT_TRUE(complement.isDeterministic());
  EXPECT_TRUE(complement.isComplete());
}
TEST(AutomatonCreateComplementTest, complementOfComplement) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'b', 1);
  fa.addTransition(1, 'a', 0);
  fa.addTransition(0, 'a', 0);
  const fa::Automaton complement = fa::Automaton::createComplement(fa);
  const fa::Automaton complement2 = fa::Automaton::createComplement(complement);
  EXPECT_TRUE(fa.match("ababaaa"));
  EXPECT_FALSE(fa.match("abbaaa"));
  EXPECT_TRUE(complement.match("abbaaa"));
  EXPECT_TRUE(complement2.match("ababaaa"));
  EXPECT_FALSE(complement2.match("abbaaa"));
}
TEST(AutomatonCreateComplementTest, invertStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  fa::Automaton complement = fa::Automaton::createComplement(fa);
  EXPECT_TRUE(complement.isStateInitial(0));
  EXPECT_FALSE(complement.isStateFinal(0));
}
TEST(AutomatonCreateComplementTest, exampleAutomaton) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 0);
  fa.addTransition(1, 'a', 0);
  fa.addTransition(0, 'b', 1);
  EXPECT_TRUE(fa.match("abababa"));
  EXPECT_FALSE(fa.match("abbaaa"));
  fa::Automaton complement = fa::Automaton::createComplement(fa);
  EXPECT_TRUE(complement.isComplete());
  EXPECT_TRUE(complement.match("abbaaa"));
  EXPECT_FALSE(complement.match("ababaaa"));
}

// Tests for createIntersection()
TEST(AutomatonCreateIntersectionTest, noInitialStates) {
  fa::Automaton fa1;
  fa1.addState(0);
  fa1.addState(1);
  fa1.setStateFinal(1);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(0, 'a', 1);
  fa1.addTransition(1, 'a', 1);
  fa1.addTransition(1, 'b', 1);

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.addState(1);
  fa2.setStateFinal(1);
  fa2.addSymbol('a');
  fa2.addSymbol('b');
  fa2.addTransition(0, 'a', 0);
  fa2.addTransition(0, 'a', 1);
  fa2.addTransition(1, 'a', 0);
  fa2.addTransition(1, 'b', 1);

  fa::Automaton intersection = fa::Automaton::createIntersection(fa1, fa2);
  EXPECT_TRUE(intersection.isLanguageEmpty());
  EXPECT_TRUE(intersection.isValid());
}
TEST(AutomatonCreateIntersectionTest, noFinalStates) {
  fa::Automaton fa1;
  fa1.addState(0);
  fa1.addState(1);
  fa1.setStateInitial(0);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(0, 'a', 1);
  fa1.addTransition(1, 'a', 1);
  fa1.addTransition(1, 'b', 1);

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.addState(1);
  fa2.setStateInitial(0);
  fa2.addSymbol('a');
  fa2.addSymbol('b');
  fa2.addTransition(0, 'a', 0);
  fa2.addTransition(0, 'a', 1);
  fa2.addTransition(1, 'a', 0);
  fa2.addTransition(1, 'b', 1);

  fa::Automaton intersection = fa::Automaton::createIntersection(fa1, fa2);
  EXPECT_TRUE(intersection.isLanguageEmpty());
  EXPECT_TRUE(intersection.isValid());
}
TEST(AutomatonCreateIntersectionTest, correctIntersection) {
  fa::Automaton fa1;
  fa1.addState(0);
  fa1.addState(1);
  fa1.setStateInitial(0);
  fa1.setStateFinal(1);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(0, 'a', 1);
  fa1.addTransition(1, 'a', 1);
  fa1.addTransition(1, 'b', 1);

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.addState(1);
  fa2.setStateInitial(0);
  fa2.setStateFinal(1);
  fa2.addSymbol('a');
  fa2.addSymbol('b');
  fa2.addTransition(0, 'a', 0);
  fa2.addTransition(0, 'b', 1);
  fa2.addTransition(1, 'a', 0);
  fa2.addTransition(1, 'b', 1);

  fa::Automaton intersection = fa::Automaton::createIntersection(fa1, fa2);
  EXPECT_FALSE(intersection.isLanguageEmpty());
  EXPECT_TRUE(intersection.match("aabb"));
  EXPECT_TRUE(fa1.match("aba"));
  EXPECT_FALSE(intersection.match("aba"));
  EXPECT_TRUE(fa2.match("bb"));
  EXPECT_FALSE(intersection.match("bb"));
}
TEST(AutomatonCreateIntersectionTest, noTransitions) {
  fa::Automaton fa1;
  fa1.addState(0);
  fa1.addState(1);
  fa1.setStateInitial(0);
  fa1.setStateFinal(1);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(0, 'a', 1);
  fa1.addTransition(1, 'a', 1);
  fa1.addTransition(1, 'b', 1);

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.setStateInitial(0);
  fa2.setStateFinal(0);
  fa2.addSymbol('a');

  fa::Automaton intersection = fa::Automaton::createIntersection(fa1, fa2);
  EXPECT_TRUE(intersection.isLanguageEmpty());
}
TEST(AutomatonCreateIntersectionTest, noCommonSymbols) {
  fa::Automaton fa1;
  fa1.addState(0);
  fa1.addState(1);
  fa1.setStateInitial(0);
  fa1.setStateFinal(1);
  fa1.addSymbol('a');
  fa1.addTransition(0, 'a', 1);

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.addState(1);
  fa2.setStateInitial(0);
  fa2.setStateFinal(1);
  fa2.addSymbol('b');
  fa2.addTransition(0, 'b', 1);

  EXPECT_FALSE(fa1.isLanguageEmpty() && fa2.isLanguageEmpty());

  fa::Automaton intersection = fa::Automaton::createIntersection(fa1, fa2);
  EXPECT_TRUE(intersection.isLanguageEmpty());
}

// Tests for hasEmptyIntersectionWith()
TEST(AutomatonHasEmptyIntersectionWithTest, noInitialStates) {
  fa::Automaton fa1;
  fa1.addState(0);
  fa1.addState(1);
  fa1.setStateFinal(1);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(0, 'a', 1);
  fa1.addTransition(1, 'a', 1);
  fa1.addTransition(1, 'b', 1);

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.addState(1);
  fa2.setStateFinal(1);
  fa2.addSymbol('a');
  fa2.addSymbol('b');
  fa2.addTransition(0, 'a', 0);
  fa2.addTransition(0, 'a', 1);
  fa2.addTransition(1, 'a', 0);
  fa2.addTransition(1, 'b', 1);

  EXPECT_TRUE(fa1.hasEmptyIntersectionWith(fa2));
}
TEST(AutomatonHasEmptyIntersectionWithTest, noFinalStates) {
  fa::Automaton fa1;
  fa1.addState(0);
  fa1.addState(1);
  fa1.setStateInitial(0);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(0, 'a', 1);
  fa1.addTransition(1, 'a', 1);
  fa1.addTransition(1, 'b', 1);

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.addState(1);
  fa2.setStateInitial(0);
  fa2.addSymbol('a');
  fa2.addSymbol('b');
  fa2.addTransition(0, 'a', 0);
  fa2.addTransition(0, 'a', 1);
  fa2.addTransition(1, 'a', 0);
  fa2.addTransition(1, 'b', 1);

  EXPECT_TRUE(fa1.hasEmptyIntersectionWith(fa2));
}
TEST(AutomatonHasEmptyIntersectionWithTest, correctIntersection) {
  fa::Automaton fa1;
  fa1.addState(0);
  fa1.addState(1);
  fa1.setStateInitial(0);
  fa1.setStateFinal(1);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(0, 'a', 1);
  fa1.addTransition(1, 'a', 1);
  fa1.addTransition(1, 'b', 1);

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.addState(1);
  fa2.setStateInitial(0);
  fa2.setStateFinal(1);
  fa2.addSymbol('a');
  fa2.addSymbol('b');
  fa2.addTransition(0, 'a', 0);
  fa2.addTransition(0, 'b', 1);
  fa2.addTransition(1, 'a', 0);
  fa2.addTransition(1, 'b', 1);

  EXPECT_FALSE(fa1.hasEmptyIntersectionWith(fa2));
}
TEST(AutomatonHasEmptyIntersectionWithTest, noTransition) {
  fa::Automaton fa1;
  fa1.addState(0);
  fa1.addState(1);
  fa1.setStateInitial(0);
  fa1.setStateFinal(1);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(0, 'a', 1);
  fa1.addTransition(1, 'a', 1);
  fa1.addTransition(1, 'b', 1);

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.setStateInitial(0);
  fa2.setStateFinal(0);
  fa2.addSymbol('a');

  EXPECT_TRUE(fa1.hasEmptyIntersectionWith(fa2));
}

// Tests for createDeterministic()
TEST(AutomatonCreateDeterministicTest, alreadyDeterministic) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 0);
  fa::Automaton deterministic = fa::Automaton::createDeterministic(fa);
  EXPECT_TRUE(deterministic.isDeterministic());
  EXPECT_EQ(deterministic.countSymbols(), fa.countSymbols());
  EXPECT_TRUE(deterministic.hasSymbol('a'));
}
TEST(AutomatonCreateDeterministicTest, noInitialStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 0);
  fa::Automaton deterministic = fa::Automaton::createDeterministic(fa);
  EXPECT_TRUE(deterministic.isDeterministic());
  EXPECT_TRUE(deterministic.isLanguageEmpty());
}
TEST(AutomatonCreateDeterministicTest, noFinalStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'a', 0);
  fa::Automaton deterministic = fa::Automaton::createDeterministic(fa);
  EXPECT_TRUE(deterministic.isDeterministic());
  EXPECT_TRUE(deterministic.isLanguageEmpty());
}
TEST(AutomatonCreateDeterministicTest, determinisationNeeded) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 0);
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'b', 1);
  EXPECT_TRUE(fa.match("aaabbbb") && fa.match("a"));
  EXPECT_FALSE(fa.isDeterministic());
  fa::Automaton deterministic = fa::Automaton::createDeterministic(fa);
  EXPECT_TRUE(deterministic.isDeterministic());
  EXPECT_TRUE(deterministic.match("aaabbbb") && deterministic.match("a"));
  EXPECT_TRUE(deterministic.hasSymbol('a') && deterministic.hasSymbol('b'));
}
TEST(AutomatonCreateDeterministicTest, DS2024) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  for (int i=0; i<=3; i++){
    fa.addState(i);
  }
  fa.addTransition(0,'a',2);
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',3);

  fa.addTransition(1,'b',3);

  fa.addTransition(2,'b',0);
  fa.addTransition(2,'b',3);
  fa.addTransition(2,'a',2);

  fa.addTransition(3,'a',1);
  fa.addTransition(3,'b',2);
  fa.addTransition(3,'a',3);

  fa.setStateFinal(2);
  fa.setStateInitial(0);

  fa::Automaton A = fa::Automaton::createDeterministic(fa);

  EXPECT_FALSE(fa.isLanguageEmpty());
  EXPECT_TRUE(A.isDeterministic());
  EXPECT_EQ(A.countStates(),9u);
}

// Tests for isIncludedIn()
TEST(AutomatonIsIncludedInTest, emptyLanguage) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.addSymbol('b');

  EXPECT_FALSE(fa.isIncludedIn(fa2));
  EXPECT_TRUE(fa2.isIncludedIn(fa));
}
TEST(AutomatonIsIncludedInTest, self) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  EXPECT_TRUE(fa.isIncludedIn(fa));
}
// Check if fails
TEST(AutomatonIsIncludedInTest, nonEmptyLanguage) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.addState(1);
  fa2.addState(2);
  fa2.setStateInitial(0);
  fa2.setStateFinal(2);
  fa2.addSymbol('b');
  fa2.addTransition(0, 'b', 1);
  fa2.addTransition(1, 'b', 2);

  EXPECT_FALSE(fa.isIncludedIn(fa2));
}
// Check if fails
TEST(AutomatonIsIncludedInTest, includedIn) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  // fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.addState(1);
  fa2.setStateInitial(0);
  fa2.setStateFinal(1);
  fa2.addSymbol('a');
  fa2.addSymbol('b');
  fa2.addTransition(0, 'a', 1);
  fa2.addTransition(1, 'b', 1);

  EXPECT_TRUE(fa.isIncludedIn(fa2));
  EXPECT_FALSE(fa2.isIncludedIn(fa));
}

// Tests for createMinimalMoore()
TEST(AutomatonCreateMinimalMooreTest, emptyAutomaton) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');

  fa::Automaton minimal = fa::Automaton::createMinimalMoore(fa);

  EXPECT_TRUE(minimal.isLanguageEmpty());
  EXPECT_TRUE(minimal.isIncludedIn(fa) && fa.isIncludedIn(minimal));
}
TEST(AutomatonCreateMinimalMooreTest, alreadyMinimal) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);

  fa::Automaton minimal = fa::Automaton::createMinimalMoore(fa);

  EXPECT_FALSE(minimal.isLanguageEmpty());
  EXPECT_TRUE(minimal.isIncludedIn(fa) && fa.isIncludedIn(minimal));
  EXPECT_TRUE(minimal.match("aaa") && fa.match("aaa"));
}

// Tests for createMinimalBrzozowski
TEST(AutomatonCreateMinimalBrzozowskiTest, emptyAutomaton) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');

  fa::Automaton minimal = fa::Automaton::createMinimalBrzozowski(fa);

  EXPECT_TRUE(minimal.isLanguageEmpty());
  EXPECT_TRUE(minimal.isIncludedIn(fa) && fa.isIncludedIn(minimal));
}
TEST(AutomatonCreateMinimalBrzozowskiTest, alreadyMinimal) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);

  fa::Automaton minimal = fa::Automaton::createMinimalBrzozowski(fa);

  EXPECT_FALSE(minimal.isLanguageEmpty());
  EXPECT_TRUE(minimal.isIncludedIn(fa) && fa.isIncludedIn(minimal));
  EXPECT_TRUE(minimal.match("aaa") && fa.match("aaa"));
  EXPECT_EQ(minimal.countSymbols(), 1u);
  EXPECT_EQ(minimal.countStates(), 1u);
}








int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
