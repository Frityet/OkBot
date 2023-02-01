
To define a new assembly line:

```cpp
Factory {
    {  }
};
```

In the {  }, the instructions that will run are defined, where the type of the instruction is

```cpp
using Instruction = std::function<void(const std::atomic<class Factory::Queue> *_Nullable input, std::atomic<class Factory::Queue> *_Nonnull output)>;
```

The output of the previous instruction, (nullptr if none) gets fed into the current instruction, like a shell pipe, which inspires the next syntax, using the `|` operator to specify the next instruction, if they are intended to run in parallel, with the `&&` or `and` operator being used for sequential operations.

```cpp
Factory {
    { move(1_cm) | write_dist() and move(-1_cm)}
};
```

One key feature of this system is for “subtasks”, an issue I took many hours to figure out. Each production line can have another production line running concurrently, where the output from the previous instruction being fed into the input of the first instruction of the sub-task

```cpp
Factory {
    { move(1_m) | { rotate(90) } and move(-1_m)}
};
```

The code being executed here will move the robot forward by 1 metre whilst also rotating it by 90 degrees, then once after the rotation and movement is finished, the robot will move backwards by a metre.
