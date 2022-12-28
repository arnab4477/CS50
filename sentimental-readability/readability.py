import nltk
import cs50
import collections

paragraph = cs50.get_string("Enter text: ")
# Counts all the non alphabetical characters of the characters
symbols = paragraph.count(' ') + paragraph.count(',') + paragraph.count('.') + paragraph.count('(') + paragraph.count(')') + paragraph.count('!') + paragraph.count(
    '/') + paragraph.count('?') + paragraph.count('-') + paragraph.count('\'') + paragraph.count('\"') + paragraph.count(';') + paragraph.count(':')
# Counts the number of words of the paragraph
wordN = (paragraph.count(' ') + 1) * 1.0
# Counts the number of sentences in the paragraph
sentenceN = len(nltk.sent_tokenize(paragraph)) * 1.0
# Counts the number of letters in the paragraph
letterN = (len(paragraph) - symbols) * 1.0

letterAverage = (letterN / wordN) * 100
sentenceAverage = (sentenceN / wordN) * 100
grade = round((0.0588 * letterAverage) - (0.296 * sentenceAverage) - 15.8)

if (grade < 1) or (grade == 1):
    print("Before Grade 1")
elif (grade > 16) or (grade == 16):
    print("Grade 16+")
else:
    print(f"Grade {grade}")
