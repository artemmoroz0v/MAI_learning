import numpy as np
import matplotlib.pyplot as plt
fig = plt.figure('Морозов Артем. 15 Вариант. Лабораторная работа №1', figsize=(7, 6))
plt.subplot(111, polar=True)
plt.title('ρ = a*cos(2ϕ)/cos(ф)')
phi = np.arange(-np.pi, np.pi, 0.05)
a = int(input())
rho = a*np.cos(2*phi)/np.cos(phi)
plt.plot(phi, rho, lw=2)
plt.show()
