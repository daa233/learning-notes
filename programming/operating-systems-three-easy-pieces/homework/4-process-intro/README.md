
This program, called process-run.py, allows you to see how the state of a
process state changes as it runs on a CPU. As described in the chapter, 
processes can be in a few different states:

```
  RUNNING - the process is using the CPU right now
  READY   - the process could be using the CPU right now
            but (alas) some other process is
  WAITING - the process is waiting on I/O
            (e.g., it issued a request to a disk)
  DONE    - the process is finished executing
```

In this homework, we'll see how these process states change as a program
runs, and thus learn a little bit better how these things work.

To run the program and get its options, do this:

```
prompt> ./process-run.py -h
```

If this doesn't work, type "python" before the command, like this:

```
prompt> python process-run.py -h
```

What you should see is this:
```
Usage: process-run.py [options]

Options:
  -h, --help            show this help message and exit
  -s SEED, --seed=SEED  the random seed
  -l PROCESS_LIST, --processlist=PROCESS_LIST
                        a comma-separated list of processes to run, in the
                        form X1:Y1,X2:Y2,... where X is the number of
                        instructions that process should run, and Y the
                        chances (from 0 to 100) that an instruction will use
                        the CPU or issue an IO
  -L IO_LENGTH, --iolength=IO_LENGTH
                        how long an IO takes
  -S PROCESS_SWITCH_BEHAVIOR, --switch=PROCESS_SWITCH_BEHAVIOR
                        when to switch between processes: SWITCH_ON_IO,
                        SWITCH_ON_END
  -I IO_DONE_BEHAVIOR, --iodone=IO_DONE_BEHAVIOR
                        type of behavior when IO ends: IO_RUN_LATER,
                        IO_RUN_IMMEDIATE
  -c                    compute answers for me
  -p, --printstats      print statistics at end; only useful with -c flag
                        (otherwise stats are not printed)
```

The most important option to understand is the `PROCESS_LIST` (as specified by
the `-l` or `--processlist` flags) which specifies exactly what each running
program (or "process") will do. A process consists of instructions, and each
instruction can just do one of two things: 
- use the CPU 
- issue an IO (and wait for it to complete)

When a process uses the CPU (and does no IO at all), it should simply
alternate between RUNNING on the CPU or being READY to run. For example, here
is a simple run that just has one program being run, and that program only
uses the CPU (it does no IO).

```
prompt> ./process-run.py -l 5:100 
```

Produce a trace of what would happen when you run these processes:
```
Process 0
  cpu
  cpu
  cpu
  cpu
  cpu

Important behaviors:
  System will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)

prompt> 
```

Here, the process we specified is "5:100" which means it should consist of 5
instructions, and the chances that each instruction is a CPU instruction are
100%. 

You can see what happens to the process by using the `-c` flag, which computes the
answers for you:

```
prompt> ./process-run.py -l 5:100 -c
Time     PID: 0        CPU        IOs
  1     RUN:cpu          1
  2     RUN:cpu          1
  3     RUN:cpu          1
  4     RUN:cpu          1
  5     RUN:cpu          1
```

This result is not too interesting: the process is simple in the RUN state and
then finishes, using the CPU the whole time and thus keeping the CPU busy the
entire run, and not doing any I/Os.

Let's make it slightly more complex by running two processes:

```
prompt> ./process-run.py -l 5:100,5:100
```

Produce a trace of what would happen when you run these processes:
```
Process 0
  cpu
  cpu
  cpu
  cpu
  cpu

Process 1
  cpu
  cpu
  cpu
  cpu
  cpu

Important behaviors:
  Scheduler will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)
```

In this case, two different processes run, each again just using the CPU. What
happens when the operating system runs them? Let's find out:

```
prompt> ./process-run.py -l 5:100,5:100 -c
Time     PID: 0     PID: 1        CPU        IOs
  1     RUN:cpu      READY          1
  2     RUN:cpu      READY          1
  3     RUN:cpu      READY          1
  4     RUN:cpu      READY          1
  5     RUN:cpu      READY          1
  6        DONE    RUN:cpu          1
  7        DONE    RUN:cpu          1
  8        DONE    RUN:cpu          1
  9        DONE    RUN:cpu          1
 10        DONE    RUN:cpu          1
```

