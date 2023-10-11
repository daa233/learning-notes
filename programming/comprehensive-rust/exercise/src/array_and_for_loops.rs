// Arrays and for Loops
pub fn array_and_for_loops() {
    let array = [10, 20, 30];
    println!("array: {array:?}");

    print!("Iterating over array:");
    for n in &array {
        print!(" {n}");
    }
    println!();

    print!("Iterating over range:");
    for i in 0..3 {
        print!(" {}", array[i]);
    }
    println!();
}

fn transpose(matrix: [[i32; 3]; 3]) -> [[i32; 3]; 3] {
    let mut transposed: [[i32; 3]; 3] = [[0; 3]; 3];
    for i in 0..matrix.len() {
        for j in 0..matrix[i].len() {
            transposed[i][j] = matrix[j][i];
        }
    }
    transposed
}

fn pretty_print(matrix: &[[i32; 3]; 3]) {
    print!("[");
    for i in 0..matrix.len() {
        if i != 0 {
            print!(" ");
        }
        print!("{:?}", matrix[i]);
        if i != matrix.len() - 1 {
            print!("\n");
        }
    }
    println!("]")
}

pub fn print_matrix() {
    let matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]];

    println!("matrix:");
    pretty_print(&matrix);

    let transposed = transpose(matrix);
    println!("transposed:");
    pretty_print(&transposed);
}
