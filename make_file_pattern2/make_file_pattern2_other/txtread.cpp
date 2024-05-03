#include <boost/program_options.hpp>
#include <cstddef>
#include <string>
#include <txtRead/txtRead.hpp>

namespace po = boost::program_options;
int main(int argc, char **argv) {
  // 定义命令行参数
  po::options_description desc("Allowed options");
  desc.add_options()("help,h", "帮助")(
      "i1", po::value<std::string>()->default_value("BEM_INPUT_1_132273.txt"),
      "输入文件1")(
      "i2", po::value<std::string>()->default_value("BEM_INPUT_1_132273.txt"),
      "输入文件2")("l1", po::value<int>()->default_value(2),
                   "top")("l2", po::value<int>()->default_value(2), "bot")(
      "save_name,s", po::value<std::string>()->default_value("2.txt"));
  // 命令行解析
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  // 帮助
  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }
  // 命令行参数声明
  auto l1 = vm["l1"].as<int>();
  auto l2 = vm["l2"].as<int>();
  auto save_name = vm["save_name"].as<std::string>();
  auto filename1 = vm["i1"].as<std::string>();
  auto filename2 = vm["i2"].as<std::string>();

  // 打开文件
  txtRead a;
  txtRead b; // b用于读取中间的部分
  // std::string filename{"BEM_INPUT_1_132273.txt"};
  try {
    a.Open(filename1);
  } catch (std::runtime_error) {
    a.Open(filename1);
  }
  // a.test();
  //  读取文件
  a.Read();

  try {
    b.Open(filename2);
  } catch (std::runtime_error) {
    b.Open(filename2);
  }
  b.Read();
  a.set_CellVecAdd(b.get_CellVecAdd(0.6745, 0.4875));
  // 写文件

  /*
  // 搜索
  std::vector<std::size_t> number{};
  // number = a.Search(Point<2, double>{-0.7476, 0.25});
  number = a.Search(0.25, 0);
  for (auto i : number) {
    std::cout << i << " ";
  }*/
  a.Replace_layer(l1, l2);
  a.Write(save_name);

  // a.Search(Point<2, double>{1, 2});
}
