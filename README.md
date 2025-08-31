[![CI](https://github.com/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System/actions/workflows/ci.yml/badge.svg)](https://github.com/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System/actions/workflows/ci.yml)
![visitors](https://visitor-badge.laobi.icu/badge?page_id=ArvoreDosSaberes.Elevation-Caused_Error_in_Azimuth-Only_DF_System)
[![License: CC BY-SA 4.0](https://img.shields.io/badge/License-CC_BY--SA_4.0-blue.svg)](https://creativecommons.org/licenses/by-sa/4.0/)
![Language: Portuguese](https://img.shields.io/badge/Language-Portuguese-brightgreen.svg)
[![Language-C](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![CMake](https://img.shields.io/badge/build-CMake-informational.svg)](https://cmake.org/)
[![Raylib](https://img.shields.io/badge/graphics-raylib-2ea44f.svg)](https://www.raylib.com/)
[![Issues](https://img.shields.io/github/issues/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System.svg)](https://github.com/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System/issues)
[![Stars](https://img.shields.io/github/stars/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System.svg)](https://github.com/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System/stargazers)
[![Forks](https://img.shields.io/github/forks/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System.svg)](https://github.com/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System/network/members)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](https://makeapullrequest.com)
[![Watchers](https://img.shields.io/github/watchers/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System)](https://github.com/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System/watchers)
[![Last Commit](https://img.shields.io/github/last-commit/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System)](https://github.com/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System/commits)
[![Contributors](https://img.shields.io/github/contributors/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System)](https://github.com/ArvoreDosSaberes/Elevation-Caused_Error_in_Azimuth-Only_DF_System/graphs/contributors)


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
