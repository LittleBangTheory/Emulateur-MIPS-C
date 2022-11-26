J 
JAL 
JR 
NOP
LUI $2, 4
LW 
ROTR $3, $2, 4 
SLL $4, $3, 5
SRL $5, $4, 2
SW 
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