import pytest
from selenium import webdriver
from browser import Browser

__author__ = 'justin'


@pytest.yield_fixture(scope="session")
def browser():
    result = webdriver.Chrome()
    driver = Browser(result)

    yield driver

    result.quit()


@pytest.fixture()
def communicator():
    return {}
