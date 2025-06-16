//ESSE CÓDIGO PODE NÃO ESTAR ATUALIZADO
//FOI USADO APENAS COMO BASE

void main(){
    int A[10], B[10], C[10], i;
    for(i=0; i<10; i++){
        A[i] = i;
        B[i] = 10-i;
    }
    for(i=0; i<10; i++)
        C[i] = A[i] + B[i];
}

// x1 = A vai da memoria 0 até 9
// x2 = B vai da memoria 10 até 19
// x3 = C vai da memoria 20 até 29
// x4 = i
// x5 = constante 10


addi x5 5
addi x5 5 
addi x15 5
mul x15 x15
add x2 x5
add x3 x2
add x3 x3
add x6 x4 
ge x6 x5
brzr x6 x15
add x7 x1 
add x7 x4 
sw x4 x7
addi x7 5
addi x7 5 
add x8 x5 
sub x8 x4 
sw x8 x7 
addi x4 1 
sub x6 x6
sub x7 x7
sub x8 x8
jalr x5 -3
fim_for
//x1, x2, x3 estão reservados
    for(i=0; i<10; i++)
        C[i] = A[i] + B[i];
//x5 = 10 
//x15 = 25
// x4 = i
// addi x15 5
// mul x15 x15
//COLOCAR QUANTO DE PULO NO x15
sub x4 x4 // i = 0
for:
jal x14 0
add x6 x4 
ge x6 x5
brzr x6 x15
add x7 x4 // x7 = &A[i]
lw x8 x7 // x8 = A[i]
add x7 x5 // x7 = &B[i]
lw x9 x7 // x9 = B[i]
add x7 x5 // x7 = &C[i]
add x8 x9 // x8 = A[i] + B[i]
sw x8 x7 // C[i] = A[i] + B[i]
addi x4 1 //i++
sub x6 x6
sub x7 x7 // x7 = 0
jalr x14 0



add t0 x0                 # add x8, x0                      # t0  -> x8
add s0 x0                 # add x12, x0                     # s0  -> x12
addi s1 5                 # addi x13, 5                     # s1  -> x13
addi s1 5                 # addi x13, 5
addi v0 5                 # addi x2, 5                      # v0  -> x2
mul v0 v0                 # mul x2, x2
addi v0 2                 # addi x2, 2
add t1 t0                 # add x9, x8                      # t1  -> x9
ge t1 s1                  # ge x9, x13
brzr t1 v0                # brzr x9, x2
add t2 s0                 # add x10, x12                    # t2  -> x10
add t2 t0                 # add x10, x8
sw t0 t2                  # sw x8, x10
add t2 s1                 # add x10, x13
add t3 s1                 # add x11, x13                    # t3  -> x11
sub t3 t0                 # sub x11, x8
sw t3 t2                  # sw x11, x10
addi t0 1                 # addi x8, 1
sub t1 t1                 # sub x9, x9
sub t2 t2                 # sub x10, x10
sub t3 t3                 # sub x11, x11
sub v1 v1                 # sub x3, x3                      # v1  -> x3
add v1 s1                 # add x3, x13
jalr v1 0                 # jalr x3, 0
sub t0 t0                 # sub x8, x8
addi v0 -2                # addi x2, -2
addi t1 1                 # addi x9, 1
slr v0 t1                 # slr x2, x9
jal v1 1                  # jal x3, 1
add t1 t0                 # add x9, x8
ge t1 s1                  # ge x9, x13
brzr t1 v0                # brzr x9, x2
add t2 t0                 # add x10, x8
lw t3 t2                  # lw x11, x10
add t2 s1                 # add x10, x13
lw t4 t2                  # lw x1, x10                      # t4  -> x1
add t2 s1                 # add x10, x13
add t3 t4                 # add x11, x1
sw t3 t2                  # sw x11, x10
addi t0 1                 # addi x8, 1
sub t1 t1                 # sub x9, x9
sub t2 t2                 # sub x10, x10
jalr v1 -1                # jalr x3, -1





