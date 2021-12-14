from sys import argv
from random import randint, seed, shuffle
from random_word import RandomWords

seed(1902913)

r = RandomWords()

categories = ['acao','sci-fi','comedia','aventura','terror','suspense','esporte','drama']
year = list(range(1800,2021))
shuffle(year)
duration = list(range(5,280))
shuffle(duration)
views = list(range(1,100000))
shuffle(views)

for k,j in enumerate(["titulo", "duracao", "ano", "visualizacoes"]):

    out = open("test."+str(k),"w")
    print(argv[1], file=out)
    print("aventura,acao,sci-fi,comedia", file=out)
    print(j, file=out)
    for i in range(int(argv[1])):
        movie = r.get_random_word(maxLength=20)
        cat = []
        for j in range(randint(1,randint(1,5))):
            cat.append(categories[randint(0,len(categories)-1)])
        print(movie, file=out)
        print(year.pop(), file=out)
        print(",".join(cat), file=out)
        print(views.pop(), file=out)
        print(duration.pop(), file=out)

