# learn-protobuf

Tutorial: [Protocol Buffer Basics: Python](https://developers.google.com/protocol-buffers/docs/pythontutorial).

## Install

```bash
$ conda install protobuf
$ protoc --version
libprotoc 3.19.1
```

## Compile

```
$ protoc -I=. --python_out=. ./addressbook.proto
```

## Run

Write some messages:
```bash
python write_message.py address_book.bin
```

Read the messages:
```bash
python read_message.py address_book.bin
```
