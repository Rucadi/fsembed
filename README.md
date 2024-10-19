# fsembed

Example of use and timing

# Creating the rootfs:

```
fsembed /home/nixos/linux mylinux --absolute

Compiling 93268 entries and 5943 folders
```


# Time to compile linux source tree (1.7GB) into a single object file

Notice that the source generator doesn't generate everything into the same .cpp file to avoid out-of-ram issues when processing large chunks of data. 


```
[nixos@nixos:~/linux_test]$ time make -C fsembed_filesystems/mylinux/ -j8
make: Entering directory '/home/nixos/linux_test/fsembed_filesystems/mylinux'
clang++ -std=c++23  -c 10602.cpp -o 10602.o
clang++ -std=c++23  -c 12035.cpp -o 12035.o
clang++ -std=c++23  -c 13987.cpp -o 13987.o
clang++ -std=c++23  -c 15349.cpp -o 15349.o
clang++ -std=c++23  -c 16628.cpp -o 16628.o
clang++ -std=c++23  -c 17893.cpp -o 17893.o
clang++ -std=c++23  -c 20307.cpp -o 20307.o
clang++ -std=c++23  -c 22113.cpp -o 22113.o
clang++ -std=c++23  -c 2234.cpp -o 2234.o
clang++ -std=c++23  -c 23463.cpp -o 23463.o
clang++ -std=c++23  -c 24836.cpp -o 24836.o
clang++ -std=c++23  -c 26649.cpp -o 26649.o
clang++ -std=c++23  -c 28526.cpp -o 28526.o
clang++ -std=c++23  -c 30419.cpp -o 30419.o
clang++ -std=c++23  -c 30851.cpp -o 30851.o
clang++ -std=c++23  -c 31060.cpp -o 31060.o
clang++ -std=c++23  -c 32246.cpp -o 32246.o
clang++ -std=c++23  -c 32971.cpp -o 32971.o
clang++ -std=c++23  -c 33914.cpp -o 33914.o
clang++ -std=c++23  -c 34358.cpp -o 34358.o
clang++ -std=c++23  -c 34786.cpp -o 34786.o
clang++ -std=c++23  -c 35570.cpp -o 35570.o
clang++ -std=c++23  -c 36181.cpp -o 36181.o
clang++ -std=c++23  -c 36632.cpp -o 36632.o
clang++ -std=c++23  -c 37100.cpp -o 37100.o
clang++ -std=c++23  -c 37716.cpp -o 37716.o
clang++ -std=c++23  -c 38380.cpp -o 38380.o
clang++ -std=c++23  -c 38987.cpp -o 38987.o
clang++ -std=c++23  -c 39652.cpp -o 39652.o
clang++ -std=c++23  -c 40225.cpp -o 40225.o
clang++ -std=c++23  -c 40816.cpp -o 40816.o
clang++ -std=c++23  -c 41262.cpp -o 41262.o
clang++ -std=c++23  -c 4186.cpp -o 4186.o
clang++ -std=c++23  -c 44121.cpp -o 44121.o
clang++ -std=c++23  -c 47349.cpp -o 47349.o
clang++ -std=c++23  -c 48785.cpp -o 48785.o
clang++ -std=c++23  -c 50221.cpp -o 50221.o
clang++ -std=c++23  -c 51532.cpp -o 51532.o
clang++ -std=c++23  -c 52930.cpp -o 52930.o
clang++ -std=c++23  -c 5432.cpp -o 5432.o
clang++ -std=c++23  -c 54390.cpp -o 54390.o
clang++ -std=c++23  -c 55789.cpp -o 55789.o
clang++ -std=c++23  -c 57723.cpp -o 57723.o
clang++ -std=c++23  -c 57863.cpp -o 57863.o
clang++ -std=c++23  -c 57864.cpp -o 57864.o
clang++ -std=c++23  -c 58312.cpp -o 58312.o
clang++ -std=c++23  -c 59134.cpp -o 59134.o
clang++ -std=c++23  -c 59584.cpp -o 59584.o
clang++ -std=c++23  -c 60024.cpp -o 60024.o
clang++ -std=c++23  -c 60762.cpp -o 60762.o
clang++ -std=c++23  -c 61423.cpp -o 61423.o
clang++ -std=c++23  -c 62090.cpp -o 62090.o
clang++ -std=c++23  -c 62471.cpp -o 62471.o
clang++ -std=c++23  -c 62717.cpp -o 62717.o
clang++ -std=c++23  -c 63204.cpp -o 63204.o
clang++ -std=c++23  -c 63863.cpp -o 63863.o
clang++ -std=c++23  -c 64388.cpp -o 64388.o
clang++ -std=c++23  -c 65254.cpp -o 65254.o
clang++ -std=c++23  -c 66077.cpp -o 66077.o
clang++ -std=c++23  -c 66782.cpp -o 66782.o
clang++ -std=c++23  -c 67189.cpp -o 67189.o
clang++ -std=c++23  -c 67502.cpp -o 67502.o
clang++ -std=c++23  -c 67921.cpp -o 67921.o
clang++ -std=c++23  -c 68498.cpp -o 68498.o
clang++ -std=c++23  -c 68918.cpp -o 68918.o
clang++ -std=c++23  -c 6901.cpp -o 6901.o
clang++ -std=c++23  -c 69359.cpp -o 69359.o
clang++ -std=c++23  -c 69912.cpp -o 69912.o
clang++ -std=c++23  -c 70557.cpp -o 70557.o
clang++ -std=c++23  -c 70914.cpp -o 70914.o
clang++ -std=c++23  -c 71344.cpp -o 71344.o
clang++ -std=c++23  -c 71490.cpp -o 71490.o
clang++ -std=c++23  -c 71931.cpp -o 71931.o
clang++ -std=c++23  -c 72674.cpp -o 72674.o
clang++ -std=c++23  -c 73344.cpp -o 73344.o
clang++ -std=c++23  -c 74266.cpp -o 74266.o
clang++ -std=c++23  -c 74752.cpp -o 74752.o
clang++ -std=c++23  -c 75369.cpp -o 75369.o
clang++ -std=c++23  -c 76159.cpp -o 76159.o
clang++ -std=c++23  -c 77125.cpp -o 77125.o
clang++ -std=c++23  -c 78246.cpp -o 78246.o
clang++ -std=c++23  -c 79115.cpp -o 79115.o
clang++ -std=c++23  -c 79661.cpp -o 79661.o
clang++ -std=c++23  -c 80242.cpp -o 80242.o
clang++ -std=c++23  -c 80617.cpp -o 80617.o
clang++ -std=c++23  -c 81103.cpp -o 81103.o
clang++ -std=c++23  -c 81875.cpp -o 81875.o
clang++ -std=c++23  -c 82709.cpp -o 82709.o
clang++ -std=c++23  -c 83472.cpp -o 83472.o
clang++ -std=c++23  -c 84146.cpp -o 84146.o
clang++ -std=c++23  -c 84657.cpp -o 84657.o
clang++ -std=c++23  -c 84953.cpp -o 84953.o
clang++ -std=c++23  -c 85036.cpp -o 85036.o
clang++ -std=c++23  -c 85037.cpp -o 85037.o
clang++ -std=c++23  -c 85041.cpp -o 85041.o
clang++ -std=c++23  -c 85042.cpp -o 85042.o
clang++ -std=c++23  -c 85046.cpp -o 85046.o
clang++ -std=c++23  -c 85047.cpp -o 85047.o
clang++ -std=c++23  -c 85051.cpp -o 85051.o
clang++ -std=c++23  -c 85074.cpp -o 85074.o
clang++ -std=c++23  -c 85076.cpp -o 85076.o
clang++ -std=c++23  -c 85077.cpp -o 85077.o
clang++ -std=c++23  -c 85078.cpp -o 85078.o
clang++ -std=c++23  -c 85081.cpp -o 85081.o
clang++ -std=c++23  -c 85087.cpp -o 85087.o
clang++ -std=c++23  -c 85090.cpp -o 85090.o
clang++ -std=c++23  -c 85091.cpp -o 85091.o
clang++ -std=c++23  -c 85093.cpp -o 85093.o
clang++ -std=c++23  -c 85094.cpp -o 85094.o
clang++ -std=c++23  -c 85095.cpp -o 85095.o
clang++ -std=c++23  -c 85096.cpp -o 85096.o
clang++ -std=c++23  -c 85098.cpp -o 85098.o
clang++ -std=c++23  -c 85099.cpp -o 85099.o
clang++ -std=c++23  -c 85101.cpp -o 85101.o
clang++ -std=c++23  -c 85102.cpp -o 85102.o
clang++ -std=c++23  -c 85105.cpp -o 85105.o
clang++ -std=c++23  -c 85117.cpp -o 85117.o
clang++ -std=c++23  -c 85144.cpp -o 85144.o
clang++ -std=c++23  -c 85163.cpp -o 85163.o
clang++ -std=c++23  -c 85164.cpp -o 85164.o
clang++ -std=c++23  -c 85165.cpp -o 85165.o
clang++ -std=c++23  -c 85170.cpp -o 85170.o
clang++ -std=c++23  -c 85174.cpp -o 85174.o
clang++ -std=c++23  -c 85176.cpp -o 85176.o
clang++ -std=c++23  -c 85177.cpp -o 85177.o
clang++ -std=c++23  -c 85180.cpp -o 85180.o
clang++ -std=c++23  -c 85181.cpp -o 85181.o
clang++ -std=c++23  -c 85182.cpp -o 85182.o
clang++ -std=c++23  -c 85183.cpp -o 85183.o
clang++ -std=c++23  -c 85184.cpp -o 85184.o
clang++ -std=c++23  -c 85210.cpp -o 85210.o
clang++ -std=c++23  -c 85216.cpp -o 85216.o
clang++ -std=c++23  -c 85230.cpp -o 85230.o
clang++ -std=c++23  -c 85239.cpp -o 85239.o
clang++ -std=c++23  -c 85244.cpp -o 85244.o
clang++ -std=c++23  -c 85250.cpp -o 85250.o
clang++ -std=c++23  -c 85256.cpp -o 85256.o
clang++ -std=c++23  -c 85259.cpp -o 85259.o
clang++ -std=c++23  -c 85261.cpp -o 85261.o
clang++ -std=c++23  -c 85264.cpp -o 85264.o
clang++ -std=c++23  -c 85339.cpp -o 85339.o
clang++ -std=c++23  -c 85347.cpp -o 85347.o
clang++ -std=c++23  -c 85393.cpp -o 85393.o
clang++ -std=c++23  -c 85642.cpp -o 85642.o
clang++ -std=c++23  -c 86321.cpp -o 86321.o
clang++ -std=c++23  -c 86937.cpp -o 86937.o
clang++ -std=c++23  -c 8735.cpp -o 8735.o
clang++ -std=c++23  -c 87982.cpp -o 87982.o
clang++ -std=c++23  -c 882.cpp -o 882.o
clang++ -std=c++23  -c 88504.cpp -o 88504.o
clang++ -std=c++23  -c 89261.cpp -o 89261.o
clang++ -std=c++23  -c 90815.cpp -o 90815.o
clang++ -std=c++23  -c 91556.cpp -o 91556.o
clang++ -std=c++23  -c 92251.cpp -o 92251.o
clang++ -std=c++23  -c 93267.cpp -o 93267.o
clang++ -std=c++23  -c folders.cpp -o folders.o
ar rcs fsembed.o 10602.o 12035.o 13987.o 15349.o 16628.o 17893.o 20307.o 22113.o 2234.o 23463.o 24836.o 26649.o 28526.o 30419.o 30851.o 31060.o 32246.o 32971.o 33914.o 34358.o 34786.o 35570.o 36181.o 36632.o 37100.o 37716.o 38380.o 38987.o 39652.o 40225.o 40816.o 41262.o 4186.o 44121.o 47349.o 48785.o 50221.o 51532.o 52930.o 5432.o 54390.o 55789.o 57723.o 57863.o 57864.o 58312.o 59134.o 59584.o 60024.o 60762.o 61423.o 62090.o 62471.o 62717.o 63204.o 63863.o 64388.o 65254.o 66077.o 66782.o 67189.o 67502.o 67921.o 68498.o 68918.o 6901.o 69359.o 69912.o 70557.o 70914.o 71344.o 71490.o 71931.o 72674.o 73344.o 74266.o 74752.o 75369.o 76159.o 77125.o 78246.o 79115.o 79661.o 80242.o 80617.o 81103.o 81875.o 82709.o 83472.o 84146.o 84657.o 84953.o 85036.o 85037.o 85041.o 85042.o 85046.o 85047.o 85051.o 85074.o 85076.o 85077.o 85078.o 85081.o 85087.o 85090.o 85091.o 85093.o 85094.o 85095.o 85096.o 85098.o 85099.o 85101.o 85102.o 85105.o 85117.o 85144.o 85163.o 85164.o 85165.o 85170.o 85174.o 85176.o 85177.o 85180.o 85181.o 85182.o 85183.o 85184.o 85210.o 85216.o 85230.o 85239.o 85244.o 85250.o 85256.o 85259.o 85261.o 85264.o 85339.o 85347.o 85393.o 85642.o 86321.o 86937.o 8735.o 87982.o 882.o 88504.o 89261.o 90815.o 91556.o 92251.o 93267.o folders.o
rm -f 10602.o 12035.o 13987.o 15349.o 16628.o 17893.o 20307.o 22113.o 2234.o 23463.o 24836.o 26649.o 28526.o 30419.o 30851.o 31060.o 32246.o 32971.o 33914.o 34358.o 34786.o 35570.o 36181.o 36632.o 37100.o 37716.o 38380.o 38987.o 39652.o 40225.o 40816.o 41262.o 4186.o 44121.o 47349.o 48785.o 50221.o 51532.o 52930.o 5432.o 54390.o 55789.o 57723.o 57863.o 57864.o 58312.o 59134.o 59584.o 60024.o 60762.o 61423.o 62090.o 62471.o 62717.o 63204.o 63863.o 64388.o 65254.o 66077.o 66782.o 67189.o 67502.o 67921.o 68498.o 68918.o 6901.o 69359.o 69912.o 70557.o 70914.o 71344.o 71490.o 71931.o 72674.o 73344.o 74266.o 74752.o 75369.o 76159.o 77125.o 78246.o 79115.o 79661.o 80242.o 80617.o 81103.o 81875.o 82709.o 83472.o 84146.o 84657.o 84953.o 85036.o 85037.o 85041.o 85042.o 85046.o 85047.o 85051.o 85074.o 85076.o 85077.o 85078.o 85081.o 85087.o 85090.o 85091.o 85093.o 85094.o 85095.o 85096.o 85098.o 85099.o 85101.o 85102.o 85105.o 85117.o 85144.o 85163.o 85164.o 85165.o 85170.o 85174.o 85176.o 85177.o 85180.o 85181.o 85182.o 85183.o 85184.o 85210.o 85216.o 85230.o 85239.o 85244.o 85250.o 85256.o 85259.o 85261.o 85264.o 85339.o 85347.o 85393.o 85642.o 86321.o 86937.o 8735.o 87982.o 882.o 88504.o 89261.o 90815.o 91556.o 92251.o 93267.o folders.o
make: Leaving directory '/home/nixos/linux_test/fsembed_filesystems/mylinux'

real    0m59.798s
user    6m24.591s
sys     1m3.671s
```


Time to compile an example and link against it:

```cpp

#include "fsembed_filesystems/mylinux/include.hpp"
#include <iostream>
#include "include/fsembed.hpp"

int main()
{
    for(const auto [path, entry] : fsembed::iterateFilesystem(mylinux::folders))
    {
        std::cout<<"Path: "<<path<<"  "<<entry->name<<std::endl;
        std::cout<<"Content: "<<entry->content<<std::endl;
    }
}
```


```
[nixos@nixos:~/linux_test]$ time clang++ -std=c++23 main.cpp fsembed_filesystems/mylinux/fsembed.o 

real    0m2.690s
user    0m1.212s
sys     0m1.322s
```


Time to dump all the contents of all the files of linux repo into a single file:

```
[nixos@nixos:~/linux_test]$ time ./a.out > out.txt

real    0m1.489s
user    0m0.161s
sys     0m1.247s
```

Binary size:

```
[nixos@nixos:~/linux_test]$ ls -lah a.out 
-rwxr-xr-x 1 nixos users 1.8G Oct 19 21:53 a.out
```

Size after compression to a .tar.gz
```
tar -czvf a.tar.gz a.out 
-rw-r--r-- 1 nixos users 506M Oct 19 21:57 a.tar.gz
```