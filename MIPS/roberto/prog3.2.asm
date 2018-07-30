#programa 3.2 (pag 39 swbas)
#char fte[16]="abcd-efgh-ijkl-";
#char dst[32];
#int i;
#
#i = 0;
#while (fte[i] != '\0') {
#    dst[i] = fte[i];
#    i = i + 1;
#}
#dst[i] = '\0';

####

            la s0, fte
            la s1, dst
            li s2, 0                    # s2 = i = 0
            
loop:       add t0, s2, s0              # t0 <- i + &fte
            lbu t1, 0(t0)               # t1 <- fte[i]
            beq t1, $zero, fim          # if t1 == 0, pula para fim
            add t0, s2, s1              # t0 <- i + &dst
            sb  t1, 0(t0)               # dst[i] <- fte[i] 
            addi s2, s2, 1              # i = i + 1
            j loop                      # pula para loop

fim:        add t0, s2, s1
            sb $zero, 0(t0)
