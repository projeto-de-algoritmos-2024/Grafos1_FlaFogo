#include <stdio.h>
#include <stdlib.h>

int qtd_cameras = 0;
/*struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};*/
 
// n -> null
// p -> Preciso de monitoramento
// m -> Estou sendo monitorado
// c -> sou uma camera

char dfs(struct TreeNode *root)
{
    if(root == NULL) return 'n';

    char left = dfs(root -> left);
    int right = dfs(root -> right);

    if(left == 'n' && right == 'n') return 'p';
    else if((left == 'p' || right == 'p'))
    {
        qtd_cameras++;
        return 'c';
    }
    else if(left == 'c' || right == 'c')
    {
        return 'm';
    }

    return 'p';
}

int minCameraCover(struct TreeNode* root) 
{
    if(dfs(root) == 'p') qtd_cameras++;
    return qtd_cameras;
}