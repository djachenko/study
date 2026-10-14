# coding=utf-8
from random import randint, choice
import pytest
from pytest_bdd import scenario, then, when, given, parsers

import constants

__author__ = 'Лена'


@scenario("UI.feature", "Input")
@pytest.allure.severity(pytest.allure.severity_level.CRITICAL)
@pytest.allure.feature("UI Feature")
def test_ui_input(browser):
    """
     Vasya is having fun clicking various buttons and laughing at numbers appearing on screen
    """


@scenario("UI.feature", "Reset")
@pytest.mark.acceptance
@pytest.allure.severity(pytest.allure.severity_level.CRITICAL)
@pytest.allure.feature("UI input", "Resetting")
def test_ui_reset():
    """
     Vasya types different numbers and checks if all his tricks can be hidden
    """


@scenario("Keyboard.feature", "Input")
@pytest.allure.severity(pytest.allure.severity_level.MINOR)
@pytest.allure.feature("Keyboard input")
def test_keyboard_input():
    """
     Vasya is having fun typing random numbers and laughing at numbers appearing on screen
    """


@given(parsers.parse("I am {name}"))
def i_am_vasya(name):
    pass


@when('I click some random stuff')
def click_random_stuff(browser, communicator):
    browser.open_page(constants.PAGE_URL)

    total = "0"

    browser.click(constants.NUMBERS[0])

    for i in range(randint(0, 5)):
        # action = choice(constants.ACTIONS.keys())  # 2.7
        action = choice(list(constants.ACTIONS.keys()))  # 2.7

        total += " %s " % action

        browser.click(constants.ACTIONS[action])

        value = randint(1, 175)

        total += str(value)

        for j in str(value):
            browser.click(constants.NUMBERS[int(j)])

    communicator["total"] = total


@when("I type some random stuff")
def type_random_stuff(browser, communicator):
    browser.open_page(constants.PAGE_URL)

    total = "0"

    browser.click(constants.NUMBERS[0])

    for i in range(randint(0, 5)):
        # action = choice(constants.ACTIONS.keys())  # 2.7
        action = choice(list(constants.ACTIONS.keys()))  # 3.5

        total += " %s " % action

        browser.click(constants.ACTIONS[action])

        value = randint(1, 175)

        total += str(value)

        for j in str(value):
            browser.type_text(constants.INPUT_ELEMENT, j)

    communicator["total"] = total


@then("I click reset")
def click_reset(browser):
    browser.reset()


@then("see clear screen")
def see_clear_screen(browser):
    result_value = browser.get_value(constants.INPUT_ELEMENT)

    assert result_value == ""


@then('I see it on screen')
def i_see_it_on_screen(browser, communicator):
    result_value = browser.get_value(constants.INPUT_ELEMENT)
    total = communicator["total"]

    assert result_value == total


@then("I type reset")
def type_reset(browser):
    browser.reset_esc()
