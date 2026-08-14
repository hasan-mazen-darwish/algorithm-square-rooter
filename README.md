# Square Rooter Algorithm

A C++ algorithm that implements the long division method to find the square root of a function up to a specified digit. Built with using a mobile phone only.

## Requirements

The only thing you really need is a device. Once you compile the given code to a binary that runs on your machine, you are good to go.

**How do I compile the code?** You either have to install GCC or Cling.

to install GCC, you can see their official documentation [here](https://gcc.gnu.org/install/). Please note that gcc is not supported in Termux, but when installing Clang on Termux (a compiler that does the same thing as gcc), it creates a hyperlink that refers gcc and g++ directly to the clang package.

To install Clang (probably for Termux), you can refer to their [official documentation](https://clang.llvm.org/get_started.html), or if you are on Termux, just run these commands:
`pkg update & pkg upgrade -y`
then
`pkg install clang -y`


## Clone, build and run

to clone, you can simply run this:
`git clone https://github.com/hasan-mazen-darwish/algorithm-square-rooter.git`

and then
`cd algorithm-square-rooter`

after that, you will find teo files: `build.sh` and `run.sh`, they already are built so you execute the build.sh and then run the resulting binary file with run.sh, but if you know a better way, you can modify them and get them to work your own way. And, please consider installing GCC (or clang on Termux. works perfectly without the need to change anything in the build.sh file). but if you prefer Clang, you can change g++ to cling++.

After that, the program is running!

## limits

Please consider that this algorithm is too low for large digits, even if it is well optimized, because the way the long division method makes it longer to deal with. It follows the time rule of O(n²), here is a benchmark of the times eact text file got generated:

| file | digits | time |
|------|--------|------|
| `sqrt_2_1M.txt` | 1,000,000 | 2h 4m 41s |
| `sqrt_2_100K.txt` | 100,000 | 67s |
| `sqrt_2_10K.txt` | 10,000 | 839ms |
| `sqrt_2_1K.txt` | 1,000 | 28ms |
| `sqrt_2_100.txt` | 100 | 3ms |

And please note that these times are for generating the square root of the number 2 for a precision of a given digit. The device used was the Termux on POCO X7 Pro.

## Input

For the input, it will request you to insert the number you want to square root. You can put an arbitrary big or precise number, because the number you insert is a string at the string itself gets vectorized and divided into parts for the long division method.

For the digits, note that the digits you insert are the exact number of the digits that will be written in the file. E.g. you put 200 as the input and 1 as the digits, you get only 1, and not 14.1 .

Another note, if you put the input as 4, it will still infinitely write zeros after the 2. as long as it did not hit the limit of the digits, because I did not make the algorithm to output a pure 2 when square rooting 4.

For the last inout, it is the file. The program will ask you for the file name you want to store the file in it. Please note that the file name you will choose will automatically be before a .txt file. If you wish to use another file extension, feel free to use the command `mv filename.txt filename.yourextension`.
