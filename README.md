cpp-lru-cache
=============

Simple and reliable LRU (Least Recently Used) cache for c++ based on hashmap and linkedlist. The library is header only, simple test and example are included.
It includes standard components and very little own logics that guarantees reliability.

How to run tests(need clone googletest)

```
mkdir build
cd build
cmake ..
make check
```

Full Example(原有代码使用例子):
```
#include "lrucache.hpp"
#include <iostream>

int main()
{
    /**Creates cache with maximum size of three. When the 
    size in achieved every next element will replace the 
    least recently used one */
    
    cache::lru_cache<int, std::string> cache(3);

    cache.put(0, "zero");
    cache.put(1, "two");
    cache.put(2, "three");
    cache.put(3, "four");
    cache.put(4, "five");

    const std::string &from_cache = cache.get(4);
    std::cout << from_cache << std::endl;

    return 0;
}

```
中文版本：

学习lamerman/cpp-lru-cache的lru的实现，记录学习中遇到的疑问。

####namespace

[C++命名空间](https://www.runoob.com/cplusplus/cpp-namespaces.html)

[维基百科-名字空间](https://zh.wikipedia.org/wiki/%E5%91%BD%E5%90%8D%E7%A9%BA%E9%97%B4)

####typename

[typename](https://zh.wikipedia.org/wiki/Typename)

[知无涯之C++ typename的起源与用法](http://feihu.me/blog/2014/the-origin-and-usage-of-typename/)

源代码修改注释版本：

include/lrucache.hpp

修改部分实现方式
添加注释
修改函数接口
简单单测


