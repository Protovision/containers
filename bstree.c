#include "bstree.h"

void bstree_init(BSTREE *t, size_t element_size, int (*compare)(const void*, const void*))
{
	t->root = NULL;
	t->size = 0;
	t->element_size = element_size;
	t->compare = compare;
}

void bstree_destroy(BSTREE *t)
{
	bstree_clear(t);
	t->root = NULL;
	t->size = 0;
	t->element_size = 0;
	t->compare = NULL;
}

void _bstree_rec_clear(struct _bstree_node *node)
{
	if (node == NULL) return;
	_bstree_rec_clear(node->left);
	_bstree_rec_clear(node->right);
	free(node);
}

void bstree_clear(BSTREE *t)
{
	_bstree_rec_clear(t->root);	
}

struct _bstree_node *_bstree_new_node(BSTREE *t, const void *key)
{
	struct _bstree_node *new;
	new = (struct _bstree_node*)malloc(sizeof(struct _bstree_node) + t->element_size);
	new->left = NULL;
	new->right = NULL;
	memcpy(new->key, key, t->element_size);
	++t->size;
	return new;
}

const void *_bstree_rec_insert(BSTREE *tree, struct _bstree_node *node, const void *key)
{
	int cmp;
	struct _bstree_node *new;

	if (node == NULL) {
		new = _bstree_new_node(tree, key);
		tree->root = new;
		return new->key;
	}

	cmp = tree->compare(key, node->key);
	if (cmp < 0) {
		if (node->left == NULL) {
			new = _bstree_new_node(tree, key);
			node->left = new;
			return new->key;	
		} else {
			return _bstree_rec_insert(tree, node->left, key);
		}	
	} else if (cmp > 0) {
		if (node->right == NULL) {
			new = _bstree_new_node(tree, key);
			node->right = new;
			return new->key;
		} else {
			return _bstree_rec_insert(tree, node->right, key);
		}
	}
	memcpy(node->key, key, tree->element_size);
	return node->key; 
}

const void *bstree_insert(BSTREE *t, const void *key)
{
	return _bstree_rec_insert(t, t->root, key);
}

const void *_bstree_rec_find(BSTREE *t, struct _bstree_node *node, const void *key)
{
	int cmp;
	if (node == NULL) return NULL;
	cmp = t->compare(key, node->key);
	if (cmp < 0) {
		return _bstree_rec_find(t, node->left, key);
	} else if (cmp > 0) {
		return _bstree_rec_find(t, node->right, key);
	}
	return node->key;
}

const void *bstree_find(BSTREE *t, const void *key)
{
	return _bstree_rec_find(t, t->root, key);
}

int _bstree_rec_remove(BSTREE *t, struct _bstree_node *parent, struct _bstree_node *child, const void *key)
{
	int cmp;
	struct _bstree_node *tchild, *tparent;

	if (child == NULL) return -1;
	cmp = t->compare(key, child->key);
	if (cmp < 0) {
		return _bstree_rec_remove(t, parent, child->left, key);
	} else if (cmp > 0) {
		return _bstree_rec_remove(t, parent, child->right, key);
	}

	if (child->left == NULL) {
		if (parent->left == child) {
			parent->left = child->right;
		} else {
			parent->right = child->right;
		}
	} else if (child->right == NULL) {
		if (parent->left == child) {
			parent->left = child->left;
		} else {
			parent->right = child->right;
		}
	} else if (child->left != NULL && child->right != NULL) {
		tparent = child;
		for (tchild = child->right; tchild->left != NULL; tchild = tchild->left) {
			tparent = tchild;
		}
		memcpy(child->key, tchild->key, t->element_size);
		if (tchild->right != NULL) tparent->left = tchild->right;
		free(tchild);
		--t->size;
		return 0;
	}
	--t->size;
	free(child);
	return 0;
}

int bstree_remove(BSTREE *t, const void *key)
{
	return _bstree_rec_remove(t, NULL, t->root, key);	
}

void _bstree_rec_iterate(BSTREE *t, struct _bstree_node *node, void (*callback)(const void *key))
{
	if (node == NULL) return;
	_bstree_rec_iterate(t, node->left, callback);
	callback(node->key);
	_bstree_rec_iterate(t, node->right, callback);
}

void bstree_iterate(BSTREE *t, void (*callback)(const void *key))
{
	_bstree_rec_iterate(t, t->root, callback);
}
