
#include "gtest/gtest.h"

#include "Automaton.h"

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
TEST(AutomatonIsCompleteTest, epsilonTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'b', 1);
  fa.addTransition(1, 'b', 0);
  fa.addTransition(0, 'a', 0);
  fa.addTransition(1, 'a', 1);
  EXPECT_TRUE(fa.isComplete());
  fa.addTransition(0, fa::Epsilon, 1);
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













int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
