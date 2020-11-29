#include <fstream>
#include <iostream>
#include <filesystem>
#include <experimental/filesystem>
namespace fs = std::filesystem;
 
int main()
{
    fs::create_directories("/tmphm/xw202/ece551/090_ch20_rq/page");
    std::ofstream("/tmphm/xw202/ece551/090_ch20_rq/page/page1.txt");
    std::ofstream("/tmphm/xw202/ece551/090_ch20_rq/page/page2.txt");
    for(auto& p: fs::directory_iterator("/tmphm/xw202/ece551/090_ch20_rq/page"))
        std::cout << p.path() << '\n';
    fs::remove_all("/tmphm/xw202/ece551/090_ch20_rq/page");
}
