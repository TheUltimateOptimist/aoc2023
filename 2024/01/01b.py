from util import read

lines = read().splitlines()
lista = list(map(lambda x: int(x.split(" ")[0]), lines))
listb = list(map(lambda x: int(x.split(" ")[-1]), lines))
lista.sort()
listb.sort()
indexa, indexb, score = 0
while indexa < len(lista):
    number = lista[indexa]
    occurrences_lista = 0
    while indexa < len(lista) and lista[indexa] == number:
        indexa += 1
        occurrences_lista += 1
    occurrences_listb = 0 
    while indexb < len(listb) and listb[indexb] < number:
        indexb += 1
    while indexb < len(listb) and listb[indexb] == number:
        occurrences_listb += 1
        indexb += 1
    score += number*occurrences_lista*occurrences_listb
print(score)