#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <list>

std::ifstream in;
std::ofstream out;

typedef std::map<std::string, int> Skills;
typedef std::map<int, int> SkVals;

struct Proj
{
    std::string name;
    int days, score, bb;
    SkVals sk;
};

struct Contr
{
    std::string name;
    SkVals sk;
};

struct Res
{
    std::string name;
    std::list<std::string> a;
};

Skills skills;
int skills_count;
std::vector<Contr> contr;
std::vector<Proj> proj;
std::list<Res> res;

int skill_id(const std::string &s)
{
    auto i = skills.find(s);
    if (i == skills.end())
    {
        auto j = skills.insert({s, skills_count++});
        i = j.first;
    }
    return i->second;
}

void contr_read(Contr &c)
{
    int n;
    in >> c.name >> n;
    for (int i = 0 ; i < n ; ++i)
    {
        std::string s;
        int sk;
        in >> s >> sk;
        c.sk[skill_id(s)] = sk;
    }
}

void proj_read(Proj &p)
{
    int n;
    in >> p.name >> p.days >> p.score >> p.bb >> n;
    for (int i = 0 ; i < n ; ++i)
    {
        std::string s;
        int sk;
        in >> s >> sk;
        p.sk[skill_id(s)] = sk;
    }
}

bool try_proj_slow(Proj &p, Res &r)
{
    std::vector<bool> used(contr.size());
    for (auto s : p.sk)
    {
        bool found = false;
        for (int c = 0 ; c < contr.size() ; ++c)
        {
            if (used[c])
                continue;

            if (contr[c].sk[s.first] >= s.second)
            {
                used[c] = true;
                r.a.push_back(contr[c].name);
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}

void stupid()
{
    for (Proj &p : proj)
    {
        Res r;
        if (try_proj_slow(p, r))
        {
            r.name = p.name;
            res.push_back(r);
        }
    }
}

void print_res()
{
    out << res.size() << "\n";
    for (auto r : res)
    {
        out << r.name << "\n";
        for (auto a : r.a)
        {
            out << a << " ";
        }
        out << "\n";
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return 1;

    in.open(argv[1]);
    out.open(argv[2]);

    int cc, pp;
    in >> cc >> pp;
    contr.resize(cc);
    for (Contr &c : contr)
        contr_read(c);

    proj.resize(pp);
    for (Proj &p : proj)
        proj_read(p);

    stupid();
    print_res();
}
