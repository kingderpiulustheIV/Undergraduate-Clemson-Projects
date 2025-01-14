//
// Created by sfarr on 2/27/2024.
//
#include <stdio.h>
#include <stdlib.h>

int main () {
    struct NODE{
        int a;
        struct NODE *b;
        struct NODE *c;
    };
    struct NODE nodes[5] = {
            {64, nodes + 2, NULL},
            {58, nodes + 4, nodes + 3},
            {95, NULL, nodes + 4},
            {43, nodes + 1, nodes},
            {88, nodes + 3, nodes + 1}
    };
    struct NODE *np = nodes + 2;
    struct NODE **npp = &nodes[1].b;
//    for (int i =0;  i < 5; i++) {
//        printf("nodes[%d].a\t%p\n", i, &nodes[i].a);
//        printf("nodes[%d].b\t%p\n", i, &nodes[i].b);
//        printf("nodes[%d].c\t%p\n", i, &nodes[i].c);
//
//    }
    printf("nodes\t%p\n", nodes);
    printf("nodes.a\tILLEGAL\n");
    printf("nodes[3].a\t%p\n", nodes[3].a);
    printf("nodes[3].c\t%p\n", nodes[3].c);
    printf("nodes[3].c->a\t%p\n", nodes[3].c->a);
    printf("*nodes.a\tILLEGAL\n");
    printf("(*nodes).a\t%p\n", (*nodes).a);
    printf("nodes->a\t%p\n", nodes->a);
    printf("nodes[3].b->b\t%p\n", nodes[3].b->b);
    printf("&nodes[3].a\t%p\n", &nodes[3].a);
    printf("&nodes[3].c\t%p\n", &nodes[3].c);
    printf("&nodes[3].c->a\t%p\n", &nodes[3].c->a);
    printf("&nodes->a\t%p\n", &nodes->a);
    printf("np\t%p\n", np);
    printf("np->a\t%p\n", np->a);
    printf("np->c->c->a\t%p\n", np->c->c->a);
    printf("npp\t%p\n", npp);
    printf("npp->a\tILLEGAL\n");
    printf("*npp\t%p\n", *npp);
    printf("*npp->a\tILLEGAL\n");
    printf("(*npp)->a\t%p\n", (*npp)->a);
    printf("&np\t%p\n", &np);
    printf("&np->a\t%p\n", &np->a);
    printf("&np->c->c->a\t%p\n", &np->c->c->a);

}