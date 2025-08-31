# Tutorial

Este projeto gera e estuda o erro de azimute causado pela elevação em um sistema DF que mede apenas azimute aparente.

## Requisitos (Linux)
- build-essential
- cmake

## Compilar
```bash
cmake -S . -B build
cmake --build build -j
```

## Executar o demo
```bash
./build/df_demo
```
Gera `error_surface.csv` com colunas `az_deg, el_deg, m_deg, error_deg`.

## Plotar (opcional, Python)
```python
import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt('error_surface.csv', delimiter=',', names=True)
az = data['az_deg']; el = data['el_deg']; err = data['error_deg']

# Exemplo de mapa de calor simples (az vs el)
# Recria grade
az_unique = np.unique(az)
el_unique = np.unique(el)
AZ, EL = np.meshgrid(az_unique, el_unique)
ERR = err.reshape(len(el_unique), len(az_unique))

plt.figure(figsize=(7,4))
plt.pcolormesh(AZ, EL, ERR, shading='auto', cmap='coolwarm')
plt.colorbar(label='Error (deg)')
plt.xlabel('Az_true (deg)')
plt.ylabel('El (deg)')
plt.title('Elevation-Caused Error in Azimuth-Only DF System')
plt.tight_layout(); plt.show()
```
