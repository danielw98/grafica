#include <stdio.h>

typedef struct{
    int x;
    int y;
}Point2;

Point2 point[100];
int calcul(Point2 a, Point2 b)
{
    return a.x*b.y - a.y*b.x;
}
int vf_convexe_concave(Point2 a, Point2 b)
{
    static int valoare = 0;
    int valoare_nou;
    if(valoare == 0){
        valoare = calcul(a,b);
        return 1;
    }
    if(valoare != 0)
    {
        valoare_nou = calcul(a,b);
        if(valoare_nou*valoare < 0)
            return 0;
        return 1;
    }
    return 0;
}
int main()
{

    Point2 A = {.x = 1, .y = 1};
    Point2 B = {.x = 5, .y = 3};
    Point2 C = {.x = 3, .y = 5};
    Point2 M = {.x = 1, .y = 2};

    point[0] = A; point[1] = B; point[2] = M; point[3] = C;

    int concav = 0;
    for(int i = 0; i < 3; i++)
    {
        if(vf_convexe_concave(point[i],point[i+1]) == 0){
            concav = 1;
        }
        
    }
    if(vf_convexe_concave(point[3],point[0]) == 0)
        concav = 1;
    
    if(concav)
        printf("concav");
    else
        printf("convex");
}