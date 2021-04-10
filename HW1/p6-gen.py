from random import choice, randint
# cmds = ["Reverse", "Insert", "Delete", "Query"]
cmds = ["Query"]
n = 50000
q = 50000
arr = [randint(-50000,50000) for i in range(n)]

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
        for i in range(q):
            cmd = choice(cmds)
            N = len(arr)
            if cmd == "Query":
                l = randint(1, N)
                r = randint(l, N)
                k = randint(1, r-l+1)
                full_cmd = f"{cmd} {l} {r} {k}\n"
                sliced = sorted(arr[l-1:r])
                f1.write(full_cmd)
                answer = str(sliced[k-1]) + "\n"
                f2.write(answer)
