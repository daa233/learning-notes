import sys

import addressbook_pb2


# Fills in a Person message based on user input.
def prompt_for_address(person):
    person.id = int(input("Enter person ID number: "))
    person.name = input("Enter name: ")

    email = input("Enter email address (blank for none): ")
    if email != "":
        person.email = email

    while True:
        number = input("Enter a phone number (or leave blank to finish): ")
        if number == "":
            break

        phone_number = person.phones.add()
        phone_number.number = number

        type = input("Is this a mobile, home, or work phone? ")
        if type == "mobile":
            phone_number.type = addressbook_pb2.Person.PhoneType.MOBILE
        elif type == "home":
            phone_number.type = addressbook_pb2.Person.PhoneType.HOME
        elif type == "work":
            phone_number.type = addressbook_pb2.Person.PhoneType.WORK
        else:
            print("Unkown phone type: leaving as default value.")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: {}, ADDRESS_BOOK_FILE".format(sys.argv[0]))
        sys.exit(-1)

    address_book = addressbook_pb2.AddressBook()

    # Read the existing address book.
    try:
        with open(sys.argv[1], "rb") as f:
            address_book.ParseFromString(f.read())
    except IOError:
        print("{}: Could not open file. Creating a new one.".format(sys.argv[1]))

    # Add an address
    prompt_for_address(address_book.people.add())

    # Write the new address book back to disk.
    with open(sys.argv[1], "wb") as f:
        f.write(address_book.SerializeToString())
