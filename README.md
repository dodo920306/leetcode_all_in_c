# LeetCode All in C

I want to solve LeetCode questions but only with C this time, and I will upload solutions here.

Any PR about the existing solutions is welcomed, while that for the nonexistent solutions isn't since I want to solve them myself first.

## Prerequisites

* A C compiler

## Installation

First, clone the repository.

```bash
$ git clone https://github.com/dodo920306/leetcode_all_in_c.git
$ cd leetcode_all_in_c
```

Second, another repository must also be included since sadly I can't make every data structure from scratch (I wish I could).

```bash
$ git clone https://github.com/troydhanson/uthash.git
```

And, This is totally legal since even [Leetcode itself](https://support.leetcode.com/hc/en-us/articles/360011833974-What-are-the-environments-for-the-programming-languages) recommend it.

## Usage

Use your C compiler on your computer to compile each solution and run it, simple as that.

If you're using `gcc`, you can simply test every question with

```bash
$ chmod +x test.sh
$ ./test.sh ${question_number}
```
.

## Content

In every solution provided here, there must be a main function in it to provide an example input to the solution function.

The example inputs used here typically came from the question descriptions provided by LeetCode itself originally.
