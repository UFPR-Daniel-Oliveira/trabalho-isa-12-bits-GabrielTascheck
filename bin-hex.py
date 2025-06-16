import sys

filename = sys.argv[1]

try:

    fp = open(filename, "r", encoding="utf-16")
    for line in fp:

        linha_limpa = line.strip()
        if linha_limpa:

            numero_inteiro = int(linha_limpa, 2)

            hex_formatado = f'{numero_inteiro:03x}'
            
            # 3. Imprime o resultado final formatado
            print(hex_formatado)

finally:

    if 'fp' in locals() and not fp.closed:
        fp.close()