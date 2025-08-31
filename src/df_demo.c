#include <stdio.h>
#include <math.h>
#include "df_error.h"

int main(void) {
    const double PI = 3.14159265358979323846;
    const double deg2rad = PI / 180.0;
    const double rad2deg = 180.0 / PI;

    const double el_min_deg = 0.0, el_max_deg = 60.0, el_step_deg = 1.0;
    const double az_min_deg = -180.0, az_max_deg = 180.0, az_step_deg = 1.0;

    FILE *f = fopen("error_surface.csv", "w");
    if (!f) {
        perror("fopen");
        return 1;
    }
    fprintf(f, "az_deg,el_deg,m_deg,error_deg\n");

    for (double el_deg = el_min_deg; el_deg <= el_max_deg + 1e-9; el_deg += el_step_deg) {
        double El = el_deg * deg2rad;
        for (double az_deg = az_min_deg; az_deg <= az_max_deg + 1e-9; az_deg += az_step_deg) {
            double Az = az_deg * deg2rad;
            double M = df_measured_angle(Az, El);
            double err = M - Az;
            fprintf(f, "%.6f,%.6f,%.6f,%.6f\n", az_deg, el_deg, M * rad2deg, err * rad2deg);
        }
    }

    fclose(f);
    printf("CSV gerado: error_surface.csv\n");
    return 0;
}
