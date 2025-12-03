#ifndef AIV_VECTOR
#define AIV_VECTOR

typedef struct vector {
    void** items;
    size_t count;
    size_t capacity;
} vector_t;

// Alternative separated from struct definition
// typedef struct aiv_vector aiv_vector;

vector_t vector_new();
void vector_destroy(vector_t* vector);

void vector_add(vector_t* vector, void* item);

void* vector_at(vector_t* vector, size_t index);

void vector_sort_bubble(vector_t* vector, int (*comparator)(void* item1, void* item2) );

void vector_remove(vector_t* vector, size_t index) ;

void vector_insert(vector_t* vector, size_t index, void* item) ;

int vector_size(vector_t* vector) ;

void vector_reallocate(vector_t* vector) ;

int vector_is_empty(vector_t* vector);

void swap(int* a, int* b) ;

int partition(int arr[], int low, int high) ;

void quickSort(int arr[], int low, int high) ;

//set
#endif