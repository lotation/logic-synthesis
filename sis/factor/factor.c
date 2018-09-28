
/*
 *  factor: factoring routine
 *  routines provided:
 *      factor();
 */

#include "factor.h"
#include "factor_int.h"
#include "sis.h"

/*
 *  factors nodep if nodep->factored is not NULL.
 */
void factor(node_t *f) {
    if (f->factored == NIL(char)) {
        factor_quick(f);
    }
}

/*
 *   quick factoring
 */
void factor_quick(node_t *f) {
    node_t *np;

    factor_free(f);
    node_scc(f);
    np = node_dup(f);
    np->type = UNASSIGNED;
    factor_recur(np, factor_quick_kernel);
    f->factored = (char *) factor_nt_to_ft(f, np);
    factor_nt_free(np);
}

/*
 *   good factoring
 */
void factor_good(node_t *f) {
    node_t *np;

    factor_free(f);
    node_scc(f);
    np = node_dup(f);
    np->type = UNASSIGNED;
    factor_recur(np, factor_best_kernel);
    f->factored = (char *) factor_nt_to_ft(f, np);
    factor_nt_free(np);
}
