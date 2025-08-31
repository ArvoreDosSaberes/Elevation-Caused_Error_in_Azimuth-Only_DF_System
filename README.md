# Elevation-Caused Error in Azimuth-Only DF System

Este projeto demonstra, em C, o erro de azimute causado pela elevação quando um sistema de Direction Finding mede apenas o ângulo no plano (M), ignorando a elevação.

Relações principais:
- cos(M) = cos(Az_true) · cos(El)
- Error = M − Az_true
- Alternativa (M conhecido): Az_true = arccos[ cos(M) / cos(El) ]

Componentes:
- Biblioteca: `include/df_error.h`, `src/df_error.c`
- Demo: `src/df_demo.c` (gera `error_surface.csv`)

## Build

```bash
cmake -S . -B build
cmake --build build -j
```

## Executar demo

```bash
./build/df_demo
```

Saída: `error_surface.csv` com colunas `az_deg, el_deg, m_deg, error_deg`.

## Visualização (opcional)
Use Python/Matplotlib para plotar a superfície (não incluído):

```python
import numpy as np, matplotlib.pyplot as plt
D = np.genfromtxt('error_surface.csv', delimiter=',', names=True)
az = D['az_deg']; el = D['el_deg']; err = D['error_deg']
# gerar grade e plotar conforme sua preferência
```
