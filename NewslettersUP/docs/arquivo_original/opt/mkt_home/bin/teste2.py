#!/usr/bin/env python3

from selenium import webdriver
from selenium.webdriver import FirefoxOptions

opts = FirefoxOptions()
opts.add_argument("--headless")
browser = webdriver.Firefox(options=opts, executable_path=r'/usr/local/bin/geckodriver')

browser.get('https://www.up.pt')
