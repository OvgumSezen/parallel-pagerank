import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('build/measurements.csv')

plt.figure(figsize=(10, 6))

variables = ['Time', 'Speedup', 'Efficiency', 'KuckFunction']

for var in variables:
    plt.plot(df['Processes'], df[var], marker='o', label=var)

plt.title('Performance Metrics vs Processes')
plt.xlabel('Processes')
plt.ylabel('Value')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
