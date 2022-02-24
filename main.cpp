#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

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

Skills skills;
int skills_count;
std::vector<Contr> contr;
std::vector<Proj> proj;

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

void stupid()
{
    out << proj.size() << "\n";
    int cur = 0;
    for (Proj &p : proj)
    {
        out << p.name << "\n";
        int n = p.sk.size();
        for (int i = 0 ; i < n ; ++i)
        {
            out << contr[cur].name << " ";
            cur = (cur + 1) % contr.size();
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
}
