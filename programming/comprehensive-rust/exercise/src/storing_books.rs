struct Book {
    title: String,
    year: u16,
}

struct Library {
    books: Vec<Book>,
}

impl Book {
    // Constructor
    fn new(title: &str, year: u16) -> Book {
        Book {
            title: String::from(title),
            year,
        }
    }
}

impl Library {
    fn new() -> Library {
        Library { books: Vec::new() }
    }

    fn len(&self) -> usize {
        self.books.len()
    }

    fn is_empty(&self) -> bool {
        self.books.len() == 0
    }

    fn add_book(&mut self, book: Book) {
        self.books.push(book);
    }

    fn print_books(&self) {
        for (idx, book) in self.books.iter().enumerate() {
            println!("No.{}: {}, published in {}", idx + 1, book.title, book.year);
        }
    }

    fn oldest_book(&self) -> Option<&Book> {
        let mut _oldest_book: Option<&Book> = None;
        for book in &self.books {
            _oldest_book = match _oldest_book {
                Some(old_book) => {
                    if book.year < old_book.year {
                        Some(book)
                    } else {
                        Some(old_book)
                    }
                }
                None => Some(book),
            };
        }
        _oldest_book
    }
}

// Exercise: Storing Books
pub fn storing_books() {
    let mut library = Library::new();

    println!(
        "The library is empty: library.is_empty() -> {}",
        library.is_empty()
    );

    library.add_book(Book::new("Lord of the Rings", 1954));
    library.add_book(Book::new("Alice's Adventures in Wonderland", 1865));

    println!(
        "The library is no longer empty: library.is_empty() -> {}",
        library.is_empty()
    );

    library.print_books();

    match library.oldest_book() {
        Some(book) => println!(
            "The oldest book is {}, published in {}",
            book.title, book.year
        ),
        None => println!("The library is empty!"),
    }

    println!("The library has {} books", library.len());
    library.print_books();
}
