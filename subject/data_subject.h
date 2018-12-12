
/*
** Functions returning an int return OK on success but may return an error,
** ERR_ALLOC if it failed to allocate new memory
** ERR_SIZE if it would need to access an element out of bounds
** ERR_MISSING if a search function fails to find the key
** A function that returned an error value must not modify the structure in any way
*/

/*
** array          Return a valid empty array. Don't allocate any memory.
** array_free     Free array, and reset it to an empty state
** array_len      Return length of the used part of the array
** array_reserve  Increase available memory, doesn't affect length
** array_push     Add "size" bytes from "data" to end of array
** array_pop      Remove "size" bytes from end of array, and copy to "data"
*/

t_array		array(void);
void		array_free(t_array *a);
size_t		array_len(const t_array *a);
int			array_reserve(t_array *a, size_t size);
int			array_push(t_array *a, const void *data, size_t size);
int			array_pop(t_array *a, void *data, size_t size);

/*
** array_set_len  Change used length of array to "size". Zeros new bytes.
** array_insert   Insert "size" bytes from "data" at position "i"
**                  Make room by moving data to the right
** array_remove   Remove "size" bytes from position "i" to "data"
**                  Fill room by moving data to the left
*/

int			array_set_len(t_array *a, size_t len);
int			array_insert(t_array *a, const void *data, size_t i, size_t size);
int			array_remove(t_array *a, void *data, size_t i, size_t size);

/* 
** bitset          Return a valid empty bitset. Don't allocate any memory.
** bitset_free     Free bitset, and reset it to an empty state
** bitset_len      Return number of bits in the used part of the bitset
** bitset_set_len  Change number of available bits to "size". Zeros new bits.
** bitset_get      Return the bit at position "i"
** bitset_set      Set the bit at position "i" to "b"
** bitset_display  Display the bitset like:
**                    9: [X__XXXX__]
*/

t_bitset	bitset(void);
void		bitset_free(t_bitset *a);
size_t		bitset_len(const t_bitset *a);
int			bitset_set_len(t_bitset *bitset, size_t len);
bool		bitset_get(const t_bitset *a, size_t i);
void		bitset_set(t_bitset *a, size_t i, bool b);
void        bitset_display(const t_bitset *a);

/*
** bitset_reserve   Increase available memory, doesn't affect length
** bitset_get_safe  Set "b" to the value of the bit at position "i"
** bitset_set_safe  Set the bit at position "i" to the value of "b" 
** bitset_push      Add "b" to the end of the bitset
** bitset_pop       Removes the last bit and store it in "b"
*/

int			bitset_reserve(t_bitset *bitset, size_t new_size);
int			bitset_get_safe(const t_bitset *a, size_t i, bool *out);
int			bitset_set_safe(t_bitset *a, size_t i, bool b);
int			bitset_push(t_bitset *a, bool b);
int			bitset_pop(t_bitset *a, bool *b);

/*
** queue             Return an empty queue, with elements of size "word"
** queue_free        Free queue, and reset it to an empty state
** queue_len         Return number of elements in the queue
** queue_reserve     Increase available memory to "size"
** queue_push_back   Add "data" to back of the queue
** queue_push_front  Add "data" to front of the queue
** queue_pop_back    Remove the last element, and store in "data"
** queue_pop_front   Remove the first element, and store in "data"
*/

t_queue		queue(t_uint word);
void		queue_free(t_queue *a);
size_t		queue_len(const t_queue *a);
int			queue_reserve(t_queue *a, size_t s);
int			queue_push_back(t_queue *a, const void *data);
int			queue_push_front(t_queue *a, const void *data);
int			queue_pop_back(t_queue *a, void *data);
int			queue_pop_front(t_queue *a, void *data);

/*
** sorted
** sorted_free
** sorted_len
** sorted_reserve
** sorted_get      returns a pointer to the nth element
** sorted_search   search for an entry matching "data"
** sorted_insert   inserts data in sorted array
** sorted_delete   remove the entry matching "data", store it inside "out"
*/

t_sorted	sorted(t_predicate predicate, t_uint word);
void		sorted_free(t_sorted *a);
size_t		sorted_len(const t_sorted *a);
int			sorted_reserve(t_sorted *a, size_t s);
const void  *sorted_get(t_sorted *a, size_t index);
t_sorteden	sorted_search(const t_sorted *a, const void *data);
int			sorted_insert(t_sorted *a, const void *data);
t_sorteden	sorted_delete(t_sorted *a, const void *data, void *out);

/*
** sorted_pop           move highest element from sorted array to "data"
** sorted_insert_hint   try to insert "data" at position "hint"
**                        if the hint is wrong, insert normally
** sorted_delete_index  delete the nth element
*/

int			sorted_pop(t_sorted *a, void *data);
int			sorted_insert_hint(t_sorted *a, const void *data, size_t hint);
int			sorted_delete_index(t_sorted *a, size_t index, void *out);

/*
** warning: "o_key" and "o_val" can be NULL
**
** pma_insert     inserts value "val" with key "key"
** pma_get        store entry matching "key" in "o_key" and "o_val"
** pma_delete     remove entry matching "key", store it in "o_key" and "o_val"
** pma_display    display the pma like:
**                  9: [X__XXXX__]
**                  5: {0:A 1:32650 5:32714 6:32545 7:32765}
** pma_pop_back   remove the highest entry, store it in "o_key" and "o_val"
** pma_pop_front  remove the smallest entry, store it in "o_key" and "o_val"
*/

t_pma		pma(t_predicate less_than, t_uint key_size, t_uint value_size);
void		pma_free(t_pma *a);
size_t		pma_len(const t_pma *a);
int			pma_insert(t_pma *a, const void *key, const void *val);
int			pma_get(const t_pma *a, const void *key, void *o_key, void *o_val);
int			pma_delete(t_pma *a, const void *key, void *o_key, void *o_val);
void		pma_display(t_pma *a, t_printer print_key, t_printer print_val);
int			pma_pop_back(t_pma *a, void *key, void *val);
int			pma_pop_front(t_pma *a, void *key, void *val);

/*
** iterators must stay valid unless the pma is modified elsewhere
**
** pma_search    search for entry matching "key", return iterator to entry
** pmait         return iterator to pma, starting at the smallest element
** pmait_next    store current entry to "o_key" and "o_val", increment iterator
** pmait_delete  delete current entry and store to "o_key" and "o_val"
** pmait_display display pma and iterator like:
**                        >----<
**                 9: [X__XXXX__]
**                 5: {0:32664 1:32650 5:32714 6:32545 7:32765}
*/

t_pmaen		pma_search(const t_pma *a, const void *key);
t_pmait		pmait(const t_pma *a);
bool		pmait_next(t_pmait *i, void *o_key, void *o_val);
bool		pmait_delete(t_pmait *i, void *o_key, void *o_val);
void		pmait_display(t_pmait *it, t_printer print_key, t_printer print_char);

/*
** for further information, lookup Rust double-ended iterators
**
** pma_range          return an iterator to every entry
**                      greater or equal than "key_a"
**                      lesser or equal than "key_b"
** pmait_next_back    store element at end of iterator, the decrement end
** pmait_delete_back  delete and store element at end of iterator, the decrement end
*/

t_pmait		pma_range(const t_pma *a, void *key_a, void *key_b);
bool		pmait_next_back(t_pmait *i, void *key, void *val);
bool		pmait_delete_back(t_pmait *i, void *key, void *val);
