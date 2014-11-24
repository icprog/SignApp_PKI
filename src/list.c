/**
 * @defgroup list ͨ�õ�������
 * @{
 */
/*
 * @file list.c
 * @brief ͨ�õ�������ʵ��
 *
 * ����ʹ��ͷ�ڵ㣬���������еĽ���������ָ���һ������ָ�롣
 * ʵ�ֵ��������������
 * - 1.list_init	 ��ʼ������ͷ�ڵ�
 * - 2.list_uninit	 ��������ͷ�ڵ�
 * - 3.list_eol		 �ж�ָ��λ���Ƿ�λ�����������
 * - 4.list_get		 ��ȡ�����������ָ��λ�õĽ���������
 * - 5.list_remove   �Ƴ�������ָ��λ�õĽ�㣬�����ش�ŵ�������
 * - 6.list_add      ��ĳ����������ӵ������е�ָ��λ�ã���Ϊ�䴴��һ����㣩
 * - 7.list_find     ���ҷ���ĳ�������Ľ�㣬���������ŵ�������
 * - 8.list_get_pos  ���ݽ���ŵ�������ָ�룬���ؽ������λ��
 * - 9.list_for_each ʹ��ָ���ص�������������
 * - 10.list_cleanup ����������Ľ�㣬�������û�ָ���Ļص�����
 *
 * @version 0.98
 * @author yemt@newlandcomputer.com
 * @date 2010-01-07
 */
#include <stdlib.h>

#include "list.h"

/**
 * ��ʼ������ͷ�ڵ㣬ʹ��calloc��֤������0
 * @param li  ���ض�̬���䵽��ͷ�ڵ�ָ��
 * @return
 * - -1 ʧ��
 * - 0  �ɹ�
 */
int list_init(list_t ** li)
{
	*li = (list_t *)calloc(1, sizeof (list_t));
	if (*li == NULL) {
		return -1;
	}
	return 0;
}

/**
 * ��������ͷ�ڵ�
 * @param li  Ҫ���ٵ�ͷ�ڵ�ָ��
 * @return
 * - 0  �ɹ�
 */
int list_uninit(list_t * li)
{
	free(li);
	return 0;
}

/**
 * �ж�ָ��λ���Ƿ�λ������β���֮��
 * @param li  ����ͷ�ڵ�
 * @param i   ָ��λ��
 * @return
 * - 0  ��
 * - 1  ��
 */
int list_eol(list_t * li, int i)
{
	if (li == NULL) return 1;
	if ((i >= 0) && (i < li->num_elt)) {
		return 0;
	}
	return 1; /* end of list */
}

list_node_t * list_get_node(list_t * li, int pos)
{
	int i = 0;
	list_node_t * ntmp;

	if ((li == NULL) || (pos < 0) || (pos >= li->num_elt)) {
		/* element does not exist */
		return NULL;
	}
	ntmp = li->node;
	while (pos > i) {
		i ++;
		ntmp = (list_node_t *)ntmp->next;
	}
	return ntmp;
}
/**
 * ����ָ��λ�ýڵ��ŵ�������
 * @param li     ����ͷ�ڵ�
 * @param pos    ָ��λ��
 * @return void* ������ָ�룬NULL��ʾ����������������ָ����λ�ò���������
 */
void * list_get(list_t * li, int pos)
{
	list_node_t * ntmp = list_get_node(li, pos);
	if (ntmp) {
		return ntmp->element;
	}
	return NULL;
}

/**
 * ɾ��ָ��λ�ýڵ㣬�����ش�ŵ�������
 * @param li     ����ͷ�ڵ�
 * @param pos    ָ��λ��
 * @return void* ������ָ�룬NULL��ʾ����������������ָ����λ�ò���������
 */
void* list_remove(list_t * li, int pos)
{
	int i = 0;
	void * element;
	list_node_t * ntmp,** tmp;

	if ((li == NULL) || (pos < 0) || (pos >= li->num_elt)) {
		/* element does not exist */
		return NULL;
	}
	tmp = &(li->node);
	while (pos > i) {
		i ++;
		tmp = (list_node_t **)&((*tmp)->next);
	}
	ntmp = *tmp;
	*tmp = (list_node_t *)((*tmp)->next);
	-- li->num_elt;
	element = ntmp->element;
	free(ntmp);
	return (element);
}
/**
 * ��ָ��λ�ô����ڵ㣬�������û�������ýڵ�
 * @param li       ����ͷ�ڵ�
 * @param element  ָ���û��������ָ��
 * @param pos      ָ��λ��
 * @return int �����µĽڵ���
 */
