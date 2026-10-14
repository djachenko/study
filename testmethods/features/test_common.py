import pytest
from pytest_bdd import given, parsers

import constants

__author__ = 'justin'


@pytest.allure.severity(pytest.allure.severity_level.BLOCKER)
@pytest.allure.feature("Common")
@pytest.mark.acceptance
@given(parsers.parse("I am {name}"))
def test_open_page(browser):
    browser.open_page(constants.PAGE_URL)

