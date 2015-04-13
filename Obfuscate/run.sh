#!/bin/bash

cd Test/
clang -S -emit-llvm -o test1.bc test1.c
clang -S -emit-llvm -o test2.bc test2.c
clang -S -emit-llvm -o test3.bc test3.c
clang -S -emit-llvm -o test4.bc test4.c

cd ..
make

opt -load ../../../Release/lib/LLVMObfuscate.so < Test/test1.bc > /dev/null -obfuscate -S > output1.s
opt -load ../../../Release/lib/LLVMObfuscate.so < Test/test1.bc > /dev/null -obfuscate > output1

opt -load ../../../Release/lib/LLVMObfuscate.so < Test/test2.bc > /dev/null -obfuscate -S > output2.s
opt -load ../../../Release/lib/LLVMObfuscate.so < Test/test2.bc > /dev/null -obfuscate > output2

opt -load ../../../Release/lib/LLVMObfuscate.so < Test/test3.bc > /dev/null -obfuscate -S > output3.s
opt -load ../../../Release/lib/LLVMObfuscate.so < Test/test3.bc > /dev/null -obfuscate > output3

opt -load ../../../Release/lib/LLVMObfuscate.so < Test/test4.bc > /dev/null -obfuscate -S > output4.s
opt -load ../../../Release/lib/LLVMObfuscate.so < Test/test4.bc > /dev/null -obfuscate > output4