As you can see above, first the process with "process ID" (or "PID") 0 runs,
while process 1 is READY to run but just waits until 0 is done. When 0 is
finished, it moves to the DONE state, while 1 runs. When 1 finishes, the trace
is done.

Let's look at one more example before getting to some questions. In this
example, the process just issues I/O requests. We specify here tht I/Os take 5
time units to complete with the flag `-L`.

```
prompt> ./process-run.py -l 3:0 -L 5
Produce a trace of what would happen when you run these processes:
Process 0
  io-start
  io-start
  io-start

Important behaviors:
  System will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)
```

What do you think the execution trace will look like? Let's find out:

```
prompt> ./process-run.py -l 3:0 -L 5 -c
Time     PID: 0        CPU        IOs
  1  RUN:io-start          1
  2     WAITING                     1
  3     WAITING                     1
  4     WAITING                     1
  5     WAITING                     1
  6* RUN:io-start          1
  7     WAITING                     1
  8     WAITING                     1
  9     WAITING                     1
 10     WAITING                     1
 11* RUN:io-start          1
 12     WAITING                     1
 13     WAITING                     1
 14     WAITING                     1
 15     WAITING                     1
 16*       DONE
```

As you can see, the program just issues three I/Os. When each I/O is issued,
the process moves to a `WAITING` state, and while the device is busy servicing
the I/O, the CPU is idle. 

Let's print some stats (run the same command as above, but with the `-p` flag)
to see some overall behaviors: 

Stats: Total Time 16
Stats: CPU Busy 3 (18.75%)
Stats: IO Busy  12 (75.00%)

As you can see, the trace took 16 clock ticks to run, but the CPU was only
busy less than 20% of the time. The IO device, on the other hand, was quite
busy. In general, we'd like to keep all the devices busy, as that is a better
use of resources.

There are a few other important flags:
```
  -s SEED, --seed=SEED  the random seed  
    this gives you way to create a bunch of different jobs randomly

  -L IO_LENGTH, --iolength=IO_LENGTH
    this determines how long IOs take to complete (default is 5 ticks)

  -S PROCESS_SWITCH_BEHAVIOR, --switch=PROCESS_SWITCH_BEHAVIOR
                        when to switch between processes: SWITCH_ON_IO, SWITCH_ON_END
    this determines when we switch to another process:
    - SWITCH_ON_IO, the system will switch when a process issues an IO
    - SWITCH_ON_END, the system will only switch when the current process is done 

  -I IO_DONE_BEHAVIOR, --iodone=IO_DONE_BEHAVIOR
                        type of behavior when IO ends: IO_RUN_LATER, IO_RUN_IMMEDIATE
    this determines when a process runs after it issues an IO:
    - IO_RUN_IMMEDIATE: switch to this process right now
    - IO_RUN_LATER: switch to this process when it is natural to 
      (e.g., depending on process-switching behavior)
```

Now go answer the questions at the back of the chapter to learn more.


----

## 问题

**1. 用以下标志运行程序：`./process-run.py -l 5:100,5:100`。CPU利用率（CPU使用时间的百分比）应该是多少？为什么你知道这一点？利用 `-c` 标记查看你的答案是否正确。**

解答：CPU 利用率 100%，因为只有 CPU 计算。
```
$ python process-run.py -l 5:100,5:100 -c -p
Time        PID: 0          PID: 1             CPU             IOs
  1        RUN:cpu           READY               1                
  2        RUN:cpu           READY               1                
  3        RUN:cpu           READY               1                
  4        RUN:cpu           READY               1                
  5        RUN:cpu           READY               1                
  6           DONE         RUN:cpu               1                
  7           DONE         RUN:cpu               1                
  8           DONE         RUN:cpu               1                
  9           DONE         RUN:cpu               1                
 10           DONE         RUN:cpu               1      

Stats: Total Time 10
Stats: CPU Busy 10 (100.00%)
Stats: IO Busy  0 (0.00%)
```


**2．现在用这些标志运行：`./process-run.py -l 4:100,1:0`。这些标志指定了一个包含4条指令的进程（都要使用CPU），并且只是简单地发出I/O并等待它完成。完成这两个进程需要多长时间？利用 `-c` 检查你的答案是否正确。**

