#include <math.h>

static double clamp(double x) {
    if (x > 1.0) return 1.0;
    if (x < -1.0) return -1.0;
    return x;
}

double df_measured_angle(double az_true, double el) {
    // M = acos( cos(Az_true) * cos(El) )
    double x = clamp(cos(az_true) * cos(el));
    return acos(x);
}

double df_azimuth_error(double az_true, double el) {
    double M = df_measured_angle(az_true, el);
    return M - az_true;
}

double df_az_error_from_M(double M, double el) {
    // Error = M - acos( cos(M)/cos(El) )
    double denom = cos(el);
    double ratio = 0.0;
    if (fabs(denom) < 1e-12) {
        ratio = (M >= 0.0) ? 1.0 : -1.0;
    } else {
        ratio = cos(M) / denom;
    }
    ratio = clamp(ratio);
    double az_true = acos(ratio);
    return M - az_true;
}
