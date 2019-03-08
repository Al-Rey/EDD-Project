from bs4 import BeautifulSoup
import requests

import statistics

thislist = []

"""This class scrapes the data from the HTML document. It then puts the desired
data (any items with the id of "count", converts the numbers there to integers,
and store them into an array"""
class WebScrape:
    def __init__(self):#constructor runs as soon as an object is created
        with open('website.html') as html_file:
            soup = BeautifulSoup(html_file, 'html.parser')
        for number in soup.find_all('table'):
            for text in number.find_all('td', class_='count'):
                num = int(text.text)
                thislist.append(num)
    """
    def getList():
        return thislist
    """

"""This class has functions that will take the data from the newly filled
array and will calculate the mean and the median"""
class Stats:
    def median(self, data):
        return round(statistics.median(data), 4)
    def average(self, data):
        return round(statistics.mean(data), 4)


site = WebScrape() #creates a new webScrape object
del site #deletes the unnecessary object because the list has been filled
math = Stats()#creates a Stats object

#data = site.getList()

#prints the mean and median of the data set
print('The median of the data set is ', math.median(thislist))
print('The mean of the data set is ', math.average(thislist))
