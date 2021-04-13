from random import choice, randint
# cmds = ["Reverse", "Insert", "Delete", "Query"]
cmds = ["Query"]
n = 5*10**4
q = 5*10**4
# n = 10
# q = 50
arr = [randint(-10**5, 10**5) for i in range(n)]

input_f = "p6-in"
sol_f = "p6-ans"
with open(input_f, mode="w+") as f:
    arr_str = ""
    for i in range(len(arr)):
        arr_str += f"{arr[i]} "
        if i%10 == 9:
            arr_str += "\n"
    arr_str += "\n"
    f.write(f"{n} {q}\n")
    f.write(arr_str)

with open(sol_f, mode="w+") as f:
    pass

with open(input_f, mode="a") as f1:
    with open(sol_f, mode="a") as f2:
        # special
        sliced = sorted(arr)

        for i in range(q):
            cmd = choice(cmds)
            N = len(arr)
            if cmd == "Query":
                # l = randint(1, N)
                # r = randint(l, N)
                l = 1
                r = N
                k = randint(1, r-l+1)
                full_cmd = f"{cmd} {l} {r} {k}\n"
                f1.write(full_cmd)
                # sliced = sorted(arr[l-1:r])
                answer = str(sliced[k-1]) + "\n"
                f2.write(answer)

