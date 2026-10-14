# coding=utf-8
__author__ = 'Лена'

PAGE_URL = "http://testmethods.tmweb.ru/"
INPUT_ELEMENT = "//input[@type='text' and @name='Input']"
RESULT_ELEMENT = "//input[@type='button' and @name='DoIt']"

NUMBERS = (
    "//input[@type='button' and @name='zero']",
    "//input[@type='button' and @name='one']",
    "//input[@type='button' and @name='two']",
    "//input[@type='button' and @name='three']",
    "//input[@type='button' and @name='four']",
    "//input[@type='button' and @name='five']",
    "//input[@type='button' and @name='six']",
    "//input[@type='button' and @name='seven']",
    "//input[@type='button' and @name='eight']",
    "//input[@type='button' and @name='nine']",
)

ACTIONS = {
    '+': "//input[@type='button' and @name='plus']",
    '-': "//input[@type='button' and @name='minus']",
    '/': "//input[@type='button' and @name='div']",
    '*': "//input[@type='button' and @name='times']"
}
