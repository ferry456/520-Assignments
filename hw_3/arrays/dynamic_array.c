#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}


/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_copy(da);
    for ( int i=0; i<DynamicArray_size(result); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(result, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

  assert(da->buffer != NULL);
  assert(b >= a);

  DynamicArray * result = DynamicArray_new();

  for (int i=a; i<b; i++) {
      DynamicArray_push(result,DynamicArray_get(da, i));
  }

  return result;

}

double DynamicArray_min ( const DynamicArray * da ){
    assert (da -> buffer != NULL);
    double temp = DynamicArray_get(da , DynamicArray_size(da) -1);
    for (int i = 0; i < DynamicArray_size(da); i++){
        if (DynamicArray_get(da , i) < temp){
            temp = DynamicArray_get(da , i);
        }
    }
    return temp;
}

double DynamicArray_max ( const DynamicArray * da ){
    assert (da -> buffer != NULL);
    double temp = DynamicArray_get(da , DynamicArray_size(da) - 1);
    for (int i = 0; i < DynamicArray_size(da); i++){
        if (DynamicArray_get(da, i) > temp){
            temp = DynamicArray_get(da , i);
        }
    }
    return temp;
}

double DynamicArray_mean ( const DynamicArray * da ){
    assert (da -> buffer != NULL);
    double temp = 0.0;
    for (int i = 0; i < DynamicArray_size(da); i++){
        temp = temp + DynamicArray_get(da , i);
    }
    return temp/DynamicArray_size(da);
}

double DynamicArray_median ( const DynamicArray * da ){
    assert (da -> buffer != NULL);
    double temp;
    double re;
    double a[DynamicArray_size(da)];
    for (int i = 0; i < DynamicArray_size(da); i++){
        a[i] = DynamicArray_get(da , i);
    }
    for (int x = 0; x < DynamicArray_size(da) - 1; x++){
        for (int y = 0; y < DynamicArray_size(da) - x - 1; y++){
            if (a[y] < a[y+1]){
                temp = a[y+1];
                a[y+1] = a[y];
                a[y] = temp;
            }
        }
    }
    if (DynamicArray_size(da)%2 != 0){
        re = a[DynamicArray_size(da) / 2 + 1];
        return re;
    }else {
        re = (a[DynamicArray_size(da) / 2] + a[DynamicArray_size(da) / 2 - 1]) / 2;
        return re;
    }
}

double DynamicArray_sum ( const DynamicArray * da ){
    double sum;
    sum = DynamicArray_mean(da) * DynamicArray_size(da);
    return sum;
}

double DynamicArray_last ( const DynamicArray * da ){
    DynamicArray *bb = DynamicArray_copy(da);
    double x;
    x = DynamicArray_pop(bb);
    return x;
}

double DynamicArray_first ( const DynamicArray * da ){
    DynamicArray *bb = DynamicArray_copy(da);
    double x;
    x = DynamicArray_pop_front(bb);
    return x;
}

DynamicArray * DynamicArray_copy ( const DynamicArray * da ){
    DynamicArray *after; 
    memcpy(after , da, DynamicArray_size(da));
    return after;
}

DynamicArray * DynamicArray_range ( double a, double b, double step){
    DynamicArray *aa = DynamicArray_new();
    for (int i = 0; i <= abs(b - a) / step; i++){
        DynamicArray_push(aa, i * step);
    }
    return aa;
}

DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b ){
    DynamicArray *ac = DynamicArray_copy(a);
    for (int i = 0; i < DynamicArray_size(b); i++){
        DynamicArray_push(ac, DynamicArray_get(b, DynamicArray_size(b)));
    }
    return ac;
}

DynamicArray * DynamicArray_take ( DynamicArray * a, int b){
    DynamicArray *ac = DynamicArray_new();
    if (abs(b) > DynamicArray_size(a)){
        ac = DynamicArray_copy(a);
        for (int i = abs(b); i < abs(b); i++){
                DynamicArray_push(ac, 0);
        }
    }else {
        if (b < 0){
            for (int i = 0; i < abs(b); i++){
            DynamicArray_push(ac, DynamicArray_pop(a));
            }
        }else {
            for (int i = 0; i < b; i++){
            DynamicArray_push(ac, DynamicArray_pop_front(a));
        }
    }
    return ac; 
}
    
    
    
    if (b < 0){
        for (int i = 0; i < abs(b); i++){
        DynamicArray_push(ac, DynamicArray_pop(a));
        }
    }else {
        for (int i = 0; i < b; i++){
        DynamicArray_push(ac, DynamicArray_pop_front(a));
        }
    }
    return ac;
}

DynamicArray * DynamicArray_take2 ( DynamicArray * a, int b){
    if (b < 0){
        return DynamicArray_subarray(a, DynamicArray_size(a)-b, DynamicArray_size(a));
    }else {
        return DynamicArray_subarray(a, 0, b);
    }
}