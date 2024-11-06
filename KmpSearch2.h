#ifndef KMPSEARCH2_H
#define KMPSEARCH2_H

#endif // KMPSEARCH2_H

#include <QString>
#include <QDebug>
#include <vector>

std::vector<int> Next; // 将 Next 数组改为动态的



void initial(const QString &pat)
{
    int j = 0;
    Next.resize(pat.size());
    Next[0] = 0;
    for (int i = 1; i < pat.size(); i++) {
        while (j > 0 && pat[i] != pat[j]) j = Next[j - 1];
        if (pat[i] == pat[j]) j++;
        Next[i] = j;
    }
}

std::vector<int> kmpSearch(const QString &txt, const QString &target)
{
    std::vector<int>ret;
    ret.push_back(-1);
    if (target.isEmpty()) return ret;

    int tmp=0;
    initial(target);

    int maxsize = txt.size() - 1;
    int j = 0;
    for (int i = 0; i < txt.size(); i++) {
        while (j > 0 && txt[i] != target[j]) j = Next[j - 1];
        if (txt[i] == target[j]) j++;
        if (j == target.size()) {
            tmp = i - j + 1;
            ret.push_back(tmp);
        }
    }
    return ret;
}
