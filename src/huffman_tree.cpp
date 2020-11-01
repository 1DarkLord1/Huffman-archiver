#include "huffman_tree.h"

using namespace huff_arch;

void huff_tree::build_tree(node_tree_queue& q) noexcept {
    auto create_nodes = [](tree_node& L, tree_node& R, tree_node& P, u_short ch) {
        L.par = R.par = ch;
        L.type = 0, R.type = 1;
        P = tree_node(ch, L.weight + R.weight, L.num, R.num);
    };

    u_short ch = UCHAR_MAX;
    while(q.size() > 1) {
        tree_node L = q.top();
        q.pop();
        tree_node R = q.top();
        q.pop();
        ch++;
        create_nodes(tree[L.num] = L, tree[R.num] = R, tree[ch], ch);
        q.push(tree[ch]);
    }
}

huff_tree::huff_tree(const std::string& data) noexcept {
    std::array <std::size_t, UCHAR_MAX + 1> chars_cnt = {0};
    node_tree_queue q;
    for(u_char ch: data) {
        chars_cnt[ch]++;
    }
    if(std::count(chars_cnt.begin(), chars_cnt.end(), 0) == chars_cnt.size() - 1) {
        chars_cnt[(chars_cnt[0] != 0 ? 1: 0)]++;
    }
    for(u_short ch = 0; ch <= UCHAR_MAX; ch++) {
        if(chars_cnt[ch] != 0) {
            q.push(tree_node(ch, chars_cnt[ch]));
        }
    }
    build_tree(q);
}

huff_tree::huff_tree(const std::vector <u_short>& encd_tree) noexcept: _root(0) {
    auto link_edges = [](tree_node& par, tree_node& l_son, tree_node& r_son) {
        par.l_node = l_son.num, par.r_node = r_son.num;
        l_son.type = 0, r_son.type = 1;
    };
    for(std::size_t i = 0; i < tree.size(); i++) {
        tree[i].num = i;
    }
    for(std::size_t i = 0; i + 2 < encd_tree.size(); i += 3) {
        u_short l_num = encd_tree[i + 1];
        u_short r_num = encd_tree[i + 2];
        u_short par_num = encd_tree[i];
        _root = std::max(_root, par_num);
        link_edges(tree[par_num], tree[l_num], tree[r_num]);
    }
    std::for_each(tree.begin(), tree.end(), [](tree_node& node) {
        if(node.num <= UCHAR_MAX) {
            node.is_terminal = 1;
        }
    });
}

std::vector <u_short> huff_tree::tree_encode() const noexcept {
    std::vector <u_short> code;
    auto& tree_link = tree;
    auto add_edge = [&code, &tree_link](const tree_node& cur_node) {
        if(cur_node.l_node != tree_node::undef) {
            code.push_back(cur_node.num);
            code.push_back(cur_node.l_node);
            code.push_back(cur_node.r_node);
        }
    };
    std::for_each(tree.begin(), tree.end(), add_edge);
    return code;
}

tree_node huff_tree::root() const noexcept {
    return tree[_root];
}

tree_node huff_tree::l_node(const tree_node& node) const noexcept {
    return (node.l_node == tree_node::undef ? node: tree[node.l_node]);
}

tree_node huff_tree::r_node(const tree_node& node) const noexcept {
    return (node.r_node == tree_node::undef ? node: tree[node.r_node]);
}

tree_node huff_tree::par(const tree_node& node) const noexcept {
    return (node.par == tree_node::undef ? node: tree[node.par]);
}

bool huff_tree::is_terminal(const tree_node& node) const noexcept {
    return node.is_terminal;
}

bool huff_tree::type(const tree_node& node) const noexcept {
    return node.type;
}

u_short huff_tree::get_num(const tree_node& node) const noexcept{
    return node.num;
}

tree_node huff_tree::get_node(u_short num) const noexcept{
    return tree[num];
}