解答：总共花了10个时间片。
```
$ python process-run.py -l 4:100,1:0 -c -p
Time        PID: 0          PID: 1             CPU             IOs
  1        RUN:cpu           READY               1                
  2        RUN:cpu           READY               1                
  3        RUN:cpu           READY               1                
  4        RUN:cpu           READY               1                
  5           DONE      RUN:io-start             1                
  6           DONE         WAITING                               1
  7           DONE         WAITING                               1
  8           DONE         WAITING                               1
  9           DONE         WAITING                               1
 10*          DONE            DONE                                

Stats: Total Time 10
Stats: CPU Busy 5 (50.00%)
Stats: IO Busy  4 (40.00%)
```

**3．现在交换进程的顺序：`./process-run.py -l 1:0,4:100`。现在发生了什么？交换顺序是否重要？为什么？同样，用 `-c` 看看你的答案是否正确。**

解答：先运行 I/O 进程，CPU 可以发起 I/O 请求后去运行第二个进程，复用进程1的 I/O 处理时间，总共6个时间片运行完成。

```$ python process-run.py -l 1:0,4:100 -c 
Time        PID: 0          PID: 1             CPU             IOs
  1     RUN:io-start         READY               1                
  2        WAITING         RUN:cpu               1               1
  3        WAITING         RUN:cpu               1               1
  4        WAITING         RUN:cpu               1               1
  5        WAITING         RUN:cpu               1               1
  6*          DONE            DONE                                

Stats: Total Time 6
Stats: CPU Busy 5 (83.33%)
Stats: IO Busy  4 (66.67%)
```

**4．现在探索另一些标志。一个重要的标志是`-S`，它决定了当进程发出I/O时系统如何反应。将标志设置为`SWITCH_ON_END`，在进程进行I/O操作时，系统将不会切换到另一个进程，而是等待进程完成。当你运行以下两个进程时，会发生什么情况？一个执行I/O，另一个执行CPU工作。（`-l 1:0,4:100 -c -S SWITCH_ON_END`）**

解答：这时 CPU 会等待 I/O 完成才运行进程2，总共需要9个时间片才能全部运行完成。

```
$ python process-run.py -l 1:0,4:100 -c -S SWITCH_ON_END -p
Time        PID: 0          PID: 1             CPU             IOs
  1     RUN:io-start         READY               1                
  2        WAITING           READY                               1
  3        WAITING           READY                               1
  4        WAITING           READY                               1
  5        WAITING           READY                               1
  6*          DONE         RUN:cpu               1                
  7           DONE         RUN:cpu               1                
  8           DONE         RUN:cpu               1                
  9           DONE         RUN:cpu               1                

Stats: Total Time 9
Stats: CPU Busy 5 (55.56%)
Stats: IO Busy  4 (44.44%)
```

**5．现在，运行相同的进程，但切换行为设置，在等待I/O时切换到另一个进程（`-l 1:0,4:100 -c -S SWITCH_ON_IO`）。现在会发生什么？利用-c来确认你的答案是否正确。**

解答：同问题3，`-S` 默认参数就是 `SWITCH_ON_IO`。

**6．另一个重要的行为是I/O完成时要做什么。利用 `-I IO_RUN_LATER`，当I/O完成时，发出它的进程不一定马上运行。相反，当时运行的进程一直运行。当你运行这个进程组合时会发生什么？（`./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p`）系统资源是否被有效利用？**

