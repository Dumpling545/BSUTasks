#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;
/**
    Проверить и сравнить следующие стандартные алгоритмы для set и multiset:
        include, set_intersection, set_difference, set_union

    Разница в том, что multiset учитывает повторяющиеся элементы, а set нет.

    Пример:
        Size of set#1/multiset#1:7
        Size of set#2/multiset#2: 7

        Set#1/multiset#1: 1 1 2 3 4 4 5
        Set#2/multiset#2: 2 2 4 4 6 7 8

        Set#1 includes set#2: no
        Multiset#1 includes multiset#2: no

        Intersection(set#1, set#2):  | 2 | 4 |
        Intersection(multiset#1, multiset#2):  | 2 | 4 | 4 |

        Difference(set#1, set#2):  | 1 | 3 | 5 |
        Difference(multiset#1, multiset#2):  | 1 | 1 | 3 | 5 |

        Union(set#1, set#2):  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
        Union(multiset#1, multiset#2):  | 1 | 1 | 2 | 2 | 3 | 4 | 4 | 5 | 6 | 7 | 8 |
*/
void print(set<int> s){
    cout << " | ";
    for(set<int>::iterator it = s.begin(); it != s.end(); it++){
        cout <<  *it << " | ";
    }
    cout <<endl;
}
void m_print(multiset<int> s){
    cout << " | ";
    for(multiset<int>::iterator it = s.begin(); it != s.end(); it++){
        cout <<  *it << " | ";
    }
    cout <<endl;
}
int main()
{
    set<int> set_1, set_2;
    multiset<int> m_set_1, m_set_2;
    int n, m;
    int k = 0;
    cout << "Size of set#1/multiset#1:" << endl;
    cin >> n;
    cout << "Size of set#2/multiset#2:" << endl;
    cin >> m;
    cout << "Set#1/multiset#1:" <<endl;
    for(int i = 0; i < n; i++){
        cin >> k;
        set_1.insert(k);
        m_set_1.insert(k);
    }
    cout << "Set#2/multiset#2:" <<endl;
    for(int i = 0; i < m; i++){
        cin >> k;
        set_2.insert(k);
        m_set_2.insert(k);
    }
    //includes
    bool is_include = includes(set_1.begin(), set_1.end(), set_2.begin(), set_2.end());
    bool m_is_include = includes(m_set_1.begin(), m_set_1.end(), m_set_2.begin(), m_set_2.end());
    cout << "Set#1 includes set#2: " << (is_include ? "yes" : "no")  << endl;
    cout << "Multiset#1 includes multiset#2: " << (m_is_include ? "yes" : "no") << endl;
    //set_intersection
    set<int> intersection;
    multiset<int> m_intersection;
    set_intersection(set_1.begin(), set_1.end(),
                        set_2.begin(), set_2.end(),
                        inserter(intersection, intersection.begin()));
    set_intersection(m_set_1.begin(), m_set_1.end(),
                        m_set_2.begin(), m_set_2.end(),
                        inserter(m_intersection, m_intersection.begin()));
    cout << "Intersection(set#1, set#2): ";
    print(intersection);
    cout << "Intersection(multiset#1, multiset#2): ";
    m_print(m_intersection);
    //set_difference
    set<int> difference;
    multiset<int> m_difference;
    set_difference(set_1.begin(), set_1.end(),
                        set_2.begin(), set_2.end(),
                        inserter(difference, difference.begin()));
    set_difference(m_set_1.begin(), m_set_1.end(),
                        m_set_2.begin(), m_set_2.end(),
                        inserter(m_difference, m_difference.begin()));
    cout << "Difference(set#1, set#2): ";
    print(difference);
    cout << "Difference(multiset#1, multiset#2): ";
    m_print(m_difference);
    //set_union
    set<int> union_set;
    multiset<int> m_union_set;
    set_union(set_1.begin(), set_1.end(),
                        set_2.begin(), set_2.end(),
                        inserter(union_set, union_set.begin()));
    set_union(m_set_1.begin(), m_set_1.end(),
                        m_set_2.begin(), m_set_2.end(),
                        inserter(m_union_set, m_union_set.begin()));
    cout << "Union(set#1, set#2): ";
    print(union_set);
    cout << "Union(multiset#1, multiset#2): ";
    m_print(m_union_set);
    return 0;
}
