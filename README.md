# Square Rooter Algorithm

A C++ algorithm that implements the long division method to find the square root of a function up to a specified digit. Built with using a mobile phone only.

## Requirements

The only thing you really need is a device. Once you compile the given code to a binary that runs on your machine, you are good to go.

**How do I compile the code?** You either have to install GCC or Cling.

to install GCC, you can see their official documentation [here](https://gcc.gnu.org/install/). Please note that gcc is not supported in Termux, but when installing Clang on Termux (a compiler that does the same thing as gcc), it creates a hyperlink that refers gcc and g++ directly to the clang package.

To install Clang (probably for Termux), you can refer to their [official documentation](https://clang.llvm.org/get_started.html), or if you are on Termux, just run these commands:
`pkg update & pkg upgrade -y`
then
```bash
pkg install clang -y
```


## Clone, build and run

to clone, you can simply run this:
```bash
git clone https://github.com/hasan-mazen-darwish/algorithm-square-rooter.git
```

and then
```bash
cd algorithm-square-rooter
```

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

For the last inout, it is the file. The program will ask you for the file name you want to store the file in it. Please note that the file name you will choose will automatically be before a .txt file. If you wish to use another file extension, feel free to use the command 
```bash
mv filename.txt filename.yourextension
```

## What I used to build this project

- My mobile phone (POCO X7 Pro)
- Termux (a powerful command line for the Android)
- Helix editor (a powerful code editor for the terminal in general; greatest for coding on mobile)
- Vim editor (to write README.md, for line wrapping)

## The maths

Sorry, I am too lazy to explain the mathematical side of the algorithm, but, here are some great resources you can see, so you can learn the long division:

- [byjus.com, a great source to learn the practical way to use this method to manually calculate the square root. (great to learn how the method is working)](https://byjus.com/maths/square-root-long-division-method/)
- [GeeksForGeeks.org, another great source for the practical way to calculate the long division method.](https://www.geeksforgeeks.org/maths/square-root-long-division-method/)

for the theory, you can search the YouTube for a video explaining how the long division method is working, if you aren't familiar already.

## The programmatic side

Now, we will be talking about how the algorithm actually works with the maths.

So, first of all, we need to get the user input. As you can see in `main.cpp`, we can see this block of code:

```cpp
std::string input;
std::cin >> input;

// ... Input validation
// ... inserting the digits number with multiple std::cout and std::cin

Parts parts = dissectStringNumber(input);
std::vector<uint> whole = parts.whole;
std::vector<uint> decimal = parts.decimal;
```

So, the program is actually getting the number of the user as a string! this property will permit the user to input a crazy number like 123456789.987654321123456789 without getting rounded by the float numbers. Plus, a string is wonderful to dissect to the digits pairs the long division method.

Now, we will be explaining the `dissectStringNumber` function logic.

So, let's take an example of all the cases that this function gets:

- 1234
- 123
- 1234.1234
- 1234.123

So, the method expects pairs of numbers. The pais are determined by the side of the numbers compared to the decimal. If the numbers are on the left side of the decimal (the whole part), we group each two digits from the right to the left. In our examples; 1234 becomes 12 34, and 123 becomes 1 23, and in the second example, since 34 is the closest pair to the decimal point, we will group them. We go to the right, as we add a 0 to the left, we group 01 as another group. But since 0 is meaningless on the left, we will be having 1 alone.

Note that we have a pattern for the whole part: if the number of digits is divisible by 2 (even), that means that we can separate the numbers to pairs at any side; and programmatically, we can run a for loop that dissects the string perfecty. Here are some examples:

- 1234 -> <12, 34>
- 1945 -> <19, 45>
- 20260815 -> <20, 26, 08, 15>

Now, if the number of digits of the whole number is not divisible by 2 (odd), we can simply group the first number alone, and then we will be having a new string without the first number that we can follow the same logic as the even digits case. Here are some examples:

- 12345 -> <1>, dissect(2345) -> <1, 23, 45>
- 911 -> <9>, dissect(11) -> <9, 11>
- 671829011 -> <6>, dissect(71829011) -> <1, 71, 82, 90, 11>

We explained the whole part. Now, for the decimal part. As we discussed, we start the pairs from the decimal point and going on the same direction, adding zeroes on the way, and since the whole part was on the left, adding zeroes was meaningless. But for the right side, it's the most important thing of this process.

So, here the things are easier. Since the pairs are already starting from the index 0; but, here is the trick: if the number of digits was even, we need to multiply the last digit by 10. **why?** because, as we discussed, we add zeroes on the side of the part we are dealing with. And, adding a zero to the right side is meaningful. So, we add a zero to the last of the string, and this is equivalent to multiplying the last digit by 10.

*Adding a 0 to the last of the string is equivalent to multiplying the last digit by 10; here is an example: if we have the number 123 after decimal; adding a 0 would give us 1230 therefore <12, 30>. now, if we dissect it before adding the 0: <12, 3> and then multiply the last digit by 10: <12, 30>. it is identical.*

so, now we covered with this simple logic, any decimal case got discussed. For example:

- 0.123  -> 0.1230 -> <0> , <12, 30>
- 0.1234 -> 0.1234 -> <0> , <12, 34>

**Now, what happens after?** We have 2 cases: the digits are finite (the only one my program is designed for), and when the digits are infinite (you can modify the code to make it possible). Cases of the infinite digits are divisions like 1/3 that produces 0.3333333... . Now, for the finite digits, the pairs would be something like:

0.1234 -> <0> , <12, 34, 00, 00, 00, ...>

we are adding infinite zeros as we continue. And, this is the logic used in the algoirthm I coded, because the user input is finite anyways. But, for the infinite digits, we do not add 0s, because there are still more available digits as we go, so, 1/3 would become like:

1/3 -> <0> , <33, 33, 33, 33, ...>

and a number like, for example, the square root of 2 (e.g. you want to calculate the 4th root of 2), the result number is something big as you scale, and it looks like: 1.41421356237309..., so it is represented as:

√2 -> <1> , <41, 12, 13, 56, 23, 73, 09, ...>

and you can clone the git and modify the algorithm to also fit these numbers!
