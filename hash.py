def Hash(value, n):
    return value % n

def linear_probing(H, index, n):
    i = 1
    while H[index] != 0:
        new_index = (index + i) % n
        if H[new_index] == 0:
            return new_index
        i += 1
    return -1  # Hash table is full

def quadratic_probing(H, index, n):
    i = 1
    while H[index] != 0:
        new_index = (index + i**2) % n
        if H[new_index] == 0:
            return new_index
        i += 1
        if i >= n:
            return -1  # Table full
    return index

n = int(input("Enter the total number of clients: "))
H = [0] * n
H2 = [0] * n

for i in range(n):
    x = int(input(f"Enter the telephone number of client {i+1}: "))
    index = Hash(x, n)
    
    # Linear Probing
    if H[index] == 0:
        H[index] = x
    else:
        new_index = linear_probing(H, index, n)
        if new_index != -1:
            H[new_index] = x
        else:
            print("Linear probing failed: Table full")

    print("Linear:", H)
    
    # Quadratic Probing
    if H2[index] == 0:
        H2[index] = x
    else:
        new_index = quadratic_probing(H2, index, n)
        if new_index != -1:
            H2[new_index] = x
        else:
            print("Quadratic probing failed: Table full")

    print("Quadratic:", H2)

print("\nFinal hash tables:")
print("Using linear probing:", H)
print("Using quadratic probing:", H2)
