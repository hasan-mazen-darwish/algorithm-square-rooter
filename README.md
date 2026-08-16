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

### dissecting the user's number input.

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

√2 -> <1> , <41, 42, 13, 56, 23, 73, 09, ...>

and you can clone the git and modify the algorithm to also fit these numbers!

Now, in the code, we have a `struct` designed to store the whole and decimal part of the number:

```cpp
struct Parts {
  std::vector<uint> whole;
  std::vector<uint> decimal;
};
```

and here, the digits pairs are going to be stored in vectors, like we saw, as 123.123 -> <1, 23>, <12, 30>.

Now, for the dissecting function.

So, the first thing we are doing is taking the number, then look for the dot.

```cpp
size_t dotIndex = input.find('.');
```

Then, we define the strings of the whole and decimal parts. And as a first step, we set the whole part as the full number. Next, as we have ourselves the index of the dot, we see if the dot exists, if it does, then we slice the string into the first part as the whole part, and the second part as the decimal part:

```cpp
std::string wholeString = input;
std::string decimalString = "";
if(dotIndex != std::string::npos) {
    wholeString = input.substr(0, dotIndex);
    decimalString = input.substr(dotIndex + 1);
}
```

and now, we need to filter the whole part. We cannot accept a whole part of "0000000002" for example. We must filter the given whole number, so we check every digit and clear out every zero until we hit a number. If we hit a regular number, we know that the number we have got is now the actual number; and we stop the checking loop. And finally, after that, we simply check if the whole number is empty (since an input like "0.1" for example will make the whole part empty as we terminate the leading 0), we replace it with double zeroes "00" (remember when we said that we need to deal with 2 digits at a time? here, we are handing the algorithm the 2 digits in a plate of gold).

```cpp
for (int i=0; i<wholeString.length() ; i++) {
    if(wholeString[i] != '0') break;
    else wholeString.pop_back();
}
if(wholeString == "") wholeString = "00";
```

Doing the same for the decimal part, even though it is unnecessary, we check the digits from the last digit all the way back to the decimal point, and do the exact same filtering.

```cpp
for (int i=decimalString.length()-1 ; i>=0 ; i--) {
    if(decimalString[i] != '0') break;
    else decimalString.pop_back();
}
```

Now, as the comments of the code explain, I am just setting two booleans to check if the given whole and decimal parts are even or odd:

```cpp
// Here I am checking if the whole numbers are pairs like 1234 or not like 12345
bool isWholePartPairs = wholeString.length()%2 == 0;
// Same for the decimals
bool isDecimalPartPairs = decimalString.length()%2 == 0;
```

Finally, I am applying the theoretical part of dissecting the whole and decimal part of the given input. You can check the code directly to see how it is applied (`main.cpp` file).

Now. After the theoretical and programmatical side of the dissection of the user's input, let's have a look at the mysterious `BigNumber` type.

### Handling huge numbers.

So, when handling with such an algorithm, the expected outputs are very large. Think of hundreds, thousands, or millions of digits (if you go crazy), and the maximum numbers the computer can store is up to 2^64 - 1 (something big but not big enough), think of 18 digits. Now, we need a logic we can use to byoass these limits. To do that, we need **a new base of numbers**.

So, before we introduce the new method, I'll need to explain the base of numbers and how do operations apply to the numbers. Feel free to skip it if you are confident with number bases and the computational side behind them.

So, a number base of n is simply saying that we have n digits to work with. Starting from 0 to n-1. For example, the base 10 we use daily contains 10 digits: starting from 0 to 9. For the binary system, it is a base 2 system, with only 0 and one. The hex, or base 16 system, has 16 digits, starting from 0 to 15, labeling 10 as A, 11 as B, and all the way to 15 as F. It might be confusing, but think of A at hex is 10 in the base 10. It's just the same value, just a different system. You can check [this article](https://betterexplained.com/articles/numbers-and-bases/) for what a number base/system is.

Now, since we answered briefly what a number base is, we need to know why we would need to know about it. So, the main idea, is that we are dealing with huge numbers. Think of hundreds of thousands of digits, and even millions. Achieving this with a single memory location (or, less rigorously, a single unsigned integer) is very impossible. So, we need to divide this huge number into *chunks*.

So, I want to share my thought process of mine with you; feel free to skip. I first though of using strings, as you can store as many digits as you want, then converting these strings into ~17 digits numbers and doing the maths with them all together. That's why I thought of Golang, as one of the best languages I know to deal with strings, especially with the Goroutines. But, this idea does the number chunkizing so badly, as it is very inefficient. But then, I asked the AI, and it suggested using bigger digits (like base 10^17, and I will be telling why this base in a few moments) and store such numbers in arrays/vectors, and I felt that this is the solution! now, a number with 34 digits will beautifully gets separated into 2 chunks of base-10^17 digits! (or 3 if this number was big enough), and I started deploying it.

So, now, we have the idea of making the huge number chunks. So, for this case, we use very high number bases, and store the new digits in arrays/vectors, this way, we can store huge numbers so easily. To show how this is possible, let me give you this example:

let's say I am dealing with base 100 (10^2), and we want to store the number 1343. As we know; 1343 = 13×100^1 + 43×100^0. And, therefore, the new number stored in vectors would be <13, 43>. Now, imagine huge numbers, and replace 100 with 10^17 (one followed by 17 zeroes), a huge number would look like: <1234567890123456, 1234567890123456>. This number is absurdly big that a single integer cannot contain.

So, this is how libraries that deal with huge integers work, and, usually they store numbers in relatively smaller bases than my custom built library, because they are generic. They need to make sure that the max digit multiplied by the max digit won't overwhelm the integer they're dealing with, also that they need to make sure they include negative numbers as well. And here is where the custom logic shines: if you look at the long division method, all the numbers are integers and positive. Also, the max number we multiply a big ingeger with is 100 when we add 2 digits to the right column number (it is equivalent to multiplying the number by 100 and summing those digits). Therefore, we can boost the number of digits to 10^17 comfortably! And these high optimized numbers make the program work faster than using the BigInt libraries and packages, despite having these big libraries very optimized (and absolutely more optimized than my code. Far more). It's just an unfair competition where I use approximately the double of their digits with a language like C++ that's already powerful in maths.

Now, let's discuss the operations. The only operations we need are the addition, substraction, and multiplication.

#### Addition

So, for addition, let's have this example:
1 2 3 4
       +
  9 2 9

So, as we learned in school (and as I did in my algorithm), here we take the first digit of each number and add them. The result is 9+4=13. As we humans do, we take the first digit, 3, and put it in the result, and put the 1 into the carry. Now, we will be doing this programmatically different. So, 3 here is the remainder of dividing the number 13 over the base, which is 10. Programmatically, we denote it as 13%10. Now, this symbol works even for 3%10, as the remainder of the division of a number smaller than the base is the same number.

Now, for the carry, we will divide the number over the base, this way: 13/10. The result is 1.3, and the result means "the number has 1.3 of the bases", and the 0.3 is the remainder! so, what we do, is we round the division to the smaller number (or we call it flooring the number, like the `Math.floor()` in javascript). And for C++, if we store the division in an integer, it automatically floors the decimal to the smallest integer.

And for the rest of the digits, it works the same. But, we just add the carry now. So, for the next digit, it's 1+3+2, as 1 is the carry.
