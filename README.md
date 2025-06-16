# Descritivo Técnico da ISA (Instruction Set Architecture)

## Arquitetura Geral
*   **Tamanho da Palavra/Instrução:** 12 bits.
*   **Número de Registradores:** 16 registradores de 12 bits (R0 a R15).
*   **Formatos de Instrução:** Tipo-R e Tipo-I, ambos com 12 bits de comprimento.

## Formatos de Instrução

### 1. Formato Tipo-R (Registrador)
Utilizado por instruções que operam primariamente entre dois registradores.

**Estrutura:**


|Bits: | 11 10 9 8 | 7 6 5 4 | 3 2 1 0 |
|---- | ---- | ---- | --- |
|Campo: |OPCODE|RS1|RS2|

*   **OPCODE (4 bits):** Define a operação (ex: `add`, `sub`, `and`).
*   **RS1 (4 bits):** Identifica o primeiro registrador fonte (`ra`), que também é, na maioria dos casos, o registrador de destino.
*   **RS2 (4 bits):** Identifica o segundo registrador fonte (`rb`).

### 2. Formato Tipo-I (Imediato)
Utilizado por instruções que operam com um valor imediato.

**Estrutura:**
|Bits: | 11 10 9 8 | 7 6 5 4 | 3 2 1 0 |
|----|----|---|--|
|Campo: |OPCODE|RS1|IMM|
*   **OPCODE (4 bits):** Define a operação (ex: `addi`, `jal`).
*   **RS1 (4 bits):** Identifica o registrador fonte/destino (`ra`).
*   **IMM (4 bits):** Valor imediato de 4 bits.

---

### Extensão de Sinal para Imediatos (IMM)
O campo `IMM` de 4 bits deve ser estendido para 12 bits para operações aritméticas e de salto. A extensão de sinal garante que números negativos (em complemento de dois) sejam tratados corretamente.

*   **Regra:** O bit 3 (o mais significativo do campo `IMM`) é replicado nos 8 bits mais altos da palavra de 12 bits.
*   **Exemplo (Positivo `+5`):** `IMM = 0101` -> Estendido para `0000 0000 0101`.
*   **Exemplo (Negativo `-3`):** `IMM = 1101` -> Estendido para `1111 1111 1101`.

### Comportamento de Saltos e Desvios
*   **`jal ra, imm`:** O PC (Program Counter) é atualizado para `PC + Imm` (onde `Imm` é o valor de 4 bits com extensão de sinal). O endereço da *próxima* instrução (`PC+1`) é salvo em `ra` para permitir o retorno.
*   **`jalr ra, imm`:** O PC é atualizado para `R[ra] + Imm`. O endereço de retorno `PC+1` é salvo em `ra`. Esta instrução é útil para retornos de função ou loops.
*   **`brzr ra, rb`:** O PC é atualizado para o valor contido em `R[rb]` somente se `R[ra]` for zero. É um desvio condicional para um endereço absoluto contido em um registrador.
*   **`ge ra, rb`:** Mesmo não sendo um salto, `ge` pode ser usado para facilitar condições de salto, em que se `R[ra] >= R[rb]`, `R[ra]` recebe 0, se não, `R[ra]` recebe 1. Podendo ser combinada com o `brzr` 


# Green Card (Cartão de Referência Rápida)

