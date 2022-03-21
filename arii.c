#include <stdio.h>
#include <math.h>
typedef struct{
    int x;
    int y;
}Point2;


double getArea(Point2 a, Point2 b, Point2 c)
{
    double det1 = b.x*c.y - b.y*c.x;
    double det2 = a.x*c.y - a.y*c.x;
    double det3 = a.x*b.y - a.y*b.x;

    double area = (det1 - det2 + det3) / 2;
    return fabsf(area);
}
int main()
{
    Point2 A = {.x = 0, .y = 0};
    Point2 B = {.x = 5, .y = 0};
    Point2 C = {.x = 0, .y = 5};
    Point2 M = {.x = 2, .y = 3};
    double arie = getArea(A,B,C);

    double arie1 = getArea(A,M,B);
    double arie2 = getArea(B,M,C);
    double arie3 = getArea(A,M,C);

    double sum = arie1 + arie2 + arie3;
    printf("arie = %f\nsum = %f\n", arie, sum);
    return 0;
}