# Created by justin at 14.12.2015
Feature: Simple arithmetics
  # Enter feature description here

  Scenario: Simple expression
    Given I am Clavdiya Agapovna
    When I type ((1 + 2) * 5 - 10 / 2 + 0.3 * 2)
    Then I count it
    And see 10.6 on screen