#include <stdio.h>
 
 
typedef struct{
    float x;
    float y;
}Point;
 
void citeste_mouse(Point *p, int n){
    static int k = 0;
    if(k < n){
        //glVertex2f(p[k]->x,p[k]->y);
        k++;   
    }
}
 
/* A * x = b; x = A^(-1) * b;
 
  / xc-xd xb-xa \ * /s0\ = /xc-xa\
  \ yc-yd yb-ya /   \t0/   \yc-ya/
 
*/
 
void rezolva(float x[], float M_inversa[], float *b)
{
    x[0] = M_inversa[0] * b[0] + M_inversa[1] * b[1];
    x[1] = M_inversa[2] * b[0] + M_inversa[3] * b[1];
}
 
float inversa(float *M, float *M_inversa)
{
    float det = M[0]*M[3] - M[1]*M[2];
    M_inversa[0] =  M[3];
    M_inversa[1] = -M[1];
    M_inversa[2] = -M[2];
    M_inversa[3] =  M[0];
    return det;
}
 
void print_puncte(Point *A, Point *B, Point *C, Point *D){
  printf("Punctele:\n"
         "A = <%.0f, %.0f>\n"
         "B = <%.0f, %.0f>\n"
         "C = <%.0f, %.0f>\n"
         "D = <%.0f, %.0f>\n\n",
         A->x,A->y,B->x,B->y,C->x,C->y,D->x,D->y);
 
}
int se_intersecteaza(Point A, Point B, Point C, Point D)
{
  printf("\n**************************************************\n");
  print_puncte(&A,&B,&C,&D);
    float M[4] =
            {C.x - D.x, B.x - A.x,
       C.y - D.y, B.y - A.y};
 
    float x[2];
    float b[2] = {
          C.x - A.x,
              C.y - A.y
             };
 
    printf("Sistemul:\n"
           " %.1fs0 + %.1ft0 = %.1f\n"
           " %.1fs0 + %.1ft0 = %.1f\n\n",
        M[0],M[1],b[0],M[2],M[3],b[1]);
   
    float M_inversa[4];
   
    float det = inversa(M,M_inversa);
 
  if(det == 0){
      if(b[0] == b[1])
        printf("Punctele sunt coliniare!!!\n");
      else
        printf("Dreptele sunt paralele!!!\n");
      return -1;
  }
    rezolva(x,M_inversa,b);
   
    printf("Solutiile sunt: <s0,t0> = <%.1f/%.1f, %.1f/%.1f>\n",  x[0],det,x[1],det);
  printf("                <s0,t0> = <%.3f, %.3f>\n\n",x[0]/det,x[1]/det);
  float s0 = x[0]/det, t0 = x[1]/det;
  if(s0 <= 1 && s0 >= 0 && t0 <= 1 && t0 >= 0){
    printf("Dreptele se intersectaza!\n");
    Point P;
    P.x = (1-t0) * A.x + t0 * B.x;
    P.y = (1-t0) * A.y + t0 * B.y;
    printf("Punctul de intersectie: <%.3f,%.3f>\n\n", P.x,P.y);
    return 0;
  }
  else {
    printf("Nu se intersectaza segmentele, insa se intersectaza dreptele!\n");
    return -1;
  }
}
 
 
void linie_poligonala(Point *p, int nr){
  // deseneaza p[0]p[1]
  int autointersectie;
  for(int i = 2; i < nr; i++){
      autointersectie = 0;
      for(int j = 2; j< i; j++){
        if(se_intersecteaza(p[j-2],p[j-1],p[i-1],p[i]) != -1){
              printf("Intersectie datorata punctului P%d(%.0f,%.0f)\n",i,p[i].x,p[i].y);
              printf("Desenez diferit segmentul (%.2f,%.2f) -> (%.2f,%.2f)\n",p[i-1].x,p[i-1].y,
              p[i].x,p[i].y);
              autointersectie = 1;
              break;
        }
      }
  }
}
 
 
void initializeaza(Point *p){
  p[0].x = 0; p[0].y = 0;
  p[1].x = 0; p[1].y = 1;
  p[2].x = 0; p[2].y = 2;
  p[3].x = 2; p[3].y = 2;
  p[4].x = 2; p[4].y = 1;
  p[5].x = -1;p[5].y = 1.5;
  p[6].x = -1;p[6].y = 0.5;
  p[7].x = 2 ;p[7].y = 0.5;
}
int main(){
    //Point p[4];
    //citeste_mouse(p,4);
    Point A = {0,4}, B = {4,0}, C = {-1,-1}, D = {3,7};
    //int k1 = se_intersecteaza(A,B,C,D);
 
  Point X = {0,0}, Y = {1,1}, Z = {2,2}, T = {3,3};
  //int k2 = se_intersecteaza(X,Y,Z,T);
 
  Point Q = {0,0}, W = {1,1}, E = {1,0}, R = {2,1};
  //int k3 = se_intersecteaza(Q,W,E,R);
 
  Point M = {0,0}, N = {1,1}, O = {0,2}, P = {1,2};
  //int k4 = se_intersecteaza(M,N,O,P);
 
  Point pts[100];
  initializeaza(pts);
  linie_poligonala(pts,8);
    return 0;
}
