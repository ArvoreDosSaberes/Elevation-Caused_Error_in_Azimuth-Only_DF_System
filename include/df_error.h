#ifndef DF_ERROR_H
#define DF_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

// Elevation-Caused Error in Azimuth-Only DF System
// Fórmulas de referência:
//  - cos(M) = cos(Az_true) * cos(El)
//  - Error = M - Az_true
//  - Alternativo (M conhecido): Az_true = acos( cos(M) / cos(El) )

// Retorna M (rad) dado azimute verdadeiro (rad) e elevação (rad)
double df_measured_angle(double az_true, double el);

// Retorna o erro (rad): Error = M - Az_true
double df_azimuth_error(double az_true, double el);

// Versão quando se conhece M (medido) e El. Retorna Error = M - Az_true (rad)
// onde Az_true = acos( cos(M) / cos(El) )
double df_az_error_from_M(double M, double el);

#ifdef __cplusplus
}
#endif

#endif // DF_ERROR_H
