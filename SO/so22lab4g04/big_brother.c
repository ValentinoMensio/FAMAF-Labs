#include "big_brother.h"
#include "fat_volume.h"
#include "fat_table.h"
#include "fat_util.h"
#include <stdio.h>
#include <string.h>

int bb_is_log_file_dentry(fat_dir_entry dir_entry) {
    return strncmp(LOG_FILE_BASENAME, (char *)(dir_entry->base_name), 3) == 0 &&
           strncmp(LOG_FILE_EXTENSION, (char *)(dir_entry->extension), 3) == 0;
}

int bb_is_log_filepath(char *filepath) {
    return strncmp(BB_LOG_FILE, filepath, 8) == 0;
}

int bb_is_log_dirpath(char *filepath) {
    return strncmp(BB_DIRNAME, filepath, 15) == 0;
}

/* Searches for a cluster that could correspond to the bb directory and returns
 * its index. If the cluster is not found, returns 0.
 */
u32 search_bb_orphan_dir_cluster() {
    u32 bb_dir_start_cluster = 0;
    u32 actual_cluster = 2;
    u32 next_cluster = 0;

    fat_volume vol = get_fat_volume();

    u32 bytes_per_cluster = fat_table_bytes_per_cluster(vol->table);    //calcula cantidad de bytes
    off_t offset = fat_table_cluster_offset(vol->table, bb_dir_start_cluster);  //offset del cluster actual
    u8 *buf = alloca(bytes_per_cluster);                                        //buf byte tiene un cluster
    full_pread(vol->table->fd, buf, bytes_per_cluster, offset);     //mira si hay errores y guarda su tamaño en buf 
    fat_dir_entry dentry = (fat_dir_entry) buf;                     //cambio de tipo
    
    while(actual_cluster<10000){
        next_cluster = fat_table_get_next_cluster(vol->table, actual_cluster);
        offset = fat_table_cluster_offset(vol->table, actual_cluster);
        full_pread(vol->table->fd, buf, bytes_per_cluster, offset);     //mira si hay errores y guarda su tamaño en buf 
        dentry = (fat_dir_entry) buf;
        
        if(fat_table_cluster_is_bad_sector(next_cluster)){
            if(bb_is_log_file_dentry(dentry)){
                bb_dir_start_cluster = actual_cluster;
                break;
            }
        }
        actual_cluster++;

    }
    if(actual_cluster>=10000){
        //creo directorio huerfno si no existe
        actual_cluster = fat_table_get_next_free_cluster(vol->table);
    }
    DEBUG("-----------------------------------------------------Actual Cluster: %d",actual_cluster);
    return bb_dir_start_cluster;
}

int bb_init_log_dir(u32 start_cluster) {
    errno = 0;
     fat_volume vol = NULL;
     fat_tree_node root_node = NULL;
     vol = get_fat_volume();

    //Create a new file from scratch, instead of using a direntry like normally done.
     fat_file loaded_bb_dir = fat_file_init_orphan_dir(BB_DIRNAME, vol->table, start_cluster);

     fat_table_set_next_cluster(vol->table, start_cluster, FAT_CLUSTER_BAD_SECTOR);

    //Add directory to file tree. It's entries will be like any other dir.
     root_node = fat_tree_node_search(vol->file_tree, "/bb");
     vol->file_tree = fat_tree_insert(vol->file_tree, root_node, loaded_bb_dir);

    return -errno;
}
