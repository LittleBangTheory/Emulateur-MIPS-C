J 2
ADDI $2, $0, 3
JAL 2  
JR $2
NOP
LUI $2, 4
LW $2, 2($2)
ROTR $3, $2, 4 
SLL $4, $3, 5
SRL $5, $4, 2
SW $5, 2($2)
SYSCALL

# EXPECTED_ASSEMBLY
# 
# 
# 
#
#

# EXPECTED_FINAL_STATE
# 
# 
# 
#
#