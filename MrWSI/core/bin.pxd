from MrWSI.core.resource cimport res_t
from libcpp cimport bool

cdef extern from "bin.h":
    struct bin_node_t
    struct item_t
    struct bin_t
    struct mempool_t

    int node_time(bin_node_t* node)

    mempool_t* bin_create_node_pool(int dimension, size_t buffer_size)
    mempool_t* bin_create_item_pool(int dimension, size_t buffer_size)
    void mp_free_pool(mempool_t*pool)

    bin_t* bin_create(int dimension, mempool_t*node_pool, mempool_t*item_pool)
    void bin_free(bin_t* bin)
    void bin_print(bin_t* bin)

    int bin_dimension(bin_t* bin)
    bool bin_is_empty(bin_t* bin)
    int bin_open_time(bin_t* bin)
    int bin_close_time(bin_t* bin)
    int bin_length(bin_t* bin)
    void bin_to_array(bin_t* bin, int* sts, res_t* usages, int dim)
    int bin_span(bin_t* bin)

    res_t* bin_peak_usage(bin_t* bin, bool force)
    # int bin_current_block(bin_t* bin, int time, res_t* volumn)
    int bin_current_block(bin_t* bin, int time, res_t* volumn,
                      bin_node_t* start_node, bin_node_t** current_node)
    int bin_earliest_slot(bin_t* bin, res_t* capacities, res_t* demands, int length,
                          int est, bin_node_t** start_node, bool only_forward)
    int bin_earliest_slot_2(bin_t* bin_x, bin_t* bin_y, res_t* capacities_x,
                            res_t* capacities_y, res_t* demands_x, res_t* demands_y, int length,
                            int est, bin_node_t** start_node_x,
                            bin_node_t** start_node_y)
    int bin_finish_time_for_demands(bin_t* bin, res_t* capacities, res_t demand,
                                    int di, int st)
    item_t* bin_alloc_item(bin_t* bin, int start_time, res_t* demands, int length,
                          bin_node_t*start_node)
    void bin_free_item(bin_t* bin, item_t* item)
    void bin_extendable_interval(bin_t* bin, item_t* item, res_t* capacities,
                                 int* ei_begin, int* ei_end)
    item_t* bin_extend_item(bin_t* bin, item_t* item, int st, int ft)

cdef class MemPool:
    cdef mempool_t* c_ptr

cdef class BinNode:
    cdef bin_node_t* c_ptr

cdef class Item:
    cdef item_t* c_ptr

cdef class Bin:
    cdef bin_t* c_ptr
    cpdef current_block(Bin self, int time, BinNode node)
