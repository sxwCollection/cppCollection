#ifndef SETTINGS_H
#define SETTINGS_H
# include <vector>
using namespace std;
class settings
{
public:
    settings();
    ~settings();
    const int pub_BoardSize=10;
    vector<int> pubB_Ships={5,4,4};

};

#endif // SETTINGS_H
