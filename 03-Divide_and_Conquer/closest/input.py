from __future__ import print_function
import random
with open("data.in", 'w') as f:
    n = 100
    print(n, file=f)
    idx1 = random.randint(5, n-1)
    idx2 = random.randint(0, idx1-1)
    print(idx1, idx2)
    for i in range(n):
        if i == idx1 or i == idx2 :
            print(-100, -101, file=f)
        else:
            print(-100, random.randint(-10**9, 10**9), file=f)