| Mnemônico | Opcode | Tipo | Sintaxe de Exemplo | Descrição da Operação |
| :--- | :--- | :--- | :--- | :--- |
| **add** | 0000 (0) | R | `add ra, rb` | **Soma**: `R[ra] = R[ra] + R[rb]` |
| **addi** | 0001 (1) | I | `addi ra, imm` | **Soma com Imediato**: `R[ra] = R[ra] + Imm` (com extensão de sinal) |
| **jal** | 0010 (2) | I | `jal ra, imm` | **Salto e Link**: Salva o endereço de retorno (`PC+1`) em `ra` e salta para o endereço `PC + Imm`. |
| **jalr** | 0011 (3) | I | `jalr ra, imm` | **Salto e Link com Registrador**: Salva `PC+1` em `ra` e salta para `R[ra] + Imm`. |
| **brzr** | 0100 (4) | R | `brzr ra, rb` | **Desvio se Zero**: Se `R[ra] == 0`, então `PC = R[rb]`. |
| **ge** | 0101 (5) | R | `ge ra, rb` | **Maior ou Igual (Set)**: Se `R[ra] >= R[rb]`, `R[ra] = 0`; senão, `R[ra] = 1`. |
| **sw** | 0110 (6) | R | `sw ra, rb` | **Store Word**: Armazena `R[ra]` no endereço de memória `M[R[rb]]`. |
| **lw** | 0111 (7) | R | `lw ra, rb` | **Load Word**: Carrega `R[ra]` com o dado do endereço de memória `M[R[rb]]`. |
| **sub** | 1000 (8) | R | `sub ra, rb` | **Subtração**: `R[ra] = R[ra] - R[rb]` |
| **mul** | 1001 (9) | R | `mul ra, rb` | **Multiplicação**: `R[ra] = R[ra] * R[rb]` |
| **slr** | 1010 (10) | R | `slr ra, rb` | **Shift Lógico à Esquerda**: `R[ra] = R[ra] << R[rb]` |
| **srr** | 1011 (11) | R | `srr ra, rb` | **Shift Lógico à Direita**: `R[ra] = R[ra] >> R[rb]` |
| **not** | 1100 (12) | R | `not ra, rb` | **Negação**: `R[ra] = not R[rb]`. |
| **or** | 1101 (13) | R | `or ra, rb` | **OU**: `R[ra] = R[ra] v R[rb]` |
| **and** | 1110 (14) | R | `and ra, rb` | **E**: `R[ra] = R[ra] & R[rb]` |
| **xor** | 1111 (15) | R | `xor ra, rb` | **OU Exclusivo**: `R[ra] = R[ra] ^ R[rb]` |


# Modelo de Programação e Convenção de Registradores

A convenção a seguir define o propósito de cada um dos 16 registradores da arquitetura, facilitando a operação entre diferentes partes de um programa (ex: funções).

| Número | Nome (ABI) | Função Principal | Tipo (Convenção) |
| :--- | :--- | :--- | :--- |
| **R0** | `zero` | Fixo em zero. Fonte de valor 0 constante. | - |
| **R1** | `t4` | **Temporário** de uso geral. | Temporário |
| **R2** | `v0` | **Valor de Retorno** de funções. | Temporário |
| **R3** | `v1` | **Valor de Retorno** secundário de funções. | Temporário |
| **R4** | `a0` | **Argumento 1** de função. Pode ser usado como registrador de link (`ra`) em `jal`. | Temporário |
| **R5** | `a1` | **Argumento 2** de função. | Temporário |
| **R6** | `a2` | **Argumento 3** de função. | Temporário |
| **R7** | `a3` | **Argumento 4** de função. | Temporário |
| **R8** | `t0` | **Temporário** de uso geral. | Temporário |
| **R9** | `t1` | **Temporário** de uso geral. | Temporário |
| **R10**| `t2` | **Temporário** de uso geral. | Temporário |
| **R11**| `t3` | **Temporário** de uso geral. | Temporário |
| **R12**| `s0` | **Salvo**. Deve ser preservado pela função chamada. | Salvo |
| **R13**| `s1` | **Salvo**. Deve ser preservado pela função chamada. | Salvo |
| **R14**| `s2` | **Salvo**. Deve ser preservado pela função chamada. | Salvo |
| **R15**| `sp` | **Ponteiro de Pilha** (`Stack Pointer`). | Salvo |

## Descrição da Convenção

*   **Temporário :** Registradores `t0-t3`, `a0-a3`, `v0-v1`. Quando chamada uma função, não se pode esperar que os valores nesses registradores sejam mantidos. Se precisar deles, deve salvá-los antes da chamada.
*   **Salvo :** Registradores `s0-s1`, `fp`, `sp`. Uma função que é chamada deve garantir que os valores nesses registradores permaneçam os mesmos ao retornar. Se a função chamada precisar usá-los, ela deve primeiro salvar seus valores originais (geralmente na pilha) e restaurá-los antes de sair.
*   **Pilha :** A pilha deve ser iniciada pelo **usuário** no começo da aplicação. Uma simples instrução `addi sp -1` já a deixará pronta para uso caso necessário.

