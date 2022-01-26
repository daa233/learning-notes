import sys

import addressbook_pb2


# Iterates through all people in the AddressBook and prints info about them.
def list_people(address_book):
    for person in address_book.people:
        print(f"Person ID: {person.id}")
        print(f"  Name: {person.name}")
        if person.HasField("email"):
            print(f"  E-mail address: {person.email}")

        for phone_number in person.phones:
            if phone_number.type == addressbook_pb2.Person.PhoneType.MOBILE:
                print(f"  Mobile phone #: {phone_number.number}")
            elif phone_number.type == addressbook_pb2.Person.PhoneType.HOME:
                print(f"  Home phone #: {phone_number.number}")
            elif phone_number.type == addressbook_pb2.Person.PhoneType.WORK:
                print(f"  Work phone #: {phone_number.number}")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} ADDRESS_BOOK_FILE")
        sys.exit(-1)

    address_book = addressbook_pb2.AddressBook()

    # Read the existing address book.
    with open(sys.argv[1], "rb") as f:
        address_book.ParseFromString(f.read())

    list_people(address_book)
