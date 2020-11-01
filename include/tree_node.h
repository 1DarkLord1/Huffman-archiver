#pragma once

#include <climits>
#include <sys/types.h>

namespace huff_arch {

class huff_tree;

class tree_node {
private:
    static const u_short undef = USHRT_MAX;

    struct tree_node_comparator {
        bool operator()(const tree_node& F, const tree_node& S) const;
    };

    u_short num;

    std::size_t weight;

    u_short l_node, r_node, par;

    bool type, is_terminal;

public:
    friend class huff_tree;
    friend class tree_node_comparator;

    bool operator==(const tree_node& Other);
    bool operator!=(const tree_node& Other);

    tree_node(u_short _num = undef, std::size_t _weight = 0, u_short _l_node = undef,
        u_short _r_node = undef, u_short _par = undef, bool _type = 0, bool is_terminal = 0) noexcept;
};

}
