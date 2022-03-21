#include <stdio.h>


typedef struct{
    float x;
    float y;
    float z;
}Vector3;

typedef struct{
    float A;
    float B;
    float C;
    float D;
}Plane;
/*
    | i   k  j |
    | a0 a1 a2 |
    | b0 b1 b2 |
*/
Plane calcul_ecuatia_planului(Vector3 p1, Vector3 p2, Vector3 p3){
   Plane plane;

   plane.A = p1.y*(p2.z - p3.z) - p1.z * (p2.y - p3.y) + p2.y*p3.z - p3.y * p2.z;
   plane.B = (-1)*(p1.x*(p2.z-p3.z) - p1.z * (p2.x - p3.x) + p2.x*p3.z - p3.x * p2.z);
   plane.C = (p1.x*(p2.y-p3.y) - p1.z * (p2.x - p3.x) + p2.x*p3.y - p3.x * p2.y);
   plane.D = (-1)*(p1.x*(p2.y*p3.z - p2.z*p3.y) - p2.x* (p1.y*p3.z-p3.y*p1.z) + p3.x * (p1.y*p2.z-p2.y*p1.z));
   printf("A = %f\n",plane.A);
   printf("B = %f\n",plane.B);
   printf("C = %f\n",plane.C);
   printf("D = %f\n",plane.D);
   return plane;
}


void Pozitie_Punct(Vector3 v, Plane p)
{
    float rez = v.x * p.A + v.y * p.B + v.z * p.C + p.D;
    printf("Punctul (%f, %f, %f)\n",v.x,v.y,v.z);
    if(rez == 0)
        printf("Punctul se afla in plan\n");
    if(rez > 0)
        printf("Punctul se afla in fata planului\n");
    if(rez < 0)
        printf("Punctul se afla in spatele planului\n");
}
void print_vector(Vector3 v)
{
    printf("(%f, %f, %f)\n", v.x, v.y, v.z);
}

void read_vector(Vector3 *v)
{
    printf("x = ");
    scanf("%f", &v->x);
    printf("y = ");
    scanf("%f", &v->y);
    printf("z = ");
    scanf("%f", &v->z);
}
int main()
{
    Vector3 v1 = {.x = 1, .y = 2, .z = 0};
    Vector3 v2 = {.x = 2, .y = 0, .z = 4};
    Vector3 v3 = {.x = 1, .y = 1, .z = 1};
    //read_vector(&v1);
    //read_vector(&v2);
    //read_vector(&v3);
    Plane plane  = calcul_ecuatia_planului(v1,v2,v3);
    Pozitie_Punct((Vector3){.x = -10, .y = -10, .z = -10}, plane);


}
