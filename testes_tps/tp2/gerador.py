from random import randint,seed, shuffle
from sys import argv

seed(123124)

for i in range(int(argv[1])):
    num_elementos = randint(100,10000)
    tam_hash = randint(10,20)
    print(tam_hash, num_elementos)
    v = [str(x) for x in range(num_elementos)]
    shuffle(v)
    print(" ".join(v))
    print(randint(0,tam_hash-1))

print("0 0")
