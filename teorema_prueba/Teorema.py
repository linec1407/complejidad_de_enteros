def main():
    # Leer los textos
    complejidad = open("complejidad.txt", "r")
    dbr_1 = open("dbr_1.txt", "r")
    dbr_2 = open("dbr_2.txt", "w")
    diccionario = {}

    for line in complejidad:
        n, complx = [int(x) for x in line.split()]
        diccionario[n] = complx
    # La variable booleana 'teorema' es True
    teorema = True
    # Cada linea en fDBR.txt 'b' (izquierda) es un numero de la forma b=(2^i)(3^j)
    # y 'r' (derecha) es un divisor propio de b.
    for line in dbr_1:
        b, r = [int(x) for x in line.split()]
        b1 = b
        i = 0
        j = 0
        while b1 % 2 == 0:
            i += 1
            b1 = b1 / 2
        while b1 % 3 == 0:
            j += 1
            b1 = b1 / 3
        # Por teorema, la complejidad de b=(2^i)(3^j) viene dado por: 2i+3j
        if diccionario[b + r] != 2 * i + 3 * j + 1:
            # Para los casos donde no se da complejidad(b+r)=2i+3j+1 verificamos
            # que complejidad(2b+r) = 2i+3j+3
            dbr_2.write(str(b) + ", " + str(r) + "\n")
            if diccionario[2 * b + r] != 2 * i + 3 * j + 3:
                teorema = False

    print("El teorema es: {}".format(teorema))


if __name__ == '__main__':
    main()
