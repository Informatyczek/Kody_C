#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <math.h>

struct point_t
{
    int x;
    int y;
};

struct rectangle_t
{
    struct point_t p;
    int width;
    int height;
};

struct circle_t
{
    struct point_t c;
    float r;
};

struct triangle_t
{
    struct point_t p1;
    struct point_t p2;
    struct point_t p3;
};
enum figure_types{
    TRIANGLE = 1,
    RECTANGLE,
    CIRCLE
};
struct figure_t{
    union
    {
        struct rectangle_t rect;
        struct triangle_t triangle;
        struct circle_t circ;
    };
    enum figure_types type;
};
int Can_build_triangle(const struct figure_t *figure);
float area_triangle(const struct triangle_t *t);
float area_rectangle(const struct rectangle_t *r);
float area_circle(const struct circle_t *c);
float area_figure(const struct figure_t *f);

void display_rectangle(const struct rectangle_t *rect);
void display_triangle(const struct triangle_t *t);
void display_circle(const struct circle_t *circ);
void display_figure(struct figure_t *f);
int sort_by_area(struct figure_t **figures, int size);


int main() {
    const int maks_dl=50;
    struct figure_t figures[50];
    int figures_count=0;

    int figure_type;
    char cc;
    int incorrect_data = 0;
    while(figures_count <= maks_dl){

        printf("Podaj typ figury: ");
        if(scanf("%d", &figure_type) != 1) {
            printf("Incorrect input");
            return 1;
        }//pobieram figure

        if(figure_type==0) break; // koncze petle dla 0

        if(!(figure_type==1 || figure_type==2 || figure_type==3 || figure_type==0)){
            printf("Incorrect input data");
            return 2;
        }//sprawdzam czy podano jedna z opcji

        if(figure_type == 1){
            printf("Enter vertices' coordinates of a triangle (x1 y1 x2 y2 x3 y3): ");
            if(scanf("%d %d %d %d %d %d",&((*(figures+figures_count)).triangle.p1.x) , &((*(figures+figures_count)).triangle.p1.y), &((*(figures+figures_count)).triangle.p2.x), &((*(figures+figures_count)).triangle.p2.y), &((*(figures+figures_count)).triangle.p3.x), &((*(figures+figures_count)).triangle.p3.y))!=6){
                printf("Incorrect input");
                return 1;
            }
            if (Can_build_triangle((figures+figures_count - 1)) == 0) {
                  incorrect_data=1;
            }

            (figures+figures_count)->type = TRIANGLE;
        } // pobranie wspolrzednych trojkata

        if(figure_type == 2) {
            printf("Enter coordinates of a rectangle along with its dimensions (x y width height): ");
            if(scanf("%d %d %d %d", &((*(figures+figures_count)).rect.p.x), &((*(figures+figures_count)).rect.p.y), &((*(figures+figures_count)).rect.width), &((*(figures+figures_count)).rect.height))!=4){
                printf("Incorrect input");
                return 1;
            }
            if(((*(figures+figures_count)).rect.width)<0 || ((*(figures+figures_count)).rect.height<0)){
                incorrect_data=1;
            }
            (figures+figures_count)->type = RECTANGLE;
        }// pobranie wspolrzednych prostokata

        if (figure_type == 3){
            printf("Enter coordinates and radius of a circle(x y r): ");
            if(scanf("%d %d %f", &((*(figures+figures_count)).circ.c.x), &((*(figures+figures_count)).circ.c.y), &((*(figures+figures_count)).circ.r))!=3){
                printf("Incorrect input");
                return 1;
            }
            if(((*(figures+figures_count)).circ.r)<0){
                incorrect_data=1;
            }
            (figures+figures_count)->type = CIRCLE;
        }// pobranie wspolrzednych kola

        figures_count++;
        while ((cc = getchar()) != '\n' && cc != '\0');
        if(figures_count==50){
            break;
        }
    }
    if(incorrect_data==1){
        printf("Incorrect input data");
        return 2;
    }

    struct figure_t *figure_pointers[50]; // Tablica wskaźników do struktur figure_t

    // Inicjalizacja tablicy wskaźników
    for (int i = 0; i < figures_count; i++) {
        *(figure_pointers+i) = &(*(figures+i)); // Przypisanie adresów struktur do tablicy wskaźników
    }
    if(sort_by_area( figure_pointers, figures_count)!=0){
        printf("Incorrect input\n");
        return 1;
    }

    for (int i = 0; i < figures_count; i++) {
        display_figure(*(figure_pointers + i));
    }

    return 0;
}


