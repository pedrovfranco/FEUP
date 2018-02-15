.data
dim: .word 7 # Número de elementos da sequência
V: .word 3, -5, 21, 2, -10, 50, 9 # Sequência
.text
la $s0, V # Inicializa registos para
lw $t0, dim # percorrer sequência
lw $t1, 0($s0) # Max inicial
ciclo: addi $t0, $t0, -1 # Atualiza número de elementos que falta aceder
beq $t0, $zero, escreve # Se percorreu todos, escreve e termina
addi $s0, $s0, 4 # Atualiza endereço para ler próximo elemento
lw $t2, 0($s0) # Elemento atual
slt $t3, $t1, $t2 # $t3=1 indica que foi encontrado novo máximo
beq $t3, $zero, salta
add $t1, $t2, $zero # Atualiza máximo
salta: j ciclo
escreve: