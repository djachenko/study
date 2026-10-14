# coding=utf-8

import pytest
from pytest_bdd import scenario, given, when, then, parsers

import constants

__author__ = 'Лена'


@pytest.mark.p2
@pytest.allure.severity(pytest.allure.severity_level.MINOR)
@pytest.allure.feature("Math library", "Complex functions")
@scenario("Complex.feature", "Sqrt")
def test_sqrt_function(browser):
    pass


@pytest.mark.p2
@pytest.allure.severity(pytest.allure.severity_level.MINOR)
@pytest.allure.feature("Complex functions")
@scenario("Complex.feature", "Braces")
def test_braces(browser):
    pass


@pytest.mark.p2
@pytest.mark.xfail
@pytest.allure.severity(pytest.allure.severity_level.MINOR)
@pytest.allure.feature("Complex functions")
@scenario("Complex.feature", "Pow")
def test_pow_function(browser):
    pass


@given("I am Rudolph Sigizmundovich")
def i_am_rudolph(browser):
    browser.open_page(constants.PAGE_URL)
    browser.reset()


@when(parsers.parse("I type {expr}"))
def type_expression(browser, expr):
    browser.type_text(constants.INPUT_ELEMENT, expr)


@then("I count it")
def count_it(browser):
    browser.click(constants.RESULT_ELEMENT)


@then(parsers.parse("see {result} on screen"))
def check_result(browser, result):
    result = float(result)
    browser.check_equality(constants.INPUT_ELEMENT, result)
