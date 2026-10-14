# Created by justin at 14.12.2015
Feature: #Enter feature name here
  # Enter feature description here

  Scenario: Sqrt
    Given I am Rudolph Sigizmundovich
    When I type Math.sqrt(16)
    Then I count it
    And see 4 on screen

  Scenario: Braces
    Given I am Rudolph Sigizmundovich
    When I type (2 + 2) * 2
    Then I count it
    And see 8 on screen

  Scenario: Pow
    Given I am Rudolph Sigizmundovich
    When I type 2^3^4
    Then I count it
    And see 4096 on screen