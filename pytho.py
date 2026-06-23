def busqueda_binaria(lista, clave):
    izq = 0
    der = len(lista) - 1
    while izq <= der:
        mid = (izq + der) // 2
    if lista[mid] == clave:
        return mid # ¡Encontrado!
    elif lista[mid] < clave:
        izq = mid + 1 # mitad derecha ↑
    else:
        der = mid - 1 # mitad izquierda
    return -1 # no está en la lista

nums = [2, 5, 8, 12, 16, 23, 38, 47, 56, 72, 89, 95]
print(busqueda_binaria(nums,23))
print("hola")