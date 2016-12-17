
/*
 * http://www.geeksforgeeks.org/maximum-difference-between-node-and-its-ancestor-in-binary-tree/
 */

int bigd (node_td *node)
{

    if (!node) return 0xFFFF;

    n =  bigd(node->left);

    diff = node->i - n;

    if (diff > maxdiff) {
        maxdiff = diff;
    }

    bigd(node->right);

    return (n > node->i) ? node->i : n;
}

int 
maxdiff (node_td *node)
{
    if (!node) return MAX_DIFF;

    n1 = maxdiff(node->left);

    diff = node->i - n1;

    if (diff > maxdiff) {
        maxdiff = diff;
    }

    n2 = maxdiff(node->right);

    diff = node->i - n2;
    
    if (diff > maxdiff) {
        maxdiff = diff;
    }

    get_min_3(n1, node->i, n2, &min);

    return min;
}
