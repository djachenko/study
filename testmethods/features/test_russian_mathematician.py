# coding=utf-8
import pytest
from pytest_bdd import scenario, then, when, given, parsers

import constants

__author__ = 'Лена'


@pytest.mark.xfail
@scenario("Keyboard.feature", "Russian comma")
@pytest.mark.p2
@pytest.allure.severity(pytest.allure.severity_level.MINOR)
@pytest.allure.feature("Keyboard input", "Data handling")
def test_comma_separation(browser):
    pass


@given("I am russian matematician")
def russian_matematician(browser):
    browser.open_page(constants.PAGE_URL)
    pass


@when(parsers.parse("I type {expr}"))
def type_simple_expression(browser, communicator, expr):
    browser.type_text(constants.INPUT_ELEMENT, expr)


@then(parsers.parse("I count it"))
def count_it(browser):
    browser.click(constants.RESULT_ELEMENT)


@then(parsers.parse("see {result} on screen"))
def check_result(browser, result):
    result = float(result)
    browser.check_equality(constants.INPUT_ELEMENT, result)
