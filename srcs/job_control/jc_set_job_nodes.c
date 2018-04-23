#include "sh21.h"

void	set_job(t_ast_node *root)
{
	if (root->tag_gpid < 0)
		root->tag_gpid = jc_create_tag();
	if (root->type == PIPE || root->piped_cmd)
	{
		if (root->left)
			root->left->tag_gpid = root->tag_gpid;
		if (root->right)
			root->right->tag_gpid = root->tag_gpid;
	}
}
