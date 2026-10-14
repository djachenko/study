# Created by justin at 14.12.2015
Feature: Keyboard
  # Enter feature description here

  Scenario: Input
    Given I am Vasya
    When I type some random stuff
    Then I see it on screen

  Scenario: Reset
    Given I am Vasya
    When I type some random stuff
    Then I click reset
    And see clear screen

  Scenario: Russian comma
    Given I am russian matematician
    When I type 0,6
    Then I count it
    And see 0.6 on screen