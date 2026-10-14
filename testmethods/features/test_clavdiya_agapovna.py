# coding=utf-8
from random import randint, choice
import allure
import pytest
from pytest_bdd import scenario, given, when, then, parsers

import constants

__author__ = 'Лена'


@pytest.allure.severity(pytest.allure.severity_level.CRITICAL)
@pytest.allure.feature("UI Feature", "Addition")
@scenario("Arithmetics.feature", "Simple expression")
def test_calculate_expression(browser):
    """
    Clavdiya Agapovna checks if she has bought correct calculator
    """


@pytest.allure.severity(pytest.allure.severity_level.CRITICAL)
@pytest.allure.feature("UI Feature", "Addition", "Subtraction", "Division", "Multiplication")
@scenario("UI.feature", "Expression")
def test_web_input(browser):
    """
     Clavdiya Agapovna counts different expressions using four arithmetic operations
    """
    browser.open_page(constants.PAGE_URL)


@given("I am Clavdiya Agapovna")
def i_am_clavdiya_agapovna(browser):
    browser.open_page(constants.PAGE_URL)


@when(parsers.parse("I input {expression}"))
def input_expression(browser, expression):
    actions = ('+', '-', '*', '/')
    numbers = list(str(i) for i in range(10))

    for c in expression:
        if c in actions:
            browser.click(constants.ACTIONS[c])
        elif c in numbers:
            browser.click(constants.NUMBERS[int(c)])


@when(parsers.parse("I type {expr}"))
def type_simple_expression(browser, communicator, expr):
    browser.type_text(constants.INPUT_ELEMENT, expr)


@then(parsers.parse("I count it"))
def count_it(browser):
    browser.click(constants.RESULT_ELEMENT)


@then(parsers.parse("see {result} on screen"))
def check_result(browser, communicator, result):
    result = float(result)
    browser.check_equality(constants.INPUT_ELEMENT, result)