解答：第一个进程需要进行频繁的 I/O 处理，但是每次 I/O 完成后都要花很多时间等待其他 CPU 运行完才能继续发起新的 I/O，大量的时间花在了等待上，CPU 没法复用好进程1 I/O 的时间。
```
$ python process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
Time        PID: 0          PID: 1          PID: 2          PID: 3             CPU             IOs
  1     RUN:io-start         READY           READY           READY               1                
  2        WAITING         RUN:cpu           READY           READY               1               1
  3        WAITING         RUN:cpu           READY           READY               1               1
  4        WAITING         RUN:cpu           READY           READY               1               1
  5        WAITING         RUN:cpu           READY           READY               1               1
  6*         READY         RUN:cpu           READY           READY               1                
  7          READY            DONE         RUN:cpu           READY               1                
  8          READY            DONE         RUN:cpu           READY               1                
  9          READY            DONE         RUN:cpu           READY               1                
 10          READY            DONE         RUN:cpu           READY               1                
 11          READY            DONE         RUN:cpu           READY               1                
 12          READY            DONE            DONE         RUN:cpu               1                
 13          READY            DONE            DONE         RUN:cpu               1                
 14          READY            DONE            DONE         RUN:cpu               1                
 15          READY            DONE            DONE         RUN:cpu               1                
 16          READY            DONE            DONE         RUN:cpu               1                
 17     RUN:io-start          DONE            DONE            DONE               1                
 18        WAITING            DONE            DONE            DONE                               1
 19        WAITING            DONE            DONE            DONE                               1
 20        WAITING            DONE            DONE            DONE                               1
 21        WAITING            DONE            DONE            DONE                               1
 22*    RUN:io-start          DONE            DONE            DONE               1                
 23        WAITING            DONE            DONE            DONE                               1
 24        WAITING            DONE            DONE            DONE                               1
 25        WAITING            DONE            DONE            DONE                               1
 26        WAITING            DONE            DONE            DONE                               1
 27*          DONE            DONE            DONE            DONE                                

Stats: Total Time 27
Stats: CPU Busy 18 (66.67%)
Stats: IO Busy  12 (44.44%)
```

**7．现在运行相同的进程，但使用 `-I IO_RUN_IMMEDIATE` 设置，该设置立即运行发出I/O的进程。这种行为有何不同？为什么运行一个刚刚完成I/O的进程会是一个好主意？**

解答：使用 `-I IO_RUN_IMMEDIATE` 后，可以立即响应进程1的 I/O 完成请求，能够尽快发起下一次新的 I/O 请求，CPU 可以更好地复用这部分 I/O 的时间来处理其他计算，利用率更高。 <br> 运行一个刚刚完成 I/O 的进程，主要优点可能是我们认为这个进程可能会频繁地发起 I/O，运行它就能更多更高效率地利用 CPU；另外就是 I/O 需要等待较久的时间，运行一个刚刚完成 I/O 的进程可以让用户更快得到响应。

```
$ python process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
Time        PID: 0          PID: 1          PID: 2          PID: 3             CPU             IOs
  1     RUN:io-start         READY           READY           READY               1                
  2        WAITING         RUN:cpu           READY           READY               1               1
  3        WAITING         RUN:cpu           READY           READY               1               1
  4        WAITING         RUN:cpu           READY           READY               1               1
  5        WAITING         RUN:cpu           READY           READY               1               1
  6*    RUN:io-start         READY           READY           READY               1                
  7        WAITING         RUN:cpu           READY           READY               1               1
  8        WAITING            DONE         RUN:cpu           READY               1               1
  9        WAITING            DONE         RUN:cpu           READY               1               1
 10        WAITING            DONE         RUN:cpu           READY               1               1
 11*    RUN:io-start          DONE           READY           READY               1                
 12        WAITING            DONE         RUN:cpu           READY               1               1
 13        WAITING            DONE         RUN:cpu           READY               1               1
 14        WAITING            DONE            DONE         RUN:cpu               1               1
 15        WAITING            DONE            DONE         RUN:cpu               1               1
 16*          DONE            DONE            DONE         RUN:cpu               1                
 17           DONE            DONE            DONE         RUN:cpu               1                
 18           DONE            DONE            DONE         RUN:cpu               1                

Stats: Total Time 18
Stats: CPU Busy 18 (100.00%)
Stats: IO Busy  12 (66.67%)
```

**8．现在运行一些随机生成的进程，例如 `-s 1 -l 3:50,3:50`，`-s 2 -l 3:50,3:50`，`-s 3 -l 3:50,3:50`。看看你是否能预测追踪记录会如何变化？当你使用 `-I IO_RUN_IMMEDIATE` 与 `-I IO_RUN_LATER` 时会发生什么？当你使用 `-S SWITCH_ON_IO` 与 `-S SWITCH_ON_END` 时会发生什么？**

解答：略。增加了随机性，和上面类似。
