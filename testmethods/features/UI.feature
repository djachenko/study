# Created by justin at 14.12.2015
Feature: UI
  # Enter feature description here

  Scenario: Input
    Given I am Vasya
    When I click some random stuff
    Then I see it on screen

  Scenario: Reset
    Given I am Vasya
    When I click some random stuff
    Then I click reset
    And see clear screen

  Scenario: Expression
    Given I am Clavdiya Agapovna
    When I input 45 + 456 * 5455 - 5454 / 4545
    Then I count it
    And see 2487523.8 on screen