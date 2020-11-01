#include "tree_node.h"

using namespace huff_arch;

tree_node::tree_node(u_short _num, std::size_t _weight, u_short _l_node,
    u_short _r_node, u_short _par, bool _type, bool _is_terminal) noexcept: num(_num),
    weight(_weight), l_node(_l_node), r_node(_r_node), par(_par), type(_type), is_terminal(_is_terminal) {}

bool tree_node::tree_node_comparator::operator()(const tree_node& F, const tree_node& S) const {
    return F.weight > S.weight || (F.weight == S.weight && F.num > S.num);
}

bool tree_node::operator==(const tree_node& Other){
    return num == Other.num;
}

bool tree_node::operator!=(const tree_node& Other) {
    return !(*this == Other);
}
