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
 * ͨ������ڵ�ṹ
 */
typedef struct {
	void * next;    /**< ָ����һ���ڵ� */
	void * element; /**< ָ��ڵ��ŵ������� */
}list_node_t;


/**
 * ͨ������ͷ�ڵ�ṹ
 */
typedef struct {
	int num_elt;		/**< �ڵ����� */
	list_node_t * node; /**< ָ���һ����� */
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
