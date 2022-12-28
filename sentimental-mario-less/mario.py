# TODO
from cs50 import get_int
while True:
    N = get_int("Enter height: ")
    if N >= 1 and N <= 8:
        break


for i in range (N):
    for j in range (N):
        if (i+j) < N - 1:
            print(" ", end="")
        else:
            print("#", end="")
    print()