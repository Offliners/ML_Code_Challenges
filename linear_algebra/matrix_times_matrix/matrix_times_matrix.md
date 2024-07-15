# Matrix times Matrix
Difficulty: `easy`

## Description
Consider two matrices $A$ and $B$, to demonstrate their multiplication, defined as follows: Matrix $A$:
```math
A = \begin{pmatrix} 
a_{11} & a_{12} \\ 
a_{21} & a_{22} 
\end{pmatrix}
```
 
Matrix $B$:
```math
B = \begin{pmatrix} 
b_{11} & b_{12} \\ 
b_{21} & b_{22} 
\end{pmatrix}
```

The multiplication of matrix $A$ by matrix $B$ is calculated as:
```math
A \times B = \begin{pmatrix} 
a_{11}b_{11} + a_{12}b_{21} & a_{11}b_{12} + a_{12}b_{22} \\ 
a_{21}b_{11} + a_{22}b_{21} & a_{21}b_{12} + a_{22}b_{22} 
\end{pmatrix}
```
 
This operation results in a new matrix where each element is the result of the dot product between the rows of matrix $A$ and the columns of matrix $B$.