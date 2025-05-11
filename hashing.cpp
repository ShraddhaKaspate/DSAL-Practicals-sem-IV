size = 10
client_list = [None] * size

def add_client():
    client_id = int(input("Client ID: "))
    name = input("Client Name: ")
    telephone = input("Client Telephone Number: ")
    client_details = [client_id, name, telephone]

    index = client_id % size
   
    for i in range(size):
        if client_list[index] is None:
            client_list[index] = client_details
            print("Client details added at index:", index, client_details)
            break
        else:
            index = (index + 1) % size
    print("\nClient List:", client_list)

def search_client():
    client_id = int(input("Enter client ID to search: "))
    index = client_id % size
    cnt = 0
    for i in range(size):
        if client_list[index] is not None:
            cnt += 1
            if client_list[index][0] == client_id:
                print("Client found at index", index, client_list[index])
                print("\nNumber of comparisons required to search client ID %d are %d." % (client_id, cnt)) 
                break
        index = (index + 1) % size
    else:
        print("Client not found")
   

def main():
    while True:
        print("\t1 : Add Client")
        print("\t2 : Search Client")
        print("\t3 : Exit")
        ch = int(input("Enter your choice: "))
        
        if ch == 3:
            print("End of Program")
            break
        elif ch == 1:
            add_client()
        elif ch == 2:
            search_client()
        else:
            print("Wrong choice entered! Try again.")

main()
