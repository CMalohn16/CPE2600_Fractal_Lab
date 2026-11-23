#include "jpegrw.h"

typedef struct {
    imgRawImage *img;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    int max;
} imgData;