import allure
from allure.constants import AttachmentType
from selenium.webdriver.common.keys import Keys
import constants

__author__ = 'justin'


class Browser(object):
    reset_element = "//input[@type='button' and @name='clear']"

    def __init__(self, driver):
        super(Browser, self).__init__()
        self.driver = driver

    def type_text(self, xpath, text):
        with allure.step("Typing text: \"%s\"" % text):
            element = self.driver.find_element_by_xpath(xpath)
            element.send_keys(text)
            allure.attach('Screenshot', self.driver.get_screenshot_as_png(), type=AttachmentType.PNG)

    def click(self, xpath):
        with allure.step("Clicking"):
            element = self.driver.find_element_by_xpath(xpath)
            element.click()
            allure.attach('Screenshot', self.driver.get_screenshot_as_png(), type=AttachmentType.PNG)

    def get_value(self, xpath):
        element = self.driver.find_element_by_xpath(xpath)
        return element.get_attribute('value')

    def open_page(self, url):
        with allure.step("Opening page"):
            self.driver.get(url)
            allure.attach('Screenshot', self.driver.get_screenshot_as_png(), type=AttachmentType.PNG)

    def check_equality(self, xpath, expected_value):
        with allure.step("Check correctness"):
            result_text = self.get_value(xpath)
            result = float(result_text)

            assert result == expected_value

    def reset(self):
        with allure.step("Reset"):
            self.click(self.reset_element)

    def reset_esc(self):
        with allure.step("Keyboard reset"):
            input_element = self.driver.find_element_by_xpath(constants.INPUT_ELEMENT)
            input_element.send_keys(Keys.ESCAPE)