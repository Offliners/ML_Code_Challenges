# Calculate Covariance Matrix
Difficulty: `medium`

## Description
The covariance matrix is a fundamental concept in statistics, illustrating how much two random variables change together. It's essential for understanding the relationships between variables in a dataset. For a dataset with $n$ features, the covariance matrix is an $n×n$ square matrix where each element (i, j) represents the covariance between the $i^{th}$ and $j^{th}$ features. Covariance is defined by the formula:
```math
\text{cov}(X, Y) = \frac{{\sum_{i=1}^{n}} (x_i - \bar{x})(y_i - \bar{y})}{n-1}
```

Where: $X$ and $Y$ are two random variables (features), $x_i$ and $y_i$ are individual observations of $X$ and $Y$, $\bar{x}$ (x-bar) and $\bar{y}$ (y-bar) are the means of $X$ and $Y$, $n$ is the number of observations. In the covariance matrix: The diagonal elements (where $i=j$) indicate the variance of each feature. The off-diagonal elements show the covariance between different features. This matrix is symmetric, as the covariance between $X$ and $Y$ is equal to the covariance between $Y$ and $X$, denoted as $cov(X, Y) = cov(Y, X)$.