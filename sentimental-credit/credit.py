from cs50 import get_int

cardN = get_int("enter your card number ")
# This will be used to in a different loop as the alternative for cardN
cardN2 = cardN
sum1 = 0
sum2 = 0
# This is the length of the card number
lengthN = int(len(str(cardN)))
firstN = int(str(cardN)[:1])
# This is the first 2 digits of the number
first2N = int(str(cardN)[:2])

while cardN > 0:
    secondlastN = int(cardN / 10)
    everyotherN = int(secondlastN % 10)
    cardN = int(cardN / 100)
    multiplyN = everyotherN * 2
    digitSum = int((multiplyN / 10) + (multiplyN % 10))
    sum1 = sum1 + digitSum

while cardN2 > 0:
    c = int(cardN2 % 10)
    cardN2 = int(cardN2 / 100)
    sum2 = sum2 + c

validity = int((sum1 + sum2) % 10)

if validity == 0 and (first2N == 34 or first2N == 37) and lengthN == 15:
    print("AMEX")

elif validity == 0 and (first2N == 51 or first2N == 52 or first2N == 53 or first2N == 54 or first2N == 55) and lengthN == 16:
    print("MASTERCARD")

elif validity == 0 and (lengthN == 13 or lengthN == 16) and firstN == 4:
    print("VISA")

else:
    print("INVALID")