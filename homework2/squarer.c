#include <stdio.h>
#include <math.h>

int main() {
    double n, lg;
    double cg;
    double diff;
    double x = 1e-10;
    scanf("%lf %lf", &n, &lg);

    while(1) {
        cg = 0.5 * (lg + (n/lg));
        diff = fabs(cg-lg);
        printf("%.10lf %.10lf %.10lf\n", cg, lg, diff);

        if (diff < x) {
            printf("%.10lf", cg);
            break;
        }

        lg = cg;
    }
    return 0;
}
