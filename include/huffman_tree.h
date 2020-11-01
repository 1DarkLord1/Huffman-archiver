#pragma once

#include <string>
#include <climits>
#include <array>
#include <queue>
#include <algorithm>
#include <iostream>
#include "tree_node.h"

namespace huff_arch {

class huff_tree {
private:
    using node_tree_queue = std::priority_queue <tree_node, std::vector <tree_node>, tree_node::tree_node_comparator>;

    u_short _root;

    std::array <tree_node, 2 * (UCHAR_MAX + 1)> tree;

public:
    friend class tree_node;

    huff_tree(const std::string& data) noexcept;
    huff_tree(const std::vector <u_short>& encd_tree) noexcept;

    tree_node root() const noexcept;
    tree_node l_node(const tree_node&) const noexcept;
    tree_node r_node(const tree_node&) const noexcept;
    tree_node par(const tree_node&) const noexcept;

    bool is_terminal(const tree_node&) const noexcept;

    bool type(const tree_node&) const noexcept;

    u_short get_num(const tree_node&) const noexcept;
    tree_node get_node(u_short num) const noexcept;

    std::vector <u_short> tree_encode() const noexcept;

private:
    void build_tree(node_tree_queue & q) noexcept;
};

}
