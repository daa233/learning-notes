import sys

from addressbook_pb2 import AddressBook
from google.protobuf.json_format import MessageToDict, MessageToJson, Parse, ParseDict

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} ADDRESS_BOOK_FILE")
        sys.exit(-1)

    address_book = AddressBook()

    # Read the existing address book.
    with open(sys.argv[1], "rb") as f:
        address_book.ParseFromString(f.read())

    # Convert message to json string
    json_obj = MessageToJson(address_book)
    print(f"JSON: {type(json_obj)} \n{json_obj}")

    # Convert json string to message
    message_from_json = Parse(json_obj, AddressBook())
    print(f"Message from json: {type(message_from_json)} \n{message_from_json}")

    # Convert message to dict
    dict_obj = MessageToDict(address_book)
    print(f"Dict: {type(dict_obj)} \n{dict_obj}")

    # Convert dict to message
    message_from_dict = ParseDict(dict_obj, AddressBook())
    print(f"Message from dict: {type(message_from_dict)} \n{message_from_dict}")

    assert address_book == message_from_json == message_from_dict
