/*
 * list.h
 *
 *  Created on: 2012-12-28
 *      Author: lingb@newlandcomputer.com
 */

#ifndef LIST_H_
#define LIST_H_

/**
 * @ingroup list
 * @{
 */
/**
 * 通用链表节点结构
 */
typedef struct {
	void * next;    /**< 指向下一个节点 */
	void * element; /**< 指向节点存放的数据项 */
}list_node_t;


/**
 * 通用链表头节点结构
 */
typedef struct {
	int num_elt;		/**< 节点总数 */
	list_node_t * node; /**< 指向第一个结点 */
}list_t;

int list_init(list_t ** li);
int list_uninit(list_t * li);
int list_eol(list_t * li, int i);
list_node_t * list_get_node(list_t * li, int pos);
void * list_get(list_t * li, int pos);
void * list_remove(list_t * li, int pos);
int list_add(list_t * li, void * element, int pos);
void * list_find(list_t * li, int (*cmp_func) (void * data, void * node), void * data);
int list_get_pos(list_t * li, void * node);
int list_for_each(list_t * li, void (*call)(void * data, void * element), void * data);
int list_cleanup(list_t * li, void (*callback)(void * data, void * element), void * data, int freehead);

#endif /* LIST_H_ */
