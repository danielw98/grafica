#include <stdio.h>


typedef struct{
    float x;
    float y;
    float z;
}Vector3;

/*
    | i   k  j |
    | a0 a1 a2 |
    | b0 b1 b2 |
*/
Vector3 calcul_produs_vectorial(Vector3 a, Vector3 b){
   Vector3 V;
   V.x = a.y*b.z - a.z*b.y;
   V.y = a.z*b.x - a.x*b.z;
   V.z = a.x*b.y - a.y*b.x;
   return V;
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
    Vector3 v1;
    Vector3 v2;
    read_vector(&v1);
    read_vector(&v2);
    Vector3 v3  = calcul_produs_vectorial(v1,v2);

    print_vector(v3);
}