# Escolhas para a ISA

Um descritivo, explicando todas as decisões de projeto, bem como o funcionamento de cada unidade funcional da microarquitetura

A maioria das implementações foram inspiradas na arquitetura REDUX V, mas há algumas diferenças:

* `ge`: função pensada para maior facilidade na hora de criar `ifs/loops`,  `ge rs1 rs2` faz que rs1 seja 0 caso `rs1 > rs2`, senão ` rs2 = 1 `
* `mul`: para maior facilidade de realizar operações de multiplicação.
* `jal e jalr`: pensados para melhor controle do fluxo do programa, em `jal` o PC é salvo em rs1 e PC recebe `PC + imm`. Em jalr, PC recebe `rs1 + imm` e rs1 recebe `PC + 1`.
* `lw`: havia erro quando usado o lw pois o valor escrito no rs1 era o do `&rs2` da instrução anterior, por causa da batida do clock "atrasada". Para resolver isso, foi implementado uma memória com `flip-flop` para que a função lw dure 2 batidas do clock. Essa memória faz com que o PC permaneça igual na primeira batida e na próxima volte ao fluxo normal do programa com `PC + 1`. Circuito `sel_lw`.
* `ULA`: similar a do REDUX V, diferença é que precisa de 4 bits de seleção pois realiza 9 operações diferentes (mul de adicional). Dessa forma, ela foi adaptada para funcionar com o `opcode` sendo o seletor. 
* `MUX seletor para o D de BREG`: Foram implementados 4 opções para o `MUX_BREG`:
    * `00`: D recebe resultado da ULA
    * `01`: D recebe dado da memória (Apenas no `load` de dados)
    * `10`: D recebe `0/1`, utilizado no `ge` 
    * `11`: D recebe `PC+1`, utilizado em `jal` e `jalr`
* `PC`: Pode reber 4 opções:
    * `00`: `PC+1` em casos padrões ou `PC` em caso de `load`
    * `01`: `PC+imm` em `jal`
    * `10`: `rs1 + imm` em `jalr`
    * `11`: `PC+1` ou `rs2` em `brzr`

Uma listagem de todos os componentes usados, por exemplo:

## Componentes usados

* `PC`: registrador 12 bits
* `Código`: ROM dados 12 bits e entrada 12 bits
* `Unidade de Controle`: ROM dados 7 bits e entrada 4 bits
* `Banco de registradores`: 15 registradores 12 bits e constante 0
* `Memória`: RAM dados 12 bits e entrada 12 bits
* Outros:
    * Flip-flop
    * Comparador
    * Portas lógicas
    * Operadores aritméticos

# Tradução do Código

Foram utilizados códigos em `python` para tradução dos arquivos do Código, um para transformar as instruções em binário e o outro para transformar de binário para hexadecimal. Este segundo também foi usado para a Unidade de Controle. 

Código formatado para entrada no `cod-bin.py` é escrito manualmente, após isso é realizado:

`python3 .\cod-bin.py programatxt.txt > programaBIN.txt`
`python3 .\bin-hex.py programaBIN.txt > rom.txt`

Assim, `rom.txt` possui o código pronto para o circuito da ISA.

### Estão sendo entregues:
* Circuito da ISA: `trabIsa12bits.circ` 
* Códigos python:
    * 1- `cod-bin.py`
    * 2- `bin-hex.py`
* Tabela de instruções: `ISA PROJETOS.pdf`
* Unidade de controle:
    * `txtISABin.txt` instruções em binário
    * `ucISA12bits.txt` instruções em hexadecimal (usado na ROM)
* Tradução do código:
    * `programaISA.c`: rascunho do código
    * `programatxt.txt`: código formatado para o programa python
    * `programaBIN.txt`: código em binário, saída do programa `1`
    * `rom.txt`: código em hexadecimal, saída programa `2` (usado na ROM)

Algum arquivo pode estar desatualizado (principalmente de rascunho), mas os finais em hexadecimal estão certos.