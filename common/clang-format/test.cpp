#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

namespace buz {
namespace engine {
class Engine
{};

template<class T>
class SceneGraph
{};
}    // namespace engine
}    // namespace buz

template<class T>
void foo(T callback)
{
}

namespace buz {
namespace engine {
class MyClass
{
  template<class T>
  struct TreeNode
  {
    T value;
    TreeNode * parent;
    TreeNode * left;
    TreeNode * right;
  };

private:
  int a_;
  int b_;
  int c_;
  int d_;

public:
  MyClass(int a, int b, int c, int d)
    : a_(a)
    , b_(b)
    , c_(c)
    , d_(d)
  {
    // other statements
  }

  std::vector<std::shared_ptr<int>> GetAllValues(std::vector<int> & in,
                                                 int filter,
                                                 int filter2,
                                                 int filter3,
                                                 std::vector<int> & out);

  int GetAllValues2(std::vector<int> & in,
                    int filter,
                    int filter2,
                    int filter3,
                    int filter4);

  int GetAllValues3(std::vector<int> & in,
                    int filter,
                    buz::engine::Engine & filter2,
                    buz::engine::SceneGraph<int> filter3,
                    std::vector<int> & out)
  {
    if (out.empty())
    {
      return {};
    }
    int l = 0;
    int r = out.size() - 1;
    while (l != r)
    {
      const int middle = l + (r - l) / 2;
      if (out[middle] == filter)
      {
        return l;
      }
      else if (out[middle] < 0)
      {
        l = middle;
      }
      else
      {
        r = middle;
      }
    }
    return out[l];
  }
};
}    // namespace engine
}    // namespace buz

int main(int argc, char * argv[])
{
  auto vec = std::vector<int>{1234, 234, 635, 123, 534, 123, 654, 345,};
  auto my_vec = std::vector<int>{};

  std::sort(my_vec.begin(),
            my_vec.end(),
            [](int thisisleftargument, int thisisrightargument) {
              return thisisleftargument < thisisrightargument;
            });
  std::sort(my_vec.begin(),
            my_vec.end(),
            std::not_fn(std::less<unsigned int>()));
  std::sort(my_vec.begin(),
            my_vec.end(),
            std::not_fn(std::less<unsigned int>()));

  bool this_is_a_condition1;
  bool this_is_a_condition2;
  bool this_is_a_condition3;

  struct
  {
    int buff;
  } * ls;

  auto luaX_newstring = [](...) {
    return 42;
  };
  auto luaZ_buffer = [](...) {
    return 42;
  };
  auto luaZ_bufflen = [](...) {
    return 42;
  };

  {
    {
      {
        {
          auto ts = luaX_newstring(ls,
                                   luaZ_buffer(ls->buff),
                                   luaZ_bufflen(ls->buff));
        }
      }
    }
  }

  if (this_is_a_condition1 && this_is_a_condition2)
  {
    // do smth
  }
  else if (this_is_a_condition3)
  {
    // do this
  }

  foo([](int a, int b, int c) {
    std::vector<std::shared_ptr<int>> vec;
  });

  return 0;
}
