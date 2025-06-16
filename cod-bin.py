import sys
import re

OPCODES = {
    "add":  "0000", "sub":  "1000", "mul":  "1001", "not":  "1100",
    "slr":  "1010", "srr":  "1011", "and":  "1110", "or":   "1101",
    "xor":  "1111", "addi": "0001", "lw":   "0111", "sw":   "0110",
    "jal":  "0010", "jalr": "0011", "brzr": "0100", "ge":  "0101"
}

def registrar_para_binario(reg_str, bits=4):

    if not re.match(r'^x([0-9]|1[0-5])$', reg_str):
        raise ValueError(f"Registrador inválido: '{reg_str}'. Esperado x0-x15.")
    
    num = int(reg_str[1:]) 
    return format(num, f'0{bits}b') 


def imediato_para_binario(num_str, bits=4): 

    num = int(num_str)
    if not (-(2**(bits-1)) <= num < (2**(bits-1))):
            raise ValueError(f"Valor imediato '{num_str}' fora do intervalo para {bits} bits ({- (2**(bits-1))} a {(2**(bits-1))-1}).")

    if num < 0:
        num = (1 << bits) + num 
    
    return format(num, f'0{bits}b')


def processar_instrucao(linha):

    linha = linha.strip()
    if not linha or linha.startswith(';'):
        return None

    partes = linha.split()
    if not partes:
        return None

    instrucao_nome = partes[0].lower()

    if instrucao_nome not in OPCODES:
        raise ValueError(f"Instrução não reconhecida: '{instrucao_nome}'. Linha: '{linha}'")

    opcode_bin = OPCODES[instrucao_nome]
    

    if len(partes) != 3:
        raise ValueError(f"Formato inválido para '{instrucao_nome}'. Esperado '{instrucao_nome} Op1 Op2'.")
    
    op1_rd = registrar_para_binario(partes[1])
    
    if instrucao_nome in ["add", "sub", "mul", "not", "sll", "slr", "and", "or", "xor", 'ge', 'brzr', 'lw', 'sw']:
        op2_rs = registrar_para_binario(partes[2])
        return f"{opcode_bin}{op1_rd}{op2_rs}" 

    elif instrucao_nome in ["addi", "jalr", 'jal']:
        op2_imm = imediato_para_binario(partes[2], bits=4) 
        return f"{opcode_bin}{op1_rd}{op2_imm}" 
    

def main():
    arquivo_entrada_path = sys.argv[1]

    with open(arquivo_entrada_path, 'r') as f_in:
        for i, linha in enumerate(f_in):
            opcode_binario = processar_instrucao(linha)
            if opcode_binario:
                print(opcode_binario)


if __name__ == "__main__":
    main()
