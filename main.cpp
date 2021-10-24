#include "alge.h"

#include <cassert>
#include <vector>
#include <set>


bool are_edges(const std::vector<Vec3>& vs, size_t i, size_t j, size_t k) {
    Vec3 u = vs[j] - vs[i];
    Vec3 v = vs[k] - vs[i];
    Vec3 n = cross(u, v);
    assert(!as_zero(length(n)));
    
    // find an initial starting vertex, other than i, j, k
    size_t l = 0;
    Vec3 m;
    for (l = 0; l < vs.size(); ++l) {
        if (l != i && l != j && l != k) {
            m = vs[l] - vs[i];
            // This vertex should not be coplanar with i j k
            if (as_zero(dot(m, n))) {
                continue;
            } else {
                break;
            }
        }
    }


    // See if all vertices are on the same side of i j k plane
    // if so, surface. Otherwise not.
    bool sign = as_positive(dot(n, m));

    for (l = 0; l < vs.size(); ++l) {
        if (l == i || l == j || l == k) {
            continue;
        }

        m = vs[l] - vs[i];
        float proj = dot(n, m);
        if (as_zero(proj)) {
            // coplanar
            // continue;
            std::cout << "coplanar " << i << ", " << j << ", " << k << " with " << l << std::endl;
            
            // TODO: experimental, need to add tolerance
            if (dot(cross(u, m), cross(m, v)) < 0) {
                std::cout << "GTFO" << std::endl;
                return false;
            } else {
                continue;
            }
            
        } else if (as_positive(proj) != sign) {
            return false;
        } else {
            continue;
        }
    }
    
    return true;

}

void get_edge_graph(const std::vector<Vec3>& vs, std::vector<std::set<size_t>>& eg) {
    eg.resize(vs.size());
    
    for (size_t i = 0; i < vs.size(); ++i) {
        for (size_t j = i + 1; j < vs.size(); ++j) {
            for (size_t k = j + 1; k < vs.size(); ++k) {
                if (are_edges(vs, i, j, k)) {
                    std::cout << "surface point = " << i << "->" << j << ", " << i << "->" << k << std::endl;
                    eg[i].insert(j);
                    eg[i].insert(k);

                    eg[j].insert(i);
                    eg[k].insert(i);
                }

                if (are_edges(vs, j, i, k)) {
                    std::cout << "surface point = " << j << "->" << i << ", " << j << "->" << k << std::endl;
                    eg[j].insert(i);
                    eg[j].insert(k);

                    eg[i].insert(j);
                    eg[k].insert(j);
                }

                if (are_edges(vs, k, i, j)) {
                    std::cout << "surface point = " << k << "->" << i << ", " << k << "->" << j << std::endl;
                    eg[k].insert(i);
                    eg[k].insert(j);

                    eg[i].insert(k);
                    eg[j].insert(k);
                }
            }
        }
    }
}

// offset point p
Vec3 offset(const Vec3& p,
            const Vec3& p0,
            const Vec3& p1,
            const Vec3& p2,
            float margin) {
    
    
}

int main() {
    std::vector<Vec3> points = {
        Vec3(1, 1, 1),
        Vec3(-1, 1, 1),
        Vec3(-1, -1, 1),
        Vec3(1, -1, 1),
        Vec3(1, 1, -1),
        Vec3(-1, 1, -1),
        Vec3(-1, -1, -1),
        Vec3(1, -1, -1)
    };

    // std::vector<Vec3> points = {
    //     Vec3(1, 0, 0),
    //     Vec3(0, 1, 0),
    //     Vec3(-1, 0, 0),
    //     Vec3(0, -1, 0),
    //     Vec3(0, 0, 1)
    // };

    for (size_t index = 0; index < points.size(); ++index) {
        std::cout << points[index] << "\t@" << index << std::endl;
    }


    std::vector<std::set<size_t>> eg;
    get_edge_graph(points, eg);

    // show edge graph
    for (const auto& s : eg) {
        for (size_t e : s) {
            std::cout << e << ", ";
        }
        std::cout << std::endl;
    }

    // Basic geometric assumption of polygon shape
    for (const auto& e : eg) {
        assert(e.size() >= 3);
    }

    // // test matrix
    // Mat33 m;
    // m[0] = Vec3(1, -1, 0);
    // m[1] = Vec3(0, 5, 3);
    // m[2] = Vec3(2, 0, -9);
    // std::cout << m << std::endl;
    // std::cout << m.inv() << std::endl;

    
    
    
    return 0;
}
