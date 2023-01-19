ADDI $2, $0, 4

ADDI $1, $0, 2
DIV $2, $1
J 8
#efuhds

SW $1, 0($2)
ADDI $3, $0, 12
ADDI $4, $0, 50
SW $3, 0($4)
LW $5, 0($2)
LW $6, 0($4)
