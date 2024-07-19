# Single Neuron
Difficulty: `easy`

## Description
This task involves a neuron model designed for binary classification with multidimensional input features, using the sigmoid activation function to output probabilities. It also involves calculating the mean squared error (MSE) to evaluate prediction accuracy.

### Mathematical Background
* Neuron Output Calculation:
```math
z = \sum (weight_i \times feature_i) + bias
```

```math
\sigma(z) = \frac{1}{1 + e^{-z}}
```
 
* MSE Calculation:
```math
MSE = \frac{1}{n} \sum (predicted - true)^2
```
 
Where:
* $z$ is the sum of weighted inputs plus bias,
* $\sigma(z)$ is the sigmoid activation output,
* $predicted$ are the probabilities after sigmoid activation,
* $true$ are the true binary labels.

### Practical Implementation
* Each feature vector is processed to calculate a combined weighted sum, which is then passed through the sigmoid function to determine the probability of the input belonging to the positive class.
* MSE provides a measure of error, offering insights into the model's performance and aiding in its optimization.