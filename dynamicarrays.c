#define REALLOC(p,s)\
 if (!((p)=realloc(p,s)))\
 { \
fprintf(stderr, "INsufficient memory"); \
exit(1);\
}
#define MALLOC(p, s) if (!((p)=malloc(p,s)))\
{\
fprintf(stderr,"insufficient memory");\
exit(1);\
}
