#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <stdio.h>
#include "df_error.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static inline float rad(float d){return d*(float)M_PI/180.0f;}
static inline float degf(float r){return r*180.0f/(float)M_PI;}

// Constrói vetor unitário a partir de Az (rad) e El (rad)
// Convenção igual ao projeto HUD: az = atan2(x, y); Z para cima
static Vector3 VecFromAzEl(float az, float el)
{
    float ch = cosf(el);
    return (Vector3){ sinf(az)*ch, cosf(az)*ch, sinf(el) };
}

// Desenha círculo no plano Z=0 com raio r
static void DrawGroundCircle(float r, Color col)
{
    const int N = 128;
    Vector3 prev = { r, 0, 0 };
    for (int i=1;i<=N;i++) {
        float t = (2.0f*(float)M_PI*i)/N;
        Vector3 cur = { r*cosf(t), r*sinf(t), 0 };
        DrawLine3D(prev, cur, col);
        prev = cur;
    }
}

// Desenha um arco no círculo do solo entre az1 e az2
static void DrawAzArc(float r, float az1, float az2, Color col)
{
    float d = az2 - az1;
    // normalizar para [-pi, pi]
    while (d > (float)M_PI) d -= 2.0f*(float)M_PI;
    while (d < -(float)M_PI) d += 2.0f*(float)M_PI;
    int steps = 64;
    float dt = d/steps;
    Vector3 prev = { r*sinf(az1), r*cosf(az1), 0 };
    for (int i=1;i<=steps;i++){
        float a = az1 + dt*i;
        Vector3 cur = (Vector3){ r*sinf(a), r*cosf(a), 0 };
        DrawLine3D(prev, cur, col);
        prev = cur;
    }
}

int main(void)
{
    const int W = 1280, H = 720;
    InitWindow(W, H, "DF Viz - Elevation-Caused Error in Azimuth-Only DF System");
    SetTargetFPS(60);

    Camera3D cam = {0};
    cam.position = (Vector3){ 3.2f, -4.5f, 2.5f };
    cam.target   = (Vector3){ 0.0f, 0.0f, 0.0f };
    cam.up       = (Vector3){ 0.0f, 0.0f, 1.0f };
    cam.fovy     = 60.0f;
    cam.projection = CAMERA_PERSPECTIVE;

    // Parâmetros controláveis
    float Az = rad(20.0f);  // verdadeiro
    float El = rad(20.0f);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        float step = rad(60.0f) * dt; // 60 deg/s

        // Controles
        // Az: A/D ; El: W/S ; Reset: R ; Câmera: mouse direito
        if (IsKeyDown(KEY_A)) Az -= step;
        if (IsKeyDown(KEY_D)) Az += step;
        if (IsKeyDown(KEY_W)) El += step;
        if (IsKeyDown(KEY_S)) El -= step;
        if (IsKeyPressed(KEY_R)) { Az = rad(20.0f); El = rad(20.0f); }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 d = GetMouseDelta();
            Matrix rotZ = MatrixRotate((Vector3){0,0,1}, -d.x*0.003f);
            Vector3 off = Vector3Subtract(cam.position, (Vector3){0,0,0});
            off = Vector3Transform(off, rotZ);
            Matrix rotX = MatrixRotate((Vector3){1,0,0}, d.y*0.003f);
            off = Vector3Transform(off, rotX);
            cam.position = off;
        }

        // Cálculos DF
        float M = (float)df_measured_angle(Az, El); // rad
        float Err = (float)df_azimuth_error(Az, El); // M - Az

        // Vetores
        Vector3 vTrue = VecFromAzEl(Az, El);
        Vector3 vMeas = VecFromAzEl(M, 0.0f); // medição assumindo El=0

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(cam);
        DrawGrid(20, 0.2f);
        // eixos
        DrawLine3D((Vector3){0,0,0}, (Vector3){1.5f,0,0}, RED);
        DrawLine3D((Vector3){0,0,0}, (Vector3){0,1.5f,0}, GREEN);
        DrawLine3D((Vector3){0,0,0}, (Vector3){0,0,1.5f}, BLUE);

        // Esfera unitária e círculo do solo
        DrawSphereWires((Vector3){0,0,0}, 1.0f, 16, 16, LIGHTGRAY);
        DrawGroundCircle(1.0f, GRAY);

        // Direções
        DrawLine3D((Vector3){0,0,0}, vTrue, MAROON);
        DrawLine3D((Vector3){0,0,0}, vMeas, DARKGREEN);
        DrawSphere(Vector3Scale(vTrue, 1.02f), 0.03f, MAROON);
        DrawSphere(Vector3Scale(vMeas, 1.02f), 0.03f, DARKGREEN);

        // Arco no solo entre Az e M (erro de azimute)
        DrawAzArc(1.0f, Az, M, ORANGE);

        EndMode3D();

        // HUD de texto
        char buf[256];
        snprintf(buf, sizeof(buf), "Az_true=%.1f°  El=%.1f°  M=%.1f°  Error=%.2f°",
                 degf(Az), degf(El), degf(M), degf(Err));
        DrawText(buf, 16, 16, 20, BLACK);
        DrawText("Controles: A/D=Az  W/S=El  R=reset  RMB=orbitar", 16, 42, 18, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