int list_add(list_t * li, void * element, int pos)
{
	int i = 0;
	list_node_t * ntmp,** tmp;

	if (li == NULL) return -1;

	if (pos < 0 || pos >= li->num_elt) {
		pos = li->num_elt;
	}
	tmp = &(li->node);
	while (pos > i) {
		i ++;
		tmp = (list_node_t **)&((*tmp)->next);
	}
	ntmp = (list_node_t *)malloc(sizeof (list_node_t));
	ntmp->element = element;
	ntmp->next = *tmp;
	*tmp = ntmp;
	return (++ li->num_elt);
}

/**
 * ���ҷ���������������
 * @param li        ����ͷ�ڵ�
 * @param cmp_func  �û��ṩ�Ļص������������ж��Ƿ����������0�ǣ�1��
 * @param data      �ص������ĵ�һ�����������û�ָ�����ڶ���������̶�Ϊ�ڵ�ָ��
 * @return void* ���ز��ҵ���������ָ�룬NULL��ʾ�������δ�ҵ�
 */
void * list_find(list_t * li, int (*cmp_func) (void * data, void * node), void * data)
{
	list_node_t * ntmp;

	if (li == NULL) {
		return NULL;
	}
	ntmp = li->node;
	while (ntmp) {
		if (cmp_func(data, ntmp) == 0) {
			break;
		}
		ntmp = ntmp->next;
	}
	return (ntmp == NULL ? NULL : ntmp->element);
}

/**
 * ���ش��ָ��������Ľڵ��λ��
 * @param li    ����ͷ�ڵ�
 * @param node  ָ���û�ָ����������
 * @return int  ���ظ��������λ�ã�-1��ʾ����������������Ҳ���
 */
int list_get_pos(list_t * li, void * node)
{
	int i = 0;
	list_node_t * ntmp;
	if (li == NULL || node == NULL) return -1;
	ntmp = li->node;
	while (ntmp) {
		if (ntmp->element == node) {
			return i;
		}
		i ++;
		ntmp = ntmp->next;
	}
	return -1;
}

/**
 * ��ָ���ص�������������
 * @param li    ����ͷ�ڵ�
 * @param call  �ص�����ָ��
 * @param data  �ص������ĵ�һ���������û�ָ�����ڶ��������ǽڵ�λ�ã�����������Ϊ�ڵ��ŵ�������ָ��
 * @return 0
 */
int list_for_each(list_t * li, void (*call)(void * data, void * element), void * data)
{
	int i = 0;
	list_node_t * ntmp = NULL;

	if (li == NULL)
		return 0;

	ntmp = li->node;
	while (ntmp) {
		if (call) {
			call(data, ntmp->element);
		}
		i ++;
		ntmp = ntmp->next;
	}
	return 0;
}

int list_for_each_breakoff(list_t * li, int (*call)(void * data, void * element), void * data)
{
	int i = 0;
	list_node_t * ntmp = NULL;

	if (li == NULL)
		return 0;
	ntmp = li->node;
	while (ntmp) {
		if (call) {
			if(call(data, ntmp->element)<0)
				return -1;
		}
		i ++;
		ntmp = ntmp->next;
	}
	return 0;
}

/**
 * ��գ���������������нڵ㣬��Ϊÿ���������û�ָ���ص�����
 * @param li        ����ͷ�ڵ�
 * @param callback  �ص�����ָ��
 * @param data      �ص������ĵ�һ���������û�ָ�����ڶ�������Ϊ�ڵ��ŵ�������ָ��
 * @param freehead  �Ƿ��ͷ�ͷ�ڵ㣬��0��ʾ�ͷ�
 * @return 0
 */
int list_cleanup(list_t * li, void (*callback)(void * data, void * element), void * data, int freehead)
{
	list_node_t * ntmp, *tmp;
	if (li == NULL) return 0;
	ntmp = li->node;
	while (ntmp) {
		if (callback) {
			callback(data, ntmp->element);
		}
		tmp = ntmp;
		ntmp = ntmp->next;
		free(tmp);
	}
	li->node = NULL;
	li->num_elt = 0;
	if (freehead) {
		free(li);
	}
	return 0;
}


/** @} */

