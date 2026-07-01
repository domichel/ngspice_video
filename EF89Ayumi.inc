.SUBCKT EF89 1 2 3 4 ; A G2 G1 C;
*      Extract V3.000
* Model created: 21-Jan-2016
*
X1 1 2 3 4 PenthodeVDE 
+ PARAMS: MU=25.0 EX=1.418 kG1=328.3 KP=58.8 kVB=0.0 kG2=1199.3
+ MUb=7.8 EXb=0.978 svar=0.068
+ Ookg1mOokG2=.22E-02 Aokg1=.36E-06 alkg1palskg2=.22E-02 be=0.122 als=2.07 RGI=2000
+ CCG1=5.5P  CCG2=0.0p CPG1=0.002p  CG1G2=0.0p CCP=5.1P  ;
.ENDS
****************************************************
.SUBCKT PenthodeVDE 1 2 3 4; A G2 G1 C
*
* NOTE: LOG(x) is base e LOG or natural logarithm.
* For some Spice versions, e.g. MicroCap, this has to be changed to LN(x).
*
+ PARAMS: MU=25.0 EX=1.418 kG1=328.3 KP=58.8 kVB=0.0 kG2=1199.3
+ MUb=7.8 EXb=0.978 svar=0.068
+ Ookg1mOokG2=.22E-02 Aokg1=.36E-06 alkg1palskg2=.22E-02 be=0.122 als= 2.07 RGI=2000
+ CCG1=5.5P  CCG2=0.0p CPG1=0.002p  CG1G2=0.0p CCP=5.1P  ;
RE1  7 0  1MEG    ; DUMMY SO NODE 7 HAS 2 CONNECTIONS
E1   7 0  VALUE=
+{V(2,4)/KP*plog(1+EXP(KP*(1/MU+V(3,4)/SQRT(KVB+V(2,4)*V(2,4)))))}
E11 17 0  VALUE=
+{V(2,4)/KP*plog(1+EXP(KP*(1/MUb+V(3,4)/SQRT(KVB+V(2,4)*V(2,4)))))}
E20  9 0  VALUE = {(1-svar)*0.5*(PWR(V(7),EX)+PWRS(V(7),EX))+ svar*0.5*(PWR(V(17),EXb)+PWRS(V(17),EXb))}
E2   8 0 VALUE = {Ookg1mOokG2 + Aokg1*V(1,4) - alkg1palskg2*Exp(-be*V(1,4)*SQRT(be*V(1,4)))}
G1   1 4  VALUE = {V(9)*V(8)}
G2   2 4 VALUE = {V(9)/KG2 *(1+als*Exp(-be*V(1,4) * SQRT(be*V(1,4))))}
RCP  1 4  1G      ; FOR CONVERGENCE	A  - C
C1   3 4  {CCG1}   ; CATHODE-GRID 1	C  - G1
C4   2 4  {CCG2}   ; CATHODE-GRID 2	C  - G2
C5   2 3  {CG1G2}   ; GRID 1 -GRID 2	G1  - G2
C2   1 3  {CPG1}  ; GRID 1-PLATE	G1 - A
C3   1 4  {CCP}   ; CATHODE-PLATE	A  - C
R1   3 5  {RGI}   ; FOR GRID CURRENT	G1 - 5
D3   5 4  DX      ; FOR GRID CURRENT	5  - C
.MODEL DX D(IS=1N RS=1 CJO=10PF TT=1N)
.ENDS PenthodeVDE
****************************************************
