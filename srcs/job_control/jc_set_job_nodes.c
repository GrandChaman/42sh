#include "sh21.h"

void	set_job(t_ast_node *root)
{
	if (root->tag_gpid < 0)
		root->tag_gpid = jc_create_tag();
	if (root->type == PIPE)
	{
		root->left->tag_gpid = root->tag_gpid;
		root->right->tag_gpid = root->tag_gpid;
	}
	if (root->mod_gpid == BG)
	{
		root->left->mod_gpid = root->mod_gpid;
		if (root->right)
			root->right->mod_gpid = root->mod_gpid;
		if (root->left)
			root->left->tag_gpid = root->tag_gpid;
	}
}
