ADDI $2, $0, 3
ADDI $4, $0, 1
AND $3, $2, $0
ADDI $4, $4, 1
BEQ $2, $4, -1
ADDI $2, $2, -1
BGTZ $2, 0, -1
BLEZ $2, 0, 1
ADDI $2, $2, 1
ADDI $4, $4, -1
BNE $2, $4, -1
OR $3, $2, $3
XOR $3, $4, $3
SLT $3, $2, $3

# EXPECTED_ASSEMBLY
# 20020005
# 401824
# 
#
#

# EXPECTED_FINAL_STATE
# $02: 5
# $03: 0
# 
#
#
