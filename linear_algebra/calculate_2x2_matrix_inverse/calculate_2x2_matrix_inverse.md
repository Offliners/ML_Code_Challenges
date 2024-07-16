# Calculate 2x2 Matrix Inverse
Difficulty: `medium`

## Description
The inverse of a matrix $A$ is another matrix, often denoted $A^{-1}$, such that:
```math
AA^{-1} = A^{-1}A = I
```

where $I$ is the identity matrix. For a 2x2 matrix:
```math
A = \begin{pmatrix} 
a & b \\ 
c & d 
\end{pmatrix}
```

The inverse is:
```math
A^{-1} = \frac{1}{\det(A)} \begin{pmatrix} 
d & -b \\ 
-c & a 
\end{pmatrix}
```

provided that the determinant $\det(A) = ad - bc$ is non-zero. If $\det(A) = 0$, the matrix does not have an inverse. This process is critical in many applications including solving systems of linear equations, where the inverse is used to find solutions efficiently.