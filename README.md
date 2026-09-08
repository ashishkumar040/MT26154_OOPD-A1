# OOPD Assignment 1 — README

**Name:** Ashish Kumar
**Roll No:** MT26154

## before Q3, some setup context

so from Q3 onwards we don't get the normal C/C++ libraries anymore. everything compiled with `-nostdlib -ffreestanding`, meaning no cout, no cin, none of it. had to build a bit of a foundation myself for Q3-Q5 to run on top of:

`syscall.S` - has `_start` in it since nothing else is going to give us one. also a `syscall3` wrapper for read/write, and `syscall6` (aliased `syscall`) for calls needing more args.

`basicIO.h`/`basicIO.cpp` - this is my iostream stand-in basically. `inputint()`, `inputstring()` in two versions (no-arg one returns an internal buffer, `char*, int` version lets you supply your own), `outputint()`, `outputstring()`, plus `errorstring()`/`errorint()` for stderr. all built directly on `syscall3`.

not going to repeat this every section below but everything past this point needs these two files to do any I/O at all.

---

## Q1

Nothing code-wise for this one, just the private `oopd-a1` repo plus an initial README pushed before any actual work started.

## Q2 - minimal no-stdlib program

Files: `q2.cpp`, `q2_shell.sh`

Point was just to confirm the toolchain works before the harder `-nostdlib`/`-ffreestanding` build kicks in later. `q2.cpp` is `int main(){ return 0; }` and that's it. `q2_shell.sh` does `g++ q2.cpp -o q2_1 -nostdlib++` then runs the binary.

Kept separate from the syscall.S stuff on purpose - `-nostdlib++` only drops the C++ stdlib, so you still get a C runtime and `_start` from the system here. Not the case anymore once Q3 starts.

## Q3 - name, age, y/n confirm

Files: `Q3_assign.cpp`, `Q3_shell.sh`

Take a name + age using nothing but our own syscalls, echo them back, then ask for y/n and report the outcome.

Name goes in `stu_name[60]`, age in `stu_age`, both via `io.inputint()`/friends, printed straight back. Confirmation char sits in `cnfrm[2]`, read with `io.inputstring(cnfrm, 2)` (one char + null terminator).

y/Y → "saved". n/N → "cleared", and resets `stu_name[0]` to `'\0'`, `stu_age` to 0. anything else → "Input is invalid", nothing touched. after the branch either way, name + age get printed again so the final state is actually visible, not just implied.

build: `Q3_shell.sh` assembles `syscall.S` with nasm, compiles `basicIO.cpp` + `Q3_assign.cpp` with `-nostdlib -ffreestanding -fno-exceptions -fno-rtti`, links statically via `g++ -nostdlib -static`, runs.

worth noting - `basicIO::inputint()` just reads digits (optional leading minus) and stops at the first non-digit rather than bailing entirely. bad input degrades to a partial number or 0 rather than crashing. matters a lot more without libc backing you up.

## Q4 - user decides how many names

Files: `q4.cpp`, `Q4_shell.sh`

made a separate branch first, per the assignment. keeps this off the Q1-Q3 commits.

ask the count first, then allocate exactly that. no overflow, period.

`NameLists` = one slot, `char name1[1][128]`, `allocate()` prompts + reads via `io.inputstring()`, `operator[]` for access, `print()` for output.

`Name_Lists` = `NameLists s[150]` (`Max_Cap`) + a size counter. main() reads the count as a raw string, manually checks every char is a digit (rejects empty/garbage rather than defaulting to 0), then confirms it's between 1 and 150 before touching anything. that range check at input time is really the whole overflow guard - array can't physically go past 150 anyway.

reading as string + parsing by hand instead of `io.inputint()` directly was kind of the whole point here, lets bad input actually get rejected instead of silently becoming 0.

## Q5 - grow/shrink, operator overloading

Files: `q4.cpp` (same class), `Q4_shell.sh`

extends Q4, lets you change the count afterward, has to go through operator overloading rather than a named function.

`operator+`: `list + n` grows by n. works out new size, caps at 150 if it'd overflow (prints something when that happens), calls `allocate()` per new slot, updates size. `operator-`: `list - n` shrinks size by n, floored at 0 - didn't bother touching the underlying data for removed slots since `printALL()` stops at current size regardless. both return `*this` by reference, mutates in place.

main(): initial `num` names allocated via `people + num`. then asks if you want to change the count. if yes, sign + delta, both validated, then either `people + delta` or `people - delta` runs. `printALL()` shows the result. one more y/n at the end to confirm.

why + and - specifically - assignment wanted operator overloading here, and `people + delta` reads more naturally than a separate named method would've. Q4 and Q5 share the class and the main() flow, so both stayed in q4.cpp instead of getting split up, banner just prints "Question 5" so it's obvious what's running.

---

## My Learning from this assignment

the OOP bit, encapsulation, operator overloading, wasn't really the hard part once I/O was in place. the real learning was one level down honestly. Q2 just confirmed the toolchain worked. building I/O from raw syscalls for Q3 through Q5 is what actually showed how much iostream is quietly doing that you never see. writing `outputint()` digit by digit, parsing numbers by hand off raw strings, setting up `_start` in `syscall.S` myself - those are the parts that made it stick.

## Prompts Used
-> basicIO.h, basicIO.cpp,syscall.s, these are the three files shared explain me their functionallity and their connectivity.
-> i want to run my sh files without using standard library, help me in this.
-> in the given oopd assignment how question3  is extension of  question 4 and 5.
-> expalin  how dynamic memory allocation concept used in question.