int Can_build_triangle(const struct figure_t *figure) {
    int x1 = figure->triangle.p1.x;
    int x2 = figure->triangle.p2.x;
    int x3 = figure->triangle.p3.x;
    int y1 = figure->triangle.p1.y;
    int y2 = figure->triangle.p2.y;
    int y3 = figure->triangle.p2.y;


    if ((x1 == x2 && y1 == y2) || (x2 == x3 && y2 == y3) || (x3 == x1 && y3 == y1)) {
        return 0; // Jeśli co najmniej dwa punkty są takie same, nie można zbudować trójkąta
    }
    return 1;
}

float area_triangle(const struct triangle_t *t) {
    if(t==NULL) return -1;
    if (t->p1.x == t->p2.x && t->p1.y == t->p2.y) {
        return -1;
    }
    if (t->p2.x == t->p3.x && t->p2.y == t->p3.y) {
        return -1;
    }
    if (t->p3.x == t->p1.x && t->p3.y == t->p1.y) {
        return -1;
    }


    float bok0 = pow(pow(t->p1.x - t->p2.x, 2) + pow(t->p1.y - t->p2.y, 2),0.5);
    float bok1 = pow(pow(t->p2.x - t->p3.x, 2) + pow(t->p2.y - t->p3.y, 2),0.5);
    float bok2 = pow(pow(t->p3.x - t->p1.x, 2) + pow(t->p3.y - t->p1.y, 2),0.5);

    float boki_pol = (bok0 + bok1 + bok2) / 2.00;

//    float liczbunika=sqrt(boki_pol * (boki_pol - bok0) * (boki_pol - bok1) * (boki_pol - bok2));
//    liczbunika = round(liczbunika * 10000) / 10000;
    return sqrt(boki_pol * (boki_pol - bok0) * (boki_pol - bok1) * (boki_pol - bok2));
}


float area_rectangle(const struct rectangle_t *r) {
    if(r==NULL) return -1;
    if (r->width <= 0 || r->height <= 0) {
        return -1;
    }

    return (float)r->width * (float)r->height;
}


float area_circle(const struct circle_t *c) {
    if(c==NULL || c->r<=0){
        return -1.000;
    }
    float polunko = M_PI * c->r * c->r;

    return polunko;
}

void display_rectangle(const struct rectangle_t *rect) {
    if (rect==NULL){
        return;
    }
    printf("Rectangle (%d, %d), width = %d, height = %d\n",rect->p.x, rect->p.y, rect->width, rect->height);

}
void display_triangle(const struct triangle_t *t) {
    if (t==NULL){
        return;
    }
    printf("Triangle p1(%d, %d), p2(%d, %d), p3(%d, %d)\n",t->p1.x, t->p1.y, t->p2.x, t->p2.y, t->p3.x, t->p3.y);
}
void display_circle(const struct circle_t *circ) {
    if (circ==NULL){
        return;
    }
    printf("Circle (%d, %d), radius = %f\n", circ->c.x, circ->c.y, circ->r);
}

void display_figure(struct figure_t *f) {
    if(f==NULL) return;
    switch(f->type) {
        case 1:
            display_triangle((struct triangle_t *) &f->triangle);
            break;
        case 2:
            display_rectangle((struct rectangle_t *) &f->rect);
            break;
        case 3:
            display_circle((struct circle_t *) &f->circ);
            break;
    }

}


float area_figure(const struct figure_t *f){
    if(f==NULL) return -1;
    if(f->type<0 || f->type>3) return -1;

    if(f->type==1){
        float farbka = area_triangle((const struct triangle_t *) &f->rect);
        if(farbka==-1){
            return -1;
        }
        return farbka;
    }
    if(f->type==2){
        float farbka = area_rectangle((const struct rectangle_t *) &f->triangle);
        if(farbka==-1){
            return -1;
        }
        return farbka;
    }
    if(f->type==3){
        float farbka = area_circle((const struct circle_t *)&f->circ);
        if(farbka==-1){
            return -1;
        }
        return farbka;
    }
    return 0;
}


int sort_by_area(struct figure_t **figures, int size){
    if(figures==NULL) return 1;
    if(size<=0) return 1;

    for (int i = 0; i < size-1; ++i){
        for (int j = i+1; j < size; j++){
            if(area_figure( *(figures + i))==-1){
                return 1;
            }
            if(area_figure( *(figures + j))==-1){
                return 1;
            }
            if (area_figure( *(figures + j)) > area_figure( *(figures + i))) {
                struct figure_t *przydupas = *(figures+i);
                *(figures+i) = *(figures+j);
                *(figures+j) = przydupas;
            }
        }
    }

    return 0;
}